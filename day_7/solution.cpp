#include "..\utils.h"


std::uint64_t getDirectorySizes(const std::vector<std::string> &lines, size_t &currIndex, std::vector<std::uint64_t>& dirSizes){
    std::uint64_t sum {0};

    while(currIndex < lines.size() && lines.at(currIndex) != "$ cd .."){
        std::string currLine {lines.at(currIndex)};
        if(currLine.find("cd") != std::string::npos){
            currIndex += 2;
            sum += getDirectorySizes(lines, currIndex, dirSizes);
        }

        if(currLine.find("dir") == std::string::npos && currLine.find("$") == std::string::npos){
            sum += getNumber(currLine);
        }
       
        currIndex++;
    }
    
    dirSizes.push_back(sum);
    return sum;
} 

std::uint64_t findDir(const std::vector<std::uint64_t> &dirSizes, const std::uint64_t &needed, const std::uint64_t &maximum){
    std::uint64_t minimum {needed};
    std::uint64_t currSum = dirSizes.at(dirSizes.size() - 1);
    for(const auto& eachDirSize: dirSizes){
        if(needed - (maximum - currSum) <= eachDirSize && eachDirSize < minimum){
            minimum = eachDirSize;
        }
    }
    
    return minimum;
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
    
    // Skip the first two lines since they're always the same commands
    size_t startIndex {2};
    std::vector<std::uint64_t> dirSizes;
    getDirectorySizes(lines, startIndex, dirSizes);
    
    // Part 1
    std::uint64_t finalSum {0};
    for(auto eachSum : dirSizes){
        if(eachSum < 100000)
            finalSum += eachSum;
    }
    std::cout << "Part 1: " << finalSum << '\n';

    // Part 2
    std::uint64_t needed {30000000};
    std::uint64_t maximum {70000000};
    std::cout << "Part 2: " << findDir(dirSizes, needed, maximum);

    return 0;
}