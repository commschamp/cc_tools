cmake_minimum_required(VERSION 3.5)

project(cc_tools LANGUAGES C CXX)

############################################################
option (CC_COMPILE_WARN_AS_ERR "Treat compilation warnings as errors" ON)
option (CC_BUILD_ECHO_SOCKET "Build echo socket plugin" ON)
option (CC_BUILD_TCP_CLIENT_SOCKET "Build TCP/IP client socket plugin" ON)
option (CC_BUILD_DEMO_PROTOCOL "Build demo protocol plugin" ON)

# Extra input variables
# CC_QT_DIR - Directory of Qt5 installation
############################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT "${CC_QT_DIR}" STREQUAL "")
    list (APPEND CMAKE_PREFIX_PATH ${CC_QT_DIR})
endif ()

find_package(Qt5 COMPONENTS Core REQUIRED)

include(GNUInstallDirs)
include(${PROJECT_SOURCE_DIR}/cmake/CommonFuncs.cmake)

cc_set_compile_flags()

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(plugin)
