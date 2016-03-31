#include "preferences.h"
#include "utility.h"
#include "gmusic.h"

namespace foo_gmusic
{

// These GUIDs identify the variables within our component's configuration file.
// {14101700-58C0-49C6-A0B2-D0B64A0496D2}
const GUID CPreferences::guid_cfg_user = { 0x14101700, 0x58c0, 0x49c6,{ 0xa0, 0xb2, 0xd0, 0xb6, 0x4a, 0x4, 0x96, 0xd2 } };
// {0EB9A152-A6E1-4772-A49F-B5B74FA96730}
const GUID CPreferences::guid_cfg_password = { 0xeb9a152, 0xa6e1, 0x4772,{ 0xa4, 0x9f, 0xb5, 0xb7, 0x4f, 0xa9, 0x67, 0x30 } };

const pfc::string8 CPreferences::default_user = "user@gmail.com";
const pfc::string8 CPreferences::default_pass = "";

cfg_string CPreferences::cfg_user{ CPreferences::guid_cfg_user, CPreferences::default_user.c_str() };
cfg_string CPreferences::cfg_password{ CPreferences::guid_cfg_password, CPreferences::default_pass.c_str() };

BOOL CPreferences::OnInitDialog(CWindow, LPARAM)
{
    using detail::toTChar;

    SetDlgItemText(IDC_USER, toTChar(cfg_user.c_str()).data());
    SetDlgItemText(IDC_PASSWORD, toTChar(cfg_password.c_str()).data());

    return FALSE;
}

void CPreferences::OnEditChange(UINT, int, CWindow)
{
    // not much to do here
    OnChanged();
}

t_uint32 CPreferences::get_state()
{
    t_uint32 state = preferences_state::resettable;
    if (HasChanged()) state |= preferences_state::changed;
    return state;
}

void CPreferences::reset()
{
    using detail::toTChar;

    SetDlgItemText(IDC_USER, toTChar(default_user).data());
    SetDlgItemText(IDC_PASSWORD, toTChar(default_pass).data());
    OnChanged();
}

void CPreferences::apply()
{
    auto new_user = ItemText(IDC_USER);
    auto new_pass = ItemText(IDC_PASSWORD);

    if (cfg_user != new_user || cfg_password != new_pass)
    {
        cfg_user = new_user;
        cfg_password = new_pass;

        g_gmusic.login();
    }

    OnChanged(); //our dialog content has not changed but the flags have - our currently shown values now match the settings so the apply button can be disabled
}

bool CPreferences::HasChanged()
{
    //returns whether our dialog content is different from the current configuration (whether the apply button should be enabled or not)
    return ItemText(IDC_USER) != default_user || ItemText(IDC_PASSWORD) != default_pass;
}
void CPreferences::OnChanged()
{
    //tell the host that our state has changed to enable/disable the apply button appropriately.
    m_callback->on_state_changed();
}

pfc::string8 CPreferences::ItemText(int item)
{
    std::vector<TCHAR> temp(256);
    GetDlgItemText(item, temp.data(), temp.size());

    return{ detail::fromTChar(temp) };
}

::preferences_page_factory_t<foo_gmusic::preferences_page_myimpl> g_preferences_page_myimpl_factory;

} // namespace foo_gmusic