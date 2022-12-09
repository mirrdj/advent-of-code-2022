#include "..\utils.h"
#include <set>
#include <stack>

// abs because cmath abs didn't work
std::int64_t abs(const size_t &nubmer1, const size_t &number2){
    std::int64_t abs;

    abs = nubmer1 - number2;
    if(abs >= 0){
        abs = nubmer1 - number2;
    }
    else{
        abs = number2 - nubmer1;
    }

    return abs;
}

bool areTouching(const std::pair<size_t, size_t>& pos1, const std::pair<size_t, size_t>& pos2){
    std::int64_t distI {abs(pos1.first, pos2.first)};
    std::int64_t distJ {abs(pos1.second, pos2.second)};

    return !(distI > 1 || distJ > 1);
}

std::uint64_t getPosNumber(const std::vector<std::string> &lines){
    std::pair<size_t, size_t> currPosT {5, 0};
    std::pair<size_t, size_t> currPosH {currPosT};
    std::set<std::pair<size_t, size_t>> posHistory;
    
    for(const auto &eachLine: lines){
        char direction {eachLine[0]};
        std::uint64_t motionNumber {getNumber(eachLine)};

        if(posHistory.empty()){
            posHistory.insert(currPosT);
        }

        switch(direction){
            case 'U':
                currPosH.first -= motionNumber;
                break;
            case 'D':
                currPosH.first += motionNumber;
                break;
            case 'L':
                currPosH.second -= motionNumber;
                break;
            case 'R':
                currPosH.second += motionNumber;
                break;
        }
        while(!areTouching(currPosH, currPosT)){
            // check if on the same row and columnt in order to determine if T should move diagonally
            if(currPosH.first != currPosT.first && currPosH.second != currPosT.second){
                if(abs(currPosH.first, currPosT.first) == 1){
                    currPosT.first = currPosH.first;
                }
                else if(abs(currPosH.second, currPosT.second) == 1){
                    currPosT.second = currPosH.second;
                }
            }

            switch(direction){
                    case 'U':
                        currPosT.first--;
                        break;
                    case 'D':
                        currPosT.first++;
                        break;
                    case 'L':
                        currPosT.second--;
                        break;
                    case 'R':
                        currPosT.second++;
                        break;
            }


            posHistory.insert(currPosT);
        }
    }

     return posHistory.size();
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
    std::cout << "Part 1: " << getPosNumber(lines) << '\n';
    // std::cout << "Part 2: " <<  << '\n';
    return 0;
}