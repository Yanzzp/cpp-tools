//
// Created by 11057 on 2023/11/24.
//

#include "MySQLTool.h"

using namespace std;
namespace fs = std::filesystem;

void MySQLTool::createTable(const std::string &TableName, bool replace) {
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        if (replace) {
            stmt->execute("DROP TABLE IF EXISTS " + TableName);
            cout << "已经存在表,清空表并重新输入" << endl;
        }
        stmt->execute("CREATE TABLE IF NOT EXISTS " + TableName + " ("
                                                                  "id INT AUTO_INCREMENT PRIMARY KEY,\n"
                                                                  "filePath VARCHAR(255),\n"
                                                                  "fileName VARCHAR(128),\n"
                                                                  "suffix VARCHAR(16),\n"
                                                                  "fileSize BIGINT\n"
                                                                  ")ENGINE=InnoDB DEFAULT CHARSET=utf8;");
        stmt->execute("CREATE INDEX idx_filePath ON " + TableName + " (filePath);");
    } catch (const sql::SQLException &e) {
        std::cerr << "创建表失败: " << e.what() << std::endl;
        exit(1);
    }

}

bool MySQLTool::connect(const std::string &host, const std::string &user, const std::string &password,
                        const std::string &database) {
    try {
        std::string connection_string = host;
        if (host.substr(0, 6) != "tcp://") {
            connection_string = "tcp://" + host;
        }
        size_t port_pos = connection_string.find(':', 6); // 从 "tcp://" 后开始查找
        if (port_pos == std::string::npos) {
            // 如果没有找到端口号，则添加默认端口 "3306"
            connection_string += ":3306";
        }

        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        connection.reset(driver->connect(connection_string, user, password));
        connection->setSchema(database);
        cout << "成功连接到  IP:" << host << " 数据库:" << database << endl;
    } catch (const sql::SQLException &e) {
        std::cerr << "连接失败: " << e.what() << std::endl;
        exit(1);
    }
}

void MySQLTool::execute(const std::string &query) {
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        stmt->execute(query);
    } catch (const sql::SQLException &e) {
        std::cerr << "执行失败: " << e.what() << std::endl;
        exit(1);
    }
}

void MySQLTool::insertData(string table, string filePath, string fileName, string suffix,
                           std::string fileSize) {
    try {
        std::replace(filePath.begin(), filePath.end(), '\\', '/');
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        stmt->execute(
                "INSERT INTO " + table + " (filePath, fileName, suffix, fileSize) VALUES ('" + filePath + "', '" +
                fileName +
                "', '" + suffix + "', '" + fileSize + "')");
    } catch (const sql::SQLException &e) {
        std::cerr << "插入数据失败: " << e.what() << std::endl;
        exit(1);
    }
}

void MySQLTool::insertFiles(const string &folderPath, string table, bool isRoot) {
    string path = linuxMode ? windows_path_to_linux_path(folderPath) : folderPath;
    std::vector<std::thread> threads; // 用于存储线程的容器

    for (const auto &entry: fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            // 在根目录下为每个文件创建一个线程
            if (isRoot) {
                threads.emplace_back([&, entry]() {
                    string filePath = linuxMode ? linux_path_to_windows_path(entry.path().string())
                                                : entry.path().string();
                    string fileName = entry.path().filename().string();
                    string suffix = entry.path().extension().string();
                    string fileSize = to_string(entry.file_size());
                    insertData(table, filePath, fileName, suffix, fileSize);
                    cout << "成功插入数据: " << filePath << endl;
                });
            } else {
                // 在子目录中，仅直接插入数据，不创建新线程
                string filePath = linuxMode ? linux_path_to_windows_path(entry.path().string()) : entry.path().string();
                string fileName = entry.path().filename().string();
                string suffix = entry.path().extension().string();
                string fileSize = to_string(entry.file_size());
                insertData(table, filePath, fileName, suffix, fileSize);
                cout << "成功插入数据: " << filePath << endl;
            }
        } else if (entry.is_directory()) {
            // 递归调用，但指明不是根目录
            insertFiles(entry.path().string(), table, false);
        }
    }

    // 等待所有线程完成
    for (auto &th: threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

bool MySQLTool::searchFile(const string &table, const string &filePath) {
    bool found = false;  // 用于指示是否找到文件
    try {
        string path = filePath;
        replace(path.begin(), path.end(), '\\', '/');
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res;

        res.reset(stmt->executeQuery(
                "SELECT * FROM " + table + " WHERE filePath = '" + path + "'"));

        while (res->next()) {
            found = true;  // 找到至少一个匹配项
            std::cout << "fileName: " << res->getString("fileName")
                      << ", suffix: " << res->getString("suffix")
                      << ", fileSize: " << res->getString("fileSize") << std::endl;
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "搜索文件失败: " << e.what() << std::endl;
        exit(-1);  // 或者可以改为 throw，根据您的错误处理策略
    }
    return found;  // 返回是否找到匹配文件
}



