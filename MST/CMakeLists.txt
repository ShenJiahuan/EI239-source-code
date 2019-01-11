cmake_minimum_required(VERSION 3.13)
project(MST)

set(CMAKE_CXX_STANDARD 17)

add_executable(MST main.cpp MST.cpp MST.h util/generate.cpp util/generate.h)