cmake_minimum_required(VERSION 3.5)

project(cc_tools LANGUAGES CXX)

############################################################
option (CC_BUILD_ECHO_SOCKET "Build echo socket plugin" ON)
option (CC_BUILD_DEMO_PROTOCOL "Build demo protocol plugin" ON)
############################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

include(GNUInstallDirs)

add_subdirectory (lib)
add_subdirectory (app)
add_subdirectory (plugin)
