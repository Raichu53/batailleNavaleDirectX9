cmake_minimum_required(VERSION 3.23)
project(projet)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} WIN32 main.c gamesFunctions.c windowProc.c dx.c includes.h gamesFunctions.h dx.h)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/MicrosoftDirectXSDKJune2010/Lib/x64/d3d9.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/MicrosoftDirectXSDKJune2010/Lib/x64/d3dx9.lib)


