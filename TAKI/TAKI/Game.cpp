/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 3/17/2019.
//


#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;


Game::Game(const Game &)
{
	cerr << " One game at a time only " << endl;
}

Game & Game::operator=(const Game &)
{
	cerr << " One game at a time only " << endl;
	return *this;
}

/* Initialize players and generate randomly cards */
void Game::init_new_settings()
{
	for (int indx = 0; indx < number_of_players; indx++) {
		string name;
		cout << "player num " << indx + 1 << " name?" << endl;
		cin >> name;
		Player *tmp_player = new Player(name, initial_number_of_cards);
		players.push_back(tmp_player);
	}
	on_floor_card = Card::generate_card();
}

/* Resseting the game setting */
void Game::resert_game_settings()
{
	has_ended = false;
	direction = 1;
	number_of_players = 0;
	initial_number_of_cards = 0;
	current_turn = 0;
	has_played_a_card = false;
}

Game::Game()
{
}

void Game::start() {
	/* Resseting the game setting */
	resert_game_settings();

	/* Setting the number of players */
	cout << "How Many Players?" << endl;
	do {
		if (!(cin >> number_of_players))
			cerr << "Failed to assign players!!" << endl;
		if (number_of_players > 1)
			break;
		else
			cout << "Number of players must be bigger than 1" << endl;
	} while (number_of_players > 1);
	//players = vector<Player>(number_of_players);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Setting the number of cards */
	cout << "How Many Cards?" << endl;
	do {
		if (!(cin >> initial_number_of_cards))
			cerr << "Failed to assign cards!!" << endl;
		if (initial_number_of_cards > 0)
			break;
		else
			cout << "Number of cards must be positive!!" << endl;
	} while (initial_number_of_cards > 0);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Initialize players and generate randomly cards */
	init_new_settings();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (!has_ended) {
		play_current_player();
	}
}


/* Change the direction of the game in case of CD card is played! */
void Game::change_direction()
{
	direction *= -1;
}

/* The dicretion of the cycle */
int Game::get_direction() const
{
	return direction;
}

void Game::play_current_player()
{	
	has_played_a_card = false;
	Card tmp(on_floor_card);
	has_played_a_card = players[current_turn]->play(on_floor_card);
	int step = 1;

	/* Check if he has won!! */
	if (players[current_turn]->get_cards_in_hand() == 0) {
		cout << players[current_turn]->get_name() << " wins!" << endl;
		has_ended = true;
		return;
	}

	/* check if card with special operation!! */
	if (has_played_a_card) {
		if (on_floor_card.get_sign() == sign::PLUS) {
			play_current_player();
			return;
		}
		else if (on_floor_card.get_sign() == sign::STOP) {
			step++;
		}
		else if (on_floor_card.get_sign() == sign::CD) {
			change_direction();
		}
	}
	/* Next step */
	this->step_while(step);
}

void Game::step_while(int step)
{
	while (step > 0) {
		if (direction == 1) {
			if (current_turn < players.size() - 1)
				current_turn++;
			else
				current_turn = 0;
		}
		else {
			if (current_turn > 0)
				current_turn--;
			else
				current_turn = players.size() - 1;
		}
		step--;
	}
}

void Game::step(int step)
{
	if (direction == 1) {
		if (current_turn + step <= players.size() - 1)
			current_turn += step;
		else
			current_turn = step - (players.size() - current_turn);
	}
	else {
		if (current_turn - step >= 0)
			current_turn -= step;
		else
			current_turn = players.size() - (step - current_turn);
	}
}
