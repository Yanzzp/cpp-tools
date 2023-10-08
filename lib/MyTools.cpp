#include <iomanip>
#include <unordered_set>
#include "MyTools.h"

using namespace std;
namespace fs = std::filesystem;



// 判断是否为图像文件
bool MyTools::isImageFile(const std::string &filename) {
    // 根据文件扩展名判断是否为图像文件
    std::vector<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};
    for (const std::string &extension: imageExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 判断是否为视频文件
bool MyTools::isVideoFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    std::vector<std::string> videoExtensions = {".mp4", ".avi", ".mkv", ".mov", ".wmv"};
    for (const std::string &extension: videoExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 判断是否为音频文件
bool MyTools::isAudioFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    std::vector<std::string> audioExtensions = {".mp3", ".wav", ".flac", ".ape", ".aac"};
    for (const std::string &extension: audioExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}


// 获取文件的大小
uintmax_t MyTools::get_file_size(string path) {
    std::lock_guard<std::mutex> lockGuard(folderSizeMutex);
    error_code ec{};
    auto size = std::filesystem::file_size(path, ec);
    if (ec == error_code{}) {
        folderSize += size;
    } else {
        cout << "Error accessing file '" << path
             << "' message: " << ec.message() << endl;
    }
    return size;
}

// 打印一个文件夹下的所有文件的路径
void MyTools::print_all_files(const std::string &path, int depth) {
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
void MyTools::delete_files(const string &path, string name, int depth) {
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

// 统计一个文件夹下的图片和视频的数量
void MyTools::count_imgs_videos_and_audio(const string &folderPath, string option) {
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (isImageFile(entry.path().filename().string())) {
            imageCount++;
        } else if (isVideoFile(entry.path().filename().string())) {
            videoCount++;
        } else if (isAudioFile(entry.path().filename().string())) {
            audioCount++;
        }
    }
    cout << "图片的数量是: " << imageCount << endl;
    cout << "视频的数量是: " << videoCount << endl;
    cout << "音频的数量是: " << audioCount << endl;

    if (option == "txt") {
        string txtFileName = folderPath + "\\";
        // 指定要创建的文件名
        if (imageCount != 0) {
            txtFileName += to_string(imageCount) + "P";
        }
        if (videoCount != 0) {
            txtFileName += to_string(videoCount) + "V";
        }
        if (audioCount != 0) {
            txtFileName += to_string(audioCount) + "A";
        }
        txtFileName += ".txt";
        try {
            fs::path fileToCreate(txtFileName);
            if (!fs::exists(fileToCreate)) {
                // 文件不存在，创建文件并打开以进行写入
                std::ofstream outputFile(fileToCreate.string());
                if (outputFile.is_open()) { // 检查文件是否成功打开
                    outputFile << "图片的数量是: " << imageCount << "\n";
                    outputFile << "视频的数量是: " << videoCount << "\n";
                    outputFile << "音频的数量是: " << videoCount << "\n";
                    outputFile.close();
                    std::cout << "文件 " << txtFileName << " 创建并写入成功。\n";
                } else {
                    std::cerr << "无法打开文件 " << txtFileName << std::endl;
                }
            } else {
                //            std::cerr << "文件 " << txtFileName << " 已经存在。\n";
                fs::remove(txtFileName);
                std::ofstream outputFile(fileToCreate.string());
                if (outputFile.is_open()) { // 检查文件是否成功打开
                    outputFile << "图片的数量是: " << imageCount << "\n";
                    outputFile << "视频的数量是: " << videoCount << "\n";
                    outputFile << "音频的数量是: " << videoCount << "\n";
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
        if (imageCount != 0) {
            textToCopy += to_string(imageCount) + "P";
        }
        if (videoCount != 0) {
            textToCopy += to_string(videoCount) + "V";
        }
        if (audioCount != 0) {
            textToCopy += to_string(audioCount) + "A";
        }

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
    if (option == "") {
        if (imageCount != 0) {
            folder_info[0] = to_string(imageCount) + "P";
        }
        if (videoCount != 0) {
            folder_info[1] = to_string(videoCount) + "V";
        }
        if (audioCount != 0) {
            folder_info[2] = to_string(audioCount) + "A";
        }
    }
}

// 统计一个文件夹的大小
void MyTools::get_folder_size(const std::string &folderPath, bool isPrint, bool printAll, bool keepData) {
    if (!keepData) {
        folderSize = 0;
    }
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            uintmax_t fileSize = get_file_size(entry.path().string());
            if (printAll) {
                float printSize = static_cast<float>(fileSize) / 1024 / 1024;
                std::cout << std::fixed << std::setprecision(2);
                if (printSize < 1024) {
                    cout << entry.path().string() << " 的大小是: " << printSize << "MB" << endl;
                } else {
                    cout << entry.path().string() << " 的大小是: " << (printSize /= 1024) << "GB" << endl;
                }
            }
        }
    }
    float Size = static_cast<float>(this->folderSize) / 1024 / 1024;
    bool isMB = true;
    if (Size > 1024) {
        Size /= 1024;
        isMB = false;
    }
    std::cout << std::fixed << std::setprecision(2);
    if (isPrint) {
        cout << "文件夹的大小是: " << Size << (isMB ? "MB" : "GB") << endl;
    }
    string store_num = to_string(Size);
    folder_info[3] = (store_num.substr(0, store_num.find('.') + 3) + (isMB ? "MB" : "GB"));
}


// 获取文件夹的信息
void MyTools::get_folder_info(const std::string &folderPath) {
    cout << "文件夹的路径是: " << folderPath << endl;
    cout << "文件夹的名称是: " << fs::path(folderPath).filename() << endl;
    count_imgs_videos_and_audio(folderPath);
    get_folder_size(folderPath);
    string textToCopy;
    for (int i = 0; i < folder_info.size(); ++i) {
        if (folder_info[i] != "") {
            textToCopy += folder_info[i] + " ";
        }
    }
    textToCopy.erase(textToCopy.end() - 1);
    textToCopy = "[" + textToCopy + "]";

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

void MyTools::change_files_extension(const string &folderPath, string newExtension, string oldExtension, bool isChange,
                                     bool option) {
    if (option == true) {
        for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                string fileName = entry.path().filename().string();
                string fileExtension = fs::path(fileName).extension().string();
                fileExtension.erase(0, 1);
                if (fileExtension == oldExtension) {
                    // 只有当文件的扩展名等于oldExtension时才执行以下操作。
                    string oldFileName = entry.path().string();
                    string newFileName = oldFileName;
                    newFileName.replace(newFileName.end() - oldExtension.size(), newFileName.end(), newExtension);

                    if (isChange) {
                        fs::rename(oldFileName, newFileName);
                    }
                    cout << oldFileName << " -> " << newFileName << endl;
                }
            }
        }
    } else {
        for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                string fileName = entry.path().filename().string();
                string fileExtension = fs::path(fileName).extension().string();
                fileExtension.erase(0, 1);
                cout << fileExtension << endl;
                string oldFileName = entry.path().string();
                string newFileName = oldFileName;
                newFileName.replace(newFileName.end() - oldExtension.size(), newFileName.end(), newExtension);
                if (isChange) {
                    fs::rename(oldFileName, newFileName);
                }
                cout << oldFileName << " -> " << newFileName << endl;
            }
        }
    }
}



void MyTools::move_files_to_main_folder(const string &folderPath, bool isMove) {
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            if (isMove) {
                try {
                    fs::rename(entry.path(), folderPath / entry.path().filename());
                    cout << entry.path().filename() << "成功移动到" << folderPath << endl;
                } catch (const std::exception &ex) {
                    cerr << "文件移动失败：" << ex.what() << std::endl;
                }
            }
        }
    }
}

void MyTools::multithread_get_folder_size(const string &folderPath, bool isPrint) {
    folderSize = 0;
    int count = 0;
    for (const auto &entry: fs::directory_iterator(folderPath)) {
        if (entry.is_directory()) {
            count++;
        }
    }
    if (count >= 4) {
        cout << "启用多线程计算文件夹大小" << endl;
    }
    std::vector<std::thread> threads;
    if (count >= 4) {
        for (const auto &entry: fs::directory_iterator(folderPath)) {
            if (entry.is_directory()) {
                threads.emplace_back(&MyTools::get_folder_size, this, entry.path().string(), false, false, true);
            } else {
                get_file_size(entry.path().string());
            }
        }
    } else {
        get_folder_size(folderPath, false);
    }


    for (auto &thread: threads) {
        thread.join();
    }
    std::cout << std::fixed << std::setprecision(2);
    cout << "文件夹的大小是: " << folder_info[3] << endl;

}






