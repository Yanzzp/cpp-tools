//#include "lib/redispool.h"
//#include "lib/threadpools.h"
//#include "lib/multithread.h"
//#include <chrono>
//
//using namespace std;
//
//
//// 假设这是一个从Redis读取数据的函数
//void readFromRedis(RedisPool &redisPool, const std::string &key) {
//    redisContext *context = redisPool.getConnection();
//    if (context == nullptr) {
//        std::cerr << "Failed to get a Redis connection" << std::endl;
//        return;
//    }
//
//    redisReply *reply = (redisReply *) redisCommand(context, "GET %s", key.c_str());
//    if (reply != nullptr && reply->type == REDIS_REPLY_STRING) {
//        std::cout << "Value for " << key << ": " << reply->str << std::endl;
//    } else {
//        std::cerr << "Failed to get data from Redis for key " << key << std::endl;
//    }
//
//    redisPool.releaseConnection(context);
//    freeReplyObject(reply);
//}
//
//// 假设这是一个向Redis写入数据的函数
//void writeToRedis(RedisPool &redisPool, const std::string &key, const std::string &value) {
//    redisContext *context = redisPool.getConnection();
//    if (context == nullptr) {
//        std::cerr << "Failed to get a Redis connection" << std::endl;
//        return;
//    }
//
//    redisReply *reply = (redisReply *) redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
//    if (reply != nullptr && reply->type == REDIS_REPLY_STATUS && std::string(reply->str) == "OK") {
//        std::cout << "Data written to Redis for key " << key << std::endl;
//    } else {
//        std::cerr << "Failed to write data to Redis for key " << key << std::endl;
//    }
//
//    redisPool.releaseConnection(context);
//    freeReplyObject(reply);
//}
//
//// 向Redis写入数据的函数
//void writeToRedis1(RedisPool &redisPool, const std::string &key, const std::string &value) {
//    redisContext *context = redisPool.getConnection();
//    if (context == nullptr) {
//        std::cerr << "Failed to get a Redis connection" << std::endl;
//        return;
//    }
//
//    redisReply *reply = (redisReply *) redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
//    if (reply != nullptr && reply->type == REDIS_REPLY_STATUS && std::string(reply->str) == "OK") {
//        std::cout << "Data written to Redis for key " << key << std::endl;
//    } else {
//        std::cerr << "Failed to write data to Redis for key " << key << std::endl;
//    }
//
//    redisPool.releaseConnection(context);
//    freeReplyObject(reply);
//}
//
//// 从Redis读取数据的函数
//void readFromRedis1(RedisPool &redisPool, const std::string &key) {
//    redisContext *context = redisPool.getConnection();
//    if (context == nullptr) {
//        std::cerr << "Failed to get a Redis connection" << std::endl;
//        return;
//    }
//
//    redisReply *reply = (redisReply *) redisCommand(context, "GET %s", key.c_str());
//    if (reply != nullptr && reply->type == REDIS_REPLY_STRING) {
//        std::cout << "Value for " << key << ": " << reply->str << std::endl;
//    } else {
//        std::cerr << "Failed to get data from Redis for key " << key << std::endl;
//    }
//
//    redisPool.releaseConnection(context);
//    freeReplyObject(reply);
//}
//
//int main() {
//    // 初始化Redis连接池
//    RedisPool redisPool(16);  // 假设连接池大小为10
//
//    // 初始化线程池
//    std::threadpool threadPool(8);  // 假设线程池大小为4
//
//    std::vector<std::future<void>> futures;
//
//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 10000; ++i) {
//        std::string key = "key" + std::to_string(i);
//        std::string value = "value" + std::to_string(i);
//        futures.push_back(threadPool.commit(writeToRedis, std::ref(redisPool), key, value));
//    }
//
//    for (int i = 0; i < 10000; ++i) {
//        std::string key = "key" + std::to_string(i);
//        futures.push_back(threadPool.commit(readFromRedis, std::ref(redisPool), key));
//    }
//
//    // 等待所有任务完成
//    for (auto &fut : futures) {
//        fut.get();
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//
//    std::cout << "多线程运行时间 " << duration.count() << " 毫秒" << std::endl;
//
//
////    for (int i = 0; i < 10000; ++i) {
////        std::string key = "key" + std::to_string(i);
////        std::string value = "value" + std::to_string(i);
////        writeToRedis1(redisPool, key, value);
////    }
////    for (int i = 0; i < 10000; ++i) {
////        std::string key = "key" + std::to_string(i);
////        readFromRedis1(redisPool, key);
////    }
////
////    cout << "no threadpool" << endl;
////
////    // 演示并发写入
////    end = std::chrono::high_resolution_clock::now();
////
////    // 计算持续时间
////    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
////
////    // 输出结果
////    std::cout << "没有开多线程运行时间 " << duration.count() << std::endl;
//
//
//    std::this_thread::sleep_for(std::chrono::seconds(10));
//    // 等待所有任务完成
//    // 这里需要一个机制来确保所有任务都完成了
//    // 例如使用std::future或其他同步方法
//
//    return 0;
//}