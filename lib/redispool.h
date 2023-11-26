//
// Created by 11057 on 2023/11/26.
//

#ifndef CPP_TOOLS_REDISPOOL_H
#define CPP_TOOLS_REDISPOOL_H

#include <iostream>
#include <thread>
#include <hiredis/hiredis.h>
#include <mutex>
#include <queue>

const char* redisHost = "127.0.0.1";
const int redisPort = 6379;
class RedisPool {
public:
    RedisPool(int size) {
        for (int i = 0; i < size; ++i) {
            redisContext *context = redisConnect(redisHost, redisPort);
            if (context != nullptr && context->err == 0) {
                connections.push(context);
            } else {
                std::cerr << "Error connecting to Redis: "
                          << (context ? context->errstr : "Can't allocate redis context") << std::endl;
            }
        }
    }

    ~RedisPool() {
        while (!connections.empty()) {
            redisContext *context = connections.front();
            connections.pop();
            redisFree(context);
        }
    }

    redisContext *getConnection() {
        std::unique_lock<std::mutex> lock(mutex);
        if (connections.empty()) {
            return nullptr;
        }
        redisContext *context = connections.front();
        connections.pop();
        return context;
    }

    void releaseConnection(redisContext *context) {
        std::unique_lock<std::mutex> lock(mutex);
        connections.push(context);
    }

private:
    std::queue<redisContext *> connections;
    std::mutex mutex;
};

#endif //CPP_TOOLS_REDISPOOL_H


