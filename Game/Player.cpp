#include "Word.cpp"
#include <iostream>
#include <string>

using namespace std;

class Player {

  private:
    int HP;           // Max: 100, Min:0
    wstring name;     //  사용자 이름
    wstring gradeNum; //  사용자 학번
    Word *word;       // player 고유 Word class

  public:
    Player(wstring name, wstring gradeNum) {

        this->name = name;
        this->gradeNum = gradeNum;
        HP = 100;
        word = new Word();
        word->setAttackWord();
        word->setServerWord();
    }

    Player &operator=(Player &anotherPlayer) {

        if (this == &anotherPlayer)
            return *this;

        this->name = anotherPlayer.name;
        this->gradeNum = anotherPlayer.gradeNum;

        delete word;
        word = anotherPlayer.word;
    }

    /*------- Player Information Function--------*/

    void setPlaerName(wstring name) { this->name = name; }
    void setPlaerGrade(wstring gradeNum) { this->gradeNum = gradeNum; }

    void setPlayerHP(int hp) {

        if ((this->HP + hp) > 100)
            this->HP = 100;
        else
            this->HP += hp;
    }

    wstring getPlayerName(void) { return this->name; }
    wstring getPlayerGrade(void) { return this->gradeNum; }
    int getPlayerHP(void) { return this->HP; }

    /*------- Word Function-------*/

    list<wstring> getAttackWord(void) { return word->getAttackWord(); }
    list<wstring> getServerWord(void) { return word->getServerWord(); }
    void printAttackWord(void) { word->printAttackWord(); }
    void printServerWord(void) { word->printServerWord(); }
    bool deleteServerWord(wstring delWord) { word->deleteServerWord(delWord); }
    bool deleteAttackWord(wstring delWord) { word->deleteAttackWord(delWord); }

    ~Player() { delete word; }
};
