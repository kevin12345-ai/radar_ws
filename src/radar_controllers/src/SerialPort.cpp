#include "SerialPort.h"
#include <fcntl.h>
#include <sys/select.h>
#include <cstdint>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>
#include <stdexcept>

// 构造函数
SerialPort::SerialPort() : fd_(-1) {}

SerialPort::SerialPort(const std::string& device) : fd_(-1) {
    if (!open(device)) {
        throw std::runtime_error("Failed to open serial port: " + device + " - " + errorMsg_);
    }
}

// 析构函数
SerialPort::~SerialPort() {
    close();
}

// 移动构造函数
SerialPort::SerialPort(SerialPort&& other) noexcept
    : fd_(other.fd_), errorMsg_(std::move(other.errorMsg_)) {
    other.fd_ = -1;  // 防止原对象析构时关闭
}

// 移动赋值运算符
SerialPort& SerialPort::operator=(SerialPort&& other) noexcept {
    if (this != &other) {
        close();  // 关闭当前
        fd_ = other.fd_;
        errorMsg_ = std::move(other.errorMsg_);
        other.fd_ = -1;
    }
    return *this;
}

// 打开串口
bool SerialPort::open(const std::string& device) {
    // 如果已打开，先关闭
    if (fd_ >= 0) {
        close();
    }

    fd_ = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_ < 0) {
        setError("open() failed: " + std::string(strerror(errno)));
        return false;
    }

    // 恢复为阻塞模式（便于 select 管理）
    if (fcntl(fd_, F_SETFL, 0) < 0) {
        setError("fcntl() failed: " + std::string(strerror(errno)));
        ::close(fd_);
        fd_ = -1;
        return false;
    }

    return true;
}

// 关闭串口
void SerialPort::close() {
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

// 配置串口参数
bool SerialPort::configure(int baudrate, int dataBits, char parity,
                           int stopBits, int flowControl) {
    if (fd_ < 0) {
        setError("Serial port not open");
        return false;
    }

    struct termios options;
    if (tcgetattr(fd_, &options) != 0) {
        setError("tcgetattr() failed: " + std::string(strerror(errno)));
        return false;
    }

    // 波特率
    speed_t speed = baudrateToSpeed(baudrate);
    if (speed == B0) {
        setError("Unsupported baudrate: " + std::to_string(baudrate));
        return false;
    }
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    // 控制模式
    options.c_cflag |= CLOCAL | CREAD;   // 忽略调制解调器状态，启用接收器

    // 数据位
    options.c_cflag &= ~CSIZE;
    switch (dataBits) {
        case 5: options.c_cflag |= CS5; break;
        case 6: options.c_cflag |= CS6; break;
        case 7: options.c_cflag |= CS7; break;
        case 8: options.c_cflag |= CS8; break;
        default:
            setError("Unsupported data bits: " + std::to_string(dataBits));
            return false;
    }

    // 校验位
    switch (parity) {
        case 'N':
        case 'n':
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        case 'O':
        case 'o':
            options.c_cflag |= PARENB;
            options.c_cflag |= PARODD;
            options.c_iflag |= INPCK;
            break;
        case 'E':
        case 'e':
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;
            break;
        default:
            setError("Unsupported parity: " + std::string(1, parity));
            return false;
    }

    // 停止位
    if (stopBits == 1) {
        options.c_cflag &= ~CSTOPB;
    } else if (stopBits == 2) {
        options.c_cflag |= CSTOPB;
    } else {
        setError("Unsupported stop bits: " + std::to_string(stopBits));
        return false;
    }

    // 流控
    switch (flowControl) {
        case 0:
            options.c_cflag &= ~CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case 1:  // 硬件流控
            options.c_cflag |= CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case 2:  // 软件流控
            options.c_cflag &= ~CRTSCTS;
            options.c_iflag |= IXON | IXOFF | IXANY;
            break;
        default:
            setError("Unsupported flow control: " + std::to_string(flowControl));
            return false;
    }

    // 本地模式：禁用规范输入、回显等
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // 输入模式：原始数据输入
    options.c_iflag &= ~(INLCR | ICRNL | IGNCR | ISTRIP | BRKINT | IGNPAR);

    // 输出模式：原始数据输出
    options.c_oflag &= ~OPOST;

    // 非规范模式下的读取控制：不等待最小字符，由 select 控制超时
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 0;   // 超时由 read 中的 select 处理

    // 清空缓冲区
    tcflush(fd_, TCIOFLUSH);

    // 应用设置
    if (tcsetattr(fd_, TCSANOW, &options) != 0) {
        setError("tcsetattr() failed: " + std::string(strerror(errno)));
        return false;
    }

    return true;
}

// 发送数据
ssize_t SerialPort::write(const void* data, size_t len) {
    if (fd_ < 0) {
        setError("Serial port not open");
        return -1;
    }
    ssize_t ret = ::write(fd_, data, len);
    // for(int i=0;i<len;i++){
    //     printf("%02X ", ((uint8_t*)data)[i]);
    // }
    // printf("\n");

    if (ret < 0) {
        setError("write() failed: " + std::string(strerror(errno)));
    }
    return ret;
}

ssize_t SerialPort::write(const std::string& data) {
    return write(data.data(), data.size());
}

// 接收数据（支持超时）
ssize_t SerialPort::read(void* buffer, size_t maxLen, int timeoutMs) {
    if (fd_ < 0) {
        setError("Serial port not open");
        return -1;
    }

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fd_, &readSet);

    struct timeval timeout, *timeoutPtr = nullptr;
    if (timeoutMs >= 0) {
        timeout.tv_sec = timeoutMs / 1000;
        timeout.tv_usec = (timeoutMs % 1000) * 1000;
        timeoutPtr = &timeout;
    }

    int selectRet = select(fd_ + 1, &readSet, nullptr, nullptr, timeoutPtr);
    if (selectRet < 0) {
        setError("select() failed: " + std::string(strerror(errno)));
        return -1;
    }
    if (selectRet == 0) {
        // 超时
        errno = ETIMEDOUT;
        setError("read timeout");
        return -1;
    }

    // 有数据可读
    ssize_t ret = ::read(fd_, buffer, maxLen);
    if (ret < 0) {
        setError("read() failed: " + std::string(strerror(errno)));
    }
    return ret;
}

// 检查是否打开
bool SerialPort::isOpen() const {
    return fd_ >= 0;
}

// 获取最后一次错误信息
std::string SerialPort::lastError() const {
    return errorMsg_;
}

// 设置错误信息
void SerialPort::setError(const std::string& msg) {
    errorMsg_ = msg;
}

// 波特率转换
speed_t SerialPort::baudrateToSpeed(int baudrate) {
    switch (baudrate) {
        case 9600:   return B9600;
        case 19200:  return B19200;
        case 38400:  return B38400;
        case 57600:  return B57600;
        case 115200: return B115200;
        case 230400: return B230400;
        case 460800: return B460800;
        case 921600: return B921600;
        default:     return B0;
    }
}

bool SerialPort::flushInput() {
    if (fd_ < 0) {
        setError("Serial port not open");
        return false;
    }
    if (tcflush(fd_, TCIFLUSH) != 0) {
        setError(std::string("tcflush(TCIFLUSH) failed: ") + strerror(errno));
        return false;
    }
    return true;
}