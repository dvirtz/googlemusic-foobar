#include "disableWarnings.h"
MSC_DISABLE_WARNINGS
#include "foobar2000.h"
MSC_RESTORE_WARNINGS
#include "genDefs.h"

namespace foo_gmusic
{

const pfc::string8 g_pluginName = "Google Music";

DECLARE_COMPONENT_VERSION(g_pluginName, "1.0", "enables listening to Google Music(TM) songs on Foobar2000");

VALIDATE_COMPONENT_FILENAME("foo_gmusic.dll");

} // namespace foo_gmusic