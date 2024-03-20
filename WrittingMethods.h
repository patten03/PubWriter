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

//типы файлов и их определение
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
	std::string address;
	std::string surname;
};

//настройка русской кодировки
void standartSettings();

//дополнительные функции
void ask(const std::vector<std::string> choice);
bool isNumber(const std::string& s);
int inputChoice(const int& end);
void checkSemicolon(const std::string& word);
void checkNameSymbols(const std::string& word);
void checkSpecialSymbols(const std::string& word);
void corrSurname(std::string& surname);
void isAdequate(const std::string str);

//ввода строк
void inputString(std::string& value, const std::string& question);
std::string writeBook();
std::string writePublisher();

//главная функция
void menu();

//создания файла
void newFile();
void createFile(const std::string& file, fileType choice);

//дозаписи файла
void editFile();
void continueWriting(const std::string& file);

#endif //WRITTINGMETHODS