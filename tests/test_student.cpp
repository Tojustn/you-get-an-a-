#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/student.hpp"
#include "../src/assignment.hpp"
#include "../src/assignment_grade.hpp"

TEST_CASE("Constructor") {
    Student student("John Doe", "12345");
    
    REQUIRE(student.name == "John Doe");
    REQUIRE(student.id == "12345");
    REQUIRE(student.grades.size() == 0);
}

TEST_CASE("Zero Grades") {
    Student student("Jane Smith", "67890");
    
    REQUIRE(student.name == "Jane Smith");
    REQUIRE(student.id == "67890");
    REQUIRE(student.grades.empty());
    REQUIRE(student.grades.size() == 0);
}

TEST_CASE("Empty Name and ID") {
    Student student("", "");
    
    REQUIRE(student.name == "");
    REQUIRE(student.id == "");
    REQUIRE(student.grades.size() == 0);
}

TEST_CASE("One Grade") {
    Student student("Bob Johnson", "11111");
    Assignment* assignment = new Assignment("Quiz 1", 100);
    AssignmentGrade* grade = new AssignmentGrade(assignment, 85);
    
    student.add_grade(grade);

    REQUIRE(student.grades.size() == 1);
    REQUIRE(student.grades[0]->grade == 85);
    REQUIRE(student.grades[0]->assignment == assignment);

    delete assignment;
}

TEST_CASE("Many Grades") {
    Student student("Alice Brown", "22222");
    Assignment* quiz1 = new Assignment("Quiz 1", 100);
    Assignment* quiz2 = new Assignment("Quiz 2", 100);
    Assignment* hw1 = new Assignment("Homework 1", 50);
    
    AssignmentGrade* grade1 = new AssignmentGrade(quiz1, 90);
    AssignmentGrade* grade2 = new AssignmentGrade(quiz2, 85);
    AssignmentGrade* grade3 = new AssignmentGrade(hw1, 45);
    
    student.add_grade(grade1);
    student.add_grade(grade2);
    student.add_grade(grade3);
    
    REQUIRE(student.grades.size() == 3);
    REQUIRE(student.grades[0]->grade == 90);
    REQUIRE(student.grades[1]->grade == 85);
    REQUIRE(student.grades[2]->grade == 45);

    delete quiz1;
    delete quiz2;
    delete hw1;
}

TEST_CASE("Single Character Name") {
    Student student("A", "1");
    
    REQUIRE(student.name == "A");
    REQUIRE(student.id == "1");
}

TEST_CASE("Long Name") {
    std::string long_name(100, 'X');
    Student student(long_name, "99999");
    
    REQUIRE(student.name == long_name);
    REQUIRE(student.id == "99999");
}

TEST_CASE("Zero Grade Value") {
    Student student("Test Student", "33333");
    Assignment* assignment = new Assignment("Quiz", 100);
    AssignmentGrade* grade = new AssignmentGrade(assignment, 0);
    
    student.add_grade(grade);

    REQUIRE(student.grades.size() == 1);
    REQUIRE(student.grades[0]->grade == 0);

    delete assignment;
}

TEST_CASE("Negative Grade") {
    Student student("Test Student", "44444");
    Assignment* assignment = new Assignment("Penalty", 100);
    AssignmentGrade* grade = new AssignmentGrade(assignment, -5);
    
    student.add_grade(grade);

    REQUIRE(student.grades.size() == 1);
    REQUIRE(student.grades[0]->grade == -5);

    delete assignment;
}

TEST_CASE("add_grade") {
    Student student("Interface Test", "55555");
    Assignment* assignment1 = new Assignment("A1", 100);
    Assignment* assignment2 = new Assignment("A2", 100);
    
    AssignmentGrade* grade1 = new AssignmentGrade(assignment1, 75);
    AssignmentGrade* grade2 = new AssignmentGrade(assignment2, 80);
    
    REQUIRE(student.grades.size() == 0);
    
    student.add_grade(grade1);
    REQUIRE(student.grades.size() == 1);
    
    student.add_grade(grade2);
    REQUIRE(student.grades.size() == 2);
    
    REQUIRE(student.grades[0] == grade1);
    REQUIRE(student.grades[1] == grade2);

    delete assignment1;
    delete assignment2;
}

TEST_CASE("Same Name Different IDs") {
    Student student1("John Doe", "11111");
    Student student2("John Doe", "22222");
    
    REQUIRE(student1.name == student2.name);
    REQUIRE(student1.id != student2.id);
    REQUIRE(student1.id == "11111");
    REQUIRE(student2.id == "22222");
}

TEST_CASE("Same ID Different Names") {
    Student student1("Alice", "12345");
    Student student2("Bob", "12345");
    
    REQUIRE(student1.id == student2.id);
    REQUIRE(student1.name != student2.name);
}

TEST_CASE("Same Assignment Multiple Grades") {
    Student student("Test Student", "66666");
    Assignment* assignment = new Assignment("Quiz", 100);
    
    AssignmentGrade* grade1 = new AssignmentGrade(assignment, 70);
    AssignmentGrade* grade2 = new AssignmentGrade(assignment, 80);
    AssignmentGrade* grade3 = new AssignmentGrade(assignment, 90);
    
    student.add_grade(grade1);
    student.add_grade(grade2);
    student.add_grade(grade3);
    
    REQUIRE(student.grades.size() == 3);
    REQUIRE(student.grades[0]->grade == 70);
    REQUIRE(student.grades[1]->grade == 80);
    REQUIRE(student.grades[2]->grade == 90);

    delete assignment;
}

