#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <windows.h>

#define RANDOM 1 + rand() % 6 // ��������� ���������� ����� �� 1 �� 6

using namespace std;

int nummove(0);	// ���������� ��� ����������� �����, ����������, ������ ��� ������������ � pointscount, � ���������� � main

void menu()	// ����
{
	int select(0);
	while(select != 49) // ���� �� ����� ������ 1 - ������ ����, ���� ��������� �� ������
	{
		system("cls");
		cout << "***����� �� ������(Yahtzee).***\n" << endl;
		cout << "1. ������ ����." << endl;
		cout << "2. �������." << endl;
		cout << "3. �����." << endl;
		select = _getch();
		switch (select)
		{
			case 49: // ������ ����
			{
				system("cls");
				break;
			}
			case 50: // ����� ������ � �������
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
			case 51: // ����� �� ����
			{
				system("cls");
				cout << "���������� ����..." << endl;
				Sleep(1200);
				exit(0);
			}
		}
	}
}

string entername(string player)		// ������� ����� ������ ������
{
	static int i(0);
	char symb('8');
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
	getline(cin, player);
	return player;
}

int count(int dice[5]) // ������� ������������� ����������
{
	int points(1); // ������
				   //�����
	if (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4])
	{
		points = 9;
		return points;
	}
	//������� �����
	if (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6)
	{
		points = 8;
		return points;
	}
	//����� �����
	if (dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5)
	{
		points = 7;
		return points;
	}
	//����
	if ((dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3]) || (dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]))
	{
		points = 6;
		return points;
	}
	//���� ����
	if ((dice[0] == dice[1] && (dice[2] == dice[3] && dice[3] == dice[4])) || ((dice[0] == dice[1] && dice[1] == dice[2]) && dice[3] == dice[4]))
	{
		points = 5;
		return points;
	}
	//������
	if ((dice[0] == dice[1] && dice[1] == dice[2]) || (dice[2] == dice[3] && dice[3] == dice[4]) || (dice[1] == dice[2] && dice[2] == dice[3]))
	{
		points = 4;
		return points;
	}
	//��� ����
	if ((dice[0] == dice[1] && dice[2] == dice[3]) || (dice[0] == dice[1] && dice[3] == dice[4]) || (dice[1] == dice[2] && dice[4] == dice[3]))
	{
		points = 3;
		return points;
	}
	//����
	if (dice[0] == dice[1] || dice[1] == dice[2] || dice[2] == dice[3] || dice[3] == dice[4])
	{
		points = 2;
		return points;
	}
	return points;
}

void outputcomb(int points) // ����� ����������
{
	switch (points)
	{
		case 2:
		{
			cout << "*����*" << endl;
			break;
		}
		case 3:
		{
			cout << "*��� ����*" << endl;
			break;
		}
		case 4:
		{
			cout << "*������*" << endl;
			break;
		}
		case 5:
		{
			cout << "*���� ����*" << endl;
			break;
		}
		case 1:
		{
			cout << "*������*" << endl;
			break;
		}
		case 6:
		{
			cout << "**����**" << endl;
			break;
		}
		case 7:
		{
			cout << "***����� �����***" << endl;
			break;
		}
		case 8:
		{
			cout << "****������� �����****" << endl;
			break;
		}
		case 9:
		{
			cout << "*****�����*****" << endl;
			break;
		}
	}
}

void outputbones(string player,int dice[5], int points)		// ������� ������ ������
{
	cout << "****����� ������ " << player << ":****\n\n[1] [2] [3] [4] [5]\n ";
	for (int i = 0; i < 5; i++)
		cout << dice[i] << "   ";
	outputcomb(points); // ����� ����������
	cout << "\n"<< endl;
}

int compare(const void * x1, const void * x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

bool inputcheck(string retake) // ������� �������� �����
{
	bool fail(false);
		for (int i = 0; i < retake.length(); i++) // ������ �� retake
			if (retake[i] != '1' && retake[i] != '2' && retake[i] != '3' && retake[i] != '4' && retake[i] != '5')	// �������� �� �����(���������: 1 2 3 4 5)
			{
				fail = true;
				cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
				return fail;
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

void turn(string player, int dice[5])
{
	bool used[5] = { false,false,false,false,false }; // ������, ������� ����� ��������� ������ ����������� ������, ����� �� ������ ��� �������������� ������ ���
	int sortdice[5] = { 0,0,0,0,0 }; // ������ ��� �������� �� ����������
	srand((unsigned)time(NULL)); // ������������� ���������� ��������� ����� � ������� ������� time
	system("cls");
	cout << "��� ������ " << player << "..\n" << endl;
	system("pause");
	system("cls");
	for (int i = 0; i < 5; i++)
		dice[i] = RANDOM;
	for (int i = 0; i < 5; i++) // �������� ������ ��� ����������, ���� ����� ����������� ��������� - ����� ��������� ���������������
		sortdice[i] = dice[i];
	qsort(sortdice, 5, sizeof(int), compare);
	int points = count(sortdice);
	outputbones(player,dice,points);
	cout << "������� ���������� �����?(y - yes)" << endl;
	int select = _getch();
	if (select == 89 || select == 121 || select == 205 || select == 237) // ��� ���� ������� Y � ��������� 1251
	{
		string retake, buf;
		int change(0);
		bool fail(false);
		cout << "\n������� ������ ������ ��� ��������:" << endl;
		do // ���� ����� ���������� �� ��� ��� ���� inputcheck �� ������ false
		{
			cin >> retake;
			fail = inputcheck(retake);
		} while (fail);
		for (int i = 0; i < retake.length(); i++) // ��������� ������
		{
			buf = retake[i];
			change = atoi(buf.c_str());
			change--; // ���������, ������ ��� ������� ������� ������� == ������ ����� � �.�.
			used[change] = true; // �������� ��� ����� ��� �������������
			dice[change] = RANDOM; // �������������
		}
		for (int i = 0; i < 5; i++)	// �������� ������ ��� ����������, ���� ����� ����������� ��������� - ����� ��������� ���������������
			sortdice[i] = dice[i];
		qsort(sortdice, 5, sizeof(int), compare);
		points = count(sortdice);
		system("cls");
		outputbones(player, dice, points);
		cout << "�����, ������� �� ������ ���������� ��� ���: ";
		for (int i = 0; i < 5; i++)
			if (used[i] == true) // ����� ������, ������� ����� ����������
				{
					cout << i + 1 << " ";
				}
		cout << "\n" << endl;
		cout << "������� ���������� ��� �����?(y - yes)" << endl;
		select = _getch();
		if (select == 89 || select == 121 || select == 205 || select == 237) // ��� ���� ������� Y � ��������� 1251
		{
			cout << "\n������� ������ ������ ��� ��������:" << endl;
			do // ���� ����� ���������� �� ��� ��� ���� inputcheck �� ������ false
			{
				cin >> retake;
				fail = inputcheck(retake);
			} while (fail);
			do // ����, ������� ��������� ���� �� ������� �� �����, ������� ��� ���� ����������
			{
				for (int i = 0; i < retake.length(); i++)
				{
					buf = retake[i];
					change = atoi(buf.c_str());
					change--;
					if (used[change] == true)
					{
						dice[change] = RANDOM;
						fail = false;
					}
					else
					{
						fail = true;
						cout << "�� ����� ������������ ��������, ����������, ��������� �������:" << endl;
						cin >> retake;
						break;
					}
				}
			} while (fail);
			for (int i = 0; i < 5; i++)
				sortdice[i] = dice[i];
			qsort(sortdice, 5, sizeof(int), compare);
			points = count(sortdice);
			system("cls");
			outputbones(player, dice, points);
			system("pause");
		}
	}
	system("cls");
}

int pointscount(string player1, string player2)
{
	int points1(0), points2(0), dice1[5] = { 0,0,0,0,0 }, dice2[5] = { 0,0,0,0,0 };
	for (;;) // ���� ��� ��������� ����������� ����� �� ���� ���� � ���������� ����������
	{
		if (nummove == 0) // ��� 1, ����� 2 ������
		{
			turn(player1, dice1);
			turn(player2, dice2);
			nummove = 1;
			break;
		}
		if (nummove == 1) // ��� 2, ����� 1 ������
		{
			turn(player2, dice2);
			turn(player1, dice1);
			nummove = 0;
			break;
		}
	}
	int sortdice1[5] = { 0,0,0,0,0 }, sortdice2[5] = { 0,0,0,0,0 }; // ������� ������� ��� �������� ���������� � �������
	/*
	dice1[0] = 1;
	dice1[1] = 1;
	dice1[2] = 4;
	dice1[3] = 5;
	dice1[4] = 5;
	dice2[0] = 1;
	dice2[1] = 1;
	dice2[2] = 4;
	dice2[3] = 5;
	dice2[4] = 5;
	*/
	for (int i = 0; i < 5; i++)
	{
		sortdice1[i] = dice1[i];
		sortdice2[i] = dice2[i];
	}
	qsort(sortdice1, 5, sizeof(int), compare);
	qsort(sortdice2, 5, sizeof(int), compare);
	points1 = count(sortdice1);
	points2 = count(sortdice2);
	outputbones(player1, dice1, points1); // ����� ���������� ������� ������
	outputbones(player2, dice2, points2); // ����� ���������� ������� ������
	//�������� �� �����
	if (points1 == 9 || points2 == 9)
	{
		if (points1 == points2)
		{
			if (sortdice1[0] > sortdice2[0])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[0] < sortdice2[0])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				cout << "�����.\n" << endl;
				return 0;
			}
		}
		if (points1 == 9)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������� �����
	if (points1 == 8 || points2 == 8)
	{
		
		if (points1 == 8)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points2 == 8)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			cout << "�����.\n" << endl;
			return 0;
		}
	}
	//�������� �� ����� �����
	if (points1 == 7 || points2 == 7)
	{

		if (points1 == 7)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (points2 == 7)
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			cout << "�����.\n" << endl;
			return 0;
		}
	}
	//�������� �� ����
	if (points1 == 6 || points2 == 6)
	{
		if (points1 == points2)
		{
			if (sortdice1[1] > sortdice2[1])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[1] < sortdice2[1])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[0] > sortdice2[0] || sortdice1[4] > sortdice2[4])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[0] < sortdice2[0] || sortdice1[4] < sortdice2[4])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "�����.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 6)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
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
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1] || sortdice1[3] > sortdice2[3])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1] || sortdice1[3] < sortdice2[3])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "�����.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 5)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
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
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[4] > sortdice2[4] || sortdice1[3] > sortdice2[3] || sortdice1[1] > sortdice2[1] || sortdice1[0] > sortdice2[0])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[4] < sortdice2[4] || sortdice1[3] < sortdice2[3] || sortdice1[1] < sortdice2[1] || sortdice1[0] < sortdice2[0])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "�����.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 4)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
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
			if (sortdice1[3] > sortdice2[3])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[3] < sortdice2[3])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[0] > sortdice2[0] || sortdice1[2] > sortdice2[2] || sortdice1[4] > sortdice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[0] < sortdice2[0] || sortdice1[2] < sortdice2[2] || sortdice1[4] < sortdice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						cout << "�����.\n" << endl;
						return 0;
					}
				}
			}
		}
		if (points1 == 3)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
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
			if (sortdice1[0] == sortdice1[1])
			{
				if (sortdice1[0] > sortdice2[0])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[0] < sortdice2[0])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[3] > sortdice2[3])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[3] < sortdice2[3])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[2] > sortdice2[2])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[2] < sortdice2[2])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (sortdice1[1] == sortdice1[2])
			{
				if (sortdice1[1] > sortdice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[3] > sortdice2[3])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[3] < sortdice2[3])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (sortdice1[2] == sortdice1[3])
			{
				if (sortdice1[2] > sortdice2[2])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[2] < sortdice2[2])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[1] > sortdice2[1])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[1] < sortdice2[1])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
			if (sortdice1[3] == sortdice1[4])
			{
				if (sortdice1[3] > sortdice2[3])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[3] < sortdice2[3])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[2] > sortdice2[2])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[2] < sortdice2[2])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[1] > sortdice2[1])
						{
							cout << "������� ����� " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[1] < sortdice2[1])
						{
							cout << "������� ����� " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "������� ����� " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "������� ����� " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "�����.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
		}
		if (points1 == 2)
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//�������� �� ������ ����
	if (sortdice1[4] > sortdice2[4])
	{
		cout << "������� ����� " << player1 << ".\n" << endl;
		return 1;
	}
	if (sortdice1[4] < sortdice2[4])
	{
		cout << "������� ����� " << player2 << ".\n" << endl;
		return -1;
	}
	else
	{
		if (sortdice1[3] > sortdice2[3])
		{
			cout << "������� ����� " << player1 << ".\n" << endl;
			return 1;
		}
		if (sortdice1[3] < sortdice2[3])
		{
			cout << "������� ����� " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "������� ����� " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "������� ����� " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1])
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[0] > sortdice2[0])
					{
						cout << "������� ����� " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[0] < sortdice2[0])
					{
						cout << "������� ����� " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						cout << "�����.\n" << endl;
						return 0;
					}
				}
			}
		}
	}
	exit(-1);
}

int systemgame() // ������� ������ ������� ����
{
	int s(0);
	cout << "�������� ������� ����:\n\n" << "1. Best of 1.\n" << "2. Best of 3.\n" << "3. Best of 5." << endl;
	do
	{
		s = _getch();
	} while (s != 49 && s != 50 && s != 51);
	switch (s)
	{
		case 49: 
		{
			s = 1;	// Best of 1(�� 1-�� ������)
			break;
		}
		case 50:
		{
			s = 2;	// Best of 3(�� 2-� �����)
			break;
		}
		case 51:
		{
			s = 3;	// Best of 5(�� 3-� �����)
			break;
		}
	}
	return s;
}

int main()
{
	system("color F0");
	SetConsoleCP(1251); // ������� ��������� �����
	SetConsoleOutputCP(1251); // ������� ��������� ������
	string player1, player2; // ����� �������
	int anew(0), sysgame(0), res(0), sc1(0), sc2(0);
	do // �������� ���� ������������ �� ��������� �� �������� � ����
	{
		menu(); // ����
		do
		{
			player1 = entername(player1); // ���� ����� ������ 1
			player2 = entername(player2); // ���� ����� ������ 2
			if (player1 == player2)
				cout << "\n����� ������� �� ����� ���� ������������, ���������� ��� ���:\n" << endl;
		} while (player1 == player2);
		system("cls");
		sysgame = systemgame(); // ����� ������� ����
		for (;;)
		{
			res = pointscount(player1, player2);
			if (res == 0) // ���� ����� - ��� ������ ������ ����� ������
			{
				system("pause");
				continue;
			}
			if (res == 1) // ���������� 1 ���� ������� ������ ���� �� �������
				sc1++;
			else // ���������� 1 ���� ������� ������ ���� �� �������
				sc2++;
			cout << "������� ����:\t" << sc1 << ":" << sc2 << ".\n" << endl;
			if (sc1 != sysgame && sc2 != sysgame) // ������ ����� ���� ���� �� ���������(�� ���� �� ������� �� ������ ����������� ���������� �����)
				system("pause");
			else
			{
				if (sc1 == sysgame)
				{
					cout << "������� ����� " << player1 << ".\n" << endl;
					nummove = 0;
					break;
				}
				else
				{
					cout << "������� ����� " << player2 << ".\n" << endl;
					nummove = 0;
					break;
				}
			}
		}
		cout << "��������� � ����?(y - yes)" << endl;
		anew = _getch();
	} while (anew == 89 || anew == 121 || anew == 205 || anew == 237);
	cout << "\n���������� ����..." << endl;
	Sleep(1200);
	return 0;
}