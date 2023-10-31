#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Parser.hpp"
#include "Method.hpp"


class Location : public Parser {
    private:
        std::vector<std::string> locationConfig;
        std::string root;
        std::string index;
        bool autoIndex;
        std::string cgiPass;
        unsigned long long clientMaxBodySize;
        bool fileUpload;
        std::vector<Method> methods;

    public:
        Location();
        Location(const Location &copy);
        Location &operator=(const Location &copy);
        virtual ~Location();

        void setConfig(std::string configLine);
        void printDataConfig() const;


};

#endif