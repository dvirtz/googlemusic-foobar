cmake_minimum_required(VERSION 2.6)

project(googlemusic-foobar)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(foobar_SDK)
foreach(target foobar2000_ATL_helpers foobar2000_component_client foobar2000_SDK foobar2000_sdk_helpers pfc)
	set_target_properties(${target} PROPERTIES FOLDER foobar2000_SDK)
endforeach()
add_subdirectory(gmusicapi-cpp)
foreach(target doc Example GMusicApi PythonHelper Tester)
	set_target_properties(${target} PROPERTIES FOLDER GMusicApi)
endforeach()
add_subdirectory(foo_gmusic)