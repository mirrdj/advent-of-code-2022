#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

std::string parseInput(std::ifstream &input){
    std::string output;
    std::string line;
    while(input >> line){
        output.append(line);
    }
    return output;
}

std::uint64_t getCharIndex(const std::string &signal, const size_t &messageLength){
    std::map<char, int> charFrequency;

    std::for_each(signal.begin(), signal.begin() + messageLength, [&](const char& c){
        if(charFrequency.count(c) == 0)
            charFrequency[c] = 1;
        else
            charFrequency[c]++;
    });

    for(size_t i{messageLength}; i < signal.size(); i++){
        size_t count = std::count_if(charFrequency.begin(), charFrequency.end(), [](const auto& cfPair){
            return cfPair.second == 1;
        });

        if(count == messageLength)
            return i;
        
        char toDecrease = signal[i - messageLength];
        charFrequency[toDecrease]--;
        if(charFrequency[toDecrease] == 0)
            charFrequency.erase(signal[i - messageLength]);

        char toIncrease = signal[i];
        if(charFrequency.count(toIncrease) == 0)
            charFrequency[toIncrease] = 1;
        else
            charFrequency[toIncrease]++;
    }
    
    return 0;
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
    
    std::string signal = parseInput(input);
    
    size_t messageLength1 {4};
    std::cout << "Part 1: " << getCharIndex(signal, messageLength1) << '\n';

    size_t messageLength2 {14};
    std::cout << "Part 2: " << getCharIndex(signal, messageLength2) << '\n';

    return 0;
}