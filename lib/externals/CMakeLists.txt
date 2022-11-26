if (NOT TINYTMX_EMBED_TINYXML2)
    add_subdirectory(tinyxml2)
endif ()

if (NOT TINYTMX_USE_MINIZ)
    # add_subdirectory(zlib)
endif ()

add_subdirectory(zstd/build/cmake)
