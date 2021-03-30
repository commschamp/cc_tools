if (NOT CC_BUILD_TCP_CLIENT_SOCKET)
    return ()
endif ()

find_package(Qt5Network REQUIRED)

set (name "cc_tcp_client_socket")
set (src
    TcpClientSocket.cpp
    TcpClientSocketIntegrationObj.cpp
    TcpClientSocketPlugin.cpp
)

set (rsrc
    resources.qrc
)

add_library (${name} MODULE ${src} ${rsrc})

target_link_libraries(${name} PRIVATE cc::plugin Qt5::Network Qt5::Core)

install(
    TARGETS ${name}
    DESTINATION ${CC_PLUGIN_INSTALL_DIR}
)