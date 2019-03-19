/* Ali Masarwe 207907171 */
//
// Created by Ali Masarweh on 3/17/2019.
//

#include "Player.h"

using namespace std;

Player::Player(string name, int num_of_cards) : name(name), num_of_cards(num_of_cards), cards(num_of_cards) 
{
	for (auto it = cards.begin(); it != cards.end(); it++) {
		*it = new Card(Card::generate_card());
		cout << **it << endl;
	}
}

Player::Player(const Player& other) : name(other.name), num_of_cards(other.num_of_cards), cards(num_of_cards)
{
	auto this_it = (this->cards).begin(); auto it = other.cards.begin(), it_end = other.cards.end();
	for (; it != it_end; it++)
	{
		*this_it = new Card(**it);
		this_it++;
	}
}

Player & Player::operator=(const Player & other)
{
	cout << "const members, please don't use!!" << endl;
	return *this;
}

bool Player::operator!=(const Player & other) const
{
	return (this->name).compare(other.name) != 0;
}

bool Player::play(Card & card)
{
	bool has_played_a_card = false;
	cout << "Current: " << card << endl << name << ", Your turn-" << endl << "Your cards: ";

	/* Show cards */
	int i = 1;
	for (auto it = cards.begin(); it != cards.end(); it++) {
		cout << "(" << i++ << ")" << **it << " ";
	}
	cout << endl;

	/* Take input of the next play!! */
	int indx;
	do {
		cin >> indx;
		if (indx == 0 || indx > cards.size()) {
			cards.push_back(new Card(Card::generate_card()));
			num_of_cards++;
			return has_played_a_card;
		}
		else if (card.is_legal(**(cards.begin() + (indx - 1)))) {
			has_played_a_card = true;
			card = **(cards.begin() + (indx - 1));
			cards.erase(cards.begin() + (indx - 1));
			num_of_cards--;
			return has_played_a_card;
		}
		else {
			cout << "You can't put " << **(cards.begin() + (indx - 1)) << " on " << card << endl;
		}
	} while (true);

	return has_played_a_card;
}

string Player::get_name() const
{
	return string(name);
}

int Player::get_cards_in_hand() const
{
	return num_of_cards;
}
