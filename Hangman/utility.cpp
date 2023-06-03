#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;
bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}
string normalize(const string& s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}
void Instruction(const string& InsFile,const int &sleepTime)
{
    ifstream file(InsFile);
    while (!file.eof())
    {
        string line;
        getline(file,line);
        cout<<line<<endl;
    }
    Sleep(sleepTime);
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif // _WIN32
}
string getFile()
{
    string in,out;
    ifstream file("ChooseMode.txt");
    while(!file.eof())
    {
        string line;
        getline(file,line);
        cout<<line<<endl;
    }
    cin>>in;
    out = out + in;
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif // _WIN32
    if (in == "1") in = "EasyTopic.txt";
    else if (in == "2") in= "MediumTopic.txt";
    else if (in == "3") in= "HardTopic.txt";
    ifstream cinf(in);
    while(!cinf.eof())
    {
        string line;
        getline(cinf,line);
        cout<<line<<endl;
    }
    cin>>in;
    out = out + in;
    return out;
}
string chooseWord(const string& fileName)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return "";

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }

    int n = vocabulary.size();
    //cout << "vocabulary size = " << n << endl;
    return n > 0 ? vocabulary[rand() % n] : "";
}
string getWord(string &WordAndHint)
{
    string word ;
    for(int i=0;i<WordAndHint.size();i++)
    {
        if(WordAndHint[i]==',') return normalize(word);
        else word+=WordAndHint[i];
    }
}
string getHint(string &WordAndHint)
{
    string hint;
    int i=0;
    while (WordAndHint[i]!=',') i++;
    for(int j=i+1;j<WordAndHint.size();j++) hint +=WordAndHint[j];
    return hint;
}
string getGWord(const string &word )
{
    string guessedWord;
    for(int i=0;i<word.size();i++)
    {
        if(word[i] == ' ') guessedWord += ' ';
        else guessedWord += '-';
    }
    return guessedWord;
}
string readAGuess(const string &word ,vector <int> &letters)
{
    string guess,ans;
    cout << "Please enter your next guess: ";
    getline(cin,guess);
    normalize(guess);
    if (guess.size() == word.size()){
        if ( guess ==  word ) return word;
        else return "0";
    }
    if(guess.size()>= word.size()) return "0";
    for(int i=0;i<guess.size();i++)
    {
        if(tolower(guess[i])<'a' || tolower(guess[i])>'z') continue;
        else if(!letters[guess[i]-'a'])
        {
            ans+=guess[i];
            letters[guess[i]-'a']++;
        }
        else continue;
    }
    return normalize(ans);
}
void update( vector<int>& letters, string& guessedWord, const string& word, string guess,int &badGuessCount,string &badGuess)
{
    int n = guessedWord.length();
    for(int j =0;j<guess.size();j++) {
        if(guess[j] == ' ') continue;
        if( contains(word, guess[j]) ){
            letters[26]++;
            for (int i = 0; i < n; i++) {
                if (word[i] == guess[j])
                guessedWord[i] = guess[j];
            }
        }
        else {
            badGuessCount++;
            badGuess = badGuess + guess[j] + ' ';
        }
    }
}
