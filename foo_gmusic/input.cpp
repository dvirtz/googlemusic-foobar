#include "input.h"
#include "gmusic.h"
#include "input_helpers.h"

namespace foo_gmusic
{
Input::Input()
    : m_gmusic(GMusic::instance()),
    m_pInputHelper(std::make_unique<input_helper>())
{}

Input::~Input() = default;

void Input::open(service_ptr_t<file> /*p_filehint*/, const char * /*p_path*/, t_input_open_reason /*p_reason*/, abort_callback & /*p_abort*/)
{
    m_songs = m_gmusic.songs();
}

void Input::get_info(t_int32 subsong, file_info & p_info, abort_callback & /*p_abort*/)
{
    assert(static_cast<size_t>(subsong) < m_songs.size());
    auto song = m_songs[subsong];
    p_info.set_length(song.m_length);
    p_info.meta_add("ARTIST", song.m_artist);
    p_info.meta_add("ALBUM", song.m_album);
    p_info.meta_add("TITLE", song.m_title);
}

t_uint32 Input::get_subsong_count()
{
    return m_songs.size();
}

t_uint32 Input::get_subsong(t_uint32 song)
{
    return song;
}

t_filestats Input::get_file_stats(abort_callback & /*p_abort*/)
{
    return m_stats;
}

void Input::decode_initialize(t_int32 subsong, unsigned /*p_flags*/, abort_callback & p_abort)
{
    auto streamUrl = m_gmusic.streamUrl(m_songs[subsong].m_id);
    m_pInputHelper->open(make_playable_location(streamUrl, 0), p_abort, input_helper::decodeOpen_t());
}

bool Input::decode_run(audio_chunk & p_chunk, abort_callback & p_abort)
{
    return m_pInputHelper->run(p_chunk, p_abort);
}

void Input::decode_seek(double p_seconds, abort_callback & p_abort)
{
    m_pInputHelper->seek(p_seconds, p_abort);
}

bool Input::decode_can_seek()
{
    return m_pInputHelper->can_seek();
}

bool Input::decode_get_dynamic_info(file_info & p_out, double & p_timestamp_delta)
{
    return m_pInputHelper->get_dynamic_info(p_out, p_timestamp_delta);
}

bool Input::decode_get_dynamic_info_track(file_info & p_out, double & p_timestamp_delta)
{
    return m_pInputHelper->get_dynamic_info_track(p_out, p_timestamp_delta);
}

void Input::decode_on_idle(abort_callback & p_abort)
{
    m_pInputHelper->on_idle(p_abort);
}

void Input::retag_set_info(t_int32 /*subsong*/, const file_info & /*p_info*/, abort_callback & /*p_abort*/)
{}

void Input::retag_commit(abort_callback & /*p_abort*/)
{}

bool Input::g_is_our_path(const char * p_full_path, const char * /*p_extension*/)
{
    return strstr(p_full_path, "Google Music") != nullptr;
}

bool Input::g_is_our_content_type(const char * /*p_content_type*/)
{
    return true;
}

} // namespace foo_gmusic

static input_factory_t<foo_gmusic::Input> m_gmusicInputFactory;
