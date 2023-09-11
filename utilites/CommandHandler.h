//
// Created by Jollu Emil on 07.09.2023.
//

#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include <filesystem>
#include <string_view>

#include "../formats/FinderTXT.h"
#include "SearchEngine.h"

enum class Extensions {
    TXT
};


class CommandHandler {
    std::string word_;
    Extensions extension_;
    std::string path_;

public:

    CommandHandler(const std::string_view word, Extensions extension, const std::string_view path) :
            word_(word),
            extension_(extension),
            path_(path) {}

    void start(const std::string& jsonfFile) {
        switch (extension_) {
            case Extensions::TXT: {
                SearchEngine searchEngine(word_, path_);
                searchEngine.startTXT(jsonfFile);
            }
        }
    }


};