# fparser

A rudimentary single class c++ library for generalizing command-line input parsing.

## How to use

The fparser::Parser class has the member function add_command(), for which one can pass the key of the command (e.g. -i) as a string, and a lambda function that takes a vector of strings as a parameter and returns a vector of strings. The lambda is used to determine whether or not the arguments are valid. The add_command() function can also be passed integers for the number of arguments the command should or can have (these default to 1).

After adding the commands to the fparser::Parser object, one can call the member function parse(int argc, char* argv[]), which will return a map where the keys are keys of the commands, and the values are the vectors returned by the lambda functions of the commands.

### Example

Considering the following main.cpp:
```
#include "parser.h"

#include <iostream>
#include <functional>
#include <set>

int main(int argc, char* argv[]) {

    const std::set<std::string> OPTIONS = {"add", "delete", "sort"};

    fparser::Parser parser = fparser::Parser();
    parser.add_command(
        "-a", // the key of the command

        // the lambda function
        [OPTIONS](std::vector<std::string> parameters) {
            for (const auto& parameter : parameters) {
                if (OPTIONS.contains(parameter)) {return std::vector<std::string>{parameter};}
            }

            std::cout << "Error: argument should be one of:" << std::endl;
            for (const auto& option : OPTIONS) {
                std::cout << option << std::endl;
            }

            return std::vector<std::string>{};
        },
        1, 1 // min and max argument count for the command
    );

    fparser::Map results = parser.parse(argc, argv);

    if (results.empty() || results["-a"].empty()) {return 1;}

    return 0;
}
```
The following invocations would cause results as such:
```
./program -a add

(results = -a: add)
(return 0)
```
```
./program -a add delete

(results = -a: add, as the max is 1, the parser will ignore delete)
(return 0)
```
```
./program -a remove

Error: argument should be one of:
add
delete
sort

(results = -a: {}, as the lambda returned an empty vector)
(return 1)
```
```
./program -a

Invalid number of arguments for command -a (Minimum of 1).

(results = {}, as the parse function returned an empty map)
(return 1)
```

## Including with CMake