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
			std::cout << "����� ������� �� ��������� ��� �� �������� ������" << std::endl;
		}
	}

	return choiceInt;
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
		}
	}
}

void newFile()
{
	std::cout << "�������� ��� �����" << std::endl;

	std::vector<std::string> fileTypeString = {
	"������� ���� ��� ������ ������ ����: <�������� �������> <��� �������> <�������� �����������> <��� �������>",
	"������� ���� ��� ������ ������ ����: <�������� �������> <����� ��������> <������� �������� ���������>"
	};

	ask(fileTypeString);
	int fileTypeInt = inputChoice(fileTypeString.size());

	std::cout << "�������� �����, ��� ������ ������� ����" << std::endl;


	bool agree = false;
	std::string folder = "C:\\";

	while (agree != true)
	{
		std::vector<std::string> pathList;
		pathList.push_back("������� ������� �����");
		pathList[0] = pathList[0] + " (" + folder + ")";
		pathList.push_back("�����");

		for (auto const& dirFolder : std::filesystem::directory_iterator(folder))
		{
			//pathList.push_back(dirFolder.path().string());
			pathList.push_back(dirFolder.path().relative_path().string());
		}

		ask(pathList);
		int choice = inputChoice(pathList.size());

		switch (choice)
		{
		case 1: break; //save current folder
		case 2: break;
		default: folder = folder + pathList[choice - 1] + "\\"; break;
		}
	}
}

void editFile()
{
	return;
}