#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <cstring>
#include <string>
#include <cwchar>

using namespace std;

int main() {
    setlocale(LC_ALL , "ko_KR.UTF-8");
    wprintf(L"%ls %d %d %d\n",L"가밀걀", L'가',L'밀',L'걀');
    wcout<<L"가밀걀"<<L'가'<<L'밀'<<L'걀'<<endl;
    string str="가밀걀";
    wstring wstr;
    wstring ws=L"가밀걀";
    int len=str.length();
    int i=0;
    while(i<len)
    {
        int uni=0;
        uni+=(str[i]+32)*4096;
        i++;
        uni+=(str[i]+128)*64;
        i++;
        uni+=(str[i]+128);
        i++;
       wstr+=uni;
    }
    wprintf(L"%ls %d %d %d\n",ws, ws[0],ws[1],ws[2]);
    wcout<<ws<<ws[0]<<ws[1]<<ws[2]<<endl;
    wprintf(L"%ls %d %d %d\n",wstr, wstr[0],wstr[1],wstr[2]);
    wcout<<ws<<ws[0]<<ws[1]<<ws[2]<<endl;
    return 0;
}
