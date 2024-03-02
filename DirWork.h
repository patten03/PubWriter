#ifndef DIRWORK
#define DIRWORK

#include "WrittingMethods.h"

std::string space2underscore(std::string text);
std::string currentTime();

int movingArrow(int ymin, int ymax, int cur, int key);
void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath);
void makeFilesList(std::string filepath, std::vector<std::string>& folderList);

std::string findFile(std::string title);

#endif //DIRWORK
