#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
MSC_RESTORE_WARNINGS
#include "gmusic.h"

// Sample initquit implementation. See also: initquit class documentation in relevant header.

namespace foo_gmusic
{

class InitQuit : public ::initquit
{
public:
    void on_init()
    {
        g_gmusic.init();
        g_gmusic.login();
    }
    void on_quit()
    {
        console::print("Sample component: on_quit()");
    }
};

static initquit_factory_t<InitQuit> g_initquit_factory;

} // namespace foo_gmusic