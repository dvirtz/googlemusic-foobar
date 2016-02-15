set(SOURCES main.cpp)

add_library(foo_gmusic SHARED ${SOURCES})

target_include_directories(foo_gmusic PUBLIC
	$<TARGET_PROPERTY:foobar2000_ATL_helpers,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(foo_gmusic PRIVATE _UNICODE)

get_target_property(SHARED_LOC shared IMPORTED_LOCATION)

target_link_libraries(foo_gmusic PRIVATE
	pfc
	foobar2000_ATL_helpers
	foobar2000_component_client
	foobar2000_SDK
	foobar2000_sdk_helpers
	${SHARED_LOC})