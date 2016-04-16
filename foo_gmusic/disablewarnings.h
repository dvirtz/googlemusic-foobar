#pragma once

#ifdef _MSC_VER
#define MSC_DISABLE_WARNINGS \
__pragma(warning(push, 0))
#define MSC_DISABLE_SPECIFIC_WARNING(number)\
__pragma(warning(push))\
__pragma(warning(disable:number))
#define MSC_RESTORE_WARNINGS \
__pragma(warning(pop))
#else
#define MSC_DISABLE_WARNINGS
#define MSC_DISABLE_SPECIFIC_WARNING(number)
#define MSC_RESTORE_WARNINGS
#endif // MSC_VER
