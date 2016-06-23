#include "ProcessLocationsNotify.h"
#include "genDefs.h"
#include <cassert>

namespace foo_gmusic
{

ProcessLocationsNotify::ProcessLocationsNotify(const std::vector<SongInfo>& songs)
    : m_songs(songs)
{}

void ProcessLocationsNotify::on_completion(const pfc::list_base_const_t<metadb_handle_ptr>& p_items)
{
    assert(m_songs.size() == p_items.get_size());

    for (size_t i = 0; i < p_items.get_size(); ++i)
    {
        static_api_ptr_t<metadb_io_v3> meta_db_io_api;
        file_info_impl f_info;
        auto& song = m_songs[i];

        f_info.meta_set("Artist", song.m_artist.c_str());
        f_info.meta_set("Album", song.m_album.c_str());
        f_info.meta_set("Title", song.m_title.c_str());
        f_info.meta_set("Year", song.m_year.c_str());
        f_info.meta_set("Tracknumber", song.m_track.c_str());
        f_info.meta_set("Genre", song.m_genre.c_str());
        f_info.set_length(song.m_length); // seconds

        t_filestats stats = p_items[i].get_ptr()->get_filestats();

        meta_db_io_api->hint_async(p_items[i].get_ptr(), f_info, stats, true);

    }

    static_api_ptr_t<playlist_manager> plm;
    auto playlist = plm->find_or_create_playlist(g_pluginName.c_str());
    plm->playlist_clear(playlist);
    plm->playlist_add_items(playlist, p_items, bit_array_true());
    plm->set_active_playlist(playlist);

    static_api_ptr_t<playback_control> pc;
    pc->play_start();
}

} // namespace foo_gmusic