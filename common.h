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
        char buf[8] = {0};
        std::snprintf(buf, sizeof(buf), "$%.4X", n);

        return buf;
    }

    inline std::string to_hex(size_t n)
    {
        char buf[8] = {0};
        std::snprintf(buf, sizeof(buf), "$%.4zX", n);

        return buf;
    }

    inline std::string to_hex(uint16_t n1, uint16_t n2)
    {
        // flip the byte order
        uint16_t result = n1 | (n2 << 8);

        return to_hex(result);
    }

    inline std::string justify(size_t len, const std::string& s1, const std::string& s2)
    {
        const size_t total_length = s1.length() + s2.length();

        const size_t pad_length = total_length > len ? 4 : len - total_length;

        const std::string pad(pad_length, ' ');

        return s1 + pad + s2;
    }

}

