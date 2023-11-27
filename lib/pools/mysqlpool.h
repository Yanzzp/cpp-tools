#pragma once
#ifndef CPP_TOOLS_MYSQLPOOL_H
#define CPP_TOOLS_MYSQLPOOL_H


#include "pools.h"


class MySQLConnection {
    MYSQL *conn;
public:
    MySQLConnection(const std::string &host, int port, const std::string &user, const std::string &password,
                    const std::string &database) {
        conn = mysql_init(NULL);
        if (conn == NULL) {
            throw std::runtime_error("MySQL initialization failed");
        }

        if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(),
                                database.c_str(), port, NULL, 0)) {
            std::string error_msg = "MySQL connection failed: ";
            error_msg += mysql_error(conn);
            mysql_close(conn);
            throw std::runtime_error(error_msg);
        }

        std::cout << "MySQLConnection created." << std::endl;
    }

    ~MySQLConnection() {
        if (conn != NULL) {
            mysql_close(conn);
        }
        std::cout << "MySQLConnection destroyed." << std::endl;
    }

    // 示例方法
    void query(const std::string &sql) {

    }

};

class MySQLPool {
    std::string _host;
    int _port;
    std::string _user;
    std::string _password;
    std::string _database;
    size_t _poolSize;
    std::queue<std::shared_ptr<MySQLConnection>> _connections;
    std::mutex _mutex;
    std::condition_variable _condition;

public:
    MySQLPool(const std::string &host, int port, const std::string &user, const std::string &password,
              const std::string &database, size_t poolSize)
            : _host(host), _port(port), _user(user), _password(password), _database(database), _poolSize(poolSize) {
        for (size_t i = 0; i < _poolSize; ++i) {
            _connections.emplace(std::make_shared<MySQLConnection>(_host, _port, _user, _password, _database));
        }
    }

    MySQLPool(const std::string &host, int port, const std::string &user, const std::string &password,
              const std::string &database)
            : _host(host), _port(port), _user(user), _password(password), _database(database) {
        // 提供默认连接池大小或通过某种逻辑计算它
        _poolSize = 8; // 假设默认大小为 10
        for (size_t i = 0; i < _poolSize; ++i) {
            _connections.emplace(std::make_shared<MySQLConnection>(_host, _port, _user, _password, _database));
        }
    }

    void setPoolSize(size_t newSize) {
        std::unique_lock<std::mutex> lock(_mutex);

        // 缩减连接池大小
        while (_connections.size() > newSize) {
            _connections.pop();
        }

        // 扩大连接池大小
        while (_connections.size() < newSize) {
            _connections.emplace(std::make_shared<MySQLConnection>(_host, _port, _user, _password, _database));
        }
        _poolSize = newSize;
    }


    ~MySQLPool() = default;

    std::shared_ptr<MySQLConnection> getConnection() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_connections.empty()) {
            _condition.wait(lock);
        }
        auto conn = _connections.front();
        _connections.pop();
        return conn;
    }

    void releaseConnection(std::shared_ptr<MySQLConnection> conn) {
        std::unique_lock<std::mutex> lock(_mutex);
        _connections.push(conn);
        _condition.notify_one();
    }
};


#endif //CPP_TOOLS_MYSQLPOOL_H
