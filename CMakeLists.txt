cmake_minimum_required(VERSION 3.7)
project(RockPaperScissors)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/woolie_main.cpp src/Referee.cpp src/Referee.h src/WoolieRPS.cpp src/WoolieRPS.h src/Arena.cpp src/Arena.h src/Woolie.cpp src/Woolie.h src/woolie_exception.h src/rng.h src/rng.cpp)
add_executable(RockPaperScissors ${SOURCE_FILES})