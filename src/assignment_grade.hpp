#pragma once

#include "assignment.hpp"
class AssignmentGrade {
    public:
        Assignment* assignment;
        int grade;

        AssignmentGrade(Assignment* assignment, int grade): assignment(assignment), grade(grade) {};
        ~AssignmentGrade();
};
