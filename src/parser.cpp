
#include "parser.h"

#include <functional>
#include <string>
#include <map>
#include <vector>

#include <iostream>

using namespace fparser;

parser::parser() {

}

parser::~parser() {

}

void parser::add_command(std::string key, 
                         std::function<int(std::vector<std::string>)> function, 
                         int min_parameter_count, 
                         int max_parameter_count
                        ) {
    this->commands.insert({key, {min_parameter_count, max_parameter_count, function}});
}

std::map<std::string, int> parser::parse(int argc, char *argv[]) {
    std::map<std::string, int> results;

    for (int i = 0; i + 1 != argc; i++) {
        
        std::string key(argv[i]);
        if (this->commands.contains(key)) {
            command cmnd = this->commands[key];
            std::vector<std::string> parameters;

            // Parse parameters into vector parameters
            for (int j = 0; j < cmnd.max_parameter_count; j++) {

                // Quit if the command's max parameter count goes beyond the argument count
                if (i+j+1 >= argc) {break;} 

                std::string parameter(argv[i+j+1]);

                // Quit if the current argument is a key
                if (this->commands.contains(parameter)) {break;}

                parameters.push_back(parameter);
            }

            // Return empty map if a command has too few arguments
            if (parameters.size() < cmnd.min_parameter_count) {
                std::cout << "Invalid number of arguments for command " 
                          << key 
                          << " (Minimum of " 
                          << cmnd.min_parameter_count 
                          << ")." 
                          << std::endl;
                return {};
            } 

            results.insert({key, this->commands[key].function(parameters)});
        }
    }

    return results;
}
