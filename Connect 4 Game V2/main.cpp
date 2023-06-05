/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: blake
 *
 * Created on May 31, 2023, 4:08 PM
 * This version adds a 10x10 board size and fixes bug with invalid input.
 */

#include <iostream>

using namespace std;

//NEW
const int maxsize = 10;
char board[maxsize][maxsize];

//Shows board
void show (int rows, int columns){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
//Checks for 4 in a row
bool wincheck(int rows, int columns, char player){
    //Vertical
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player) {
                return true;
            }
        }
    }

    //Horizontal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player) {
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
    //NEW
    int size, rows, columns;
    cout << "0 for normal size board(6x7) 1 for large board(10x10) ";
    cin >> size;
    switch (size){
        case 0:
            rows = 6;
            columns = 7;
            break;
        case 1:
            rows = 10;
            columns = 10;   
            break;
    }
    
    
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            board[i][j] = '-';
        }
    }
    
    show(rows, columns);
    
    char p1 = 'X';
    char p2 = 'O';
    char curplay = p1;
    
    int nummove = 0;
    
    while (true){
        int col;
        
        //NEW
        if (columns == 10){
            cout << "Player " << curplay << " enter 0-9 to play. ";
        }
        else if (columns == 7){
            cout << "Player " << curplay << " enter 0-6 to play. ";
        }
        cin >> col;
        
        //NEW
        if (col >= columns || col < 0){
            cout << "Not a valid column choose another.\n";
            continue;
        }
        
        int row = rows - 1;
        while (row >= 0 && board[row][col] != '-'){
            row--;
        }
        
        if (row < 0) {
            cout << "Column " << col << " is already full choose another." << endl;
            continue;
        }
        
        board[row][col] = curplay;
                
        nummove++;
        
        show(rows, columns);
        
        if (wincheck(rows, columns, curplay)){
            cout << "Player " << curplay << " wins!" << endl;
            return 0;
        }
        
        if (nummove == rows * columns){
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
