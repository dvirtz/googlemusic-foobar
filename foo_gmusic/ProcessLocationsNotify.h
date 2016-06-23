#pragma once
#include "disablewarnings.h"
MSC_DISABLE_WARNINGS
#include "foobar2000.h"
MSC_RESTORE_WARNINGS
#include "SongInfo.h"
#include <vector>

namespace foo_gmusic
{

class ProcessLocationsNotify : public process_locations_notify
{
public:
    ProcessLocationsNotify(const std::vector<SongInfo>& songs);

    virtual void on_completion(const pfc::list_base_const_t<metadb_handle_ptr> & p_items) override;

    virtual void on_aborted() override {};

private:

    class callback : public play_callback_impl_base
    {
        using play_callback_impl_base::play_callback_impl_base;
        void on_playback_dynamic_info(const file_info & /*p_info*/) { }
        void on_playback_dynamic_info_track(const file_info & /*p_info*/) { }
    };

    std::vector<SongInfo> m_songs;
    callback m_callback;
};
} // namespace foo_gmusic