#ifndef CPP_TOOLS_CVTOOLS_H
#define CPP_TOOLS_CVTOOLS_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

class CVTools {
private:

public:
    int mergeVideo(std::string video1,std::string video2);
};


#endif