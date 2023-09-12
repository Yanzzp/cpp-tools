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

void mytools::countFiles(const string &folderPath,int depth) {

    try {
        for (const auto &entry: fs::directory_iterator(folderPath)) {
            if (entry.is_directory()) {
                countFiles(entry.path().string(), depth + 1); // 递归调用自身遍历子文件夹
            } else if (entry.is_regular_file()) {
                if (isImageFile(entry.path().filename().string())) {
                    imageCount++;
                } else if (isVideoFile(entry.path().filename().string())) {
                    videoCount++;
                }
            }
        }
    } catch (const std::exception &ex) {
        std::cerr << "发生错误: " << ex.what() << std::endl;
    }
}

int mytools::printFiles(const std::string &folderPath, int depth) {
    countFiles(folderPath, depth);
    cout << "图片的数量是: " << imageCount << endl;
    cout << "视频的数量是: " << videoCount << endl;

//    string filename = "E:\\资源\\4女神大合集JVID猫系少女+淇淇+夏暮光+姗姗就打奥特曼合集\\example.txt"; // 指定要创建的文件名
    string filename = folderPath + "\\图片数量("+ to_string(imageCount)+") 视频数量("+ to_string(videoCount)+").txt"; // 指定要创建的文件名
    cout << filename << endl;

    try {
        fs::path fileToCreate(filename);
        if (!fs::exists(fileToCreate)) {
            // 文件不存在，创建文件并打开以进行写入
            std::ofstream outputFile(fileToCreate);
            // 检查文件是否成功打开
            if (outputFile.is_open()) {
                // 写入数据到文件
                outputFile << "图片的数量是: " << imageCount << "\n";
                outputFile << "视频的数量是: " << videoCount << "\n";
                // 关闭文件流
                outputFile.close();
                std::cout << "文件 " << filename << " 创建并写入成功。\n";
            } else {
                std::cerr << "无法打开文件 " << filename << std::endl;
            }
        } else {
            std::cerr << "文件 " << filename << " 已经存在。\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "发生错误: " << ex.what() << std::endl;
    }
}