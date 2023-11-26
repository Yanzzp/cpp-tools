////
//// Created by 11057 on 2023/11/26.
////
//
//#ifndef CPP_TOOLS_REDISTOOL_H
//#define CPP_TOOLS_REDISTOOL_H
//
//#include "../tools/tools.h"
//#include "redis.h"
//
//class RedisTool : public Tools {
//private:
//    int database = 0;
//    Redis redis;
//
//public:
//    RedisTool() = default;
//
//    RedisTool(const std::string &host, int port, int database = 0) {
//        redis.connect(host, port, database);
//    }
//
//    void setDatabase(int database,bool reWrite = true);
//
//    void insertData(FileInfo &data,int database = 0) {
//        redis.insertData(data, database);
//    }
//
//    void insertFiles(const std::string &folderPath);
//
//    void insertFile(FileInfo &data,int database = 0);
//};
//
//
//#endif //CPP_TOOLS_REDISTOOL_H
