cmake_minimum_required(VERSION 3.30)
project(Cpp_project)
set(CXX_STANDARD 20)
add_executable(proj main.cpp
complex.h
complex.cpp
Rect.h
bmp.h
bmp.cpp
vec.h)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(
	tests
	tests/vec_test.cpp)
target_link_libraries(
	tests
	GTest::gtest_main)
	
include(GoogleTest)
gtest_discover_tests (tests)