cmake_minimum_required(VERSION 3.22.1)
project(emlio-lite VERSION 0.1.0)

option(EMLIO_BUILD_TESTS "Turn on to build the tests." OFF)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(emlio emlio.cpp)
include(GenerateExportHeader)
generate_export_header(emlio EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/emlio/export.h)
target_include_directories(emlio
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include;${CMAKE_CURRENT_BINARY_DIR}>"
        "$<INSTALL_INTERFACE:include>"
)

add_subdirectory(src)

if(EMLIO_BUILD_TESTS)
    add_subdirectory(test)
endif()
if(EMLIO_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
