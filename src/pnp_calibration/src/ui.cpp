#include "ui.h"

#include <iostream>

// 两个独立的回调函数，分别处理不同窗口
static void cameraMouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        //std::cout << "Camera窗口 - 左键按下 - 坐标: (" << x << ", " << y << ")" << std::endl;
        ((UI*)userdata)->clickCameraPoint(x,y,LEFT_BUTTON_DOWN);
    } else if (event == cv::EVENT_RBUTTONDOWN) {
        //std::cout << "Camera窗口 - 右键按下 - 坐标: (" << x << ", " << y << ")" << std::endl;
        ((UI*)userdata)->clickCameraPoint(x,y,RIGHT_BUTTON_DOWN);
    }
}

static void mapMouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        //std::cout << "Map窗口 - 左键按下 - 坐标: (" << x << ", " << y << ")" << std::endl;
        ((UI*)userdata)->clickMapPoint(x,y,LEFT_BUTTON_DOWN);
    } else if (event == cv::EVENT_RBUTTONDOWN) {
        //std::cout << "Map窗口 - 右键按下 - 坐标: (" << x << ", " << y << ")" << std::endl;
        ((UI*)userdata)->clickMapPoint(x,y,RIGHT_BUTTON_DOWN);
    }
    
}

void UI::show_image() {
    cv::Mat camera_image_temp = camera_image.clone();
    cv::Mat map_image_temp = map_image.clone();
    cv::putText(camera_image_temp, "POINT", cv::Point(0, 25), 
            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            cv::Scalar color;
            switch (j) {
                case 0:
                    color = cv::Scalar(0, 0, 255);
                    break;
                case 1:
                    color = cv::Scalar(0, 255, 0);
                    break;
                case 2:
                    color = cv::Scalar(255, 0, 0);
                    break;
                case 3:
                    color = cv::Scalar(255, 255, 0);
                    break;
            }
            float cx=calibration.pts.camera_points[i][j].x * CAR_CAMERA_SCALE_FACTOR;
            float cy=calibration.pts.camera_points[i][j].y * CAR_CAMERA_SCALE_FACTOR;
            float mx=calibration.pts.map_points[i][j].x * MAP_SCALE_FACTOR;
            float my=calibration.pts.map_points[i][j].y * MAP_SCALE_FACTOR;
            cv::circle(camera_image_temp, cv::Point2f(cx,cy), 2, color, -1);
            cv::circle(map_image_temp, cv::Point2f(mx,my), 2, color, -1);
            cv::putText(camera_image_temp, std::to_string(i+1), cv::Point2f(cx,cy), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            cv::putText(map_image_temp, std::to_string(i+1), cv::Point2f(mx,my), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        }
    }
    
    // 创建窗口并设置鼠标回调
    //自动调整大小
    cv::namedWindow("Camera", cv::WINDOW_GUI_NORMAL);
    cv::resizeWindow("Camera", camera_image_temp.cols, camera_image_temp.rows);
    cv::setMouseCallback("Camera", cameraMouseCallback, this);
    cv::imshow("Camera", camera_image_temp);
    
    cv::namedWindow("Map", cv::WINDOW_GUI_NORMAL);
    cv::resizeWindow("Map", map_image_temp.cols, map_image_temp.rows);
    cv::setMouseCallback("Map", mapMouseCallback, this);
    cv::imshow("Map", map_image_temp);
}

void UI::clickMapPoint(int x, int y, MouseEventType event){
    if(event == LEFT_BUTTON_DOWN)
        calibration.SetPoint(cv::Point2f((float)x/MAP_SCALE_FACTOR,(float)y/MAP_SCALE_FACTOR),false);
    else if(event == RIGHT_BUTTON_DOWN)
        calibration.CancelPoint(false);
        //std::cout << "Map窗口 - 取消点: ["<<calibration.pts.map_id<<"]" << std::endl;

}
void UI::clickCameraPoint(int x, int y, MouseEventType event){
    if(event == LEFT_BUTTON_DOWN)
        calibration.SetPoint(cv::Point2f((float)x/CAR_CAMERA_SCALE_FACTOR,(float)y/CAR_CAMERA_SCALE_FACTOR),true);
    else if(event == RIGHT_BUTTON_DOWN)
        calibration.CancelPoint(true);
        //std::cout << "Camera窗口 - 取消点: ["<<id<<"]" << std::endl;
}