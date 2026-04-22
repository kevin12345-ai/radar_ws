#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include "config/config.h"
typedef struct points{
    cv::Point2f camera_points[3][4];
    cv::Point2f map_points[3][4];
    int camera_id;
    int map_id;
    int layer_id;
}points;

class Calibration{
private:

public:
    cv::Mat L,M,H;
    Calibration();
    void SetPoint(cv::Point2f point,bool isCamera);
    void CancelPoint(bool isCamera);
    void getTransformationMatrix();
    void saveMatrices(const std::string& filename);
    void loadMatrices(const std::string& filename);
    points pts;
};

#endif