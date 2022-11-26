enable_testing()

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(tinytmxlibtest 
                tinytmxlibtest.cpp
              )


target_link_libraries(tinytmxlibtest
              PRIVATE
                project_options
                tinytmx::tinytmx
                GTest::gtest 
                GTest::gtest_main
                GTest::gmock 
                GTest::gmock_main
)


gtest_discover_tests(tinytmxlibtest)