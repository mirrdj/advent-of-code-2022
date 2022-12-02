#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<std::string> parseInput(std::ifstream &input){
    std::vector<std::string> output;
    std::string line;
    while(input){
        std::getline(input, line);
        output.push_back(line);
    }
    output.pop_back();
    return output;
}


int calculateScore(const std::vector<std::string>& strategyLines){
    int totalScore = 0;
    std::vector<std::pair<int, int>> winningPairs{
        std::pair<int, int>{1, 3}, 
        std::pair<int, int>{2, 1}, 
        std::pair<int, int>{3, 2}
    };

    for(const auto eachLine: strategyLines){
        switch(eachLine[2]){
            // find shape value that leads to loose
            case 'X':{
                    auto itLoose = find_if(winningPairs.begin(), winningPairs.end(), [&](auto pair){
                        return eachLine[0] - 'A' + 1 == pair.first;
                    });
                    totalScore += itLoose->second;
                }
                break;
            // find shape value that leads to draw
            case 'Y':
                totalScore += eachLine[0] - 'A' + 1;
                totalScore += 3;
                break;
            // find shape value that leads to win
            case 'Z':{
                    totalScore += 6;
                    auto itWin = find_if(winningPairs.begin(), winningPairs.end(), [&](auto pair){
                        return eachLine[0] - 'A' + 1 == pair.second;
                    });
                    totalScore += itWin->first;
                }
                break;
        }
    }

    return totalScore;
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
    std::cout << "Result is: " << calculateScore(strategyLines);

    return 0;
}