//
// Created by 11057 on 2023/11/18.
//

#ifndef CPP_TOOLS_DATABASE_H
#define CPP_TOOLS_DATABASE_H
#include <string>

class Database {
public:
    virtual ~Database() = default;

    virtual bool connect(const std::string &host, const std::string &user,
                         const std::string &password, const std::string &database) = 0;

    virtual void execute(const std::string &query) = 0;
};


#endif //CPP_TOOLS_DATABASE_H
