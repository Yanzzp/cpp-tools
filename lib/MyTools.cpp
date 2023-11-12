#include "MyTools.h"


namespace fs = std::filesystem;


const std::set<std::string> MyTools::imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};
const std::set<std::string> MyTools::videoExtensions = {".mp4", ".avi", ".mkv", ".mov", ".wmv"};
const std::set<std::string> MyTools::audioExtensions = {".mp3", ".wav", ".flac", ".ape", ".aac"};

// 判断是否为图像文件
bool MyTools::isImageFile(const std::string &filename) {
    // 根据文件扩展名判断是否为图像文件
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
    for (const std::string &extension: audioExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string MyTools::windows_path_to_linux_path(std::string path) {
    std::string result = std::move(path);
    std::replace(result.begin(), result.end(), '\\', '/');
    if (result.size() > 1 && result[1] == ':') {
        char driveLetter = std::tolower(result[0]);
        result = "/mnt/" + std::string(1, driveLetter) + result.substr(2);
    }
    return result;
}

std::string MyTools::copy_to_clipboard(std::string str) {
    std::string cmd = "echo \"" + str + "\" | clip.exe";
    std::system(cmd.c_str());
    return str;
}


// 获取文件的大小
uintmax_t MyTools::get_file_size(std::string path) {
    std::lock_guard<std::mutex> lockGuard(fileSizeMutex);
    std::error_code ec{};
    auto size = std::filesystem::file_size(path, ec);
    if (ec == std::error_code{}) {
        folderSize += size;
    } else {
        std::cout << "Error accessing file '" << path
                  << "' message: " << ec.message() << std::endl;
    }
    return size;
}

// 打印一个文件夹下的所有文件的路径
void MyTools::print_all_files(const std::string &folderPath, int depth) {
    std::string path;
    if(linuxMode){
         path = windows_path_to_linux_path(folderPath);
    }
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


void MyTools::delete_files(const std::string &folderPath, const std::vector<std::string> &names, bool isDelete,
                           bool isPrint) {
    std::string path;
    if(linuxMode){
        path = windows_path_to_linux_path(folderPath);
    }

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        // 如果当前条目是一个目录，递归进入这个目录
        if (std::filesystem::is_directory(entry.status())) {
            delete_files(entry.path().string(), names, isDelete, isPrint);
        }

        for (const auto &name: names) {
            if (entry.path().string().find(name) != std::string::npos) {
                if (isPrint) {
                    std::cout << entry.path().string() << std::endl;
                }
                if (isDelete) {
                    std::error_code ec; // 用于捕获错误
                    std::filesystem::remove_all(entry.path(), ec); // 删除文件或目录
                    if (ec) { // 如果有错误
                        std::cerr << "Error deleting: " << entry.path().string() << ". Reason: " << ec.message()
                                  << std::endl;
                    }
                }
                break; // 如果找到了一个匹配，就跳出循环
            }
        }
    }
}


// 统计一个文件夹下的图片和视频的数量
void MyTools::count_imgs_videos_and_audio(const std::string &folderPath, const std::string &option) {
    std::string path;
    if(linuxMode){
        path = windows_path_to_linux_path(folderPath);
    }

    for (const auto &entry: fs::recursive_directory_iterator(path)) {
        if (isImageFile(entry.path().filename().string())) {
            imageCount++;
        } else if (isVideoFile(entry.path().filename().string())) {
            videoCount++;
        } else if (isAudioFile(entry.path().filename().string())) {
            audioCount++;
        }
    }
    std::cout << "图片的数量是: " << imageCount << std::endl;
    std::cout << "视频的数量是: " << videoCount << std::endl;
    std::cout << "音频的数量是: " << audioCount << std::endl;

    if (option == "txt") {
        std::string txtFileName = path + "/" +
                                  (imageCount ? std::to_string(imageCount) + "P" : "") +
                                  (videoCount ? std::to_string(videoCount) + "V" : "") +
                                  (audioCount ? std::to_string(audioCount) + "A" : "") +
                                  (!(imageCount || videoCount || audioCount) ? "Empty" : "") +
                                  ".txt";
        fs::path fileToCreate(txtFileName);

        // 检查文件是否存在，如果存在则删除
        if (fs::exists(fileToCreate)) {
            std::cout << "文件 " << txtFileName << " 已存在，将被覆盖。\n";
            fs::remove(fileToCreate);
        }
        // 创建并写入文件
        try {
            std::ofstream outputFile(fileToCreate.string());
            if (outputFile.is_open()) {
                outputFile << "图片的数量是: " << imageCount << "\n";
                outputFile << "视频的数量是: " << videoCount << "\n";
                outputFile << "音频的数量是: " << audioCount << "\n";
                outputFile.close();
                std::cout << "文件 " << txtFileName << " 创建并写入成功。\n";
            } else {
                std::cerr << "无法打开文件 " << txtFileName << std::endl;
            }
        } catch (const std::exception &ex) {
            std::cerr << "发生错误: " << ex.what() << std::endl;
        }
    }
    if (option == "copy") {
        std::string textToCopy;

        // 通过条件运算符合并三个条件的判断和字符串拼接
        textToCopy += (imageCount != 0) ? std::to_string(imageCount) + "P" : "";
        textToCopy += (videoCount != 0) ? std::to_string(videoCount) + "V" : "";
        textToCopy += (audioCount != 0) ? std::to_string(audioCount) + "A" : "";

        // 如果上面的统计都是0，textToCopy将为空
        if (textToCopy.empty()) {
            textToCopy = "Empty";  // 或者你可能想要一个指示"无内容"的消息
        }

        // 输出到剪贴板结果
        std::cout << copy_to_clipboard(textToCopy) << std::endl;
    }
    if (option.empty()) {
        folder_info[0] = (imageCount != 0) ? std::to_string(imageCount) + "P" : "";
        folder_info[1] = (videoCount != 0) ? std::to_string(videoCount) + "V" : "";
        folder_info[2] = (audioCount != 0) ? std::to_string(audioCount) + "A" : "";
    }
}

// 统计一个文件夹的大小
void MyTools::get_folder_size(const std::string &folderPath, bool isPrint, bool printAll, bool keepData) {
    std::string path;
    if(linuxMode){
        path = windows_path_to_linux_path(folderPath);
    }
    // 是否保留之前文件的大小
    if (!keepData) {
        folderSize = 0;
    }
    for (const auto &entry: fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            uintmax_t fileSize = get_file_size(entry.path().string());
            if (printAll) {
                float printSize = static_cast<float>(fileSize) / 1024 / 1024;
                std::cout << std::fixed << std::setprecision(2);
                if (printSize < 1024) {
                    std::cout << entry.path().string() << " 的大小是: " << printSize << "MB" << std::endl;
                } else {
                    std::cout << entry.path().string() << " 的大小是: " << (printSize /= 1024) << "GB" << std::endl;
                }
            }
        }
    }
    uintmax_t sizeBytes = this->folderSize; // 保持原始大小，单位为字节
    std::vector<std::string> units = {"B", "KB", "MB", "G", "T"}; // 单位数组
    int unitIndex = 0; // 用于索引单位的数组
    double displaySize = static_cast<double>(sizeBytes); // 用于显示的大小

    // 循环通过1024除以大小，直到找到合适的单位
    while (displaySize >= 1024 && unitIndex < units.size() - 1) {
        displaySize /= 1024;
        ++unitIndex;
    }

    // 根据单位决定是否显示小数位
    std::streamsize precision = (unitIndex > 1) ? 2 : 0;
    std::cout << std::fixed << std::setprecision(precision);

    if (isPrint) {
        // 输出文件夹的大小，用适当的单位
        std::cout << "文件夹的大小是: " << displaySize << units[unitIndex] << std::endl;
    }

    // 存储格式化后的文件夹大小信息
    std::ostringstream storeStream;
    storeStream << std::fixed << std::setprecision(precision) << displaySize << units[unitIndex];
    folder_info[3] = storeStream.str();

}

void MyTools::multithread_get_folder_size(const std::string &folderPath, bool isPrint) {
    folderSize = 0;
    int count = 0;
    std::string path;
    if(linuxMode){
        path = windows_path_to_linux_path(folderPath);
    }
    for (const auto &entry: fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            count++;
        }
    }
    if (count >= 4) {
        std::cout << "启用多线程计算文件夹大小" << std::endl;
    }
    std::vector<std::thread> threads;
    if (count >= 4) {
        for (const auto &entry: fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                threads.emplace_back(&MyTools::get_folder_size, this, entry.path().string(), false, false, true);
            } else {
                get_file_size(entry.path().string());
            }
        }
    } else {
        get_folder_size(path, false);
    }

    for (auto &thread: threads) {
        thread.join();
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "文件夹的大小是: " << folder_info[3] << std::endl;

}

void MyTools::get_folder_info(const std::string &folderPath) {
    std::string path;
    if(linuxMode){
        path = windows_path_to_linux_path(folderPath);
    }
    std::cout << "文件夹的路径是: " << path << std::endl;
    std::cout << "文件夹的名称是: " << fs::path(path).filename() << std::endl;
    count_imgs_videos_and_audio(path);
    get_folder_size(path);

    std::string textToCopy;
    for (const auto &info: folder_info) {
        if (!info.empty()) {
            textToCopy += info + " ";
        }
    }
    if (!textToCopy.empty()) {
        textToCopy.pop_back();
    }
    textToCopy = "[" + textToCopy + "]";

    std::cout << copy_to_clipboard(textToCopy) << std::endl;

}

void MyTools::change_files_extension(const std::string &folderPath, std::string newExtension, std::string oldExtension,
                                     bool isChange,
                                     bool option) {
    if (option) {
        for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string fileName = entry.path().filename().string();
                std::string fileExtension = fs::path(fileName).extension().string();
                fileExtension.erase(0, 1);
                if (fileExtension == oldExtension) {
                    // 只有当文件的扩展名等于oldExtension时才执行以下操作。
                    std::string oldFileName = entry.path().string();
                    std::string newFileName = oldFileName;
                    newFileName.replace(newFileName.end() - oldExtension.size(), newFileName.end(), newExtension);

                    if (isChange) {
                        fs::rename(oldFileName, newFileName);
                    }
                    std::cout << oldFileName << " -> " << newFileName << std::endl;
                }
            }
        }
    } else {
        for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string fileName = entry.path().filename().string();
                std::string fileExtension = fs::path(fileName).extension().string();
                fileExtension.erase(0, 1);
                std::cout << fileExtension << std::endl;
                std::string oldFileName = entry.path().string();
                std::string newFileName = oldFileName;
                newFileName.replace(newFileName.end() - oldExtension.size(), newFileName.end(), newExtension);
                if (isChange) {
                    fs::rename(oldFileName, newFileName);
                }
                std::cout << oldFileName << " -> " << newFileName << std::endl;
            }
        }
    }
}

void MyTools::move_files_to_main_folder(const std::string &folderPath, bool isMove) {
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            if (isMove) {
                try {
                    fs::rename(entry.path(), folderPath / entry.path().filename());
                    std::cout << entry.path().filename() << "成功移动到" << folderPath << std::endl;
                } catch (const std::exception &ex) {
                    std::cerr << "文件移动失败：" << ex.what() << std::endl;
                }
            }
        }
    }
}










