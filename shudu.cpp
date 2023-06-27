/*****************************************************************************
*  xxx xxx  Co., Ltd                                                         *
*  Copyright (C) 2014 xxx xxx                                                * 
*  This program implements a Sudoku program. You can use it to generate      *
*  Sudoku endings to files, and read Sudoku from files and solve puzzles. In *
*  this program, we have used backtracking algorithm to solve sudoku problem.*                                       *
*                                                                            *
*  @file     shudu.cpp                                                       *
*  @brief    数独                                                            *
*  Details.                                                                  *
*                                                                            *
*  @author   jlx lxk                                                         *
*  @email    jlx0626sammi@163.com                                            *
*  @version  1.0.0.1(版本号)                                                  *
*  @date     2023-06-27                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*   Date      |   Version | Author      | Description                        *
*----------------------------------------------------------------------------*
*  2023/06/27 | 1.0.0.1   | lxk jlx      | Create file                         *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
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

// Function to generate a Sudoku puzzle
void generateSudoku(int numPuzzles) {
    std::ofstream file("sudoku_puzzles.txt");

    std::vector<int> nums(BOARD_SIZE);
    std::iota(nums.begin(), nums.end(), 1);

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int i = 0; i < numPuzzles; i++) {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

        for (int j = 0; j < BOARD_SIZE; j++) {
            board[0][j] = nums[j];
        }

        solveSudoku(board);

        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                file << board[row][col] << " ";
            }
            file << std::endl;
        }
        file << std::endl;
    }

    file.close();
}