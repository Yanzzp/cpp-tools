#include "tools.h"

bool Tools::linuxMode = true;

const std::set<std::string> Tools::imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};
const std::set<std::string> Tools::videoExtensions = {".mp4", ".avi", ".mkv", ".mov", ".wmv"};
const std::set<std::string> Tools::audioExtensions = {".mp3", ".wav", ".flac", ".ape", ".aac"};


// 判断是否为图像文件
bool Tools::isImageFile(const std::string &filename) {
    // 根据文件扩展名判断是否为图像文件
    for (const std::string &extension: imageExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 判断是否为视频文件
bool Tools::isVideoFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    for (const std::string &extension: videoExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 判断是否为音频文件
bool Tools::isAudioFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    for (const std::string &extension: audioExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string Tools::windows_path_to_linux_path(std::string path) {
    std::string result = std::move(path);
    std::replace(result.begin(), result.end(), '\\', '/');
    if (result.size() > 1 && result[1] == ':') {
        char driveLetter = std::tolower(result[0]);
        result = "/mnt/" + std::string(1, driveLetter) + result.substr(2);
    }
    return result;
}

std::string Tools::copy_to_clipboard(std::string str) {
    std::string cmd = "echo \"" + str + "\" | clip.exe";
    std::system(cmd.c_str());
    return str;
}


std::string Tools::exec_command(const char *cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    try {
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
    } catch (const std::runtime_error &e) {
        // 返回错误消息，而不是抛出异常
        return std::string("Error: ") + e.what();
    }

    return result;
}
