#include "gradebook.hpp"
#include "student.hpp"
#include "assignment_grade.hpp"
#include "assignment.hpp"
#include <iostream>

Gradebook::Gradebook() {
}

Gradebook::~Gradebook() {
    for (Student* student : students) {
        delete student;
    }
    for (Assignment* assignment : assignments) {
        delete assignment;
    }
    students.clear();
    assignments.clear();
}

void Gradebook::add_student(std::string name, std::string id) {
    Student* student = new Student(name, id);
    students.push_back(student);
}
void Gradebook::enter_grade(std::string student_name, std::string assignment_name, int grade) {
    for (Student* student : students) {
        if (student->name == student_name) {
            for (Assignment* assignment : assignments) {
                if (assignment->name == assignment_name) {
                    student->add_grade(new AssignmentGrade(assignment, grade));
                }
            }
        }
    }
}

void Gradebook::add_assignment(std::string name, int points) {
    assignments.push_back(new Assignment(name, points));
}

std::string Gradebook::report() {
    std::string output = "Last_Name,First_Name,Student_Id";
    for (Assignment* a : assignments) output += "," + a->name;
    output += "\n";

    for (Student* s : students) {
        size_t space = s->name.find(' ');
        std::string first = (space != std::string::npos) ? s->name.substr(0, space) : s->name;
        std::string last = (space != std::string::npos) ? s->name.substr(space + 1) : s->name;
        output += last + "," + first + "," + s->id;

        for (Assignment* a : assignments) {
            int grade = -1;
            for (AssignmentGrade* g : s->grades) {
                if (g->assignment == a) grade = g->grade;
            }
            output += (grade != -1) ? "," + std::to_string(grade) : ",none";
        }
        output += "\n";
    }
    return output;
}