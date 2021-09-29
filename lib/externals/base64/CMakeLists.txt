include(GNUInstallDirs)

add_library(base64 "")
target_sources(base64
        PRIVATE base64.cpp
        )
target_include_directories(base64
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

install(TARGETS base64
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
