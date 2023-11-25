#ifndef CPP_TOOLS_MYSQLTOOL_H
#define CPP_TOOLS_MYSQLTOOL_H

#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include "tools.h"
#include "../database/Database.h"

class MySQLTool : public Database, public Tools {
private:
    std::unique_ptr<sql::Connection> connection;
public:
    bool connect(const std::string &host, const std::string &user,
                 const std::string &password, const std::string &database) override;

    // 执行 SQL 语句
    void execute(const std::string &query) override;

    void createTable(const std::string &TableName = "FileName", bool replace = false);

    void
    insertData(std::string table, std::string filePath, std::string fileName, std::string suffix, std::string fileSize);

    void insertFiles(const std::string &folderPath, std::string table, bool isRoot = true);

    bool searchFile(const std::string& table,const std::string &filePath);
};


#endif
