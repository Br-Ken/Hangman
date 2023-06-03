#ifndef __DRAW_H__
#define __DRAW_H__

#include <string>

std::string getHangPicture(int badGuessCount);
void clearScreen();
void renderGame(std::string guessedWord, int badGuessCount, std::string badGuess = "");
void printGameOverInfo(std::string guessedWord, std::string word, int badGuessCount,const int speed, int loop, float &time);
void HighScore(std::vector<int> &letters, int &badGuessCount, const int & MAX_BAD_GUESS, std::string &name,float &time,const int &sleepTime);
std::string getName();
bool AskForPlayAgain();

#endif // __DRAW_H__
