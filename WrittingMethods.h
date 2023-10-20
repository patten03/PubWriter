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
#include <algorithm>

enum fileType { book = 1, publisher = 2 };

struct Book
{
	std::string name;
	std::string kind;
	std::string organization;
	unsigned int year;
};

struct Publisher
{
	std::string name;
	std::string addres;
	std::string surname;
};

void standartSettings();

void ask(const std::vector<std::string> choice);
bool isNumber(const std::string& s);
int inputChoice(const int& end);
void checkSpecialSymbol(std::string word);
std::string space2underscore(std::string text);
std::string currentTime();
int countSymbol(const std::string& s, const char& sym);

void inputString(std::string& value, const std::string& question);
std::string writeBook();
std::string writePublisher();

void menu();

void newFile();
std::string findFolder();
void createFile(const std::string& file, fileType choice);


void editFile();
std::string findFile();
void continueWriting(const std::string& file);

#endif //WRITTINGMETHODS