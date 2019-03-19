/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 3/17/2019.
//


#pragma once

#ifndef CPP_ASSIGNMENT1_GAME_H
#define CPP_ASSIGNMENT1_GAME_H

#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Card.h"
#include <vector>

using namespace std;

class Game {
private:
	//private members and functions
	vector<Player*> players; // vector of the game players
	int number_of_players;
	int initial_number_of_cards;
	int direction;// direction of cycle either 1 or -1
	Card on_floor_card;// the card on the floor (current)
	bool has_ended;// if game has a winner
	int current_turn;
	bool has_played_a_card;
	Game(const Game&);
	Game& operator=(const Game&);



	void init_new_settings();
	void resert_game_settings();
	void play_current_player();
	void step_while(int step);
	void step(int step);

public:
	//public members and functions
	// Starts the game
	Game();
	void start();
	void change_direction();//Changes the direction of the cycle
	int get_direction() const;//Returns the direction of the cycle

};
#endif







#endif //CPP_ASSIGNMENT1_GAME_H
