#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Parser.hpp"
#include "Libraries.hpp"


class Location : public Parser {
    private:
        std::vector<std::string> locationConfig;
        std::string pathLocation;
        std::string root;
        std::string index;
        bool autoIndex;
        std::string cgiPass;
        int clientMaxBodySize;
        bool fileUpload;
        std::vector<std::string> methods;
        bool _redirect;
        std::string _redirect_path;

    public:

        Location();
        Location(const Location &copy);
        Location &operator=(const Location &copy);

        void setConfig(std::string &configLine);
        void printDataConfig() const;
        void printLocationData();
        std::string getCgiPass() const;
        bool isRedirect() const;
        const std::string &getRoot() const;
        const std::string &getPathLocation() const;
        const std::string &getRedirectPath() const;
        void updateDataInLocation();
        void parsePathLocation();


};


#endif