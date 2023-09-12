#include "mytools.h"

// 打印一个文件夹下的所有文件的路径
void mytools::print_all_files(const std::string &path, int depth) {
    for (const auto &entry: fs::directory_iterator(path)) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "    "; // 用缩进表示层级
        }

        if (entry.is_directory()) {
            std::cout << "[Folder] " << entry.path().string() << std::endl;
            print_all_files(entry.path().string(), depth + 1); // 递归调用自身遍历子文件夹
        } else if (entry.is_regular_file()) {
            std::cout << "[File]   " << entry.path().string() << std::endl;
        }
    }
}


// 删除一个文件夹含有某个字符串的文件
void mytools::delete_files(const string &path, string name, int depth) {
    for (const auto &entry: fs::directory_iterator(path)) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "    "; // 用缩进表示层级
        }

        if (entry.is_directory()) {
            if (entry.path().filename().string().find(name) != string::npos) {
                cout << "delete " << entry.path().string() << endl;
            }
            print_all_files(entry.path().string(), depth + 1); // 递归调用自身遍历子文件夹
        } else if (entry.is_regular_file()) {

        }
    }

}


bool mytools::isImageFile(const std::string &filename) {
    // 根据文件扩展名判断是否为图像文件
    std::vector<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};
    for (const std::string &extension: imageExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool mytools::isVideoFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    std::vector<std::string> videoExtensions = {".mp4", ".avi", ".mkv", ".mov", ".wmv"};
    for (const std::string &extension: videoExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 统计一个文件夹下的图片和视频的数量
void mytools::count_imgs_and_videos(const string &folderPath, string option) {
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (isImageFile(entry.path().filename().string())) {
            imageCount++;
        } else if (isVideoFile(entry.path().filename().string())) {
            videoCount++;
        }
    }
    cout << "图片的数量是: " << imageCount << endl;
    cout << "视频的数量是: " << videoCount << endl;

    if (option == "txt") {
        string txtFileName;
        // 指定要创建的文件名
        if (imageCount == 0 && videoCount != 0) {
            txtFileName = folderPath + "\\" + to_string(videoCount) + "V.txt";
        } else if (videoCount == 0 && imageCount != 0) {
            txtFileName = folderPath + "\\" + to_string(imageCount) + "P.txt";
        }
        if (imageCount != 0 && videoCount != 0) {
            txtFileName = folderPath + "\\" + to_string(imageCount) + "P_" + to_string(videoCount) + "V.txt";
        }

        try {
            fs::path fileToCreate(txtFileName);
            if (!fs::exists(fileToCreate)) {
                // 文件不存在，创建文件并打开以进行写入
                std::ofstream outputFile(fileToCreate);
                if (outputFile.is_open()) { // 检查文件是否成功打开
                    outputFile << "图片的数量是: " << imageCount << "\n";
                    outputFile << "视频的数量是: " << videoCount << "\n";
                    outputFile.close();
                    std::cout << "文件 " << txtFileName << " 创建并写入成功。\n";
                } else {
                    std::cerr << "无法打开文件 " << txtFileName << std::endl;
                }
            } else {
                //            std::cerr << "文件 " << txtFileName << " 已经存在。\n";
                fs::remove(txtFileName);
                std::ofstream outputFile(fileToCreate);
                if (outputFile.is_open()) { // 检查文件是否成功打开
                    outputFile << "图片的数量是: " << imageCount << "\n";
                    outputFile << "视频的数量是: " << videoCount << "\n";
                    outputFile.close();
                    std::cout << "文件 " << txtFileName << " 创建并写入成功。\n";
                } else {
                    std::cerr << "无法打开文件 " << txtFileName << std::endl;
                }
            }
        } catch (const std::exception &ex) {
            std::cerr << "发生错误: " << ex.what() << std::endl;
        }
    }
    if (option == "copy") {
        string textToCopy;
        // 指定要创建的文件名
        if (imageCount == 0 && videoCount != 0) {
            textToCopy = to_string(videoCount) + "V";
        } else if (videoCount == 0 && imageCount != 0) {
            textToCopy = to_string(imageCount) + "P";
        }
        if (imageCount != 0 && videoCount != 0) {
            textToCopy = to_string(imageCount) + "P_" + to_string(videoCount) + "V";
        }
        cout << textToCopy << endl;

        if (OpenClipboard(nullptr)) {
            // 清空剪贴板内容
            EmptyClipboard();
            // 获取字符串的长度，包括 null 终止字符
            size_t textSize = textToCopy.size() + 1;
            // 分配全局内存并将字符串复制进去
            HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, textSize);
            if (hClipboardData != nullptr) {
                char *pClipboardText = static_cast<char *>(GlobalLock(hClipboardData));
                if (pClipboardText != nullptr) {
                    strcpy_s(pClipboardText, textSize, textToCopy.c_str());
                    GlobalUnlock(hClipboardData);

                    // 将数据设置到剪贴板
                    SetClipboardData(CF_TEXT, hClipboardData);
                } else {
                    std::cerr << "无法锁定全局内存。" << std::endl;
                }
            } else {
                std::cerr << "无法分配全局内存。" << std::endl;
            }

            CloseClipboard();
        } else {
            std::cerr << "无法打开剪贴板。" << std::endl;
        }
    }

}
