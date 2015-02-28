// Deleter.h

#pragma once

#include <vorbis/vorbisfile.h>


namespace Ogg {

struct OvfDeleter {
    void operator()(OggVorbis_File *ptr) {
        ov_clear(ptr);
        delete (ptr);
    }
};

} // namespace Ogg
