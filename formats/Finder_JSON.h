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
   struct Answer_JSON {
       std::string fileName_;
       std::string finding_word_;
       size_t count_;
       Ans

   }answer_{};
    json parse_;
    void finder() {

    }
public:
    FinderJSON(const std::string& finding_word, std::ifstream&file_name) : answer_.finding_word_(finding_word) , parse_(json::parse(file_name)) {}



};