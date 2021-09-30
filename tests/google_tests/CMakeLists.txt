project(google_tests)

add_subdirectory(lib)

add_executable(google_test_run
        DefaultFiniteMapTest.cpp
        ModifiedFiniteMapTest.cpp
        TilesetFiniteMapTest.cpp
        TilesetWangsetsFiniteOrthogonalMap.cpp
        TilesetExternalFiniteOrthogonalMap.cpp
        TilesetExternalFiniteOrthogonalMapObjectGroup.cpp
        FiniteOrthogonalMapObjectGroupTileObjectEmbedded.cpp
        FiniteOrthogonalMapObjectGroupTileObjectTemplated.cpp
        FiniteOrthogonalMapTiles.cpp
        TilesetExternalFiniteOrthogonalMapObjectGroupLayer.cpp
        FiniteMapTilesetImageCollection.cpp)

target_include_directories(google_test_run PRIVATE
        ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
        )

target_link_libraries(google_test_run PRIVATE
        gtest
        gtest_main
        tinytmx::tinytmx
        )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

