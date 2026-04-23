#include "tinyxml2.h"

#ifdef USE_MINIZ
#include "miniz.h"
#else
#include <zlib.h>
#endif

#include <zstd.h>

#include "tinytmxImage.hpp"
#include "tinytmxUtil.hpp"

namespace tinytmx
{   
    Image::Image(tinyxml2::XMLNode const *imageNode)
        : width(0)
        , height(0)
        , transparent_color() {
        Parse(imageNode);
    }


    void Image::Parse(tinyxml2::XMLNode const *imageNode)
    {
        tinyxml2::XMLElement const *imageElem = imageNode->ToElement();
        
        // Read all the attributes into member variables.
        if (char const *sourceAttr = imageElem->Attribute("source")) {
            source = sourceAttr;
        }

        if (char const *formatAttr = imageElem->Attribute("format")) {
            format = formatAttr;
        }

        width = imageElem->UnsignedAttribute("width");
        height = imageElem->UnsignedAttribute("height");

        char const *trans = imageElem->Attribute("trans");
        if (trans) 
        {
            transparent_color = tinytmx::Color(trans);
        }

        // Parse optional embedded <data> child element.
        tinyxml2::XMLElement const *dataElem = imageElem->FirstChildElement("data");
        if (dataElem) {
            if (char const *encAttr = dataElem->Attribute("encoding")) {
                encoding = encAttr;
            }
            if (char const *compAttr = dataElem->Attribute("compression")) {
                compression = compAttr;
            }

            // Per spec, "csv" encoding is only valid for tile layer data; image
            // data only supports "base64" or no encoding at all.
            if (!encoding.empty() && encoding != "base64") {
                parse_error = "embedded image: unsupported encoding '" + encoding + "'";
                return;
            }

            char const *text = dataElem->GetText();
            if (text) {
                std::string payload(text);
                Util::Trim(payload);

                // Decode base64 if needed.
                if (encoding == "base64") {
                    payload = Util::DecodeBase64(payload);
                }

                // Decompress if needed.
                if (compression == "zlib" || compression == "gzip") {
                    // Use streaming inflate for both zlib and gzip.
                    // windowBits: 15 for zlib, 15+16 for gzip auto-detection.
                    int windowBits = (compression == "gzip") ? (15 + 16) : 15;

                    z_stream strm{};
                    // const_cast is safe: zlib's next_in is non-const but inflate does not modify the input.
                    strm.next_in = const_cast<Bytef *>(reinterpret_cast<Bytef const *>(payload.data()));
                    strm.avail_in = static_cast<uInt>(payload.size());

                    int ret = inflateInit2(&strm, windowBits);
                    if (ret != Z_OK) {
                        parse_error = "embedded image: inflateInit2 failed (zlib error " + std::to_string(ret) + ")";
                        return;
                    }

                    std::vector<unsigned char> buf;
                    std::size_t chunk = (payload.size() < 256) ? 1024 : payload.size() * 4;
                    buf.resize(chunk);

                    strm.next_out = buf.data();
                    strm.avail_out = static_cast<uInt>(buf.size());

                    do {
                        ret = inflate(&strm, Z_NO_FLUSH);
                        if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR
                            || ret == Z_MEM_ERROR || ret == Z_NEED_DICT
                            || ret == Z_BUF_ERROR) {
                            inflateEnd(&strm);
                            parse_error = "embedded image: inflate failed (zlib error " + std::to_string(ret) + ")";
                            return;
                        }
                        if (strm.avail_out == 0 && ret != Z_STREAM_END) {
                            std::size_t old_size = buf.size();
                            buf.resize(old_size * 2);
                            strm.next_out = buf.data() + old_size;
                            strm.avail_out = static_cast<uInt>(old_size);
                        }
                    } while (ret != Z_STREAM_END);

                    if (strm.avail_in != 0) {
                        inflateEnd(&strm);
                        parse_error = "embedded image: trailing data after compressed stream";
                        return;
                    }

                    buf.resize(strm.total_out);
                    inflateEnd(&strm);
                    raw_data = std::move(buf);

                } else if (compression == "zstd") {
                    size_t const frameSize = ZSTD_getFrameContentSize(payload.data(), payload.size());
                    size_t outlen = (frameSize != ZSTD_CONTENTSIZE_UNKNOWN && frameSize != ZSTD_CONTENTSIZE_ERROR)
                                    ? frameSize
                                    : payload.size() * 4;
                    if (outlen < 256) { outlen = 256; }
                    std::vector<unsigned char> buf(outlen);
                    size_t const result = ZSTD_decompress(buf.data(), buf.size(),
                                                          payload.data(), payload.size());
                    if (ZSTD_isError(result)) {
                        parse_error = std::string("embedded image: zstd decompression failed (")
                                    + ZSTD_getErrorName(result) + ")";
                        return;
                    }
                    buf.resize(result);
                    raw_data = std::move(buf);

                } else if (compression.empty()) {
                    // No compression — payload is already raw bytes.
                    raw_data.assign(reinterpret_cast<unsigned char const *>(payload.data()),
                                    reinterpret_cast<unsigned char const *>(payload.data()) + payload.size());
                } else {
                    parse_error = "embedded image: unsupported compression '" + compression + "'";
                }
            }
        }
    }
}
