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
    wstring str=L"asdf";
    printf("%d\n%d\n",L'a',str[0]);
    wcout<<str[0]<<endl;
    wcout<<L'a'<<endl;
    if(str[0] == L'a')
    {
        wcout<<L"true"<<endl;
    }
    return 0;
}
