#include <iostream>
#include <string>
#include <fstream>

#include <re2/re2.h>
#include <emlio/mime.hpp>

int main(int, const char *argv[]) {
    std::string content;
    std::ifstream ifs(argv[1], std::ios::ate);
    content.resize(ifs.tellg());
    ifs.seekg(0);
    ifs.read(content.data(), content.size());

    RE2::Options options;
    options.set_case_sensitive(false);

    RE2 url_regex(R"((https?://[\w\-.~!*'();:@&=+$,/?%#\[\]]+))");

    emlio::mime mime;
    mime.line_policy(emlio::codec::line_len_policy_t::MANDATORY, emlio::codec::line_len_policy_t::MANDATORY);

    mime.parse(content);
    for (const auto &m : mime.parts()) {
        re2::StringPiece input(m.content());
        std::string url;
        while (RE2::FindAndConsume(&input, url_regex, &url)) {
            std::cout << url << std::endl;
        }
    }

    return 0;
}