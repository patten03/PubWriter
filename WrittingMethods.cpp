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

	return choiceInt;
}

void menu()
{
	std::cout << "Добро пожаловать в программу PublisherWriter" << std::endl;

	bool work = true;

	while (work)
	{
		std::cout << "Выберите задачу, которую хотите выполнить:" << std::endl;

		std::vector<std::string> menuQuestions{
			"Создать файл",
			"Редактировать файл",
			"Выйти из программы"
		};

		ask(menuQuestions);
		int choice = inputChoice(menuQuestions.size());

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

	std::vector<std::string> fileTypeString = {
	"Создать файл для записи данных вида: <название издания> <вид издания> <издающая организация> <год выпуска>",
	"Создать файл для записи данных вида: <название издания> <адрес редакции> <фамилия главного редактора>"
	};

	ask(fileTypeString);
	int fileTypeInt = inputChoice(fileTypeString.size());

	std::cout << "Выберите папку, где будете хранить файл" << std::endl;
	std::string folder = findFolder();


}

std::string findFolder()
{
	bool agree = false;
	std::string folder = "C:";

	while (agree != true)
	{
		std::vector<std::string> folderList;
		folderList.push_back("Выбрать текущую папку");
		folderList[0] = folderList[0] + " (" + folder + ")";
		folderList.push_back("Назад");

		for (auto const& dirFolder : std::filesystem::directory_iterator(folder + "\\"))
		{
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
		case 2: folder = folder.substr(0, folder.rfind("\\") + 1); break;
		default: folder = folder + "\\" + folderList[choice - 1]; break;
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