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

struct message {
    long type;
    char ch[100];
};

int main() {
    printf("%d\n%d\n%d\n", sizeof("각"), sizeof("가나"), sizeof("as"));
    return 0;
}
