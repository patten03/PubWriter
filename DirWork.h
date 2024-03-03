#ifndef DIRWORK
#define DIRWORK

#include "WrittingMethods.h"

//функции, измен€ющие название файлов
std::string space2underscore(std::string text);
std::string currentTime();
std::string formatXX(int num);

//составные части findFile()
int movingArrow(int ymin, int ymax, int cur, int key);
void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath);
void makeFilesList(std::string filepath, std::vector<std::string>& folderList);

//функци€, позвол€юща€ выбирать пользователю файлы
std::string findFile(std::string title);

#endif //DIRWORK
