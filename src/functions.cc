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
    // FIXED Bug 2: 修正边界检查，支持0索引
    if (row < 0 || row >= kBoardSize || col < 0 || col >= kBoardSize) {
        std::cerr << "Error: Move out of bounds!\n";
        return false;
    }
    
    // FIXED Bug 1: 修正索引顺序，使用board[row][col]
    if (board[row][col] != ' ') {
        std::cerr << "Error: Cell already occupied!\n";
        return false;
    }
    
    board[row][col] = player;
    return true;
}

char CheckWinner(const std::vector<std::vector<char>>& board) {
    // 检查行
    for (unsigned int i = 0; i < kBoardSize; ++i) {
        if (board[i][0] == board[i][1] && 
            board[i][1] == board[i][2] && 
            board[i][0] != ' ') {
            return board[i][0];  // FIXED: 返回正确的字符
        }
    }

    // 检查列
    for (unsigned int i = 0; i < kBoardSize; ++i) {
        if (board[0][i] == board[1][i] && 
            board[1][i] == board[2][i] && 
            board[0][i] != ' ') {
            return board[0][i];  // FIXED: 返回正确的字符
        }
    }

    // FIXED: 添加主对角线检查
    if (board[0][0] == board[1][1] && 
        board[1][1] == board[2][2] && 
        board[0][0] != ' ') {
        return board[0][0];
    }

    // FIXED: 修正次对角线检查的返回值
    if (board[0][2] == board[1][1] && 
        board[1][1] == board[2][0] && 
        board[0][2] != ' ') {
        return board[0][2];  // FIXED: 返回正确的字符
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
