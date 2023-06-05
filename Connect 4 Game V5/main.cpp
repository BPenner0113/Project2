/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: blake
 *
 * Created on June 5, 2023, 11:54 AM
 * This version gets rid of global variables and adds more comments.
 */

//Import libraries
#include <iostream>
#include <limits>
#include <fstream>


using namespace std;

const int maxsize = 10;


//Save the winner's name in a file
void savestats(char curplay, char p1, string name1, string name2){
    string winner;
    if (curplay == p1){
        winner = name1;
    }
    else{
        winner = name2;
    }
    ofstream outFile;
    outFile.open("c4stats.txt", ios_base::app);
    outFile << winner << " wins!" << endl;
    outFile.close();
}

//Load the previous game's stats from the file and show them
void loadstats(){
    ifstream inFile;
    inFile.open("c4stats.txt");
    string line;
    while (getline(inFile, line)){
        cout << line << endl;
    }
    inFile.close();
}

//Shows game board
void show (int rows, int columns, char board[][maxsize]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
//Checks for 4 in a row
bool wincheck(int rows, int columns, char player, char curplay, char p1, string name1, string name2, char board[][maxsize]){
    //Vertical
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player) {
                //NEW
                savestats(curplay, p1, name1, name2);
                return true;
            }
        }
    }

    //Horizontal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player) {
                //NEW
                savestats(curplay, p1, name1, name2);
                return true;
            }
        }
    }

    //Diagonal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player) {
                //NEW
                savestats(curplay, p1, name1, name2);
                return true;
            }
        }
    }

    //Diagonal
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == player && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player) {
                //NEW
                savestats(curplay, p1, name1, name2);
                return true;
            }
        }
    }

    return false;
}



int main(int argc, char** argv) {
    //Declare variables
    int size, rows, columns;
    string name1, name2;
    bool valid;
    bool cont = false;
    char board[maxsize][maxsize];
    
    //Load previous game's stats
    loadstats();
    
    
    while (cont == false){
        //Ask player to choose board size
        cout << "0 for normal size board(6x7) 1 for large board(10x10) 2 for small board(5x5)" ;
        cin >> size;
        //Check if the input is valid
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
        
        else if (size == 0 || size == 1 || size == 2){
            cont = true;
        }
        
        else{
            cout << "Invalid input. Please enter 0, 1, or 2\n";
        }
    }
    
    //Get player names
    cout << "Enter name for Player 1\n";
    cin >> name1; 
    cout << "Enter name for Player 2\n";
    cin >> name2;
    //Set up board according to chosen size
    switch (size){
        case 0:
            rows = 6;
            columns = 7;
            break;
        case 1:
            rows = 10;
            columns = 10;   
            break;
            //NEW
        case 2:
            rows = 5;
            columns = 5;
            break;
        default:
            return 1;
    }
    
    
    //Initialize the board with '-'
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            board[i][j] = '-';
        }
    }
    //Display game board
    show(rows, columns, board);
    //Initialize player symbols and current player
    char p1 = 'X';
    char p2 = 'O';
    char curplay = p1;
    int nummove = 0;
    //Game loop starts
    while (true){
        int col; //Player selected column
        
        //Ask current player to choose column
        switch (columns){
            case 10:
                cout << "Player " << curplay << " enter 0-9 to play. ";
                break;
            case 7:
                cout << "Player " << curplay << " enter 0-6 to play. ";
                break;
            
            case 5:
                cout << "Player " << curplay << " enter 0-4 to play. ";
                break;
            
            default:
                return 1;   
        }
        //Gets player's chosen column
        cin >> col;
        //Check if input == a valid column
        valid = false;
        for (int i = 0; i < columns; i++){
            if (i == col){
                valid = true;
            }
        }
        //Restarts loop if input != a valid column
        if (valid == false){
            cout << "Not a valid column choose another.\n";
            continue;
        }
        //Check if input is an integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        //Check if column is full
        int row = rows - 1;
        while (row >= 0 && board[row][col] != '-'){
            row--;
        }
        //Restarts loop if column is full
        if (row < 0) {
            cout << "Column " << col << " is already full choose another." << endl;
            continue;
        }
        //Adds player symbol to board
        board[row][col] = curplay;
        //Increases move counter by 1      
        nummove++;
        //Displays updated board
        show(rows, columns, board);
        //Check if current player won
        if (wincheck(rows, columns, curplay, p1, p1, name1, name2, board)){
            cout << "Player " << curplay << " wins!" << endl;
            return 0;
        }
        //Check if no more moves available
        if (nummove == rows * columns){
            cout << "Tie Game!" << endl;
            return 0;
        }
        //Swaps current player
        if (curplay == p1){
            curplay = p2;
        }
        else{
            curplay = p1;
        }
    }

    return 0;
}

