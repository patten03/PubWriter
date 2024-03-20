#include "WrittingMethods.h"

void standartSettings()
{
	//��������� ������� ��������� ��� �������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::setlocale(LC_ALL, "ru");
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;//���� ����������� ���� ������ �� �����
	return !s.empty() && it == s.end(); //���������� false, ���� it �� �������� ��������� ��������
}

void ask(const std::vector<std::string> choice)
{
	//����� ���� ��� ������������� ������
	for (int i(0); i < choice.size(); i++)
	{
		std::cout << i + 1 << ". " << choice[i] << std::endl;
	}
}

void checkSemicolon(const std::string& word)
{
	if (word.find(";") != -1)
		throw std::invalid_argument("������ �� ����� ��������� <;>!");
}

void checkNameSymbols(const std::string& word)
{
	std::string forbiddenSymbols("0123456789!@#&()�[{}]:;',?/*`~$^+=<>\\�\"");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1)
			throw std::invalid_argument("������� �� ����� ��������� ����������� �������!");
	}
}

void checkSpecialSymbols(const std::string& word)
{
	std::string forbiddenSymbols("\\/:*?<>\"|");
	for (int i(0); i < forbiddenSymbols.size(); i++)
	{
		if (word.find(forbiddenSymbols[i]) != -1)
			throw std::invalid_argument("�������� ����� �� ����� ��������� \\/:*?<>\"|");
	}
}

void menu()
{
	std::cout << "����� ���������� � ��������� PublisherWriter" << std::endl << std::endl
		<< "��������� ��������� ��������� ����� ���� �����:" << std::endl
		<< "��� �������, ������� ������� �� �����:" << std::endl
		<< "- <�������� ������������>;" << std::endl
		<< "- <��� ������������>;" << std::endl
		<< "- <�������� �����������>;" << std::endl
		<< "- <��� �������>." << std::endl
		<< "��� ��������, �������� ������� �� �����:" << std::endl
		<< "- <�������� ������������>;" << std::endl
		<< "- <����� ��������>;" << std::endl
		<< "- <������� �������� ���������>;" << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������" << std::endl << std::endl;


	bool work = true; //���������� �����, ������� �������� �� ����� �� ���������

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
		default: break;
		}
	}
}

std::string writeBook()
{
	Book book;
	//��� ����������� �������� inputString() �������� ""
	//������� writeBook() ���������� "quit" ��� ������ ��
	//����� � ������� writtingLoop()

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
	while (year == "") //���� �������� ���� �� ������� ���������� ����
	{
		try
		{
			std::cout << "������� ��� ������� � �������� ������� ������� ���� � ��������� 1000-9999" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, year);

			if (year == "0") //����� 0 �������� �������� ��� ������ �� �����
				return "quit";

			if (!isNumber(year) or year.length() != 4 or stoi(year) < 1000) //�������� �� ������������ �������
				throw std::invalid_argument("��� ������� �� ������������� ��������� ������� ������� ���� � ��������� 1000-9999");

			book.year = stoi(year);
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			year = "";
		}
	}

	//������� ������, ������� ����� ������� � ����
	return (book.name + "; "
		+ book.kind + "; "
		+ book.organization + "; "
		+ std::to_string(book.year));
}

std::string writePublisher()
{
	Publisher publisher;
	//��� ����������� �������� inputString() �������� ""
	//������� writeBook() ���������� "quit" ��� ������ ��
	//����� � ������� writtingLoop()

	inputString(publisher.name, "������� �������� �������");
	if (publisher.name == "")
		return "quit";
	inputString(publisher.address, "������� ����� ��������");
	if (publisher.address == "")
		return "quit";

	publisher.surname = "";
	while (publisher.surname == "") //���� �������� ���� �� ������� ���������� �������
	{
		try
		{
			std::cout << "������� ������� �������� ���������" << std::endl;
			std::cout << ">>";
			std::getline(std::cin, publisher.surname);
			if (publisher.surname == "0")
				return "quit";

			checkNameSymbols(publisher.surname); //�������� �� ����������� �������
			corrSurname(publisher.surname); //��������� �������� ���� ���� �������
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			publisher.surname = "";
		}
	}

	//������� ������, ������� ����� ������� � ����
	return (publisher.name + "; "
		+ publisher.address + "; "
		+ publisher.surname);
}

void inputString(std::string& value, const std::string& question)
{
	bool approved(false); //���������� �����, ���������� true ����� ������ ������� ��� �����
	while (approved != true)
	{
		try
		{
			std::cout << question << std::endl;
			std::cout << ">>";
			std::getline(std::cin, value);
			checkSemicolon(value);
			if (value == "") //����������� ������������ �� ����� ������ �����
				throw std::invalid_argument("���������� ������ ������ ������, ��������� �������");
			if (value == "0") //0 - ������ ������ �� �����
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
	std::cout << "������� �������� �����, ��� ������ �� ����� ������� 0" << std::endl;

	bool approved(false);
	while (!approved) //�������� �� ������������ ����� �������� �����
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
	if (filename != "0") //����� �� ����� �������� ����� �� ����� ���������� �������
	{
		std::cout << "�������� ��� �����" << std::endl;

		std::vector<std::string> fileTypeString = {
		"������� ���� �������",
		"������� ���� ��������"
		};

		ask(fileTypeString);
		int fileTypeInt = inputChoice(fileTypeString.size());

		filename = space2underscore(filename); //������ �������� �� <_> � �������� �����
		filename = filename + "_" + currentTime(); //���������� � ����� �������� ����� ��������
		std::string fullPath;

		//���������� ����� ���� ����� � ��� ��������
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
	std::string end(""); //���������� �����, �������� �� ����� �� ������ ������ � ����

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
		default: break;
		}

		if (buff == "quit") //��������� ������� "�����" �� writeBook() ��� writePublisher()
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
			throw std::invalid_argument("�� ������� ������� ����!");
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
	
	if (file == "") //����� � ������� ����
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
			throw std::invalid_argument("�� ������� ������� ����!");

		fileType choice = defineFileType(file);

		std::cout << "��� ������ ���� " << file << std::endl << std::endl;

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

	//���� ����������� ������ ��� ������� ������� �� 1 �� <end>
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