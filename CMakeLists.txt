cmake_minimum_required(VERSION 3.10)
project(SPSCQueue)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(prog
	src/main.cpp
)

target_include_directories(prog PRIVATE include src)

# ───────────────────────────────────────────────────────
# Google Test setup and test target
# ───────────────────────────────────────────────────────

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
    	GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_rb
	src/test_rb.cpp
)

target_link_libraries(test_rb
	gtest_main
	pthread
)

target_include_directories(test_rb PRIVATE include src)

include(GoogleTest)
gtest_discover_tests(test_rb)
