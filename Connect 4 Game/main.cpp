/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: blake
 *
 * Created on May 9, 2023, 8:09 PM
 */
#include <iostream>

using namespace std;

const int rows = 6;
const int columns = 7;


void show (char board[rows][columns]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool wincheck(char board[rows][columns], char player){
    //Vertical
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player) {
                return true;
            }
        }
    }

    //Horizontal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player) {
                return true;
            }
        }
    }

    //Left up diagonal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return true;
            }
        }
    }

    //Left down diagonal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == player && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player) {
                return true;
            }
        }
    }

    return false;
}



int main(int argc, char** argv) {
    
    char board[rows][columns];
    int x[7] = {0, 1, 2, 3, 4, 5, 6};
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            board[i][j] = '-';
        }
    }
    
    show(board);
    
    char p1 = 'X';
    char p2 = 'O';
    char curplay = p1;
    
    int nummove = 0;
    
    while (true){
        int col;
        cout << "Player " << curplay << " enter 0-6 to play. ";
        cin >> col;
        
        int row = rows - 1;
        while (row >= 0 && board[row][col] != '-'){
            row--;
        }
        
        if (row < 0) {
            cout << "Column " << col << " is already full choose another." << endl;
            continue;
        }
        
        if (col >= columns){
            cout << "Not a valid column choose another.\n";
            continue;
        }
        
        board[row][col] = curplay;
        nummove++;
        
        show(board);
        
        if (wincheck(board, curplay)){
            cout << "Player " << curplay << " wins!" << endl;
            return 0;
        }
        
        if (nummove == rows *columns){
            cout << "Tie Game!" << endl;
            return 0;
        }
        
        if (curplay == p1){
            curplay = p2;
        }
        else{
            curplay = p1;
        }
    }

    return 0;
}

