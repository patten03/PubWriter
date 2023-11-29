#ifndef DIRWORK
#define DIRWORK

#include "WrittingMethods.h"

std::string space2underscore(std::string text);
std::string currentTime();

int movingArrow(int ymin, int ymax, int cur, int key);
void makeDirList(std::string folder, std::vector<std::string>& folderList);
void folderChoice(int menuSize, std::vector<std::string> folders, int& cur, bool& agree, std::string& folder);
void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath);
void makeDirNFilesList(std::string filepath, std::vector<std::string>& folderList);

#endif //DIRWORK
