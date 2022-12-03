#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<std::string> parseInput(std::ifstream &input){
    std::vector<std::string> output;
    std::string line;
    while(input >> line){
        output.push_back(line);
    }
    return output;
}

std::uint64_t calculatePriorities(const std::vector<std::string>& rucksackItems){
    std::uint64_t priorities = 0;
    for(const auto &eachItem: rucksackItems){
        // length of eachItem is always even so mid can be found by diving with 2
        size_t mid = eachItem.size() / 2;
        
        // find element in the first half that is also present in the second half
        auto it = find_if(eachItem.begin(), eachItem.begin() + mid, [&](char item){
            return eachItem.substr(mid, mid).find(item) != std::string::npos;
        });

        if(it != eachItem.end()){
            if(*it >= 'a' && *it <= 'z'){
                priorities += *it - 'a' + 1;
            }
            else {
                priorities += *it - 'A' + 27;
            }
        }
    }

    return priorities;
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Wrong number of parameters \n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if(!input.is_open()){
        std::cerr << "Failed to open file \n";
        return 1;
    }
    
    std::vector<std::string> strategyLines = parseInput(input);
    std::cout << "Result is: " << calculatePriorities(strategyLines);

    return 0;
}