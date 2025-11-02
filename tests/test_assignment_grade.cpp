#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/assignment_grade.hpp"
#include "../src/assignment.hpp"

TEST_CASE("Constructor") {
    Assignment* assignment = new Assignment("Quiz 1", 100);
    AssignmentGrade grade(assignment, 85);
    
    REQUIRE(grade.assignment == assignment);
    REQUIRE(grade.grade == 85);
    REQUIRE(grade.assignment->name == "Quiz 1");
    
    delete assignment;
}

TEST_CASE("Zero Grade") {
    Assignment* assignment = new Assignment("Homework", 50);
    AssignmentGrade grade(assignment, 0);
    
    REQUIRE(grade.assignment == assignment);
    REQUIRE(grade.grade == 0);
    
    delete assignment;
}

TEST_CASE("One Grade") {
    Assignment* assignment = new Assignment("Exam", 200);
    AssignmentGrade grade(assignment, 175);
    
    REQUIRE(grade.grade == 175);
    REQUIRE(grade.assignment->points == 200);
    
    delete assignment;
}

TEST_CASE("Many Grades") {
    Assignment* assignment1 = new Assignment("Quiz 1", 100);
    Assignment* assignment2 = new Assignment("Quiz 2", 100);
    Assignment* assignment3 = new Assignment("Final", 300);
    
    AssignmentGrade grade1(assignment1, 90);
    AssignmentGrade grade2(assignment2, 85);
    AssignmentGrade grade3(assignment3, 270);
    
    REQUIRE(grade1.grade == 90);
    REQUIRE(grade1.assignment->name == "Quiz 1");
    REQUIRE(grade2.grade == 85);
    REQUIRE(grade2.assignment->name == "Quiz 2");
    REQUIRE(grade3.grade == 270);
    REQUIRE(grade3.assignment->name == "Final");
    
    delete assignment1;
    delete assignment2;
    delete assignment3;
}

TEST_CASE("Maximum Points") {
    Assignment* assignment = new Assignment("Perfect Score", 100);
    AssignmentGrade grade(assignment, 100);
    
    REQUIRE(grade.grade == 100);
    REQUIRE(grade.assignment->points == 100);
    
    delete assignment;
}

TEST_CASE("Grade Exceeds Points") {
    Assignment* assignment = new Assignment("Quiz", 100);
    AssignmentGrade grade(assignment, 110);
    
    REQUIRE(grade.grade == 110);
    REQUIRE(grade.assignment->points == 100);
    
    delete assignment;
}

TEST_CASE("Negative Grade") {
    Assignment* assignment = new Assignment("Penalty", 100);
    AssignmentGrade grade(assignment, -10);
    
    REQUIRE(grade.grade == -10);
    
    delete assignment;
}

TEST_CASE("Zero Points Assignment") {
    Assignment* assignment = new Assignment("Participation", 0);
    AssignmentGrade grade(assignment, 0);
    
    REQUIRE(grade.grade == 0);
    REQUIRE(grade.assignment->points == 0);
    
    delete assignment;
}

TEST_CASE("Multiple Grades Same Assignment") {
    Assignment* assignment = new Assignment("Test", 100);
    
    AssignmentGrade grade1(assignment, 50);
    REQUIRE(grade1.grade == 50);
    
    AssignmentGrade grade2(assignment, 75);
    REQUIRE(grade2.grade == 75);
    
    REQUIRE(grade1.assignment == assignment);
    REQUIRE(grade2.assignment == assignment);
    
    delete assignment;
}

TEST_CASE("Same Assignment Different Grades") {
    Assignment* assignment = new Assignment("Quiz", 100);
    
    AssignmentGrade grade1(assignment, 60);
    AssignmentGrade grade2(assignment, 80);
    AssignmentGrade grade3(assignment, 100);
    
    REQUIRE(grade1.grade == 60);
    REQUIRE(grade2.grade == 80);
    REQUIRE(grade3.grade == 100);
    REQUIRE(grade1.assignment == assignment);
    REQUIRE(grade2.assignment == assignment);
    REQUIRE(grade3.assignment == assignment);
    
    delete assignment;
}

TEST_CASE("Different Assignments Same Grade") {
    Assignment* assignment1 = new Assignment("Quiz 1", 100);
    Assignment* assignment2 = new Assignment("Quiz 2", 100);
    Assignment* assignment3 = new Assignment("Homework", 50);
    
    AssignmentGrade grade1(assignment1, 85);
    AssignmentGrade grade2(assignment2, 85);
    AssignmentGrade grade3(assignment3, 85);
    
    REQUIRE(grade1.grade == 85);
    REQUIRE(grade2.grade == 85);
    REQUIRE(grade3.grade == 85);
    REQUIRE(grade1.assignment != grade2.assignment);
    REQUIRE(grade2.assignment != grade3.assignment);
    
    delete assignment1;
    delete assignment2;
    delete assignment3;
}

