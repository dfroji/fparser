#pragma once

#include <functional>
#include <string>
#include <map>

struct command {
    std::string key;
    std::function<int(std::string)> function;
};

namespace fparser {
    class parser;
}

class fparser::parser {
    public:
        parser();
        ~parser();

        // Add a key and function pair to commands.
        // The function is used to determine if a given option for the command is valid.
        void add_command(std::string key, std::function<int(std::string)> function);

        // Parse the passed arguments.
        // Returns a map of command keys and integers returned by their respective functions.
        std::map<std::string, int> parse(int argc, char *argv[]);

    private:
        std::map<std::string, std::function<int(std::string)>> commands;
};
