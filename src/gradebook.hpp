#pragma once

#include <vector>
#include <string>
#include "student.hpp"
class Gradebook {
    private:
        std::vector<Student*> students;
        std::vector<Assignment*> assignments;
    public:
        Gradebook();
        ~Gradebook();

        void add_student(std::string name, std::string id);
        void add_assignment(std::string name, int points);
        void enter_grade(std::string student_name, std::string assignment_name, int grade);
        std::string report();
};