#pragma once

#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
MSC_RESTORE_WARNINGS
#include "songInfo.h"
#include <vector>

namespace foo_gmusic
{

class GMusic;

/// win traits for device property view
typedef CWinTraitsOR<LVS_REPORT | LVS_SINGLESEL, WS_EX_CLIENTEDGE, CControlWinTraits>
SongsTableWinTraits;

class SongsTable : public CWindowImpl<SongsTable, CListViewCtrl, SongsTableWinTraits>
{
public:
    SongsTable(HWND hWndParent);
    ~SongsTable();

    // ATL window class declaration. Replace class name with your own when reusing code.
    DECLARE_WND_CLASS_EX(_T("Google Music Main Dialog"), CS_VREDRAW | CS_HREDRAW, (-1));
    
    BEGIN_MSG_MAP(CMainDialog)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClick);
    END_MSG_MAP()

private:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnLButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    GMusic&                 m_gmusic;
    std::vector<SongInfo>   m_songs;
};

} // namespace foo_gmusic