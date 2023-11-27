#ifndef CPP_TOOLS_REDISTOOLS_H
#define CPP_TOOLS_REDISTOOLS_H

#include "../tools/tools.h"
#include "../pools/threadpools.h"
#include "../pools/redispool.h"

struct FileInfo {
    std::string filePath;
    std::string fileName;
    std::string suffix;
    std::string fileSize;
};
class RedisTools : public Tools{
private:
    int thread_size;
    int redis_size;
    RedisPool redisPool{16};
    std::threadpool threadPool{16};
public:
    RedisTools() = default;
    RedisTools(int thread_size, int redis_size);

//    void insertFile(FileInfo file);

    void insertFolder(std::string folderPath);

    FileInfo readFolder(std::string filePath);

    FileInfo serchFile(const std::string& filePath);
};


#endif //CPP_TOOLS_REDISTOOLS_H
