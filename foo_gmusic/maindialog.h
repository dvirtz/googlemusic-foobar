#pragma once
#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
MSC_RESTORE_WARNINGS
#include "resource.h"
#include <memory>
#include <array>

namespace foo_gmusic
{

class SongsTable;

class CMainDialog : public ui_element_instance, public CWindowImpl<CMainDialog, CTabCtrl>
{
public:
    // ATL window class declaration. Replace class name with your own when reusing code.
    DECLARE_WND_CLASS_EX(_T("Google Music Main Dialog"), CS_VREDRAW | CS_HREDRAW, (-1));

    void initialize_window(HWND parent) { WIN32_OP(Create(parent, 0, 0, 0, WS_EX_STATICEDGE) != NULL); }

    CMainDialog(ui_element_config::ptr p_config, ui_element_instance_callback_ptr p_callback);

    BEGIN_MSG_MAP(CMainDialog)
        MESSAGE_HANDLER(WM_CREATE, OnCreate);
        NOTIFY_HANDLER(IDC_LIBRARYTAB, TCN_SELCHANGE, OnTcnSelchangeLibrarytab)
        MSG_WM_SIZE(OnSize)
    END_MSG_MAP()
    
    LRESULT OnTcnSelchangeLibrarytab(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

    virtual HWND get_wnd() override;

    virtual void set_configuration(ui_element_config::ptr data) override;

    virtual ui_element_config::ptr get_configuration() override;

    virtual GUID get_guid() override;

    virtual GUID get_subclass() override;

    static GUID g_get_guid();

    static const char * g_get_description();

    static ui_element_config::ptr g_get_default_configuration();

    static void g_get_name(pfc::string_base & out);

    static GUID g_get_subclass();
protected:

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void SetRectangle();

    LRESULT OnSize(UINT state, CSize Size);
    
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

    ui_element_config::ptr m_config;
    
    std::unique_ptr<SongsTable> m_pSongsTable;

    // this must be declared as protected for ui_element_impl_withpopup<> to work.
    const ui_element_instance_callback_ptr m_callback;
};

} // namespace foo_gmusic