if (NOT CC_BUILD_ECHO_SOCKET)
    return ()
endif ()

set (name "cc_echo_socket")
set (src
    EchoSocket.cpp
    EchoSocketPlugin.cpp
)

add_library (${name} MODULE ${src})

target_link_libraries(${name} PRIVATE cc::plugin Qt5::Core)

install(
    TARGETS ${name}
    DESTINATION ${CC_PLUGIN_INSTALL_DIR}
)