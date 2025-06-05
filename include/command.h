//
// Created by anuj on 12/5/25.
//

#pragma once
#include <vector>
#include <string>

struct Command {
    std::vector<std::string> args;
    std::string input_redirect;
    std::string output_redirect;
    bool append_output = false;
    bool run_in_background = false;
};
