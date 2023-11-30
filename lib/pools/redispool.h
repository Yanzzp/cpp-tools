#pragma once
#ifndef CPP_TOOLS_REDISPOOL_H
#define CPP_TOOLS_REDISPOOL_H


#include "pools.h"

class RedisPool {
private:
    const char *redisHost = "127.0.0.1";
    const int redisPort = 6379;
    int size = 10;
    std::queue<redisContext *> connections;
    std::mutex mutex;
    int selectedDatabase = 0;
public:
    RedisPool(int size, int initialDatabase = 0) : size(size), selectedDatabase(initialDatabase) {
        for (int i = 0; i < size; ++i) {
            redisContext *context = redisConnect(redisHost, redisPort);
            if (context != nullptr && context->err == 0) {
                connections.push(context);
                // 选择初始数据库
                if (initialDatabase != 0) {
                    redisCommand(context, "SELECT %d", initialDatabase);
                }
            } else {
                std::cerr << "Error connecting to Redis: "
                          << (context ? context->errstr : "Can't allocate redis context") << std::endl;
            }
        }
    }

    RedisPool() = default;

    RedisPool(const char *redisHost, int redisPort, int size, int initialDatabase = 0)
            : redisHost(redisHost), redisPort(redisPort), size(size), selectedDatabase(initialDatabase) {
        for (int i = 0; i < size; ++i) {
            redisContext *context = redisConnect(redisHost, redisPort);
            if (context != nullptr && context->err == 0) {
                connections.push(context);
                // 选择初始数据库
                if (initialDatabase != 0) {
                    redisCommand(context, "SELECT %d", initialDatabase);
                }
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

    void setSize(int newSize) {
        std::unique_lock<std::mutex> lock(mutex);
        while (connections.size() < newSize) {
            redisContext *context = redisConnect(redisHost, redisPort);
            if (context != nullptr && context->err == 0) {
                connections.push(context);
            } else {
                std::cerr << "Error connecting to Redis: "
                          << (context ? context->errstr : "Can't allocate redis context") << std::endl;
            }
        }
        while (connections.size() > newSize) {
            redisContext *context = connections.front();
            connections.pop();
            redisFree(context);
        }
        size = newSize;
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

    void selectDatabase(int database) {
        selectedDatabase = database;
        std::unique_lock<std::mutex> lock(mutex);
        while (!connections.empty()) {
            redisContext *context = connections.front();
            connections.pop();
            // 选择指定的数据库
            redisCommand(context, "SELECT %d", selectedDatabase);
        }
    }

};

#endif //CPP_TOOLS_REDISPOOL_H


