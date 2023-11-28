#Environment config
cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)
include_directories(./include)

#Project
set(PROJECT_NAME Curl)
project(${PROJECT_NAME})

#Source and lib
set(SOURCE_FILES)
set(LIBRARIES OpenMaya Foundation)

#Build
build_plugin()