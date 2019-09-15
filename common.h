#pragma once

#include <cstdlib>
#include <cstdio>

namespace gbdsm {

    template <class... Args>
    inline void abort(const char *msg, Args&&... args)
    {
        std::fprintf(stderr, msg, std::forward<Args>(args)...);
        std::abort();
    }

    inline void abort(const char *msg)
    {
        std::fputs(msg, stderr);
        std::abort();
    }
}

