

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <future>
#include "ConvertJSON.h"

namespace fs = std::filesystem;


class SearchEngine {
    std::vector<std::string> files_;
    const std::string finding_;
    ConvertJSON convertJson;

    void getFiles(const std::string_view path) {
        for (auto &p: fs::directory_iterator(path)) {
            if (p.path().extension() == ".txt") files_.emplace_back(p.path());
        }
    }

    void parsTXTFiles() {
        std::vector<std::future<Answer>> futures;
        for (auto &file_name: files_) {
            futures.push_back(std::async(std::launch::async, [this, &file_name] {
                FinderTXT finderTxt(finding_, file_name);
                return finderTxt.sent_answer();
            }));
        }
        for (auto &fut: futures) {
            Answer ans = fut.get();
            convertJson.insert(std::move(ans));
        }
    }


public:
    SearchEngine(const std::string_view word, const std::string_view path) : finding_(word) {
        getFiles(path);
    }

    void startTXT(const std::string &jsonFile) {
        parsTXTFiles();
        if (jsonFile.empty()) convertJson.print_results();
        else convertJson.save_to_json(jsonFile);
    }


};


