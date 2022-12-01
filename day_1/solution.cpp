#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int countCalories(std::ifstream &input){
    int currSum = 0;
    int maxSum = 0;
    std::string line;
    std::vector<int> caloriesSums;

    while(input){
        std::getline(input, line);
        if(line.empty()){
            caloriesSums.push_back(currSum);
            
            currSum = 0;
            std::getline(input, line);
        }
        
        if(!line.empty()){
            currSum += stoi(line);
        }
    }
    
    std::sort(caloriesSums.begin(), caloriesSums.end(), std::greater<int>());
    maxSum = std::accumulate(caloriesSums.begin(), caloriesSums.begin() + 3, 0);
                     
    return maxSum;
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

    std::cout << "Result is: " << countCalories(input);

    return 0;
}