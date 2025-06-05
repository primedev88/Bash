//
// Created by anuj on 12/5/25.
//

#pragma once
#include "command.h"
#include <string>
#include <vector>

class Parser {
public:
    static std::vector<Command> parse(const std::string& input);
};
