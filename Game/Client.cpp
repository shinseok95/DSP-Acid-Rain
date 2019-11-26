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
        int readlen=recv(serfd, readbuffer, 128, 0);
    if (readlen <= 0) {
        cout << "서버의 연결이 끊어졌습니다." << endl;
        return NULL;
    }
        int len=strlen(readbuffer);
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
        int tag = readbuffer[0];

        switch (tag) {
        case 1:
            // 방어할 단어 tag : R
            game.setServerWord(str);
            break;
        case 2:
            // 공격할 단어 tag : A
            game.setAttackWord(str);
            break;
        case 7:
            cout<<"start"<<endl;
            wait=false;
            break;
        }
    }
}

void Write(int tag, wstring str) { // 공격할 단어 서버로 전송
        char writebuffer[128];
        memset(writebuffer,0,128);
        writebuffer[0]=tag;
        int len=str.size();
        for(int i=0;i<len;i++)
        {
            writebuffer[i*4+1]=(str[i]/1000000)%100;
            writebuffer[i*4+2]=(str[i]/10000)%100;
            writebuffer[i*4+3]=(str[i]/100)%100;
            writebuffer[i*4+4]=str[i]%100;
            if(writebuffer[i*4+1]==0)
                writebuffer[i*4+1]=101;
            if(writebuffer[i*4+2]==0)
                writebuffer[i*4+2]=101;
            if(writebuffer[i*4+3]==0)
                writebuffer[i*4+3]=101;
            if(writebuffer[i*4+4]==0)
                writebuffer[i*4+4]=101;
        }
    int sendlen = send(serfd, writebuffer, 128, 0);
    if (sendlen < 0) {
        cout << "서버의 연결이 끊어졌습니다." << endl;
        return;
    }
}
