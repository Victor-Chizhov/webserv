#include "../../include/Parser.hpp"

void Parser::removeSpaces(std::string &line) {
    std::string result = "";
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] != ' ') {
            result += line[i];
        }
    }
    line = result;
}

