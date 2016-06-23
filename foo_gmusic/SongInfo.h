#pragma once
#include "string_base.h"

namespace foo_gmusic
{

struct SongInfo
{
    pfc::string8    m_id;
    pfc::string8    m_title;
    pfc::string8    m_album;
    pfc::string8    m_artist;
    pfc::string8    m_year;
    pfc::string8    m_track;
    pfc::string8    m_genre;
    double          m_length;
};

} // namespace foo_gmusic