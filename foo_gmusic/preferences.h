#pragma once

#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
MSC_RESTORE_WARNINGS
#include "resource.h"

namespace foo_gmusic
{
// Sample preferences interface: two meaningless configuration settings accessible through a preferences page and one accessible through advanced preferences.
class CPreferences : public CDialogImpl<CPreferences>, public preferences_page_instance
{
public:
    //Constructor - invoked by preferences_page_impl helpers - don't do Create() in here, preferences_page_impl does this for us
    CPreferences(preferences_page_callback::ptr callback) : m_callback(callback) {}

    //Note that we don't bother doing anything regarding destruction of our class.
    //The host ensures that our dialog is destroyed first, then the last reference to our preferences_page_instance object is released, causing our object to be deleted.


    //dialog resource ID
    enum { IDD = IDD_PREFERENCES };
    // preferences_page_instance methods (not all of them - get_wnd() is supplied by preferences_page_impl helpers)
    t_uint32 get_state() override;
    void apply() override;
    void reset() override;
    
    static cfg_string cfg_user;
    static cfg_string cfg_password;

    //WTL message map
    BEGIN_MSG_MAP(CPreferences)
        MSG_WM_INITDIALOG(OnInitDialog)
        COMMAND_HANDLER_EX(IDC_USER, EN_CHANGE, OnEditChange)
        COMMAND_HANDLER_EX(IDC_PASSWORD, EN_CHANGE, OnEditChange)
    END_MSG_MAP()
private:
    BOOL OnInitDialog(CWindow, LPARAM);
    void OnEditChange(UINT, int, CWindow);
    bool HasChanged();
    void OnChanged();
    pfc::string8 ItemText(int item);

    // These GUIDs identify the variables within our component's configuration file.
    // {14101700-58C0-49C6-A0B2-D0B64A0496D2}
    static const GUID guid_cfg_user;
    // {0EB9A152-A6E1-4772-A49F-B5B74FA96730}
    static const GUID guid_cfg_password;

    static const pfc::string8 default_user;
    static const pfc::string8 default_pass;

    const preferences_page_callback::ptr m_callback;
};

class preferences_page_myimpl : public preferences_page_impl<CPreferences>
{
    // preferences_page_impl<> helper deals with instantiation of our dialog; inherits from preferences_page_v3.
public:
    const char * get_name() override { return "Google Music"; }
    GUID get_guid() override
    {
        // {E9BCE613-22F8-428E-BB06-B59714765B48}
        static const GUID guid =
        { 0xe9bce613, 0x22f8, 0x428e,{ 0xbb, 0x6, 0xb5, 0x97, 0x14, 0x76, 0x5b, 0x48 } };
        return guid;
    }
    GUID get_parent_guid() override { return guid_tools; }
};

extern ::preferences_page_factory_t<foo_gmusic::preferences_page_myimpl> g_preferences_page_myimpl_factory;
} // namespace foo_gmusic
