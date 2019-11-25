
#include <iostream>
#include <string>

using namespace std;

class Player {

  private:
    int HP; // Max: 100, Min:0

  public:
    Player() { HP = 100; }

    /*------- Player Information Function--------*/

    void setPlayerHP(int hp) {

        if ((this->HP + hp) > 100)
            this->HP = 100;
        else
            this->HP += hp;
    }

    int getPlayerHP(void) { return this->HP; }

    ~Player() {}
};
