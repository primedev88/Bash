//
// Created by anuj on 12/5/25.
//
#include "executor.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>

void Executor::execute(const Command& cmd) {
    if (cmd.args.empty()) return;

    pid_t pid = fork();
    if (pid == 0) {
        if (!cmd.input_redirect.empty()) {
            int in = open(cmd.input_redirect.c_str(),O_RDONLY);
            if (in < 0) perror("open input");
            else dup2(in, STDIN_FILENO);
        }
        if (!cmd.output_redirect.empty()) {
            int flags = O_WRONLY | O_CREAT | (cmd.append_output ? O_APPEND : O_TRUNC);
            int out = open(cmd.output_redirect.c_str(), flags, 0644);
            if (out < 0) perror("open output");
            else dup2(out,STDOUT_FILENO);
        }

        std::vector<char*> argv;
        for (const auto& arg : cmd.args) argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        perror("execvp failed");
        exit(1);
    } else if (!cmd.run_in_background) {
        waitpid(pid, nullptr, 0);
    }
}