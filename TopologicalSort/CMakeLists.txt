cmake_minimum_required(VERSION 3.13)
project(TopologicalSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
add_executable(TopologicalSort main.cpp DAG.cpp DAG.h util/util.cpp util/util.h)