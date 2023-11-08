#include "FFmpegTool.h"

namespace fs = std::filesystem;

std::string FFmpegTool::windows_path_to_linux_path(std::string path) {
    std::string result = std::move(path);
    std::replace(result.begin(), result.end(), '\\', '/');
    if (result.size() > 1 && result[1] == ':') {
        char driveLetter = std::tolower(result[0]);
        result = "/mnt/" + std::string(1, driveLetter) + result.substr(2);
    }
    return result;
}

// 自定义错误处理回调函数
void FFmpegTool::customErrorCallback(void *avcl, int level, const char *fmt, va_list vl) {
    if (level <= AV_LOG_ERROR) {
        char logMessage[1024];
        vsnprintf(logMessage, sizeof(logMessage), fmt, vl);

        // 获取传入的视频文件路径
        std::string videoFilePath = *static_cast<std::string *>(avcl);

        // 打印视频文件路径和错误消息
        std::cerr << "视频文件: " << videoFilePath << ", FFmpeg Error: " << logMessage << std::endl;
    }
}

int FFmpegTool::get_single_video_time(const std::string &filePath, bool isPrint) {
    std::string linuxPath = windows_path_to_linux_path(filePath);
    // 设置自定义错误处理回调函数，并传入视频文件路径
    av_log_set_callback(customErrorCallback);

    AVFormatContext *formatContext = nullptr;

    // 打开视频文件并获取视频信息
    if (avformat_open_input(&formatContext, linuxPath.c_str(), nullptr, nullptr) != 0 ||
        avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "无法打开视频文件或获取视频信息" << std::endl;
        if (formatContext) avformat_close_input(&formatContext);
        return -1; // 如果出错，返回-1或其他错误代码
    }

    // 获取视频时长（以秒为单位）
    int returnSeconds = static_cast<int>(formatContext->duration / AV_TIME_BASE);

    // 将秒转换为时分秒格式
    int hours = returnSeconds / 3600;
    int minutes = (returnSeconds % 3600) / 60;
    int seconds = returnSeconds % 60;

    if (isPrint) {
        // 只在需要时构造文件名字符串
        std::cout << fs::path(linuxPath).filename().string()
                  << " 视频时长: "
                  << hours << "时 "
                  << minutes << "分 "
                  << seconds << "秒" << std::endl;
    }

    // 关闭视频文件
    avformat_close_input(&formatContext);

    return returnSeconds;
}


void FFmpegTool::get_folder_videos_time(const std::string &folderPath, bool isPrint) {
    std::string path = windows_path_to_linux_path(folderPath);
    int videoCount = 0;
    std::vector<std::string> videos;
    std::vector<std::thread> threads;
    for (const auto &entry: fs::directory_iterator(path)) {
        if (MyTools::isVideoFile(entry.path().filename().string())) {
            int time = get_single_video_time(entry.path().string(), isPrint);
            videoCount++;
        }
    }
    std::cout << "视频总数: " << videoCount << std::endl;

}

void FFmpegTool::move_short_videos(const std::string &folderPath, int maxTime, bool isMove, bool isPrint) {
    int videoCount = 0;
    try {
        // 要创建的文件夹路径
        fs::path shortPath = folderPath + "\\short";

        // 使用 create_directory 函数创建文件夹
        if (fs::create_directory(shortPath)) {
            std::cout << "文件夹创建成功！" << std::endl;
        } else {
            std::cout << "文件夹创建失败或文件夹已存在。" << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "文件夹创建失败: " << e.what() << std::endl;
    }
    for (const auto &entry: fs::directory_iterator(folderPath)) {
        if (MyTools::isVideoFile(entry.path().filename().string())) {
            videoCount++;
            int time = get_single_video_time(entry.path().string(), isPrint);

            if (time > maxTime) {
                continue;
            }
            try {
                fs::path sourceFolder = entry.path().string();
                fs::path targetFolder = folderPath + "\\short\\" + entry.path().filename().string();
                fs::rename(sourceFolder, targetFolder);
            } catch (const std::exception &e) {
                std::cerr << entry.path().filename().string() << "移动失败: " << e.what() << std::endl;
            }
        }
    }
    std::cout << "视频总数: " << videoCount << std::endl;
}

std::vector<std::string> FFmpegTool::check_video_properties(const std::string &Path, bool isPrint) {
    std::string filePath;
    if (linuxMode) {
        filePath = windows_path_to_linux_path(Path);
    }
    std::vector<std::string> result;
    const char *filename = filePath.c_str();
    AVFormatContext *pFormatCtx = avformat_alloc_context();

    // 打开视频文件
    if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0) {
        std::cerr << "Could not open file: " << filename << std::endl;
    }

    // 检索流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        std::cerr << "Could not find stream information for file: " << filename << std::endl;
    }

    // 找到视频流
    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        std::cerr << "Could not find video stream in file: " << filename << std::endl;
    }

    // 获取视频流的编解码器参数
    AVCodecParameters *pCodecPar = pFormatCtx->streams[videoStreamIndex]->codecpar;

    // 获取编解码器描述符
    const AVCodecDescriptor *codec_desc = avcodec_descriptor_get(pCodecPar->codec_id);

    double frame_rate = av_q2d(pFormatCtx->streams[videoStreamIndex]->avg_frame_rate);

    // 使用ostringstream来进行转换
    std::ostringstream stream;

    // 检查小数部分是否为0
    if (frame_rate - static_cast<int>(frame_rate) == 0.0) {
        // 小数部分为0，只输出整数部分
        stream << static_cast<int>(frame_rate);
    } else {
        // 小数部分不为0，保留两位小数
        stream << std::fixed << std::setprecision(2) << frame_rate;
    }

    // 将ostringstream转换为string
    std::string frame_rate_str = stream.str();

    // 打印所需的信息
    if (isPrint) {
        std::cout << "File: " << filename << std::endl;
        if (codec_desc) {
            std::cout << "Codec: " << codec_desc->name << std::endl; // 打印编解码器的名称
            result.emplace_back(codec_desc->name);
        } else {
            std::cout << "Codec ID: " << pCodecPar->codec_id << " (Unknown)" << std::endl; // 未知的编解码器ID
            result.emplace_back(std::to_string(pCodecPar->codec_id));

        }
        std::cout << "Resolution: " << pCodecPar->width << "x" << pCodecPar->height << std::endl;
        std::cout << "Frame rate: " << frame_rate_str << std::endl;
        result.emplace_back(std::to_string(pCodecPar->width));
        result.emplace_back(std::to_string(pCodecPar->height));
        result.emplace_back(frame_rate_str);
    }

    // 关闭视频文件并清理
    avformat_close_input(&pFormatCtx);
    avformat_free_context(pFormatCtx);

    return result;
}



