#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>
#include <vector>

bool contains( std::string word, char guess);
std::string normalize(const std::string& s);
void Instruction(const std::string& InsFile,const int &sleepTime);
std::string getFile();
std::string chooseWord(const std::string& fileName);
std::string getWord(std::string &WordAndHint);
std::string getHint(std::string &WordAndHint);
std::string getGWord(const std::string &word );
std::string readAGuess(const std::string &word , std::vector <int> &letters);
void update( std::vector<int>& letters, std::string& guessedWord, const std::string& word, std::string guess,int &badGuessCount,std::string &badGuess);

#endif // __UTILITY_H__
