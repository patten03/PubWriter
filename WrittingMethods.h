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
#include <conio.h>
#include "DirWork.h"

enum fileType { none = 0, book = 1, publisher = 2 };
fileType defineFileType(const std::string& filename);

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
void checkSemicolon(const std::string& word);

void inputString(std::string& value, const std::string& question);
std::string writeBook();
std::string writePublisher();

void menu();

void newFile();
std::string findFolder(std::string title);
void createFile(const std::string& file, fileType choice);

void editFile();
std::string findFile(std::string title);
void continueWriting(const std::string& file);

#endif //WRITTINGMETHODS