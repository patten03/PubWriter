#ifndef WRITTINGMETHODS
#define WRITTINGMETHODS

#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <filesystem>
#include <ctime>

void standartSettings();

void ask(const std::vector<std::string> choice);
bool isNumber(const std::string& s);
int inputChoice(const int& end);

void menu();

void newFile();

std::string currentTime();

std::string findFolder();

void editFile();
std::string findFile();

#endif //WRITTINGMETHODS