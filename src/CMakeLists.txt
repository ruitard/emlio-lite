find_package(re2 CONFIG REQUIRED)

target_sources(emlio
PRIVATE
    codec.cpp
    base64.cpp
    binary.cpp
    bit7.cpp
    bit8.cpp
    quoted_printable.cpp
    q_codec.cpp
    mime.cpp
)

target_link_libraries(emlio PRIVATE re2::re2)