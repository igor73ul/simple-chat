#Минимальная версия CMake выбрана на основе той версии, что была под рукой
cmake_minimum_required(VERSION 2.8.12)

SET(PROJECTNAME "chat_application")
project(${PROJECTNAME})
SET(CMAKE_BUILD_TYPE Release)
message ("Project generation: " ${PROJECTNAME})
add_definitions("-std=c++11")
#set(QMAKE_CXXFLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
endif()

set(LIBS ${LIBS} ./lib/)
include_directories(include)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#Qt Libs
#set (CMAKE_PREFIX_PATH "C:/Qt5.9.7/5.9.7/msvc2015_64")
set (CMAKE_PREFIX_PATH "/opt/Qt5.1.1/5.1.1/gcc_64/")
#set(CMAKE_MAKE_PROGRAM)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_subdirectory(src)
