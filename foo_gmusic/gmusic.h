#pragma once
#include <memory>
#include <string>
#include <vector>
#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "foobar2000.h"
MSC_RESTORE_WARNINGS

namespace GMusicApi
{
class Module;
class Mobileclient;
struct Song;
}

namespace foo_gmusic
{

class GMusic
{
public:
    void init();
    void login();
    std::vector<metadb_handle_ptr> songs(bool include_deleted = false);

private:
    std::string streamUrl(const GMusicApi::Song& song);

private:
    std::unique_ptr<GMusicApi::Module>          m_module;
    std::unique_ptr<GMusicApi::Mobileclient>    m_client;
    bool                                        m_isLoggedIn;
};

extern GMusic g_gmusic;

} // namespace foo_gmusic