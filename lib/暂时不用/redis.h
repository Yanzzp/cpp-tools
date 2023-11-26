//#ifndef CPP_TOOLS_REDIS_H
//#define CPP_TOOLS_REDIS_H
//
//#include <hiredis/hiredis.h>
//#include <stdexcept>
//#include <iostream>
//
//struct FileInfo {
//    std::string filePath;
//    std::string fileName;
//    std::string suffix;
//    std::string fileSize;
//};
//
//class Redis {
//private:
//
//
//    void handleReply(const redisReply *reply);
//
//    void selectDatabase(int database);
//
//    bool executeCommand(const char* format, ...);
//protected:
//    redisReply *reply;
//public:
//    Redis() {
//        context = nullptr;
//        reply = nullptr;
//    }
//
//    Redis(const std::string &host, int port, int database = 0) {
//        context = nullptr;
//        reply = nullptr;
//        connect(host, port, database);
//    }
//
//    ~Redis() {
//        if (context != nullptr) {
//            redisFree(context);
//        }
//        if (reply != nullptr) {
//            freeReplyObject(reply);
//        }
//    }
//
//    bool connect(const std::string &host, int port, int database = 0);
//
//    bool execute(const std::string &query);
//
//    void insertData(FileInfo &data, int database = 0);
////
////    void createTable(const std::string &TableName, bool replace = false);
//
//    redisContext *context;
//};
//
//
//#endif //CPP_TOOLS_REDIS_H
