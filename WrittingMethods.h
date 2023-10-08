#ifndef WRITTINGMETHODS
#define WRITTINGMETHODS

#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <filesystem>

void standartSettings();

void ask(const std::vector<std::string> choice);
bool isNumber(const std::string& s);
int inputChoice(const int& end);

void menu();

void newFile();

void editFile();

#endif //WRITTINGMETHODS