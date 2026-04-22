/**
 * @file        serial.h
 * @brief       上位机与 STM32 下位机通信协议头文件（对应下位机 v2.0.0 版本）
 * @details     包含数据结构定义、CRC16 校验及数据打包/解析函数声明。
 *              使用 GCC 的 __attribute__((packed)) 确保结构体内存布局紧凑，
 *              与下位机完全一致。上位机需自行实现串口收发。
 * @note        本文件不包含任何硬件相关代码，可跨平台使用（Linux/Windows）。
 *              字节序：下位机为小端模式，x86 也为小端，故无需转换；若在大端平台需处理。
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>     // 使用标准整数类型
#include <string.h>     // memcpy

#ifdef __cplusplus
extern "C" {
#endif

/* 与下位机完全一致的数据结构 ----------------------------------------------- */

/**
 * @brief   下位机发送给上位机的数据包（STM32 -> PC）
 */
typedef struct
{
    uint8_t header;                 // 固定为 0x5A
    uint8_t detect_color : 1;        // 0-红色 1-蓝色
    uint8_t task_mode : 2;           // 0-auto 1-aim 2-buff
    uint8_t reset_tracker : 1;
    uint8_t is_play : 1;
    uint8_t change_target : 1;
    uint8_t reserved : 2;            // 保留位，对齐字节
    float roll;
    float pitch;
    float yaw;
    float aim_x;
    float aim_y;
    float aim_z;
    uint16_t game_time;               // 游戏剩余时间 (秒) [0,450]
    uint32_t timestamp;                // 板载时间戳 (毫秒)
    uint32_t last_pc_timestamp_us;
    uint16_t checksum;                 // CRC16 校验和（从 header 到 timestamp 的校验值）
} __attribute__((packed)) to_pc_packet_t;

/**
 * @brief   上位机发送给下位机的数据包（PC -> STM32）
 */
typedef struct
{
    uint8_t header;                 // 固定为 0xA5
    uint8_t state : 2;               // 0-未跟踪 1-瞄准跟踪 2-能量机关跟踪
    uint8_t id : 3;                  // 目标ID: 0-前哨站 6-基地 7-守护者（根据协议）
    uint8_t armors_num : 3;           // 装甲板数量: 2-平衡 3-前哨 4-普通
    float target_yaw;
    float target_pitch;
    float target_v_yaw;
    float target_v_pitch;
    int fire_advice;                  // 开火建议（0/1 或其他自定义）
    uint32_t pc_timestamp_us;
    uint16_t checksum;                 // CRC16 校验和
} __attribute__((packed)) to_stm_packet_t;

/* 函数声明 ----------------------------------------------------------------- */

/**
 * @brief   计算 CRC16-CCITT 校验和（多项式 0x1021，初始值 0xFFFF）
 * @param   data    数据指针
 * @param   length  数据长度
 * @return  计算出的 CRC16 值
 * @note    与下位机 Get_CRC16_Check_Sum 算法完全一致
 */
uint16_t calc_crc16(const uint8_t* data, uint32_t length);

/**
 * @brief   将发送数据打包成二进制帧（自动填充校验和）
 * @param   pkt     指向 to_stm_packet_t 的指针（已填充除 checksum 外的所有字段）
 * @param   out_buf 输出缓冲区，大小至少为 sizeof(to_stm_packet_t) 字节
 * @return  无
 */
void pack_send_packet(const to_stm_packet_t* pkt, uint8_t* out_buf);

/**
 * @brief   解析接收到的二进制帧，并进行校验和验证
 * @param   in_buf  输入缓冲区，包含从串口接收的原始数据（长度应为 sizeof(to_pc_packet_t)）
 * @param   pkt     指向 to_pc_packet_t 的指针，用于存放解析结果
 * @retval  0   成功，校验通过
 * @retval -1   帧头错误（不是 0x5A）
 * @retval -2   校验和错误
 */
int parse_receive_packet(const uint8_t* in_buf, to_pc_packet_t* pkt);

#ifdef __cplusplus
}
#endif
typedef struct
{
    uint8_t header;                 // 固定为 0xAC
    float yaw_angle_p;
    float yaw_angle_i;
    float yaw_angle_d;
    float pitch_angle_p;
    float pitch_angle_i;
    float pitch_angle_d;
    float yaw_speed_p;
    float yaw_speed_i;
    float yaw_speed_d;
    float pitch_speed_p;
    float pitch_speed_i;
    float pitch_speed_d;
} __attribute__((packed)) to_stm_pid_packet_t;
#endif // SERIAL_H

//