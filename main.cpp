//#include "mytools.h"
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//using namespace std;
//
//
//int main() {
////    mytools tools;
//
////    tools.create_txt_file("C:\\Users\\Administrator\\Desktop\\test\\test.txt");
//
//    return 0;
//}
//


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main() {
    Mat img = imread("C:\\Users\\11057\\Desktop\\test.jpg");
    // 打开第一个视频文件和第二个视频文件
//    VideoCapture video1("E:\\MyCodeProject\\CLionProjects\\cpp-tools\\v4.mp4"); // 替换为第一个视频文件的路径
//    VideoCapture video2("E:\\MyCodeProject\\CLionProjects\\cpp-tools\\v7.mp4"); // 替换为第二个视频文件的路径

    // 检查视频文件是否成功打开
//    if (!video1.isOpened() || !video2.isOpened()) {
//        std::cerr << "无法打开视频文件" << std::endl;
//        return -1;
//    }
//
//    // 获取视频的帧率、宽度、高度和音频参数
//    double fps = video1.get(CAP_PROP_FPS); // 获取第一个视频的帧率
//    int width = video1.get(CAP_PROP_FRAME_WIDTH); // 获取第一个视频的宽度
//    int height = video1.get(CAP_PROP_FRAME_HEIGHT); // 获取第一个视频的高度
//    int audioCodec = static_cast<int>(video1.get(CAP_PROP_FOURCC)); // 获取音频编解码器
//
//    // 创建一个VideoWriter来保存合并的视频，并设置音频参数
//    VideoWriter outputVideo("C:\\Users\\11057\\Desktop\\v9.mp4", audioCodec, fps, Size(width, height * 2), true);
//
//    Mat frame1, frame2;
//
//    while (true) {
//        video1 >> frame1;
//        video2 >> frame2;
//
//        if (frame1.empty() || frame2.empty()) {
//            break;
//        }
//
//        Mat combinedFrame(height * 2, width, frame1.type());
//
//        // 在输出帧上拷贝第一个视频的帧
//        Mat top(combinedFrame, Rect(0, 0, width, height));
//        frame1.copyTo(top);
//
//        // 在输出帧上拷贝第二个视频的帧
//        Mat bottom(combinedFrame, Rect(0, height, width, height));
//        frame2.copyTo(bottom);
//
//        outputVideo << combinedFrame;
//    }
//
//    // 释放视频捕捉和写入对象，完成合并
//    video1.release();
//    video2.release();
//    outputVideo.release();

    return 0;
}
