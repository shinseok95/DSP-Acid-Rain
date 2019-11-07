#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

using namespace std;

struct Client {
    bool clienton = false;
    char readbuffer[32];
    char writebuffer[32];
    sockaddr_in addr;
    int fd;
    std::queue<string> dataqueue;

    Client(sockaddr_in _addr, int _fd) {
        addr = _addr;
        fd = _fd;
        clienton = true;
    }

    void read() {
        while (clienton) {
            int readlen = 0;
            memset(readbuffer, 0, sizeof(readbuffer));
            readlen = recv(fd, readbuffer, sizeof(readbuffer), 0);
            if (readlen == 0) {
                cout << "클라이언트 " << inet_ntoa(addr.sin_addr)
                     << "의 연결이 끊어졌습니다." << endl;
                clienton = false;
                close(fd);
                break;
            }
            dataqueue.push(readbuffer);
        }
    }

    void write() {
        send(fd, writebuffer, sizeof(writebuffer), 0);
        memset(writebuffer, 0, sizeof(writebuffer));
    }

    void Disconnect() {
        clienton = false;
        close(fd);
    }

  private:
    Client() {}
    void dataprocess() {
        switch (readbuffer[0]) {
        case 100:
            dataqueue.push(string(&readbuffer[1]));
        }
    }
};
