#include "client.hpp"
#include <cstdlib>
#include <string>
#include <sys/wait.h>

using namespace std;

sockaddr_in serveraddr;
int serverfd;
bool listening = false;
bool running = false;

Client *clients[10];
thread *clientread[10];
int clientnum = 0;

void ListenClient();
void Disconnect();
void readdata();
void DataProcess(string str);

int main() {
    pid_t pid = 0;
    int status = 0;
    cout << "주제를 설정해주세요. (모든 주제는 ALL)" << endl;
    char theme[10];
    cin >> theme;
    char *const exeargv[] = {"python3", "worddbcreate.py", theme, NULL};
    pid = fork();
    switch (pid) {
    case -1:
        perror("포크 에러");
        exit(-1);
    case 0:
        execvp("python3", exeargv);
        return 0;
    }

    if (pid > 0) {
        wait(&status);
    }

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
        cout << "소켓을 열 수 없습니다." << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    int on = 1;
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&on,
                   sizeof(on)) < 0) {
        cout << "소켓 설정 에러" << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(7777);
    if (bind(serverfd, (sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        cout << "바인딩 에러" << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < 10; i++)
        clients[i] = nullptr;
    cout << "서버가 실행되었습니다. 클라이언트를 기다리는 중입니다." << endl;
    cout << "IP주소:" << inet_ntoa(serveraddr.sin_addr) << endl;
    cout << "포트:" << ntohs(serveraddr.sin_port) << endl;
    if (listen(serverfd, 10) < 0) {
        cout << "서버 열기 실패" << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    listening = true;
    thread listenthread(ListenClient);
    listenthread.detach();
    string listenexit;
    cout << "엔터를 눌러서 게임을 시작해주세요" << endl;
    cin >> listenexit;
    listening = false;
    listenthread.~thread();
    //  thread readthread(readdata);
    // readthread.join();
    Disconnect();
    close(serverfd);
    FILE *clear;
    clear = fopen(".db", "wt");
    fclose(clear);
    return 0;
}

void ListenClient() {
    while (listening) {
        sockaddr_in clientaddr;
        int clientfd = accept(serverfd, (sockaddr *)&clientaddr,
                              (socklen_t *)sizeof(clientaddr));
        if (clientfd < 0) {
            cout << "클라이언트 연결 오류" << endl;
            fprintf(stderr, "%s\n", strerror(errno));
            exit(-1);
        }

        int i = 0;
        for (i = 0; i < 10; i++) {
            if (clients[i] == nullptr)
                continue;
            if (!clients[i]->clienton) {
                clients[i]->Disconnect();
                // clientread[i]->~thread();
                // delete clientread[i];
                delete clients[i];
                clients[i] = nullptr;
                continue;
            }
        }
        for (i = 0; i < 10; i++) {
            if (clients[i] == nullptr)
                break;
        }
        if (i >= 10) {
            cout << "접속 인원 초과" << endl;
            close(clientfd);
            continue;
        }

        clients[i] = new Client(clientaddr, clientfd);
        // clientread[i] = new thread(clients[i]->read);
        // clientread[i]->detach();

        cout << "클라이언트 접속" << endl;
        cout << "IP주소:" << inet_ntoa(clientaddr.sin_addr) << endl;
        cout << "포트:" << ntohs(clientaddr.sin_port) << endl;
    }
}

void Disconnect() {
    for (int i = 0; i < 10; i++) {
        if (clients[i] == nullptr)
            continue;
        clients[i]->Disconnect();
        // clientread[i]->~thread();
        // delete clientread[i];
        delete clients[i];
        clients[i] = nullptr;
    }
    close(serverfd);
}

void readdata() {
    while (running) {
        for (int i = 0; i < 10; i++) {
            if (clients[i] == nullptr)
                continue;
            if (!clients[i]->clienton) {
                clients[i]->Disconnect();
                // clientread[i]->~thread();
                // delete clientread[i];
                delete clients[i];
                clients[i] = nullptr;
            }
            if (clients[i]->dataqueue.empty())
                continue;
            DataProcess(clients[i]->dataqueue.front());
            clients[i]->dataqueue.pop();
        }
    }
}

void DataProcess(string str) {}
