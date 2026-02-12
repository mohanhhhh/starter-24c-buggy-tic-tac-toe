#include <iostream>
#include <limits>

#include "functions.hpp"

int main() {
  std::vector<std::vector<char>> board;
  InitializeBoard(board);

  char current_player = 'X';
  int row = 0, col = 0;

  PrintBoard(board);

  while (true) {
    std::cout << "Player " << current_player
              << ", enter your move (row and column): ";

    while (!(std::cin >> row >> col)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Invalid input: Please enter integers." << std::endl;
    }

    if (MakeMove(board, row, col, current_player)) {
      char winner = CheckWinner(board);
      
      // FIXED: 先检查是否有人赢了
      if (winner != ' ') {
        PrintBoard(board);
        std::cout << "Player " << winner << " wins!" << std::endl;
        break;
      }
      
      // FIXED: 再检查平局
      if (IsBoardFull(board)) {
        PrintBoard(board);
        std::cout << "It's a tie!" << std::endl;
        break;
      }
      
      SwitchPlayer(current_player);
      PrintBoard(board);  // 可选：显示更新后的棋盘
    }
  }

  return 0;
}
