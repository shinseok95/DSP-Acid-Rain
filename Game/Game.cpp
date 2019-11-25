#include "Player.cpp"
#include "typing.cpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstring>
#include <list>
#include <queue>

using namespace sf;
using namespace std;

#define HP_MINUS_VALUE 10
#define HP_PLUS_VALUE 3

class Game {
  private:
    list<Text> temlist;    // 디펜스 단어 임시 리스트
    list<Text> temAtklist; // 공격할 단어 임시 리스트
    list<wstring> serverword; // 서버로부터 받아온 디펜스 단어 리스트
    list<wstring> attackword; // 서버로부터 받아온 공격할 단어 리스트

    Font font;
    Text text;   // 저장될 단어
    Text typing; // 타이핑 단어
    Text result; // 엔터를 쳤을 때 넘어가는 단어

    Player *player;

  public:
    std::wstring TEXTBOX; // 타이핑 단어 임시 저장

    Game();
    ~Game();

    Text getText() { return text; }
    Player &getPlayer() { return *this->player; }
    void setWordColor(Text &text, int randomX);
    void setShape(Texture &texture, Sprite &sprite, Vertex *line1,
                  Vertex *line2, Vertex *line3, Vertex *HPtop, Vertex *HPmiddle,
                  ConvexShape &right, ConvexShape &below, ConvexShape &HPshape,
                  ConvexShape &HPbar, Text &HPtitle, Text &HPtopvalue,
                  Text &HPmidvalue, Text &typing, Text &attack);

    void setTyping(wstring t);
    Text getTyping();
    void setResult(wstring t);
    Text getResult();

    void setServerWord(wstring word);
    void setAttackWord(wstring word);

    void setServerWord(wstring word);
    void setAttackWord(wstring word);

    void setServerWord(wstring word);
    void setAttackWord(wstring word);

    void setResultImage(Texture &texture, Sprite &sprite, bool result);
    void severAtk();
    void update(Time elapsed, Game &game, size_t level);
    void addWord();
    void addAtackWord();

    void attackWord();

    queue<wstring> sendAtkWord; // 공격 성공한 단어 리스트
    list<Text> tlist;           // 떨어지고 있는 단어 리스트
    list<Text> alist;           // 공격할 단어 리스트
    list<Text>::iterator tlistIter;
};

/*-----------------------------------------생성자----------------------------------------------*/

Game::Game() {
    player = new Player();

    /*---- 타이핑 단어 디자인 ----*/
    font.loadFromFile("Nanum.ttf");
    typing.setFont(font);
    typing.setFillColor(sf::Color::White);
    typing.setCharacterSize(30);
    typing.setPosition(170, 648);
}

/*---------------서버로부터 받아온 단어 관련 함수------------------*/

void Game::setServerWord(wstring word) { serverword.push_back(word); }
void Game::setAttackWord(wstring word) { attackword.push_back(word); }

/*-------------------tlist 단어 관련 함수-----------------------------*/

void Game::severAtk() { //임시 단어 리스트 관리

    srand((unsigned int)time(NULL));

    while (temlist.size() != 10) { // 임시 단어 리스트 개수 < 10 (temlist < 10)

        int randomX = rand() % 900; // x좌표 랜덤 지정

        Text newtext = Text(serverword.front(), font, 30);
        newtext.setPosition((float)randomX, 0.f);
        setWordColor(newtext, randomX);

        serverword.pop_front();     // serverword의 단어를 빼서 (pop)
        temlist.push_back(newtext); // temlist에 삽입 (push)
    }
}

void Game::addWord() { // 떨어지고 있는 단어 리스트 추가

    tlist.push_back(temlist.front());
    temlist.pop_front();
}

/*---------------------alist 단어 관련 함수----------------------------*/

void Game::addAtackWord() { // 공격할 단어 리스트 추가 (size가 0일시))

    for (int i = 0; i < 5; i++) {

        alist.push_back(temAtklist.front());
        temAtklist.pop_front();
    }
}

void Game::attackWord() {

    int ypos = 0;

    while (temAtklist.size() < 5) { // temAtklist에 Text 5개 채움

        Text newtext = Text(attackword.front(), font, 27);

        newtext.setPosition(1105, 50 + ypos);
        newtext.setFillColor(sf::Color::Magenta);

        attackword.pop_front();        // attackword의 단어를 빼서 (pop)
        temAtklist.push_back(newtext); // temAtklist에 삽입 (push)

        ypos += 55; // y좌표 지정
    }
}

/*------------------실시간 단어 update ----------------------*/

void Game::update(Time elapsed, Game &game, size_t level) {

    for (tlistIter = tlist.begin(); tlistIter != tlist.end(); ++tlistIter) {

        if (game.result.getString() ==
            (*tlistIter).getString()) { // 떨어지고 있는 단어와 타이핑 단어 비교
            tlist.erase(tlistIter++);
            player->setPlayerHP(HP_PLUS_VALUE); // 동일시 HP +3
            game.result.setString("");
        }

        if (tlistIter->getPosition().y > 580) {
            ++tlistIter;
            tlist.pop_front();

            player->setPlayerHP(
                -HP_MINUS_VALUE); // 단어가 바닥에 닿는 경우 HP -10

        } else
            tlistIter->move(0, elapsed.asSeconds() * 20 *
                                   level); // 게임 난이도 설정
    }

    for (tlistIter = alist.begin();
         tlistIter != alist.end(); // 타이핑 단어와 공격할 단어 비교
         ++tlistIter) {

        if (game.result.getString() ==
            (*tlistIter).getString()) { // 동일시 공격할 단어 삭제 후 서버 전송

            sendAtkWord.push(
                (*tlistIter).getString()); // snedAtkWord에 공격할 단어 저장
            alist.erase(tlistIter++);
            game.result.setString("");
            break;
        }
    }
}

/*------------------------Typing 관련 함수--------------------------*/

void Game::setTyping(wstring t) { typing.setString(t); }
Text Game::getTyping() { return typing; }

void Game::setResult(wstring t) { result.setString(t); }
Text Game::getResult() { return result; }

/*------------------------디자인 함수-----------------------------*/

void Game::setWordColor(Text &text, int randomX) { // 단어 랜덤 색으로

    if (randomX % 3 == 0)
        text.setFillColor(sf::Color::Yellow); // White

    else if (randomX % 3 == 1)
        text.setFillColor(sf::Color::Red); // Red
    else
        text.setFillColor(sf::Color::Green); // Yellow
}

void Game::setResultImage(Texture &texture, Sprite &sprite,
                          bool result) { // 게임 결과 이미지 지정

    if (result) { // true일 때 win

        if (!texture.loadFromFile("winner.jpg")) {

            cout << "image loading error";
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(-500, -250, 1280, 720));

    } else { // false일 때

        if (!texture.loadFromFile("loser.jpg")) {

            cout << "image loading error";
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(-500, -250, 1280, 720));
    }
}

// 게임 디자인 설정

void Game::setShape(Texture &texture, Sprite &sprite, Vertex *line1,
                    Vertex *line2, Vertex *line3, Vertex *HPtop,
                    Vertex *HPmiddle, ConvexShape &right, ConvexShape &below,
                    ConvexShape &HPshape, ConvexShape &HPbar, Text &HPtitle,
                    Text &HPtopvalue, Text &HPmidvalue, Text &typing,
                    Text &attack) {

    /*BG setting*/

    if (!texture.loadFromFile("BG.jpg")) {

        cout << "BG image loading error";
        exit(-1);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 1280, 720));

    /* Line setting*/

    line1[0] = Vertex(Vector2f(0, 610));
    line1[1] = Vertex(Vector2f(1100, 610));
    line2[0] = Vertex(Vector2f(1100, 0));
    line2[1] = Vertex(Vector2f(1100, 720));
    line3[0] = Vertex(Vector2f(1100, 350));
    line3[1] = Vertex(Vector2f(1280, 350));

    /*HP line setting*/

    HPtop[0] = Vertex(Vector2f(1250, 420));
    HPtop[1] = Vertex(Vector2f(1262, 420));

    HPmiddle[0] = Vertex(Vector2f(1250, 570));
    HPmiddle[1] = Vertex(Vector2f(1262, 570));

    /*Right Rectangles setting*/

    right.setPointCount(4); // Rectangles

    right.setPoint(0, sf::Vector2f(1100, 0));
    right.setPoint(3, sf::Vector2f(1100, 720));
    right.setPoint(1, sf::Vector2f(1280, 0));
    right.setPoint(2, sf::Vector2f(1280, 720));

    right.setFillColor(sf::Color::Black);

    /*below Rectangles setting*/

    below.setPointCount(4); // Rectangles

    below.setPoint(0, sf::Vector2f(0, 610));
    below.setPoint(1, sf::Vector2f(1100, 610));
    below.setPoint(2, sf::Vector2f(1100, 720));
    below.setPoint(3, sf::Vector2f(0, 720));

    below.setFillColor(sf::Color::Black);

    /*HP shape setting*/

    HPshape.setPointCount(4);
    HPshape.setPoint(0, sf::Vector2f(1150, 420));
    HPshape.setPoint(1, sf::Vector2f(1250, 420));
    HPshape.setPoint(2, sf::Vector2f(1250, 720));
    HPshape.setPoint(3, sf::Vector2f(1150, 720));

    HPshape.setOutlineColor(sf::Color::White);
    HPshape.setFillColor(sf::Color::Black);
    HPshape.setOutlineThickness(1);

    /* HP bar setting*/

    HPbar.setPointCount(4);
    HPbar.setPoint(0, sf::Vector2f(1150, 420));
    HPbar.setPoint(1, sf::Vector2f(1250, 420));
    HPbar.setPoint(2, sf::Vector2f(1250, 720));
    HPbar.setPoint(3, sf::Vector2f(1150, 720));

    HPbar.setFillColor(sf::Color::Red);

    /*HP text setting*/

    font.loadFromFile("Nanum.ttf");
    HPtitle.setFont(font);
    HPtopvalue.setFont(font);
    HPmidvalue.setFont(font);

    HPtitle.setString(L"HP");
    HPtopvalue.setString(L"100");
    HPmidvalue.setString(L"50");

    HPtitle.setCharacterSize(30);
    HPtopvalue.setCharacterSize(10);
    HPmidvalue.setCharacterSize(10);

    HPtitle.setFillColor(sf::Color::Red);
    HPtopvalue.setFillColor(sf::Color::White);
    HPmidvalue.setFillColor(sf::Color::White);

    HPtitle.setPosition(1180, 380);
    HPtopvalue.setPosition(1262, 410);
    HPmidvalue.setPosition(1262, 560);

    /*Typing & Attack text setting*/

    typing.setFont(font);
    attack.setFont(font);

    typing.setString(L"Defense : ");
    attack.setString(L"Attack");

    typing.setFillColor(sf::Color::White);
    attack.setFillColor(sf::Color::Magenta);

    typing.setCharacterSize(30);
    attack.setCharacterSize(30);

    typing.setPosition(20, 648);
    attack.setPosition(1148, 10);
}

/*------------------------------------소멸자-------------------------------*/

Game::~Game() { delete player; }

//////////////////////////////////////////////////////////////////////
//////////////typing.cpp 내용 복사////////////////////////////////////

int cho = -1, jung = -1, jong = -1;

void combi(std::wstring &Textbox) {
    int com;
    if (cho < 0)
        return;
    else if (jung < 0)
        return;
    else if (jong < 0)
        com = 44032 + (cho * 588) + (jung * 28);
    else
        com = 44032 + (cho * 588) + (jung * 28) + jong;
    Textbox += com;
    cho = -1, jung = -1;
    jong = -1;
}

int tempcombi() {
    int com;
    if (cho < 0)
        return 0;
    else if (jung < 0) {
        switch (cho) {
        case 0:
            return 12593;
            break;
        case 1:
            return 12594;
            break;
        case 2:
            return 12596;
            break;
        case 3:
            return 12599;
            break;
        case 4:
            return 12600;
            break;
        case 5:
            return 12601;
            break;
        case 6:
            return 12609;
            break;
        case 7:
            return 12610;
            break;
        case 8:
            return 12611;
            break;
        case 9:
            return 12613;
            break;
        case 10:
            return 12614;
            break;
        case 11:
            return 12615;
            break;
        case 12:
            return 12616;
            break;
        case 13:
            return 12617;
            break;
        case 14:
            return 12618;
            break;
        case 15:
            return 12619;
            break;
        case 16:
            return 12620;
            break;
        case 17:
            return 12621;
            break;
        case 18:
            return 12622;
            break;
        default:
            return 0;
        }
    } else if (jong < 0)
        com = 44032 + (cho * 588) + (jung * 28);
    else
        com = 44032 + (cho * 588) + (jung * 28) + jong;
}

void typeWord(/*std::wstring &Textbox,*/ sf::Event event, Uint32 uni,
              Game &game) {

    Font f;
    f.loadFromFile("Nanum.ttf");
    Text t;
    Text result;
    uni = event.text.unicode;

    if ((uni >= 'a' && uni <= 'z') || uni == 'Q' || uni == 'W' || uni == 'E' ||
        uni == 'R' || uni == 'T' || uni == 'O' || uni == 'P') {
        if (cho < 0) {
            switch (uni) {
            case 'r':
                cho = 0;
                break;
            case 'R':
                cho = 1;
                break;
            case 's':
                cho = 2;
                break;
            case 'e':
                cho = 3;
                break;
            case 'E':
                cho = 4;
                break;
            case 'f':
                cho = 5;
                break;
            case 'a':
                cho = 6;
                break;
            case 'q':
                cho = 7;
                break;
            case 'Q':
                cho = 8;
                break;
            case 't':
                cho = 9;
                break;
            case 'T':
                cho = 10;
                break;
            case 'd':
                cho = 11;
                break;
            case 'w':
                cho = 12;
                break;
            case 'W':
                cho = 13;
                break;
            case 'c':
                cho = 14;
                break;
            case 'z':
                cho = 15;
                break;
            case 'x':
                cho = 16;
                break;
            case 'v':
                cho = 17;
                break;
            case 'g':
                cho = 18;
                break;
            }
        } else if (jung < 0) {
            switch (uni) {
            case 'k':
                jung = 0;
                break;
            case 'o':
                jung = 1;
                break;
            case 'i':
                jung = 2;
                break;
            case 'O':
                jung = 3;
                break;
            case 'j':
                jung = 4;
                break;
            case 'p':
                jung = 5;
                break;
            case 'u':
                jung = 6;
                break;
            case 'P':
                jung = 7;
                break;
            case 'h':
                jung = 8;
                break;
            case 'y':
                jung = 12;
                break;
            case 'n':
                jung = 13;
                break;
            case 'b':
                jung = 17;
                break;
            case 'm':
                jung = 18;
                break;
            case 'l':
                jung = 20;
                break;
            }
        } else if (jong < 0) {
            switch (uni) {
            case 'k':
                if (jung == 8)
                    jung = 9;
                break;
            case 'o':
                if (jung == 8)
                    jung = 10;
                break;
            case 'j':
                if (jung == 13)
                    jung = 14;
                break;
            case 'p':
                if (jung == 13)
                    jung = 15;
                break;
            case 'l':
                if (jung == 8)
                    jung = 11;
                else if (jung == 13)
                    jung = 16;
                else if (jung == 18)
                    jung = 19;
                break;

            case 'r':
                jong = 1;
                break;
            case 'R':
                jong = 2;
                break;
            case 's':
                jong = 4;
                break;
            case 'e':
                jong = 7;
                break;
            case 'E':
                combi(game.TEXTBOX);
                cho = 4;
                break;
            case 'f':
                jong = 8;
                break;
            case 'a':
                jong = 16;
                break;
            case 'q':
                jong = 17;
                break;
            case 'Q':
                combi(game.TEXTBOX);
                cho = 8;
                break;
            case 't':
                jong = 19;
                break;
            case 'T':
                jong = 20;
                break;
            case 'd':
                jong = 21;
                break;
            case 'w':
                jong = 22;
                break;
            case 'W':
                combi(game.TEXTBOX);
                cho = 13;
                break;
            case 'c':
                jong = 23;
                break;
            case 'z':
                jong = 24;
                break;
            case 'x':
                jong = 25;
                break;
            case 'v':
                jong = 26;
                break;
            case 'g':
                jong = 27;
                break;
            }
        } else {
            switch (uni) {
            case 'r':
                if (jong == 8)
                    jong = 9;
                else {
                    combi(game.TEXTBOX);
                    cho = 0;
                }
                break;
            case 'R':
                combi(game.TEXTBOX);
                cho = 1;
                break;
            case 's':
                combi(game.TEXTBOX);
                cho = 2;
                break;
            case 'e':
                combi(game.TEXTBOX);
                cho = 3;
                break;
            case 'E':
                combi(game.TEXTBOX);
                cho = 4;
                break;
            case 'f':
                combi(game.TEXTBOX);
                cho = 5;
                break;
            case 'a':
                if (jong == 8)
                    jong = 10;
                else {
                    combi(game.TEXTBOX);
                    cho = 6;
                }
                break;
            case 'q':
                if (jong == 8)
                    jong = 11;
                else {
                    combi(game.TEXTBOX);
                    cho = 7;
                }
                break;
            case 'Q':
                combi(game.TEXTBOX);
                cho = 8;
                break;
            case 't':
                if (jong == 1)
                    jong = 3;
                else if (jong == 8)
                    jong = 12;
                else if (jong == 17)
                    jong = 18;
                else {
                    combi(game.TEXTBOX);
                    cho = 9;
                }
                break;
            case 'T':
                combi(game.TEXTBOX);
                cho = 10;
                break;
            case 'd':
                combi(game.TEXTBOX);
                cho = 11;
                break;
            case 'w':
                if (jong == 4)
                    jong = 5;
                else {
                    combi(game.TEXTBOX);
                    cho = 12;
                }
                break;
            case 'W':
                combi(game.TEXTBOX);
                cho = 13;
                break;
            case 'c':
                combi(game.TEXTBOX);
                cho = 14;
                break;
            case 'z':
                combi(game.TEXTBOX);
                cho = 15;
                break;
            case 'x':
                if (jong == 8)
                    jong = 13;
                else {
                    combi(game.TEXTBOX);
                    cho = 16;
                }
                break;
            case 'v':
                if (jong == 8)
                    jong = 14;
                else {
                    combi(game.TEXTBOX);
                    cho = 17;
                }
                break;
            case 'g':
                if (jong == 4)
                    jong = 6;
                else if (jong == 8)
                    jong = 15;
                else {
                    combi(game.TEXTBOX);
                    cho = 18;
                }
                break;
            default:
                int temp;
                switch (jong) {
                case 1:
                    jong = 0;
                    temp = 0;
                    break;
                case 2:
                    jong = 0;
                    temp = 1;
                    break;
                case 3:
                    jong = 1;
                    temp = 9;
                    break;
                case 4:
                    jong = 0;
                    temp = 2;
                    break;
                case 5:
                    jong = 4;
                    temp = 12;
                    break;
                case 6:
                    jong = 4;
                    temp = 18;
                    break;
                case 7:
                    jong = 0;
                    temp = 3;
                    break;
                case 8:
                    jong = 0;
                    temp = 5;
                    break;
                case 9:
                    jong = 8;
                    temp = 0;
                    break;
                case 10:
                    jong = 8;
                    temp = 6;
                    break;
                case 11:
                    jong = 8;
                    temp = 7;
                    break;
                case 12:
                    jong = 8;
                    temp = 9;
                    break;
                case 13:
                    jong = 8;
                    temp = 16;
                    break;
                case 14:
                    jong = 8;
                    temp = 17;
                    break;
                case 15:
                    jong = 8;
                    temp = 18;
                    break;
                case 16:
                    jong = 0;
                    temp = 6;
                    break;
                case 17:
                    jong = 0;
                    temp = 7;
                    break;
                case 18:
                    jong = 17;
                    temp = 9;
                    break;
                case 19:
                    jong = 0;
                    temp = 9;
                    break;
                case 20:
                    jong = 0;
                    temp = 10;
                    break;
                case 21:
                    jong = 0;
                    temp = 11;
                    break;
                case 22:
                    jong = 0;
                    temp = 12;
                    break;
                case 23:
                    jong = 0;
                    temp = 14;
                    break;
                case 24:
                    jong = 0;
                    temp = 15;
                    break;
                case 25:
                    jong = 0;
                    temp = 16;
                    break;
                case 26:
                    jong = 0;
                    temp = 17;
                    break;
                case 27:
                    jong = 0;
                    temp = 18;
                    break;
                }
                combi(game.TEXTBOX);
                cho = temp;
                switch (uni) {
                case 'k':
                    jung = 0;
                    break;
                case 'o':
                    jung = 1;
                    break;
                case 'i':
                    jung = 2;
                    break;
                case 'O':
                    jung = 3;
                    break;
                case 'j':
                    jung = 4;
                    break;
                case 'p':
                    jung = 5;
                    break;
                case 'u':
                    jung = 6;
                    break;
                case 'P':
                    jung = 7;
                    break;
                case 'h':
                    jung = 8;
                    break;
                case 'y':
                    jung = 12;
                    break;
                case 'n':
                    jung = 13;
                    break;
                case 'b':
                    jung = 17;
                    break;
                case 'm':
                    jung = 18;
                    break;
                case 'l':
                    jung = 20;
                    break;
                }
            }
        }
    } else if (uni == 13 || uni == 32) {
        combi(game.TEXTBOX);
        game.setResult(game.TEXTBOX);
        game.TEXTBOX.clear();
    } else if (uni == 8) {
        if (cho < 0)
            game.TEXTBOX = game.TEXTBOX.substr(0, game.TEXTBOX.size() - 1);
        else if (jung < 0)
            cho = -1;
        else if (jong < 0)
            jung = -1;
        else
            jong = -1;
    }
}
