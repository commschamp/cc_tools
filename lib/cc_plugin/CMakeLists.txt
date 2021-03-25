set (name "cc_plugin")
set (src
    src/Plugin.cpp
    src/PluginObject.cpp
    src/Protocol.cpp
    src/Socket.cpp
)

set (hdr
    include/cc_tools/cc_plugin/Plugin.h
    #include/cc_tools/cc_plugin/Socket.h
)

add_library (${name} SHARED ${src} ${hdr})
add_library (cc::plugin ALIAS ${name})

target_compile_definitions(${name} PRIVATE -DCC_PLUGIN_LIB_EXPORT)    
target_link_libraries(${name} PUBLIC Qt5::Core)
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

install (
    DIRECTORY "include/cc_tools"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)