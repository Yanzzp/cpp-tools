#ifndef CPP_TOOLS_TOOLS_H
#define CPP_TOOLS_TOOLS_H

#include <iostream>
#include <set>


class Tools {
private:
public:
    bool linuxMode = true;

    const std::set<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};
    const std::set<std::string> videoExtensions = {".mp4", ".avi", ".mkv", ".mov", ".wmv"};
    const std::set<std::string> audioExtensions = {".mp3", ".wav", ".flac", ".ape", ".aac"};


    bool isImageFile(const std::string &filename);

    bool isVideoFile(const std::string &filename);

    bool isAudioFile(const std::string &filename);

    static std::string windows_path_to_linux_path(std::string path);

    static std::string copy_to_clipboard(std::string str);
};


#endif //CPP_TOOLS_TOOLS_H
