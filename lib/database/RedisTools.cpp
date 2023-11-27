//
// Created by 11057 on 2023/11/26.
//

#include <sstream>
#include <cstring>
#include "RedisTools.h"

using namespace std;


RedisTools::RedisTools(int threadpool_size, int redispool_size) {
    RedisTools::thread_size = threadpool_size;
    RedisTools::redis_size = redispool_size;
}

void insertFile(RedisPool &redisPool, FileInfo file) {
    // 获取 Redis 连接
    redisContext *context = redisPool.getConnection();
    if (context == nullptr) {
        std::cerr << "Failed to get a Redis connection" << std::endl;
        return;
    }

    // 使用 HMSET 一次性设置多个字段
    redisReply *reply = (redisReply *) redisCommand(context,
                                                    "HMSET %s fileName %s suffix %s fileSize %s",
                                                    file.filePath.c_str(),
                                                    file.fileName.c_str(),
                                                    file.suffix.c_str(),
                                                    file.fileSize.c_str());
    if (reply == nullptr || reply->type != REDIS_REPLY_STATUS || strcmp(reply->str, "OK") != 0) {
        std::cerr << "Failed to write file info to Redis for key " << file.filePath << std::endl;
        // 释放连接和回复对象
        redisPool.releaseConnection(context);
        freeReplyObject(reply);
        return;
    }
    std::cout << "File info written to Redis for key " << file.filePath << std::endl;

    // 释放回复对象和连接
    freeReplyObject(reply);
    redisPool.releaseConnection(context);
}


void readFile(RedisPool &redisPool, string filePath) {
    FileInfo file;

    // 获取 Redis 连接
    redisContext *context = redisPool.getConnection();
    if (context == nullptr) {
        std::cerr << "Failed to get a Redis connection" << std::endl;
        return;
    }

    // 一次性读取 fileName, suffix, fileSize
    redisReply *reply = (redisReply *) redisCommand(context, "HMGET %s fileName suffix fileSize", filePath.c_str());
    if (reply && reply->type == REDIS_REPLY_ARRAY) {
        // 设置 fileName
        if (reply->element[0]->type == REDIS_REPLY_STRING) {
            file.fileName = reply->element[0]->str;
        } else {
            std::cerr << "Failed to read fileName from Redis for key " << filePath << std::endl;
        }

        // 设置 suffix
        if (reply->element[1]->type == REDIS_REPLY_STRING) {
            file.suffix = reply->element[1]->str;
        } else {
            std::cerr << "Failed to read suffix from Redis for key " << filePath << std::endl;
        }

        // 设置 fileSize
        if (reply->element[2]->type == REDIS_REPLY_STRING) {
            file.fileSize = reply->element[2]->str;
        } else {
            std::cerr << "Failed to read fileSize from Redis for key " << filePath << std::endl;
        }
    } else {
        std::cerr << "Failed to read file info from Redis for key " << filePath << std::endl;
    }

    freeReplyObject(reply); // 释放回复对象

    // 释放连接
    redisPool.releaseConnection(context);

    std::cout << "File info read from Redis for key " << filePath << std::endl;
}


void RedisTools::insertFolder(string folderPath) {
    std::string path = linuxMode ? windows_path_to_linux_path(folderPath) : folderPath;
    std::vector<std::future<void>> futures;

    for (const auto &entry: std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            FileInfo data;
            data.filePath = linuxMode ? linux_path_to_windows_path(entry.path().string())
                                      : entry.path().string();
            data.fileName = entry.path().filename().string();
            data.suffix = entry.path().extension().string();
            data.fileSize = std::to_string(entry.file_size() / 1024);
            futures.push_back(threadPool.commit(insertFile, std::ref(redisPool), data));
            std::cout << "成功插入数据: " << data.filePath << std::endl;
        }
    }
    // 等待所有任务完成
    for (auto &fut: futures) {
        fut.get();
    }
}



FileInfo RedisTools::readFolder(string filePath) {
    std::vector<std::future<void>> futures;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 200; ++i) {
        string filePath = "filePath" + std::to_string(i);
        futures.push_back(threadPool.commit(readFile, std::ref(redisPool), filePath));
    }
    // 等待所有任务完成
    for (auto &fut: futures) {
        fut.get();
    }
}

FileInfo RedisTools::serchFile(const std::string& filePath) {
    FileInfo file;
    file.filePath = filePath;

    // 获取 Redis 连接
    redisContext* context = redisPool.getConnection();
    if (context == nullptr) {
        std::cerr << "Failed to get a Redis connection" << std::endl;
        return file;
    }

    // 使用 HGETALL 命令一次性获取所有字段
    redisReply* reply = (redisReply*)redisCommand(context, "HGETALL %s", filePath.c_str());
    if (reply != nullptr && reply->type == REDIS_REPLY_ARRAY) {
        for (size_t i = 0; i < reply->elements; i += 2) {
            std::string field(reply->element[i]->str);
            std::string value(reply->element[i + 1]->str);

            if (field == "fileName") {
                file.fileName = value;
            } else if (field == "suffix") {
                file.suffix = value;
            } else if (field == "fileSize") {
                file.fileSize = value;
            }
        }
    } else {
        std::cerr << "Failed to read file info from Redis for key " << filePath << std::endl;
    }

    freeReplyObject(reply); // 释放回复对象
    redisPool.releaseConnection(context); // 释放连接

    return file;
}

