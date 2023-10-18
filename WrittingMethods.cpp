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

	system("cls");

	return choiceInt;
}

std::string space2underscore(std::string text)
{
	std::replace(text.begin(), text.end(), ' ', '_');
	return text;
}

void checkSpecialSymbol(std::string word)
{
	if (word.find(";") != -1) throw std::invalid_argument("Слово содержало <;>!");
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

std::string writeBook()
{
	Book book;

	bool approved(false);
	while (approved != true)
	{
		std::cout << "Слова не должны содержать в себе специальный символ <;>" << std::endl;
		try
		{
			std::cout << "Введите название издания" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, book.name);
			checkSpecialSymbol(book.name);

			std::cout << "Введите вид издания" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, book.kind);
			checkSpecialSymbol(book.kind);

			std::cout << "Введите издающую организацию" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, book.organization);
			checkSpecialSymbol(book.organization);
			approved = true;
		}
		catch (std::exception& ex)
		{
			system("cls");
			std::cout << ex.what() << std::endl;
		}
	}
	std::string year;
	while (year == "")
	{
		try
		{
			std::cout << "Введите год выпуска XXXX" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, year);

			if (!isNumber(year)) throw std::invalid_argument("Год выпуска не соответствует XXXX");

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

	bool approved(false);
	while (approved != true)
	{
		try
		{
			std::cout << "Введите название издания" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.name);
			checkSpecialSymbol(publisher.name);

			std::cout << "Введите адрес редакции" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.addres);
			checkSpecialSymbol(publisher.addres);

			std::cout << "Введите фамилию главного редактора" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.surname);
			checkSpecialSymbol(publisher.surname);

			approved = true;
		}
		catch(std::exception& ex)
		{
			system("cls");
			std::cout << ex.what() << std::endl;
		}
	}

	return (publisher.name + "; " + publisher.addres + "; " + publisher.surname);
}

void newFile()
{
	std::cout << "Выберите тип файла" << std::endl;

	std::vector<std::string> fileTypeString = {
	"Создать файл для записи данных вида: <название издания> <вид издания> <издающая организация> <год выпуска XXXX>",
	"Создать файл для записи данных вида: <название издания> <адрес редакции> <фамилия главного редактора>"
	};

	ask(fileTypeString);
	int fileTypeInt = inputChoice(fileTypeString.size());

	std::cout << "Выберите папку, где будете хранить файл" << std::endl;
	std::string folder = findFolder();

	std::cout << "Введите название файла" << std::endl << ">>";
	std::string filename;
	std::getline(std::cin, filename);
	system("cls");

	filename = space2underscore(filename);
	filename = filename + "_" + currentTime();
	std::string fullPath = folder + "/" + filename + ".txt";

	createFile(fullPath, fileType(fileTypeInt));
}

void createFile(const std::string& file, fileType choice)
{
	std::fstream fout;

	try
	{
		fout.open(file, std::ios_base::out);

		if (!fout.is_open()) throw std::invalid_argument("Не удалось создать файл!");

		std::string end("");

		while (end != "0")
		{
			switch (choice)
			{
			case book:
				fout << writeBook() << std::endl; break;
			case publisher:
				fout << writePublisher() << std::endl; break;
			}

			std::cout << "Для продолжения нажмите Enter, для выхода введите 0" << std::endl;
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

			for (auto const& dirFolder : std::filesystem::directory_iterator(folder + "/")) //maybe "\"
			{
				//"../../ghj.txt"
				std::string path = dirFolder.path().string();
				path = path.substr(path.rfind("/") + 1, path.size());

				folderList.push_back(path);
				//folderList.push_back(dirFolder.path().string().substr();
			}
	
			ask(folderList);
			int choice = inputChoice(folderList.size());

			switch (choice)
			{
			case 1: agree = true; break; //save current folder
			case 2: folder = folder.substr(0, folder.rfind("/")); break; //return from last folder
			default: folder = folder + "/" + folderList[choice - 1]; break;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "Вы не можете выбрать этот файл или папку!" << std::endl;
			folder = folder.substr(0, folder.rfind("/"));
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