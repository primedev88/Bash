#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>

void parseInput(const std::string &input, std::vector<char*> &args) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        char* arg;
        arg = new char[token.size() + 1];
        std::strcpy(arg, token.c_str());
        args.push_back(arg);
    }
    args.push_back(nullptr);
}

int main() {
    std::string input;
    while (true) {
        std::cout<<"mini-shell> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        std::vector<char*> args;
        parseInput(input, args);

        pid_t pid = fork();
        if (pid==0) {
            execvp(args[0],args.data());
            perror("execvp failed");
            exit(1);
        }else {
            wait(nullptr);
        }

        // Clean up memory
        for (auto arg : args) {
            delete[] arg;
        }
    }
    return 0;
}