//#include "RedisTool.h"
//
//using namespace std;
//
//void RedisTool::insertFiles(const string &folderPath) {
//    std::string path = linuxMode ? windows_path_to_linux_path(folderPath) : folderPath;
//    std::threadpool pool(16); // 创建线程池，假设有 4 个工作线程
//    for (const auto &entry: std::filesystem::recursive_directory_iterator(path)) {
//        if (entry.is_regular_file()) {
//            FileInfo data;
//            data.filePath = linuxMode ? linux_path_to_windows_path(entry.path().string())
//                                      : entry.path().string();
//            data.fileName = entry.path().filename().string();
//            data.suffix = entry.path().extension().string();
//            data.fileSize = std::to_string(entry.file_size() / 1024);
//            insertData(data, database);
//            std::cout << "成功插入数据: " << data.filePath << std::endl;
//        }
//    }
//}
//
//void RedisTool::setDatabase(int database, bool reWrite) {
//    if (redis.context == nullptr) {
//        std::cerr << "Redis context is not initialized." << std::endl;
//        return;
//    }
//    // 切换到指定的数据库
//    if (!redis.execute("SELECT " + to_string(database))) {
//        std::cerr << "Failed to select database " << database << std::endl;
//        return;
//    }
//
//    // 如果需要重写，清空数据库
//    if (reWrite) {
//        redis.execute("FLUSHDB");
//    }
//}
//
//void RedisTool::insertFile(FileInfo &data, int database) {
//
//}
