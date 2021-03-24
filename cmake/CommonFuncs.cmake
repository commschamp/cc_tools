macro (_cc_set_unix_flags)
    if ((CMAKE_COMPILER_IS_GNUCXX) OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
        set (extra_flags_list
            "-Wall" "-Wextra" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy"
            "-Wmissing-include-dirs"
            "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wundef" "-Wunused"
            "-fdiagnostics-show-option"
            "-Wcast-align" "-Wunused" "-Wconversion" 
            "-Wold-style-cast" "-Wdouble-promotion"
            
            "-Wno-unknown-pragmas" 
            "-Wno-sign-conversion" # This one is impractical
        )

        if (CMAKE_COMPILER_IS_GNUCC)
            list (APPEND extra_flags_list
                "-Wnoexcept" "-Wlogical-op" "-Wstrict-null-sentinel"
            )

            if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.0")
                list (APPEND extra_flags_list
                    "-Wmisleading-indentation" "-Wduplicated-cond" 
                )
            endif()      

            if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0")
                list (APPEND extra_flags_list
                    "-Wduplicated-branches" 
                )
            endif()                        

        endif ()

        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            list (APPEND extra_flags_list "-Wno-dangling-field -Wno-unused-command-line-argument")
        endif ()
        
        if (CC_COMPILE_WARN_AS_ERR)
            list (APPEND extra_flags_list "-Werror")
        endif ()
        
        string(REPLACE ";" " " extra_flags "${extra_flags_list}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")
    endif ()
endmacro()

macro (_cc_set_windows_flags)
endmacro()

###############################################################
macro (cc_set_compile_flags)
    if (UNIX)
        _cc_set_unix_flags ()
    endif ()

    if (WIN32)
        _cc_set_windows_flags()
    endif ()
endmacro ()