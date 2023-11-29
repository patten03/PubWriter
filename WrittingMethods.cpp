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

void checkSemicolon(const std::string& word)
{
	if (word.find(";") != -1) throw std::invalid_argument("Слово содержало <;>!");
}

void chechSpecialSymbols(const std::string& word)
{
	std::string forbiddenSymbols("0123456789!@#&()–[{}]:;',?/*`~$^+=<>\\№\"");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1) throw std::invalid_argument("Фамилия не может содержать специальные символы!");
	}
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
			"Дозаписать файл",
			"Выйти из программы"
		};

		ask(menuQuestions);
		int choice = inputChoice(menuQuestions.size());

		switch (choice)
		{
		case 1: newFile(); break;
		case 2: editFile(); break;
		case 3: work = false; break;
		default: throw std::invalid_argument("Некорректный формат ввода!");
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
			corrSurname(publisher.surname);
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
	std::string folder = findFolder("Выберите папку, где будете хранить файл");
	if (folder == "") return;

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
	case book: fullPath = folder + "\\" + filename + "{b}" + ".txt"; break;
	case publisher: fullPath = folder + "\\" + filename + "{p}" + ".txt"; break;
	default: throw std::invalid_argument("Некорректный формат ввода!");
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
		else
		{
			int beg = file.rfind("\\") + 1;
			int end = beg - file.length();
			std::cout << "Был создан файл " << file.substr(beg, end) << std::endl << std::endl;
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
			default: throw std::invalid_argument("Некорректный формат ввода!");
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

void editFile()
{
	std::string file = findFile("Выберите файл, который будете редактировать");
	if (file == "") return;

	continueWriting(file);
}

void continueWriting(const std::string& file)
{
	std::fstream stream;

	try
	{
		stream.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);

		if (!stream.is_open()) throw std::invalid_argument("Не удалось создать файл!\nПопробуйте выбрать другую папку или не использовать специальные символы.");

		fileType choice = defineFileType(file);

		std::string end("");

		while (end != "0")
		{
			switch (choice)
			{
			case book:
				stream << writeBook() << std::endl; break;
			case publisher:
				stream << writePublisher() << std::endl; break;
			default: throw std::invalid_argument("Некорректный формат ввода!");
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

int inputChoice(const int& end)
{
	int choiceInt = _getch();
	while (choiceInt <= '0' or choiceInt > char(end + '0'))
		choiceInt = _getch();

	choiceInt = choiceInt - '0';
	system("cls");
	return choiceInt;
}

void corrSurname(std::string& surname)
{
	surname[0] = toupper(surname[0]);
	for (int i(1); i < surname.size(); i++)
	{
		surname[i] = tolower(surname[i]);
	}
}