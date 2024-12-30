//
//  main.cpp
//  rock_paper_scissors
//
//  Created by Alexandros Giannopoulos on 12/27/24.
//

#include <iostream>

using namespace std;

int convo3(int scoreComputer){
    string response;
    cin >> response;
    if (response == "rock"){
        cout << "computer chose paper, you lose!" << endl;
        return scoreComputer + 1;
    } else if (response == "paper"){
        cout << "computer chose scissors, you lose!" << endl;
        return scoreComputer + 1;
    } else if (response == "scissors"){
        cout << "computer chose rock, you lose!" << endl;
        return scoreComputer + 1;
    } else {
        cout << "Please choose rock, paper or scissors. ";
        return convo3(scoreComputer);
        
    }
}

int convo2(){
    int response;
    cin >> response;
    
    return response;
}

int convo1(){
    string response;
    cin >> response;
    
    std::erase_if(response, [](char c) { return c == ' '; }); // remove all spaces from response
    
    if (response == "Y" || response == "Yes" || response == "YES" || response == "yes"  || response == "y"){
        cout << "How many games would you like to play? (0-99) ";
        int games = convo2();
        return games;
        } else if (response == "N" || response == "No" || response == "NO" || response == "no"  || response == "n"){
            cout << "Ok, have a nice day." << endl;
        } else {
            cout << "Please respond with yes or no. ";
            convo1();
        }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    cout << "Would you like to play rock, paper, scissors? ";

    int numGames = convo1();
    
    int scorePlayer = 0;
    int scoreComputer = 0;
    
    
    while (numGames > 0){
        cout << "Do you choose rock, paper or scissors? ";
        scoreComputer = convo3(scoreComputer);
        
        cout << "Score: (" << scorePlayer << "-" << scoreComputer << ")" << endl;
        
        numGames--;
    }
    
    if (scoreComputer > scorePlayer){
        cout << "You lost! Thanks for playing." << endl;
    } else if (scoreComputer < scorePlayer){
        cout << "You won! Thanks for playing." << endl;
    } else if (scoreComputer + scorePlayer > 0){
        cout << "You tied! Thanks for playing." << endl;
    }
    
    return 0;
}
