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
    std::string output;
    output += "Last_Name,First_Name,Student_Id";
    for (Assignment* assignment : assignments) {
        output += "," + assignment->name;
    }
    output += "\n";

    for (Student* student : students) {
        std::string first_name, last_name;
        std::string name = student->name;
        size_t space_pos = name.find(' ');
        if (space_pos != std::string::npos) {
            first_name = name.substr(0, space_pos);
            last_name = name.substr(space_pos + 1);
        } else {
            first_name = name;
            last_name = name;
        }
        output += last_name + "," + first_name + "," + student->id;

        for (Assignment* assignment : assignments) {
            bool found = false;
            int found_grade = -1;
            for (AssignmentGrade* grade : student->grades) {
                if (grade->assignment == assignment) {
                    found = true;
                    found_grade = grade->grade;
                }
            }
            if (found) {
                output += "," + std::to_string(found_grade);
            } else {
                output += ",none";
            }
        }
        output += "\n";
    }
    return output;

}