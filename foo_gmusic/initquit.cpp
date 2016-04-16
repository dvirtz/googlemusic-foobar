#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
#include "foobar2000.h"
#include "component.h"
MSC_RESTORE_WARNINGS
#include "gmusic.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>

// Sample initquit implementation. See also: initquit class documentation in relevant header.

namespace foo_gmusic
{

class InitQuit : public ::initquit
{
    class info_update_completion : public completion_notify_receiver
    {};
public:
    void on_init()
    {
        GMusic::instance().login();


        auto playlistManager    = static_api_ptr_t<playlist_manager>();
        auto playlistCount      = playlistManager->get_playlist_count();
        auto gmusicPlaylist     = pfc::infinite_size;
        auto gmusicPlaylistName = "Google Music";
        for (t_size i = 0; i < playlistCount; ++i)
        {
            pfc::string8 playlistName;
            playlistManager->playlist_get_name(i, playlistName);
            if (playlistName == gmusicPlaylistName)
            {
                gmusicPlaylist = i;
                break;
            }
        }

        if (gmusicPlaylist == pfc::infinite_size)
        {
            gmusicPlaylist = playlistManager->create_playlist(gmusicPlaylistName, strlen(gmusicPlaylistName), pfc::infinite_size);
            playlistManager->playlist_add_locations(gmusicPlaylist, pfc::list_single_ref_t<const char*>("Google Music"), 
                                                    false, core_api::get_main_window());
        }
    }
    void on_quit()
    {
        console::print("Sample component: on_quit()");
    }

private:
    info_update_completion m_infoUpdateCompletion;
};

static initquit_factory_t<InitQuit> g_initquit_factory;

} // namespace foo_gmusic