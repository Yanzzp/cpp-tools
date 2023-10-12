#include "FFmpegTool.h"

using namespace std;


namespace fs = std::filesystem;

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

int FFmpegTool::get_single_video_time(const string &filePath, bool isPrint) {
    // 设置自定义错误处理回调函数，并传入视频文件路径
    av_log_set_callback(customErrorCallback);
    fs::path path(filePath);
    AVFormatContext *formatContext = nullptr;

    // 打开视频文件
    if (avformat_open_input(&formatContext, filePath.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "无法打开视频文件" << std::endl;
        avformat_close_input(&formatContext);
    }
    // 获取视频信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "无法获取视频信息" << std::endl;
        avformat_close_input(&formatContext);
    }
    // 获取视频时长（以微秒为单位）
    int64_t duration = formatContext->duration;
    // 转换为秒
    int seconds = static_cast<int>(duration / AV_TIME_BASE);
    int returnSeconds = seconds;
    // 将秒转换为时分秒格式
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    if (isPrint) {
        std::cout << path.filename().string() << "  视频时长: " << hours << "时 " << minutes << "分 " << seconds << "秒"
                  << std::endl;
    }
    // 关闭视频文件
    avformat_close_input(&formatContext);
    return returnSeconds;
}

void FFmpegTool::get_folder_videos_time(const string &folderPath, bool isPrint) {
    int videoCount = 0;
    vector<string> videos;
    vector<std::thread> threads;
    for (const auto &entry: fs::directory_iterator(folderPath)) {
        if (MyTools::isVideoFile(entry.path().filename().string())) {
            int time = get_single_video_time(entry.path().string(), isPrint);
            videoCount++;
        }
    }
    cout << "视频总数: " << videoCount << endl;

}

void FFmpegTool::move_short_videos(const string &folderPath, int maxTime, bool isMove, bool isPrint) {
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
    cout << "视频总数: " << videoCount << endl;
}