#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>

#include "draw.h"
#include "utility.h"

using namespace std;
int main(int argc, char* argv[])
{
    srand(time(0));
    Instruction("dinosaur.dat",6000); // luật chơi
    while (true) {
        string num = getFile(); // chọn level và topic
        string fileName = num + ".txt"; // chọn file dựa theo topic và level
        string WordAndHint = chooseWord(fileName); // máy chọn bộ từ và hint
        if (WordAndHint.empty()) {
            cout << "No word available in " << fileName << endl;
            return 0;
        } //check xem file có rỗng hay không
        const string word = getWord(WordAndHint);//chọn từ
        const string hint = getHint(WordAndHint);//chọn hint
        string guessedWord = getGWord(word);//tạo xâu với full kí tự - (ẩn đáp án trên screen)
        const int MAX_BAD_GUESS = 7;
        int badGuessCount = 0;
        string badGuess;
        vector <int> letters;
        letters.assign(27,0);
        float start = clock()/CLOCKS_PER_SEC;
        float finish = clock()/CLOCKS_PER_SEC;
        float time ;
        do {
            renderGame(guessedWord, badGuessCount, badGuess) ;
            cout << "You have: " <<20 - time<<" second(s) left"<<endl;
            if( badGuessCount > ( MAX_BAD_GUESS / 3) ) cout<<endl<<"HERE IS THE HINT FOR YOU: "<<hint<<endl; // nếu người chơi gặp khó khăn thì đưa hint
            string guess = readAGuess(word,letters);//nhập kí tự và fix lỗi nhập mọi kí tự và những kí tự đã bị nhập
            if(guess == word) {
                guessedWord == word;
                break;
            }
            else if (guess =="0"){
                badGuessCount = MAX_BAD_GUESS;
                break;
            }
            else update(letters,guessedWord,word,guess,badGuessCount,badGuess);
            finish = clock()/CLOCKS_PER_SEC;
            time = finish - start;
        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word&& (finish-start) <= 20);
        if(time == 20 )
        {
            badGuessCount = MAX_BAD_GUESS;
            time =20;
        }
        printGameOverInfo(guessedWord, word, badGuessCount,20,25,time);

//        cout<<time;
        string name =getName();
        clearScreen();
        HighScore(letters,badGuessCount,MAX_BAD_GUESS,name,time,8000);
        if(!AskForPlayAgain()) break;
        else clearScreen();
    }
    return 0;
}
