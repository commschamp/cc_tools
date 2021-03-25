set (name "cc_app")
set (src
    src/ConfigMgr.cpp
    src/PluginMgr.cpp
    src/PluginMgrImpl.cpp
)

set (hdr
)

add_library (${name} ${src} ${hdr})
add_library (cc::app ALIAS ${name})

target_compile_definitions(${name} PRIVATE -DCC_APP_LIB_EXPORT)    
target_link_libraries(${name} PUBLIC cc::plugin Qt5::Core)
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