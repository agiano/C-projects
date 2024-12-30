//
//  main.cpp
//  tictactoe
//
//  Created by Alexandros Giannopoulos on 12/29/24.
//

#include <iostream> // for std::cout and std::cin
#include <vector> // for std::vector
#include <algorithm> // for std::find
#include <random> // for mt19937 and random_device{}()

#define nl '\n'

using namespace std;

class tictactoe{
private:
    vector<vector< char >> board{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    
    vector<vector< char >> empty_board{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    
    vector<vector< char >> numbered_board{{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    
    vector<int> moves {1,2,3,4,5,6,7,8,9};
    
    bool current_turn {0}; // 0 = player, 1 = computer
    
    mt19937 MT {random_device{}()};
    
    
public:
    void display_board() 
    {
        cout << "* * * * * * * * * *" << nl;
        cout << "*     |     |     *" << nl;
        cout << "*  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  *" << nl;
        cout << "*     |     |     *" << nl;
        cout << "*-----------------*" << nl;
        cout << "*     |     |     *" << nl;
        cout << "*  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  *" << nl;
        cout << "*     |     |     *" << nl;
        cout << "*-----------------*" << nl;
        cout << "*     |     |     *" << nl;
        cout << "*  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  *" << nl;
        cout << "*     |     |     *" << nl;
        cout << "* * * * * * * * * *" << nl;
    }
    void set_board(vector<vector< char >> new_board)
    {
        board = new_board;
    }
    vector<vector< char >> get_board()
    {
        return board;
    }
    vector<vector< char >> get_empty_board()
    {
        return empty_board;
    }
    vector<vector< char >> get_numbered_board()
    {
        return numbered_board;
    }
    
    bool is_board_full()
    {
        for (vector<char> row : board){
            for (char cell : row){
                if (cell == ' '){
                    return false;
                }
            }
        }
        return true;
    }
    
    // if check_win == true, game is over
    bool check_win(){
        string result;
        for (int i {0}; i < 3; i++){
            // check rows
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' '){
                result = (board[i][0] == 'O' ? "player_win" : "computer_win)");
                // check columns
            }
            else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' '){
                result = (board[0][i] == 'O' ? "player_win" : "computer_win");
            }
        }
        
        // check diagonals
        if (result != "player_win" && result != "computer_win"){
            if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' '){
                result = (board[0][0] == 'O' ? "player_win" : "computer_win");
            }
            else if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != ' '){
                result = (board[2][0] ? "player_win": "computer_win");
            }
        }
        // no one won
        if (result.empty() && is_board_full()){
            result = "tie";
        }
        
        // output results
        if (result == "player_win"){
            cout << "Congratulations! You won." << nl;
            return true;
        } 
        else if (result == "tie"){
            cout << "You tied. Better luck next time." << nl;
            return true;
        } 
        else if (result == "computer_win"){
            cout << "You lossed. You really suck at this!" << nl;
            return true;
        }
        return false;
    }
    
    
    void player_move()
    {
        cout << "Where would you like to go? ";
        string response;
        cin >> response;
        int square = stoi(response);
        
        if (
            find(
                 moves.begin(), // iterator points to first element
                 moves.end(), // iterator points to one position past element
                 square) // element to find
            != moves.end() // if the result == moves.end(), element wasn't in vector
            )
        { // square # is in vector:
            
            switch (square)
            {
                case 1: board[0][0] = 'O'; break;
                case 2: board[0][1] = 'O'; break;
                case 3: board[0][2] = 'O'; break;
                case 4: board[1][0] = 'O'; break;
                case 5: board[1][1] = 'O'; break;
                case 6: board[1][2] = 'O'; break;
                case 7: board[2][0] = 'O'; break;
                case 8: board[2][1] = 'O'; break;
                case 9: board[2][2] = 'O'; break;
            }
            
            moves.erase(find(moves.begin(), moves.end(), square)); // remove # from possible moves
        } else
        { 
            // if move is not in vector (invalid move)
            cout << "Please enter a valid move (";
            for (size_t i {0}; i < moves.size(); ++i){
                if (i < moves.size() - 1){
                    cout << moves[i] << ", ";
                }
                else {
                    cout << moves[i];
                }
            }
            cout << ')' << nl;
            player_move();
        }
    }
    
    void computer_move(){
        int len = static_cast<int>(moves.size());
        // static_cast is a compile-time cast operator
        // a cast is type conversion operation, must be used with compatible types though
        uniform_int_distribution comp_move_dist{ 0, len - 1}; // create uniform distribution between every possible move
        int comp_move {moves[comp_move_dist(MT)]};
        cout << "computer move: " << comp_move << nl;
        
        switch (comp_move)
        {
            case 1: board[0][0] = 'X';break;
            case 2: board[0][1] = 'X'; break;
            case 3: board[0][2] = 'X'; break;
            case 4: board[1][0] = 'X'; break;
            case 5: board[1][1] = 'X'; break;
            case 6: board[1][2] = 'X'; break;
            case 7: board[2][0] = 'X'; break;
            case 8: board[2][1] = 'X'; break;
            case 9: board[2][2] = 'X'; break;
        }
        
        moves.erase(find(moves.begin(), moves.end(), comp_move)); // remove # from possible moves
    }
    
    void play_game(){
//        cout << "Hello, to decide who goes first, pick heads or tails. ";
//        string response;
//        cin >> response;
//        heads_or_tails(response);
        
        set_board(get_numbered_board());
        display_board(); // show numbered board
        
        set_board(get_empty_board()); // reset the board
        moves = {1,2,3,4,5,6,7,8,9};
        
        while (!check_win()) {
            if (current_turn == 0){
                player_move();
                current_turn = 1;
            }
            else {
                computer_move();
                current_turn = 0;
            }
            
            cout << nl << nl << nl;
            display_board();
            
            
        }
        
        play_again();
        
    }
    
    void play_again(){
        cout << nl << "Would you like to play again? (yes/no) ";
        string response;
        cin >> response;
        if (response == "yes"){
            play_game();
        } 
        else if (response == "no"){
            cout << "Have a nice day!" << nl;
        } else {
            play_again();
        }
    }
    
};
int main(int argc, const char * argv[]) {
    
    tictactoe game;
    game.play_game();
        
    return 0;
}
