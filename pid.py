import serial
import serial.tools.list_ports
import struct
import sys

def build_pid_packet(
    mode: int,
    yaw_angle_p: float, yaw_angle_i: float, yaw_angle_d: float,
    pitch_angle_p: float, pitch_angle_i: float, pitch_angle_d: float,
    yaw_speed_p: float, yaw_speed_i: float, yaw_speed_d: float,
    pitch_speed_p: float, pitch_speed_i: float, pitch_speed_d: float,
    header: int = 0xAC
) -> bytes:
    """
    构建包含 mode 的 PID 参数包。
    格式：header(1B) + mode(4B) + 12个float (小端序) = 53 字节
    """
    fmt = '<Bi' + 'f' * 12   # 小端：B(header), i(mode), 12个float
    packet = struct.pack(fmt, header, mode,
                         yaw_angle_p, yaw_angle_i, yaw_angle_d,
                         pitch_angle_p, pitch_angle_i, pitch_angle_d,
                         yaw_speed_p, yaw_speed_i, yaw_speed_d,
                         pitch_speed_p, pitch_speed_i, pitch_speed_d)
    return packet

def get_serial_port():
    """列出可用串口，让用户选择，返回端口名"""
    ports = serial.tools.list_ports.comports()
    if not ports:
        print("没有找到任何串口设备。")
        return input("请手动输入串口号（如 COM3 或 /dev/ttyUSB0）: ").strip()

    print("可用串口：")
    for i, p in enumerate(ports):
        print(f"{i}: {p.device} - {p.description}")
    while True:
        choice = input("请输入序号或直接输入串口号: ").strip()
        try:
            idx = int(choice)
            if 0 <= idx < len(ports):
                return ports[idx].device
            else:
                print("序号超出范围，请重新输入。")
        except ValueError:
            # 不是数字，当作直接输入的串口号
            return choice

def input_float(prompt: str, default: float = None) -> float:
    """带默认值的浮点数输入"""
    while True:
        try:
            if default is not None:
                val = input(f"{prompt} (默认 {default}): ").strip()
                if val == "":
                    return default
                return float(val)
            else:
                return float(input(prompt))
        except ValueError:
            print("输入无效，请输入一个数字。")

def main():
    # 1. 选择串口
    port = get_serial_port()
    baudrate = 921600  # 可根据需要修改
    try:
        ser = serial.Serial(port, baudrate, timeout=1.0)
        print(f"已打开串口 {port}，波特率 {baudrate}")
    except Exception as e:
        print(f"打开串口失败: {e}")
        sys.exit(1)

    # 2. 输入 PID 参数（提供默认值，可自行修改）
    print("\n请输入 PID 参数（浮点数）：")
    #yaw_speed_p   = 150.0
    yaw_speed_p   = 300.0
    yaw_speed_i   = 1
    #yaw_speed_i   = 10.0
    yaw_speed_d   = 0.1

    yaw_angle_p   = 300.0
    yaw_angle_i   = 1
    yaw_angle_d   = 0.1

    pitch_speed_p = 200.0
    pitch_speed_i = 5
    pitch_speed_d = 0.1
    #pitch_speed_p = 135.0
    #pitch_speed_i = 6.0
    #pitch_speed_d = 5.0
    
    pitch_angle_p = 300.0
    pitch_angle_i = 3
    pitch_angle_d = 0.1
    
    mode = 0

    # 3. 构建并发送数据包
    packet = build_pid_packet(
        mode,
        yaw_angle_p, yaw_angle_i, yaw_angle_d,
        pitch_angle_p, pitch_angle_i, pitch_angle_d,
        yaw_speed_p, yaw_speed_i, yaw_speed_d,
        pitch_speed_p, pitch_speed_i, pitch_speed_d
    )
    print(f"\n待发送数据 ({len(packet)} 字节): {packet.hex().upper()}")
    ser.write(packet)
    ser.flush()  # 等待数据发送完成
    print("数据包已发送。")

    # 4. 可选择读取下位机的回复（若无回复可注释掉）
    # resp = ser.read(34)  # 假设下位机回复固定长度，根据实际情况调整
    # if resp:
    #     print(f"收到回复: {resp.hex().upper()}")

    # 5. 关闭串口
    ser.close()
    print("串口已关闭。")

if __name__ == "__main__":
    main()