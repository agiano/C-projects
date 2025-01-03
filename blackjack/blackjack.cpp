//
//  main.cpp
//  blackjack
//
//  Created by Alexandros Giannopoulos on 12/28/24.
//

#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <algorithm>

#define nl "\n";

using namespace std;

class Card {
public:
    string suit;
    string rank;
    int value;

    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}
};

class Deck {
public:
    vector<Card> cards;

    Deck() {
        vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
        vector<string> ranks = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        for (const auto &suit : suits) {
            for (int i = 0; i < ranks.size(); i++) {
                int value = (i < 10) ? i + 1 : 10;
                cards.emplace_back(suit, ranks[i], value);
            }
        }
    }

    void shuffle_deck() {
        mt19937 MT{random_device{}()};
        shuffle(cards.begin(), cards.end(), MT);
    }

    Card deal() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

class Hand {
private:
    vector<Card> hand;
public:
    void add_cards(Deck &deck, int n) {
        while (n > 0) {
            hand.push_back(deck.deal());
            n--;
        }
    }

    int get_value() {
        int total = 0;
        for (Card &card : hand) {
            total += card.value;
        }
        return total;
    }

    void display_hand(const string &owner) {
        cout << owner << "'s hand:" << nl;
        for (Card &card : hand) {
            cout << card.rank << " of " << card.suit << " (Value: " << card.value << ")" << nl;
        }
        cout << "Total value: " << get_value() << '\n' << '\n';
    }
};

class Game {
public:
    bool play_question() {
        cout << "Would you like to play blackjack? (yes/no) ";
        string response;
        cin >> response;
        if (response == "yes") {
            return true;
        } else if (response == "no") {
            cout << "Ok. Have a nice day!" << nl;
            return false;
        } else {
            return play_question();
        }
    }

    int num_games_question() {
        cout << "How many games would you like to play? (1-99) ";
        int input;
        while (!(cin >> input) || input < 1 || input > 99) {
            cout << "Invalid input. Please enter a whole number (1-99): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return input;
    }

    void play_round() {
        Deck deck;
        deck.shuffle_deck();
        Hand player_hand, dealer_hand;

        player_hand.add_cards(deck, 2);
        dealer_hand.add_cards(deck, 1);
        
        cout << "*********************************";
        cout << '\n' << '\n';

        while (true) {
            player_hand.display_hand("Player");
            dealer_hand.display_hand("Dealer");

            if (player_hand.get_value() > 21) {
                cout << "You busted! Dealer wins." << nl;
                return;
            }

            cout << "Would you like to hit or stand? ";
            string choice;
            cin >> choice;

            if (choice == "hit") {
                player_hand.add_cards(deck, 1);
                cout << nl;
            } else if (choice == "stand") {
                cout << nl;
                break;
            } else {
                cout << "Invalid choice. Please type 'hit' or 'stand'." << nl;
            }
        }

        int player_total = player_hand.get_value();
        int dealer_total = player_total + 1;

        cout << "Final results:" << nl;
        player_hand.display_hand("Player");
        cout << "Dealer's final total: " << dealer_total << nl;

        if (dealer_total > 21) {
            cout << "Dealer busted! You win!" << '\n' << '\n';
        } else if (dealer_total > player_total) {
            cout << "Dealer wins!" << '\n' << '\n';
        } else {
            cout << "It's a tie!" << '\n' << '\n';
        }
    }

    void play_game() {
        if (!play_question()) {
            return;
        }
        int num_games = num_games_question();
        while (num_games > 0) {
            play_round();
            num_games--;
        }
    }
};

int main() {
    Game blackjack;
    blackjack.play_game();
    return 0;
}
