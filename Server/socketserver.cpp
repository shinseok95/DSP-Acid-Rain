#include "header.h"

using namespace std;

sockaddr_in serveraddr;
int serverfd;
bool listening = false;
bool running = false;

bool clienton[10];
int clientfd[10];
sockaddr_in clientaddr[10];
char readbuffer[10][128];
queue<pair<int,wstring>> dataqueue[10];
pthread_t readthread[10];
pthread_mutex_t writemutex[10];

vector<wstring> words;
int wordlen;
random_device rd;
mt19937 mt;

void *ListenClient(void *none);
void ClientDisconnect(int i);
void Disconnect(void* none);
void Write(int tag, wstring str, int i);
void* Read(void* index);
void* DataProcess(void* none);
bool awake = false;

int main() {
    pid_t pid = 0;
    int status = 0;
    int msqid = msgget(2017610015, IPC_CREAT | 0666);
    cout << "주제를 설정해주세요. (모든 주제는 ALL)" << endl;
    char theme[10];
    cin >> theme;
    char *const exeargv[] = {"python", "worddbcreate.py", theme, NULL};
    pid = fork();
    switch (pid) {
    case -1:
        perror("포크 에러");
        exit(-1);
    case 0:
        execvp("python3", exeargv);
        return 0;
    }

    message msg;
    while (true) {
        memset(&msg, 0, sizeof(msg));
        msgrcv(msqid, &msg, sizeof(msg) - sizeof(long), 1, 0);
        string temp(msg.str);
        wstring word;
        word.assign(temp.begin(),temp.end());
        if (word == L"END")
            break;
        else
            words.push_back(word);
        wcout << words.back() << endl;
    }
    msgctl(msqid, IPC_RMID, NULL);
    if (words.empty()) {
        cout << "주제코드가 잘못 되었거나 단어를 불러올 수 없습니다." << endl;
        return -1;
    }
    cout << "불러오기 완료!" << endl;
    wordlen = words.size();
    mt.seed(rd());
    
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
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(7777);
    if (bind(serverfd, (sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        cout << "바인딩 에러" << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < 10; i++)
        clienton[i] = false;
    cout << "서버가 실행되었습니다. 클라이언트를 기다리는 중입니다." << endl;
    cout << "IP주소:" << inet_ntoa(serveraddr.sin_addr) << endl;
    cout << "포트:" << ntohs(serveraddr.sin_port) << endl;
    if (listen(serverfd, 10) < 0) {
        cout << "서버 열기 실패" << endl;
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

    listening = true;
    pthread_t listenthread;
    pthread_create(&listenthread, NULL, ListenClient, NULL);
    pthread_detach(listenthread);
    string listenexit;
    cout << "아무 문자열이나 입력 후 엔터를 눌러서 게임을 시작해주세요" << endl;
    cin >> listenexit;
    for(int j=0;j<10;j++)
    {
            int idx = mt() % wordlen;
            for(int i=0;i<10;i++)
            {
                if(!clienton[i])
                    continue;
                Write(1, words[idx],i);
            }
    }
    for(int j=0;j<10;j++)
    {
            int idx = mt() % wordlen;
            for(int i=0;i<10;i++)
            {
                if(!clienton[i])
                    continue;
                Write(2, words[idx],i);
            }
    }

    for(int i=0;i<10;i++)
    {
        if(!clienton[i])
            continue;
        Write(7,L"시작",i);
    }
    listening = false;
    pthread_cancel(listenthread);
    pthread_t mainthread;
    pthread_create(&mainthread,NULL,DataProcess,NULL);
    int* state;
    running=true;
    pthread_join(mainthread, (void**)&state);
    Disconnect(NULL);
    return 0;
}

void *ListenClient(void *none) {
    while (listening) {
        sockaddr_in addr;
        socklen_t addsize = sizeof(addr);
        int fd = accept(serverfd, (sockaddr *)&addr, &addsize);
        if (fd < 0) {
            cout << "클라이언트 연결 오류" << endl;
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }

        int i = 0;
        for (i = 0; i < 10; i++) {
            if (!clienton[i])
                break;
        }

        if (i >= 10) {
            cout << "접속 인원 초과" << endl;
            close(fd);
            continue;
        }

        clienton[i] = true;
        clientfd[i] = fd;
        clientaddr[i] = addr;
        pthread_create(&readthread[i],NULL,Read,&i);
        pthread_detach(readthread[i]);
        pthread_mutex_init(&writemutex[i],NULL);

        cout << "클라이언트 접속" << endl;
        cout << "IP주소:" << inet_ntoa(addr.sin_addr) << endl;
        cout << "포트:" << ntohs(addr.sin_port) << endl;
    }
}

void ClientDisconnect(int i) {
    pthread_cancel(readthread[i]);
    pthread_mutex_destroy(&writemutex[i]);
    clienton[i] = false;
    close(clientfd[i]);
}

void Disconnect(void *none) {
    for (int i = 0; i < 10; i++) {
        if (!clienton[i])
            continue;
        ClientDisconnect(i);
    }
    close(serverfd);
}

void Write(int tag, wstring str, int i)
{
        pthread_mutex_lock(&writemutex[i]);
        wcout<<str<<endl;
        char writebuffer[128];
        memset(writebuffer,0,128);
        writebuffer[0]=tag;
        int len=str.size();
        cout<<len<<endl;
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
        len=strlen(writebuffer);
        cout<<len<<endl;
        for(int j=0;j<len;j++)
        {
            printf("%d ",writebuffer[j]);
        }
        printf("\n");
        int sendlen = send(clientfd[i], writebuffer, 128, MSG_NOSIGNAL);
        if (sendlen < 0) {
            cout << "클라이언트 " << inet_ntoa(clientaddr[i].sin_addr) << "의 연결이 끊어졌습니다." << endl;
            pthread_mutex_unlock(&writemutex[i]);
            ClientDisconnect(i);
            return;
        }
    pthread_mutex_unlock(&writemutex[i]);
}

void* Read(void* index)
{
    int i=*((int*)index);
    while(clienton[i])
    {
        int readlen = 0;
        memset(readbuffer[i], 0,128);
        readlen = recv(clientfd[i], readbuffer[i], 128, MSG_NOSIGNAL);
        if (readlen < 0) {
            cout << "클라이언트 " << inet_ntoa(clientaddr[i].sin_addr) << "의 연결이 끊어졌습니다." << endl;
            ClientDisconnect(i);
            pthread_exit(NULL);
        }
        cout<<readbuffer[i]<<endl<<strlen(readbuffer[i])<<endl;
        int len=strlen(readbuffer[i]);
        for(int j=0;j<len;j++)
        {
            printf("%d ",readbuffer[i][j]);
        }
        if(len==0)
            continue;
        wstring str;
        int j=1;
        while(j<len)
        {
            int uni=0;
            char ch=readbuffer[i][j++];
            if(ch==101)
                ch=0;
            uni+=ch*1000000;
            ch=readbuffer[i][j++];
            if(ch==101)
                ch=0;
            uni+=ch*10000;
            ch=readbuffer[i][j++];
            if(ch==101)
                ch=0;
            uni+=ch*100;
            ch=readbuffer[i][j++];
            if(ch==101)
                ch=0;
            uni+=ch;
            
            str+=uni;
        }
        wcout<<str<<endl;
        int tag = readbuffer[i][0];
        pair<int,wstring> data(tag,str);
        dataqueue[i].push(data);
    }
}

void* DataProcess(void *none) {
    int timestep=5000;
    long totaltime=0;
    timeval pre, now;
    gettimeofday(&pre,NULL);
    while (running) {
        for (int i = 0; i < 10; i++) {
            if (!clienton[i])
                continue;
            if (dataqueue[i].empty())
                continue;
            pair<int,wstring> data = dataqueue[i].front();
            dataqueue[i].pop();
            switch (data.first) {
            case L'공':
                int idx = mt() % wordlen;
                Write(2,words[idx],i);
                int target;
                do
                {
                    target=mt()%10;
                } while (!clienton[target]);
                Write(1,data.second,target);
            break;
            }
        }
        gettimeofday(&now,NULL);
        long second,usecond;
        second=abs(now.tv_sec-pre.tv_sec);
        usecond=now.tv_usec-pre.tv_usec;
        int mtime=(second*1000+usecond/1000.0)+0.5;
        if(mtime>=timestep)
        {
            int idx = mt() % wordlen;
            wcout<<words[idx]<<endl;
            for(int i=0;i<10;i++)
            {
                if(!clienton[i])
                    continue;
                Write(1,words[idx],i);
            }
            totaltime+=mtime;
            pre=now;
            if(totaltime>=20000)
                timestep-=timestep/10;
        }
    }
}
