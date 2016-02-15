set(SOURCES AutoComplete.cpp CDialogResizeHelper.cpp inplace_edit.cpp inplace_edit_v2.cpp misc.cpp stdafx.cpp)
set(HEADERS ATLHelpers.h AutoComplete.h BumpableElem.h CDialogResizeHelper.h GDIUtils.h inplace_edit.h inplace_edit_v2.h misc.h stdafx.h WindowPositionUtils.h 
	WTL-PP.h)
	
add_library(foobar2000_ATL_helpers ${HEADERS} ${SOURCES})

target_compile_definitions(foobar2000_ATL_helpers PRIVATE _UNICODE)

find_package(WTL REQUIRED)

target_include_directories(foobar2000_ATL_helpers PUBLIC ${WTL_INCLUDE_DIRS})