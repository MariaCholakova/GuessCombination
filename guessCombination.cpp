#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

const int COLORS_CNT = 6;

void printVector(const std::vector<int>& v) {
    for (int a : v) {
        std::cout << a << " ";
    }
}

void makeGuess(std::vector<int>& numbers) {
    std::cout << "Enter 4 numbers : " << std::endl;
    size_t i = 0;
    while (i < 4 && std::cin >> numbers[i]) {
        ++i;
    }
    printVector(numbers);
}

std::vector<int> checkGuess(const std::vector<int>& guessBoard, const std::vector<int>& correctBoard, const int colorsCount) {
    int fullyAccurate = 0;     // count of pawns where both color and position match
    int onlyColorAccurate = 0; // count of pawns where only color matches

    std::vector<unsigned int> correctMap(colorsCount, 0);
    std::vector<unsigned int> guessMap(colorsCount, 0);
    for (size_t i = 0; i < correctBoard.size(); i++) {

        if (correctBoard[i] == guessBoard[i])
            fullyAccurate++;
        else {
            correctMap[correctBoard[i]]++;
            guessMap[guessBoard[i]]++;
        }
    }

    for (size_t  i = 0; i < colorsCount; i++) {
        onlyColorAccurate += std::min(correctMap[i], guessMap[i]);
    }

    return { fullyAccurate, onlyColorAccurate };
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void initBoard(std::vector<int>& board, const int colorsCount) {
    std::generate(board.begin(), board.end(), [colorsCount] { return std::rand() % colorsCount; });
}

void findSolution(const std::vector<int>& correctBoard, const int colorsCount) {

    // find out the frequency of each color
    std::vector<int> colorsHistogram(colorsCount, 0);

    for (int color = 0; color < colorsCount; color++) {
        printVector({ color, color, color, color });
        for (int number : correctBoard) {
            if (number == color) {
                colorsHistogram[color]++;
            }
        }
        std::cout << "  - " << colorsHistogram[color] << " fully matched pawns" << std::endl;
    }

    // get the necessary colors which compose the solution
    std::vector<int> necessaryColors;
    for (int i = 0; i < colorsCount; i++) {
        while (colorsHistogram[i] > 0) {
            necessaryColors.push_back(i);
            colorsHistogram[i]--;
        }
    }

    // check all permutations of the necessary colors
    do {
        printVector(necessaryColors);
        std::cout << std::endl;

        if (std::equal(necessaryColors.begin(), necessaryColors.end(), correctBoard.begin())) {
            std::cout << "Solution is : ";
            printVector(necessaryColors);
            break;
        }

    } while (std::next_permutation(necessaryColors.begin(), necessaryColors.end()));
}

int main()
{
    // use current time as seed for random generator
    std::srand(std::time(0));

    // the board has 4 holes
    std::vector<int> realBoard(4);

    // Player1 puts random colors(numbers 0-5) in the 4 holes
    initBoard(realBoard, COLORS_CNT);
    printVector(realBoard);
    std::cout << std::endl;

    findSolution(realBoard, COLORS_CNT);

    return 0;
}