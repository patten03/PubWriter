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

void checkSemicolon(const std::string& word)
{
	if (word.find(";") != -1) throw std::invalid_argument("Слово содержало <;>!");
}

void chechSpecialSymbols(const std::string& word)
{
	std::string forbiddenSymbols("0123456789!@#&()–[{}]:;',?/*`~$^+=<>\\");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1) throw std::invalid_argument("Фамилия не может содержать специальные символы!");
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

	inputString(book.name, "Введите название издания");
	inputString(book.kind, "Введите вид издания");
	inputString(book.organization, "Введите издающую организацию");

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

	inputString(publisher.name, "Введите название издания");
	inputString(publisher.addres, "Введите адрес редакции");

	publisher.surname = "";
	while (publisher.surname == "")
	{
		try
		{
			std::cout << "Введите фамилию главного редактора" << std::endl;
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
	//inputString(publisher.surname, "Введите фамилию главного редактора");

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
			if (value == "") throw std::invalid_argument("Пустое поле ввода!");

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
	std::cout << "Выберите папку, где будете хранить файл" << std::endl;
	std::string folder = findFolder();

	std::cout << "Введите название файла" << std::endl << ">>";
	std::string filename;
	std::getline(std::cin, filename);
	system("cls");

	std::cout << "Выберите тип файла" << std::endl;

	std::vector<std::string> fileTypeString = {
	"Создать файл издания",
	"Создать файл редакции"
	};

	ask(fileTypeString);
	int fileTypeInt = inputChoice(fileTypeString.size());

	filename = space2underscore(filename);
	filename = filename + "_" + currentTime();
	std::string fullPath;

	switch (fileType(fileTypeInt))
	{
	case book: fullPath = folder + "/" + filename + "{b}" + ".txt";
	case publisher: fullPath = folder + "/" + filename + "{p}" + ".txt";
	}

	createFile(fullPath, fileType(fileTypeInt));
}

void createFile(const std::string& file, fileType choice)
{
	std::fstream fout;

	try
	{
		fout.open(file, std::ios_base::out);

		if (!fout.is_open()) throw std::invalid_argument("Не удалось создать файл!\nПопробуйте выбрать другую папку или не использовать специальные символы.");

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
	//std::string folder = "C:";
	std::string folder = ".";

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
				if (dirFolder.is_directory())
				{
					std::string path = dirFolder.path().string();
					path = path.substr(path.rfind("/") + 1, path.size());

					folderList.push_back(path);
				}
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
	std::cout << "Выберите файл, который будете редактировать" << std::endl;
	std::string file = findFile();
	
	std::vector<std::string> editFileMenu{
		"Продолжить запись",
		"Назад"
	};

	ask(editFileMenu);
	int answer = inputChoice(editFileMenu.size());

	switch (answer)
	{
	case 1: continueWriting(file); break;
	case 2: break;
	}
	
}

std::string findFile()
{
	//std::string folder = "C:";
	std::string filepath = ".";

	while (filepath.find(".txt") == -1)
	{
		try
		{
			std::vector<std::string> folderList;
			folderList.push_back("Назад");

			for (auto const& dirFolder : std::filesystem::directory_iterator(filepath + "/"))
			{
				if ((dirFolder.is_regular_file()
					and dirFolder.path().extension() == ".txt"
					and defineFileType(dirFolder.path().string()) != none)

					or dirFolder.is_directory())
				{
					std::string path = dirFolder.path().string();
					path = path.substr(path.rfind("/") + 1, path.size());

					folderList.push_back(path);
				}
			}

			std::cout << "Текущая папка - (" + filepath + ")" << std::endl;
			ask(folderList);
			int choice = inputChoice(folderList.size());

			switch (choice)
			{
			case 1: filepath = filepath.substr(0, filepath.rfind("/")); break; //return from last folder
			default: filepath = filepath + "/" + folderList[choice - 1]; break;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "Вы не можете выбрать этот файл или папку!" << std::endl;
			filepath = filepath.substr(0, filepath.rfind("/"));
		}
	}

	return filepath;
}

void continueWriting(const std::string& file)
{
	std::fstream stream;

	try
	{
		stream.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);

		if (!stream.is_open()) throw std::invalid_argument("Не удалось создать файл!\nПопробуйте выбрать другую папку или не использовать специальные символы.");
		
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
			}

			std::cout << "Для продолжения нажмите Enter, для выхода введите 0" << std::endl;
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