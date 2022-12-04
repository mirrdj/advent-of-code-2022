#include <string>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> parseInput(std::ifstream &input){
    std::vector<std::string> output;
    std::string line;
    while(input >> line){
        output.push_back(line);
    }
    return output;
}

std::uint64_t countFullyContainedPairs(const std::vector<std::string>& pairs){
    uint64_t count = 0;
    for(const auto& eachPair: pairs){
        auto pos = eachPair.find(",");
        
        std::string firstPair = std::string(eachPair.begin(), eachPair.begin() + pos);
        std::string secondPair = std::string(eachPair.begin() + pos + 1, eachPair.end());
        std::string minFirst =  std::string(firstPair.begin(), firstPair.begin() + firstPair.find("-"));
        std::string maxFirst = std::string(firstPair.begin() + firstPair.find("-") + 1, firstPair.end());
        std::string minSecond =  std::string(secondPair.begin(), secondPair.begin() + secondPair.find("-"));
        std::string maxSecond = std::string(secondPair.begin() + secondPair.find("-") + 1, secondPair.end());

        if((std::stoull(maxSecond) >= std::stoull(minFirst) && std::stoull(maxSecond) <= std::stoull(maxFirst)) || 
            (std::stoull(minSecond) >= std::stoull(minFirst) && std::stoull(minSecond) <= std::stoull(maxFirst)) ||
            (std::stoull(minFirst) >= std::stoull(minSecond) && std::stoull(minFirst) <= std::stoull(maxSecond)) ||
            (std::stoull(maxFirst) >= std::stoull(minSecond) && std::stoull(maxFirst) <= std::stoull(maxSecond))){
                std::cout << minFirst << ' ' << maxFirst << " " << minSecond << " " << maxSecond << '\n';
                count++;
        }
    }

    return count;
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
    std::cout << "Result is: " << countFullyContainedPairs(strategyLines);

    return 0;
}