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

void ask(const std::string* choice, const int& size)
{
	for (int i(0); i < size; i++)
	{
		std::cout << i + 1 << ". " << choice[i] << std::endl;
	}
}

int inputChoice(const int& end)
{
	bool incorrectInput = true;
	std::string choiceString;
	int choiceInt;
	std::exception ex;

	while (incorrectInput)
	{
		try
		{
			std::cout << ">>";
			std::getline(std::cin, choiceString);

			choiceInt = std::stoi(choiceString);

			if (choiceInt >= 1 and choiceInt <= end and isNumber(choiceString))
				incorrectInput = false;
			else
				throw ex;
		}
		catch (const std::exception& ex)
		{
			std::cout << "Выбор выходит из диапазона или не является числом!" << std::endl;
		}
	}

	system("cls");

	return choiceInt;
}

void menu()
{
	std::cout << "Добро пожаловать в программу PublisherWriter" << std::endl;

	bool work = true;

	while (work)
	{
		std::cout << "Выберите задачу, которую хотите выполнить:" << std::endl;

		//std::vector<std::string> menuQuestions{
		//	"Создать файл",
		//	"Редактировать файл",
		//	"Выйти из программы"
		//};

		std::string menuQuestions[]{
			"Создать файл",
			"Редактировать файл",
			"Выйти из программы"
		};


		ask(menuQuestions, sizeof(menuQuestions) / sizeof(menuQuestions[0]));
		int choice = inputChoice(sizeof(menuQuestions));

		switch (choice)
		{
		case 1: newFile(); break;
		case 2: editFile(); break;
		case 3: work = false; break;
		}
	}
}

void newFile()
{
	std::cout << "Выберите тип файла" << std::endl;

	std::string fileTypeString[]{
		"Создать файл для записи данных вида: <название издания> <вид издания> <издающая организация> <год выпуска>",
		"Создать файл для записи данных вида: <название издания> <адрес редакции> <фамилия главного редактора>"
	};

	//std::vector<std::string> fileTypeString = {
	//"Создать файл для записи данных вида: <название издания> <вид издания> <издающая организация> <год выпуска>",
	//"Создать файл для записи данных вида: <название издания> <адрес редакции> <фамилия главного редактора>"
	//};

	ask(fileTypeString, sizeof(fileTypeString) / sizeof(fileTypeString[0]));
	int fileTypeInt = inputChoice(sizeof(fileTypeString) / sizeof(fileTypeString[0]));

	std::cout << "Выберите папку, где будете хранить файл" << std::endl;
	std::string folder = findFolder();

	std::cout << "Введите название файла" << std::endl << ">>";
	std::string filename;
	std::getline(std::cin, filename);
	system("cls");

	filename = filename + " " + currentTime();

	std::string fullPath = folder + "\\" + filename + ".txt";
	std::fstream fout;
	fout.open(fullPath,std::ios::out);

	//fout << "Hello world!" << std::endl;

	//std::cout << fout.is_open() << std::endl; // сделать проверку на открытие файла и задать отдельной функцией создание файла

	writeData(fout, fileTypeInt);


	fout.close();
}

void writeData(std::fstream &stream, int fileType)
{
	enum fileTypes {book = 1, publisher = 2};

	switch (fileType)
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
			std::cout << "Введите " << std::endl << ">>";
			std::getline(std::cin, buff);
		}
		break;
	}
	}

}

std::string currentTime()
{
	std::string res;

	std::time_t t = std::time(NULL);
	std::tm now{};
	localtime_s(&now, &t);

	std::string date = std::to_string(now.tm_mday) + "."
		+ std::to_string(now.tm_mon + 1) + "."
		+ std::to_string(now.tm_year + 1900);


	std::string clockTime;

	if (now.tm_min < 10)
	{
		clockTime = std::to_string(now.tm_hour) + "."
			+ "0" + std::to_string(now.tm_min);
	}
	else
	{
		clockTime = std::to_string(now.tm_hour) + "."
			+ std::to_string(now.tm_min);
	}

	res = clockTime + " " + date;
	return res;
}

std::string findFolder()
{
	bool agree = false;
	std::string folder = "C:";

	while (agree != true)
	{
		try
		{
			std::vector<std::string> folderList;
			folderList.push_back("Выбрать текущую папку");
			folderList[0] = folderList[0] + " (" + folder + ")";

			folderList.push_back("Назад");

			for (auto const& dirFolder : std::filesystem::directory_iterator(folder + "\\")) //maybe "\"
			{
				//"../../ghj.txt"
				std::string path = dirFolder.path().string();
				path = path.substr(path.rfind("\\") + 1, path.size());

				folderList.push_back(path);
				//folderList.push_back(dirFolder.path().string().substr();
			}
	
			ask(folderList);
			int choice = inputChoice(folderList.size());

			switch (choice)
			{
			case 1: agree = true; break; //save current folder
			case 2: folder = folder.substr(0, folder.rfind("\\")); break; //return from last folder
			default: folder = folder + "\\" + folderList[choice - 1]; break;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "Вы не можете выбрать этот файл или папку!" << std::endl;
			folder = folder.substr(0, folder.rfind("\\"));
		}
	}
	return folder;
}

void editFile()
{
	return;
}

std::string findFile()
{
	return 0;
}