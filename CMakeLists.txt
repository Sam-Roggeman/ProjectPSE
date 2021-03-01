cmake_minimum_required(VERSION 3.6)
project(project)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES src/ProjectMain.cpp src/Project.cpp
        src/Project.h
        src/ProjectDomainTests.cpp
        src/ProjectInputTests.cpp
        src/ProjectOutputTests.cpp
        src/test.xml
        src/tinystr.cpp
        src/tinystr.h
        src/tinyxml.cpp
        src/tinyxml.h
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp HUB.cpp HUB.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/ProjectTests.cpp
        src/test.xml
        src/tinystr.cpp
        src/tinystr.h
        src/tinyxml.cpp
        src/tinyxml.h
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp src/Vaccinatiecentrum.cpp src/Vaccinatiecentrum.h)

# Create RELEASE target
add_executable(project ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(project_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(project_debug gtest)