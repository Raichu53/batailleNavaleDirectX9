cmake_minimum_required(VERSION 3.23)
project(projet)

set(CMAKE_CXX_STANDARD 14)

add_executable(projet WIN32 main.c includes.h gamesFunctions.c gamesFunctions.cpp.h windowProc.c)
