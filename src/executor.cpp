//
// Created by anuj on 12/5/25.
//
#include "executor.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

void Executor::execute(std::vector<char*>& args) {
    if (args.empty()) return;

    const pid_t pid = fork();
    if (pid==0) {
        execvp(args[0],args.data());
        perror("execvp failed");
        exit(1);
    }else {
        wait(nullptr);
    }
    for (const auto arg:args) {
        delete[] arg;
    }
}