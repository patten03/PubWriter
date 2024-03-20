#include "WrittingMethods.h"

void standartSettings()
{
	//установка русской кодировки для консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::setlocale(LC_ALL, "ru");
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;//цикл прерывается если символ не цифра
	return !s.empty() && it == s.end(); //возвращает false, если it не является последним символом
}

void ask(const std::vector<std::string> choice)
{
	//вывод меню как нумерованного списка
	for (int i(0); i < choice.size(); i++)
	{
		std::cout << i + 1 << ". " << choice[i] << std::endl;
	}
}

void checkSemicolon(const std::string& word)
{
	if (word.find(";") != -1)
		throw std::invalid_argument("Строка не может содержать <;>!");
}

void checkNameSymbols(const std::string& word)
{
	std::string forbiddenSymbols("0123456789!@#&()–[{}]:;',?/*`~$^+=<>\\№\"");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1)
			throw std::invalid_argument("Фамилия не может содержать специальные символы!");
	}
}

void checkSpecialSymbols(const std::string& word)
{
	std::string forbiddenSymbols("\\/:*?<>\"|");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1)
			throw std::invalid_argument("Название файла не может содержать \\/:*?<>\"|");
	}
}

void menu()
{
	std::cout << "Добро пожаловать в программу PublisherWriter" << std::endl << std::endl
		<< "Программа позволяет создавать файлы двух типов:" << std::endl
		<< "Тип издание, который состоит из полей:" << std::endl
		<< "- <название издательства>;" << std::endl
		<< "- <вид издательства>;" << std::endl
		<< "- <издающая организация>;" << std::endl
		<< "- <год издания>." << std::endl
		<< "Тип редакции, котороый состоит из полей:" << std::endl
		<< "- <название издательства>;" << std::endl
		<< "- <адрес редакции>;" << std::endl
		<< "- <фамилия главного редактора>;" << std::endl << std::endl
		<< "Для работы с файлами они должны находится в той же директории, что и программа" << std::endl << std::endl;


	bool work = true; //переменная цикла, которая отвечает за выход из программы

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
		default: break;
		}
	}
}

std::string writeBook()
{
	Book book;
	//при возвращении функцией inputString() значения ""
	//функция writeBook() возвращает "quit" для выхода из
	//цикла в функции writtingLoop()

	inputString(book.name, "Введите название издания");
	if (book.name == "")
		return "quit";
	inputString(book.kind, "Введите вид издания");
	if (book.kind == "")
		return "quit";
	inputString(book.organization, "Введите издающую организацию");
	if (book.organization == "")
		return "quit";

	std::string year;
	while (year == "") //цикл работает пока не получит корректную дату
	{
		try
		{
			std::cout << "Введите год выпуска в числовом формате четырех цифр в диапазоне 1000-9999" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, year);

			if (year == "0") //цифра 0 является символом для выхода из цикла
				return "quit";

			if (!isNumber(year) or year.length() != 4 or stoi(year) < 1000) //проверка на соотвествует формату
				throw std::invalid_argument("Год выпуска не соответствует числовому формату четырех цифр в диапазоне 1000-9999");

			book.year = stoi(year);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			year = "";
		}
	}

	//возврат строки, которая будет введена в файл
	return (book.name + "; "
		+ book.kind + "; "
		+ book.organization + "; "
		+ std::to_string(book.year));
}

std::string writePublisher()
{
	Publisher publisher;
	//при возвращении функцией inputString() значения ""
	//функция writeBook() возвращает "quit" для выхода из
	//цикла в функции writtingLoop()

	inputString(publisher.name, "Введите название издания");
	if (publisher.name == "")
		return "quit";
	inputString(publisher.address, "Введите адрес редакции");
	if (publisher.address == "")
		return "quit";

	publisher.surname = "";
	while (publisher.surname == "") //цикл работает пока не получит корректную фамилию
	{
		try
		{
			std::cout << "Введите фамилию главного редактора" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.surname);
			if (publisher.surname == "0")
				return "quit";

			checkNameSymbols(publisher.surname); //Проверка на специальные символы
			corrSurname(publisher.surname); //Изменения регистра всех букв фамилии
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			publisher.surname = "";
		}
	}

	//возврат строки, которая будет введена в файл
	return (publisher.name + "; "
		+ publisher.address + "; "
		+ publisher.surname);
}

void inputString(std::string& value, const std::string& question)
{
	bool approved(false); //переменная цикла, становится true когда строка введена без ошибо
	while (approved != true)
	{
		try
		{
			std::cout << question << std::endl;
			std::cout << ">>";
			std::getline(std::cin, value);
			checkSemicolon(value);
			if (value == "") //ограничения пользователя от ввода пустых строк
				throw std::invalid_argument("Невозможно ввести пустую строку, повторите попытку");
			if (value == "0") //0 - символ выхода из цикла
				value = "";

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
	std::string filename;
	std::cout << "Введите название файла, для выхода из ввода введите 0" << std::endl;

	bool approved(false);
	while (!approved) //проверка на корректность ввода названия файла
	{
		try
		{

			std::cout << ">>";
			std::getline(std::cin, filename);
			checkSpecialSymbols(filename);
			approved = true;
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	system("cls");
	if (filename != "0") //выход из цикла названия файла по вводу служебного символа
	{
		std::cout << "Выберите тип файла" << std::endl;

		std::vector<std::string> fileTypeString = {
		"Создать файл издания",
		"Создать файл редакции"
		};

		ask(fileTypeString);
		int fileTypeInt = inputChoice(fileTypeString.size());

		filename = space2underscore(filename); //замена пробелов на <_> в названии файла
		filename = filename + "_" + currentTime(); //добавление к концу названия время создания
		std::string fullPath;

		//добавление метки типа файла в его название
		switch (fileType(fileTypeInt))
		{
		case book: fullPath = filename + "{b}" + ".txt"; break;
		case publisher: fullPath = filename + "{p}" + ".txt"; break;
		default: break;
		}

		createFile(fullPath, fileType(fileTypeInt));
	}
}

void writingLoop(std::fstream& file, fileType type)
{
	std::string end(""); //переменная цикла, отвечает за выход из записи данных в файл

	std::string buff;
	while (end != "quit")
	{
		std::cout << "Для прекращения работы с файлом введите 0" << std::endl << std::endl;
		switch (type)
		{
		case book:
			buff = writeBook(); break;
		case publisher:
			buff = writePublisher(); break;
		default: break;
		}

		if (buff == "quit") //получение команды "выход" из writeBook() или writePublisher()
			end = buff;
		else
			file << buff << std::endl;

		system("cls");
	}
}

void createFile(const std::string& file, fileType choice)
{
	std::fstream fout;

	try
	{
		fout.open(file, std::ios_base::out);

		if (!fout.is_open())
			throw std::invalid_argument("Не удалось создать файл!");
		else
		{
			int beg = file.rfind("\\") + 1;
			int end = beg - file.length();
			std::cout << "Был создан файл " << file.substr(beg, end) << std::endl << std::endl;
		}

		writingLoop(fout, choice);

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
	
	if (file == "") //выход в главное меню
		return;

	continueWriting(file);
}

void continueWriting(const std::string& file)
{
	std::fstream stream;

	try
	{
		stream.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);

		if (!stream.is_open())
			throw std::invalid_argument("Не удалось создать файл!");

		fileType choice = defineFileType(file);

		std::cout << "Был выбран файл " << file << std::endl << std::endl;

		writingLoop(stream, choice);

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

	//цикл прерывается только при нажатии клавиши от 1 до <end>
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