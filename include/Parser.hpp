#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unistd.h>
#include <cstring>

class Parser {

    public:
        void removeSpaces(std::string &line);

        template<typename T>
        void addConfigsInArray(std::vector<T> vector, std::vector<std::string> &configLine, std::string finder);
};

template<typename T>
void Parser::addConfigsInArray(std::vector<T> array, std::vector<std::string> &configLines, std::string finder) {
    for (size_t i = 0; i < configLines.size(); i++) {
        removeSpaces(configLines[i]);
        if (configLines[i].find(finder) != std::string::npos) {
            T data;
            size_t openBrackets = 0;
//            static int id = 0;
            while (i < configLines.size()) {
                data.setServerConfig(configLines[i]);
                if (configLines[i].find("{") != std::string::npos) { openBrackets++; }
                if (configLines[i].find("}") != std::string::npos) { openBrackets--; }
                if (openBrackets == 0) { break; }
                i++;
            }
//            id++;
//            std::cout << "Server config: " << id << std::endl;
//            data.printServerConfig();
            array.push_back(data);
        }
    }
}




#endif