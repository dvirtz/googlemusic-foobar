set(SOURCES component_client.cpp)

add_library(foobar2000_component_client ${SOURCES})

target_compile_definitions(foobar2000_component_client PRIVATE _UNICODE)