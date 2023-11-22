#include "FFmpegTool.h"

namespace fs = std::filesystem;
using namespace std;

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

std::string FFmpegTool::convert_seconds_to_time_format(int total_seconds) {
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    std::stringstream ss;
    ss << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds;

    return ss.str();
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

std::vector<std::string> FFmpegTool::get_video_details(const std::string &path) {
    /*
     * 1. 获取视频文件的详细信息
     * 2. 返回一个vector，包含视频文件的详细信息
     * 3. {"路径", "文件名", "编码格式", "分辨率", "帧率", "码率", "时长"}
     */
    string filePath = windows_path_to_linux_path(path);
    vector<std::string> videoInfo;
    // {"路径", "文件名", "编码格式", "分辨率", "帧率", "码率", "时长"}
    videoInfo.push_back(linux_path_to_windows_path(filePath));
    videoInfo.push_back(fs::path(filePath).filename().string());

    avformat_network_init();

    // 打开媒体文件
    AVFormatContext* formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, path.c_str(), NULL, NULL) != 0) {
        std::cerr << "无法打开文件：" << path << std::endl;
        return videoInfo;
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, NULL) < 0) {
        std::cerr << "无法获取流信息" << std::endl;
        return videoInfo;
    }

    // 查找视频流
    AVStream* videoStream = nullptr;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = formatContext->streams[i];
            break;
        }
    }

    if (!videoStream) {
        std::cerr << "未找到视频流" << std::endl;
        return videoInfo;
    }

    // 获取编码器上下文
    AVCodecParameters* codecParams = videoStream->codecpar;

    // 获取视频详细信息
    videoInfo.emplace_back(avcodec_get_name(codecParams->codec_id)); // 编码格式
    videoInfo.emplace_back(std::to_string(codecParams->width) + "x" + std::to_string(codecParams->height)); // 分辨率
    videoInfo.emplace_back(std::to_string(videoStream->avg_frame_rate.num / (double)videoStream->avg_frame_rate.den)); // 帧率
    videoInfo.emplace_back(std::to_string(codecParams->bit_rate)); // 码率

    videoInfo.emplace_back(to_string(formatContext->duration / AV_TIME_BASE)); // 时长（秒）

    // 清理
    avformat_close_input(&formatContext);
    avformat_free_context(formatContext);
    avformat_network_deinit();
}


void FFmpegTool::get_folder_videos_time(const std::string &folderPath, bool isPrint) {
    std::string path = windows_path_to_linux_path(folderPath);
    int videoCount = 0;
    std::vector<std::string> videos;
    std::vector<std::thread> threads;
    for (const auto &entry: fs::directory_iterator(path)) {
        if (Tools::isVideoFile(entry.path().filename().string())) {
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
        if (Tools::isVideoFile(entry.path().filename().string())) {
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

    // 获取视频流的比特率
    int64_t bit_rate = pCodecPar->bit_rate / 1000;

    // 获取视频流的时长
    int64_t duration = pFormatCtx->duration + (pFormatCtx->duration <= INT64_MAX - 5000 ? 5000 : 0);
    int64_t duration_in_seconds = duration / AV_TIME_BASE;

    // 获取编解码器描述符
    const AVCodecDescriptor *codec_desc = avcodec_descriptor_get(pCodecPar->codec_id);

    // 获取帧率
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
        std::cout << "Bit rate: " << bit_rate << "kbps" << std::endl;
        std::cout << "Duration: " << duration_in_seconds << " seconds" << std::endl;
    }
    if (codec_desc) {
        result.emplace_back(codec_desc->name);
    } else {
        result.emplace_back(std::to_string(pCodecPar->codec_id));
    }
    result.emplace_back(std::to_string(pCodecPar->width));
    result.emplace_back(std::to_string(pCodecPar->height));
    result.emplace_back(frame_rate_str);
    result.emplace_back(std::to_string(bit_rate));
    result.emplace_back(std::to_string(duration_in_seconds));

    // 关闭视频文件并清理
    avformat_close_input(&pFormatCtx);
    avformat_free_context(pFormatCtx);

    return result;
}

void FFmpegTool::get_folder_video_properties(const std::string &folderPath, bool isPrint) {
    std::string path = linuxMode ? windows_path_to_linux_path(folderPath) : folderPath;

    std::vector<std::vector<std::string>> outputProperties;

    for (const auto &entry: fs::recursive_directory_iterator(path)) {
        if (Tools::isVideoFile(entry.path().filename().string())) {
            std::vector<std::string> temp = check_video_properties(entry.path().string(), isPrint);
            std::vector<std::string> properties{entry.path().filename().string()};
            properties.insert(properties.end(), temp.begin(), temp.end());
            properties.emplace_back(entry.path().string());
            outputProperties.push_back(properties);
        }
    }

    fs::path outputPath = fs::path(path) / "output.txt";
    std::ofstream outfile(outputPath); // 创建或打开文件

    if (!outfile) {
        // 文件未能打开，可能是由于权限问题或其他原因
        std::cerr << "Unable to open file for writing." << '\n';
        return;
    }


    std::map<std::pair<std::string, std::string>, std::vector<std::string>> groupedProperties;
    for (const auto &props: outputProperties) {
        if (props.size() >= 5) { // 确保有足够的属性信息
            // 创建一个包含编码格式和分辨率的键
            std::pair<std::string, std::string> key(props[1], props[2] + "x" + props[3]);
            // 添加文件名到对应的分组中
            groupedProperties[key].push_back(props[0]);
        }
    }

    // 遍历 map 并输出每个分组的视频文件
    for (const auto &group: groupedProperties) {
        const auto &[key, filenames] = group;
        const auto &[codec, resolution] = key;
        outfile << "编码格式: " << codec << " 分辨率: " << resolution << '\n';

        for (const auto &filename: filenames) {
            // 查找完整路径和帧数
            auto it = std::find_if(outputProperties.begin(), outputProperties.end(),
                                   [&](const std::vector<std::string> &props) {
                                       return props.size() > 0 && props[0] == filename;
                                   });

            if (it != outputProperties.end() && it->size() >= 8) {

                outfile << "    文件名: " << filename
                        << " 路径: " << it->at(7)
                        << " 帧数: " << it->at(4)
                        << " 码率: " << it->at(5)
                        << " 时长: " << it->at(6) << '\n';

            }
        }
        outfile << '\n';
    }

    outfile << "********************" << "\n\n";

    for (const auto &group: groupedProperties) {
        const auto &[key, filenames] = group;
        const auto &[codec, resolution] = key;

        bool isFirst = true;

        for (const auto &filename: filenames) {
            // 查找完整路径
            auto it = std::find_if(outputProperties.begin(), outputProperties.end(),
                                   [&](const std::vector<std::string> &props) {
                                       return props.size() > 0 && props[0] == filename;
                                   });

            if (it != outputProperties.end() && it->size() >= 8) {
                // 如果是第一个文件，先输出编码格式和分辨率
                if (isFirst) {
                    outfile << "编码格式: " << codec << " 分辨率: " << resolution << '\n';
                    isFirst = false;
                }
                // 按照指定格式输出文件路径
                outfile << "file '" << it->at(7) << "'\n";
            }
        }
        outfile << '\n'; // 每个分组后面加一个新行
    }
    // 关闭文件
    outfile.close();
}



