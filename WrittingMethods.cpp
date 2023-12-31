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

void menu()
{
	std::cout << "����� ���������� � ��������� PublisherWriter" << std::endl;

	bool work = true;

	while (work)
	{
		std::cout << "�������� ������, ������� ������ ���������:" << std::endl;

		std::vector<std::string> menuQuestions{
			"������� ����",
			"���������� ����",
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
	if (book.name == "")
		return "quit";
	inputString(book.kind, "������� ��� �������");
	if (book.kind == "")
		return "quit";
	inputString(book.organization, "������� �������� �����������");
	if (book.organization == "")
		return "quit";

	std::string year;
	while (year == "")
	{
		try
		{
			std::cout << "������� ��� ������� XXXX" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, year);

			if (year == "0")
				return "quit";

			if (!isNumber(year))
				throw std::invalid_argument("��� ������� �� ������������� XXXX");

			book.year = stoi(year);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			year = "";
		}
	}

	return (book.name + "; "
		+ book.kind + "; "
		+ book.organization + "; "
		+ std::to_string(book.year));
}

std::string writePublisher()
{
	Publisher publisher;

	inputString(publisher.name, "������� �������� �������");
	if (publisher.name == "")
		return "quit";
	inputString(publisher.address, "������� ����� ��������");
	if (publisher.address == "")
		return "quit";

	publisher.surname = "";
	while (publisher.surname == "")
	{
		try
		{
			std::cout << "������� ������� �������� ���������" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.surname);
			if (publisher.surname == "0")
				return "quit";

			chechSpecialSymbols(publisher.surname);
			corrSurname(publisher.surname);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			publisher.surname = "";
		}
	}

	return (publisher.name + "; "
		+ publisher.address + "; "
		+ publisher.surname);
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
			if (value == "0") value = "";

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

void writingLoop(std::fstream& file, fileType type)
{
	std::string end("");

	std::string buff;
	while (end != "quit")
	{
		std::cout << "��� ����������� ������ � ������ ������� 0" << std::endl << std::endl;
		switch (type)
		{
		case book:
			buff = writeBook(); break;
		case publisher:
			buff = writePublisher(); break;
		default: throw std::invalid_argument("������������ ������ �����!");
		}

		if (buff == "quit")
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

		if (!fout.is_open()) throw std::invalid_argument("�� ������� ������� ����!\n���������� ������� ������ ����� ��� �� ������������ ����������� �������.");
		else
		{
			int beg = file.rfind("\\") + 1;
			int end = beg - file.length();
			std::cout << "��� ������ ���� " << file.substr(beg, end) << std::endl << std::endl;
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
	std::string file = findFile("�������� ����, ������� ������ �������������");
	if (file == "") return;

	continueWriting(file);
}

void continueWriting(const std::string& file)
{
	std::fstream stream;

	try
	{
		stream.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);

		if (!stream.is_open()) throw std::invalid_argument("�� ������� ������� ����!\n���������� ������� ������ ����� ��� �� ������������ ����������� �������.");

		fileType choice = defineFileType(file);

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