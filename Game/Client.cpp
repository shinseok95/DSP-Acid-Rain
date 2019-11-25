#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

sockaddr_in seraddr;
int serfd;
wchar_t readbuffer[64];
wchar_t writebuffer[64];
bool running=false;

void* Read(void* none)
{
    while(running)
    {

    }
}