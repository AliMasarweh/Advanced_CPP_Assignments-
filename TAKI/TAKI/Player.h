/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 3/17/2019.
//


#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#define RANDOM

using namespace std;

class Player {
private:
	//private members
	const string name;
	int num_of_cards;
	//vector of cards
	vector<Card*> cards;


public:
	//public members
	Player(string s = "defualt", int i = 1);
	Player(const Player& other);
	Player& operator=(const Player& other);
	bool operator!=(const Player& other) const;
	bool play(Card&);
	string get_name() const;
	int get_cards_in_hand() const;
};
#endif
