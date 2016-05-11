#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <windows.h>

#define RANDOM 1 + rand() % 6 // Генерация случайного числа от 1 до 6

using namespace std;

int nummove(0);	// Переменная для очередности ходов, глобальная, потому что используется в pointscount, а обнуляется в main

void menu()	// Меню
{
	int select(0);
	while(select != 49) // Пока не будет нажата 1 - начать игру, меню останется на экране
	{
		system("cls");
		cout << "***Покер на костях(Yahtzee).***\n" << endl;
		cout << "1. Начать игру." << endl;
		cout << "2. Правила." << endl;
		cout << "3. Выход." << endl;
		select = _getch();
		switch (select)
		{
			case 49: // Начало игры
			{
				system("cls");
				break;
			}
			case 50: // Вывод правил в консоль
			{
				ifstream rules("rules.txt");
				char ch({ ' ' }),buff[100];
				system("cls");
				if (rules.is_open())
					while (ch != '\0')	// Чтение и вывод файла построчно пока не нйдена пустая строка
					{
						rules.getline(buff, 100);
						ch = buff[0];
						cout << buff << endl;
					}
				else
					cout << "Файл не может быть открыт." << endl;
				rules.close();
				system("pause");
				break;
			}
			case 51: // Выход из игры
			{
				system("cls");
				cout << "Завершение игры..." << endl;
				Sleep(1200);
				exit(0);
			}
		}
	}
}

string entername(string player)		// Функция ввода имеени игрока
{
	static int i(0);
	char symb('8');
	cout << "Введите имя ";
	if (i == 0)		// Отличает первого игрока от второго
	{
		cout << "первого";
		i++;
	}
	else
	{
		cout << "второго";
		i--;
	}
	cout << " игрока: " << endl;
	getline(cin, player);
	return player;
}

int count(int dice[5]) // Функция распознавания комбинаций
{
	int points(1); // Ничего
				   //Покер
	if (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4])
	{
		points = 9;
		return points;
	}
	//Большой стрит
	if (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6)
	{
		points = 8;
		return points;
	}
	//Малый стрит
	if (dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5)
	{
		points = 7;
		return points;
	}
	//Каре
	if ((dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3]) || (dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]))
	{
		points = 6;
		return points;
	}
	//Фулл хаус
	if ((dice[0] == dice[1] && (dice[2] == dice[3] && dice[3] == dice[4])) || ((dice[0] == dice[1] && dice[1] == dice[2]) && dice[3] == dice[4]))
	{
		points = 5;
		return points;
	}
	//Тройка
	if ((dice[0] == dice[1] && dice[1] == dice[2]) || (dice[2] == dice[3] && dice[3] == dice[4]) || (dice[1] == dice[2] && dice[2] == dice[3]))
	{
		points = 4;
		return points;
	}
	//Две пары
	if ((dice[0] == dice[1] && dice[2] == dice[3]) || (dice[0] == dice[1] && dice[3] == dice[4]) || (dice[1] == dice[2] && dice[4] == dice[3]))
	{
		points = 3;
		return points;
	}
	//Пара
	if (dice[0] == dice[1] || dice[1] == dice[2] || dice[2] == dice[3] || dice[3] == dice[4])
	{
		points = 2;
		return points;
	}
	return points;
}

void outputcomb(int points) // Вывод комбинаций
{
	switch (points)
	{
		case 2:
		{
			cout << "*Пара*" << endl;
			break;
		}
		case 3:
		{
			cout << "*Две пары*" << endl;
			break;
		}
		case 4:
		{
			cout << "*Тройка*" << endl;
			break;
		}
		case 5:
		{
			cout << "*Фулл хаус*" << endl;
			break;
		}
		case 1:
		{
			cout << "*Ничего*" << endl;
			break;
		}
		case 6:
		{
			cout << "**Каре**" << endl;
			break;
		}
		case 7:
		{
			cout << "***Малый стрит***" << endl;
			break;
		}
		case 8:
		{
			cout << "****Большой стрит****" << endl;
			break;
		}
		case 9:
		{
			cout << "*****Покер*****" << endl;
			break;
		}
	}
}

void outputbones(string player,int dice[5], int points)		// Функция вывода костей
{
	cout << "****Кости игрока " << player << ":****\n\n[1] [2] [3] [4] [5]\n ";
	for (int i = 0; i < 5; i++)
		cout << dice[i] << "   ";
	outputcomb(points); // Вывод комбинации
	cout << "\n"<< endl;
}

int compare(const void * x1, const void * x2)   // Функция сравнения элементов массива
{
	return (*(int*)x1 - *(int*)x2);              // Если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

bool inputcheck(string retake) // Функция проверки ввода
{
	bool fail(false);
		for (int i = 0; i < retake.length(); i++) // Пробег по retake
			if (retake[i] != '1' && retake[i] != '2' && retake[i] != '3' && retake[i] != '4' && retake[i] != '5')	// Проверка на цифры(возможные: 1 2 3 4 5)
			{
				fail = true;
				cout << "Вы ввели недопустимое значение, пожалуйста, повторите попытку:" << endl;
				return fail;
			}
		for (int i = 0; i < retake.length(); i++)	// Пробег по retake
		{
			for (int j = i + 1; j < retake.length(); j++)	// Пробег по символу, следующему за символом в прошлом цикле
				if (retake[i] == retake[j])		// Сравнение двух чисел, проверка на повторяющиеся числа(их быть не должно)
				{
					fail = true;
					cout << "Вы ввели недопустимое значение, пожалуйста, повторите попытку:" << endl;
					return fail;
				}
		}
	return fail;
}

void turn(string player, int dice[5])
{
	bool used[5] = { false,false,false,false,false }; // Массив, который будет содержать данные перекинутых костей, чтобы во второй раз перекидывались именно они
	int sortdice[5] = { 0,0,0,0,0 }; // Массив для проверки на комбинацию
	srand((unsigned)time(NULL)); // Инициализация генератора случайных чисел с помощью функции time
	system("cls");
	cout << "Ход игрока " << player << "..\n" << endl;
	system("pause");
	system("cls");
	for (int i = 0; i < 5; i++)
		dice[i] = RANDOM;
	for (int i = 0; i < 5; i++) // Копируем массив для сортировки, если будет сортировать начальный - будет выводится отсортированный
		sortdice[i] = dice[i];
	qsort(sortdice, 5, sizeof(int), compare);
	int points = count(sortdice);
	outputbones(player,dice,points);
	cout << "Желаете перекинуть кости?(y - yes)" << endl;
	int select = _getch();
	if (select == 89 || select == 121 || select == 205 || select == 237) // Все коды клавиши Y в кодировке 1251
	{
		string retake, buf;
		int change(0);
		bool fail(false);
		cout << "\nВведите номера костей без пробелов:" << endl;
		do // Цикл будет повторятся до тех пор пока inputcheck не вернет false
		{
			cin >> retake;
			fail = inputcheck(retake);
		} while (fail);
		for (int i = 0; i < retake.length(); i++) // Перекидка костей
		{
			buf = retake[i];
			change = atoi(buf.c_str());
			change--; // Уменьшаем, потому что нулевой элемент массива == первая кость и т.д.
			used[change] = true; // Помечаем эту кость как переброшенную
			dice[change] = RANDOM; // Перебрасываем
		}
		for (int i = 0; i < 5; i++)	// Копируем массив для сортировки, если будет сортировать начальный - будет выводится отсортированный
			sortdice[i] = dice[i];
		qsort(sortdice, 5, sizeof(int), compare);
		points = count(sortdice);
		system("cls");
		outputbones(player, dice, points);
		cout << "Кости, которые вы можете перекинуть еще раз: ";
		for (int i = 0; i < 5; i++)
			if (used[i] == true) // Вывод костей, которые можно перекинуть
				{
					cout << i + 1 << " ";
				}
		cout << "\n" << endl;
		cout << "Желаете перекинуть эти кости?(y - yes)" << endl;
		select = _getch();
		if (select == 89 || select == 121 || select == 205 || select == 237) // Все коды клавиши Y в кодировке 1251
		{
			cout << "\nВведите номера костей без пробелов:" << endl;
			do // Цикл будет повторятся до тех пор пока inputcheck не вернет false
			{
				cin >> retake;
				fail = inputcheck(retake);
			} while (fail);
			do // Цикл, который проверяет были ли введены те кости, которые уже были перекинуты
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
						cout << "Вы ввели недопустимое значение, пожалуйста, повторите попытку:" << endl;
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
	for (;;) // Цикл для изменения очередности ходов по ходу игры с глобальной переменной
	{
		if (nummove == 0) // Ход 1, затем 2 игрока
		{
			turn(player1, dice1);
			turn(player2, dice2);
			nummove = 1;
			break;
		}
		if (nummove == 1) // Ход 2, затем 1 игрока
		{
			turn(player2, dice2);
			turn(player1, dice1);
			nummove = 0;
			break;
		}
	}
	int sortdice1[5] = { 0,0,0,0,0 }, sortdice2[5] = { 0,0,0,0,0 }; // Создаем массивы для проверки комбинации у игроков
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
	outputbones(player1, dice1, points1); // Вывод результата первого игрока
	outputbones(player2, dice2, points2); // Вывод результата второго игрока
	//Проверка на покер
	if (points1 == 9 || points2 == 9)
	{
		if (points1 == points2)
		{
			if (sortdice1[0] > sortdice2[0])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[0] < sortdice2[0])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				cout << "Ничья.\n" << endl;
				return 0;
			}
		}
		if (points1 == 9)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на большой стрит
	if (points1 == 8 || points2 == 8)
	{
		
		if (points1 == 8)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		if (points2 == 8)
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			cout << "Ничья.\n" << endl;
			return 0;
		}
	}
	//Проверка на малый стрит
	if (points1 == 7 || points2 == 7)
	{

		if (points1 == 7)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		if (points2 == 7)
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			cout << "Ничья.\n" << endl;
			return 0;
		}
	}
	//Проверка на каре
	if (points1 == 6 || points2 == 6)
	{
		if (points1 == points2)
		{
			if (sortdice1[1] > sortdice2[1])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[1] < sortdice2[1])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[0] > sortdice2[0] || sortdice1[4] > sortdice2[4])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[0] < sortdice2[0] || sortdice1[4] < sortdice2[4])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "Ничья.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 6)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на фулл хаус
	if (points1 == 5 || points2 == 5)
	{
		if (points1 == points2)
		{
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1] || sortdice1[3] > sortdice2[3])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1] || sortdice1[3] < sortdice2[3])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "Ничья.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 5)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на тройку
	if (points1 == 4 || points2 == 4)
	{
		if (points1 == points2)
		{
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[4] > sortdice2[4] || sortdice1[3] > sortdice2[3] || sortdice1[1] > sortdice2[1] || sortdice1[0] > sortdice2[0])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[4] < sortdice2[4] || sortdice1[3] < sortdice2[3] || sortdice1[1] < sortdice2[1] || sortdice1[0] < sortdice2[0])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					cout << "Ничья.\n" << endl;
					return 0;
				}
			}
		}
		if (points1 == 4)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на две пары
	if (points1 == 3 || points2 == 3)
	{
		if (points1 == points2)
		{
			if (sortdice1[3] > sortdice2[3])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[3] < sortdice2[3])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[0] > sortdice2[0] || sortdice1[2] > sortdice2[2] || sortdice1[4] > sortdice2[4])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[0] < sortdice2[0] || sortdice1[2] < sortdice2[2] || sortdice1[4] < sortdice2[4])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						cout << "Ничья.\n" << endl;
						return 0;
					}
				}
			}
		}
		if (points1 == 3)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на пару
	if (points1 == 2 || points2 == 2)
	{
		if (points1 == points2)
		{
			if (sortdice1[0] == sortdice1[1])
			{
				if (sortdice1[0] > sortdice2[0])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[0] < sortdice2[0])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[3] > sortdice2[3])
						{
							cout << "Выиграл игрок " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[3] < sortdice2[3])
						{
							cout << "Выиграл игрок " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[2] > sortdice2[2])
							{
								cout << "Выиграл игрок " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[2] < sortdice2[2])
							{
								cout << "Выиграл игрок " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "Ничья.\n" << endl;
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
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[3] > sortdice2[3])
						{
							cout << "Выиграл игрок " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[3] < sortdice2[3])
						{
							cout << "Выиграл игрок " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "Выиграл игрок " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "Выиграл игрок " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "Ничья.\n" << endl;
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
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[2] < sortdice2[2])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[4] > sortdice2[4])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[4] < sortdice2[4])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[1] > sortdice2[1])
						{
							cout << "Выиграл игрок " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[1] < sortdice2[1])
						{
							cout << "Выиграл игрок " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "Выиграл игрок " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "Выиграл игрок " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "Ничья.\n" << endl;
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
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[3] < sortdice2[3])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[2] > sortdice2[2])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[2] < sortdice2[2])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						if (sortdice1[1] > sortdice2[1])
						{
							cout << "Выиграл игрок " << player1 << ".\n" << endl;
							return 1;
						}
						if (sortdice1[1] < sortdice2[1])
						{
							cout << "Выиграл игрок " << player2 << ".\n" << endl;
							return -1;
						}
						else
						{
							if (sortdice1[0] > sortdice2[0])
							{
								cout << "Выиграл игрок " << player1 << ".\n" << endl;
								return 1;
							}
							if (sortdice1[0] < sortdice2[0])
							{
								cout << "Выиграл игрок " << player2 << ".\n" << endl;
								return -1;
							}
							else
							{
								cout << "Ничья.\n" << endl;
								return 0;
							}
						}
					}
				}
			}
		}
		if (points1 == 2)
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		else
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
	}
	//Проверка на высшее очко
	if (sortdice1[4] > sortdice2[4])
	{
		cout << "Выиграл игрок " << player1 << ".\n" << endl;
		return 1;
	}
	if (sortdice1[4] < sortdice2[4])
	{
		cout << "Выиграл игрок " << player2 << ".\n" << endl;
		return -1;
	}
	else
	{
		if (sortdice1[3] > sortdice2[3])
		{
			cout << "Выиграл игрок " << player1 << ".\n" << endl;
			return 1;
		}
		if (sortdice1[3] < sortdice2[3])
		{
			cout << "Выиграл игрок " << player2 << ".\n" << endl;
			return -1;
		}
		else
		{
			if (sortdice1[2] > sortdice2[2])
			{
				cout << "Выиграл игрок " << player1 << ".\n" << endl;
				return 1;
			}
			if (sortdice1[2] < sortdice2[2])
			{
				cout << "Выиграл игрок " << player2 << ".\n" << endl;
				return -1;
			}
			else
			{
				if (sortdice1[1] > sortdice2[1])
				{
					cout << "Выиграл игрок " << player1 << ".\n" << endl;
					return 1;
				}
				if (sortdice1[1] < sortdice2[1])
				{
					cout << "Выиграл игрок " << player2 << ".\n" << endl;
					return -1;
				}
				else
				{
					if (sortdice1[0] > sortdice2[0])
					{
						cout << "Выиграл игрок " << player1 << ".\n" << endl;
						return 1;
					}
					if (sortdice1[0] < sortdice2[0])
					{
						cout << "Выиграл игрок " << player2 << ".\n" << endl;
						return -1;
					}
					else
					{
						cout << "Ничья.\n" << endl;
						return 0;
					}
				}
			}
		}
	}
	exit(-1);
}

int systemgame() // Функция выбора системы игры
{
	int s(0);
	cout << "Выберите систему игры:\n\n" << "1. Best of 1.\n" << "2. Best of 3.\n" << "3. Best of 5." << endl;
	do
	{
		s = _getch();
	} while (s != 49 && s != 50 && s != 51);
	switch (s)
	{
		case 49: 
		{
			s = 1;	// Best of 1(до 1-ой победы)
			break;
		}
		case 50:
		{
			s = 2;	// Best of 3(до 2-х побед)
			break;
		}
		case 51:
		{
			s = 3;	// Best of 5(до 3-х побед)
			break;
		}
	}
	return s;
}

int main()
{
	system("color F0");
	SetConsoleCP(1251); // Задание кодировки ввода
	SetConsoleOutputCP(1251); // Задание кодировки вывода
	string player1, player2; // Имена игроков
	int anew(0), sysgame(0), res(0), sc1(0), sc2(0);
	do // Работает пока пользователь не откажется от возврата в меню
	{
		menu(); // Меню
		do
		{
			player1 = entername(player1); // Ввод имени игрока 1
			player2 = entername(player2); // Ввод имени игрока 2
			if (player1 == player2)
				cout << "\nИмена игроков не могут быть одиннаковыми, попробуйте еще раз:\n" << endl;
		} while (player1 == player2);
		system("cls");
		sysgame = systemgame(); // Выбор системы игры
		for (;;)
		{
			res = pointscount(player1, player2);
			if (res == 0) // Если ничья - оба игрока кидают кости заново
			{
				system("pause");
				continue;
			}
			if (res == 1) // Присвоение 1 очка первому игроку если он выиграл
				sc1++;
			else // Присвоение 1 очка второму игроку если он выиграл
				sc2++;
			cout << "Текущий счёт:\t" << sc1 << ":" << sc2 << ".\n" << endl;
			if (sc1 != sysgame && sc2 != sysgame) // Делает паузу если игра не завершена(ни один из игроков не набрал необходимое количество побед)
				system("pause");
			else
			{
				if (sc1 == sysgame)
				{
					cout << "Победил игрок " << player1 << ".\n" << endl;
					nummove = 0;
					break;
				}
				else
				{
					cout << "Победил игрок " << player2 << ".\n" << endl;
					nummove = 0;
					break;
				}
			}
		}
		cout << "Вернуться в меню?(y - yes)" << endl;
		anew = _getch();
	} while (anew == 89 || anew == 121 || anew == 205 || anew == 237);
	cout << "\nЗавершение игры..." << endl;
	Sleep(1200);
	return 0;
}