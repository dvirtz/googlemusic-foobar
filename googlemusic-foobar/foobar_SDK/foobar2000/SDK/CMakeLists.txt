set(SOURCES abort_callback.cpp advconfig.cpp album_art.cpp app_close_blocker.cpp audio_chunk.cpp audio_chunk_channel_config.cpp cfg_var.cpp chapterizer.cpp 
	commandline.cpp completion_notify.cpp componentversion.cpp config_object.cpp console.cpp dsp.cpp dsp_manager.cpp file_cached_impl.cpp file_info.cpp 
	file_info_impl.cpp file_info_merge.cpp file_operation_callback.cpp filesystem.cpp filesystem_helper.cpp guids.cpp hasher_md5.cpp input.cpp 
	input_file_type.cpp link_resolver.cpp main_thread_callback.cpp mainmenu.cpp mem_block_container.cpp menu_helpers.cpp menu_item.cpp menu_manager.cpp 
	metadb.cpp metadb_handle.cpp metadb_handle_list.cpp output.cpp packet_decoder.cpp playable_location.cpp playback_control.cpp playlist.cpp 
	playlist_loader.cpp popup_message.cpp preferences_page.cpp replaygain.cpp replaygain_info.cpp search_tools.cpp service.cpp stdafx.cpp tag_processor.cpp 
	tag_processor_id3v2.cpp threaded_process.cpp titleformat.cpp ui.cpp ui_element.cpp)
set(HEADERS abort_callback.h advconfig.h album_art.h album_art_helpers.h app_close_blocker.h audio_chunk.h audio_postprocessor.h autoplaylist.h cfg_var.h 
	chapterizer.h commandline.h completion_notify.h component.h component_client.h components_menu.h componentversion.h config_io_callback.h config_object.h 
	config_object_impl.h console.h contextmenu.h contextmenu_manager.h core_api.h coreversion.h decode_postprocessor.h dsp.h dsp_manager.h event_logger.h 
	exceptions.h file_info.h file_info_impl.h file_operation_callback.h filesystem.h filesystem_helper.h foobar2000.h genrand.h hasher_md5.h http_client.h 
	icon_remap.h info_lookup_handler.h initquit.h input.h input_file_type.h input_impl.h library_manager.h link_resolver.h main_thread_callback.h 
	mem_block_container.h menu.h menu_helpers.h message_loop.h metadb.h metadb_handle.h modeless_dialog.h ole_interaction.h output.h packet_decoder.h 
	play_callback.h playable_location.h playback_control.h playback_stream_capture.h playlist.h playlist_loader.h popup_message.h preferences_page.h 
	progress_meter.h replaygain.h replaygain_scanner.h resampler.h search_tools.h service.h service_impl.h shortcut_actions.h system_time_keeper.h 
	tag_processor.h threaded_process.h titleformat.h track_property.h ui.h ui_edit_context.h ui_element.h unpack.h vis.h)
	
add_library(foobar2000_SDK ${HEADERS} ${SOURCES})

target_compile_definitions(foobar2000_SDK PRIVATE _UNICODE)