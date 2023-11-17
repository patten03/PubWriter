#include "WrittingMethods.h"

void standartSettings()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::setlocale(LC_ALL, "ru");
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void ask(const std::vector<std::string> choice)
{
	for (int i(0); i < choice.size(); i++)
	{
		std::cout << i + 1 << ". " << choice[i] << std::endl;
	}
}

//int inputChoice(const int& end)
//{
//	bool incorrectInput = true;
//	std::string choiceString;
//	int choiceInt;
//	std::exception ex;
//
//	while (incorrectInput)
//	{
//		try
//		{
//			std::cout << ">>";
//			std::getline(std::cin, choiceString);
//
//			choiceInt = std::stoi(choiceString);
//
//			if (choiceInt >= 1 and choiceInt <= end and isNumber(choiceString))
//				incorrectInput = false;
//			else
//				throw ex;
//		}
//		catch (const std::exception& ex)
//		{
//			std::cout << "����� ������� �� ��������� ��� �� �������� ������!" << std::endl;
//		}
//	}
//
//	system("cls");
//
//	return choiceInt;
//}

std::string space2underscore(std::string text)
{
	std::replace(text.begin(), text.end(), ' ', '_');
	return text;
}

void checkSemicolon(const std::string& word)
{
	if (word.find(";") != -1) throw std::invalid_argument("����� ��������� <;>!");
}

void chechSpecialSymbols(const std::string& word)
{
	std::string forbiddenSymbols("0123456789!@#&()�[{}]:;',?/*`~$^+=<>\\�\"");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1) throw std::invalid_argument("������� �� ����� ��������� ����������� �������!");
	}
}

int countSymbol(const std::string& s, const char& sym)
{
	int count = 0;

	for (int i = 0; i < s.size(); i++)
		if (s[i] == sym) count++;

	return count;
}

fileType defineFileType(const std::string& filename)
{
	fileType result(none);
	if (filename.find("{b}") != -1) result = book;
	if (filename.find("{p}") != -1) result = publisher;

	return result;
}

void menu()
{
	std::cout << "����� ���������� � ��������� PublisherWriter" << std::endl;

	bool work = true;

	while (work)
	{
		std::cout << "�������� ������, ������� ������ ���������:" << std::endl;

		std::vector<std::string> menuQuestions{
			"������� ����",
			"������������� ����",
			"����� �� ���������"
		};

		ask(menuQuestions);
		int choice = inputChoice(menuQuestions.size());

		switch (choice)
		{
		case 1: newFile(); break;
		case 2: editFile(); break;
		case 3: work = false; break;
		default: throw std::invalid_argument("������������ ������ �����!");
		}
	}
}

std::string writeBook()
{
	Book book;

	inputString(book.name, "������� �������� �������");
	inputString(book.kind, "������� ��� �������");
	inputString(book.organization, "������� �������� �����������");

	std::string year;
	while (year == "")
	{
		try
		{
			std::cout << "������� ��� ������� XXXX" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, year);

			if (!isNumber(year)) throw std::invalid_argument("��� ������� �� ������������� XXXX");

			book.year = stoi(year);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			year = "";
		}
	}

	return (book.name + "; " + book.kind + "; " + book.organization + "; " + std::to_string(book.year));
}

std::string writePublisher()
{
	Publisher publisher;

	inputString(publisher.name, "������� �������� �������");
	inputString(publisher.addres, "������� ����� ��������");

	publisher.surname = "";
	while (publisher.surname == "")
	{
		try
		{
			std::cout << "������� ������� �������� ���������" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.surname);

			chechSpecialSymbols(publisher.surname);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			publisher.surname = "";
		}
	}
	//inputString(publisher.surname, "������� ������� �������� ���������");

	return (publisher.name + "; " + publisher.addres + "; " + publisher.surname);
}

void inputString(std::string& value, const std::string& question)
{
	bool approved(false);
	while (approved != true)
	{
		try
		{
			std::cout << question << std::endl;
			std::cout << ">>";
			std::getline(std::cin, value);
			checkSemicolon(value);
			if (value == "") throw std::invalid_argument("������ ���� �����!");

			approved = true;
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}

void newFile()
{
	std::string folder = findFolder("�������� �����, ��� ������ ������� ����");
	if (folder == "") return;

	std::cout << "������� �������� �����" << std::endl << ">>";
	std::string filename;
	std::getline(std::cin, filename);
	system("cls");

	std::cout << "�������� ��� �����" << std::endl;

	std::vector<std::string> fileTypeString = {
	"������� ���� �������",
	"������� ���� ��������"
	};

	ask(fileTypeString);
	int fileTypeInt = inputChoice(fileTypeString.size());

	filename = space2underscore(filename);
	filename = filename + "_" + currentTime();
	std::string fullPath;

	switch (fileType(fileTypeInt))
	{
	case book: fullPath = folder + "\\" + filename + "{b}" + ".txt"; break;
	case publisher: fullPath = folder + "\\" + filename + "{p}" + ".txt"; break;
	default: throw std::invalid_argument("������������ ������ �����!");
	}

	createFile(fullPath, fileType(fileTypeInt));
}


/*
* 
* doxygen
 @brief JJJ
 @param fsfs
*/
void createFile(const std::string& file, fileType choice)
{
	std::fstream fout;

	try
	{
		fout.open(file, std::ios_base::out);

		if (!fout.is_open()) throw std::invalid_argument("�� ������� ������� ����!\n���������� ������� ������ ����� ��� �� ������������ ����������� �������.");
		else
		{
			int beg = file.rfind("\\") + 1;
			int end = beg - file.length();
			std::cout << "��� ������ ���� " << file.substr(beg, end) << std::endl << std::endl;
		}

		std::string end("");

		while (end != "0")
		{
			switch (choice)
			{
			case book:
				fout << writeBook() << std::endl; break;
			case publisher:
				fout << writePublisher() << std::endl; break;
			default: throw std::invalid_argument("������������ ������ �����!");
			}

			std::cout << "��� ����������� ������� Enter, ��� ������ ������� 0" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, end);

			system("cls");
		}

		fout.close();
	}

	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void writeData(std::fstream &stream, fileType choice)
{
	switch (choice)
	{
	case book:
	{
		break;
	}
	case publisher:
	{
		std::string buff("_");

		while (buff != "")
		{
			std::cout << "������� " << std::endl << ">>";
			std::getline(std::cin, buff);
		}
		break;
	}
	default: throw std::invalid_argument("������������ ������ �����!");
	}

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

void editFile()
{
	std::string file = findFile("�������� ����, ������� ������ �������������");
	if (file == "") return;
	
	std::vector<std::string> editFileMenu{
		"���������� ������",
		"�����"
	};

	ask(editFileMenu);
	int answer = inputChoice(editFileMenu.size());

	switch (answer)
	{
	case 1: continueWriting(file); break;
	case 2: break;
	default: throw std::invalid_argument("������������ ������ �����!");
	}
}

void continueWriting(const std::string& file)
{
	std::fstream stream;

	try
	{
		stream.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);

		if (!stream.is_open()) throw std::invalid_argument("�� ������� ������� ����!\n���������� ������� ������ ����� ��� �� ������������ ����������� �������.");
		
		int a = stream.tellg();
		stream.seekg(std::ios::beg);
		a = stream.tellg();

		std::string str;
		std::getline(stream, str);
		fileType choice;
		if (countSymbol(str, ';') == 3) choice = book;
		else choice = publisher;

		stream.seekg(0, std::ios::end);
		a = stream.tellg();

		std::string end("");

		while (end != "0")
		{
			switch (choice)
			{
			case book:
				stream << writeBook() << std::endl; break;
			case publisher:
				stream << writePublisher() << std::endl; break;
			default: throw std::invalid_argument("������������ ������ �����!");
			}

			std::cout << "��� ����������� ������� Enter, ��� ������ ������� 0" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, end);

			system("cls");
		}

		stream.close();
	}

	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void showDir(const std::vector<std::string>& dir)
{
	for (const auto& item : dir)
	{
		std::cout << "  " << item << std::endl;
	}
}

std::string findFolder(std::string title)
{
	bool agree = false;
	std::filesystem::path p = ".";
	std::string folder = std::filesystem::absolute(p).string();

	while (agree != true)
	{
		try
		{
			std::vector<std::string> folderList;
			std::cout << title << std::endl;
			std::vector<std::string> menu{
				"������� ������� �����",
				"����� �� �����",
				"������� � ����"
			};
			menu[0] = menu[0] + " (" + folder + ")";

			int begCoord = menu.size() + 1;
			int cur(begCoord); // arrow coordinate for folders

			makeDirList(folder, folderList);

			ask(menu);
			showDir(folderList);

			folderChoice(begCoord, folderList, cur, agree, folder);

			system("cls");
		}
		catch (const std::exception& ex)
		{
			std::cout << "�� �� ������ ������� ���� ���� ��� �����!" << std::endl;
			folder = folder.substr(0, folder.rfind("\\"));
		}
	}
	return folder;
}

void makeDirList(std::string folder, std::vector<std::string>& folderList)
{
	for (auto const& dirFolder : std::filesystem::directory_iterator(folder + "\\")) //maybe "\"
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

	bool choosedMenu(false);
	while (!choosedMenu)
	{
		switch (int c = _getch())
		{
		case 224: cur = movingArrow(menuSize, menuSize + folders.size() - 1, cur, _getch()); break;
		case '1':
		{
			choosedMenu = true;
			cur = menuSize;
			agree = true; break; //save current folder
		}
		case '2':
		{
			choosedMenu = true;
			cur = menuSize;
			folder = folder.substr(0, folder.rfind("\\")); break; //return from last folder
		}
		case '3':
		{
			choosedMenu = true;
			cur = menuSize;
			agree = true;
			folder = "";
			break;
		}
		case 13:
		{
			if (folders.size() == 0)
				folder = folder.substr(0, folder.rfind("\\"));
			else
				folder = folder + "\\" + folders[cur - menuSize];
			choosedMenu = true;
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
	std::string filepath = std::filesystem::absolute(p).string();

	while (filepath.find(".txt") == -1 and filepath != "")
	{
		try
		{
			std::vector<std::string> folderList;
			makeDirNFilesList(filepath, folderList);
			std::cout << title << std::endl;

			std::cout << "������� ����� - (" + filepath + ")" << std::endl;
			std::vector<std::string> menu{
				"����� �� �����",
				"������� � ����"
			};

			int begCoord = menu.size() + 1 + 1;
			int cur(begCoord); // arrow coordinate for folders

			ask(menu);
			showDir(folderList);

			fileChoice(begCoord, folderList, cur, filepath);

			system("cls");
		}
		catch (const std::exception& ex)
		{
			std::cout << "�� �� ������ ������� ���� ���� ��� �����!" << std::endl;
			filepath = filepath.substr(0, filepath.rfind("\\"));
		}
	}
	return filepath;
}

void fileChoice(int begCoord, std::vector<std::string> folders, int& cur, std::string& filepath)
{
	movingArrow(begCoord, begCoord + folders.size(), cur, 0); // just show the arrow

	bool choosedMenu(false);
	while (!choosedMenu)
	{
		switch (int c = _getch())
		{	// arrow code
		case 224: cur = movingArrow(begCoord, begCoord + folders.size() - 1, cur, _getch()); break;
		case '1':
		{
			filepath = filepath.substr(0, filepath.rfind("\\")); //return from last folder
			choosedMenu = true;
			cur = begCoord;
			break;
		}
		case '2':
		{
			choosedMenu = true;
			cur = begCoord;
			filepath = ""; break; //stop process
		}
		case 13: //enter key
		{
			if (folders.size() == 0)
				filepath = filepath.substr(0, filepath.rfind("\\"));
			else
				filepath = filepath + "\\" + folders[cur - begCoord];
			choosedMenu = true;
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

int inputChoice(const int& end)
{
	int choiceInt = _getch();
	while (choiceInt <= '0' or choiceInt > char(end + '0'))
		choiceInt = _getch();

	choiceInt = choiceInt - '0';
	system("cls");
	return choiceInt;
}