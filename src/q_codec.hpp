/*

q_codec.hpp
-----------

Copyright (C) 2017, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/

#pragma once

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

#include <string>
#include <vector>
#include <tuple>
#include <emlio/codec.hpp>

namespace emlio {

/**
Q codec.

ASCII and UTF-8 charsets are recognized.
**/
class q_codec : public codec {
public:
    /**
    Setting the encoder and decoder line policy to recommended one.

    @param encoder_line_policy  Line policy to apply.
    @param decoder_line_policy  Line policy to apply.
    @param codec_method Method for encoding/decoding.
    **/
    q_codec(codec::line_len_policy_t encoder_line_policy, codec::line_len_policy_t decoder_line_policy);

    q_codec(const q_codec &) = delete;

    q_codec(q_codec &&) = delete;

    /**
    Default destructor.
    **/
    ~q_codec() = default;

    void operator=(const q_codec &) = delete;

    void operator=(q_codec &&) = delete;

    /**
    Encoding a text by applying the given method.

    @param text    String to encode.
    @param charset Charset used by the string.
    @return        Encoded string.
    **/
    std::vector<std::string> encode(const std::string &text, const std::string &charset, header_codec_t method) const;

    /**
    Decoding a string.

    @param text        String to decode.
    @return            Decoded string, its charset and its codec method.
    @throw codec_error Missing Q codec separator for charset.
    @throw codec_error Missing Q codec separator for codec type.
    @throw codec_error Missing last Q codec separator.
    @throw codec_error Bad encoding method.
    @throw *           `decode_qp(const string&)`, `base64::decode(const string&)`.
    **/
    std::tuple<std::string, std::string, header_codec_t> decode(const std::string &text) const;

    /**
    Checking if a string is Q encoded and decodes it.

    @param text        String to decode.
    @return            Decoded string, its charset and its codec method.
    @throw codec_error Bad Q codec format.
    **/
    std::tuple<std::string, std::string, header_codec_t> check_decode(const std::string &text) const;

private:
    /**
    String representation of Base64 method.
    **/
    static const std::string BASE64_CODEC_STR;

    /**
    String representation of Quoted Printable method.
    **/
    static const std::string QP_CODEC_STR;

    /**
    Decoding by using variation of the Quoted Printable method.

    @param text String to decode.
    @return     Decoded string.
    @throw *    `quoted_printable::decode(const vector<string>&)`
    **/
    std::string decode_qp(const std::string &text) const;

    /**
    Checking if a character is allowed.

    @param ch Character to check.
    @return   True if allowed, false if not.
    **/
    bool is_q_allowed(char ch) const;

    /**
    Method used for encoding/decoding.
    **/
};

} // namespace emlio

#ifdef _MSC_VER
#pragma warning(pop)
#endif
