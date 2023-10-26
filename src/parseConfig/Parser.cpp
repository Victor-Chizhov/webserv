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
        if (line.find_first_not_of(" \t") < 1) {
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        }
        line.erase(line.find(';'), 1);
        data = line.substr(pos + finder.length());

        /*
         понять как проверить строку на наличие символов кроме пробелов
         кинуть ошибку если в строке есть символы кроме пробелов
         оптимизировать код
        */

        line.erase();
    }
}

void Parser::cutDataNum(std::string &line, std::string finder, unsigned long &data) {

    unsigned long numValue = 0;

    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        std::string strData = line.substr(pos + finder.length());
        if (strData.find_first_not_of(" \t") < 1) {
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        }
        strData.erase(strData.find(';'), 1);
        if (!isValidNum(strData, numValue)) {
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        }
        data = std::stoul(strData);
        line.erase();
    }
}

void Parser::cutDataMap(std::string &line, std::string finder, std::map<int, std::string> &data) {
    (void)data;
    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        line = line.substr(pos + finder.length());
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
//            printf("line:%s\n", line.c_str());
//            printf("pos %lu\n", spacePos);
//            printf("str: %s\n", line.substr(0, spacePos).c_str());
//            int key = std::stoi(line.substr(0, spacePos));
//            std::string value = line.substr(spacePos + 1);
//            data[key] = value;
//            line.erase();
        }
        else
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
    }
}
