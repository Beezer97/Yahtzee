#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <windows.h>

#define random 1 + rand() % 6	// ��������� ���������� ����� �� 1 �� 6

using namespace std;

int nummove(0);		// ���������� ��� ����������� �����, ����������, ������ ��� ������������ � pointscount, � ���������� � main

HANDLE Cons = GetStdHandle(STD_OUTPUT_HANDLE);	// ����������� ����������� Cons ����� ������� ������ WinApi

void menu()		// ����
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
					while (ch != '\0')	// ������ � ����� ����� ��������� ���� �� ������ ������ ������
					{
						rules.getline(buff, 100);
						ch = buff[0];
						cout << buff << endl;
					}
				else
					cout << "���� �� ����� ���� ������." << endl;
				rules.close();
				system("pause");
				break;
			}
			case 51:
			{
				system("cls");
				cout << "���������� ����..." << endl;
				Sleep(1300);
				exit(0);
			}
		}
	}
}

string entername(string player)		// ������� ����� ������ ������
{
	static int i(0);
	cout << "������� ��� ";
	if (i == 0)		// �������� ������� ������ �� �������
	{
		cout << "�������";
		i++;
	}
	else
	{
		cout << "�������";
		i--;
	}
	cout << " ������: " << endl;
	cin >> player;
	return player;
}

int count(int dice[6])
{
	int points(1);
	//�����
	if (dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4] && dice[4] == dice[5])
	{
		points = 9;
		return points;
	}
	//������� �����
	if (dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5 && dice[5] == 6)
	{
		points = 8;
		return points;
	}
	//����� �����
	if (dice[1] == 1 && dice[2] == 2 && dice[3] == 3 && dice[4] == 4 && dice[5] == 5)
	{
		points = 7;
		return points;
	}
	//����
	if ((dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]) || (dice[2] == dice[3] && dice[3] == dice[4] && dice[4] == dice[5]))
	{
		points = 6;
		return points;
	}
	//���� ����
	if ((dice[1] == dice[2] && (dice[3] == dice[4] && dice[4] == dice[5])) || ((dice[1] == dice[2] && dice[2] == dice[3]) && dice[4] == dice[5]))
	{
		points = 5;
		return points;
	}
	//������
	if ((dice[1] == dice[2] && dice[2] == dice[3]) || (dice[3] == dice[4] && dice[4] == dice[5]) || (dice[2] == dice[3] && dice[3] == dice[4]))
	{
		points = 4;
		return points;
	}
	//��� ����
	if ((dice[1] == dice[2] && dice[3] == dice[4]) || (dice[1] == dice[2] && dice[4] == dice[5]) || (dice[2] == dice[3] && dice[5] == dice[4]))
	{
		points = 3;
		return points;
	}
	//����
	if (dice[1] == dice[2] || dice[2] == dice[3] || dice[3] == dice[4] || dice[4] == dice[5])
	{
		points = 2;
		return points;
	}
	return points;
}

void outputcomb(int points)
{
	if (points == 9)
		cout << "*****�����*****" << endl;
	if (points == 8)
		cout << "****������� �����****" << endl;
	if (points == 7)
		cout << "***����� �����***" << endl;
	if (points == 6)
		cout << "**����**" << endl;
	if (points == 5)
		cout << "*���� ����*" << endl;
	if (points == 4)
		cout << "*������*" << endl;
	if (points == 3)
		cout << "*��� ����*" << endl;
	if (points == 2)
		cout << "*����*" << endl;
	if (points == 1)
		cout << "*������*" << endl;
}

void outputbones(string player,int dice[6], int points)		// ������� ������ ������
{
	cout << "****����� ������ " << player << ":****\n\n[1] [2] [3] [4] [5]\n ";
	for (int i = 1; i < 6; i++)
		cout << dice[i] << "   ";
	outputcomb(points);
	cout << "\n" << endl;
}

int compare(const void * x1, const void * x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

bool inputcheck(string retake) // ������� �������� �����
{
	bool fail(true);
		for (int i = 0; i < retake.length(); i++) // ������ �� retake
		{
			if (retake[i] == '1' || retake[i] == '2' || retake[i] == '3' || retake[i] == '4' || retake[i] == '5')	// �������� �� �����(���������: 1 2 3 4 5)
				fail = false;
			else
			{
				fail = true;
				cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
				return fail;
			}
		}
		for (int i = 0; i < retake.length(); i++)	// ������ �� retake
		{
			for (int j = i + 1; j < retake.length(); j++)	// ������ �� �������, ���������� �� �������� � ������� �����
				if (retake[i] == retake[j])		// ��������� ���� �����, �������� �� ������������� �����(�� ���� �� ������)
				{
					fail = true;
					cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
					return fail;
				}
		}
	return fail;
}

void turn(string player, int dice[6])
{
	bool used[6] = { false,false,false,false,false,false }; 
	int sortdice[6] = { 0,0,0,0,0,0 };
	srand(time(0)); // ������������� ���������� ��������� ����� � ������� ������� time
	system("cls");
	cout << "��� ������ " << player << "..\n" << endl;
	system("pause");
	system("cls");
	for (int i = 1; i < 6; i++)
	{
		dice[i] = random;
	}
	for (int i = 0; i < 6; i++)
		sortdice[i] = dice[i];
	qsort(sortdice, 6, sizeof(int), compare);
	int points = count(sortdice);
	outputbones(player,dice,points);
	cout << "������� ���������� �����?(y - yes)\n" << endl;
	int select = _getch();
	if (select == 89 || select == 121 || select == 205 || select == 237) // ��� ���� ������� Y � ��������� 1251
	{
		string retake, buf;
		int j(0),change, bufforsort[6] = { 0,0,0,0,0,0 };
		bool fail(true);
		cout << "������� ������ ������ ��� ��������:" << endl;
		while (fail) // ���� ����� ���������� �� ��� ��� ���� inputcheck �� ������ false
		{
			cin >> retake;
			fail = inputcheck(retake);
		}
		for (int i = 0; i < retake.length(); i++) // ��������� ������
		{
			buf = retake[i];
			change = atoi(buf.c_str()); 
			used[change] = true; // �����, ����� � ��������� ��� ����� ���� ���������� ������ �� �����, ������� ���� ����������.
			dice[change] = random;
		}
		for (int i = 0; i < 6; i++)
			sortdice[i] = dice[i];
		system("cls");
		qsort(sortdice, 6, sizeof(int), compare);
		points = count(sortdice);
		outputbones(player, dice, points);
		cout << "�����, ������� �� ������ ���������� ��� ���: ";
		for (int i = 0; i < 6; i++)
			if (used[i] == true) // ����� ������, ������� ����� ����������
				cout << i << " ";
		cout << ".\n" << endl;
		cout << "������� ���������� ��� �����?(y - yes)\n" << endl;
		select = _getch();
		if (select == 89 || select == 121 || select == 205 || select == 237) // ��� ���� ������� Y � ��������� 1251
		{
			cout << "������� ������ ������ ��� ��������:" << endl;
			fail = true;
			while (fail) // ���� ����� ���������� �� ��� ��� ���� inputcheck �� ������ false
			{
				cin >> retake;
				fail = inputcheck(retake);
			}
			bool bufer(true);
			while (bufer) // ����, ������� ��������� ���� �� ������� �� �����, ������� ��� ���� ����������
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
			system("cls");
			for (int i = 0; i < 6; i++)
				sortdice[i] = dice[i];
			qsort(sortdice, 6, sizeof(int), compare);
			points = count(sortdice);
			outputbones(player, dice, points);
			system("pause");
		}
	}
	system("cls");
}

int pointscount(string player1, string player2)
{
	int points1(0), points2(0), dice1[6] = { 0,0,0,0,0,0 }, dice2[6] = { 0,0,0,0,0,0 };
	for (;;) // ���� ��� ��������� ����������� ����� �� ���� ���� � ���������� ����������
	{
		if (nummove == 0)
		{
			turn(player1, dice1);
			turn(player2, dice2);
			nummove = 1;
			break;
		}
		if (nummove == 1)
		{
			turn(player2, dice2);
			turn(player1, dice1);
			nummove = 0;
			break;
		}
	}
	int sortdice[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 6; i++)
		sortdice[i] = dice1[i];
	qsort(sortdice, 6, sizeof(int), compare); 
	points1 = count(sortdice);
	for (int i = 0; i < 6; i++)
		sortdice[i] = dice2[i];
	qsort(sortdice, 6, sizeof(int), compare);
	points2 = count(sortdice);
	outputbones(player1, dice1, points1);
	outputbones(player2, dice2, points2);
	//�������� �� �����
	if (points1 == 9 || points2 == 9)
	{
		if (points1 == points2)
		{
			if (dice1[1] == dice2[1])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[1] > dice2[1])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[1] < dice2[1])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 9 && points2 < 9)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 9 && points2 == 9)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������� �����
	if (points1 == 8 || points2 == 8)
	{
		if (points1 == points2)
		{
			cout << "�����.\n" << endl;
			return 0;
		}
		if (points1 == 8 && points2 < 8)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 8 && points2 == 8)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����� �����
	if (points1 == 7 || points2 == 7)
	{
		if (points1 == points2)
		{
			cout << "�����.\n" << endl;
			return 0;
		}
		if (points1 == 7 && points2 < 7)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 7 && points2 == 7)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����
	if (points1 == 6 || points2 == 6)
	{
		if (points1 == points2)
		{
			if (dice1[5] == dice2[5] && dice1[1] == dice2[1])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[2] == dice2[2])
			{
				if (dice1[1] > dice2[1] || dice1[5] > dice2[5])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[1] < dice2[1] || dice1[5] < dice2[5])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
			}
			if (dice1[2] > dice2[2])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[2] < dice2[2])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 6 && points2 < 6)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 6 && points2 == 6)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ���� ����
	if (points1 == 5 || points2 == 5)
	{
		if (points1 == points2)
		{
			if (dice1[2] == dice2[2] && dice1[4] == dice2[4])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[3] > dice2[3])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[3] < dice2[3])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[2] > dice2[2] || dice1[4] > dice2[4])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[2] < dice2[2] || dice1[4] < dice2[4])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 5 && points2 < 5)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 5 && points2 == 5)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������
	if (points1 == 4 || points2 == 4)
	{
		if (points1 == points2)
		{
			if (dice1[3] == dice2[3])
			{
				if (dice1[5] == dice2[5] && dice1[4] == dice2[4] && dice1[2] == dice2[2] && dice1[1] == dice2[1])
				{
					cout << "�����.\n" << endl;
					return 0;
				}
				if (dice1[5] > dice2[5] || dice1[4] > dice2[4] || dice1[2] > dice2[2] || dice1[1] > dice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[5] < dice2[5] || dice1[4] < dice2[4] || dice1[2] < dice2[2] || dice1[1] < dice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
			}
		}
		if (points1 == 4 && points2 < 4)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 4 && points2 == 4)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ��� ����
	if (points1 == 3 || points2 == 3)
	{
		if (points1 == points2)
		{
			if (dice1[4] > dice2[4])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[4] < dice2[4])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[4] == dice2[4])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[1] > dice2[1] || dice1[3] > dice2[3] || dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[1] < dice2[1] || dice1[3] < dice2[3] || dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
				}
			}
		}
		if (points1 == 3 && points2 < 3)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 3 && points2 == 3)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����
	if (points1 == 2 || points2 == 2)
	{
		if (points1 == points2)
		{
			if (dice1[1] == dice1[2])
			{
				if (dice1[1] > dice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[1] < dice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[1] == dice2[1])
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
				if (dice1[5] < dice2[5])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[5] == dice2[5])
				{
					if (dice1[4] > dice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[4] < dice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[4] == dice2[4])
					{
						if (dice1[3] > dice2[3])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[3] < dice2[3])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[3] == dice2[3])
						{
							cout << "�����.\n" << endl;
							return 0;
						}
					}
				}
			}
			if (dice1[2] == dice1[3])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[5] == dice2[5])
					{
						if (dice1[4] > dice2[4])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[4] < dice2[4])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[4] == dice2[4])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (dice1[3] == dice1[4])
			{
				if (dice1[3] > dice2[3])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[3] < dice2[3])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[3] == dice2[3])
				{
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[5] == dice2[5])
					{
						if (dice1[2] > dice2[2])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[2] < dice2[2])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[2] == dice2[2])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (dice1[4] == dice1[5])
			{
				if (dice1[4] > dice2[4])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[4] < dice2[4])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[4] == dice2[4])
				{
					if (dice1[3] > dice2[3])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[3] < dice2[3])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[3] == dice2[3])
					{
						if (dice1[2] > dice2[2])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[2] < dice2[2])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[2] == dice2[2])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
		}
		if (points1 == 2 && points2 < 2)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 < 2 && points2 == 2)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������ ����
	if (dice1[5] > dice2[5])
	{
		cout << "������� ����� " << player1 << ".\n" << endl;
		return 1;
	}
	if (dice1[5] < dice2[5])
	{
		cout << "������� ����� " << player2 << ".\n" << endl;
		return -1;
	}
	if (dice1[5] == dice2[5])
	{
		if (dice1[4] > dice2[4])
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (dice1[4] < dice2[4])
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
		if (dice1[4] == dice2[4])
		{
			if (dice1[3] > dice2[3])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[3] < dice2[3])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[3] == dice2[3])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[1] > dice2[1])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[1] < dice2[1])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[1] == dice2[1])
					{
						cout << "�����.\n" << endl;
						return 0;
					}
				}
			}
		}
	}
}
/*
int pointscount(string player1, string player2)
{
	int points1(0), points2(0), dice1[6] = { 0,0,0,0,0,0 }, dice2[6] = { 0,0,0,0,0,0 };
	for (;;) // ���� ��� ��������� ����������� ����� �� ���� ���� � ���������� ����������
	{
		if (nummove == 0)
		{
			turn(player1, dice1);
			turn(player2, dice2);
			nummove = 1;
			break;
		}
		if (nummove == 1)
		{
			turn(player2, dice2);
			turn(player1, dice1);
			nummove = 0;
			break;
		}
	}
	outputbones(player1, dice1);
	outputbones(player2, dice2);
	qsort(dice1, 6, sizeof(int), compare); // ���������� �������� ��� �������� �� ����������
	qsort(dice2, 6, sizeof(int), compare); //
	//�������� �� �����
	if (dice1[1] == dice1[2] && dice1[2] == dice1[3] && dice1[3] == dice1[4] && dice1[4] == dice1[5])
		points1 = 9;
	if (dice2[1] == dice2[2] && dice2[2] == dice2[3] && dice2[3] == dice2[4] && dice2[4] == dice2[5])
		points2 = 9;
	if (points1 == 9 || points2 == 9)
	{
		if (points1 == points2)
		{
			if (dice1[1] == dice2[1])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[1] > dice2[1])
			{
				cout << "������� ����� " << player1 << ".\n"<< endl;
				return 1;
			}
			if (dice1[1] < dice2[1])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 9 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 9)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������� �����
	if (dice1[1] == 2 && dice1[2] == 3 && dice1[3] == 4 && dice1[4] == 5 && dice1[5] == 6)
		points1 = 8;
	if (dice2[1] == 2 && dice2[2] == 3 && dice2[3] == 4 && dice2[4] == 5 && dice2[5] == 6)
		points2 = 8;
	if (points1 == 8 || points2 == 8)
	{
		if (points1 == points2)
		{
			cout << "�����.\n" << endl;
			return 0;
		}
		if (points1 == 8 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 8)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����� �����
	if (dice1[1] == 1 && dice1[2] == 2 && dice1[3] == 3 && dice1[4] == 4 && dice1[5] == 5)
		points1 = 7;
	if (dice2[1] == 1 && dice2[2] == 2 && dice2[3] == 3 && dice2[4] == 4 && dice2[5] == 5)
		points2 = 7;
	if (points1 == 7 || points2 == 7)
	{
		if (points1 == points2)
		{
			cout << "�����.\n" << endl;
			return 0;
		}
		if (points1 == 7 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 7)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����
	if ((dice1[1] == dice1[2] && dice1[2] == dice1[3] && dice1[3] == dice1[4]) || (dice1[2] == dice1[3] && dice1[3] == dice1[4] && dice1[4] == dice1[5]))
		points1 = 6;
	if ((dice2[1] == dice2[2] && dice2[2] == dice2[3] && dice2[3] == dice2[4]) || (dice2[2] == dice2[3] && dice2[3] == dice2[4] && dice2[4] == dice2[5]))
		points2 = 6;
	if (points1 == 6 || points2 == 6)
	{
		if (points1 == points2)
		{
			if (dice1[5] == dice2[5] && dice1[1] == dice2[1])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[2] == dice2[2])
			{
				if (dice1[1] > dice2[1] || dice1[5] > dice2[5])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[1] < dice2[1] || dice1[5] < dice2[5])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
			}
			if (dice1[2] > dice2[2])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[2] < dice2[2])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 6 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 6)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ���� ����
	if ((dice1[1] == dice1[2] && (dice1[3] == dice1[4] && dice1[4] == dice1[5])) || ((dice1[1] == dice1[2] && dice1[2] == dice1[3]) && dice1[4] == dice1[5]))
		points1 = 5;
	if ((dice2[1] == dice2[2] && (dice2[3] == dice2[4] && dice2[4] == dice2[5])) || ((dice2[1] == dice2[2] && dice2[2] == dice2[3]) && dice2[4] == dice2[5]))
		points2 = 5;
	if (points1 == 5 || points2 == 5)
	{
		if (points1 == points2)
		{
			if (dice1[2] == dice2[2] && dice1[4] == dice2[4])
			{
				cout << "�����.\n" << endl;
				return 0;
			}
			if (dice1[3] > dice2[3])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[3] < dice2[3])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[2] > dice2[2] || dice1[4] > dice2[4])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[2] < dice2[2] || dice1[4] < dice2[4])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
		}
		if (points1 == 5 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 5)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������
	if ((dice1[1] == dice1[2] && dice1[2] == dice1[3]) || (dice1[3] == dice1[4] && dice1[4] == dice1[5]) || (dice1[2] == dice1[3] && dice1[3]== dice1[4]))
		points1 = 4;
	if ((dice2[1] == dice2[2] && dice2[2] == dice2[3]) || (dice2[3] == dice2[4] && dice2[4] == dice2[5]) || (dice2[2] == dice2[3] && dice2[3] == dice2[4]))
		points2 = 4;
	if (points1 == 4 || points2 == 4)
	{
		if (points1 == points2)
		{
			if (dice1[3] == dice2[3])
			{
				if (dice1[5] == dice2[5] && dice1[4] == dice2[4] && dice1[2] == dice2[2] && dice1[1] == dice2[1])
				{
					cout << "�����.\n" << endl;
					return 0;
				}
				if (dice1[5] > dice2[5] || dice1[4] > dice2[4] || dice1[2] > dice2[2] || dice1[1] > dice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[5] < dice2[5] || dice1[4] < dice2[4] || dice1[2] < dice2[2] || dice1[1] < dice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
			}
		}
		if (points1 == 4 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 4)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ��� ����
	if ((dice1[1] == dice1[2] && dice1[3] == dice1[4]) || (dice1[1] == dice1[2] && dice1[4] == dice1[5]) || (dice1[2] == dice1[3] && dice1[5] == dice1[4]))
		points1 = 3;
	if ((dice2[1] == dice2[2] && dice2[3] == dice2[4]) || (dice2[1] == dice2[2] && dice2[4] == dice2[5]) || (dice2[2] == dice2[3] && dice2[5] == dice2[4]))
		points2 = 3;
	if (points1 == 3 || points2 == 3)
	{
		if (points1 == points2)
		{
			if (dice1[4] > dice2[4])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[4] < dice2[4])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[4] == dice2[4])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[1] > dice2[1] || dice1[3] > dice2[3] || dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[1] < dice2[1] || dice1[3] < dice2[3] || dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
				}
			}
		}
		if (points1 == 3 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 3)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ����
	if (dice1[1] == dice1[2] || dice1[2] == dice1[3] || dice1[3] == dice1[4] || dice1[4] == dice1[5])
		points1 = 2;
	if (dice2[1] == dice2[2] || dice2[2] == dice2[3] || dice2[3] == dice2[4] || dice2[4] == dice2[5])
		points2 = 2;
	if (points1 == 2 || points2 == 2)
	{
		if (points1 == points2)
		{
			if (dice1[1] == dice1[2])
			{
				if (dice1[1] > dice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[1] < dice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[1] == dice2[1])
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
				if (dice1[5] < dice2[5])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[5] == dice2[5])
				{
					if (dice1[4] > dice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[4] < dice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[4] == dice2[4])
					{
						if (dice1[3] > dice2[3])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[3] < dice2[3])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[3] == dice2[3])
						{
							cout << "�����.\n" << endl;
							return 0;
						}
					}
				}
			}
			if (dice1[2] == dice1[3])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[5] == dice2[5])
					{
						if (dice1[4] > dice2[4])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[4] < dice2[4])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[4] == dice2[4])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (dice1[3] == dice1[4])
			{
				if (dice1[3] > dice2[3])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[3] < dice2[3])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[3] == dice2[3])
				{
					if (dice1[5] > dice2[5])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[5] < dice2[5])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[5] == dice2[5])
					{
						if (dice1[2] > dice2[2])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[2] < dice2[2])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;																																						
							return -1;
						}
						if (dice1[2] == dice2[2])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;																																														
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (dice1[4] == dice1[5])
			{
				if (dice1[4] > dice2[4])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[4] < dice2[4])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[4] == dice2[4])
				{
					if (dice1[3] > dice2[3])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[3] < dice2[3])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[3] == dice2[3])
					{
						if (dice1[2] > dice2[2])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (dice1[2] < dice2[2])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						if (dice1[2] == dice2[2])
						{
							if (dice1[1] > dice2[1])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (dice1[1] < dice2[1])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							if (dice1[1] == dice2[1])
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
		}
		if (points1 == 2 && points2 == 0)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points1 == 0 && points2 == 2)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������ ����
	if (dice1[5] > dice2[5])
	{
		cout << "������� ����� " << player1 << ".\n" << endl;
		return 1;
	}
	if (dice1[5] < dice2[5])
	{
		cout << "������� ����� " << player2 << ".\n" << endl;
		return -1;
	}
	if (dice1[5] == dice2[5])
	{
		if (dice1[4] > dice2[4])
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (dice1[4] < dice2[4])
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
		if (dice1[4] == dice2[4])
		{
			if (dice1[3] > dice2[3])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (dice1[3] < dice2[3])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			if (dice1[3] == dice2[3])
			{
				if (dice1[2] > dice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (dice1[2] < dice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				if (dice1[2] == dice2[2])
				{
					if (dice1[1] > dice2[1])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (dice1[1] < dice2[1])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					if (dice1[1] == dice2[1])
					{
						cout << "�����.\n" << endl;
						return 0;
					}
				}
			}
		}
	}
}
*/
int systemgame() // ������� ������ ������� ����
{
	int s(0);
	cout << "\n\n�������� ������� ����:\n\n" << "1. Best of 1.\n" << "2. Best of 3.\n" << "3. Best of 5." << endl;
	do
	{
		s = _getch();
	} while (s != 49 && s != 50 && s != 51);
	switch (s)
	{
		case 49: 
		{
			s = 1;	// Best of 1
			break;
		}
		case 50:
		{
			s = 2;	// Best of 3
			break;
		}
		case 51:
		{
			s = 3;	// Best of 5
			break;
		}
	}
	return s;
}

int main()
{
	SetConsoleCP(1251); // ������� ��������� �����
	SetConsoleOutputCP(1251); // ������� ��������� ������
	SetConsoleTextAttribute(Cons, (WORD)(9 << 4 | 14)); // ������� ����� ���� ������� � ������
	string player1, player2; // ����� �������
	int j(0), sysgame(0), anew(89), res(0); // �������, ������� ����, ������� � ����, ��������� ����
	while (anew == 89 || anew == 121 || anew == 205 || anew == 237)
	{
		menu();
		player1 = entername(player1);
		player2 = entername(player2);
		sysgame = systemgame();
		int sc1(0), sc2(0); // ���������� ����� ������� � ������� ������ ��������������
		for (int i = 0; i <= j; i++)
		{
			res = pointscount(player1, player2);
			j = sysgame;
			if (res == 0)
			{
				i--;
				j++;
			}
			if (res == 1)
				sc1++;
			if (res == -1)
				sc2++;
			cout << "������� ����:\t" << sc1 << ":" << sc2 << ".\n" << endl;
			if (sc1 != sysgame && sc2 != sysgame)
				system("pause");
			if (sc1 == sysgame || sc2 == sysgame)
			{
				if (sc1 == sysgame)
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					nummove = 0;
					break;
				}
				if (sc2 == sysgame)
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					nummove = 0;
					break;
				}
			}
		}
		cout << "��������� � ����?(y - yes)" << endl;
		anew = _getch();
	}
	cout << "\n���������� ����..." << endl;
	Sleep(1300);
	return 0;
}