#include "gmusic.h"
#include "preferences.h"
#include "Module.h"
#include "Mobileclient.h"
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

GMusicApi::SongRange GMusic::songs(bool incremental /*= false*/, bool include_deleted /*= false*/)
{
    assert(m_isLoggedIn);
    return m_client->get_all_songs(incremental, include_deleted);
}

} // namespace foo_gmusic