#include "foo_gmusic/gmusic.h"
#include "foo_gmusic/preferences.h"
#include "gmusicapi/Module.h"
#include "gmusicapi/Mobileclient.h"
#include "gmusicapi/Song.h"
#include "utility.h"
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include "GMusicInterface.h"

namespace foo_gmusic
{

using detail::toStdString;
using detail::toPfcString;

GMusicInterface::GMusicInterface()
    : m_module(std::make_unique<GMusicApi::Module>()),
    m_client(std::make_unique<GMusicApi::Mobileclient>(*m_module))
{
}

GMusicInterface::~GMusicInterface() = default;

GMusicInterface & GMusicInterface::instance()
{
    static GMusicInterface s_instance;
    return s_instance;
}

void GMusicInterface::login()
{
    if (m_isLoggedIn)
        return;

    auto user = Preferences::cfg_user.toString();
    auto password = Preferences::cfg_password.toString();
    pfc::string8 androidId;
    Preferences::cfg_device_id.get(androidId);

    try
    {
        m_isLoggedIn = m_client->login(user, password, androidId.toString());
        if (m_isLoggedIn)
        {
            m_deviceId = deviceId();
        }
    }
    catch(std::exception& e)
    {
        console::error(e.what());
        popup_message::g_complain("Google Music login failed, please make sure the user name and password are updated on the preferences page");
    }
}

std::vector<SongInfo> GMusicInterface::songs(bool include_deleted /*= false*/)
{
    if (m_isLoggedIn == false)
    {
        return {};
    }
    auto songs = m_client->get_all_songs(false, include_deleted);

    std::vector<SongInfo> res;
    for (auto&& song : songs)
    {
        SongInfo info;
        info.m_id       = toPfcString(song.id);
        info.m_title    = toPfcString(song.title);
        info.m_album    = toPfcString(song.album);
        info.m_artist   = toPfcString(song.artist);
        info.m_year     = toPfcString(song.year);
        info.m_track    = toPfcString(song.trackNumber);
        info.m_genre    = toPfcString(song.genre);
        info.m_length   = std::stod(song.durationMillis) / 1000;
        res.push_back(info);
    }

    return res;
}

pfc::string8 GMusicInterface::deviceId()
{
    pfc::string8 res;
    Preferences::cfg_device_id.get(res);
    if (res.is_empty())
    {
        auto devices = m_client->get_registered_devices();
        if (devices.size() >= 10)
        {
            console::warning("10 devices already registered");
        }

        for (auto&& device : devices)
        {
            std::set<std::string> mobileTypes{ "ANDROID", "PHONE", "IOS" };
            if (mobileTypes.find(device.type) != mobileTypes.end())
            {
                res = toPfcString(device.id);
                break;
            }
        }

        if (res.is_empty())
        {
            console::warning("Failed to find a registered device");
        }
        else
        {
            Preferences::cfg_device_id.set(res);
        }
    }

    return res;
}

pfc::string8 GMusicInterface::streamUrl(const pfc::string8& songId, boost::optional<pfc::string8> deviceId /*= boost::none*/)
{
    if (deviceId == boost::none)
    {
        deviceId = m_deviceId;
    }

    return toPfcString(m_client->get_stream_url(toStdString(songId), toStdString(*deviceId)));
}

} // namespace foo_gmusic