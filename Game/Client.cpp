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
bool wait=true;

void *Read(void *none) { // 서버로부터 단어 받아오기
    while (running) {
        memset(readbuffer, 0, sizeof(readbuffer));
        recv(serfd, readbuffer, sizeof(readbuffer), 0);
            wcout<<readbuffer<<endl;
        wstring str = readbuffer;
        wchar_t tag = str[0];
        str = readbuffer + 1;
        switch (tag) {
        case L'R':
            // 방어할 단어 tag : R
            wcout<<str<<endl;
            game.setServerWord(str);
            break;
        case L'A':
            // 공격할 단어 tag : A
            wcout<<str<<endl;
            game.setAttackWord(str);
            break;
       case L'S':
            cout<<"start"<<endl;
            wait=false;
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
