#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

#define BOARD_SIZE 9
#define EMPTY 0

// Function to check if a number can be placed at a given position([row][col]) in the board
bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check if the number already exists in the same row or column
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the same 3x3 grid
    int gridStartRow = row - row % 3;
    int gridStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + gridStartRow][j + gridStartCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Find an empty cell
            if (board[row][col] == EMPTY) {
                // Try placing numbers from 1 to 9
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        board[row][col] = EMPTY;
                    }
                }

                return false;
            }
        }
    }

    return true;
}