#pragma once

#include <functional>
#include <string>
#include <map>
#include <vector>

struct command {
    int min_parameter_count;
    int max_parameter_count;
    std::function<int(std::vector<std::string>)> function;
};

namespace fparser {
    class parser;
}

class fparser::parser {
    public:
        parser();
        ~parser();

        // Add a key and function pair with parameter counts to commands.
        // The function is used to determine if a given option for the command is valid.
        void add_command(std::string key, 
                         std::function<int(std::vector<std::string>)> function,
                         int min_parameter_count = 1, 
                         int max_parameter_count = 1
                        );

        // Parse the passed arguments.
        // Returns a map of command keys and integers returned by their respective functions.
        std::map<std::string, int> parse(int argc, char *argv[]);

    private:
        std::map<std::string, command> commands;
};
