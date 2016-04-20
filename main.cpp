#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <windows.h>

#define random 1 + rand() % 6

using namespace std;

string player1, player2;

void menu()
{
	int select(0);
	while (select != 49)
	{
		system("cls");
		cout << "***����� �� ������(Yahtzee).***\n" << endl;
		cout << "1. ������ ����." << endl;
		cout << "2. �������." << endl;
		cout << "3. �����." << endl;
		select = _getch();
		switch (select)
		{
		case 49:
		{
			system("cls");
			break;
		}
		case 50:
		{
			ifstream rules("rules.txt");
			char ch({ ' ' }),buff[100];
			system("cls");
			if (rules.is_open())
				while (ch != '\0')
				{

					rules.getline(buff, 100);
					ch = buff[0];
					cout << buff << endl;
				}
			else
				cout << "���� �� ����� ���� ������." << endl;
			system("pause");
			break;
		}
		case 51:
		{
			system("cls");
			cout << "�� ��������!" << endl;
			Sleep(1300);
			exit(-1);
		}
		}
	}
}

void enternames()
{
	while (player1 == player2)
	{
		cout << "������� ��� ������� ������: " << endl;
		cin >> player1;
		cout << "������� ��� ������� ������: " << endl;
		cin >> player2;
		if (player1 == player2)
		{
			cout << "����� ������ ���� �������." << endl;
			system("pause");
		}
		system("cls");
	}
}

void outputbones(string player,int dice[6])
{
	cout << "****����� ������ " << player << ":****\n\n[1] [2] [3] [4] [5]\n ";
	for (int i = 1; i < 6; i++)
		cout << dice[i] << "   ";
	cout << "\n" << endl;
}

int compare(const void * x1, const void * x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

bool inputcheck(string retake)
{
	bool fail(true);
		for (int i = 0; i < retake.length(); i++)
		{
			if (retake[i] == '1' || retake[i] == '2' || retake[i] == '3' || retake[i] == '4' || retake[i] == '5')
				fail = false;
			else
			{
				fail = true;
				cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
				break;
			}
		}
		if (fail)			// ��� �������������� ������ ��������� �� ������ ��������� ���
			return fail;
		for (int i = 0; i < retake.length(); i++)
		{
			for (int j = i + 1; j < retake.length(); j++)
				if (retake[i] == retake[j])
				{
					fail = true;
					cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
					break;
				}
			break;
		}
		return fail;
}

void turn(string player, int dice[6])
{
	bool used[6] = { false,false,false,false,false,false };
	srand(time(0));
	cout << "��� ������ " << player << "..\n" << endl;
	system("pause");
	system("cls");
	for (int i = 1; i < 6; i++)
		dice[i] = random;
	outputbones(player,dice);
	cout << "������� ���������� �����?(y - yes)" << endl;
	int select = _getch();
	if (select == 89 || select == 121 || select == 205 || select == 237)
	{
		string retake, buf;
		int j(0),change, bufforsort[6] = { 0,0,0,0,0,0 };
		bool fail(true);
		cout << "������� ������ ������ ��� ��������:" << endl;
		while (fail)
		{
			cin >> retake;
			fail = inputcheck(retake);
		}
		for (int i = 0; i < retake.length(); i++)
		{
			buf = retake[i];
			change = atoi(buf.c_str());
			used[change] = true;
			dice[change] = random;
		}
		system("cls");
		outputbones(player, dice);
		cout << "������� ���������� �����, ������� ���� ����������?(y - yes)" << endl;
		select = _getch();
		if (select == 89 || select == 121 || select == 205 || select == 237)
		{
			cout << "������� ������ ������ ��� ��������:" << endl;
			fail = true;
			while (fail)
			{
				cin >> retake;
				fail = inputcheck(retake);
				
				//	if (fail)			// ��� �������������� ������ ��������� �� ������ ��������� ���
				//	continue;
			//	if (strstr(retake.c_str(), retake2.c_str()) != 0)
			//		fail = false;
				//else
				//{
			////		fail = true;
				//	cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
			//	}
			}
			//system("cls");
			bool bufer(true);
			while (bufer)
			{
				for (int i = 0; i < retake.length(); i++)
			{
					buf = retake[i];
					change = atoi(buf.c_str());
					if (used[change] == true)
					{
						dice[change] = random;
						bufer = false;
					}
					else
					{
						bufer = true;
						cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
						cin >> retake;
						break;
					}

				}
			}
			outputbones(player, dice);
		}
	}
	system("pause");
	system("cls"); 
}

int pointscount()
{
	int dice1[6], dice2[6];
	int score1(0), score2(0);
	turn(player1,dice1);
	turn(player2,dice2);
	outputbones(player1, dice1);
	outputbones(player2, dice2);
	system("pause");
	qsort(dice1, 6, sizeof(int), compare);
	qsort(dice2, 6, sizeof(int), compare);
	
	system("pause");
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int anew(89),res[3];
	while (anew == 89 || anew == 121 || anew == 205 || anew == 237)
	{
		menu();
		enternames();
		for (int i = 0; i < 3; i++)
		{
			res[i] = pointscount();
		}
		//������ ���� ��������
		cout << "��������� � ����?(y - yes)" << endl;
		anew = _getch();
	}
	system("cls");
	cout << "�� ��������!" << endl;
	Sleep(1300);
}