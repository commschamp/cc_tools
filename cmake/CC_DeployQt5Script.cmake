# This script deploys Qt5 libraries on Windows.
# 
# Expected input variables
# CC_QT_DIR - Directory of Qt5 installation
# CC_DEPLOY_DIR - Directory where all Qt5 libraries need to be deployed
# CC_PARSE_DIR - Directory that need to parsed for deployment dependencies
# CC_QML_DIRS - Directories where all qml files are located

if (NOT WIN32)
    message (FATAL_ERROR "Qt5 deployment works only on Windows.")
endif ()

if ("${CC_QT_DIR}" STREQUAL "")
    message (FATAL_ERROR "Qt5 directory hasn't been provided.")
endif()

if ("${CC_DEPLOY_DIR}" STREQUAL "")
    message (FATAL_ERROR "Deployment directory hasn't been provided.")
endif()

if ("${CC_PARSE_DIR}" STREQUAL "")
    message (FATAL_ERROR "Directory to parse hasn't been provided.")
endif()

find_program (deploy_exe windeployqt PATHS ${CC_QT_DIR}/bin)

if (NOT deploy_exe)
    message (FATAL_ERROR "windeployqt.exe hasn't been found.")
endif ()

set (qml_args)
foreach (p ${CC_QML_DIRS})
    set (qml_args "${qml_args} --qmldir ${p}")
endforeach ()

execute_process (
    COMMAND ${deploy_exe} --dir ${CC_DEPLOY_DIR} ${qml_args} ${CC_PARSE_DIR}
)

