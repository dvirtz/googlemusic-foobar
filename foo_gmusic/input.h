#pragma once
#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "foobar2000.h"
MSC_RESTORE_WARNINGS
#include <memory>
#include <vector>

class input_helper;

namespace foo_gmusic
{

struct SongInfo;
class GMusic;

class Input
{
public:
    Input();
    ~Input();

    void open(service_ptr_t<file> p_filehint, const char * p_path, t_input_open_reason p_reason, abort_callback & p_abort);

    void get_info(t_int32 subsong, file_info & p_info, abort_callback & p_abort);

    t_uint32 get_subsong_count();

    t_uint32 get_subsong(t_uint32 song);

    t_filestats get_file_stats(abort_callback & p_abort);

    void decode_initialize(t_int32 subsong, unsigned p_flags, abort_callback & p_abort);

    bool decode_run(audio_chunk & p_chunk, abort_callback & p_abort);

    void decode_seek(double p_seconds, abort_callback & p_abort);

    bool decode_can_seek();

    bool decode_get_dynamic_info(file_info & p_out, double & p_timestamp_delta);

    bool decode_get_dynamic_info_track(file_info & p_out, double & p_timestamp_delta);

    void decode_on_idle(abort_callback & p_abort);

    void retag_set_info(t_int32 subsong, const file_info & p_info, abort_callback & p_abort);

    void retag_commit(abort_callback & p_abort);

    static bool g_is_our_path(const char * p_full_path, const char * p_extension);

    static bool g_is_our_content_type(const char * p_content_type);
private:
    GMusic&                         m_gmusic;
    std::vector<SongInfo>           m_songs;
    t_filestats                     m_stats;
    std::unique_ptr<input_helper>   m_pInputHelper;
};

} // namespace foo_gmusic