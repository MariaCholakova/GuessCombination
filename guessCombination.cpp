#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

void orderPawns(std::vector<int>& board, const int colorsCount) {
    std::generate(board.begin(), board.end(), [ colorsCount ] { return std::rand() % colorsCount; });
}


void printBoard(const std::vector<int>& board) {
    for (int a : board) {
        std::cout << a << std::endl;
    }
}

int main()
{
    // use current time as seed for random generator
    std::srand(std::time(0));

    // the board has 4 holes
    std::vector<int> board(4);

    // Player1 puts random colors(numbers 0-5) in the 4 holes
    orderPawns(board, 6);
    printBoard(board);

    return 0;
}