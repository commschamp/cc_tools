find_package(Qt5 COMPONENTS Quick Widgets REQUIRED)

set (name "cc_view")
set (src
    src/AppMgr.cpp
    src/GuiState.cpp
    src/main.cpp
    src/PluginListModel.cpp
    resources.qrc
)

add_executable (${name} ${src})

target_compile_definitions(${name}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${name} PRIVATE cc::app cc::plugin Qt5::Quick Qt5::Widgets Qt5::Core)

install(
    TARGETS ${name}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (UNIX)
    install(
        PROGRAMS script/cc_view.sh
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif ()  