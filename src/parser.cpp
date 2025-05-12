//
// Created by anuj on 12/5/25.
//
#include "parser.h"
#include <sstream>
#include <cstring>

std::vector<char*> Parser::parse(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    std::vector<char*> args;

    while (iss>>token) {
        char* arg = new char[token.size()+1];
        std::strcpy(arg,token.c_str());
        args.push_back(arg);
    }
    args.push_back(nullptr);
    return args;
}