#pragma once

#include <functional>
#include <string>
#include <map>
#include <vector>

namespace fparser {
    class Parser;
    using Function = std::function<std::vector<std::string>(std::vector<std::string>)>;
}

struct command {
    fparser::Function function;
    int min_parameter_count;
    int max_parameter_count;
};

class fparser::Parser {
    public:
        Parser();
        ~Parser();

        // Add a key and function pair with parameter counts to commands.
        // The function is used to determine if a given option for the command is valid.
        void add_command(std::string key, 
                         fparser::Function function,
                         int min_parameter_count = 1, 
                         int max_parameter_count = 1
                        );

        // Parse the passed arguments.
        // Returns a map of command keys and vectors returned by their respective functions.
        std::map<std::string, std::vector<std::string>> parse(int argc, char *argv[]);

    private:
        std::map<std::string, command> commands;
};
