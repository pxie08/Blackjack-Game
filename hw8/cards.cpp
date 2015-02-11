/***************************************************
** cards.cpp
** Definitions of the Card and Player
** and Hand class member functions.
** Patrick Xie, 03/05/10
****************************************************/
#include "cards.h"
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <iomanip>

/***************************************************
** Card
** default constructor
** assigns random rank and suit to card
****************************************************/
Card::Card() {
	int rand_numR = 1 + rand () % 13; //Random # between 1 and 10. rand_numR for rank
	switch (rand_numR) { //switch used to pick a random rank
		case 1: rank = "Ace"; break;
		case 2: rank = "Two"; break;
		case 3: rank = "Three"; break;
		case 4: rank = "Four"; break;
		case 5: rank = "Five"; break;
		case 6: rank = "Six"; break;
		case 7: rank = "Seven"; break;
		case 8: rank = "Eight"; break;
		case 9: rank = "Nine"; break;
		case 10: rank = "Ten"; break;
		case 11: rank = "Jack"; break;
		case 12: rank = "Queen"; break;
		case 13: rank = "King"; break;
	}
	int rand_numS = 1 + rand() % 4;  //Random # between 1 and 4. rand_numS for suit
	switch(rand_numS) { //switch used to pic a random suit
		case 1: suit = "Hearts"; break;
		case 2: suit = "Diamonds"; break;
		case 3: suit = "Clubs"; break;
		case 4: suit = "Spades"; break;
	}
}

/***************************************************
** get_rank
** returns the rank of the card
****************************************************/
string Card::get_rank() const {
	return rank;
}

/***************************************************
** get_suit
** returns the suit of the card
****************************************************/
string Card::get_suit() const {
	return suit;
}

/***************************************************
** rank2num
** converts card rank into a int number
** used to compare cards
****************************************************/
int Card::rank2num() const {
	int value;
	if (get_rank() == "Ace")
		value = 11;
	if (get_rank() == "Two")
		value = 2;
	if (get_rank() == "Three")
		value = 3;
	if (get_rank() == "Four")
		value = 4;
	if (get_rank() == "Five")
		value = 5;
	if (get_rank() == "Six")
		value = 6;
	if (get_rank() == "Seven")
		value = 7;
	if (get_rank() == "Eight")
		value = 8;
	if (get_rank() == "Nine")
		value = 9;
	if (get_rank() == "Ten")
		value = 10;
	if (get_rank() == "Jack")
		value = 10;
	if (get_rank() == "Queen")
		value = 10;
	if (get_rank() == "King")
		value = 10;
	return value;
}

/***************************************************
** operator<
** compares the rank of two cards
****************************************************/
bool Card::operator< (Card card2) const {
	return rank2num() < card2.rank2num();
}

/***************************************************
** Player
** constructs Player with intial amount of money
****************************************************/
Player::Player(int start_money) {
	money = start_money;
}

/***************************************************
** get_money
** returns the current amount of money
****************************************************/
int Player::get_money() const {
	return money;
}

/***************************************************
** change_money
** adds an amount to total amount of money
****************************************************/
void Player::change_money(int update) {
	money += update;
}

/***************************************************
** Hand
** default constructor
** creates a empty vector
****************************************************/
Hand::Hand(){
	cards.resize(0);
}

/***************************************************
** drawCard
** creates a new card and push backs into vector
****************************************************/
void Hand::drawCard() {
	Card newCard; //creates a random card
	cards.push_back(newCard);
	return;
}

/***************************************************
** resetHand
** makes card vector empty again
****************************************************/
void Hand::resetHand() {
	cards.resize(0);
	return;
}

/***************************************************
** print
** cout's what is in the card vector
****************************************************/
void Hand::print() const{
	for(int i=0; i<cards.size(); i++){
		cout << setw(10) << cards[i].get_rank() << " of "
			<< cards[i].get_suit() << "\n";
	}
}

/***************************************************
** sum
** adds all the cards in the vector
** gives option of ace being valued at 11 or 1
****************************************************/
int Hand::sum() {
	int sum = 0;
	bool haveAce = false;
	int aceCount = 0;
	for(int i=0; i<cards.size(); i++){
		sum += cards[i].rank2num();
		if(cards[i].get_rank() == "Ace"){
			aceCount++;
			haveAce = true;
		}
		if(haveAce && sum > 21){
			if(aceCount >=1){
				sum -= 10;
				aceCount --;
			}
		}
	}
	return sum;
}