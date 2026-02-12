#include "functions.hpp"
#include <iostream>

void PrintBoard(const std::vector<std::vector<char>>& board) {
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    for (unsigned int j = 0; j < kBoardSize; ++j) {
      std::cout << board[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void InitializeBoard(std::vector<std::vector<char>>& board) {
  board.clear();
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    board.push_back(std::vector<char>(kBoardSize, ' '));
  }
}

bool MakeMove(std::vector<std::vector<char>>& board,
              int row,
              int col,
              char player) {
  /* 
   * DEBUGGER FINDINGS - 2026-02-12
   * BUG #1: Out-of-bounds validation error
   * --------------------------------------------------
   * Problem: The code checked row <= 0 || row > kBoardSize, but the game uses 0-based indexing.
   *          This caused row 0 to be incorrectly treated as out of bounds.
   * Debugger Method: 
   * 1. Set breakpoint at MakeMove() entry
   * 2. Enter "0 0" as a move
   * 3. Observed row=0, col=0 in variable watch
   * 4. Stepped through and saw row <= 0 condition evaluate to true
   * Fix: Changed to row < 0 || row >= kBoardSize
   */
  if (row < 0 || row >= kBoardSize || col < 0 || col >= kBoardSize) {
    std::cerr << "Error: Move out of bounds!\n";
    return false;
  }
  
  /* 
   * DEBUGGER FINDINGS - 2026-02-12
   * BUG #2: Row/Column index swap
   * --------------------------------------------------
   * Problem: Used board[col][row] instead of board[row][col], causing moves to be placed
   *          in wrong positions
   * Debugger Method:
   * 1. Set breakpoint after board assignment
   * 2. Entered row=1, col=2
   * 3. Watched board array and saw the move was placed at board[2][1]
   * Fix: Changed to board[row][col]
   */
  if (board[row][col] != ' ') {
    std::cerr << "Error: Cell already occupied!\n";
    return false;
  }
  
  board[row][col] = player;
  return true;
}

char CheckWinner(const std::vector<std::vector<char>>& board) {
  /* 
   * DEBUGGER FINDINGS - 2026-02-12
   * BUG #3: Incorrect return values in win condition checks
   * --------------------------------------------------
   * Problem: Row check returned board[0][i] instead of board[i][0]
   *          Column check returned board[i][0] instead of board[0][i]
   *          Missing main diagonal check
   *          Anti-diagonal check returned wrong value
   * Debugger Method:
   * 1. Set breakpoint in CheckWinner()
   * 2. Created board with X winning on row 1
   * 3. Stepped through and saw it detected win but returned wrong character
   * 4. Watched return value vs actual winning player
   * Fix: Corrected return values and added missing diagonal check
   */
  
  // Check rows
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
        board[i][0] != ' ') {
      return board[i][0];  // FIXED: Return the player from the winning row
    }
  }

  // Check columns
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
        board[0][i] != ' ') {
      return board[0][i];  // FIXED: Return the player from the winning column
    }
  }

  // Check main diagonal (top-left to bottom-right)
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
      board[0][0] != ' ') {
    return board[0][0];  // FIXED: Added missing diagonal check
  }

  // Check anti-diagonal (top-right to bottom-left)
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
      board[0][2] != ' ') {
    return board[0][2];  // FIXED: Return the correct player
  }
  
  return ' ';
}

bool IsBoardFull(const std::vector<std::vector<char>>& board) {
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    for (unsigned int j = 0; j < kBoardSize; ++j) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

void SwitchPlayer(char& player) { 
  player = (player == 'X') ? 'O' : 'X'; 
}
