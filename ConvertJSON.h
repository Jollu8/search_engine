//
// Created by Jollu Emil on 10.09.2023.
//

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "Answer.h"

using json = nlohmann::json;


class ConvertJSON {
    std::vector<Answer> results_;

public:
    void insert(Answer &&answer) {
        results_.emplace_back(answer);
    }

    void save_to_json(const std::string fileJSON) {
        json answer;

        for (const auto &res: results_) {
            if (res.result) {
                answer[res.fileName]["result"] = res.result;
                answer[res.fileName]["finding"] = res.count;
            } else answer[res.fileName]["result"] = res.result;
        }

        std::ofstream file(fileJSON);
        file << answer.dump(4); // 4 - это количество пробелов для отступа
    }

    void print_results() {
        std::cout << std::left << std::setw(20) << "File Name"
                  << std::setw(10) << "Count"
                  << std::setw(10) << "Result" << std::endl;

        for (const auto &res: results_) {
            std::cout << std::left << std::setw(20) << res.fileName
                      << std::setw(10) << res.count
                      << std::setw(10) << std::boolalpha << res.result
                      << std::endl;
        }
    }

};