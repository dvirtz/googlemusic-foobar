#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "foobar2000.h"
MSC_RESTORE_WARNINGS

// {0344E4E3-07A3-4E86-9535-A5E5259E1402}
static const GUID g_foo_gmusic_menu_group_id =
{ 0x344e4e3, 0x7a3, 0x4e86,{ 0x95, 0x35, 0xa5, 0xe5, 0x25, 0x9e, 0x14, 0x2 } };

static mainmenu_group_popup_factory g_mainmenu_group(g_foo_gmusic_menu_group_id, 
                                                     mainmenu_groups::file, 
                                                     static_cast<t_uint32>(mainmenu_commands::sort_priority_dontcare), 
                                                     "Google Music");

namespace foo_gmusic
{

extern void RunMainDialog();

class menu_commands : public mainmenu_commands
{
public:
    t_uint32 get_command_count()
    {
        return from_command(commands::count);
    }
    GUID get_command(t_uint32 p_index)
    {
        // {CDF0E35F-9609-48E2-93CE-8E4A1F21093C}
        static const GUID guid_library =
        { 0xcdf0e35f, 0x9609, 0x48e2,{ 0x93, 0xce, 0x8e, 0x4a, 0x1f, 0x21, 0x9, 0x3c } };
        switch (to_command(p_index))
        {
            case commands::library: return guid_library;
            default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
        }
    }
    void get_name(t_uint32 p_index, pfc::string_base & p_out)
    {
        switch (to_command(p_index))
        {
            case commands::library: p_out = "My Library"; break;
            default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
        }
    }
    bool get_description(t_uint32 p_index, pfc::string_base & p_out)
    {
        switch (to_command(p_index))
        {
            case commands::library: p_out = "Show library"; break;
            default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
        }

        return true;
    }
    GUID get_parent()
    {
        return g_foo_gmusic_menu_group_id;
    }
    void execute(t_uint32 p_index, service_ptr_t<service_base> p_callback)
    {
        switch (to_command(p_index))
        {
            case commands::library: RunMainDialog(); break;
            default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
        }
    }

private:
    enum class commands : t_uint32
    {
        library,
        count
    };

    t_uint32 from_command(commands command)
    {
        return static_cast<t_uint32>(command);
    }

    commands to_command(t_uint32 index)
    {
        return static_cast<commands>(index);
    }
};

} // namespace foo_gmusic


static mainmenu_commands_factory_t<foo_gmusic::menu_commands> g_foo_gmusic_menu_commands_factory;