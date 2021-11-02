#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>

enum suit
{
    H = 1, S, D, C
};

enum nominal
{
    A = 1, II, III, IV, V, VI, VII, VIII, IX, X, J, Q, K
};
class Card
{
public:
    Card(nominal _nominal, suit _suit)
    {
        m_nominal = _nominal;
        m_suit = _suit;
        m_shown = true;
    }

    void Flip()
    {
        m_shown = !m_shown;
    }

    bool getShown() const
    {
        return m_shown;
    }

    nominal getValue() const
    {
        switch (m_nominal)
        {
        case A:
            return A;
            break;
        case II:
            return II;
            break;
        case III:
            return III;
            break;
        case IV:
            return IV;
            break;
        case V:
            return V;
            break;
        case VI:
            return VI;
            break;
        case VII:
            return VII;
            break;
        case VIII:
            return VIII;
            break;
        case IX:
            return IX;
            break;
        case X:
            return X;
            break;
        case J:
            return J;
            break;
        case Q:
            return Q;
            break;
        case K:
            return K;
            break;
        default:
            throw "Error 1: Wrong card nominal";
            break;
        }
    }

    std::string getSuit() const
    {
        switch (m_suit)
        {
        _setmode(_fileno(stdout), _O_U8TEXT);
        case H:
            return "\x2665";
            break;
        case S:
            return "\x2660";
            break;
        case D:
            return "\x2666";
            break;
        case C:
            return "\x2663";
            break;
        default:
            return "Error 2: Wrong card suit";
            break;
        };
    }
    ~Card()
    {

    }
    friend std::ostream& operator << (std::ostream& out, const Card& card);
private:
    nominal m_nominal;
    suit m_suit;
    bool m_shown;
};

std::ostream& operator << (std::ostream& out, const Card& card)
{
    if (card.getShown())
    {
        switch (card.getValue())
        {
        case A:
        {
            out << card.getSuit() << "|" << "A" << std::endl;
            break;
        }
        case II:
        {
            out << card.getSuit() << "|" << "II" << std::endl;
            break;
        }
        case III:
        {
            out << card.getSuit() << "|" << "III" << std::endl;
            break;
        }
        case IV:
        {
            out << card.getSuit() << "|" << "IV" << std::endl;
            break;
        }
        case V:
        {
            out << card.getSuit() << "|" << "V" << std::endl;
            break;
        }
        case VI:
        {
            out << card.getSuit() << "|" << "VI" << std::endl;
            break;
        }
        case VII:
        {
            out << card.getSuit() << "|" << "VII" << std::endl;
            break;
        }
        case VIII:
        {
            out << card.getSuit() << "|" << "VIII" << std::endl;
            break;
        }
        case IX:
        {
            out << card.getSuit() << "|" << "IX" << std::endl;
            break;
        }
        case X:
        {
            out << card.getSuit() << "|" << "X" << std::endl;
            break;
        }
        case J:
        {
            out << card.getSuit() << "|" << "J" << std::endl;
            break;
        }
        case Q:
        {
            out << card.getSuit() << "|" << "Q" << std::endl;
            break;
        }
        case K:
        {
            out << card.getSuit() << "|" << "K" << std::endl;
            break;
        }
        default:
            break;
        }
    }
    else
    {
        out << "XX" << std::endl;;
    }
    return out;
}

class Hand
{
protected:
    std::vector<Card*> m_hand;
public:

    void Add(Card* _newcard)
    {
        m_hand.push_back(_newcard);
    }
    void Clear()
    {
        m_hand.clear();
    }
    unsigned int GetValue() const
    {
        int count = 0;
        size_t A_counter = 0;
        for (size_t i = 0; i < m_hand.size(); i++)
        {
            if (m_hand[i]->getValue() == A)
            {
                count += 11;
                A_counter++;
            }
            else if (m_hand[i]->getValue() == K || m_hand[i]->getValue() == Q || m_hand[i]->getValue() == J || m_hand[i]->getValue() == X)
            {
                count += 10;
            }
            else if (m_hand[i]->getValue() == IX)
            {
                count += 9;
            }
            else if (m_hand[i]->getValue() == VIII)
            {
                count += 8;
            }
            else if (m_hand[i]->getValue() == VII)
            {
                count += 7;
            }
            else if (m_hand[i]->getValue() == VI)
            {
                count += 6;
            }
            else if (m_hand[i]->getValue() == V)
            {
                count += 5;
            }
            else if (m_hand[i]->getValue() == IV)
            {
                count += 4;
            }
            else if (m_hand[i]->getValue() == III)
            {
                count += 3;
            }
            else if (m_hand[i]->getValue() == II)
            {
                count += 2;
            }
        }
        size_t A_sub = 0;
        while (count > 21 && A_counter != A_sub)
        {
            count -= 10;
            A_sub++;
        }
        return count;
    }
    size_t getSize() const
    {
        return m_hand.size();
    }
    Card getCard(size_t i) const
    {
        return *m_hand[i];
    }
    virtual ~Hand()
    {

    }
};

class GenericPlayer : public Hand
{
private:
    std::string m_name;
public:
    GenericPlayer(std::string _name)
    {
        m_name = _name;
    }
    virtual bool IsHitting() = 0;// ЧИСТО ВИРТУАЛЬНЫЙ МЕТОД // const
    bool IsBoosted() //const тут если писать const, то компилятор выдаёт ошибку
    {
        return GetValue() > 21;
    }
    void Bust() const
    {
        std::cout << m_name << " is bust ";
    }
    std::string getName() const
    {
        return m_name;
    }
    friend std::ostream& operator << (std::ostream& out, const GenericPlayer& play);
};
std::ostream& operator << (std::ostream& out, const GenericPlayer& play)
{
    out << play.getName() << std::endl;
    for (size_t i = 0; i < play.getSize(); i++)
    {
        out << play.getCard(i);
    }
    return out;
}

class Player : public GenericPlayer
{
public:
    Player(std::string _name) : GenericPlayer(_name)
    {

    }
    virtual bool IsHitting() override
    {
        std::cout << getName() << " anouther card? Y/N" << std::endl;
        bool check = true;
        while (check)
        {
            char ask;
            std::cin >> ask;
            if (ask == 'Y' || ask == 'y' || ask == 'n' || ask == 'N')
            {
                if (ask == 'Y' || ask == 'y')
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    void Win() const
    {
        std::cout << "Winner is " << getName() << std::endl;
    }
    void Lose() const
    {
        std::cout << getName() << " lost!" << std::endl;
    }
    void Push() const
    {
        std::cout << "The " << getName() << " played a draw!" << std::endl;
    }
};

class House : public GenericPlayer
{
public:
    House(std::string _name = "AI") : GenericPlayer(_name)
    {

    }
    virtual bool IsHitting()
    {
        if (GetValue() <= 16)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void FlipFirstCard()
    {
        m_hand[0]->Flip();
    }
};

class Deck : public Hand
{
public:
    Deck()
    {
        m_hand.reserve(52);
        Populate();
        Shuffle();
    }
    void Populate()
    {
        Clear();

        for (int s = H; s <= C; ++s)
        {
            for (int r = A; r <= K; ++r)
            {
                Add(new Card(static_cast<nominal>(r), static_cast<suit>(s)));
            }
        }
    }
    void Shuffle()
    {
        srand(time(0));
        std::random_shuffle(m_hand.begin(), m_hand.end());
    }
    void Deal(Hand& aHand)
    {
        if (!m_hand.empty())
        {
            aHand.Add(m_hand.back());
            m_hand.pop_back();
        }
        else
        {
            std::cout << "Out of cards" << std::endl;
        }
    }
    void AddltionalCards(GenericPlayer& aGenerlcPlayer)
    {
        while (aGenerlcPlayer.IsHitting())
        {
            Deal(aGenerlcPlayer);
            std::cout << aGenerlcPlayer << aGenerlcPlayer.GetValue() << std::endl;
        }
    }
};

class Game
{
private:
    House m_house;
    std::vector<Player> m_players;
    Deck m_deck;
    unsigned int m_NumberOfPlayers;
public:
    Game(unsigned int _NumberOfPlayers)
    {
        m_NumberOfPlayers = _NumberOfPlayers;
    }
    void play()
    {
        for (size_t i = 0; i < m_NumberOfPlayers; i++)
        {
            std::cout << "Enter player name " << char(252) << i << std::endl;
            std::string name;
            std::cin >> name;
            m_players.push_back(Player(name));
            m_deck.Deal(m_players[i]);
            m_deck.Deal(m_players[i]);
        }
        m_deck.Deal(m_house);
        m_deck.Deal(m_house);
        m_house.FlipFirstCard();
        std::cout << m_house;
        for (size_t i = 0; i < m_NumberOfPlayers; i++)
        {
            std::cout << m_players[i] << m_players[i].GetValue() << std::endl;
        }
        for (size_t i = 0; i < m_NumberOfPlayers; i++)
        {
            m_deck.AddltionalCards(m_players[i]);
        }
        m_deck.AddltionalCards(m_house);
        m_house.FlipFirstCard();
        std::cout << m_house << m_house.GetValue() << std::endl;
        for (size_t i = 0; i < m_NumberOfPlayers; i++)
        {
            if (m_players[i].IsBoosted())
            {
                m_players[i].Lose();
            }
            else if (m_players[i].GetValue() == m_house.GetValue())
            {
                m_players[i].Push();
            }
            else if (m_players[i].GetValue() < m_house.GetValue())
            {
                m_players[i].Lose();
            }
            else
            {
                m_players[i].Win();
            }
        }
        m_house.Clear();
        for (size_t i = 0; i < m_NumberOfPlayers; i++)
        {
            m_players[i].Clear();
        }
    }
};

int main()
{
    bool check = true;
    while (check)
    {
        unsigned int NumPlayers;
        std::cout << "How many players are in the game?" << std::endl;
        std::cin >> NumPlayers;
        Game BJ(NumPlayers);
        BJ.play();
        std::cout << "Play anather game?" << std::endl;
        char play;
        std::cin >> play;
        if (play == 'N' || play == 'n')
        {
            check = false;
        }
        system("cls");
    }
    
}