#include "calibration.h"

Calibration::Calibration(){
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            pts.camera_points[i][j] = cv::Point(0,0);
            pts.map_points[i][j] = cv::Point(0,0);
        }
    }
    pts.camera_id = 0;
    pts.map_id = 0;
}

void Calibration::SetPoint(cv::Point2f point,bool isCamera){
    if(isCamera){
        if(pts.camera_id >=12) return;
        pts.camera_id++;
        std::cout << "Camera窗口 - 设置点: ["<<pts.camera_id<<"](" << point.x << ", " << point.y << ")" << std::endl;
        pts.camera_points[(pts.camera_id-1)/4][(pts.camera_id-1)%4] = point;
    }else{
        if(pts.map_id >=12) return;
        pts.map_id++;
        std::cout << "Map窗口 - 设置点: ["<<pts.map_id<<"](" << point.x << ", " << point.y << ")" << std::endl;
        pts.map_points[(pts.map_id-1)/4][(pts.map_id-1)%4] = point;
    }
}

void Calibration::CancelPoint(bool isCamera){
    if(isCamera){
        if(pts.camera_id <=0) return;
        std::cout << "Camera窗口 - 取消点: ["<<pts.camera_id<<"]" << std::endl;
        pts.camera_points[(pts.camera_id-1)/4][(pts.camera_id-1)%4] = cv::Point(0,0);
        pts.camera_id--;
    }else{
        if(pts.map_id <=0) return;
        std::cout << "Map窗口 - 取消点: ["<<pts.map_id<<"]" << std::endl;
        pts.map_points[(pts.map_id-1)/4][(pts.map_id-1)%4] = cv::Point(0,0);
        pts.map_id--;
    }
}

void Calibration::getTransformationMatrix() {
    H = getPerspectiveTransform(pts.camera_points[2], pts.map_points[2]);
    M = getPerspectiveTransform(pts.camera_points[1], pts.map_points[1]);
    L = getPerspectiveTransform(pts.camera_points[0], pts.map_points[0]);
    switch (CAMERA_CAR_MODE)
    {
    case MODE_TEST:
        saveMatrices("calibration_matrices_test.yaml");
        break;
    
    case MODE_VIDEO:
        saveMatrices("calibration_matrices_video.yaml");
        break;
    
    case MODE_HIK:
        saveMatrices("calibration_matrices_hik.yaml");
        break;
    case MODE_CAMERA:
        saveMatrices("calibration_matrices_camera.yaml");
        break;
    default:
        break;
    }
    // 保存三个矩阵到YAML文件

}

void Calibration::saveMatrices(const std::string& filename) {
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    // 只保存三个矩阵，没有其他任何信息
    fs << "L" << L;
    fs << "M" << M;
    fs << "H" << H;
    
    fs.release();
    std::cout << "三个矩阵已保存到: " << filename << std::endl;
}

void Calibration::loadMatrices(const std::string& filename) {
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }
    
    // 只读取三个矩阵
    fs["L"] >> L;
    fs["M"] >> M;
    fs["H"] >> H;
    
    fs.release();
    std::cout << "三个矩阵已从 " << filename << " 加载" << std::endl;
}