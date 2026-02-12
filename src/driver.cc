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
      /* 
       * DEBUGGER FINDINGS - 2026-02-12
       * BUG #4: Tie check executed before win check
       * --------------------------------------------------
       * Problem: IsBoardFull() was checked immediately after each valid move,
       *          causing winning moves to be incorrectly declared as ties
       * Debugger Method:
       * 1. Set breakpoint at IsBoardFull() and CheckWinner()
       * 2. Created board where next move would win the game
       * 3. Stepped through and observed program entered tie condition first
       * 4. Winner was 'X' but program printed "It's a tie!"
       * Fix: Reordered checks - check winner first, then check for tie
       */
      
      // Check for winner first
      char winner = CheckWinner(board);
      if (winner != ' ') {
        PrintBoard(board);
        std::cout << "Player " << winner << " wins!" << std::endl;
        break;
      }
      
      // Then check for tie
      if (IsBoardFull(board)) {
        PrintBoard(board);
        std::cout << "It's a tie!" << std::endl;
        break;
      }
      
      SwitchPlayer(current_player);
      PrintBoard(board);  // Show updated board
    }
  }

  return 0;
}
