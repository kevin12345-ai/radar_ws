#ifndef EKF_TRACKER_H
#define EKF_TRACKER_H

#include <opencv2/opencv.hpp>

class EKFTracker {
public:
    EKFTracker();
    void init(const cv::Point2f& init_angle);
    cv::Point2f predict(double dt);
    void update(const cv::Point2f& measured_angle);
    void handleLost();

    bool isInitialized() const;
    cv::Point2f getEstimatedPos() const;
    cv::Point2f getEstimatedVel() const; // 获取前馈速度
private:
    bool initialized_;
    int lost_count_;
    
    // 状态向量 [yaw, pitch, v_yaw, v_pitch] (4x1)
    cv::Mat x_; 
    cv::Mat P_, Q_, R_, H_; 
};
#endif