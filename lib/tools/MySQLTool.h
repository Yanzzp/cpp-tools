#ifndef CPP_TOOLS_MYSQLTOOL_H
#define CPP_TOOLS_MYSQLTOOL_H

#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include "tools.h"


class MySQLTool : public Tools {
private:
    std::unique_ptr<sql::Connection> connection;
public:
    bool connect(const std::string &host, const std::string &user,
                 const std::string &password, const std::string &database);

    // 执行 SQL 语句
    void execute(const std::string &query);

    void createTable(const std::string &TableName = "FileName", bool replace = false);

    static void
    insertData(std::unique_ptr<sql::Statement> &stmt, std::string table, std::string filePath, std::string fileName,
               std::string suffix, std::string fileSize);

    static void
    insertData1(std::unique_ptr<sql::Statement> &stmt, const std::string &table, const std::string &filePath,
                const std::string &fileName, const std::string &suffix, const std::string &fileSize);

    void insertFiles(const std::string &folderPath, std::string table, bool isRoot = true);

    void insertFiles1(const std::string &folderPath, std::string table);

    bool searchFile(const std::string &table, const std::string &filePath);
};


#endif
