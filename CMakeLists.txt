cmake_minimum_required(VERSION 3.10)
project(Template VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
enable_testing()

# Google Test
set(CMAKE_BUILD_TYPE "Debug")
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Build template library
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(TemplateLibrary ${SOURCES})  # Create a library target (optional)
target_compile_features(TemplateLibrary PUBLIC cxx_std_17)
target_compile_options(TemplateLibrary PRIVATE -Wall -Werror -pedantic -O3 -ffast-math)
target_include_directories(TemplateLibrary PUBLIC include)

# Build test executable
file(GLOB_RECURSE TEST_SOURCES test/*.cc)
add_executable(TemplateTest ${TEST_SOURCES})
target_compile_features(TemplateTest PUBLIC cxx_std_17)
target_link_libraries(TemplateTest TemplateLibrary GTest::gtest_main)  
target_include_directories(TemplateTest PUBLIC include)

# Build app executable
file(GLOB_RECURSE APP_SOURCES app/*.cpp)
add_executable(TemplateApp app/app_bigint.cpp)
target_link_libraries(TemplateApp TemplateLibrary)
target_include_directories(TemplateApp PUBLIC include)
target_compile_features(TemplateApp PUBLIC cxx_std_17)

include(GoogleTest)
gtest_discover_tests(test_bigInt)




