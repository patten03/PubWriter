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
void ask(const std::string* choice, const int& size);
bool isNumber(const std::string& s);
int inputChoice(const int& end);

void menu();

void newFile();

void writeData(std::fstream& stream, int fileType);

std::string currentTime();

std::string findFolder();

void editFile();
std::string findFile();

#endif //WRITTINGMETHODS