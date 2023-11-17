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

enum fileType {none = 0, book = 1, publisher = 2};

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
std::string space2underscore(std::string text);
std::string currentTime();
int countSymbol(const std::string& s, const char& sym);
fileType defineFileType(const std::string& filename);

int movingArrow(int ymin, int ymax, int cur, int key);
void makeDirList(std::string folder, std::vector<std::string>& folderList);
void folderChoice(int menuSize, std::vector<std::string> folders, int& cur, bool& agree, std::string& folder);
void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath);
void makeDirNFilesList(std::string filepath, std::vector<std::string>& folderList);

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