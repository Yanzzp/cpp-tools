////
//// Created by 11057 on 2023/11/26.
////
//
//#include "redis.h"
//
//using namespace std;
//
//bool Redis::connect(const std::string &host, int port, int database) {
//    try {
//        // 尝试连接到 Redis 服务器
//        context = redisConnect(host.c_str(), port);
//        if (context == nullptr || context->err) {
//            throw std::runtime_error(
//                    "Connection error: " + std::string(context ? context->errstr : "can't allocate redis context"));
//        }
//        // 选择数据库
//        selectDatabase(database);
//        cout << "成功连接到  IP:" << host << " 数据库:" << database << endl;
//        return true;
//    } catch (const std::exception &e) {
//        // 处理连接错误
//        if (context != nullptr) {
//            redisFree(context);
//            context = nullptr;
//        }
//        printf("Redis connection error: %s\n", e.what());
//        return false;
//    }
//}
//
//
//bool Redis::execute(const std::string &query) {
//    // 确保已经建立了连接
//    if (context == nullptr) {
//        std::cerr << "Redis context is not initialized." << std::endl;
//        return false;
//    }
//
//    // 发送命令
//    redisReply *reply = (redisReply *) redisCommand(context, query.c_str());
//    if (reply == nullptr) {
//        std::cerr << "Redis command failed: " << context->errstr << std::endl;
//        return false;
//    }
//
//
//    freeReplyObject(reply);
//    return true;
//}
//
//void Redis::selectDatabase(int database) {
//    redisReply *reply = (redisReply *) redisCommand(context, "SELECT %d", database);
//    if (reply == nullptr || context->err) {
//        throw std::runtime_error("Select database error: " + std::string(reply ? reply->str : context->errstr));
//    }
//    freeReplyObject(reply);
//}
//
//
//
//void Redis::insertData(FileInfo &data, int database) {
//    if (context == nullptr) {
//        std::cerr << "Redis context is not initialized." << std::endl;
//        return;
//    }
//
//    // 选择数据库
//    if (!executeCommand("SELECT %d", database)) {
//        std::cerr << "Failed to select database " << database << std::endl;
//        return;
//    }
//
//    bool success = executeCommand("HSET %s fileName %s", data.filePath.c_str(), data.fileName.c_str()) &&
//                   executeCommand("HSET %s suffix %s", data.filePath.c_str(), data.suffix.c_str()) &&
//                   executeCommand("HSET %s fileSize %s", data.filePath.c_str(), data.fileSize.c_str());
//
//    if (!success) {
//        std::cerr << data.filePath << " 插入失败" << std::endl;
//        return;
//    }
//
//    // std::cout << data.filePath << " 插入成功" << std::endl;
//}
//
//
//bool Redis::executeCommand(const char *format, ...) {
//    if (context == nullptr) {
//        std::cerr << "Redis context is not initialized." << std::endl;
//        return false;
//    }
//
//    va_list args;
//    va_start(args, format);
//    redisReply *reply = (redisReply *) redisvCommand(context, format, args);
//    va_end(args);
//
//    if (reply == nullptr) {
//        std::cerr << "Redis command failed." << std::endl;
//        return false;
//    }
//
//    freeReplyObject(reply);
//    return true;
//}
//
//
