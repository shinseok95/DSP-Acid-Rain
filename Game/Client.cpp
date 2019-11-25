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
wchar_t readbuffer[64];
bool running = false;

void *Read(void *none) { // 서버로부터 단어 받아오기
    while (running) {
        memset(readbuffer, 0, sizeof(readbuffer));
        recv(serfd, readbuffer, sizeof(readbuffer), 0);
        wstring str = readbuffer;
        wchar_t tag = str[0];
        str = readbuffer + 1;
        switch (tag) {
        case 'R':
            // 방어할 단어 tag : R
            game.setServerWord(str);
            break;
        case 'A':
            // 공격할 단어 tag : A
            game.setAttackWord(str);
            break;
        }
    }
}

void Write(wstring str) { // 공격할 단어 서버로 전송
    int sendlen = send(serfd, str.data(), str.size(), 0);
    if (sendlen < 0) {
        cout << "서버의 연결이 끊어졌습니다." << endl;
        return;
    }
}
