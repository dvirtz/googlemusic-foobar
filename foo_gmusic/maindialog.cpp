#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
MSC_RESTORE_WARNINGS
#include "resource.h"
//#include "atlcontrols.h"

namespace foo_gmusic
{

class CMainDialog : public CDialogImpl<CMainDialog>
{
public:
    enum { IDD = IDD_LIBRARY };

    BEGIN_MSG_MAP(CMainDialog)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_CLOSE(OnClose);
    NOTIFY_HANDLER(IDC_LIBRARYTAB, TCN_SELCHANGE, OnTcnSelchangeLibrarytab)
    END_MSG_MAP()
private:

    BOOL OnInitDialog(CWindow, LPARAM);

    LRESULT CMainDialog::OnClose();

    CTabCtrl m_tabCtrl;

    enum class Tabs
    {
        playlists,
        mixes,
        artists,
        albums,
        songs,
        genres,
        count
    };
public:
    LRESULT OnTcnSelchangeLibrarytab(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
};

BOOL CMainDialog::OnInitDialog(CWindow, LPARAM)
{
    m_tabCtrl = GetDlgItem(IDC_LIBRARYTAB);
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
        m_tabCtrl.AddItem(tab);
    }

    ::ShowWindowCentered(*this, GetParent()); // Function declared in SDK helpers.
    return TRUE;
}

LRESULT CMainDialog::OnClose()
{
    DestroyWindow();

    return 0;
}

void RunMainDialog()
{
    try
    {
        // ImplementModelessTracking registers our dialog to receive dialog messages thru main app loop's IsDialogMessage().
        // CWindowAutoLifetime creates the window in the constructor (taking the parent window as a parameter) and deletes the object when the window has been destroyed (through WTL's OnFinalMessage).
        new CWindowAutoLifetime<ImplementModelessTracking<CMainDialog> >(core_api::get_main_window());
    }
    catch (std::exception const & e)
    {
        popup_message::g_complain("Dialog creation failure", e);
    }
}

LRESULT CMainDialog::OnTcnSelchangeLibrarytab(int /*idCtrl*/, LPNMHDR /*pNMHDR*/, BOOL& /*bHandled*/)
{
    // TODO: Add your control notification handler code here
    // auto tab = static_cast<Tabs>(m_tabCtrl.GetCurSel());

    return 0;
}

} // namespace foo_gmusic
