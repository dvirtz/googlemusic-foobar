#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "disablewarnings.h"

MSC_DISABLE_WARNINGS
#include <Windows.h>
MSC_RESTORE_WARNINGS


namespace foo_gmusic
{

namespace detail
{
inline std::vector<TCHAR> toTChar(const pfc::string8& text)
{
#ifdef  UNICODE
    size_t requiredSize;
    mbstowcs_s(&requiredSize, nullptr, 0, text.c_str(), text.get_length());

    auto res = std::vector<TCHAR>(requiredSize + 1);
    mbstowcs_s(nullptr, res.data(), res.size(), text.c_str(), text.get_length());
#else
    auto res = std::vector<TCHAR>(text.size());
    std::copy(text.begin(), text.end(), res.begin());
#endif
    return res;
}

inline pfc::string8 fromTChar(const std::vector<TCHAR>& text)
{
#ifdef UNICODE
    std::vector<char> chars(text.size() / sizeof(TCHAR));
    wcstombs_s(nullptr, chars.data(), chars.size(), text.data(), _TRUNCATE);
    return{ chars.data(), chars.size() };
#else
    return{ text.data(), test.size() };
#endif
}

} // namespace detail

} // namespace foo_gmusic