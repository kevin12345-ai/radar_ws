#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <termios.h>
#include <unistd.h>

/**
 * Linux 串口通信类
 * 封装了打开、配置、读写和关闭操作，使用 termios 进行底层配置。
 * 支持移动语义，禁止拷贝。
 */
class SerialPort {
public:
    /**
     * 构造函数，不打开串口
     */
    SerialPort();

    /**
     * 构造函数，自动打开指定设备
     * @param device 串口设备路径，如 "/dev/ttyUSB0"
     * @throws std::runtime_error 如果打开失败
     */
    explicit SerialPort(const std::string& device);

    /**
     * 析构函数，自动关闭串口
     */
    ~SerialPort();

    // 禁止拷贝
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;

    // 允许移动
    SerialPort(SerialPort&& other) noexcept;
    SerialPort& operator=(SerialPort&& other) noexcept;

    /**
     * 打开串口设备
     * @param device 设备路径
     * @return true 成功，false 失败（可通过 lastError() 获取错误信息）
     */
    bool open(const std::string& device);

    /**
     * 关闭串口（已在析构中自动调用）
     */
    void close();

    /**
     * 配置串口参数
     * @param baudrate    波特率，支持 9600,19200,38400,57600,115200,230400,460800,921600
     * @param dataBits    数据位，支持 5,6,7,8
     * @param parity      校验位：'N' 无校验，'O' 奇校验，'E' 偶校验
     * @param stopBits    停止位：1 或 2
     * @param flowControl 流控：0 无，1 硬件流控(RTS/CTS)，2 软件流控(XON/XOFF)
     * @return true 成功，false 失败（参数不支持或配置失败）
     */
    bool configure(int baudrate, int dataBits = 8, char parity = 'N',
                   int stopBits = 1, int flowControl = 0);

    /**
     * 发送数据
     * @param data 数据缓冲区
     * @param len  数据长度
     * @return 实际发送的字节数，失败返回 -1（可通过 lastError() 获取错误信息）
     */
    ssize_t write(const void* data, size_t len);

    /**
     * 发送字符串（重载）
     * @param data 字符串
     * @return 实际发送的字节数
     */
    ssize_t write(const std::string& data);

    /**
     * 接收数据，支持超时
     * @param buffer    接收缓冲区
     * @param maxLen    最大读取字节数
     * @param timeoutMs 超时时间（毫秒），-1 表示无限等待
     * @return 实际读取的字节数；超时返回 -1 并设置 errno 为 ETIMEDOUT；其他错误返回 -1
     */
    ssize_t read(void* buffer, size_t maxLen, int timeoutMs = -1);

    /**
     * 检查串口是否已打开
     */
    bool isOpen() const;

    /**
     * 获取最后一次操作的错误信息
     */
    std::string lastError() const;

    bool flushInput();
private:
    int         fd_;         // 文件描述符
    std::string errorMsg_;   // 错误信息

    // 设置错误信息
    void setError(const std::string& msg);

    // 将整数波特率转换为 termios 宏
    static speed_t baudrateToSpeed(int baudrate);
};

#endif // SERIALPORT_H