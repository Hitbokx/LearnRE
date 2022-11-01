#include <iostream>
#include <array>

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
		case rank_10:		std::cout << '10';		break;
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
using cardIndex = Deck::size_type;

Deck createDeck()
{	
	Card card{};
	Deck deck{};
	for (int i{ 0 }; i < (static_cast<int>(CardSuit::max_suit)); ++i)
	{
		for (int i{ 0 }; (static_cast<CardRank>(i)) < CardRank::max_rank; ++i)
		{
			card.suit={  };
		}
	}

	return deck;
}

void printDeck(Deck& deck)
{
	for (Card card : deck)
	{
		//printCard(card);
		std::cout << ' ';
	}
}

int main()
{
	auto deck{ createDeck() };
	printDeck(deck);

	return 0;
}