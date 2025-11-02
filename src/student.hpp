#pragma once

#include <string>
#include <vector>
#include "assignment_grade.hpp"
class Student {

    public:
        std::string name;
        std::string id;
        std::vector<AssignmentGrade*> grades;
        Student(const std::string& name, const std::string& id): name(name), id(id) {};
        void add_grade( AssignmentGrade* grade);
        ~Student();
};
