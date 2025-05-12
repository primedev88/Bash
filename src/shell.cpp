//
// Created by anuj on 12/5/25.
//
#include "shell.h"
#include "parser.h"
#include "executor.h"
#include <iostream>

void Shell::run() {
    std::string input;
    while (true) {
        std::cout<<"pro-shell> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        auto args = Parser::parse(input);
        Executor::execute(args);
    }
}