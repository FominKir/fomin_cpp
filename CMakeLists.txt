cmake_minimum_required(VERSION 3.30)
project(Cpp_project)
set(CXX_STANDARD 20)
add_library(source_lib
complex.h
complex.cpp
Rect.h
bmp.h
bmp.cpp
vec.h
vec_functions.h
templates.h
tasks/factorial.h
thread/thread_pool.h
thread/thread_pool.cpp
RayMarching/Camera.cpp
RayMarching/LightSource.cpp
RayMarching/Material.cpp
RayMarching/Object.cpp
RayMarching/Ray.cpp
RayMarching/Scene.cpp
RayMarching/Texture.cpp
RayMarching/Camera.h
RayMarching/LightSource.h
RayMarching/Material.h
RayMarching/Object.h
RayMarching/Ray.h
RayMarching/Scene.h
RayMarching/Texture.h
)
add_executable(proj main.cpp)
target_link_libraries(proj source_lib)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(
	tests
	tests/vec_test.cpp
	tests/vec_func_test.cpp
	tests/template_test.cpp
	tasks/factorial_test.cpp
	tests/objects_test.cpp
	)
target_link_libraries(
	tests
	GTest::gtest_main
	source_lib)
	
include(GoogleTest)
gtest_discover_tests (tests)