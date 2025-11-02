#pragma once
#include <string>
class Assignment {

    public:
        std::string name;
        int points;
        Assignment(const std::string name, int points): name(name), points(points) {};
        ~Assignment();
};