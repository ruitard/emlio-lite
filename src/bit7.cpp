/*

bit7.cpp
--------

Copyright (C) 2016, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/

#include <string>
#include <vector>
#include "bit7.hpp"

using std::string;
using std::vector;

namespace emlio {

// TODO: is it possible to apply seven bit encoding to latin1 charset?
vector<string> bit7::encode(const string &text) const {
    vector<string> enc_text;
    string line;
    string::size_type line_len = 0;
    for (auto ch = text.begin(); ch != text.end(); ch++) {
        if (is_allowed(*ch)) {
            line += *ch;
            line_len++;
        } else if (*ch == '\r' && (ch + 1) != text.end() && *(ch + 1) == '\n') {
            enc_text.push_back(line);
            line.clear();
            line_len = 0;
            // skip both crlf characters
            ch++;
        } else {
            throw codec_error("Bad character `" + string(1, *ch) + "`.");
        }

        if (line_len == string::size_type(line_policy_)) {
            enc_text.push_back(line);
            line.clear();
            line_len = 0;
        }
    }
    if (!line.empty()) {
        enc_text.push_back(line);
    }
    while (!enc_text.empty() && enc_text.back().empty()) {
        enc_text.pop_back();
    }
    return enc_text;
}

string bit7::decode(const vector<string> &text) const {
    string dec_text;
    for (const auto &line : text) {
        if (line.length() > string::size_type(decoder_line_policy_)) {
            throw codec_error("Line policy overflow.");
        }
        for (auto ch : line) {
            if (!is_allowed(ch)) {
                throw codec_error("Bad character `" + string(1, ch) + "`.");
            }
            dec_text += ch;
        }
        dec_text += "\r\n";
    }
    trim_right(dec_text);

    return dec_text;
}

/*
For details see [rfc 2045, section 2.7].
*/
bool bit7::is_allowed(char ch) const {
    if (strict_mode_) {
        return (ch > NIL_CHAR && ch <= TILDE_CHAR && ch != CR_CHAR && ch != LF_CHAR);
    }
    return (ch != NIL_CHAR && ch != CR_CHAR && ch != LF_CHAR);
}

} // namespace emlio
