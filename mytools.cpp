#include "mytools.h"
// 判断是否为图像文件
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
// 判断是否为视频文件
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
// 判断是否为音频文件
bool mytools::isAudioFile(const std::string &filename) {
    // 根据文件扩展名判断是否为视频文件
    std::vector<std::string> audioExtensions = {".mp3", ".wav", ".flac", ".ape", ".aac"};
    for (const std::string &extension: audioExtensions) {
        if (filename.find(extension) != std::string::npos) {
            return true;
        }
    }
    return false;
}

string mytools::translate(string text, string from, string to,bool isPrint) {
    Py_Initialize();

    PyObject *sysPath = PySys_GetObject("path");
    PyList_Append(sysPath, PyUnicode_DecodeFSDefault("E:\\MyCodeProject\\CLionProjects\\cpp-tools"));

    PyObject *pModule = PyImport_ImportModule("translate");

    if (pModule != NULL) {
        // 获取模块中的函数
        PyObject *pDict = PyModule_GetDict(pModule);
        PyObject *pFunc = PyDict_GetItemString(pDict, "translate");

        if (PyCallable_Check(pFunc)) {
            // 调用Python函数
            PyObject *pArgs = PyTuple_Pack(3, PyUnicode_DecodeFSDefault(text.c_str()),
                                           PyUnicode_DecodeFSDefault(from.c_str()),
                                           PyUnicode_DecodeFSDefault(to.c_str()));
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                // 处理Python函数的返回值
                if (PyUnicode_Check(pValue)) {
                    const char *result = PyUnicode_AsUTF8(pValue);
                    if (isPrint)
                        cout << result << endl;
                    return result;
                } else {
                    std::cerr << "函数返回的不是字符串。" << std::endl;
                }
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            PyErr_Print();
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    // 结束Python解释器
    Py_Finalize();
}

// 获取文件的大小
void mytools::get_file_size(string path) {
    error_code ec{};
    auto size = std::filesystem::file_size(path, ec);
    if (ec == error_code{}){
        folderSize += size;
    }
    else{
        cout << "Error accessing file '" << path
        << "' message: " << ec.message() << endl;
    }

}

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

// 统计一个文件夹下的图片和视频的数量
void mytools::count_imgs_videos_and_audio(const string &folderPath, string option) {
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
                std::ofstream outputFile(fileToCreate);
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
                std::ofstream outputFile(fileToCreate);
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
void mytools::get_folder_size(const std::string &folderPath) {
    for (const auto &entry: fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            get_file_size(entry.path().string());
        }
    }
    uintmax_t Size = this->folderSize / 1024 / 1024;
    bool isMB = true;
    if (Size < 1024) {
        cout << "文件夹的大小是: " << Size << "MB" << endl;
    } else {
        cout << "文件夹的大小是: " << (Size /= 1024) << "GB" << endl;
        isMB = false;
    }
    folder_info[3] = (to_string(Size) + (isMB ? "MB" : "GB"));
}

// 获取文件夹的信息
void mytools::get_folder_info(const std::string &folderPath) {
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


