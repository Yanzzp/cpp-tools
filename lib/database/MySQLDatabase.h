#ifndef CPP_TOOLS_MYSQLDATABASE_H
#define CPP_TOOLS_MYSQLDATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>


class MySQLDatabase {
private:
    std::unique_ptr<sql::Connection> connection;
public:
    bool connect(const std::string &host, const std::string &user,
                 const std::string &password, const std::string &database) ;

    // 执行 SQL 语句
    void execute(const std::string &query) ;

    void createTable(const std::string &TableName, bool replace = false);

    // 新增插入数据函数
    void insertData(const std::string &query) {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        stmt->executeUpdate(query);
    }

    // 新增查找数据函数
    std::unique_ptr<sql::ResultSet> findData(const std::string &query) {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
        return res;
    }
};


#endif //CPP_TOOLS_MYSQLDATABASE_H
