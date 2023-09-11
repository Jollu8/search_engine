#include <iostream>
#include <algorithm>
#include <vector>
#include <string_view>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"
#include "../utilites/Answer.h"
#include "../main/Abstract.h"

using json = nlohmann::json;


class FinderJSON : public Abstract {
    Answer answer_;
    std::string finding_word_;
    json parse_;
    struct parse_JSON {
        bool key_JSON_;
        std::vector<std::pair<std::string, std::string> > value_JSON_;

    } parseJson_;

    void finder() {
        if (parse_.contains(finding_word_)) parseJson_.key_JSON_ = true;
        for (auto &it: parse_.items()) {
            if (it.value() == finding_word_) {
                parseJson_.value_JSON_.emplace_back(it.key(), it.value());
                ++answer_.count;
            }
        }
    }

public:
    FinderJSON(const std::string &finding_word, std::string &file_name) {
        answer_.count = 0;
        answer_.fileName = file_name;
        finding_word_ = finding_word;
        parse_ = json::parse(file_name);
    }

    Answer sent_answer_to_convert_JSON() override {
        finder();
        answer_.result = !parse_.empty();
        return answer_;
    }
};