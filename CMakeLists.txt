cmake_minimum_required(VERSION 2.7)
project(Hodgkin_Huxley_model)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

set(SOURCE_FILES main.cpp)
add_executable(Hodgkin_Huxley_model ${SOURCE_FILES} DataLoader.cpp DataLoader.h Params.h Logger.h Params.cpp Params.h Solver.cpp Solver.h)