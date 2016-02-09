set(SOURCES clipboard.cpp CPowerRequest.cpp create_directory_helper.cpp cue_creator.cpp cue_parser.cpp cue_parser_embedding.cpp cuesheet_index_list.cpp 
	dialog_resize_helper.cpp dropdown_helper.cpp dynamic_bitrate_helper.cpp file_info_const_impl.cpp file_list_helper.cpp file_move_helper.cpp 
	file_win32_wrapper.cpp filetimetools.cpp IDataObjectUtils.cpp input_helpers.cpp listview_helper.cpp metadb_io_hintlist.cpp mp3_utils.cpp seekabilizer.cpp 
	StdAfx.cpp stream_buffer_helper.cpp text_file_loader.cpp VisUtils.cpp win32_dialog.cpp win32_misc.cpp window_placement_helper.cpp writer_wav.cpp)
set(HEADERS bitreader_helper.h CallForwarder.h cfg_guidlist.h clipboard.h COM_utils.h CPowerRequest.h create_directory_helper.h cue_creator.h cue_parser.h 
	cuesheet_index_list.h dialog_resize_helper.h dropdown_helper.h dynamic_bitrate_helper.h fb2k_threads.h file_cached.h file_info_const_impl.h 
	file_list_helper.h file_move_helper.h file_win32_wrapper.h filetimetools.h fullFileBuffer.h helpers.h icon_remapping_wildcard.h IDataObjectUtils.h 
	input_helpers.h listview_helper.h meta_table_builder.h metadb_io_hintlist.h mp3_utils.h playlist_position_reference_tracker.h ProcessUtils.h 
	ProfileCache.h seekabilizer.h StdAfx.h stream_buffer_helper.h string_filter.h text_file_loader.h ThreadUtils.h VisUtils.h win32_dialog.h win32_misc.h 
	window_placement_helper.h writer_wav.h)

add_library(foobar2000_sdk_helpers ${HEADERS} ${SOURCES})

target_compile_definitions(foobar2000_sdk_helpers PRIVATE _UNICODE)