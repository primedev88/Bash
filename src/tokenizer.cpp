//
// Created by anuj on 12/5/25.
//
#include "tokenizer.h"
#include <sstream>
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string current;
    bool in_quotes = false;
    char quote_char = '\0';

    for (size_t i = 0; i < input.size(); ++i) {
        const char c = input[i];

        if ( in_quotes ) {
            if (c == quote_char) {
                in_quotes = false;
                tokens.push_back(current);
                current.clear();
            }else {
                current += c;
            }
        } else {
            if (c == '"' || c == '\'') {
                in_quotes = true;
                quote_char = c;
            } else if (std::isspace(c)){
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
            } else if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>') {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                // Handle >>
                if (c == '>' && i + 1 < input.size() && input[i + 1] == '>') {
                    tokens.emplace_back(">>");
                    ++i;
                } else {
                    tokens.push_back(std::string(1, c));
                }
            } else {
                current += c;
            }
        }
    }
    if ( !current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}