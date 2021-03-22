if (NOT CC_BUILD_DEMO_PROTOCOL)
    return ()
endif ()

set (name "cc_demo_protocol")
set (src
    DemoProtocol.cpp
    DemoProtocolPlugin.cpp
)

add_library (${name} MODULE ${src})

target_link_libraries(${name} PRIVATE cc::plugin Qt5::Core)

install(
    TARGETS ${name}
    DESTINATION ${CC_PLUGIN_INSTALL_DIR}
)