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
wchar_t writebuffer[64];
bool running = false;

void *Read(void *none) {
    while (running) {
        memset(readbuffer, 0, sizeof(readbuffer));
        recv(serfd, readbuffer, sizeof(readbuffer), 0);
        wstring str = readbuffer;
        wchar_t tag = str[0];
        str = readbuffer + 1;
        switch (tag) {
        case 'R':
            // str이 내려오고 있는 단어
            break;
        case 'A':
            // str이 공격할 단어
            break;
        }
    }
}

void Write(wstring str) {}
