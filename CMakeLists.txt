#cmake_minimum_required(VERSION 3.6)
#
cmake_minimum_required(VERSION 3.17)

project(project)

set(CMAKE_CXX_STANDARD 98)

#
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)


# Set include dir
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/ProjectMain.cpp
        src/TicTacToeUtils.h
        src/TicTacToeUtils.cpp
        src/tinystr.cpp
        src/tinystr.h
        src/tinyxml.cpp
        src/tinyxml.h
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/Hub.cpp
        src/Hub.h
        src/Vaccinatiecentrum.cpp
        src/Vaccinatiecentrum.h
        src/Simulation.cpp
        src/Simulation.h
        src/simulationImporter.cpp
        src/simulationImporter.h
        src/VaccinType.cpp
        src/VaccinType.h
        src/vaccininterface.cpp
        src/vaccininterface.h
        src/vaccininterface.ui
        src/vaccininterface.h
        src/vaccininterface.cpp
        src/vaccininterface.ui
        src/Gegevens.cpp
        src/Gegevens.h
        )

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/ProjectDomainTests.cpp
        src/ProjectInputTests.cpp
        src/ProjectOutputTests.cpp
        src/ProjectTests.cpp

        src/tinystr.cpp
        src/tinystr.h
        src/tinyxml.cpp
        src/tinyxml.h
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/Vaccinatiecentrum.cpp
        src/Vaccinatiecentrum.h
        src/Hub.cpp
        src/Hub.h
        src/TicTacToeUtils.h
        src/TicTacToeUtils.cpp
        src/Simulation.cpp
        src/Simulation.h
        src/simulationImporter.cpp
        src/simulationImporter.h
        src/VaccinType.cpp
        src/VaccinType.h
        src/vaccininterface.h
        src/vaccininterface.cpp
        src/vaccininterface.ui
        src/Gegevens.cpp
        src/Gegevens.h


        )

# Create RELEASE target
add_executable(project ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(project_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(project_debug gtest Qt5::Widgets Qt5::Charts)
target_link_libraries(project Qt5::Widgets Qt5::Charts)
