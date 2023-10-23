#ifndef METHOD_HPP
#define METHOD_HPP

#include <iostream>
#include <vector>
#include <map>

class Method {
    private:
        int id;
        std::string name;

    public:
        Method();
        ~Method();
        int getId();
        void setId(int id);
        std::string getName();
        void setName(std::string name);
};

#endif