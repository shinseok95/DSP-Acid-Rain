#include "header.h"

using namespace std;
wchar_t readbuffer[32];
wchar_t writebuffer[32];

int main()
{
    int sockfd;
size_t readSize = 0;
size_t totalSize = 0;
sockaddr_in servAddr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
servAddr.sin_family = AF_INET;
servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servAddr.sin_port = htons(7777);
if(connect(sockfd, (sockaddr *)&servAddr, sizeof(servAddr))<0)
{
            fprintf(stderr, "%s\n", strerror(errno));
            return -1;
}
while (1) {
    memset(writebuffer,0, 64);
    wcin>>writebuffer;
    wcout<<writebuffer;
    int sendlen = (send(sockfd,writebuffer,sizeof(writebuffer), 0));
    cout<<sendlen;
}

    return 0;
}