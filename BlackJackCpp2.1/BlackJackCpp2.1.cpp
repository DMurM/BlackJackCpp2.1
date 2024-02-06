
#include <iostream>
#include <random>
#include <ctime>
#include <set>
#include <string>
#include <Windows.h>

using namespace std;

string deckType[4] = { " Spears ", " Hearts ", "Diamonds", " Clubs  " };
int card[13] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11, 12, 13 };

set<pair<int, string>> usedCards; 

pair<int, string> getRandomCard() {
    int randDeckType = rand() % 4;
    int randCard = rand() % 13;
    pair<int, string> cardPair = { randDeckType, to_string(randCard) };

    while (usedCards.count(cardPair) > 0 || randCard == 0) {
        randDeckType = rand() % 4;
        randCard = rand() % 13;
        cardPair = { randDeckType, to_string(randCard) };
    }
    usedCards.insert(cardPair);
    return cardPair;
}

string validarFiguras(int value) {

    if (value == 10)
    {
        return "J";
    }
    else if (value == 11)
    {
        return "Q";
    }
    else if (value == 12)
    {
        return "K";
    }
    else
    {
        return "0";
    };
}

void printCard(const string & suit, int value) {
    
    string figuras = validarFiguras(value);
    
    cout << "" << endl;
    cout << " +-------------+" << endl;
    cout << " |";   
    if (value < 10) {
        cout << " " << value << "           |" << endl;
        cout << " |             |" << endl;
        cout << " |   " << suit << "  |" << endl;
        cout << " |             |" << endl;
        cout << " |          " << value << "  |" << endl;
        cout << " +-------------+" << endl;
    }
    else {
        
        cout << " " << figuras << "           |" << endl;
        cout << " |             |" << endl;
        cout << " |   " << suit << "  |" << endl;
        cout << " |             |" << endl;
        cout << " |          " << figuras << "  |" << endl;
        cout << " +-------------+" << endl;
    }
}

void determinarGanador(int pointsPlayer, int pointsCroupier) {
    
    cout << "Player's points: " << pointsPlayer << endl;
    cout << "Croupier's points: " << pointsCroupier << endl;

    if (pointsPlayer > 21) {
        cout << "\t-------- CROUPIER WINS! --------" << endl;
    }
    else if (pointsCroupier > 21) {
        cout << "\t-------- PLAYER WINS! --------" << endl;
    }
    else if (pointsPlayer > pointsCroupier) {
        cout << "\t-------- PLAYER WINS! --------" << endl;
    }
    else if (pointsCroupier > pointsPlayer) {
        cout << "\t-------- CROUPIER WINS! --------" << endl;
    }
    else {
        cout << "\t-------- IT'S A TIE! --------" << endl;
    }

}

void mostrarCarta(const string& quien, const string& suit, int value) {
    cout << quien << " received the following card:" << endl;
    printCard(suit, value);
    cout << endl;
}

void inicio() {
    cout << "==================================================" << endl;
    cout << "  ____  _            _    _            _    " << endl;
    cout << " |  _ \\| |          | |  | |          | |   " << endl;
    cout << " | |_) | | __ _  ___| | _| | __ _  ___| | __" << endl;
    cout << " |  _ <| |/ _` |/ __| |/ / |/ _` |/ __| |/ /" << endl;
    cout << " | |_) | | (_| | (__|   <| | (_| | (__|   < " << endl;
    cout << " |____/|_|\\__,_|\\___|_|\\_\\_|\\__,_|\\___|_|\\_\\" << endl;
    cout << "==================================================" << endl;
    cout << "Welcome to the Blackjack table!" << endl;
    cout << "Get as close as you can to 21 without going over." << endl;
    cout << "==================================================" << endl;
    cout << endl;
}

void cartasInicialesPlayer(int& pointsPlayer, int& cardsPlayer) {
    cout << "----- The croupier deals the initial cards to the player -----" << endl;

    while (cardsPlayer < 2) {
        pair<int, string> cardPair = getRandomCard();
        int randDeckType = cardPair.first;
        int randCard = stoi(cardPair.second);

        if (randCard == 0) {
            int aceInUser;
            cout << "\tYou got an ACE, do you want a 1 or 11?: ";
            cin >> aceInUser;
            while (aceInUser != 1 && aceInUser != 11) {
                cout << "\tInvalid choice. Please enter 1 or 11: ";
                cin >> aceInUser;
            }
            pointsPlayer += (aceInUser == 1) ? 1 : 11;
        }
        else if (randCard >= 1 && randCard <= 10) {
            randCard += 1;
            //cout << "\tYou got a " << randCard << endl;
            //cout << "\tYou add " << randCard << " points" << endl;
            if (randCard >= 10){
                pointsPlayer += 10;
            }
            else {
                pointsPlayer += randCard;
            }
            
        }
        else if (randCard >= 11 && randCard <= 13) {
            switch (randCard) {
            case 11:
                //cout << "\tYou got a JACK" << endl;
                break;
            case 12:
                //cout << "\tYou got a QUEEN" << endl;
                break;
            case 13:
                //cout << "\tYou got a KING" << endl;
                break;
            }
            cout << "\tYou add 10 points" << endl;
            pointsPlayer += 10;
        }

        mostrarCarta("Player", deckType[randDeckType], randCard);
        cout << "\tYour total points is: " << pointsPlayer << endl;
        cout << " " << endl;
        cardsPlayer += 1;
    }
}

void cartasInicalesCroupier(int& pointsCroupier) {
    cout << "----- The croupier deals the initial cards to himself -----" << endl;

    pair<int, string> cardPair = getRandomCard();
    int randDeckType = cardPair.first;
    int randCard = stoi(cardPair.second);

    if (randCard == 0) {
        //cout << "\tThe croupier got an ACE, it counts as 11" << endl;
        pointsCroupier += 11;
    }
    else if (randCard >= 1 && randCard <= 10) {
        randCard += 1;
        //cout << "\tThe croupier got a " << randCard << endl;
        //cout << "\tIt adds " << randCard << " points" << endl;
        pointsCroupier += randCard;
    }
    else if (randCard >= 11 && randCard <= 13) {
        switch (randCard) {
        case 11:
            //cout << "\tThe croupier got a JACK" << endl;
            break;
        case 12:
            //cout << "\tThe croupier got a QUEEN" << endl;
            break;
        case 13:
            //cout << "\tThe croupier got a KING" << endl;
            break;
        }
        //cout << "\tThe croupier adds 10 points" << endl;
        pointsCroupier += 10;
    }
    cout << "The croupier adds " << randCard << "points" << endl;
    mostrarCarta("Croupier", deckType[randDeckType], randCard);

    cout << "----- The croupier gets the second card -----" << endl;
    //cout << "You will not see it" << endl;
        cout << "The last card was a: " << randCard <<"\n";
    cardPair = getRandomCard();
    randDeckType = cardPair.first;
    randCard = stoi(cardPair.second);

    if (randCard == 0) {
        pointsCroupier += 1;
    }
    else if (randCard >= 1 && randCard <= 10) {
        randCard += 1;
        pointsCroupier += randCard;
    }
    else if (randCard >= 11 && randCard <= 13) {
        pointsCroupier += 10;
    }
}

void carta2Player(int& pointsPlayer) {
    char nextCardChoice;

    do {
        cout << "Do you want another card (Y/N)? You have " << pointsPlayer << " points: ";
        cin >> nextCardChoice;

        if (nextCardChoice == 'Y' || nextCardChoice == 'y') {
            pair<int, string> cardPair = getRandomCard();
            int randDeckType = cardPair.first;
            int randDeckNum = stoi(cardPair.second);

            if (randDeckNum == 0) {
                int aceInUser;
                cout << "\tYou got an ACE, do you want a 1 or 11?: ";
                cin >> aceInUser;
                while (aceInUser != 1 && aceInUser != 11) {
                    cout << "\tInvalid choice. Please enter 1 or 11: ";
                    cin >> aceInUser;
                }
                pointsPlayer += (aceInUser == 1) ? 1 : 11;
            }
            else if (randDeckNum >= 1 && randDeckNum <= 10) {
                randDeckNum += 1;
                cout << "\tYou add " << randDeckNum << " points" << endl;
                pointsPlayer += randDeckNum;
            }
            else if (randDeckNum >= 11 && randDeckNum <= 13) {
                switch (randDeckNum) {
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    break;
                }
                cout << "\tYou add 10 points" << endl;
                pointsPlayer += 10;
            }
            mostrarCarta("Player", deckType[randDeckType], randDeckNum);

            cout << "\tYour total points is: " << pointsPlayer << endl;

            if (pointsPlayer > 21) {
                cout << "\tYou have exceeded 21 points" << endl;
                cout << "\t-------- You lose --------" << endl;
                break;
            }
        
        }
        else if (nextCardChoice == 'N' || nextCardChoice == 'n') {
            cout << "\tYou stay at " << pointsPlayer << " points" << endl;
        }
        else {
            cout << "\tInvalid choice. Please enter Y or N." << endl;
        }
    } while (nextCardChoice != 'N' && nextCardChoice != 'n');
}

void pedirCartasExtraCroupier(int& pointsCroupier, int& pointsPlayer) {

    while (pointsCroupier <= 16 && pointsCroupier < pointsPlayer && pointsPlayer <= 21) {
        pair<int, string> cardPair = getRandomCard();
        int randDeckType = cardPair.first;
        int randCard = stoi(cardPair.second);

        if (randCard == 0) {
            pointsCroupier += (pointsCroupier <= 10) ? 11 : 1;
        }
        else if (randCard >= 1 && randCard <= 10) {
            pointsCroupier += randCard;
        }
        else if (randCard >= 11 && randCard <= 13) {
            pointsCroupier += 10;
        }

        mostrarCarta("Croupier", deckType[randDeckType], randCard);
    }

    cout << "\tThe total points of the croupier is " << pointsCroupier << endl;
}

int main() {
    char jugarDeNuevo;
    do {
        time_t time2;
        time(&time2);
        srand(time2);

        inicio();
        int pointsPlayer = 0;
        int cardsPlayer = 0;
        int pointsCroupier = 0;

        cartasInicialesPlayer(pointsPlayer, cardsPlayer);
        cartasInicalesCroupier(pointsCroupier);
        carta2Player(pointsPlayer);
        pedirCartasExtraCroupier(pointsCroupier, pointsPlayer);

        determinarGanador(pointsPlayer, pointsCroupier);

        cout << "¿Do you wana play again?): ";
        cin >> jugarDeNuevo;

        system("pause");
        system("cls");

    } while (jugarDeNuevo == 'Y' || jugarDeNuevo == 'y');

    return 0;
}