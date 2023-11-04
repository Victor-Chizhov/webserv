#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>


class Parser {

    public:
        void removeSpaces(std::string &line);
        void cutDataStr(std::string &line, std::string finder, std::string &data);
        void cutDataMap(std::string &line, std::string finder, std::map<int, std::string> &data);
        void cutDataNum(std::string &line, std::string finder, unsigned long &data);
        void cutDataBool(std::string &line, std::string finder, bool &data);
        void cutDataArray(std::string &line, std::string finder, std::vector<std::string> &data);
        void ParseAndCheckLine(std::string &line, std::string finder);
        std::string trim(const std::string &line);
        std::string fullTrim(const std::string &line);

        template<typename T>
        bool isValidNum(const std::string& str, T numValue);

        template<typename T>
        void addConfigInArray(std::vector<T> &array, std::vector<std::string> &configLine, std::string finder);

        void setConfig(std::string &configLine);

        void printDataConfig() const;


};

//сделать проверку на fghfgh server dfkghdfkg {
//сделать проверку на flgdlfg location dfkgjdkjg {


template<typename T>
void Parser::addConfigInArray(std::vector<T> &array, std::vector<std::string> &configLines, std::string finder) {
    for (size_t i = 0; i < configLines.size(); i++) {
        if (configLines[i].find(finder) != std::string::npos) {
            T data;
            size_t openBrackets = 0;
            while (i < configLines.size()) {
                data.setConfig(configLines[i]);
                if (configLines[i].find("{") != std::string::npos) { openBrackets++; }
                if (configLines[i].find("}") != std::string::npos) { openBrackets--; }
                if (openBrackets == 0) { break; }
                i++;
            }
            array.push_back(data);
        }
    }
}

template<typename T>
bool Parser::isValidNum(const std::string& str, T numValue) {
    std::istringstream iss(str);
    return (iss >> numValue) && iss.eof();
}


#endif