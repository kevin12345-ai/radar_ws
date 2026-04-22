#include "rclcpp/rclcpp.hpp"
#include "serial.h"
#include "config/config.h"
#include "SerialPort.h"
#include "vision_detector/msg/drone_diff.hpp"
#include "vision_detector/msg/gimbal_info.hpp"
#include <memory>



to_stm_packet_t pkt;
class STMSerial : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    STMSerial(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
        //command_subscribe_ = this->create_subscription<camera_stream::msg::ShareImage>("command",10,std::bind(&STMSerial::command_callback,this,std::placeholders::_1));
        while(1){
            if(initSerialPort() == 0){
                break;
            }
            RCLCPP_ERROR(this->get_logger(), "STM串口初始化失败，正在重试...");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        memset(&pkt, 0, sizeof(pkt));
        pkt.header = 0xA5;
        pkt.state = 0;
        pkt.id = 0;
        pkt.armors_num = 0;
        pkt.target_yaw = deg_to_rad(10.0f);
        pkt.target_pitch = deg_to_rad(10.0f);
        pkt.target_v_yaw = 0;
        pkt.target_v_pitch = 0;
        pkt.fire_advice = 1;
        pkt.pc_timestamp_us = 0;
        auto qos = rclcpp::QoS(2)
            .best_effort();                    // 不保证送达，适合实时数据

        drone_diff_subscribe_ = this->create_subscription<vision_detector::msg::DroneDiff>("drone_diff", qos, std::bind(&STMSerial::drone_diff_callback,this,std::placeholders::_1));
        gimbal_info_publish_ = this->create_publisher<vision_detector::msg::GimbalInfo>("gimbal_info",10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&STMSerial::main_loop, this));
        
    }

private:
    // 声明节点
    rclcpp::TimerBase::SharedPtr timer_;
    void main_loop(void);
    int send_to_stm(const to_stm_packet_t* pkt);
    int receive_from_stm(to_pc_packet_t *pkt);
    void test(void);
    int initSerialPort(void);
    std::unique_ptr<SerialPort> serial_stm_;
    rclcpp::Subscription<vision_detector::msg::DroneDiff>::SharedPtr drone_diff_subscribe_;
    rclcpp::Publisher<vision_detector::msg::GimbalInfo>::SharedPtr gimbal_info_publish_;
    void drone_diff_callback(const vision_detector::msg::DroneDiff::SharedPtr msg);
    // }
};

int main(int argc, char **argv){

    rclcpp::init(argc,argv);
    auto node = std::make_shared<STMSerial>("node_stm_serial");
    RCLCPP_INFO(node->get_logger(),"STARTED.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

void STMSerial::main_loop(void){
    RCLCPP_INFO(this->get_logger(), "发送数据包：state=%d, id=%d, armors_num=%d, target_yaw=%.2f, target_pitch=%.2f, target_v_yaw=%.2f, target_v_pitch=%.2f, fire_advice=%d, pc_timestamp_us=%u",
                pkt.state, pkt.id, pkt.armors_num, pkt.target_yaw, pkt.target_pitch, pkt.target_v_yaw, pkt.target_v_pitch, pkt.fire_advice, pkt.pc_timestamp_us);
    if(send_to_stm(&pkt) < 0){
        RCLCPP_ERROR(this->get_logger(), "Failed to send test packet to STM");
    }else{
        RCLCPP_INFO(this->get_logger(), "Packet sent to STM successfully");
    }
    
    to_pc_packet_t recv_pkt;
    if (receive_from_stm(&recv_pkt) == 0) {
        printf("接收到数据包:");
        printf("Header: 0x%02X\n", recv_pkt.header);
        printf("Detect Color: %d  ", recv_pkt.detect_color);
        printf("Is Play: %d  ", recv_pkt.is_play);
        printf("Change Target: %d  ", recv_pkt.change_target);
        printf("Roll: %.2f  ", recv_pkt.roll);
        printf("Pitch: %.2f  ", recv_pkt.pitch);
        printf("Yaw: %.2f\n", recv_pkt.yaw);
        printf("Aim X: %.2f  ", recv_pkt.aim_x);
        printf("Aim Y: %.2f  ", recv_pkt.aim_y);
        printf("Aim Z: %.2f  ", recv_pkt.aim_z);
        printf("Game Time: %u seconds  ", recv_pkt.game_time);
        printf("Timestamp: %u ms  ", recv_pkt.timestamp);
        printf("Last PC Timestamp: %u ms\n", recv_pkt.last_pc_timestamp_us);
        vision_detector::msg::GimbalInfo gimbal_info_msg;
        gimbal_info_msg.current_yaw = recv_pkt.yaw;
        gimbal_info_msg.current_pitch = recv_pkt.pitch;
        gimbal_info_msg.last_pc_timestamp_us = recv_pkt.last_pc_timestamp_us;
        gimbal_info_publish_->publish(gimbal_info_msg);
    } else {
        printf("未收到有效数据或校验失败\n");
    }
}

int STMSerial::send_to_stm(const to_stm_packet_t* pkt){
    uint8_t out_buf[sizeof(to_stm_packet_t)];
    pack_send_packet(pkt, out_buf);
    if (serial_stm_ && serial_stm_->isOpen()) {
        ssize_t bytes_written = serial_stm_->write(out_buf, sizeof(out_buf));
        if (bytes_written < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to write to STM serial: %s", serial_stm_->lastError().c_str());
        } else {
            RCLCPP_INFO(this->get_logger(), "Sent %zd bytes to STM", bytes_written);
        }
        serial_stm_->flushInput(); // 确保数据发送出去，清空输入缓冲区
    } else {
        RCLCPP_ERROR(this->get_logger(), "STM serial port is not open");
        while(initSerialPort() != 0){
            RCLCPP_ERROR(this->get_logger(), "Failed to reinitialize STM serial port, retrying...");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        return -1;
    }
    return 0;
}

int STMSerial::receive_from_stm(to_pc_packet_t *pkt)
{
    uint8_t rx_buffer[sizeof(to_pc_packet_t)];
    int len = serial_stm_->read(rx_buffer, sizeof(rx_buffer), 50); // 50ms超时
    // for(int i=0;i<len;i++){
    //     printf("%02X ", rx_buffer[i]);
    // }
    // printf("\n");
    if (len < 0) {
        RCLCPP_ERROR(this->get_logger(), "Failed to read from STM serial: %s", serial_stm_->lastError().c_str());
        return -1;
    }
    if (len == 0) {
        // 超时，无数据
        return -1;
    }
    if (len != sizeof(rx_buffer)) {
        RCLCPP_ERROR(this->get_logger(), "Received incomplete packet: expected %zu bytes, got %d bytes", sizeof(rx_buffer), len);
        return -1;
    }

    // 解析并校验
    int ret = parse_receive_packet(rx_buffer, pkt);
    
    if (ret != 0) {
        RCLCPP_ERROR(this->get_logger(), "Received packet validation failed, error code: %d", ret);
        return -1;
    }
    return 0;
}

// void STMSerial::test(void){
//     to_stm_packet_t pkt;
//     pkt.header = 0xA5;
//     pkt.state = 1;
//     pkt.id = 3;
//     pkt.armors_num = 4;
//     pkt.yaw = 0.0f;
//     pkt.pitch = 0.0f;
//     pkt.yaw_diff = 0.5f;
//     pkt.pitch_diff = 0.2f;
//     pkt.fire_advice = 1;
//     if(send_to_stm(&pkt) < 0){
//         RCLCPP_ERROR(this->get_logger(), "Failed to send test packet to STM");
//     }else{
//         RCLCPP_INFO(this->get_logger(), "Test packet sent to STM successfully");
//     }
//     to_pc_packet_t recv_pkt;
//     if (receive_from_stm(&recv_pkt) == 0) {
//         printf("接收到数据包:\n");
//         printf("Header: 0x%02X\n", recv_pkt.header);
//         printf("Detect Color: %d\n", recv_pkt.detect_color);
//         printf("Is Play: %d\n", recv_pkt.is_play);
//         printf("Change Target: %d\n", recv_pkt.change_target);
//         printf("Roll: %.2f\n", recv_pkt.roll);
//         printf("Pitch: %.2f\n", recv_pkt.pitch);
//         printf("Yaw: %.2f\n", recv_pkt.yaw);
//         printf("Aim X: %.2f\n", recv_pkt.aim_x);
//         printf("Aim Y: %.2f\n", recv_pkt.aim_y);
//         printf("Aim Z: %.2f\n", recv_pkt.aim_z);
//         printf("Game Time: %u seconds\n", recv_pkt.game_time);
//         printf("Timestamp: %u ms\n", recv_pkt.timestamp);
//     } else {
//         printf("未收到有效数据或校验失败\n");
//     }
    

// }

int STMSerial::initSerialPort(void){
    try {
        serial_stm_ = std::make_unique<SerialPort>(STM_SERIAL_DEVICE);
        if (!serial_stm_->configure(STM_SERIAL_BAUDRATE, 8, 'N', 1, 0)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to configure stm serial [%s]: %s", STM_SERIAL_DEVICE, serial_stm_->lastError().c_str());
        }
        RCLCPP_INFO(this->get_logger(), "STM Serial [%s] opened and configured successfully.", STM_SERIAL_DEVICE);
        return 0;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Error initializing stm serial [%s] ports: %s", STM_SERIAL_DEVICE, e.what());
        // 发生异常时，自动释放已打开的资源（unique_ptr 会调用析构关闭串口）
        serial_stm_.reset();
        return -1;
    }
}

void STMSerial::drone_diff_callback(const vision_detector::msg::DroneDiff::SharedPtr msg){
    RCLCPP_INFO(this->get_logger(), "Received drone diff: yaw=%.2f, pitch=%.2f", msg->target_yaw, msg->target_pitch);
    memset(&pkt, 0, sizeof(pkt));
    pkt.header = 0xA5;
    pkt.state = 1;
    pkt.id = 3;
    pkt.armors_num = 0;
    // pkt.target_yaw = 0;
    // pkt.target_pitch = 0;
    // pkt.target_v_yaw = 0;
    // pkt.target_v_pitch = 0;
    pkt.target_yaw = msg->target_yaw;
    pkt.target_pitch = msg->target_pitch;
    pkt.target_v_yaw = msg->v_yaw;
    pkt.target_v_pitch = msg->v_pitch;
    pkt.fire_advice = 1;
    pkt.pc_timestamp_us = msg->pc_timestamp_us;
}