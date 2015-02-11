/***************************************************
** hw8.cpp
** Black Jack Game
** Patrick Xie, 03/05/10
****************************************************/
#include <iostream>
#include "cards.h"
#include <ctime>
#include <string>

using namespace std;

int main(){

	srand( (int) time(0)); //generates the random cards
	Player dollars(100); //initial amount of money the player is given 

	//variables
	Hand player1;
	Hand dealer;
	string response;
	int bet;

	//loop of the game and checks when the player wins more than $1000 or loses all the money
	while(dollars.get_money() > 0 && dollars.get_money() < 1000){
		cout<< "You have $" << dollars.get_money() << ". Enter bet: ";
		cin >> bet;

		//loop that checks whether the player is inputing the correct amount in bet
		while (bet> dollars.get_money() || bet < 0){
			cout<<"\nYou only have $" << dollars.get_money() << " to bet! Enter a new bet: ";
			cin >> bet;
		}

		//player draw cards and puts into the player vector
		player1.drawCard();
		player1.drawCard();
		bool pNotBusted = true;

		/*loop for the player which asks if player wants a card
		if user doesn't want a card, then inputs something other than
		y or Y. Also checks if the player busts(sum > 21)*/
		do{
			cout<< "\nYour cards are:\n";
			player1.print();
			cout<< "Your total is " << player1.sum() << ".";
			if(player1.sum() > 21){
				cout<<" You busted!";
				pNotBusted = false;
			}
			if(player1.sum() <= 21){
				cout<<" Do you want another card (y/n)?";
				cin>>response;
				if(response == "y" || response == "Y")
					player1.drawCard();
				else
					pNotBusted = false;
			}
		}while(pNotBusted);

		//dealer draws two cards and adds into dealer vector
		dealer.drawCard();
		dealer.drawCard();
		bool dNotBusted = true;

		/*loop in which the dealer draws cards if it has less than or equal
		to a sum of 16. if the player busts, the dealer does nothing and 
		the player will lose the betted amount. if the dealer busts then
		the player wins the bet.*/
		while(dNotBusted){
			cout << "\n\nThe dealer's cards are:\n";
			dealer.print();
			cout<< "The dealer's total is " << dealer.sum() <<".";
			if(dealer.sum() > 16 && dealer.sum() <= 21)
				dNotBusted = false;
			if(dealer.sum() >21){
				dNotBusted = false;
				cout<< " The dealer has busted.";
			}
			if(player1.sum() >21)
				dNotBusted = false;
			if(dealer.sum() <= 16 && dNotBusted){
				cout<< " The dealer draws one card.\n";
				dealer.drawCard();
				dNotBusted = true;
			}
		}

		/*if statements to check if the player won or lost or tied
		then gives an update to the amount of money the player has*/
		if(player1.sum() > dealer.sum() && player1.sum() <= 21 || dealer.sum()>21){
			cout<<" You win $" << bet << "!\n\n";
			dollars.change_money(bet);
		}
		if(dealer.sum() > player1.sum() && dealer.sum() <= 21 || player1.sum() > 21){
			cout<< " Too bad. You lose $" << bet <<".\n\n";
			dollars.change_money(-bet);
		}
		if(dealer.sum() <= 21 && player1.sum() <= 21 && dealer.sum() == player1.sum())
			cout<< " Tied. You don't win or lose anything.\n\n";
		//resets the player and dealer's hands(vectors) to start a new game
		player1.resetHand();
		dealer.resetHand();
	}

	//cout statements telling the player if he won or lost the entire game
	if (dollars.get_money() <= 0)
		cout<< "You are out of money. GAME OVER.\n";
	if (dollars.get_money() >= 1000)
		cout<< "YOU WIN. You have $1000 or more. GAME OVER.\n";
return 0;
}
