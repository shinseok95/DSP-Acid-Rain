#include "client.hpp"
#include <cstdlib>
#include <string>

using namespace std;

sockaddr_in serveraddr;
int serverfd;
Client *clients[10];
int clientnum = 0;
bool listening = false;
bool running = false;

void ListenClient();
void Disconnect();
void read();
void DataProcess();

int main() {
    if (serverfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) < 0) {
        cout << "소켓을 열 수 없습니다." << endl;
        return -1;
    }

    int on = 1;
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const char *)on,
                   sizeof(on)) < 0) {
        cout << "아무튼 에러" << endl;
        return -1;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(7777);

    if (bind(serverfd, (sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        cout << "바인딩 에러" << endl;
        return -1;
    }

    memset(clients, NULL, sizeof(clients));
    cout << "서버가 실행되었습니다. 클라이언트를 기다리는 중입니다." << endl;
    cout << "IP주소:" << inet_ntoa(serveraddr.sin_addr) << endl;
    cout << "포트:" << ntohs(serveraddr.sin_port) << endl;
    if (listen(serverfd, 10) < 0) {
        cout << "서버 열기 실패" << endl;
        return -1;
    }

    thread listenthread(ListenClient);
    listening = true;
    listenthread.detach();
    int listenexit;
    cin >> listenexit;
    listening = false;
    listenthread.~thread();
    thread readthread(read);
    readthread.detach();

    close(serverfd);
    return 0;
}

void ListenClient() {
    while (listening) {
        sockaddr_in clientaddr;
        int clientfd;
        if (clientfd = accept(serverfd, (sockaddr *)&clientaddr,
                              (socklen_t *)sizeof(clientaddr)) < 0) {
            cout << "클라이언트 연결 오류" << endl;
            exit(-1);
        }

        int i = 0;
        for (i = 0; i < 10; i++) {
            if (clients[i] == NULL)
                continue;
            if (!clients[i]->clienton) {
                delete clients[i];
                clients[i] = NULL;
                continue;
            }
        }
        for (i = 0; i < 10; i++) {
            if (clients[i] == NULL)
                break;
        }
        if (i >= 10) {
            cout << "접속 인원 초과" << endl;
            continue;
        }

        clients[i] = new Client(clientaddr, clientfd);

        cout << "클라이언트 접속" << endl;
        cout << "IP주소:" << inet_ntoa(clientaddr.sin_addr) << endl;
        cout << "포트:" << ntohs(clientaddr.sin_port) << endl;
    }
}

void Disconnect() {
    for (int i = 0; i < 10; i++) {
        if (clients[i] == NULL)
            continue;
        clients[i]->Disconnect();
        delete clients[i];
        clients[i] = NULL;
    }
    close(serverfd);
}

void read() {
    while (running) {
        for (int i = 0; i < 10; i++) {
            if (clients[i] == NULL)
                continue;
            if (!clients[i]->clienton) {
                delete clients[i];
                clients[i] = NULL;
            }
            if (clients[i]->dataqueue.empty())
                continue;
            clients[i]->dataqueue.front();
        }
    }
}
