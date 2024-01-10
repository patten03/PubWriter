#include "DirWork.h"

fileType defineFileType(const std::string& filename)
{
	fileType result(none);
	if (filename.find("{b}") != -1) result = book;
	if (filename.find("{p}") != -1) result = publisher;

	return result;
}

std::string space2underscore(std::string text)
{
	std::replace(text.begin(), text.end(), ' ', '_');
	return text;
}

std::string currentTime()
{
	std::string res;

	std::time_t t = std::time(NULL);
	std::tm now{};
	localtime_s(&now, &t);

	std::string date = std::to_string(now.tm_mday) + "_"
		+ std::to_string(now.tm_mon + 1) + "_"
		+ std::to_string(now.tm_year + 1900);


	std::string clockTime;

	if (now.tm_min < 10)
	{
		clockTime = std::to_string(now.tm_hour) + "_"
			+ "0" + std::to_string(now.tm_min);
	}
	else
	{
		clockTime = std::to_string(now.tm_hour) + "_"
			+ std::to_string(now.tm_min);
	}

	res = clockTime + "_" + date;
	return res;
}

void showDir(const std::vector<std::string>& dir)
{
	for (const auto& item : dir)
	{
		std::cout << "  " << item << std::endl;
	}
}

bool dirAccess(const std::string& folder)
{
	std::string filepath = folder + "\\check_permission.txt";
	std::ofstream file(filepath);
	file.close();

	bool res = std::filesystem::exists(filepath);
	if (res)
		system(("del " + filepath).c_str());
	return res;
}

std::string findFolder(std::string title)
{
	bool agree = false;
	std::filesystem::path p = ".";
	std::string begFolder = std::filesystem::absolute(p).string();
	std::string curFolder = begFolder;

	while (agree != true)
	{
		try
		{
			bool permission = dirAccess(curFolder);

			std::vector<std::string> folderList;
			std::cout << title << std::endl;
			std::vector<std::string> menu{
				"Выбрать текущую папку",
				"Выйти из папки",
				"Вернуться в изначальную папку",
				"Возврат в меню"
			};
			if (!permission)
				menu[0] = "Невозможно выбрать текущую папку";
			menu[0] = menu[0] + " (" + curFolder + ")";

			int begCoord = menu.size() + 1;
			int cur(begCoord); // arrow coordinate for folders

			makeDirList(curFolder, folderList);

			ask(menu);
			showDir(folderList);

			folderChoice(begCoord, folderList, cur, agree, curFolder);
			
			if (curFolder == "returnStart")
				curFolder = begFolder;
			if (agree and !permission and curFolder != "")
				agree = false;

			system("cls");
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			curFolder = curFolder.substr(0, curFolder.rfind("\\"));
		}
	}
	return curFolder;
}

void makeDirList(std::string folder, std::vector<std::string>& folderList)
{
	for (auto const& dirFolder : std::filesystem::directory_iterator(folder + "\\"))
	{
		if (dirFolder.is_directory())
		{
			std::string path = dirFolder.path().string();
			path = path.substr(path.rfind("\\") + 1, path.size());

			folderList.push_back(path);
		}
	}
}

void folderChoice(int menuSize, std::vector<std::string> folders, int& cur, bool& agree, std::string& folder)
{
	movingArrow(menuSize, menuSize + folders.size(), cur, 0); // just show the arrow

	bool chosenMenu(false);
	while (!chosenMenu)
	{
		switch (int c = _getch())
		{
		case 224: cur = movingArrow(menuSize, menuSize + folders.size() - 1, cur, _getch()); break;
		case '1': //сохранение текущей папки
		{
			chosenMenu = true;
			cur = menuSize;
			agree = true; break; //save current folder
		}
		case '2': //возвращение из текущей папки
		{
			chosenMenu = true;
			cur = menuSize;
			folder = folder.substr(0, folder.rfind("\\")); break; //return from last folder
		}
		case '3': //возвращение в изначальную папку
		{
			chosenMenu = true;
			cur = menuSize;
			folder = "returnStart";
			break;
		}
		case '4': //выход без выбора папки
		{
			chosenMenu = true;
			cur = menuSize;
			agree = true;
			folder = "";
			break;
		}
		case 13: //выбор папки
		{
			if (folders.size() == 0)
				folder = folder.substr(0, folder.rfind("\\"));
			else
				folder = folder + "\\" + folders[cur - menuSize];
			chosenMenu = true;
			cur = menuSize;
			break;
		}
		default: break;
		}
	}
}

std::string findFile(std::string title)
{
	std::filesystem::path p = ".";
	std::string begFilepath = std::filesystem::absolute(p).string();
	std::string curFilepath = begFilepath;

	while (curFilepath.find(".txt") == -1 and curFilepath != "")
	{
		try
		{
			std::vector<std::string> folderList;
			makeDirNFilesList(curFilepath, folderList);
			std::cout << title << std::endl;

			std::cout << "Текущая папка - (" + curFilepath + ")" << std::endl;
			std::vector<std::string> menu{
				"Выйти из папки",
				"Вернуться в изначальную папку",
				"Возврат в меню"
			};

			int begCoord = menu.size() + 1 + 1;
			int cur(begCoord); // arrow coordinate for folders

			ask(menu);
			showDir(folderList);

			fileChoice(begCoord, folderList, cur, curFilepath);
			if (curFilepath == "returnStart")
				curFilepath = begFilepath;

			system("cls");
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			curFilepath = curFilepath.substr(0, curFilepath.rfind("\\"));
		}
	}
	return curFilepath;
}

void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath)
{
	movingArrow(begCoord, begCoord + folders.size(), cur, 0); // just show the arrow

	bool chosenMenu(false);
	while (!chosenMenu)
	{
		switch (int c = _getch())
		{	// arrow code
		case 224: cur = movingArrow(begCoord, begCoord + folders.size() - 1, cur, _getch()); break;
		case '1':
		{
			filepath = filepath.substr(0, filepath.rfind("\\")); //return from last folder
			chosenMenu = true;
			cur = begCoord;
			break;
		}
		case '2':
		{
			filepath = "returnStart";
			chosenMenu = true;
			cur = begCoord;
			break;
		}
		case '3':
		{
			chosenMenu = true;
			cur = begCoord;
			filepath = ""; //stop process
			break; 
		}
		case 13: //enter key
		{
			if (folders.size() == 0)
				filepath = filepath.substr(0, filepath.rfind("\\"));
			else
				filepath = filepath + "\\" + folders[cur - begCoord];
			chosenMenu = true;
			cur = begCoord;
			break;
		}
		default: break;
		}
	}
}

void makeDirNFilesList(std::string filepath, std::vector<std::string>& folderList)
{
	for (auto const& dirFolder : std::filesystem::directory_iterator(filepath + "\\"))
	{
		if ((dirFolder.is_regular_file()
			and dirFolder.path().extension() == ".txt"
			and defineFileType(dirFolder.path().string()) != none)

			or dirFolder.is_directory())
		{
			std::string path = dirFolder.path().string();
			path = path.substr(path.rfind("\\") + 1, path.size());

			folderList.push_back(path);
		}
	}
}

int movingArrow(int ymin, int ymax, int cur, int key)
{
	DWORD dw;
	COORD here{ 0, cur };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		printf("Invalid handle");
	}

	if (here.Y > ymin and key == 72)
	{
		WriteConsoleOutputCharacter(hStdOut, L"  ", 2, here, &dw);
		here.Y -= 1;
	}
	if (here.Y < ymax and key == 80)
	{
		WriteConsoleOutputCharacter(hStdOut, L"  ", 2, here, &dw);
		here.Y += 1;
	}

	WriteConsoleOutputCharacter(hStdOut, L">>", 2, here, &dw);

	return here.Y;
}