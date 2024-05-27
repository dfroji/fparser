
#include "parser.h"

#include <functional>
#include <string>
#include <map>

using namespace fparser;

parser::parser() {

}

parser::~parser() {

}

void parser::add_command(std::string key, std::function<int(std::string)> function) {
    this->commands.insert({key, function});
}

std::map<std::string, int> parser::parse(int argc, char *argv[]) {
    std::map<std::string, int> results;

    for (int i = 0; i + 1 != argc; i++) {

        std::string key(argv[i]);
        std::string parameter(argv[i+1]);
        if (this->commands.contains(key)) {
            results.insert({key, this->commands[key](parameter)});
        }
    }

    return results;
}
