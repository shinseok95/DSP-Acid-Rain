/*
Word Class
*/

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Word {

  private:
    list<wstring> serverWord; // 서버에서 받아올 단어
    list<wstring> attackWord; // 공격할 단어 1000개

  public:
    Word() {}

    Word &operator=(Word &anotherWord) {

        if (this == &anotherWord)
            return *this;

        list<wstring>::iterator serverIter =
            anotherWord.getServerWord().begin();
        list<wstring>::iterator attackIter =
            anotherWord.getAttackWord().begin();

        serverWord.clear();
        attackWord.clear();

        serverWord.splice(serverIter, anotherWord.getServerWord());
        serverWord.splice(attackIter, anotherWord.getAttackWord());
    }

    void setServerWord(void) {}

    void setAttackWord(void) {

        // ifstream input(".db"); // DB에서 단어 받아오기
        // if (input.fail()) {
        //     cout << ".db open fail" << endl;
        //     exit(-1);
        // }

        // array<string, 1000>
        //     tempWord; // 랜덤하게 받기 위해 임시 저장할 array(1000개)
        // string word;

        // for (int i = 0; i < 1000; i++) {
        //     input >> word;

        //     tempWord[i] = word;
        // }

        // srand((unsigned int)time(0));

        // for (int i = 0; i < 1000; i++)
        //     attackWord.push_back(tempWord[rand() % 1000]); // attackWord에
        //     저장
    }

    list<wstring> getServerWord(void) { return serverWord; }
    list<wstring> getAttackWord(void) { return attackWord; }

    void printAttackWord(void) { // attackWord 출력

        list<wstring>::iterator iter;
        for (iter = attackWord.begin(); iter != attackWord.end(); iter++)
            cout << iter->c_str() << endl;
    }

    void printServerWord(void) { // serverWord 출력

        list<wstring>::iterator iter;
        for (iter = attackWord.begin(); iter != attackWord.end(); iter++)
            cout << iter->c_str() << endl;
    }

    bool deleteServerWord(
        wstring word) { // 입력받은 단어가 존재하는 경우 삭제하고 ture 반환
        list<wstring>::iterator iter;

        for (iter = serverWord.begin(); iter != serverWord.end(); iter++) {
            if (*iter == word) {
                serverWord.erase(iter);
                return true;
            } else
                continue;
        }
        // wstring a = L"가나";
        return false;
    }

    bool deleteAttackWord(
        wstring word) { // 입력받은 단어가 존재하는 경우 삭제하고 ture 반환
        list<wstring>::iterator iter;

        for (iter = attackWord.begin(); iter != attackWord.end(); iter++) {
            if (*iter == word) {
                attackWord.erase(iter);
                return true;
            } else
                continue;
        }

        return false;
    }
};
