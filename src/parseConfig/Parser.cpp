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

void Parser::cutDataStr(std::string &line, std::string finder, std::string &data) {

    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        data = line.substr(pos + finder.length());
        line.erase();
    }
}

void Parser::cutDataNum(std::string &line, std::string finder, unsigned long &data) {

    unsigned long numValue = 0;

    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        std::string strData = line.substr(pos + finder.length());
        if (isValidNum<int>(strData, numValue)) {
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        }
        data = std::stoul(strData);
        line.erase();
    }
}

void Parser::cutDataMap(std::string &line, std::string finder, std::map<int, std::string> &data) {
    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        std::string strData = line.substr(pos + finder.length());
        std::string::size_type pos1 = strData.find(' ');
        std::string::size_type pos2 = strData.find(';');
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string strKey = strData.substr(0, pos1);
            std::string strValue = strData.substr(pos1 + 1, pos2 - pos1 - 1);
            int key = 0;
            if (isValidNum<int>(strKey, key)) {
                throw std::out_of_range("Error: invalid " + finder + " value in config file");
            }
            data[key] = strValue;
        }
    }
}
