#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

const int COLORS_CNT = 6;

void printVector(const std::vector<int>& v) {
    for (int a : v) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

void makeGuess(std::vector<int>& numbers) {
    std::cout << "Enter 4 numbers : " << std::endl;
    size_t i = 0;
    while (i < 4 && std::cin >> numbers[i]) {
        ++i;
    }
    printVector(numbers);
}


void orderPawns(std::vector<int>& board, const int colorsCount) {
    std::generate(board.begin(), board.end(), [ colorsCount ] { return std::rand() % colorsCount; });
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

int main()
{
    // use current time as seed for random generator
    std::srand(std::time(0));

    // the board has 4 holes
    std::vector<int> realBoard(4);

    // Player1 puts random colors(numbers 0-5) in the 4 holes
    orderPawns(realBoard, COLORS_CNT);
    printVector(realBoard);

    std::vector<int> guessBoard(4);
    makeGuess(guessBoard);

    std::vector<int> guessResult = checkGuess(guessBoard, realBoard, COLORS_CNT);
    printVector(guessResult);

    return 0;
}