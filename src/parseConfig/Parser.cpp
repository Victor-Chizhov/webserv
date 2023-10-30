#include "../../include/Parser.hpp"

std::string Parser::fullTrim(const std::string &line) {
    size_t posLeft = line.find_first_not_of(" \t\r\n");
    size_t posRight = line.find_last_not_of(" \t\r\n");

    if (posLeft == std::string::npos || posRight == std::string::npos)
        return "";
    return line.substr(posLeft, posRight - posLeft + 1);
}

void Parser::removeSpaces(std::string &line) {
    std::string result = "";
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] != ' ') {
            result += line[i];
        }
    }
    line = result;
}

void Parser::ParseAndCheckLine(std::string &line, std::string finder) {
    line = trim(line);
    if (line.find(finder) != 0) {
        throw std::out_of_range("Error: invalid " + finder + " value in config file");
    }
    line = line.substr(finder.length());
    if (line.find_first_not_of(" \t") != 1) {
        throw std::out_of_range("Error: invalid " + finder + " value in config file");
    }
    if (line.find(';') != line.length() - 1) {
        throw std::out_of_range("Error: invalid " + finder + " value in config file");
    }
    line.erase(line.find(';'), 1);
    if (line.find_last_not_of(" \t") != line.length() - 1) {
        throw std::out_of_range("Error: invalid " + finder + " value in config file");
    }
}

std::string Parser::trim(const std::string &line) {
    size_t posLeft = line.find_first_not_of(" \t\r\n");

    if (posLeft == std::string::npos)
        return "";
    return line.substr(posLeft);
}

void Parser::cutDataStr(std::string &line, std::string finder, std::string &data) {
    
    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        ParseAndCheckLine(line, finder);
        data = trim(line);
        line.erase();
    }
}

void Parser::cutDataNum(std::string &line, std::string finder, unsigned long &data) {

    unsigned long numValue = 0;

    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        ParseAndCheckLine(line, finder);
        line = trim(line);
        if (!isValidNum(line, numValue)) {
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        }
        data = std::stoul(line);
        line.erase();
    }
}

void Parser::cutDataMap(std::string &line, std::string finder, std::map<int, std::string> &data) {

    size_t pos = line.find(finder);
    if (pos != std::string::npos) {
        ParseAndCheckLine(line, finder);
        line = trim(line);
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            std::string strKey = line.substr(0, spacePos);
            if (!isValidNum(strKey, 0)) {
                throw std::out_of_range("Error: invalid " + finder + " value in config file");
            }
            int key = std::stoi(strKey);
            data[key] = trim(line.substr(spacePos + 1));
        }
        else
            throw std::out_of_range("Error: invalid " + finder + " value in config file");
        line.erase();
    }
}
