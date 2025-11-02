#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/assignment.hpp"

TEST_CASE("Constructor") {
    Assignment assignment("Homework 1", 100);
    
    REQUIRE(assignment.name == "Homework 1");
    REQUIRE(assignment.points == 100);
}

TEST_CASE("Zero Points") {
    Assignment assignment("Extra Credit", 0);
    
    REQUIRE(assignment.name == "Extra Credit");
    REQUIRE(assignment.points == 0);
}

TEST_CASE("Empty Name") {
    Assignment assignment("", 50);
    
    REQUIRE(assignment.name == "");
    REQUIRE(assignment.points == 50);
}

TEST_CASE("One Item") {
    Assignment assignment("Quiz 1", 25);
    
    REQUIRE(assignment.name == "Quiz 1");
    REQUIRE(assignment.points == 25);
}

TEST_CASE("Many Assignments") {
    Assignment hw1("Homework 1", 100);
    Assignment hw2("Homework 2", 150);
    Assignment quiz("Quiz 1", 50);
    Assignment exam("Final Exam", 200);
    
    REQUIRE(hw1.name == "Homework 1");
    REQUIRE(hw1.points == 100);
    REQUIRE(hw2.name == "Homework 2");
    REQUIRE(hw2.points == 150);
    REQUIRE(quiz.name == "Quiz 1");
    REQUIRE(quiz.points == 50);
    REQUIRE(exam.name == "Final Exam");
    REQUIRE(exam.points == 200);
}

TEST_CASE("Maximum Points") {
    Assignment assignment("Large Assignment", 1000);
    
    REQUIRE(assignment.name == "Large Assignment");
    REQUIRE(assignment.points == 1000);
}

TEST_CASE("Single Character Name") {
    Assignment assignment("A", 10);
    
    REQUIRE(assignment.name == "A");
    REQUIRE(assignment.points == 10);
}

TEST_CASE("Long Name") {
    std::string long_name(200, 'A');
    Assignment assignment(long_name, 100);
    
    REQUIRE(assignment.name == long_name);
    REQUIRE(assignment.points == 100);
}

TEST_CASE("Negative Points") {
    Assignment assignment("Penalty", -10);
    
    REQUIRE(assignment.name == "Penalty");
    REQUIRE(assignment.points == -10);
}

TEST_CASE("Constructor with Const String") {
    const std::string name = "Lab Assignment";
    Assignment assignment(name, 75);
    
    REQUIRE(assignment.name == "Lab Assignment");
    REQUIRE(assignment.points == 75);
}

TEST_CASE("Same Name Different Objects") {
    Assignment assignment1("Quiz", 25);
    Assignment assignment2("Quiz", 50);
    
    REQUIRE(assignment1.name == "Quiz");
    REQUIRE(assignment1.points == 25);
    REQUIRE(assignment2.name == "Quiz");
    REQUIRE(assignment2.points == 50);
}

