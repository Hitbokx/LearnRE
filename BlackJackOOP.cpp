#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <iostream>
#include <random> 

class Card
{
public:
    enum Suit
    {
        club,
        diamond,
        heart,
        spade,

        max_suit
    };

    enum Rank
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
        rank_jack,
        rank_queen,
        rank_king,
        rank_ace,

        max_rank
    };
private:
    Rank m_rank{};
    Suit m_suit{};
public:
    Card(Rank rank = Rank::rank_2, Suit suit = Suit::club) :m_rank{ rank }, m_suit{ suit }{}
    void print()    const
    {
        switch (m_rank)
        {
            case Rank::rank_2:      std::cout << '2';   break;
            case Rank::rank_3:      std::cout << '3';   break;
            case Rank::rank_4:      std::cout << '4';   break;
            case Rank::rank_5:      std::cout << '5';   break;
            case Rank::rank_6:      std::cout << '6';   break;
            case Rank::rank_7:      std::cout << '7';   break;
            case Rank::rank_8:      std::cout << '8';   break;
            case Rank::rank_9:      std::cout << '9';   break;
            case Rank::rank_10:     std::cout << 'T';   break;
            case Rank::rank_jack:   std::cout << 'J';   break;
            case Rank::rank_queen:  std::cout << 'Q';   break;
            case Rank::rank_king:   std::cout << 'K';   break;
            case Rank::rank_ace:    std::cout << 'A';   break;
            default:                std::cout << '?';   break;
        }

        switch (m_suit) 
        {
            case Suit::club:       std::cout << 'C';   break;
            case Suit::diamond:    std::cout << 'D';   break;
            case Suit::heart:      std::cout << 'H';   break;
            case Suit::spade:      std::cout << 'S';   break;
            default:               std::cout << '?';   break;
        }
    }

    int value()  const
    {
        switch (m_rank)
        {
            case Rank::rank_2:        return 2;
            case Rank::rank_3:        return 3;
            case Rank::rank_4:        return 4;
            case Rank::rank_5:        return 5;
            case Rank::rank_6:        return 6;
            case Rank::rank_7:        return 7;
            case Rank::rank_8:        return 8;
            case Rank::rank_9:        return 9;
            case Rank::rank_10:       return 10;
            case Rank::rank_jack:     return 10;
            case Rank::rank_queen:    return 10;
            case Rank::rank_king:     return 10;
            case Rank::rank_ace:      return 11;
            default:
                assert(false && "should never happen");
                return 0;
        }
    }

    friend class Deck;
};

using DeckType = std::array<Card, 52>;

class Deck
{
private:
    DeckType m_deck{};
    Card m_card{};
    int m_cardIndex{ 0 };
public:
    Deck()
    {
        for (int i{ 0 }; i < (static_cast<int>(Card::Suit::max_suit)); ++i)// 
        {
            m_card.m_suit = { static_cast<Card::Suit>(i) };
            for (int iterator{ 0 }; iterator < (static_cast<int>(Card::Rank::max_rank)); ++iterator)
            {
                m_card.m_rank = { static_cast<Card::Rank>(iterator) };
                m_deck[iterator + 13 * i] = { m_card };
            }
        }
    }
    void print()    const
    {
        for (const auto& card : m_deck)
        {
            card.print();
            std::cout << ' ';
        }

        std::cout << '\n';
    }

    void shuffle() 
    {
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
     
        std::shuffle(m_deck.begin(), m_deck.end(), mt);

        m_cardIndex = 0;
    }

    const Card& dealCard() 
    {
        return  m_deck[m_cardIndex++];
    }
};

constexpr int g_maximumScore{ 21 };

constexpr int g_minimumDealerScore{ 17 };

class Player
{
private:
    int m_score{};
public:
    int drawCard( Deck& m_deck)
    {
        int cardVal{ m_deck.dealCard().value() };
        m_score += cardVal;
        return cardVal;
    }

    int score() const
    {
        return m_score;
    }

    bool isBust()   const
    {
        return m_score > g_maximumScore;
    }
};

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case 'h':
                return true;
            case 's':
                return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn( Deck& deck, Player& player)
{
    while(true)
    {
        if (player.isBust())
        {
            std::cout << "You busted!\n";
            return player.isBust();
        }
        else 
        {
            if (playerWantsHit())
            {
                int cardVal{ player.drawCard(deck) };
                std::cout << "You were dealt a " << cardVal << " and now have " << player.score() << '\n';
            }
            else
            {
                return player.isBust();
            }
        }
    }
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    // Draw cards until we reach the minimum value.
    while (dealer.score() < g_minimumDealerScore)
    {
        int cardValue{ dealer.drawCard(deck) };
        std::cout << "The dealer turned up a " << cardValue << " and now has " << dealer.score() << '\n';

    }
    
    if (dealer.score() > g_maximumScore)
    {
        return dealer.isBust();
    }

    return dealer.isBust();
}

bool playBlackjack( Deck& deck)
{
    Player dealer{};

    dealer.drawCard(deck);
    std::cout << "The dealer is showing: " << dealer.score() << '\n';

    // Create the player and give them 2 cards.
    Player player{};
    player.drawCard(deck);
    player.drawCard(deck);
    std::cout << "You have: " << player.score() << '\n';

    if (playerTurn(deck, player))
    {
        // The player went bust.
        std::cout << "You busted!";
        return false;
    }

    if (dealerTurn(deck, dealer))
    {
        // The dealer went bust, the player wins.
        std::cout << "The dealer busted!";
        return true;
    }

    return (player.score() > dealer.score());
}

int main()
{
    Deck deck{};
    deck.shuffle();
    deck.print();
    if (playBlackjack(deck))
    {
        std::cout << "YOU WIN!\n";
    }
    else
    {
        std::cout << "YOU LOSE!\n";
    }

    return 0;
}