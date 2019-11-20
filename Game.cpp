#include "Player.cpp"
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

class Game {
  private:
    list<Text> temlist;       //떨어지기 전 임시 리스트
    list<wstring> serverword; // 서버에서 받아온 단어 리스트 (string)
    Font font;
    Text text;
    Player *player;

  public:
    Game(wstring, wstring);
    ~Game();
    Text getText() { return text; }
    void severAtk();
    void update(Time elapsed);
    void addWord();
    list<Text> tlist; //떨어지고 있는 리스트
    list<Text>::iterator tlistIter = tlist.begin();
};

void Game::severAtk() { //임시 단어 리스트 관리

    // list<string>::iterator svIter = serverword.begin();
    srand((unsigned int)time(NULL));
    while (temlist.size() != 10) { // 임시 단어들 리스트의 갯수가 10개 미만이면
                                   // x좌표 랜덤 지정해서 넣는다.
        int randomX = rand() % 560;
        // cout << randomX << serverword.front().c_str() << endl;
        Text newtext = Text(serverword.front(), font, 30);
        serverword.pop_front();
        newtext.setPosition((float)randomX, 0.f);
        newtext.setFillColor(sf::Color::Black);
        temlist.push_back(newtext);
    }
}

void Game::update(Time elapsed) {
    for (tlistIter = tlist.begin(); tlistIter != tlist.end(); ++tlistIter) {
        if (tlistIter->getPosition().y > 400) {
            ++tlistIter;
            tlist.pop_front();
            // HP바 줄어들음
        } else {
            tlistIter->move(0, elapsed.asSeconds() * 80);
        }
    }
    // text.setString("hello");
    // text.setFont(font);
    // text.setCharacterSize(30);
    // text.setFillColor(sf::Color::Black);
    // text.move(0,elapsed.asSeconds()*50);
}
void Game::addWord() {
    tlist.push_back(temlist.front());
    temlist.pop_front();
}

Game::Game(wstring name, wstring gradNum) {
    player = new Player(name, gradNum);
    font.loadFromFile("Nanum.ttf");
    // text.setPosition(10,20);
    // list<string> serverword = player->getServerWord();
    for (int i = 0; i < 10000; i++) {
        serverword.push_back(
            L"가나다라마바사아자차카타파하가나다마라바사아자차카타파하");
    }
}

Game::~Game() {}

int main() {

    Clock clock;
    Clock sectimer;
    wstring name, gradeNum;
    Game game(name, gradeNum);
    RenderWindow window(VideoMode(800, 600), L"산성비 테스트");
    list<Text>::iterator iter;

    while (window.isOpen()) { // 창 열림
        Event event;

        while (window.pollEvent(event)) { //이벤트 처리
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //////////////////////////1초마다 단어
        ///추가///////////////////////////////
        if (sectimer.getElapsedTime().asMilliseconds() > 1000) {
            sectimer.restart();
            game.addWord();
        }

        //////////////////////////////////////////////////////////////////

        //////////////////////////화면 갱신///////////////////////////////
        Time elapsed = clock.restart();
        game.severAtk();
        game.update(elapsed);
        //////////////////////////////////////////////////////////////////
        // while (event.type != sf::Event::KeyPressed){;}
        // sf::sleep(sf::seconds(1));
        // tlist.push_back(text);

        //////////////////////////화면 그리기//////////////////////////////
        window.clear(sf::Color::White);
        for (iter = game.tlist.begin(); iter != game.tlist.end(); ++iter) {
            window.draw(*iter);
        }
        window.display();
        //////////////////////////////////////////////////////////////////
    } //창 닫힘

    return 0;
}
