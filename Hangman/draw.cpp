#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <windows.h>
using namespace std;
bool cmp(pair<int,string> a,pair<int,string> b)
{
    return (a.first > b.first);
}
string getHangPicture(int badGuessCount)
{
    string picture[] = {"",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

};
    return picture[badGuessCount];
}
const vector<string> HANGED =
{
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
};
void clearScreen()
{
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif // _WIN32
}
void renderGame(string guessedWord, int badGuessCount, string badGuess = "")
{
    clearScreen();
    cout << "Current guess = " << guessedWord << endl;
    cout << "You have made bad " << badGuessCount << " guess(es)"
         << (badGuess.empty() ? "" : ": ") << badGuess << endl
         << getHangPicture(badGuessCount) << endl;
}
void printGameOverInfo(string guessedWord, string word, int badGuessCount,const int speed, int loop, float &time)
{
    renderGame(guessedWord, badGuessCount);

    if (guessedWord != word) {

        int n = 0;
        // số vòng lặp
        while (loop--)
        {
            clearScreen();
            if (time == 20) cout <<"TIME OUT !!! You lose"<<endl;
            cout << "Game Over!!! You are hanged" << endl
                 << "The correct word is " << word << endl;
            cout << HANGED[n] << endl ;
            if (time == 20) cout <<"TIME OUT !!! You lose";
            n = (n+1) % HANGED.size();
            std::this_thread::sleep_for (std::chrono::milliseconds(speed));

        }
    } else {
        cout << "Congrats!!! You are free" ;
        Sleep(speed*loop*2);
    }
    clearScreen();
}
void HighScore(vector<int> &letters, int &badGuessCount, const int & MAX_BAD_GUESS, string &name,float &time,const int &sleepTime)
{

    int score = (badGuessCount == MAX_BAD_GUESS) ? 0 : (letters[26]*1000) - (badGuessCount*100) + (20 - time);
    if (time >= 20 )
    {
        time = 20;
        score = 0;
        cout<<"You lose because of TIMEOUT"<<endl;
        Sleep(sleepTime);
        clearScreen();
    }
    cout << "Hey," << name <<".You finish the game with:"<<time<<" seconds." << endl << "This is your score: " << score << endl << "And here is the leaderboard: " << endl;

    ifstream file("HighScore.txt");
    vector <pair<int,string>> HS;
    while(!file.eof())
    {
        int n;
        file>>n; // so diem
        string s;
        getline(file,s);// ten
        HS.push_back(make_pair(n,s));
    }
    HS.pop_back();
    HS.push_back(make_pair(score,name));// cho toan bo dieme vao vector sort
    ofstream ouf("HighScore.txt");
    sort(HS.begin(),HS.end(),cmp);// sort
    int ldb = (HS.size()>10) ? 10 : HS.size();
    for(int i=0;i<ldb;i++)
    {
        cout<<i+1<<setw(30)<<HS[i].second<<setw(30)<<HS[i].first<<endl;
        ouf<<HS[i].first<<HS[i].second<<'\n';// viet de len file
    }
    Sleep(sleepTime);
    clearScreen();
}
string getName()
{
    string name;
    cout<<"Enter your name: ";
    //cin.ignore(1);
    getline(cin,name);
    if(name[0]<='9'&&name[1]>='0') name.erase(0,1);
    return name;
}
bool AskForPlayAgain()
{
    cout << "Do you want more (Y/N) ?";
    string answer;
    //cin.ignore(1);
    getline(cin, answer);
    if (answer == "Y" || answer == "y") return true;
    return false;
}
