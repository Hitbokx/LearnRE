#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cassert>
#include <numeric>

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_Jack,
	rank_Queen,
	rank_King,
	rank_Ace,

	max_rank,
};

enum class CardSuit
{
	clubs,
	diamonds,
	hearts,
	spades,

	max_suit,
};

enum class BlackJack
{
	win,
	lose,
	tie,
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};

void printCard(const Card& card)
{
	switch (card.rank)
	{
		using enum CardRank;
		case rank_2:		std::cout << '2';		break;
		case rank_3:		std::cout << '3';		break;
		case rank_4:		std::cout << '4';		break;
		case rank_5:		std::cout << '5';		break;
		case rank_6:		std::cout << '6';		break;
		case rank_7:		std::cout << '7';		break;
		case rank_8:		std::cout << '8';		break;
		case rank_9:		std::cout << '9';		break;
		case rank_10:		std::cout << "10";		break;
		case rank_Jack:		std::cout << 'J';		break;
		case rank_Queen:	std::cout << 'Q';		break;
		case rank_King:		std::cout << 'K';		break;
		case rank_Ace:		std::cout << 'A';		break;
		default:			std::cout << "????";	break;
	}
	switch (card.suit)
	{
		using enum CardSuit;
		case clubs:			std::cout << 'C';		break;
		case diamonds:		std::cout << 'D';		break;
		case hearts:		std::cout << 'H';		break;
		case spades:		std::cout << 'S';		break;
		default:			std::cout << "????";	break;
	}
}

using Deck = std::array<Card, 52>;

Deck createDeck()
{
	Card card{};
	Deck deck{};

	for (int i{ 0 }; i < (static_cast<int>(CardSuit::max_suit)); ++i)// 
	{
		card.suit = { static_cast<CardSuit>(i) };
		for (int iterator{ 0 }; iterator < (static_cast<int>(CardRank::max_rank)); ++iterator)
		{
			card.rank = { static_cast<CardRank>(iterator) };
			deck[iterator + 13 * i] = { card };
		}
	}

	return deck;
}

void printDeck(const Deck& deck)
{
	for (const Card& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}
}

using Deck = std::array<Card, 52>;

Deck shuffleDeck(Deck& deck)
{
	/*std::random_device rd;
	std::seed_seq ss{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };*/

	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(deck.begin(), deck.end(), mt);
	return deck;
}

int getCardValue(const Card& card)
{
	using enum CardRank;
	switch (card.rank)
	{
		case rank_2:		return 2;
		case rank_3:		return 3;
		case rank_4:		return 4;
		case rank_5:		return 5;
		case rank_6:		return 6;
		case rank_7:		return 7;
		case rank_8:		return 8;
		case rank_9:		return 9;
		case rank_10:		return 10;
		case rank_Jack:		return 10;
		case rank_Queen:	return 10;
		case rank_King:		return 10;
		case rank_Ace:		return 11;
		default:			assert(false && "Should never happen!");	return 0;
	}
}

using PlayerDeck = std::vector<Card>;
using DealerDeck = std::vector<Card>;

PlayerDeck getPlayerDeck(Deck& shuffledDeck)
{
	PlayerDeck playerDeck{};

	playerDeck.resize(2);
	int usedCards{ 3 };

	for (int i{ 1 }; i < usedCards; i++)
	{
		playerDeck[i - 1] = { shuffledDeck[i] };
	}
	return playerDeck;
}

DealerDeck getDealerDeck(Deck& shuffledDeck)
{
	DealerDeck dealerDeck{ };

	dealerDeck.resize(1);
	for (int i{ 0 }; i < 1; i++)
	{
		dealerDeck[i] = { shuffledDeck[i] };
	}

	return dealerDeck;
}

std::string getInput()
{
	std::cout << "Please 'Hit' or 'Stand': ";
	std::string input{};
	std::cin >> input;

	return input;
}

int maxScore{ 21 };

int calculatePlayerScore(Deck& shuffledDeck, PlayerDeck& playerDeck, int dealerCards)
{
	int playerScore{ 0 };
	{
		int playerScore{ 0 };

		for (Card& card : playerDeck)
		{
			playerScore = playerScore + getCardValue(card);
		}
		std::cout << "You have score of: " << playerScore << " and ";
		std::cout << "your cards are: ";
		for (Card& card : playerDeck)
		{
			printCard(card);
			std::cout << ' ';
			playerScore += getCardValue(card);
		}
		std::cout << '\n';
	}
	std::string input{ getInput() };

	while (input == "Hit" || input == "hit" || input == "HIT")
	{
		int playerCards{ 0 };

		for (Card& card : playerDeck)
		{
			++playerCards;
		}

		int cardsUsed{ playerCards + dealerCards };
		int nextCard{ cardsUsed + 1 };

		Card cardDrawn{ shuffledDeck[nextCard - 1] };

		playerDeck.resize(cardsUsed);
		playerDeck[cardsUsed - 1] = cardDrawn;
		int playerScore1{ 0 };

		std::cout << "Your cards are: ";
		for (Card& card : playerDeck)
		{
			printCard(card);
			std::cout << ' ';
			playerScore1 += getCardValue(card);
		}
		std::cout << '\n';

		std::cout << "You were dealt a : ";
		printCard(playerDeck[cardsUsed - 1]);
		std::cout << " and now have: " << playerScore1;
		std::cout << '\n';

		if (playerScore1 > maxScore)
			return playerScore1;

		input = getInput();
	}

	if (input == "Stand" || input == "stand")
	{
		for (Card& card : playerDeck)
		{
			playerScore += getCardValue(card);
		}

		std::cout << "Your current score is: " << playerScore << '\n';

		return playerScore;
	}
}

int calculateDealerScore(Deck& shuffledDeck, DealerDeck& dealerDeck, int playerCards)
{
	int dealerScore{ 0 };
	constexpr int maxDealerScore{ 17 };
	int cardDrawnValue{};

	for (Card& card : dealerDeck)
	{
		dealerScore += getCardValue(card);
	}
	while (dealerScore < maxDealerScore)
	{
		int dealerCards{ 0 };
		for (Card& card : dealerDeck)
		{
			++dealerCards;
		}

		int cardsUsed{ playerCards + dealerCards };
		int nextCard{ cardsUsed + 1 };

		Card cardDrawn{ shuffledDeck[nextCard - 1] };

		dealerDeck.resize(cardsUsed - 1);
		dealerDeck[cardsUsed - 2] = cardDrawn;
		cardDrawnValue += getCardValue(cardDrawn);

		dealerScore += getCardValue(cardDrawn);
	}
	std::cout << "The Dealer has turned up a score of " << cardDrawnValue << " and now has: " << dealerScore << '\n';

	return dealerScore;
}

int getPlayerCards(PlayerDeck& playerDeck)
{
	int playerCards{ 0 };
	for (Card& card : playerDeck)
	{
		++playerCards;
	}
	return playerCards;
}

int getDealerCards(DealerDeck& dealerDeck)
{
	int dealerCards{ 0 };
	for (Card& card : dealerDeck)
	{
		++dealerCards;
	}
	return dealerCards;
}

BlackJack playBlackJack(Deck& shuffledDeck)
{
	PlayerDeck playerDeck{ getPlayerDeck(shuffledDeck) };
	DealerDeck dealerDeck{ getDealerDeck(shuffledDeck) };

	std::cout << "The dealer is showing: " << getCardValue(shuffledDeck[0]) << '\n';
	int playerCards{ getPlayerCards(playerDeck) };
	int dealerCards{ getDealerCards(dealerDeck) };

	int playerScore{ calculatePlayerScore(shuffledDeck,playerDeck,dealerCards) };
	playerCards = getPlayerCards(playerDeck);
	if (playerScore > maxScore)
	{
		std::cout << "You busted!\n";
		return BlackJack::lose;
	}

	int dealerScore{ calculateDealerScore(shuffledDeck,dealerDeck,playerCards) };
	dealerCards = getDealerCards(dealerDeck);

	if (dealerScore > maxScore)
	{
		std::cout << "The dealer busted!\n";
		return BlackJack::win;
	}

	if (dealerScore < playerScore)
	{
		std::cout << "You outscored the Dealer!\n";
		return BlackJack::win;
	}
	else if (dealerScore == playerScore)
		return BlackJack::tie;

	else
	{
		std::cout << "The Dealer outscored you!\n";
		return BlackJack::lose;
	}
}

int main()
{
	auto deck{ createDeck() };
	auto shuffledDeck{ shuffleDeck(deck) };
	printDeck(shuffledDeck);
	std::cout << '\n';

	BlackJack blackJack{ playBlackJack(shuffledDeck) };

	switch (blackJack)
	{
		using enum BlackJack;
		case win:	std::cout << "YOU WON!";		break;
		case lose:	std::cout << "YOU LOST!";		break;
		case tie:	std::cout << "IT'S A TIE!";		break;
	}

	return 0;
}