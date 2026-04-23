import serial
import serial.tools.list_ports
import struct
import time
import math  # 新增：用于角度计算

# ------------------------------------------------------------
# CRC16 查表（与下位机完全一致）
# ------------------------------------------------------------
CRC_TABLE = [
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf, 0x8c48,
    0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7, 0x1081, 0x0108,
    0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e, 0x9cc9, 0x8d40, 0xbfdb,
    0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876, 0x2102, 0x308b, 0x0210, 0x1399,
    0x6726, 0x76af, 0x4434, 0x55bd, 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e,
    0xfae7, 0xc87c, 0xd9f5, 0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e,
    0x54b5, 0x453c, 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd,
    0xc974, 0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3, 0x5285,
    0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a, 0xdecd, 0xcf44,
    0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72, 0x6306, 0x728f, 0x4014,
    0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9, 0xef4e, 0xfec7, 0xcc5c, 0xddd5,
    0xa96a, 0xb8e3, 0x8a78, 0x9bf1, 0x7387, 0x620e, 0x5095, 0x411c, 0x35a3,
    0x242a, 0x16b1, 0x0738, 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862,
    0x9af9, 0x8b70, 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e,
    0xf0b7, 0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036, 0x18c1,
    0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e, 0xa50a, 0xb483,
    0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5, 0x2942, 0x38cb, 0x0a50,
    0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd, 0xb58b, 0xa402, 0x9699, 0x8710,
    0xf3af, 0xe226, 0xd0bd, 0xc134, 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7,
    0x6e6e, 0x5cf5, 0x4d7c, 0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1,
    0xa33a, 0xb2b3, 0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72,
    0x3efb, 0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a, 0xe70e,
    0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1, 0x6b46, 0x7acf,
    0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9, 0xf78f, 0xe606, 0xd49d,
    0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330, 0x7bc7, 0x6a4e, 0x58d5, 0x495c,
    0x3de3, 0x2c6a, 0x1ef1, 0x0f78
]


def crc16(data: bytes, init=0xFFFF) -> int:
    """计算 CRC16 校验值"""
    crc = init
    for byte in data:
        crc = (crc >> 8) ^ CRC_TABLE[(crc ^ byte) & 0xFF]
    return crc

# ------------------------------------------------------------
# 发送包结构体：receive_packet_t（上位机 → 下位机）
# ------------------------------------------------------------
def build_receive_packet(state, id, armors_num, target_yaw, target_pitch, v_yaw, v_pitch, fire_advice):
    header = 0xA5
    flags = ((armors_num << 5) | (id << 2) | state) & 0xFF
    # 获取微秒时间戳的低32位
    pc_timestamp_us = int(time.time() * 1000000) & 0xFFFFFFFF
    # <BBffffiI : 2 byte header/flags + 4 float + 1 int + 1 uint32
    fmt = '<BBffffiI'
    data_without_crc = struct.pack(fmt, header, flags, target_yaw, target_pitch, v_yaw, v_pitch, fire_advice, pc_timestamp_us)
    crc = crc16(data_without_crc)
    return data_without_crc + struct.pack('<H', crc)

# ------------------------------------------------------------
# 接收包结构体：send_packet_t（下位机 → 上位机）
# ------------------------------------------------------------
def parse_send_packet(data: bytes):
    """
    解析下位机返回的响应包。包长度由 34 扩展为 38 字节。
    """
    EXPECTED_LEN = 38  # 【修改】：因为增加了 4 字节的 last_pc_timestamp
    if len(data) != EXPECTED_LEN:
        print(f"错误: 包长度应为{EXPECTED_LEN}，实际{len(data)}")
        return None

    # 验证CRC（前36字节计算CRC，与最后2字节比较）
    calc_crc = crc16(data[:-2])
    recv_crc = struct.unpack('<H', data[-2:])[0]
    if calc_crc != recv_crc:
        print(f"CRC校验失败: 计算={calc_crc:04X}, 接收={recv_crc:04X}")
        return None

    # 【修改】：fmt 末尾增加一个 'I'
    # 结构：header(1), flags(1), roll(4), pitch(4), yaw(4), aim_x(4), aim_y(4), aim_z(4), game_time(2), timestamp(4), last_pc_timestamp(4) = 36字节
    fmt = '<BBffffffHII'
    unpacked = struct.unpack(fmt, data[:-2])
    header, flags, roll, pitch, yaw, aim_x, aim_y, aim_z, game_time, timestamp, last_pc_timestamp_us = unpacked
    if header != 0x5A:
        print(f"头部错误: 期望0x5A，实际0x{header:02X}")
        return None

    # 解析flags位域
    detect_color = flags & 0x01
    task_mode = (flags >> 1) & 0x03
    reset_tracker = (flags >> 3) & 0x01
    is_play = (flags >> 4) & 0x01
    change_target = (flags >> 5) & 0x01
    reserved = (flags >> 6) & 0x03

    # 【新增】：计算往返延迟 RTT (Round Trip Time)
    current_time_us = int(time.time() * 1000000) & 0xFFFFFFFF
    rtt_latency = current_time_us - last_pc_timestamp_us

    return {
        'header': header,
        'detect_color': detect_color,
        'task_mode': task_mode,
        'reset_tracker': reset_tracker,
        'is_play': is_play,
        'change_target': change_target,
        'reserved': reserved,
        'roll': roll,
        'pitch': pitch,
        'yaw': yaw,
        'aim_x': aim_x,
        'aim_y': aim_y,
        'aim_z': aim_z,
        'game_time': game_time,
        'timestamp': timestamp,
        'last_pc_timestamp': last_pc_timestamp_us, 
        'rtt_latency_us': rtt_latency  # 方便你在终端直观看到链路延迟
    }

# ------------------------------------------------------------
# 主程序
# ------------------------------------------------------------
def main():
    ports = serial.tools.list_ports.comports()
    if not ports:
        print("没有找到串口设备，请手动指定。")
        port_name = input("请输入串口号 (如 COM3): ")
    else:
        print("可用串口:")
        for i, p in enumerate(ports):
            print(f"{i}: {p.device} - {p.description}")
        choice = input("请选择串口编号或直接输入串口号: ")
        try:
            idx = int(choice)
            port_name = ports[idx].device
        except:
            port_name = choice

    try:
        ser = serial.Serial(port_name, baudrate=921600, timeout=1.0)
        print(f"已打开串口 {port_name}")
    except Exception as e:
        print(f"打开串口失败: {e}")
        return

    # ---------- 新增：模式选择 ----------
    print("\n请选择工作模式：")
    print("1: 固定模式 (发送固定 yaw=0, pitch=0)")
    print("2: 画圆模式 (以0,0为起点向下画圆，直径10°，5秒一圈)")
    mode = input("输入1或2: ").strip()
    # 画圆模式参数
    if mode == '2':
        start_time = time.time()          # 记录起始时间
        R_deg = 1                          # 半径 20°（直径40°）
        R_rad = math.radians(R_deg)        # 转换为弧度
        T = 5                             # 周期5秒
        print(f"画圆模式启动：半径={R_deg}°，周期={T}s")
    else:
        mode = '1'   # 默认为固定模式
        print("固定模式启动：发送 (0,0)")
    # ------------------------------------

    state = 1          
    id = 0             
    armors_num = 4     
    yaw_diff = 0.0
    pitch_diff = 0.0
    fire_advice = 1
    last_pc_timestamp_us = int(time.time() * 1000000) & 0xFFFFFFFF # 获取微秒
    print("开始循环发送请求包，按 Ctrl+C 停止")
    try:
        while True:
            # ---------- 根据模式计算目标角度 ----------
            if mode == '2':
                # 计算当前周期内的相对时间
                t = (time.time() - start_time) % T
                theta = 2 * math.pi * t / T
                # 参数方程：pitch = R*(1-cosθ), yaw = R*sinθ
                pitch =  R_rad * (1 - math.cos(theta))
                yaw =    - R_rad * math.sin(theta)
                # 可选：打印角度（度）便于观察
                print(f"画圆: t={t:.2f}s, pitch={math.degrees(pitch):.2f}°, yaw={math.degrees(yaw):.2f}°")
            else:
                pitch = 1.0
                yaw = 0.0
            # ----------------------------------------

            # 构建请求包
            packet = build_receive_packet(state, id, armors_num,
                                          yaw, pitch, yaw_diff, pitch_diff,
                                          fire_advice)
            print(f"发送: {packet.hex().upper()}")
            ser.write(packet)
            ser.reset_input_buffer() 

            # 【修改】：读取长度由 34 增加至 38 字节
            resp = ser.read(38)
            if len(resp) == 38:
                print(f"接收: {resp.hex().upper()}")
                parsed = parse_send_packet(resp)
                if parsed:
                    print("解析结果:")
                    for k, v in parsed.items():
                        # 把延迟标红打印出来，方便调试观察
                        if k == 'rtt_latency_us':
                            print(f"  {k}: {v} us <--- 链路总延迟")
                        else:
                            print(f"  {k}: {v}")
                else:
                    print("解析失败")
            else:
                print(f"接收超时，仅收到 {len(resp)} 字节")

            print("-" * 50)
            time.sleep(0.1)  

    except KeyboardInterrupt:
        print("\n用户停止")
    finally:
        ser.close()
        print("串口已关闭")

if __name__ == '__main__':
    main()