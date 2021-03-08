set (name "cc_plugin")
set (src
    src/Plugin.cpp
    src/PluginObject.cpp
    src/Socket.cpp
)

set (hdr
    include/cc_tools/cc_plugin/Plugin.h
    include/cc_tools/cc_plugin/Socket.h
)

add_library (${name} ${src} ${hdr})
add_library (cc::plugin ALIAS ${name})

target_link_libraries(${name} PRIVATE Qt5::Core)
target_include_directories(${name} 
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(
    TARGETS ${name}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)