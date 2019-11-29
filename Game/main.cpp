#include "Client.cpp"
#include <SFML/Audio.hpp>

int main() {

    char ip[20];
    cout << "서버의 IP주소를 입력해주세요" << endl;
    cin >> ip;
    serfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr(ip);
    seraddr.sin_port = htons(7777);
    if (connect(serfd, (sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    running = true;
    pthread_create(&readthread, NULL, Read, NULL);
    pthread_detach(readthread);

    cout << "게임이 시작하기를 기다리고 있습니다..." << endl;
    Write(7, L"시작");

    while (wait) {
    } // 게임 시작 전 무한루프

    Clock clock;
    Clock sectimer;
    RenderWindow window(VideoMode(1385, 720), L"Acid Rain Game");
    list<Text>::iterator iter;

    sf::Music music;
    if (!music.openFromFile("BGM.wav"))
        return -1; // error

    music.setLoop(true);
    music.play();

    /* BG */
    Texture texture;
    Sprite sprite;

    /* Line */
    Vertex line1[2];
    Vertex line2[2];
    Vertex line3[2];
    Vertex line4[2];
    line4[0].position = {1280, 0};
    line4[1].position = {1280, 720};

    /*HP Text*/
    Vertex HPtop[2];
    Vertex HPmiddle[2];

    /* rectangle */
    ConvexShape right;
    ConvexShape below;

    /*HP Bar*/
    ConvexShape HPshape;
    ConvexShape HPbar;

    ConvexShape ALLHP[10];
    ConvexShape fullHP[10];

    int p = 22;

    for (int i = 0; i < 10; i++) {
        fullHP[i].setFillColor(sf::Color(50, 50, 50));
        ALLHP[i].setFillColor(sf::Color::Red);
        fullHP[i].setPointCount(4);
        ALLHP[i].setPointCount(4);
        if (i % 2 == 0) {
            fullHP[i].setPoint(0, sf::Vector2f(1295, p));
            fullHP[i].setPoint(1, sf::Vector2f(1325, p));
            fullHP[i].setPoint(2, sf::Vector2f(1325, p + 100));
            fullHP[i].setPoint(3, sf::Vector2f(1295, p + 100));
            ALLHP[i].setPoint(0, sf::Vector2f(1295, p));
            ALLHP[i].setPoint(1, sf::Vector2f(1325, p));
            ALLHP[i].setPoint(2, sf::Vector2f(1325, p + 100));
            ALLHP[i].setPoint(3, sf::Vector2f(1295, p + 100));
        } else {
            fullHP[i].setPoint(0, sf::Vector2f(1340, p));
            fullHP[i].setPoint(1, sf::Vector2f(1370, p));
            fullHP[i].setPoint(2, sf::Vector2f(1370, p + 100));
            fullHP[i].setPoint(3, sf::Vector2f(1340, p + 100));
            ALLHP[i].setPoint(0, sf::Vector2f(1340, p));
            ALLHP[i].setPoint(1, sf::Vector2f(1370, p));
            ALLHP[i].setPoint(2, sf::Vector2f(1370, p + 100));
            ALLHP[i].setPoint(3, sf::Vector2f(1340, p + 100));
            p += 144;
        }
    }

    /*HP Text*/
    Text HPtitle;
    Text HPtopvalue;
    Text HPmidvalue;

    /*Typing & Attack Text*/

    Text typing;
    Text attack;

    game.setShape(texture, sprite, line1, line2, line3, HPtop, HPmiddle, right,
                  below, HPshape, HPbar, HPtitle, HPtopvalue, HPmidvalue,
                  typing, attack);

    // for (int i = 0; i < 10; i++)
    //     game.severAtk();

    long totaltime = 0;

    while (window.isOpen()) { // 창 열림
        Event event;

        while (window.pollEvent(event)) { //이벤트 처리
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) { // Typing 처리
                Uint32 uni = event.text.unicode;
                typeWord(event, uni, game);
            }
            //////////////////////////1초마다 단어
            ///추가///////////////////////////////
        }

        //////////////////////////화면 그리기//////////////////////////////

        window.clear();
        window.draw(sprite); // 배경화면 띄우기

        window.draw(right); // 모형 그리기
        window.draw(below);
        window.draw(HPshape); // HP 모형 그리기

        window.draw(line1, 2, sf::Lines); // 라인 그리기
        window.draw(line2, 2, sf::Lines);
        window.draw(line3, 2, sf::Lines);
        window.draw(line4, 2, sf::Lines);
        window.draw(HPtop, 2, sf::Lines); // HP 라인 그리기
        window.draw(HPmiddle, 2, sf::Lines);

        window.draw(HPtitle); // HP text 그리기
        window.draw(HPtopvalue);
        window.draw(HPmidvalue);

        window.draw(typing);
        window.draw(attack);

        /* 입력받은 단어 처리 */
        std::wstring text = game.TEXTBOX;
        text += tempcombi();
        game.setTyping(text);
        window.draw(game.getTyping());

        //////////////////////////화면 갱신///////////////////////////////
        Time elapsed = clock.restart();

        totaltime += elapsed.asMilliseconds();
        if (totaltime >= 1000) {
            Write(3, L"");
            totaltime = 0;
        }

        game.update(elapsed, game);

        /*-------- sendAtkWord(queue)에 단어가 존재하는 경우 -----------*/

        if (!game.sendAtkWord.empty()) {
            Write(2, game.sendAtkWord.front()); // 서버로 전송
            game.sendAtkWord.pop();
        }

        /*HP 갱신*/
        HPbar.setPoint(
            0, sf::Vector2f(1150, 720 - game.getPlayer().getPlayerHP() * 3));
        HPbar.setPoint(
            1, sf::Vector2f(1250, 720 - game.getPlayer().getPlayerHP() * 3));

        for (int i = 0; i < 10; i++) {
            if (me == i) {
                ALLHP[i].setFillColor(sf::Color::Yellow);
                otherHP[i] = game.getPlayer().getPlayerHP();
            }
            ALLHP[i].setPoint(
                0, sf::Vector2f(ALLHP[i].getPoint(3).x,
                                ALLHP[i].getPoint(3).y - otherHP[i]));
            ALLHP[i].setPoint(
                1, sf::Vector2f(ALLHP[i].getPoint(2).x,
                                ALLHP[i].getPoint(2).y - otherHP[i]));
            window.draw(fullHP[i]);
            window.draw(ALLHP[i]);
        }

        window.draw(HPbar);

        /*----------------------게임 종료 요건----------------------*/

        if (game.getPlayer().getPlayerHP() <=
            0) { // HP가 0 이하가 될 경우 게임종료
            game.setResultImage(texture, sprite,
                                false); // 패배 이미지 가져오기
            Write(6, L"");
            window.setSize(sf::Vector2u(1280, 720));
            pthread_cancel(readthread);
            while (sectimer.getElapsedTime().asMilliseconds() < 5000) {
                window.clear();
                window.draw(sprite);
                window.display();
            }

            break;
        }

        if (game.getOver()) { // 체력이 남아있는데 게임이 끝난경우(승리))

            game.setResultImage(texture, sprite,
                                true); // 승리 이미지 가져오기
            while (sectimer.getElapsedTime().asMilliseconds() < 5000) {
                window.clear();
                window.draw(sprite);
                window.display();
            }

            break;
        }

        if (!game.tlist.empty()) {
            for (iter = game.tlist.begin(); iter != game.tlist.end(); iter++) {

                window.draw(*iter);
            }
        }

        int ypos = 50;
        if (!game.alist.empty()) {
            for (iter = game.alist.begin(); iter != game.alist.end(); iter++) {
                iter->setPosition(1105, ypos);
                window.draw(*iter);
                ypos += 55;
            }
        }

        window.display();

        sectimer.restart(); // 게임 종료 time을 위해 필요
        //////////////////////////////////////////////////////////////////
    } //창 닫힘

    return 0;
}
