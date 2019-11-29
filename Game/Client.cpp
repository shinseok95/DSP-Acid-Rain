#include "Game.cpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Game game;

pthread_t readthread;

sockaddr_in seraddr;
int serfd;
char readbuffer[128];
bool running = false;
bool wait = true;

int otherHP[10] = {
    0,
};
int me;

void *Read(void *none) { // 서버로부터 단어 받아오기
    while (running) {
        memset(readbuffer, 0, 128);
        int readlen = recv(serfd, readbuffer, 128, 0);
        if (readlen <= 0) {
            cout << "서버의 연결이 끊어졌습니다." << endl;
            exit(-1);
        }

        int tag = readbuffer[0];
        if (tag == 3) {
            for (int i = 0; i < 10; i++) {
                if (i == me) {
                    otherHP[i] = game.getPlayer().getPlayerHP();
                } else {
                    otherHP[i] = readbuffer[i + 1];
                    if (otherHP[i] == 101)
                        otherHP[i] = 0;
                }
            }
            continue;
        }

        if (tag == 7) {
            me = readbuffer[1];
            cout << endl << "게임을 시작합니다!" << endl;
            wait = false;
            continue;
        }

        int len = strlen(readbuffer);
        if (len == 0)
            continue;
        wstring str;
        int j = 1;
        while (j < len) {
            int uni = 0;
            char ch = readbuffer[j++];
            if (ch == 101)
                ch = 0;
            uni += ch * 10000;
            ch = readbuffer[j++];
            if (ch == 101)
                ch = 0;
            uni += ch * 100;
            ch = readbuffer[j++];
            if (ch == 101)
                ch = 0;
            uni += ch;

            str += uni;
        }

        switch (tag) {
        case 1:
            // 방어할 단어 tag : R
            game.setServerWord(str);
            break;
        case 2:
            // 공격할 단어 tag : A
            game.setAttackWord(str);
            break;
        case 6:
            // 승리 신호
            game.setOver();
            pthread_exit(NULL);
            break;
        }
    }
}

void Write(int tag, wstring str) { // 공격할 단어 서버로 전송
    char writebuffer[128];
    memset(writebuffer, 0, 128);
    writebuffer[0] = tag;
    if (tag == 3) {
        writebuffer[1] = game.getPlayer().getPlayerHP();
        if (writebuffer[1] == 0)
            writebuffer[1] = 101;
    } else {
        int len = str.size();
        for (int i = 0; i < len; i++) {
            writebuffer[i * 3 + 1] = (str[i] / 10000) % 100;
            writebuffer[i * 3 + 2] = (str[i] / 100) % 100;
            writebuffer[i * 3 + 3] = str[i] % 100;
            if (writebuffer[i * 3 + 1] == 0)
                writebuffer[i * 3 + 1] = 101;
            if (writebuffer[i * 3 + 2] == 0)
                writebuffer[i * 3 + 2] = 101;
            if (writebuffer[i * 3 + 3] == 0)
                writebuffer[i * 3 + 3] = 101;
        }
    }

    int sendlen = send(serfd, writebuffer, 128, 0);
    if (sendlen <= 0) {
        cout << "서버의 연결이 끊어졌습니다." << endl;
        exit(-1);
    }
}
