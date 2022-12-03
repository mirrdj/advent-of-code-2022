#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

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

    // find character present in all 3 strings in the group
    for(size_t i = 0; i < rucksackItems.size(); i += 3){
        auto commonCharacter = std::find_if(rucksackItems.at(i).begin(), rucksackItems.at(i).end(), [&](char item){
            return rucksackItems.at(i + 1).find(item) != std::string::npos && rucksackItems.at(i + 2).find(item) != std::string::npos;
        });

        // calculate priority
        if(commonCharacter != rucksackItems.at(i).end()){
            if(*commonCharacter >= 'a' && *commonCharacter <= 'z'){
                priorities += *commonCharacter - 'a' + 1;
            }
            else {
                priorities += *commonCharacter - 'A' + 27;
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