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

void menu();

std::string writeBook();
std::string writePublisher();

void newFile();
std::string currentTime();
std::string findFolder();
std::string space2underscore(std::string text);
void createFile(const std::string& file, fileType choice);
void inputString(std::string& value, const std::string& question);

void editFile();
std::string findFile();

#endif //WRITTINGMETHODS