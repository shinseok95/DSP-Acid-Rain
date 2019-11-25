#include "Player.cpp"
#include "typing.cpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstring>
#include <list>

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

    void setResultImage(Texture &texture, Sprite &sprite, bool result);
    void severAtk();
    void update(Time elapsed, Text t, size_t level);
    void addWord();
    void addAtackWord();

    void attackWord();

    list<Text> tlist; // 떨어지고 있는 단어 리스트
    list<Text> alist; // 공격할 단어 리스트
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

    serverword.push_back(L"스타크래프트");
    serverword.push_back(L"리그오브레전드");
    serverword.push_back(L"오버워치");
    serverword.push_back(L"서든어택");
    serverword.push_back(L"메이플스토리");
    serverword.push_back(L"던전앤파이터");
    serverword.push_back(L"피파온라인");
    serverword.push_back(L"리니지");
    serverword.push_back(L"도타");
    serverword.push_back(L"하스스톤");

    attackword.push_back(L"방");
    attackword.push_back(L"탄");
    attackword.push_back(L"소");
    attackword.push_back(L"년");
    attackword.push_back(L"단");
    attackword.push_back(L"김");
    attackword.push_back(L"치");
    attackword.push_back(L"찌");
    attackword.push_back(L"개");
    attackword.push_back(L"를");
    attackword.push_back(L"좋");
    attackword.push_back(L"아");
    attackword.push_back(L"해");
    attackword.push_back(L"아");
    attackword.push_back(L"이");

    for (int i = 0; i < 1000; i++) {
        serverword.push_back(L"가나다");
    }

    for (int i = 0; i < 1000; i++) {
        attackword.push_back(L"김범수");
    }
}

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

void Game::update(Time elapsed, Text t, size_t level) {

    for (tlistIter = tlist.begin(); tlistIter != tlist.end(); ++tlistIter) {

        if (t.getString() ==
            (*tlistIter).getString()) { // 떨어지고 있는 단어와 타이핑 단어 비교
            tlist.erase(tlistIter++);
            player->setPlayerHP(HP_PLUS_VALUE); // 동일시 HP +3
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

        if (t.getString() ==
            (*tlistIter).getString()) { // 동일시 공격할 단어 삭제 후 서버 전송

            alist.erase(tlistIter++);

            /* 서버로 attack word를 전송해야함*/
        }
    }
}

/*------------------------Typing 관련 함수--------------------------*/

void Game::setTyping(wstring t) { typing.setString(t); }
Text Game::getTyping() { return typing; }

/*------------------------디자인 함수-----------------------------*/

void Game::setWordColor(Text &text, int randomX) { // 단어 랜덤 색으로

    if (randomX % 2 == 0)
        text.setFillColor(sf::Color::Yellow); // White

    else if (randomX % 3 == 0)
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
