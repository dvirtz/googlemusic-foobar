#include "disableWarnings.h"
MSC_DISABLE_WARNINGS
#include "ATLHelpers.h"
#include "foobar2000.h"
#include "component.h"
MSC_RESTORE_WARNINGS
#include "GMusicInterface.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>

// Sample initquit implementation. See also: initquit class documentation in relevant header.

namespace foo_gmusic
{

class InitQuit : public ::initquit
{
    class info_update_completion : public completion_notify_receiver
    {};
public:
    void on_init()
    {
        GMusicInterface::instance().login();
    }
    void on_quit()
    {
        console::print("Sample component: on_quit()");
    }

private:
    info_update_completion m_infoUpdateCompletion;
};

static initquit_factory_t<InitQuit> g_initquit_factory;

} // namespace foo_gmusic