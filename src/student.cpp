#include "student.hpp"
#include "assignment_grade.hpp"
#include <vector>
void Student::add_grade(AssignmentGrade* grade) {
    grades.push_back(grade);
}

Student::~Student() {
    for (AssignmentGrade* grade : grades) {
        delete grade;
    }
    grades.clear();
}