set(SOURCES main.cpp preferences.cpp maindialog.cpp initquit.cpp gmusic.cpp songstable.cpp 
	ProcessLocationsNotify.cpp)
set(HEADERS utility.h atlcontrols.h gmusic.h disablewarnings.h preferences.h genDefs.h songstable.h
	ProcessLocationsNotify.h songInfo.h resource.h)
set(RESOURCES foo_gmusic.rc)

source_group("Resource Files" FILES ${RESOURCES})

add_library(foo_gmusic SHARED ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(foo_gmusic PUBLIC
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR})

find_package(WTL REQUIRED)

target_include_directories(foo_gmusic PRIVATE ${WTL_INCLUDE_DIRS})

target_compile_options(foo_gmusic PRIVATE $<$<BOOL:${MSVC}>:/WX> $<$<BOOL:${MSVC}>:/W4>)

target_compile_definitions(foo_gmusic PRIVATE _UNICODE BOOST_ALL_NO_LIB BOOST_PYTHON_STATIC_LIB NOMINMAX)

get_target_property(SHARED_LOC shared IMPORTED_LOCATION)

if("${PYTHON_VERSION}" STREQUAL "2.7")
    set(BOOST_PYTHON python)
else()
    set(BOOST_PYTHON python3)
endif()
set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost REQUIRED COMPONENTS ${BOOST_PYTHON})
find_package(PythonLibs ${PYTHON_VERSION} REQUIRED)

target_link_libraries(foo_gmusic PRIVATE
	pfc
	foobar2000_ATL_helpers
	foobar2000_component_client
	foobar2000_SDK
	foobar2000_sdk_helpers
	${SHARED_LOC}
	GMusicApi
	PythonHelper
	${Boost_LIBRARIES}
	${PYTHON_LIBRARY_RELEASE})

if(${CMAKE_CL_64})
set(PROGRAMFILES ProgramFiles)
else()
set(PROGRAMFILES "ProgramFiles(x86)")
endif()

find_file(COMPNENTS_DIR
	NAMES components 
	PATHS
	"$ENV{${PROGRAMFILES}}/foobar2000"
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\foobar2000;InstallLocation]"
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\foobar2000;InstallLocation]"
	DOC "foobar2000 components directory") 

install(TARGETS foo_gmusic RUNTIME DESTINATION ${COMPNENTS_DIR})