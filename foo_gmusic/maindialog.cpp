#include "maindialog.h"
#include "songstable.h"
#include "genDefs.h"

namespace foo_gmusic
{

// ui_element_impl_withpopup autogenerates standalone version of our component and proper menu commands. Use ui_element_impl instead if you don't want that.
class ui_element_myimpl : public ui_element_impl_withpopup<CMainDialog> {};

static service_factory_single_t<ui_element_myimpl> g_ui_element_myimpl_factory;

CMainDialog::CMainDialog(ui_element_config::ptr p_config, ui_element_instance_callback_ptr p_callback)
    : m_config(p_config), m_callback(p_callback)
{
    AtlInitCommonControls(ICC_TAB_CLASSES);
}

LRESULT CMainDialog::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & /*bHandled*/)
{
    LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);

    //CTabCtrl::SetDlgCtrlID(IDC_LIBRARYTAB);  

    auto tabs =
    {
        _T("Playlists"),
        _T("Instant Mixes"),
        _T("Artists"),
        _T("Albums"),
        _T("Songs"),
        _T("Genres")
    };

    for (auto&& tab : tabs)
    {
        AddItem(tab);
    }

    SetCurSel(static_cast<int>(Tabs::songs));

    m_pSongsTable = std::make_unique<SongsTable>(m_hWnd);
    m_pSongsTable->ShowWindow(SW_SHOW);

    SetRectangle();

    return lRet;
}

void CMainDialog::SetRectangle()
{
    CRect tabRect, itemRect;
    int nX, nY, nXc, nYc;

    GetClientRect(&tabRect);
    GetItemRect(static_cast<int>(Tabs::songs), &itemRect);

    nX = itemRect.left;
    nY = itemRect.bottom + 1;
    nXc = tabRect.right - itemRect.left - 1;
    nYc = tabRect.bottom - nY - 1;

    m_pSongsTable->SetWindowPos(HWND_TOP, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
}

LRESULT CMainDialog::OnSize(UINT /*state*/, CSize /*Size*/)
{
    SetRectangle();
    SetMsgHandled(FALSE);
    return 0;
}

LRESULT CMainDialog::OnTcnSelchangeLibrarytab(int /*idCtrl*/, LPNMHDR /*pNMHDR*/, BOOL& /*bHandled*/)
{
    // TODO: Add your control notification handler code here
    // auto tab = static_cast<Tabs>(m_tabCtrl.GetCurSel());

    return 0;
}

HWND CMainDialog::get_wnd()
{
    return *this;
}

void CMainDialog::set_configuration(ui_element_config::ptr data)
{
    m_config = data;
}

ui_element_config::ptr CMainDialog::get_configuration()
{
    return m_config;
}

GUID CMainDialog::get_guid()
{
    return g_get_guid();
}

GUID CMainDialog::get_subclass()
{
    return g_get_subclass();
}

GUID CMainDialog::g_get_guid()
{
    // {934BF96D-CB16-4E07-9CCA-3D8D1BD3AF95}
    static const GUID guid =
    { 0x934bf96d, 0xcb16, 0x4e07,{ 0x9c, 0xca, 0x3d, 0x8d, 0x1b, 0xd3, 0xaf, 0x95 } };

    return guid;
}

const char * CMainDialog::g_get_description() 
{ 
    return "Google Music library viewer";
}

ui_element_config::ptr CMainDialog::g_get_default_configuration() 
{ 
    return ui_element_config::g_create_empty(g_get_guid()); 
}

void CMainDialog::g_get_name(pfc::string_base & out) 
{ 
    out = g_pluginName;
}

inline GUID CMainDialog::g_get_subclass() 
{ 
    return ui_element_subclass_media_library_viewers; 
}

} // namespace foo_gmusic
