cmake_minimum_required(VERSION 3.24)

project(you_get_an_a)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(test_assignment tests/test_assignment.cpp
        src/assignment.cpp)

add_executable(test_student tests/test_student.cpp
        src/assignment.cpp
        src/assignment_grade.cpp
        src/student.cpp)

add_executable(test_assignment_grade tests/test_assignment_grade.cpp
        src/assignment.cpp
        src/assignment_grade.cpp)

add_executable(test_gradebook tests/test_gradebook.cpp
        src/assignment.cpp
        src/assignment_grade.cpp
        src/gradebook.cpp
        src/student.cpp)

target_link_libraries(test_assignment PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_student PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_assignment_grade PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_gradebook PRIVATE Catch2::Catch2WithMain)

# Main executable
add_executable(main main.cpp
        main.cpp
        src/assignment.cpp
        src/assignment_grade.cpp
        src/gradebook.cpp
        src/student.cpp
        )
