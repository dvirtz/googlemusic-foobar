add_library(shared STATIC IMPORTED GLOBAL)
set_target_properties(shared PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/shared.lib)