#si lors du build cette erreur :
#The system cannot find the file specified
#CMake Error: Generator: execution of make failed. Make command was: D:/CLion 2022.2.4/bin/mingw/bin/mingw32-make.exe -f Makefile -j 12 projet &&
#faire : vider le fichier cmake-build-debug (si il est pas deja vide ) -> clic droit dessus -> "reload cmake project"
cmake_minimum_required(VERSION 3.23)
project(projet)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} WIN32 main.c gamesFunctions.c windowProc.c dx.c includes.h gamesFunctions.h dx.h)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/MicrosoftDirectXSDKJune2010/Lib/x64/d3d9.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/MicrosoftDirectXSDKJune2010/Lib/x64/d3dx9.lib)


