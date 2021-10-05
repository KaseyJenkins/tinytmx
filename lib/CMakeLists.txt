cmake_minimum_required(VERSION 3.20)
project(tinytmx)
include(GNUInstallDirs)


set(TINYTMX_VERSION_MAJOR 1)
set(TINYTMX_VERSION_MINOR 1)
set(TINYTMX_VERSION_PATCH 2)
set(TINYTMX_VERSION "${TINYTMX_VERSION_MAJOR}.${TINYTMX_VERSION_MINOR}.${TINYTMX_VERSION_PATCH}")
message(STATUS "TINYTMX VERSION ${TINYTMX_VERSION}")

include(cmake/tinytmxProjectSettings.cmake)

add_subdirectory(externals)

add_library(tinytmx "")
add_library(tinytmx::tinytmx ALIAS tinytmx)
#set_target_properties(tinytmx PROPERTIES CXX_STANDARD 17)

if (BUILD_SHARED_LIBS)
    set_target_properties(tinytmx PROPERTIES
            SOVERSION ${TINYTMX_VERSION_MAJOR}
            VERSION ${TINYTMX_VERSION})
endif ()

target_sources(tinytmx
        PRIVATE src/tinytmxColor.cpp
        PRIVATE src/tinytmxDataChunkTile.cpp
        PRIVATE src/tinytmxEllipse.cpp
        PRIVATE src/tinytmxGrid.cpp
        PRIVATE src/tinytmxGroupLayer.cpp
        PRIVATE src/tinytmxImage.cpp
        PRIVATE src/tinytmxImageLayer.cpp
        PRIVATE src/tinytmxMap.cpp
        PRIVATE src/tinytmxObject.cpp
        PRIVATE src/tinytmxObjectGroup.cpp
        PRIVATE src/tinytmxPolyObject.cpp
        PRIVATE src/tinytmxProperty.cpp
        PRIVATE src/tinytmxPropertySet.cpp
        PRIVATE src/tinytmxTerrain.cpp
        PRIVATE src/tinytmxTerrainArray.cpp
        PRIVATE src/tinytmxText.cpp
        PRIVATE src/tinytmxTile.cpp
        PRIVATE src/tinytmxLayer.cpp
        PRIVATE src/tinytmxTileLayer.cpp
        PRIVATE src/tinytmxTileOffset.cpp
        PRIVATE src/tinytmxTileset.cpp
        PRIVATE src/tinytmxTransformations.cpp
        PRIVATE src/tinytmxUtil.cpp
        PRIVATE src/tinytmxWangColor.cpp
        PRIVATE src/tinytmxWangSet.cpp
        PRIVATE src/tinytmxWangSetArray.cpp
        PRIVATE src/tinytmxWangTile.cpp
        )

if (TINYTMX_USE_MINIZ)
    target_sources(tinytmx
            PRIVATE externals/miniz/miniz.c)
    target_include_directories(tinytmx PRIVATE
            externals/miniz
            )
    target_compile_definitions(tinytmx
            PRIVATE -DUSE_MINIZ)
elseif (NOT TINYTMX_USE_MINIZ)
    target_include_directories(tinytmx PRIVATE
            externals/zlib
            ${CMAKE_CURRENT_BINARY_DIR}/externals/zlib
            )
    target_link_libraries(tinytmx PRIVATE
            zlibstatic
            )
endif ()

if (TINYTMX_EMBED_TINYXML2)
    target_sources(tinytmx
            PRIVATE externals/tinyxml2/tinyxml2.cpp
            )
    target_include_directories(tinytmx PRIVATE
            externals/tinyxml2
            )
elseif (NOT TINYTMX_EMBED_TINYXML2)
    target_link_libraries(tinytmx PRIVATE
            tinyxml2
            )
endif ()

if (TINYTMX_EMBED_BASE64)
    target_sources(tinytmx
            PRIVATE externals/base64/base64.cpp)
    target_include_directories(tinytmx PRIVATE
            externals/base64
            )
elseif (NOT TINYTMX_EMBED_BASE64)
    target_link_libraries(tinytmx PRIVATE
            base64
            )
endif ()


target_include_directories(tinytmx PRIVATE
        externals/zstd/lib
        )

target_include_directories(tinytmx PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

target_link_libraries(tinytmx PRIVATE
        project_options
        libzstd_static
        #        project_warnings
        )

include(CMakePackageConfigHelpers)

configure_file(cmake/tinytmx.pc.in tinytmx.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tinytmx.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/tinytmxConfigVersion.cmake
        VERSION ${TINYTMX_VERSION}
        COMPATIBILITY SameMajorVersion)

configure_package_config_file(cmake/tinytmxConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/tinytmxConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinytmx
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

install(TARGETS tinytmx
        project_options
        libzstd_static

        EXPORT tinytmxTargets

        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (NOT TINYTMX_USE_MINIZ)
    install(TARGETS zlibstatic
            EXPORT tinytmxTargets

            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif ()

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tinytmxConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/tinytmxConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinytmx)

install(EXPORT tinytmxTargets
        NAMESPACE tinytmx::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinytmx)