#Environment config
cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)
include_directories(./include)

#Variables
set(PROJECT_NAME Sphelix)
set(PLUGIN_VERSION 1.0.0)
set(PLUGIN_VENDOR "SPHEREFRAME ANIMATION")

#Project and Compile definitions
project(${PROJECT_NAME} VERSION ${PLUGIN_VERSION})
add_compile_definitions(PLUGIN_VENDOR="${PLUGIN_VENDOR}")
add_compile_definitions(PLUGIN_VERSION="${PLUGIN_VERSION}")

#Source and lib
set(SOURCE_FILES src/PluginMain.cpp)
set(LIBRARIES OpenMaya Foundation)

#Build
build_plugin()
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${PLUGIN_VERSION}-WIN")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${PLUGIN_VERSION}-MAC")
endif()