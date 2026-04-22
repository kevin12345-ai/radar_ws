#include "ekf_tracker.h"

EKFTracker::EKFTracker() {
    initialized_ = false;
    lost_count_ = 0;

    x_ = cv::Mat::zeros(4, 1, CV_64F);
    P_ = cv::Mat::eye(4, 4, CV_64F);
    
    // 观测矩阵 H (只能观测到角度yaw, pitch)
    H_ = cv::Mat::zeros(2, 4, CV_64F);
    H_.at<double>(0, 0) = 1.0;
    H_.at<double>(1, 1) = 1.0;

    // 过程噪声 Q
    Q_ = cv::Mat::eye(4, 4, CV_64F);
    Q_.at<double>(0, 0) = 1e-4; // 角度噪声
    Q_.at<double>(1, 1) = 1e-4;
    Q_.at<double>(2, 2) = 1.0;  // 速度变化剧烈，设大一点
    Q_.at<double>(3, 3) = 1.0;

    // 测量噪声 R
    R_ = cv::Mat::eye(2, 2, CV_64F) * 1e-3; 
}

void EKFTracker::init(const cv::Point2f& init_angle) {
    x_.at<double>(0, 0) = init_angle.x;
    x_.at<double>(1, 0) = init_angle.y;
    x_.at<double>(2, 0) = 0.0;
    x_.at<double>(3, 0) = 0.0;
    P_ = cv::Mat::eye(4, 4, CV_64F) * 1.0;
    initialized_ = true;
    lost_count_ = 0;
}

cv::Point2f EKFTracker::predict(double dt) {
    if (!initialized_) return cv::Point2f(0, 0);

    // 线性状态转移矩阵 F
    cv::Mat F = cv::Mat::eye(4, 4, CV_64F);
    F.at<double>(0, 2) = dt;
    F.at<double>(1, 3) = dt;

    x_ = F * x_;
    
    // 引入速度衰减阻尼，防止目标丢失后云台狂奔
    x_.at<double>(2, 0) *= 0.90; 
    x_.at<double>(3, 0) *= 0.90;

    P_ = F * P_ * F.t() + Q_;
    return cv::Point2f(x_.at<double>(0, 0), x_.at<double>(1, 0));
}

void EKFTracker::update(const cv::Point2f& measured_angle) {
    if (!initialized_) {
        init(measured_angle);
        return;
    }
    cv::Mat z = (cv::Mat_<double>(2, 1) << measured_angle.x, measured_angle.y);
    cv::Mat y = z - H_ * x_; // 残差
    
    // 突跳强同步
    if (cv::norm(y) > 5.0) { // 角度偏差大于5度直接重置
        init(measured_angle);
        return;
    }

    cv::Mat S = H_ * P_ * H_.t() + R_;
    cv::Mat K = P_ * H_.t() * S.inv();

    x_ = x_ + (K * y);
    P_ = (cv::Mat::eye(4, 4, CV_64F) - K * H_) * P_;
    lost_count_ = 0;
}

void EKFTracker::handleLost() {
    if (!initialized_) return;
    lost_count_++;
    if (lost_count_ > 10) initialized_ = false;
}

cv::Point2f EKFTracker::getEstimatedPos() const {
    return cv::Point2f(x_.at<double>(0, 0), x_.at<double>(1, 0));
}
cv::Point2f EKFTracker::getEstimatedVel() const {
    return cv::Point2f(x_.at<double>(2, 0), x_.at<double>(3, 0));
}
bool EKFTracker::isInitialized() const { return initialized_; }