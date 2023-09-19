#include "FFmpegToolBox.h"

void FFmpegToolBox::customErrorCallback(void *avcl, int level, const char *fmt, va_list vl) {
    if (level <= AV_LOG_ERROR) {
        char logMessage[1024];
        vsnprintf(logMessage, sizeof(logMessage), fmt, vl);

        // 获取传入的视频文件路径
        std::string videoFilePath = *static_cast<std::string *>(avcl);

        // 打印视频文件路径和错误消息
        std::cerr << "视频文件: " << videoFilePath << ", FFmpeg Error: " << logMessage << std::endl;
    }
}

vector<string> FFmpegToolBox::get_video_duration(const std::string &filePath, bool isPrint) {
    vector<string> video_info;

    // 设置自定义错误处理回调函数，并传入视频文件路径
    av_log_set_callback(customErrorCallback);

    fs::path path(filePath);
    AVFormatContext *formatContext = nullptr;

    // 打开视频文件
    if (avformat_open_input(&formatContext, filePath.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "无法打开视频文件" << std::endl;
        avformat_close_input(&formatContext);
        return video_info;
    }

    // 获取视频信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "无法获取视频信息" << std::endl;
        avformat_close_input(&formatContext);
        return video_info;
    }

    // 获取视频时长（以微秒为单位）
    int64_t duration = formatContext->duration;

    // 转换为秒
    int seconds = static_cast<int>(duration / AV_TIME_BASE);

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
    return video_info;
}

void FFmpegToolBox::get_all_videos_duration(const string &folderPath, bool isPrint) {
    for (const auto &entry: fs::directory_iterator(folderPath)) {
        if (mytools::isVideoFile(entry.path().filename().string())) {
            get_video_duration(entry.path().string(), isPrint);
        }
    }
}

int FFmpegToolBox::merge_videos(string folderPath1, string folderPath2) {

    AVFormatContext* mainFormatCtx = nullptr;
    if (avformat_open_input(&mainFormatCtx, folderPath1.c_str(), nullptr, nullptr) != 0) {
        fprintf(stderr, "Error: Could not open main video file\n");
        return 1;
    }

    if (avformat_find_stream_info(mainFormatCtx, nullptr) < 0) {
        fprintf(stderr, "Error: Could not find stream information\n");
        return 1;
    }

    AVFormatContext* additionalFormatCtx = nullptr;
    if (avformat_open_input(&additionalFormatCtx, folderPath1.c_str(), nullptr, nullptr) != 0) {
        fprintf(stderr, "Error: Could not open additional video file\n");
        return 1;
    }

    if (avformat_find_stream_info(additionalFormatCtx, nullptr) < 0) {
        fprintf(stderr, "Error: Could not find stream information for the additional video\n");
        return 1;
    }

    AVFormatContext* outputFormatCtx = nullptr;
    if (avformat_alloc_output_context2(&outputFormatCtx, nullptr, nullptr, "output.mp4") < 0) {
        fprintf(stderr, "Error: Could not create output format context\n");
        return 1;
    }

    if (avio_open(&outputFormatCtx->pb, "D:\\output.mp4", AVIO_FLAG_WRITE) < 0) {
        fprintf(stderr, "Error: Could not open output file\n");
        return 1;
    }


    for (int i = 0; i < mainFormatCtx->nb_streams; i++) {
        AVStream* stream = avformat_new_stream(outputFormatCtx, nullptr);
        avcodec_parameters_copy(stream->codecpar, mainFormatCtx->streams[i]->codecpar);
    }

    for (int i = 0; i < additionalFormatCtx->nb_streams; i++) {
        AVStream* stream = avformat_new_stream(outputFormatCtx, nullptr);
        avcodec_parameters_copy(stream->codecpar, additionalFormatCtx->streams[i]->codecpar);
    }

    if (avformat_write_header(outputFormatCtx, nullptr) < 0) {
        fprintf(stderr, "Error: Could not write header to output file\n");
        return 1;
    }

    AVPacket packet;
    while (av_read_frame(mainFormatCtx, &packet) >= 0) {
        packet.dts = 0;
        if(packet.pts < packet.dts) continue;
        if (av_interleaved_write_frame(outputFormatCtx, &packet) < 0) {
            fprintf(stderr, "Error while writing packet to output file\n");
            break;
        }

        av_packet_unref(&packet);
    }

    while (av_read_frame(additionalFormatCtx, &packet) >= 0) {
        packet.dts = 0;
        if(packet.pts < packet.dts) continue;
        if (av_interleaved_write_frame(outputFormatCtx, &packet) < 0) {
            fprintf(stderr, "Error while writing packet to output file\n");
            break;
        }

        av_packet_unref(&packet);
    }

    av_write_trailer(outputFormatCtx);

    avformat_close_input(&mainFormatCtx);
    avformat_close_input(&additionalFormatCtx);
    if (outputFormatCtx) {
        avio_closep(&outputFormatCtx->pb);
        avformat_free_context(outputFormatCtx);
    }
}
