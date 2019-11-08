#include "Player.cpp"
#include <iostream>
#include <list>

using namespace std;

int main(void) { // Player Test;

    Player *player1 = new Player("신현석", "2015906051");
    Player *player2 = new Player("아이유", "20191231234");
    cout << player1->getPlayerName() << endl;
    cout << player1->getPlayerGrade() << endl;
    cout << endl << endl;

    player1->printAttackWord();
    cout << endl << endl << endl;

    cout << player2->getPlayerName() << endl;
    cout << player2->getPlayerGrade() << endl;
    cout << endl << endl;

    player2->printAttackWord();
    cout << endl << endl << endl;

    player1 = player2;

    cout << player1->getPlayerName() << endl;
    cout << player1->getPlayerGrade() << endl;
    cout << endl << endl;

    player1->printAttackWord();
}
