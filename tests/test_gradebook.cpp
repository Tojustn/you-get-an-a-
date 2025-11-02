#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/gradebook.hpp"
#include "../src/student.hpp"
#include "../src/assignment.hpp"
#include "../src/assignment_grade.hpp"
#include <sstream>

TEST_CASE("Constructor") {
    Gradebook gradebook;
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id\n");
}

TEST_CASE("Empty Gradebook") {
    Gradebook gradebook;
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id\n");
}

TEST_CASE("One Assignment No Students") {
    Gradebook gradebook;
    gradebook.add_assignment("Quiz 1", 100);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz 1\n");
}

TEST_CASE("One Student No Assignments") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id\nDoe,John,12345\n");
}

TEST_CASE("One Student One Assignment") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz 1", 100);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz 1\nDoe,John,12345,none\n");
}

TEST_CASE("One Student One Assignment With Grade") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz 1", 100);
    gradebook.enter_grade("John Doe", "Quiz 1", 85);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz 1\nDoe,John,12345,85\n");
}

TEST_CASE("Many Students Many Assignments") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "11111");
    gradebook.add_student("Jane Smith", "22222");
    gradebook.add_student("Bob Johnson", "33333");
    
    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Quiz 2", 100);
    gradebook.add_assignment("Homework", 50);
    
    gradebook.enter_grade("John Doe", "Quiz 1", 90);
    gradebook.enter_grade("John Doe", "Quiz 2", 85);
    gradebook.enter_grade("Jane Smith", "Quiz 1", 95);
    gradebook.enter_grade("Bob Johnson", "Homework", 45);
    
    std::string report = gradebook.report();
    std::string expected = "Last_Name,First_Name,Student_Id,Quiz 1,Quiz 2,Homework\n";
    expected += "Doe,John,11111,90,85,none\n";
    expected += "Smith,Jane,22222,95,none,none\n";
    expected += "Johnson,Bob,33333,none,none,45\n";
    
    REQUIRE(report == expected);
}

TEST_CASE("Name Without Space") {
    Gradebook gradebook;
    gradebook.add_student("John", "12345");
    gradebook.add_assignment("Quiz", 100);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nJohn,John,12345,none\n");
}

TEST_CASE("Name With Multiple Spaces") {
    Gradebook gradebook;
    gradebook.add_student("John Middle Doe", "12345");
    gradebook.add_assignment("Quiz", 100);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nMiddle Doe,John,12345,none\n");
}

TEST_CASE("Empty Student Name") {
    Gradebook gradebook;
    gradebook.add_student("", "12345");
    gradebook.add_assignment("Quiz", 100);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\n,,12345,none\n");
}

TEST_CASE("Zero Grade") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz", 100);
    gradebook.enter_grade("John Doe", "Quiz", 0);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nDoe,John,12345,0\n");
}

TEST_CASE("Negative Grade") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Penalty", 100);
    gradebook.enter_grade("John Doe", "Penalty", -5);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Penalty\nDoe,John,12345,-5\n");
}

TEST_CASE("Grade Exceeds Points") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz", 100);
    gradebook.enter_grade("John Doe", "Quiz", 110);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nDoe,John,12345,110\n");
}

TEST_CASE("add_student") {
    Gradebook gradebook;
    
    gradebook.add_student("Alice", "11111");
    gradebook.add_student("Bob", "22222");
    
    std::string report = gradebook.report();
    std::string expected = "Last_Name,First_Name,Student_Id\n";
    expected += "Alice,Alice,11111\n";
    expected += "Bob,Bob,22222\n";
    
    REQUIRE(report == expected);
}

TEST_CASE("add_assignment") {
    Gradebook gradebook;
    
    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Quiz 2", 100);
    gradebook.add_assignment("Final", 200);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz 1,Quiz 2,Final\n");
}

TEST_CASE("enter_grade") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz", 100);
    
    gradebook.enter_grade("John Doe", "Quiz", 85);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nDoe,John,12345,85\n");
}

TEST_CASE("report") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    
    std::string report = gradebook.report();
    REQUIRE(!report.empty());
    REQUIRE(report.find("Last_Name") != std::string::npos);
    REQUIRE(report.find("First_Name") != std::string::npos);
    REQUIRE(report.find("Student_Id") != std::string::npos);
}

TEST_CASE("Multiple Grades Same Assignment") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    gradebook.add_assignment("Quiz", 100);
    
    gradebook.enter_grade("John Doe", "Quiz", 70);
    gradebook.enter_grade("John Doe", "Quiz", 80);
    gradebook.enter_grade("John Doe", "Quiz", 90);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\nDoe,John,12345,90\n");
}

TEST_CASE("Student Not Found") {
    Gradebook gradebook;
    gradebook.add_assignment("Quiz", 100);
    
    gradebook.enter_grade("Nonexistent Student", "Quiz", 85);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id,Quiz\n");
}

TEST_CASE("Assignment Not Found") {
    Gradebook gradebook;
    gradebook.add_student("John Doe", "12345");
    
    gradebook.enter_grade("John Doe", "Nonexistent Quiz", 85);
    
    std::string report = gradebook.report();
    REQUIRE(report == "Last_Name,First_Name,Student_Id\nDoe,John,12345\n");
}

TEST_CASE("Complex Scenario") {
    Gradebook gradebook;
    
    gradebook.add_student("Alice Anderson", "A001");
    gradebook.add_student("Bob Brown", "B002");
    gradebook.add_student("Charlie Chen", "C003");
    
    gradebook.add_assignment("Homework 1", 50);
    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Midterm", 200);
    
    gradebook.enter_grade("Alice Anderson", "Homework 1", 45);
    gradebook.enter_grade("Alice Anderson", "Quiz 1", 95);
    gradebook.enter_grade("Alice Anderson", "Midterm", 180);
    
    gradebook.enter_grade("Bob Brown", "Quiz 1", 85);
    gradebook.enter_grade("Bob Brown", "Midterm", 150);
    
    gradebook.enter_grade("Charlie Chen", "Homework 1", 50);
    gradebook.enter_grade("Charlie Chen", "Quiz 1", 100);
    
    std::string report = gradebook.report();
    std::string expected = "Last_Name,First_Name,Student_Id,Homework 1,Quiz 1,Midterm\n";
    expected += "Anderson,Alice,A001,45,95,180\n";
    expected += "Brown,Bob,B002,none,85,150\n";
    expected += "Chen,Charlie,C003,50,100,none\n";
    
    REQUIRE(report == expected);
}

