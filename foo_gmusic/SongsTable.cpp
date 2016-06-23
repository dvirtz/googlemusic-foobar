#include "songstable.h"
#include "utility.h"
#include "gmusic.h"
#include "processLocationsNotify.h"

namespace foo_gmusic
{

SongsTable::SongsTable(HWND hWndParent)
    : m_gmusic(GMusic::instance())
{
    Create(hWndParent);
}

SongsTable::~SongsTable()
{
    //DestroyWindow();
}

LRESULT SongsTable::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & /*bHandled*/)
{
    auto lRes = DefWindowProc(uMsg, wParam, lParam);

    AddColumn(_T("Title"), 0);
    AddColumn(_T("Artist"), 1);
    AddColumn(_T("Album"), 2);
    
    m_songs = m_gmusic.songs();
    for (size_t i = 0; i < m_songs.size(); ++i)
    {
        using detail::toTChar;
        AddItem(i, 0, toTChar(m_songs[i].m_title).data());
        AddItem(i, 1, toTChar(m_songs[i].m_artist).data());
        AddItem(i, 2, toTChar(m_songs[i].m_album).data());
    }

    return lRes;
}

LRESULT SongsTable::OnLButtonDblClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL & /*bHandled*/)
{
    LVITEM item;
    if (GetSelectedItem(&item))
    {
        auto song = m_songs[item.iItem];
        auto url = m_gmusic.streamUrl(song.m_id);
        static_api_ptr_t<playlist_incoming_item_filter_v2>()->process_locations_async(
            pfc::list_single_ref_t<const char*>(url.c_str()),
            playlist_incoming_item_filter_v2::op_flag_background,
            NULL,
            NULL,
            m_hWnd,
            service_ptr_t<ProcessLocationsNotify>(new service_impl_t<ProcessLocationsNotify>(std::vector<SongInfo>{ song }))
        );

    }
    return LRESULT();
}

} // namespace foo_gmusic