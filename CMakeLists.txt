cmake_minimum_required (VERSION 3.13)

project(ONFIAnalyzer)

add_definitions( -DLOGIC2 )

# enable generation of compile_commands.json, helpful for IDEs to locate include files.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# custom CMake Modules are located in the cmake directory.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(ExternalAnalyzerSDK)

set(SOURCES
src/source/ONFIAnalyzer.cpp
src/source/ONFIAnalyzer.h
src/source/ONFIAnalyzerResults.cpp
src/source/ONFIAnalyzerResults.h
src/source/ONFIAnalyzerSettings.cpp
src/source/ONFIAnalyzerSettings.h
src/source/ONFISimulationDataGenerator.cpp
src/source/ONFISimulationDataGenerator.h
)

add_analyzer_plugin(${PROJECT_NAME} SOURCES ${SOURCES})
