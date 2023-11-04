#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Parser.hpp"


class Location : public Parser {
    private:
        std::vector<std::string> locationConfig;
        std::string pathLocation;
        std::string root;
        std::string index;
        bool autoIndex;
        std::string cgiPass;
        unsigned long clientMaxBodySize;
        bool fileUpload;
        std::vector<std::string> methods;

    public:

        Location();
        Location(const Location &copy);
        Location &operator=(const Location &copy);

        void setConfig(std::string &configLine);
        void printDataConfig() const;
        void printLocationData();

        void updateDataInLocation();


};


#endif