cmake_minimum_required(VERSION 3.23)
include(FetchContent)

project(finderSkillBox)

set(CMAKE_CXX_STANDARD 20)



FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        GIT_TAG v3.11.2)

FetchContent_MakeAvailable(json)

add_executable(finderSkillBox main.cpp)
target_link_libraries(finderSkillBox PRIVATE nlohmann_json::nlohmann_json)
