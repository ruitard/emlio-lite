find_package(Catch2 CONFIG REQUIRED)
add_executable(test_mime test_mime.cpp)
target_link_libraries(test_mime PRIVATE emlio Catch2::Catch2WithMain)