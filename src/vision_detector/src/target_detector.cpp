#include <opencv2/opencv.hpp>
#include "config/config.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
std::vector<cv::Point2f> detectLaserSpot(const cv::Mat& frame);
std::vector<cv::Point2f> detectLaserModule(const cv::Mat& frame);



// 检查矩形是否大小和形状合理
bool isValidRect(const cv::Rect& rect) {
    int area = rect.width * rect.height;
    double wh_ratio = double(rect.width) / rect.height;
    return area > 100 && area < 2000 && wh_ratio > 0.5 && wh_ratio < 2.0;
}

// 返回每排最中心的y值，判定谁属于直线（±max_delta范围内）
std::vector<int> filterAligned(const std::vector<cv::Rect>& group, double max_delta = 10.0) {
    std::vector<int> centerYs;
    for (const auto& r : group) centerYs.push_back(r.y + r.height / 2);
    double meanY = std::accumulate(centerYs.begin(), centerYs.end(), 0.0) / centerYs.size();
    std::vector<int> alignedIdx;
    for (size_t i = 0; i < centerYs.size(); ++i) {
        if (std::abs(centerYs[i] - meanY) <= max_delta)
            alignedIdx.push_back(i);
    }
    return alignedIdx;
}

// 求两线交点
cv::Point2f intersectionPoint(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3, cv::Point2f p4) {
    float A1 = p2.y - p1.y;
    float B1 = p1.x - p2.x;
    float C1 = A1 * p1.x + B1 * p1.y;

    float A2 = p4.y - p3.y;
    float B2 = p3.x - p4.x;
    float C2 = A2 * p3.x + B2 * p3.y;

    float det = A1 * B2 - A2 * B1;
    if (std::abs(det) < 1e-5) // 平行
        return cv::Point2f(-1, -1);

    float x = (B2 * C1 - B1 * C2) / det;
    float y = (A1 * C2 - A2 * C1) / det;
    return cv::Point2f(x, y);
}

std::vector<cv::Point2f> detectLaserSpot(const cv::Mat& frame) {
    std::vector<cv::Point2f> candidates;
    
    cv::Mat hsvImage;
    cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);   // BGR → HSV

    std::vector<cv::Mat> hsvChannels;
    cv::split(hsvImage, hsvChannels);                      // 分离 H, S, V

    cv::Mat hChannel = hsvChannels[0];  // 色调通道 (Hue)
    cv::Mat sChannel = hsvChannels[1];  // 饱和度通道 (Saturation)
    cv::Mat vChannel = hsvChannels[2];  // 明度通道 (Value)
    cv::Scalar lower_green(40, 0, 150);
    cv::Scalar upper_green(75, 255, 255);
    cv::Mat green_mask;
    cv::inRange(hsvImage, lower_green, upper_green, green_mask);
    //cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_OPEN, kernel);

    //cv::erode(green_mask, green_mask, cv::Mat(), cv::Point(-1,-1), 2);
    //cv::dilate(green_mask, green_mask, cv::Mat(), cv::Point(-1,-1), 2);
    //cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    //cv::Mat processed;
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_CLOSE, kernel);

    // 可选：开运算去除残留的小噪点（先闭后开）
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_OPEN, kernel);
    // 查找轮廓（含层级）
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(green_mask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    double min_area = 50;
    double max_area = 999999;
    double circ_thresh = 0.8;//
    double concentric_thresh = 0.2; //

    for (size_t i = 0; i < contours.size(); i++) {
        if (hierarchy[i][2] == -1) continue; // 无子轮廓，跳过

        // 外部轮廓
        std::vector<cv::Point> outer = contours[i];
        double outer_area = cv::contourArea(outer);
        if (outer_area < min_area || outer_area > max_area) continue;

        // 凸包 + 圆度
        std::vector<cv::Point> hull;
        cv::convexHull(outer, hull);
        double hull_area = cv::contourArea(hull);
        double peri = cv::arcLength(hull, true);
        if (peri == 0) continue;
        double circ = 4 * CV_PI * hull_area / (peri * peri);
        if (circ < circ_thresh) continue;

        cv::Point2f outer_center;
        float outer_radius;
        cv::minEnclosingCircle(outer, outer_center, outer_radius);

        // 遍历子轮廓
        int child = hierarchy[i][2];
        while (child != -1) {
            std::vector<cv::Point> inner = contours[child];
            double inner_area = cv::contourArea(inner);
            if (inner_area > min_area/4) {
                // 计算内部轮廓圆度
                std::vector<cv::Point> inner_hull;
                cv::convexHull(inner, inner_hull);
                double inner_hull_area = cv::contourArea(inner_hull);
                double inner_peri = cv::arcLength(inner_hull, true);
                if (inner_peri > 0) {
                    double inner_circ = 4 * CV_PI * inner_hull_area / (inner_peri * inner_peri);
                    if (inner_circ > circ_thresh) {
                        cv::Point2f inner_center;
                        float inner_radius;
                        cv::minEnclosingCircle(inner, inner_center, inner_radius);
                        double dist = cv::norm(outer_center - inner_center);
                        if (dist / outer_radius < concentric_thresh) {
                            // 识别到圆环
                            candidates.push_back(outer_center);
                            break;
                        }
                    }
                }
            }
            child = hierarchy[child][0]; // 下一个兄弟
        }
    }
    return candidates;
}



std::vector<cv::Point2f> detectLaserModule(const cv::Mat& frame){
    // --- 抖动抑制状态（函数静态）---
    static cv::Point2f last_cross(-1.f, -1.f);
    static bool has_last_cross = false;
    static int lost_count = 0;

    static cv::Point2f roi_center(-1.f, -1.f);
    static bool has_roi_center = false;

    // 新增：记录上上一帧中心用于估计速度
    static cv::Point2f prev_cross(-1.f, -1.f);
    static bool has_prev_cross = false;

    // 新增：平滑后的动态 ROI 尺寸
    static float roi_w_f = 320.0f;
    static float roi_h_f = 240.0f;

    const int base_roi_w = 320;
    const int base_roi_h = 240;
    const int max_roi_w = frame.cols;
    const int max_roi_h = frame.rows;

    // 基于“上一帧两次中心”估计速度
    float speed = 0.0f;
    if (has_prev_cross && has_last_cross) {
        speed = cv::norm(last_cross - prev_cross);
    }

    // 速度映射到目标 ROI 尺寸（更明显）
    float scale = 1.0f + std::clamp(speed / 8.0f, 0.0f, 2.5f); // 1.0 ~ 3.5
    int target_w = std::clamp((int)std::round(base_roi_w * scale), base_roi_w, max_roi_w);
    int target_h = std::clamp((int)std::round(base_roi_h * scale), base_roi_h, max_roi_h);

    // 尺寸平滑，防止抖动
    const float size_alpha = 0.25f;
    roi_w_f = (1.0f - size_alpha) * roi_w_f + size_alpha * (float)target_w;
    roi_h_f = (1.0f - size_alpha) * roi_h_f + size_alpha * (float)target_h;

    int dyn_w = std::clamp((int)std::round(roi_w_f), base_roi_w, max_roi_w);
    int dyn_h = std::clamp((int)std::round(roi_h_f), base_roi_h, max_roi_h);

    // 小变化抑制（避免视觉上“没变化”）
    static int last_dyn_w = base_roi_w, last_dyn_h = base_roi_h;
    if (std::abs(dyn_w - last_dyn_w) < 8) dyn_w = last_dyn_w;
    if (std::abs(dyn_h - last_dyn_h) < 8) dyn_h = last_dyn_h;
    last_dyn_w = dyn_w;
    last_dyn_h = dyn_h;

    // 丢失时：直接全图搜索
    cv::Rect roi_rect(0, 0, frame.cols, frame.rows);
    if (has_roi_center && lost_count == 0) {
        int x = (int)std::round(roi_center.x - dyn_w * 0.5f);
        int y = (int)std::round(roi_center.y - dyn_h * 0.5f);
        roi_rect = cv::Rect(x, y, dyn_w, dyn_h) & cv::Rect(0, 0, frame.cols, frame.rows);
        if (roi_rect.width < 32 || roi_rect.height < 32) roi_rect = cv::Rect(0, 0, frame.cols, frame.rows);
    }

    // 在 ROI 内处理
    cv::Mat frame_roi = frame(roi_rect);
    cv::Mat hsv;
    cv::cvtColor(frame_roi, hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Point2f> candidates;

    // 远距增强：先增强亮小点（TopHat + 增益），再做颜色阈值
    std::vector<cv::Mat> hsv_ch0;
    cv::split(hsv, hsv_ch0);
    cv::Mat v_enh;
    cv::Mat k_tophat = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(9, 9));
    cv::morphologyEx(hsv_ch0[2], v_enh, cv::MORPH_TOPHAT, k_tophat);
    cv::addWeighted(hsv_ch0[2], 1.0, v_enh, 1.8, 0.0, hsv_ch0[2]); // 提亮小高光
    cv::merge(hsv_ch0, hsv); // 回写增强后的 HSV

    cv::Mat mask, red1, red2;
    if (DETECT_COLOR == COLOR_BLUE) {
        cv::inRange(hsv, cv::Scalar(90, 40, 55), cv::Scalar(145, 255, 255), mask);
    } else if (DETECT_COLOR == COLOR_RED) {
        cv::inRange(hsv, cv::Scalar(0, 35, 55), cv::Scalar(15, 255, 255), red1);
        cv::inRange(hsv, cv::Scalar(155, 35, 55), cv::Scalar(180, 255, 255), red2);
        cv::bitwise_or(red1, red2, mask);
    } else {
        return candidates;
    }

    // 新增：抑制墙面反光/白亮噪声（低S高V）
    {
        std::vector<cv::Mat> ch;
        cv::split(hsv, ch); // H,S,V
        cv::Mat white_reflect_mask;
        cv::inRange(hsv, cv::Scalar(0, 0, 200), cv::Scalar(180, 45, 255), white_reflect_mask);
        cv::bitwise_not(white_reflect_mask, white_reflect_mask);
        cv::bitwise_and(mask, white_reflect_mask, mask);
    }

    cv::Mat mask_raw = mask.clone();

    // LM2: 先填孔，解决空心点
    cv::Mat k2 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2));
    cv::Mat k3 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, k3); // 填充空心
    cv::medianBlur(mask, mask, 3);                     // 轻去噪，不强腐蚀

    // LM3: 轻开 + 距离变换分离粘连点（避免点被挖穿）
    cv::Mat mask_open;
    cv::morphologyEx(mask, mask_open, cv::MORPH_OPEN, k2);

    cv::Mat dist32f, dist8u;
    cv::distanceTransform(mask_open, dist32f, cv::DIST_L2, 3);
    double maxv = 0.0;
    cv::minMaxLoc(dist32f, nullptr, &maxv);
    double th = std::max(1.0, maxv * 0.35);           // 分离阈值
    cv::threshold(dist32f, dist32f, th, 255.0, cv::THRESH_BINARY);
    dist32f.convertTo(dist8u, CV_8U);

    // split_mask 用于 LM4 连通域，尽量把粘连拆成多个点
    cv::Mat split_mask;
    cv::bitwise_and(mask_open, dist8u, split_mask);
    cv::morphologyEx(split_mask, split_mask, cv::MORPH_DILATE, k2); // 回补一点面积，防止过小

    cv::Mat labels, stats, centroids;
    int n = cv::connectedComponentsWithStats(split_mask, labels, stats, centroids, 8, CV_32S);

    std::vector<cv::Point2f> pts;
    pts.reserve(n);
    cv::Mat comp_vis = cv::Mat::zeros(frame.size(), CV_8UC3);

    std::vector<cv::Mat> hsv_ch;
    cv::split(hsv, hsv_ch);
    const cv::Mat& v_ch = hsv_ch[2];
    double global_mean_v = cv::mean(v_ch)[0];
    double dyn_min_v = std::clamp(global_mean_v + 6.0, 60.0, 135.0); // 原 +10 / [70,145]

    float motion = has_last_cross ? 3.0f : 0.0f;
    int max_area = (motion > 2.0f) ? 320 : 220;  // 原 260/180
    float min_ratio = 0.12f;                     // 原 0.15
    float max_ratio = 7.0f;                      // 原 6.0

    for (int i = 1; i < n; ++i) {
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        int w = stats.at<int>(i, cv::CC_STAT_WIDTH);
        int h = stats.at<int>(i, cv::CC_STAT_HEIGHT);

        if (area < 1 || area > 160) continue; // 降低上限，避免一大团当一个点
        if (w < 1 || h < 1 || w > 24 || h > 24) continue; // 限制单点矩形尺寸

        float ratio = (h > 0) ? static_cast<float>(w) / h : 999.f;
        if (ratio < min_ratio || ratio > max_ratio) continue;

        cv::Rect r(stats.at<int>(i, cv::CC_STAT_LEFT), stats.at<int>(i, cv::CC_STAT_TOP), w, h);
        r &= cv::Rect(0, 0, frame.cols, frame.rows);
        if (r.empty()) continue;

        double mean_v = cv::mean(v_ch(r))[0];
        if (mean_v < dyn_min_v) continue;

        // 连通域中心点从 ROI 坐标映射回全图坐标
        cv::Point2f c(static_cast<float>(centroids.at<double>(i, 0) + roi_rect.x),
                      static_cast<float>(centroids.at<double>(i, 1) + roi_rect.y));

        // 新增：时序位置门控，抑制“被拐跑”
        if (has_last_cross) {
            float gate = (lost_count == 0) ? 180.0f : 260.0f; // 丢失时放宽
            if (cv::norm(c - last_cross) > gate) continue;
        }

        pts.push_back(c);

        cv::rectangle(comp_vis, r, cv::Scalar(255, 255, 0), 1);
        cv::circle(comp_vis, c, 2, cv::Scalar(0, 255, 255), -1);
    }

    // 邻域一致性过滤：放宽 + 亮点优先保留
    {
        std::vector<std::pair<cv::Point2f, float>> pts_scored;
        pts_scored.reserve(pts.size());
        for (auto &p : pts) {
            int x = std::clamp((int)std::round(p.x) - roi_rect.x, 0, frame_roi.cols - 1);
            int y = std::clamp((int)std::round(p.y) - roi_rect.y, 0, frame_roi.rows - 1);
            pts_scored.push_back({p, (float)v_ch.at<uchar>(y, x)});
        }

        std::vector<cv::Point2f> filtered;
        const float neighbor_dist = 65.0f;  // 原 50
        for (size_t i = 0; i < pts_scored.size(); ++i) {
            int cnt = 0;
            for (size_t j = 0; j < pts_scored.size(); ++j) {
                if (i == j) continue;
                if (cv::norm(pts_scored[i].first - pts_scored[j].first) < neighbor_dist) cnt++;
            }
            // 有邻居直接保留；无邻居但亮度高也保留
            if (cnt >= 1 || pts_scored[i].second >= (float)(dyn_min_v + 20.0)) {
                filtered.push_back(pts_scored[i].first);
            }
        }

        // 兜底：若仍太少，按亮度取前N个
        if (filtered.size() < 4) {
            std::sort(pts_scored.begin(), pts_scored.end(),
                      [](const auto& a, const auto& b){ return a.second > b.second; });
            filtered.clear();
            for (size_t i = 0; i < std::min<size_t>(12, pts_scored.size()); ++i) {
                filtered.push_back(pts_scored[i].first);
            }
        }
        pts.swap(filtered);
    }

    // fallback：点仍不足时，从 mask 提角点补充
    if (pts.size() < 4) {
        std::vector<cv::Point2f> corners;
        cv::goodFeaturesToTrack(mask, corners, 20, 0.01, 8);
        for (auto &cp : corners) pts.emplace_back(cp.x + roi_rect.x, cp.y + roi_rect.y);

        // 去重（近邻合并）
        std::vector<cv::Point2f> dedup;
        for (auto &p : pts) {
            bool ok = true;
            for (auto &q : dedup) {
                if (cv::norm(p - q) < 4.0f) { ok = false; break; }
            }
            if (ok) dedup.push_back(p);
        }
        pts.swap(dedup);
    }

    if (pts.size() < 4) {
        if (has_last_cross && lost_count < 5) {
            candidates.push_back(last_cross);
            lost_count++;
        }

        // 丢失即全图
        has_roi_center = false;

        // 新增：早退分支也更新调试画面
        cv::Mat dbg = frame.clone();
        cv::rectangle(dbg, roi_rect, cv::Scalar(0, 128, 255), 2);
        cv::putText(dbg, "ROI", cv::Point(roi_rect.x + 4, std::max(16, roi_rect.y - 4)),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 128, 255), 1);
        cv::putText(dbg, "Target Lost", cv::Point(20, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
        if (has_last_cross) {
            cv::circle(dbg, last_cross, 6, cv::Scalar(0, 0, 255), -1);
        }
        cv::imshow("Detected Laser Module (Point Mode)", dbg);
        cv::waitKey(1);

        return candidates;
    }

    cv::Mat y_mat(static_cast<int>(pts.size()), 1, CV_32F);
    for (size_t i = 0; i < pts.size(); ++i) y_mat.at<float>(static_cast<int>(i), 0) = pts[i].y;

    cv::Mat labels_k;
    cv::kmeans(y_mat, 2, labels_k,
               cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0),
               3, cv::KMEANS_PP_CENTERS);

    std::vector<cv::Point2f> row1, row2;
    for (size_t i = 0; i < pts.size(); ++i) {
        if (labels_k.at<int>(static_cast<int>(i), 0) == 0) row1.push_back(pts[i]);
        else row2.push_back(pts[i]);
    }
    if (row1.size() < 2 || row2.size() < 2) {
        // 分组失败视作丢失，下一帧全图
        has_roi_center = false;
        lost_count = std::min(lost_count + 1, 1000);

        // 新增：分组失败也刷新调试
        cv::Mat dbg = frame.clone();
        cv::rectangle(dbg, roi_rect, cv::Scalar(0, 128, 255), 2);
        cv::putText(dbg, "ROI", cv::Point(roi_rect.x + 4, std::max(16, roi_rect.y - 4)),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 128, 255), 1);
        cv::putText(dbg, "Grouping Failed", cv::Point(20, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
        cv::imshow("Detected Laser Module (Point Mode)", dbg);
        cv::waitKey(1);
        return candidates;
    }

    auto meanY = [](const std::vector<cv::Point2f>& v){
        double s = 0.0; for (auto &p : v) s += p.y; return s / std::max<size_t>(1, v.size());
    };
    if (meanY(row1) > meanY(row2)) std::swap(row1, row2);

    // 行内带宽约束：剔除离群点（长焦抖动+误检）
    auto filterRowByBand = [](std::vector<cv::Point2f>& row, float band){
        if (row.size() < 2) return;
        double my = 0.0; for (auto& p : row) my += p.y; my /= row.size();
        std::vector<cv::Point2f> keep;
        for (auto& p : row) if (std::fabs(p.y - my) <= band) keep.push_back(p);
        if (keep.size() >= 2) row.swap(keep);
    };
    filterRowByBand(row1, 18.0f);
    filterRowByBand(row2, 18.0f);
    if (row1.size() < 2 || row2.size() < 2) return candidates;

    std::sort(row1.begin(), row1.end(), [](const cv::Point2f& a, const cv::Point2f& b){ return a.x < b.x; });
    std::sort(row2.begin(), row2.end(), [](const cv::Point2f& a, const cv::Point2f& b){ return a.x < b.x; });

    cv::Point2f LU = row1.front(), RU = row1.back();
    cv::Point2f LD = row2.front(), RD = row2.back();

    // 原始交点（保留作参考）
    cv::Point2f crossPt = intersectionPoint(LU, RD, RU, LD);

    // 新中心：上下中点连线的中点（对上下边长度不一致更鲁棒）
    cv::Point2f upper_mid = 0.5f * (LU + RU);
    cv::Point2f lower_mid = 0.5f * (LD + RD);
    cv::Point2f mid_center = 0.5f * (upper_mid + lower_mid);

    // 融合中心：中点法为主，交点法为辅
    cv::Point2f fused_center = mid_center;
    if (crossPt.x >= 0 && crossPt.y >= 0 && crossPt.x < frame.cols && crossPt.y < frame.rows) {
        fused_center = 0.8f * mid_center + 0.2f * crossPt;
    }

    if (fused_center.x >= 0 && fused_center.y >= 0 &&
        fused_center.x < frame.cols && fused_center.y < frame.rows) {

        // 关键修复：先保存更新前的 last_cross 到 prev_cross
        if (has_last_cross) {
            prev_cross = last_cross;
            has_prev_cross = true;
        }

        if (!has_last_cross) {
            last_cross = fused_center;
            has_last_cross = true;
        } else {
            float move = cv::norm(fused_center - last_cross);
            float alpha = (move < 2.0f) ? 0.18f : (move < 6.0f ? 0.30f : 0.55f);
            last_cross = (1.0f - alpha) * last_cross + alpha * fused_center;
        }

        candidates.push_back(last_cross);
        lost_count = 0;
        roi_center = last_cross;
        has_roi_center = true;

    } else if (has_last_cross && lost_count < 5) {
        candidates.push_back(last_cross);
        lost_count++;
        has_roi_center = false;
    } else {
        has_roi_center = false;
    }

    // 可视化：评估中心点、对角线、图像中心、偏差连线
    cv::Mat dbg = frame.clone();

    // 候选点
    for (auto &p : pts) cv::circle(dbg, p, 2, cv::Scalar(0, 255, 255), -1);

    // 四角点
    cv::circle(dbg, LU, 4, cv::Scalar(255, 0, 0), -1);
    cv::circle(dbg, RU, 4, cv::Scalar(255, 0, 0), -1);
    cv::circle(dbg, LD, 4, cv::Scalar(0, 255, 0), -1);
    cv::circle(dbg, RD, 4, cv::Scalar(0, 255, 0), -1);

    // 对角线（用于评估中心）
    cv::line(dbg, LU, RD, cv::Scalar(255, 255, 255), 1);
    cv::line(dbg, RU, LD, cv::Scalar(255, 255, 255), 1);

    // 新增：上下中点及中线
    cv::circle(dbg, upper_mid, 4, cv::Scalar(255, 255, 0), -1);
    cv::circle(dbg, lower_mid, 4, cv::Scalar(255, 255, 0), -1);
    cv::line(dbg, upper_mid, lower_mid, cv::Scalar(255, 255, 0), 1);

    // 图像中心点
    cv::Point2f img_center(dbg.cols * 0.5f, dbg.rows * 0.5f);
    cv::circle(dbg, img_center, 5, cv::Scalar(255, 0, 255), 2);

    // 评估中心点 + 连线到图像中心
    if (!candidates.empty()) {
        cv::Point2f eval_center = candidates[0];
        cv::circle(dbg, eval_center, 6, cv::Scalar(0, 0, 255), -1);
        cv::line(dbg, img_center, eval_center, cv::Scalar(0, 255, 255), 2);

        float dx = eval_center.x - img_center.x;
        float dy = eval_center.y - img_center.y;
        cv::putText(dbg, cv::format("dX=%.1f dY=%.1f", dx, dy), cv::Point(20, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
    }

    // 调试显示：增加 ROI 框
    cv::rectangle(dbg, roi_rect, cv::Scalar(0, 128, 255), 2);
    cv::putText(dbg, "ROI", cv::Point(roi_rect.x + 4, std::max(16, roi_rect.y - 4)),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 128, 255), 1);
    cv::putText(dbg, cv::format("ROI:%dx%d V:%.1f", dyn_w, dyn_h, speed),
                cv::Point(20, 55), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                cv::Scalar(0, 200, 255), 2);

    cv::imshow("Detected Laser Module (Point Mode)", dbg);
    cv::waitKey(1);

    return candidates;
}