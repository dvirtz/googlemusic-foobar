#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
#include "foobar2000.h"
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
public:
    void on_init()
    {
        g_gmusic.init();
        g_gmusic.login();

        auto songs = g_gmusic.songs();
        auto song_list = pfc::list_const_array_t<metadb_handle_ptr, std::vector<metadb_handle_ptr>>(songs, songs.size());

        auto playlistManager = static_api_ptr_t<playlist_manager>();
        std::string playlistName{ "Google music" };
        auto playlist = playlistManager->create_playlist(playlistName.c_str(), playlistName.size(), std::numeric_limits<size_t>::max());
        playlistManager->playlist_add_items(playlist, song_list, bit_array_false());

    }
    void on_quit()
    {
        console::print("Sample component: on_quit()");
    }
};

static initquit_factory_t<InitQuit> g_initquit_factory;

} // namespace foo_gmusic