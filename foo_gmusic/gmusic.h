#pragma once
#include <memory>

namespace GMusicApi
{
class Module;
class Mobileclient;
class SongRange;
}

namespace foo_gmusic
{

class GMusic
{
public:
    void init();
    void login();
    GMusicApi::SongRange songs(bool incremental = false, bool include_deleted = false);

private:
    std::unique_ptr<GMusicApi::Module>          m_module;
    std::unique_ptr<GMusicApi::Mobileclient>    m_client;
    bool                                        m_isLoggedIn;
};

extern GMusic g_gmusic;

} // namespace foo_gmusic