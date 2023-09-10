#include <iostream>
#include <string>
#include <string_view>
#include <map>

#include "CommandHandler.h"
#include "FinderTXT.h"


const std::map<std::string, Extensions> MAPS{
        {"txt", Extensions::TXT}
};

int main(int argc, char *argv[]) {
//    FinderTXT finderTxt("abaptiston", "./words1.txt");
//    finderTxt.print();
//
//
//    return 0;
    if (argc != 4) {
        std::cout << "Command counts is not correct!" << std::endl;
        return 1;
    } else {

        const std::string_view WORD = argv[1];
        if (MAPS.find(argv[2]) == MAPS.end()) {
            std::cout << "Extension is not correct! " << std::endl;
            return 1;
        };
        const std::string_view PATH = argv[3];
        std::cout << "If you want to save result to answer.json enter Y :" << std::endl;
        char ch;
        std::cin >> ch;
        std::string answerJSON;
        if (ch == 'Y') answerJSON = "./answerJSON";

        // Start Commands
        CommandHandler commandHandler(WORD, MAPS.find(argv[2])->second, PATH);

        commandHandler.start(answerJSON);


    }

    return 0;
}