set(SOURCES audio_math.cpp audio_sample.cpp base64.cpp bit_array.cpp bsearch.cpp cpuid.cpp filehandle.cpp guid.cpp nix-objects.cpp other.cpp pathUtils.cpp 
	printf.cpp selftest.cpp sort.cpp stdafx.cpp string_base.cpp string_conv.cpp stringNew.cpp synchro_nix.cpp threads.cpp timers.cpp utf8.cpp wildcard.cpp 
	win-objects.cpp)
set(HEADERS alloc.h array.h audio_sample.h avltree.h base64.h binary_search.h bit_array.h bit_array_impl.h bit_array_impl_part2.h bsearch.h 
	bsearch_inline.h byte_order_helper.h chain_list_v2.h com_ptr_t.h cpuid.h event.h filehandle.h guid.h instance_tracker.h int_types.h iterators.h 
	list.h map.h mem_block_mgr.h memalign.h nix-objects.h order_helper.h other.h pathUtils.h pfc.h pp-gettickcount.h pp-winapi.h primitives.h 
	primitives_part2.h ptr_list.h rcptr.h ref_counter.h sort.h string_base.h string_conv.h string_list.h string8_impl.h stringNew.h syncd_storage.h 
	synchro_nix.h synchro_win.h threads.h timers.h traits.h wildcard.h win-objects.h)
	
add_library(pfc ${HEADERS} ${SOURCES})