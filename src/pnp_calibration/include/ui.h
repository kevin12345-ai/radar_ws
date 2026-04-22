#ifndef UI_H
#define UI_H
#include <opencv2/opencv.hpp>
#include "calibration.h"
#include "config/config.h"

enum MouseEventType {
    LEFT_BUTTON_DOWN,
    RIGHT_BUTTON_DOWN
};

class UI {
public:
    cv::Mat camera_image;
    cv::Mat map_image;

    
    void show_image();
    static void onMouseWithWindow(int event, int x, int y, int flags, void* userdata);
    void clickMapPoint(int x, int y, MouseEventType event);
    void clickCameraPoint(int x, int y, MouseEventType event);
    Calibration calibration;
};
#endif  // UI_H