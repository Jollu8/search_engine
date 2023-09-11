//
// Created by Jollu Emil on 09.09.2023.
//
#pragma once


#include <string_view>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>
#include <execution>

#include "../main/Abstract.h"
#include "../utilites/Answer.h"


class FinderTXT : public Abstract {
    Answer answer_;
    std::string finding_words;
    std::vector<std::string> words_;


    std::vector<std::string> get_sequence(const std::string &_file_name) {
        std::ifstream infile(_file_name);
        std::vector<std::string> result;

        std::vector<std::string>::value_type item;

        while (infile >> item) {
            result.emplace_back(item);
        }

        return result;
    }

    void finder() {
        answer_.count = std::count(words_.begin(), words_.end(), finding_words);
        answer_.result = answer_.count;


    }

    void reader(const std::string &_file_name) {
        words_ = get_sequence(_file_name);
        answer_.fileName = _file_name;
        finder();

    }

public:
    FinderTXT(const std::string &finding, const std::string &file_name) : finding_words(finding) {
        reader(file_name);
    }


    // Ending job
    Answer sent_answer_to_convert_JSON() override {
        return answer_;
    }

#ifdef NDEBUG
    void print()const override  {

        std::cout << "File : " << answer_.fileName << " result : " << answer_.result << " found : " << answer_.count <<std::endl;
//        for(auto i = 0; i < 10; i++) {
//            std::cout << words_[i] << "\n";
//        }
    }
#endif


};









