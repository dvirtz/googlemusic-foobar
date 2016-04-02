#include "foo_gmusic/gmusic.h"
#include "foo_gmusic/preferences.h"
#include "gmusicapi/Module.h"
#include "gmusicapi/Mobileclient.h"
#include "gmusicapi/Song.h"
#include <iostream>

namespace foo_gmusic
{

GMusic g_gmusic;

void GMusic::init()
{
    m_module = std::make_unique<GMusicApi::Module>();
    m_client = std::make_unique<GMusicApi::Mobileclient>(*m_module);
}

void GMusic::login()
{
    if (m_isLoggedIn)
        return;

    auto user = CPreferences::cfg_user.toString();
    auto password = CPreferences::cfg_password.toString();

    if (m_client->login(user, password) == false)
    {
        popup_message::g_complain("Google Music login failed, please make sure the user name and password are updated on the preferences page");
    }
    else
    {
        m_isLoggedIn = true;
    }
}

std::vector<metadb_handle_ptr> GMusic::songs(bool include_deleted /*= false*/)
{
    assert(m_isLoggedIn);
    auto songs = m_client->get_all_songs(false, include_deleted);

    std::vector<metadb_handle_ptr> res;
    auto metaDbManager = static_api_ptr_t<metadb>();
    std::transform(songs.begin(), songs.end(), std::back_inserter(res), [&metaDbManager](const auto& song)
    {
        auto url = g_gmusic.streamUrl(song);
        auto loc = make_playable_location(url.c_str(), 0);
        metadb_handle_ptr handle;
        metaDbManager->handle_create(handle, loc);
        handle->
        return handle;
    });

    return res;
}

std::string GMusic::streamUrl(const GMusicApi::Song & song)
{
    return m_client->get_stream_url(song.id);
}

} // namespace foo_gmusic