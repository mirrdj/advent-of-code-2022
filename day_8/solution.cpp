#include "..\utils.h"
#include <map>

std::vector<std::vector<std::uint64_t>> getMatrix(const std::vector<std::string> &lines){
    std::vector<std::vector<std::uint64_t>> output;
    std::size_t index {0};
    
    for(const auto &eachLine: lines){
        output.push_back(std::vector<std::uint64_t>());
        for_each(eachLine.begin(), eachLine.end(), [&](const char &c){
            output[index].push_back(static_cast<std::uint64_t>(c) - 48);
        });
        index++;
    }
    
    return output;
}

std::map<std::pair<size_t, size_t>, uint64_t> getVisibleMap(const std::vector<std::vector<std::uint64_t>> &matrix){
    std::map<std::pair<size_t, size_t>, uint64_t> visibleMap;

    std::size_t matrixWidth {matrix[0].size()};
    std::size_t matrixHeight {matrix.size()};
    
    for(size_t i {1}; i < matrixHeight - 1; i++){
        uint64_t max {matrix[i][0]};
        for(size_t j {1}; j < matrixWidth - 1; j++){
            if(matrix[i][j] > max){
                max = matrix[i][j];
                visibleMap[std::pair<size_t, size_t>(i, j)] = matrix[i][j];
            }
        }
    }

    for(size_t i {1}; i < matrixHeight - 1; i++){
        uint64_t max {matrix[i][matrixWidth - 1]};
        for(size_t j {matrixWidth - 2}; j > 0; j--){
            if(matrix[i][j] > max){
                max = matrix[i][j];
                visibleMap[std::pair<size_t, size_t>(i, j)] = matrix[i][j];
            }
        }
    }

    for(size_t j {1}; j < matrixWidth - 1; j++){
        uint64_t max {matrix[0][j]};
        for(size_t i {1}; i < matrixHeight - 1; i++){
            if(matrix[i][j] > max){
                max = matrix[i][j];
                visibleMap[std::pair<size_t, size_t>(i, j)] = matrix[i][j];
            }
        }
    }

    for(size_t j {1}; j < matrixWidth - 1; j++){
        uint64_t max {matrix[matrixHeight - 1][j]};
        for(size_t i {matrixHeight - 2}; i > 0; i--){
            if(matrix[i][j] > max){
                max = matrix[i][j];
                visibleMap[std::pair<size_t, size_t>(i, j)] = matrix[i][j];
            }
        }
    }

    return visibleMap;
}

std::uint64_t getVisibleNumber(const std::map<std::pair<size_t, size_t>, uint64_t> &visibleMap, const std::vector<std::vector<std::uint64_t>> &matrix){
    std::uint64_t visibleNumber {0};
    std::size_t matrixWidth {matrix[0].size()};
    std::size_t matrixHeight {matrix.size()};
    visibleNumber += 2 * matrixWidth;
    visibleNumber += 2 * matrixHeight;
    visibleNumber -= 4;
    visibleNumber += visibleMap.size();

    return visibleNumber;
}

std::uint64_t getHighestScenicScore(const std::map<std::pair<size_t, size_t>, uint64_t> &visibleMap, const std::vector<std::vector<std::uint64_t>> &matrix){
    std::uint64_t product {1}, maxProduct {1};

    std::size_t matrixWidth {matrix[0].size()};
    std::size_t matrixHeight {matrix.size()};

    for(auto it {visibleMap.begin()}; it != visibleMap.end(); it++){
        size_t up {0}, down {0}, left {0}, right {0};
        size_t visI {it->first.first};
        size_t visJ {it->first.second};

        if(visI != matrixHeight - 1 && visI != 0 
            && visJ != matrixWidth - 1 && visJ != 0){
            size_t i {visI};
            do {
            i++;
            down++;  
            } while(i < matrixHeight - 1 && matrix[i][visJ] < matrix[visI][visJ]);
            
            i = visI;
            do {
            i--;
            up++;  
            } while(i > 0 && matrix[i][visJ] < matrix[visI][visJ]);

            size_t j {visJ};
            do {
            j++;
            right++;  
            } while(j < matrixWidth - 1 && matrix[visI][j] < matrix[visI][visJ]);

            j = visJ;
            do {
            j--;
            left++;  
            } while(j > 0 && matrix[visI][j] < matrix[visI][visJ]);

            product = up * down * left * right;
            if(product > maxProduct){
                maxProduct = product;
            }
        }
    }

    return maxProduct;
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
    std::vector<std::vector<std::uint64_t>> matrix = getMatrix(lines);
    std::map<std::pair<size_t, size_t>, uint64_t> visibleMap = getVisibleMap(matrix);
    std::cout << "Part 1: " << getVisibleNumber(visibleMap, matrix) << '\n';
    std::cout << "Part 2: " << getHighestScenicScore(visibleMap, matrix) << '\n';
    return 0;
}