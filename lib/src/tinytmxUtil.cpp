#include <cstdlib>
#include <algorithm>
#include <cctype>

#ifdef USE_MINIZ
#include "miniz.h"
#else

#include "zlib.h"

#endif

#include "tinytmxUtil.hpp"
#include "base64.h"

namespace tinytmx {

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    void Util::Trim(std::string &str) {
        trim(str);
    }



//
// trim from start (copying)
//    static inline std::string ltrim_copy(std::string s) {
//        ltrim(s);
//        return s;
//    }
//
// trim from end (copying)
//    static inline std::string rtrim_copy(std::string s) {
//        rtrim(s);
//        return s;
//    }
//
// trim from both ends (copying)
//    static inline std::string trim_copy(std::string s) {
//        trim(s);
//        return s;
//    }



    std::string Util::DecodeBase64(std::string const &str) {
        return base64_decode(str);
    }

    char *Util::DecompressGZIP(char const *data, uint32_t dataSize, uint32_t expectedSize) {
        uint32_t bufferSize = expectedSize;
        int ret;
        z_stream strm;
        char *out = (char *) malloc(bufferSize);

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.next_in = (Bytef *) data;
        strm.avail_in = dataSize;
        strm.next_out = (Bytef *) out;
        strm.avail_out = bufferSize;

        ret = inflateInit2(&strm, 15 + 32);

        if (ret != Z_OK) {
            free(out);
            return NULL;
        }

        do {
            ret = inflate(&strm, Z_SYNC_FLUSH);

            switch (ret) {
                case Z_NEED_DICT:
                case Z_STREAM_ERROR:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    free(out);
                    return NULL;
            }

            if (ret != Z_STREAM_END) {
                out = (char *) realloc(out, bufferSize * 2);

                if (!out) {
                    inflateEnd(&strm);
                    free(out);
                    return NULL;
                }

                strm.next_out = (Bytef *) (out + bufferSize);
                strm.avail_out = bufferSize;
                bufferSize *= 2;
            }
        } while (ret != Z_STREAM_END);

        if (strm.avail_in != 0) {
            free(out);
            return NULL;
        }

        inflateEnd(&strm);

        return out;
    }
}
