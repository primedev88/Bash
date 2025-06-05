//
// Created by anuj on 12/5/25.
//
#include "parser.h"
#include "tokenizer.h"
#include <iostream>

std::vector<Command> Parser::parse(const std::string& input) {
   std::vector<std::string> tokens = Tokenizer::tokenize(input);
   std::vector<Command> commands;
   Command current;

   for (size_t i = 0; i < tokens.size(); ++i) {
      std::string& tok = tokens[i];

      if (tok == "<") {
         if (i+1 <tokens.size()) current.input_redirect = tokens[++i];
      } else if (tok == ">") {
         if (i+1 < tokens.size()) current.output_redirect = tokens[++i];
      } else if (tok == ">>") {
         current.append_output = true;
         if (i+1 < tokens.size()) current.output_redirect = tokens[++i];
      } else if (tok == "&") {
         current.run_in_background = true;
      } else if (tok == ";") {
         if (!current.args.empty()) {
            commands.push_back(current);
            current = Command();
         }
      } else {
         current.args.push_back(tok);
      }
   }
   if (!current.args.empty()) {
      commands.push_back(current);
   }
   return commands;
}