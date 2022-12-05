#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <regex>

std::vector<std::stack<char>> parseCrateInput(const std::vector<std::string>& lines){
    std::vector<std::stack<char>> crates;
    uint64_t crateNumber {9};
    for(auto it = lines.rbegin() + 1; it != lines.rend(); ++it){
        for(size_t j {0}; j < crateNumber; j++){
            size_t letterIndex{j * 4 + 1};
            if(it->at(letterIndex) != ' '){
                if(crates.size() <= j){
                    crates.push_back(std::stack<char>());
                }
                crates[j].push(it->at(letterIndex)); 
            }
        }
    }

    return crates;
} 

std::vector<std::vector<std::uint64_t>> parseMoveInput(const std::vector<std::string>& lines){
    std::vector<std::vector<std::uint64_t>> moves;
    for(size_t i {0}; i < lines.size(); i++){
        std::regex rgx("[[:digit:]]+");
        std::smatch match;
        std::string::const_iterator searchStart(lines[i].cbegin());
        moves.push_back(std::vector<std::uint64_t>());
        while(std::regex_search(searchStart, lines[i].cend(), match, rgx)){
            searchStart = match.suffix().first;
            moves[i].push_back(std::stoi(match[0]));
        }
    }

    return moves;
}

std::vector<std::string> parseInput(std::ifstream &input){
    std::vector<std::string> output;
    std::string line;
    while(getline(input, line)){
        output.push_back(line);
    }
    return output;
}

std::vector<char> getTopCrates(std::vector<std::stack<char>> crates, const std::vector<std::vector<std::uint64_t>>& moves){
    std::vector<char> topCrates;
    for(const auto& eachMove: moves){
        std::uint64_t moveNumber = eachMove.at(0);
        std::uint64_t fromIndex = eachMove.at(1) - 1;
        std::uint64_t toIndex = eachMove.at(2) - 1;

        std::stack<char> temporaryCrate;
        for(int i = 0; i < moveNumber; i++){
            char toMove = crates.at(fromIndex).top();
            crates.at(fromIndex).pop();
            temporaryCrate.push(toMove);
        }
        
        for(int i = 0; i < moveNumber; i++){
            char toMove = temporaryCrate.top();
            temporaryCrate.pop();
            crates.at(toIndex).push(toMove);
        }

        
    }

    for(const auto& eachCrate : crates){
        topCrates.push_back(eachCrate.top());
    }

    return topCrates;
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
    
    std::vector<std::string> lines = parseInput(input);
    auto it = std::find_if(lines.begin(), lines.end(), [](std::string str){
        return str == "";
    });
    
    std::vector<std::vector<std::uint64_t>> moves = parseMoveInput(std::vector<std::string>(it + 1, lines.end()));
    std::vector<std::stack<char>> crates = parseCrateInput(std::vector<std::string>(lines.begin(), it));
    std::vector<char> topCrates = getTopCrates(crates, moves);

     for(const auto& eachCrate : topCrates){
        std::cout << eachCrate;
    }

    return 0;
}