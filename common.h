#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>

#define GBDSM_UNUSED(x) (void)x

namespace gbdsm {

    enum class DisassemblerAlgo {

        LINEAR_SWEEP,
        RECURSIVE_SEARCH

    };

    template <class... Args>
    inline void error(const char *msg, Args&&... args)
    {
        std::fprintf(stderr, msg, std::forward<Args>(args)...);
    }

    inline void error(const char *msg)
    {
        std::fputs(msg, stderr);
    }

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

    template <class N>
    inline std::string to_hex(N n)
    {
        std::string buf;
        while (n != 0) {
            int d = n % 16;
            char c = "0123456789ABCDEF"[d];
            buf.push_back(c);
            n /= 16;
        }
        buf.push_back('$');
        std::reverse(buf.begin(), buf.end());

        return buf;
    }

    inline std::string to_hex(uint16_t n1, uint16_t n2)
    {
        // flip the byte order
        uint16_t result = n1 | (n2 << 8);

        return to_hex(result);
    }

}

