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
bool wait=true;

void *Read(void *none) { // 서버로부터 단어 받아오기
    while (running) {
        memset(readbuffer, 0, 128);
        recv(serfd, readbuffer, 128, 0);
        cout<<readbuffer<<endl<<strlen(readbuffer)<<endl;
        int len=strlen(readbuffer);
        for(int j=0;j<len;j++)
        {
            printf("%d ",readbuffer[j]);
        }
        if(len==0)
            continue;
        wstring str;
        int j=1;
        while(j<len)
        {
            int uni=0;
            char ch=readbuffer[j++];
            if(ch==101)
                ch=0;
            uni+=ch*1000000;
            ch=readbuffer[j++];
            if(ch==101)
                ch=0;
            uni+=ch*10000;
            ch=readbuffer[j++];
            if(ch==101)
                ch=0;
            uni+=ch*100;
            ch=readbuffer[j++];
            if(ch==101)
                ch=0;
            uni+=ch;
            
            str+=uni;
        }
        wcout<<str<<endl;
        int tag = readbuffer[0];

        switch (tag) {
        case 1:
            // 방어할 단어 tag : R
            wcout<<str<<endl;
            game.setServerWord(str);
            break;
        case 2:
            // 공격할 단어 tag : A
            wcout<<str<<endl;
            game.setAttackWord(str);
            break;
       case 7:
            cout<<"start"<<endl;
            wait=false;
            break;
        }
    }
}

void Write(wstring str) { // 공격할 단어 서버로 전송
    int sendlen = send(serfd, str.data(), 128, 0);
    if (sendlen < 0) {
        cout << "서버의 연결이 끊어졌습니다." << endl;
        return;
    }
}
