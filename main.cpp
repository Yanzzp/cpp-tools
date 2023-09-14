#include <iostream>
#include "mytools.h"
#include "cppjieba/Jieba.hpp"

using namespace std;


int main() {
//    mytools tools;

    cppjieba::Jieba jieba("../dict/jieba.dict.utf8",
                          "../dict/hmm_model.utf8",
                          "../dict/user.dict.utf8",
                          "../dict/idf.utf8",
                          "../dict/stop_words.utf8");

    std::string text = "今天天气不错，我们一起出去玩吧！";
    std::vector<std::string> words;
    jieba.Cut(text, words, true);

    for (auto& word : words) {
        std::cout << word << "/";
    }

}

