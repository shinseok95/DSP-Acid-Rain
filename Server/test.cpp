#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

int main() {
    printf("%d %d",L'공'%256,L'비'%256);
    return 0;
}
