include(GNUInstallDirs)

add_library(tinyxml2 "")
target_sources(tinyxml2
        PRIVATE tinyxml2.cpp
        )

target_include_directories(tinyxml2 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

install(TARGETS tinyxml2 EXPORT tinytmxTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )

