find_package(re2 CONFIG REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE emlio re2::re2)