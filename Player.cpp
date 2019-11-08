#include "Word.cpp"
#include <iostream>
#include <string>

using namespace std;

class Player {

  private:
    int HP;          // Max: 100, Min:0
    string name;     //  사용자 이름
    string gradeNum; //  사용자 학번
    Word *word;      // player 고유 Word class

  public:
    Player(string name, string gradeNum) {

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

    void setPlaerName(string name) { this->name = name; }
    void setPlaerGrade(string gradeNum) { this->gradeNum = gradeNum; }
    void setPlayerHP(int);
    string getPlayerName(void) { return this->name; }
    string getPlayerGrade(void) { return this->gradeNum; }
    int getPlayerHP(void) { return this->HP; }

    /*------- Word Function-------*/

    list<string> getAttackWord(void) { return word->getAttackWord(); }
    list<string> getServerWord(void) { return word->getServerWord(); }
    void printAttackWord(void) { word->printAttackWord(); }
    void printServerWord(void) { word->printServerWord(); }
    bool deleteServerWord(string delWord) { word->deleteServerWord(delWord); }
    bool deleteAttackWord(string delWord) { word->deleteAttackWord(delWord); }

    ~Player() { delete word; }
};
