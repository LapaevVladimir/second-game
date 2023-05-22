#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <stdio.h>

using namespace std;

int X = 110, Y = 24;
int sposX = 1, sposY = 5;
int bposX, bposY;
int s2posX = 2, s2posY = 24;
int posX = sposX, posY = sposY;
char symb1 = 222, symb2 = 223, symb3 = 42;
int direction = 1;
bool complete = false;
int coin = 0;
int number_levels = 2;
int level1_coins[3][3] = { {1, 80, 5}, {1, 70, 10}, {1, 20, 20} };
int level2_coins[3][3] = { {1, 14, 22}, {1, 36, 4}, {1, 93, 18} };
int color = 14;
int menu_choice;
int k = 0;
int temp_ch;
int temp_direction = 1;

int button();
void character_left(int);
void character_right(int);
void move(int);
void right_left();
void coins();
void level1();
void level2();

//получение элемента по координатам
char get_char_at_xy(int x, int y)
{
	CHAR_INFO ci;
	COORD xy = { 0, 0 };
	COORD a = { 1, 1 };
	SMALL_RECT rect = { x, y, x, y };
	ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, a, xy, &rect);
	return ci.Char.AsciiChar;
}

//мен€ю цвет
void Setcolor(int text, int backG = 0)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, (WORD)((backG << 4) | text));
}

//перемащаюсь по координтам
void SetPos(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//рамка игры
void ram()
{
	Setcolor(15, 15);
	for (int i = 0; i < Y; i++)
	{
		SetPos(X, i);
		cout << 1;
	}

	for (int i = 0; i < Y; i++)
	{
		SetPos(0, i);
		cout << 1;
	}

	SetPos(0, 0);
	for (int i = 0; i <= X; i++)
		cout << 1;
	SetPos(0, Y);
	for (int i = 0; i <= X; i++)
		cout << 1;
	Setcolor(15, 0);
}

//вывод персонажа если он смотрит вправо
void character_right(int bckg = 0)
{
	Setcolor(color, bckg);
	char leg = 211;
	char body = 219;
	char face = 205;
	char eye = 253;

	SetPos(posX, posY - 1);
	cout << leg << leg;
	SetPos(posX, posY - 2);
	cout << body << body;
	SetPos(posX, posY - 3);
	cout << body;
	Setcolor(0, 15);
	cout << eye;
	Setcolor(color, bckg);
	cout << face;
	SetPos(0, 0);
}

//вывод персонажа если он смотрит влево
void character_left(int bckg = 0)
{
	Setcolor(color, bckg);
	char leg = 189;
	char body = 219;
	char face = 205;
	char eye = 253;

	SetPos(posX + 1, posY - 1);
	cout << leg << leg;
	SetPos(posX + 1, posY - 2);
	cout << body << body;
	SetPos(posX, posY - 3);
	cout << face;
	Setcolor(0, 15);
	cout << eye;
	Setcolor(color, 0);
	cout << body;
	SetPos(0, 0);
}

//нажатие клавиши дл€ передвижени€ персонажа
int button()
{
	char ch;
	int code;
	ch = _getch();
	code = static_cast<int>(ch);
	if (code == 27) // если клавиша esc
		return 2;
	if (code == 77)
		return 3;
	if (code == 75)
		return 4;
	if (code == 72)
		return 5;
	if (code == 80)
		return 6;
    if(code == 32)
        return 7;

	return 1;
}

//направление персоанажа вправо/влево дл€ передвижени€ вверх/вниз
void right_left()
{
	if (direction) character_right(0);
	else character_left(0);
}

//удал€ю персонажа(дл€ перемещени€)
void clear()
{
	SetPos(posX, posY - 1);
	cout << "   ";
	SetPos(posX, posY - 2);
	cout << "   ";
	SetPos(posX, posY - 3);
	cout << "   ";
}

//провер€ю если персонаж собрал монетку
void check_coins_level1(int x)
{
	switch (x)
	{
		//вправо
		case 1:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (posX + 3 == level1_coins[i][1] && posY - 1 - j == level1_coins[i][2]) level1_coins[i][0] = 0;
				}
			}
			break;
		//влево
		case 2:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (posX - 1 == level1_coins[i][1] && posY - 1 - j == level1_coins[i][2]) level1_coins[i][0] = 0;
				}
			}
			break;
		//вверх
		case 3:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (posX + j == level1_coins[i][1] && posY - 4 == level1_coins[i][2]) level1_coins[i][0] = 0;
				}
			}
			break;
		//вниз
		case 4:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (posX + j == level1_coins[i][1] && posY == level1_coins[i][2]) level1_coins[i][0] = 0;
				}
			}
			break;

	}
}

void check_coins_level2(int x)
{
	switch (x)
	{
		//вправо
	case 1:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (posX + 3 == level2_coins[i][1] && posY - 1 - j == level2_coins[i][2]) level2_coins[i][0] = 0;
			}
		}
		break;
		//влево
	case 2:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (posX - 1 == level2_coins[i][1] && posY - 1 - j == level2_coins[i][2]) level2_coins[i][0] = 0;
			}
		}
		break;
		//вверх
	case 3:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (posX + j == level2_coins[i][1] && posY - 4 == level2_coins[i][2]) level2_coins[i][0] = 0;
			}
		}
		break;
		//вниз
	case 4:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (posX + j == level2_coins[i][1] && posY == level2_coins[i][2]) level2_coins[i][0] = 0;
			}
		}
		break;

	}
}

//провер€ю какой символ перед персонажем дл€ хода
int check(char a, char b, char c, int x)
{
	if (a == '*' || b == '*' || c == '*') return 1;
	else if (a == '0' || b == '0' || c == '0')
	{
		if(menu_choice == 1) check_coins_level1(x);
		else if (menu_choice == 2) check_coins_level2(x);
		coin++;
		coins();
		if (coin == 3)
		{
			if (menu_choice == 1) level1();
			else if (menu_choice == 2) level2();
		}
	}
	else if (a == '+' || b == '+' || c == '+')
	{
		complete = true;
		return 1;
	}
	return 0;
}

//ход персонажа
void move(int ch)
{
	//char a = get_char_at_xy();
	//if (ch != 1 && ch != 2) clear();
	if (ch == 3)
	{
		char a = get_char_at_xy(posX + 3, posY - 1);
		char b = get_char_at_xy(posX + 3, posY - 2);
		char c = get_char_at_xy(posX + 3, posY - 3);
		int check_s = check(a, b, c, 1);

		if(check_s == 1) return ;

		clear();
		posX++;
		//posX += 2;
		if (posX + 3 > X) posX = 1;
		character_right(0);
		direction = 1;
	}
	else if (ch == 4)
	{
		char a = get_char_at_xy(posX - 1, posY - 1);
		char b = get_char_at_xy(posX - 1, posY - 2);
		char c = get_char_at_xy(posX - 1, posY - 3);
		int check_s = check(a, b, c, 2);

		if (check_s == 1) return;

		clear();
		posX--;
		//posX -= 2;
		if (posX <= 0) posX = X - 3;
		character_left(0);
		direction = 0;
	}
	else if (ch == 5)
	{
		char a = get_char_at_xy(posX, posY - 4);
		char b = get_char_at_xy(posX + 1, posY - 4);
		char c = get_char_at_xy(posX + 2, posY - 4);
		int check_s = check(a, b, c, 3);

		if (check_s == 1) return;

		clear();
		posY--;
		if (posY - 3 <= 0) posY = Y;
		right_left();
	}
	else if (ch == 6)
	{
		char a = get_char_at_xy(posX, posY);
		char b = get_char_at_xy(posX + 1, posY);
		char c = get_char_at_xy(posX + 2, posY);
		int check_s = check(a, b, c, 4);

		if (check_s == 1) return;

		clear();
		posY++;
		if (posY - 1 == Y) posY = 4;
		right_left();
	}
}

//рисует 1 уровень в консоли
void level1()
{
	Setcolor(13, 13);
	//¬ерхн€€ полоска
	SetPos(0, 8);
	for (int i = 0; i <= 80; i++)
		cout << symb3;
	//права€ полоска
	for (int i = 0; i < 7; i++)
	{
		SetPos(80, i + 9);
		cout << symb3;
	}
	//нижн€€ полоска
	SetPos(0, 16);
	for (int i = 0; i <= 80; i++)
		cout << symb3;

	//Setcolor(15, 0);

	// ќграничени€ портала
	Setcolor(15, 15);
	//верхн€€ сторона
	//SetPos(0, 0);
	//for(int i = 0; i < X; i++)
	//cout << "*";

	//—тенка
	SetPos(X, 8);
	cout << "*";

	SetPos(X, 16);
	cout << "*";

	//¬ыход
	if (coin == 3)
	{
		Setcolor(10, 10);
		for (int i = 0; i < 7; i++)
		{
			SetPos(0, i + 17);
			cout << '+';
		}
	}
	else
	{
		Setcolor(15, 15);
		for (int i = 0; i < 7; i++)
		{
			SetPos(0, i + 17);
			cout << '1';
		}
	}


	// монетки
	Setcolor(6, 6);

	for (int i = 0; i < 3; i++)
	{
		if (level1_coins[i][0] == 1)
		{
			SetPos(level1_coins[i][1], level1_coins[i][2]);
			cout << 0;
		}
	}

	//номер уровн€
	Setcolor(4, 4);

	for (int i = 0; i < 5; i++)
	{
		SetPos(71, 25 + i);
		cout << " ";
	}

	Setcolor(15, 0);
}

//выход из уровн€ в меню
bool exit_menu()
{
	Setcolor(0, 7);
	SetPos(50, 12);
	cout << setw(12) << " ";
	SetPos(50, 13);
	cout << "    Exit    ";
	SetPos(50, 14);
	cout << setw(12) << " ";
	SetPos(50, 15);
	cout << "  YES   NO  ";
	SetPos(50, 16);
	cout << setw(12) << " ";
	Setcolor(15, 0);

	char ch = 75;
	bool k = false;
	do
	{
		if (ch == 75 || ch == 77)
		{
			if (k) k = false;
			else k = true;
		}

		if (k)
		{
			SetPos(52, 15);
			Setcolor(15, 0);
			cout << "YES";
			SetPos(58, 15);
			Setcolor(0, 7);
			cout << "NO";

		}
		else
		{
			SetPos(58, 15);
			Setcolor(15, 0);
			cout << "NO";
			SetPos(52, 15);
			Setcolor(0, 7);
			cout << "YES";
		}
		SetPos(0, 0);
		ch = _getch();
	} while (ch != 13);
	Setcolor(15, 0);

	for (int i = 0; i < 5; i++)
	{
		SetPos(50, 12 + i);
		cout << setw(12) << " ";
	}

	return k;
}

//¬ыыодит количество монеток
void coins()
{
	Setcolor(6, 6);
	if (coin >= 1)
	{
		for (int i = 0; i < 3; i++)
		{
			SetPos(21 + (coin - 1) * 4, 26 + i);
			cout << "   ";
		}
	}
	Setcolor(15, 0);
}

//выводит информацию о том что уровень пройден
void complete_menu()
{
	Setcolor(0, 7);
	SetPos(50, 12);
	cout << setw(14) << " ";
	SetPos(50, 13);
	cout << "  Completed!  ";
	SetPos(50, 14);
	cout << setw(14) << " ";

	int ch = 13;
	do
	{
		ch = _getch();
	} while (ch != 13);
}

//заставка
void logo()
{
	Setcolor(0, 15);
	int k = 0;
	int a = 29, b = 119;
	int c = 15;
	double time = 0.9;
	while (c)
	{
		SetPos(k, k);
		for (int i = 0; i <= b - k; i++)
		{
			cout << " ";
			Sleep(time);
		}
		for (int i = 0; i <= a - k; i++)
		{
			SetPos(b - k, k + i);
			cout << " ";
			Sleep(time);
		}
		for (int i = 0; i <= b - k; i++)
		{
			SetPos(b - k - i, a - k);
			cout << " ";
			Sleep(time);
		}
		for (int i = 0; i <= a - k; i++)
		{
			SetPos(k , a - i - k);
			cout << " ";
			Sleep(time);
		}
		k++;
		c--;
		Sleep(30);
	}
	Setcolor(15, 0);

}

//им€
void name()
{
	char s = 219;
	srand(time(NULL));
	Setcolor(4, 0);
	for (int i = 0; i < 150; i++)
	{
		int a = rand() % 119;
		int b = rand() % 30;
		SetPos(a, b);
		cout << s << s;
		Sleep(1);
	}
	Setcolor(14, 15);
	Sleep(150);
	SetPos(25, 7);
	cout << s << s << setw(14) << " " << s << s << "     " << s << s << s << s << s << s << "     " << s << s << setw(14) << " " << s << s << "       " << s << s << s;
	Sleep(50);
	SetPos(25, 8);
	cout << s << s << setw(14) << " " << s << s << "   " << s << s << s << s << s << s << s << s << s << s << "   " << s << s << setw(14) << " " << s << s << "      " << s << s << s << s << s;
	Sleep(50);
	SetPos(26, 9);
	cout << s << s << setw(12) << " " << s << s << "    " << s << s << s << s << "  " << s << s << s << s << "    " << s << s << setw(12) << " " << s << s << "       " << s << s << " " << s << s;
	Sleep(50);
	SetPos(26, 10);
	cout << s << s << setw(12) << " " << s << s << "   " << s << s << s << "      " << s << s << s  << "   " << s << s << setw(12) << " " << s << s << "      " << s << s << "   " << s << s;
	Sleep(50);
	SetPos(27, 11);
	cout << s << s << setw(10) << " " << s << s << "    " << s << s << s << "      " << s << s << s << "    " << s << s << setw(10) << " " << s << s << "      " << s << s << s <<"   " << s << s << s;
	Sleep(50);
	SetPos(27, 12);
	cout << s << s << setw(10) << " " << s << s << "    " << s << s << "        " << s << s << "    " << s << s << setw(10) << " " << s << s << "      " << s << s <<  "     " << s << s;
	Sleep(50);
	SetPos(28, 13);
	cout << s << s << setw(8) << " " << s << s << "     " << s << s << "        " << s << s << "     " << s << s << setw(8) << " " << s << s << "      " << s << s << "       " << s << s;
	Sleep(50);
	SetPos(28, 14);
	cout << s << s << setw(8) << " " << s << s << "     " << s << s << "        " << s << s << "     " << s << s << setw(8) << " " << s << s << "      " << s << s << "       " << s << s;
	Sleep(50);
	SetPos(29, 15);
	cout << s << s << setw(6) << " " << s << s << "      " << s << s << "        " << s << s << "      " << s << s << setw(6) << " " << s << s << "      " << s << s << "         " << s << s;
	Sleep(50);
	SetPos(29, 16);
	cout << s << s << setw(6) << " " << s << s << "      " << s << s << "        " << s << s << "      " << s << s << setw(6) << " " << s << s << "      " << s << s << "         " << s << s;
	Sleep(50);
	SetPos(30, 17);
	cout << s << s << setw(4) << " " << s << s << "       " << s << s << "        " << s << s << "       " << s << s << setw(4) << " " << s << s << "      ";
	for (int i = 0; i < 15; i++)
		cout << s;
	Sleep(50);
	SetPos(30, 18);
	cout << s << s << setw(4) << " " << s << s << "       " << s << s << s << "      " << s << s << s << "       " << s << s << setw(4) << " " << s << s << "      ";
	for (int i = 0; i < 15; i++)
		cout << s;
	Sleep(50);
	SetPos(31, 19);
	cout << s << s <<  "  " << s << s << "        " << s << s << s << "      " << s << s << s << "        " << s << s << "  " << s << s << "      " << s << s << setw(13) << " " << s << s;
	Sleep(50);
	SetPos(31, 20);
	cout << s << s << s << s << s << s << "         " << s << s << s << s <<"  " << s << s << s << s << "         " << s << s << s << s << s << s << "      " << s << s << setw(13) << " " << s << s;
	Sleep(50);
	SetPos(32, 21);
	cout << s << s << s << s <<  "          " << s << s << s << s << s << s << s << s << s << s << "          " << s << s << s << s << "      " << s << s << setw(15) << " " << s << s;
	Sleep(50);
	SetPos(33, 22);
	cout << s << s <<  "             " << s << s << s << s << s << s << "             " << s << s << "       " << s << s << setw(15) << " " << s << s;
	Setcolor(15, 0);

}

//выбор уровн€ в меню
int select_level()
{
	Setcolor(15, 15);
	for (int i = 0; i < 7; i++)
	{
		SetPos(50, 12 + i);
		cout << setw(16) << " ";
	}

	Setcolor(0, 7);
	SetPos(50, 12);
	cout << setw(11) << " ";
	SetPos(50, 13);
	cout << "  Levels   ";
	SetPos(50, 14);
	cout << setw(11) << " ";
	SetPos(50, 15);
	cout << "  Level 1  ";
	SetPos(50, 16);
	cout << "  Level 2  ";
	SetPos(50, 17);
	cout << setw(11) << " ";
	Setcolor(15, 0);

	int x = 1;

	int ch = 72;
	while (ch != 13)
	{
		if (ch == 72) x--;
		else if (ch == 80) x++;

		if (x > number_levels) x = 1;
		if (x <= 0) x = number_levels;

		if (x)
		{
			SetPos(52, 15);
			Setcolor(0, 7);
			cout << "Level 1";
			SetPos(52, 16);
			cout << "Level 2";
		}

		if (x == 1)
		{
			SetPos(52, 15);
			Setcolor(15, 0);
			cout << "Level 1";

		}
		else if (x == 2)
		{
			SetPos(52, 16);
			Setcolor(15, 0);
			cout << "Level 2";
		}
		SetPos(0, 0);
		ch = _getch();
	}

	Setcolor(15, 15);

	for (int i = 0; i < 6; i++)
	{
		SetPos(50, 12 + i);
		cout << setw(12) << " ";
	}

	return x;
}

//кастомизаци€ персонажа
void customise()
{
	Setcolor(0, 7);
	SetPos(50, 8);
	cout << setw(18) << " ";
	SetPos(50, 9);
	cout << "    Customise     ";
	for (int i = 0; i < 6; i++)
	{
		SetPos(50, 10 + i);
		cout << setw(18) << " ";
	}

	posX = 52;
	posY = 14;
	character_right(7);

	posX = 63;
	character_left(7);

	Setcolor(0, 7);
	SetPos(50, 16);
	cout << "  ";
	Setcolor(15, 15);
	cout << "  ";
	Setcolor(0, 7);
	cout << "  ";
	Setcolor(11, 11);
	cout << "  ";
	Setcolor(0, 7);
	cout << "  ";
	Setcolor(14, 14);
	cout << "  ";
	Setcolor(0, 7);
	cout << "  ";
	Setcolor(12, 12);
	cout << "  ";
	Setcolor(0, 7);
	cout << "  ";
	Setcolor(0, 7);
	SetPos(50, 17);
	cout << setw(18) << " ";
	SetPos(50, 18);
	cout << setw(18) << " ";

	int ch = 1;
	int x = 1;

	while (ch != 13)
	{
		if (ch == 75) x--;
		else if (ch == 77) x++;

		if (x > 4) x = 1;
		else if (x < 1) x = 4;

		if (x == 1) color = 15;
		else if (x == 2) color = 11;
		else if (x == 3) color = 14;
		else if (x == 4) color = 12;

		posX = 52;
		posY = 14;
		character_right(7);

		posX = 63;
		character_left(7);

		if (x)
		{
			Setcolor(0, 7);
			SetPos(50, 16);
			cout << "  ";
			Setcolor(15, 15);
			cout << "  ";
			Setcolor(0, 7);
			cout << "  ";
			Setcolor(11, 11);
			cout << "  ";
			Setcolor(0, 7);
			cout << "  ";
			Setcolor(14, 14);
			cout << "  ";
			Setcolor(0, 7);
			cout << "  ";
			Setcolor(12, 12);
			cout << "  ";
			Setcolor(0, 7);
			cout << "  ";
			Setcolor(0, 7);
			SetPos(51, 15);
			cout << setw(16) << " ";
			SetPos(51, 17);
			cout << setw(16) << " ";
		}


		if (x == 1)
		{
			Setcolor(0, 0);
			SetPos(51, 15);
			cout << "    ";
			SetPos(51, 16);
			cout << " ";
			SetPos(54, 16);
			cout << " ";
			SetPos(51, 17);
			cout << "    ";
		}
		if (x == 2)
		{
			Setcolor(0, 0);
			SetPos(55, 15);
			cout << "    ";
			SetPos(55, 16);
			cout << " ";
			SetPos(58, 16);
			cout << " ";
			SetPos(55, 17);
			cout << "    ";
		}
		if (x == 3)
		{
			Setcolor(0, 0);
			SetPos(59, 15);
			cout << "    ";
			SetPos(59, 16);
			cout << " ";
			SetPos(62, 16);
			cout << " ";
			SetPos(59, 17);
			cout << "    ";
		}
		if (x == 4)
		{
			Setcolor(0, 0);
			SetPos(63, 15);
			cout << "    ";
			SetPos(63, 16);
			cout << " ";
			SetPos(66, 16);
			cout << " ";
			SetPos(63, 17);
			cout << "    ";
		}
		SetPos(0, 0);
		ch = _getch();
	}

	Setcolor(15, 15);
	for (int i = 0; i < 13; i++)
	{
		SetPos(50, 8 + i);
		cout << setw(18) << " ";
	}
}

//меню
int menu()
{
	Setcolor(0, 7);
	SetPos(50, 12);
	cout << setw(16) << " ";
	SetPos(50, 13);
	cout << setw(6) << " " << "Menu" << setw(6) << " ";
	SetPos(50, 14);
	cout << setw(16) << " ";
	SetPos(50, 15);
	cout << "  Select level  ";
	SetPos(50, 16);
	cout << "  Customise     ";
	SetPos(50, 17);
	cout << "  Exit" << setw(10) << " ";
	SetPos(50, 18);
	cout << setw(16) << " ";
	Setcolor(15, 0);

	char ch = 1;
	int k = 1;
	do
	{
		if (ch == 72) k--;
		else if (ch == 80) k++;

		if (k <= 0) k = 3;
		else if (k > 3) k = 1;

		if (ch == 13)
		{
			Setcolor(0, 7);
			SetPos(50, 12);
			cout << setw(16) << " ";
			SetPos(50, 13);
			cout << setw(6) << " " << "Menu" << setw(6) << " ";
			SetPos(50, 14);
			cout << setw(16) << " ";
			SetPos(50, 15);
			cout << "  Select level  ";
			SetPos(50, 16);
			cout << "  Customise     ";
			SetPos(50, 17);
			cout << "  Exit" << setw(10) << " ";
			SetPos(50, 18);
			cout << setw(16) << " ";
			Setcolor(15, 0);
		}

		if (k)
		{
			SetPos(52, 15);
			Setcolor(0, 7);
			cout << "Select level";
			SetPos(52, 16);
			cout << "Customise";
			SetPos(52, 17);
			cout << "Exit";
		}

		if (k == 1)
		{
			SetPos(52, 15);
			Setcolor(15, 0);
			cout << "Select level";
			Setcolor(0, 7);
		}
		else if (k == 2)
		{
			SetPos(52, 16);
			Setcolor(15, 0);
			cout << "Customise";
			Setcolor(0, 7);
		}
		else
		{
			SetPos(52, 17);
			Setcolor(15, 0);
			cout << "Exit";
			Setcolor(0, 7);
		}
		SetPos(0, 0);
		ch = _getch();
		if (ch == 13 && k == 2)
		{
			customise();
		}
	} while (ch != 13 || (k == 2 && ch == 13) );
	Setcolor(15, 0);

	int x = 1;

	if (k == 3) return 0;
	else if (k == 1) x = select_level();

	Setcolor(15, 0);
	return x;
}

//загрузка уровн€
void load()
{
	int temp_color = color;
	Setcolor(10, 10);
	for (int i = 0; i < 5; i++)
	{
		SetPos(119, 27 - i);
		cout << " ";
	}

	SetPos(1, 27);
	posX = 1;
	posY = 27;
	color = 0;
	for (int i = 0; i < 116; i++)
	{
		character_right(15);
		SetPos(posX - 1, posY - 3);
		Setcolor(15, 15);
		cout << " ";
		SetPos(posX - 1, posY - 2);
		cout << " ";
		SetPos(posX - 1, posY - 1);
		cout << " ";
		posX++;
		Sleep(20);
	}
	color = temp_color;
	Setcolor(0, 15);
	SetPos(100, 28);
	cout << "Tap to continue...";
	_getch();
	Setcolor(15, 0);
}

//нижн€€ шапка в игре
void panel()
{
	Setcolor(7, 7);
	for (int i = 0; i < 5; i++)
	{
		SetPos(0, 25 + i);
		cout << setw(111) << " ";
	}

	posX = 3;
	posY = 29;
	character_right(7);

	posX = 105;
	character_left(7);

	SetPos(14, 27);
	Setcolor(0, 7);
	cout << "COINS";

	Setcolor(8, 8);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetPos(21 + i * 4, 26 + j);
			cout << "   ";
		}
	}

	Setcolor(1, 1);

	for (int i = 0; i < 4; i++)
	{
		SetPos(42, 25 + i);
		cout << " ";
	}
	SetPos(42, 29);
	cout << "    ";

	for (int i = 0; i < 5; i++)
	{
		SetPos(47, 25 + i);
		cout << (i % 2 ? " " : "    ");
	}

	SetPos(52, 25);
	cout << " ";
	SetPos(58, 25);
	cout << " ";

	SetPos(53, 26);
	cout << " ";
	SetPos(57, 26);
	cout << " ";

	SetPos(53, 27);
	cout << "  ";
	SetPos(56, 27);
	cout << "  ";

	SetPos(54, 28);
	cout << "   ";

	SetPos(55, 29);
	cout << " ";

	for (int i = 0; i < 5; i++)
	{
		SetPos(60, 25 + i);
		cout << (i % 2 ? " " : "    ");
	}

	for (int i = 0; i < 4; i++)
	{
		SetPos(65, 25 + i);
		cout << " ";
	}
	SetPos(65, 29);
	cout << "    ";

	Setcolor(0, 7);
	SetPos(83, 26);
	cout << "You need to collect";
	SetPos(84, 27);
	cout << "all coins then a";
	SetPos(84, 28);
	cout << "portal will open";

	Setcolor(15, 0);
}

//второй уровень
void level2()
{
	Setcolor(15, 15);
	SetPos(0, 0);
	for (int i = 0; i <= X; i++)
		cout << "*";

	SetPos(33, 0);
	for (int i = 0; i < 8; i++)
		cout << 1;

	SetPos(67, 0);
	for (int i = 0; i < 15; i++)
		cout << 1;

	for (int i = 0; i < 5; i++)
	{
		SetPos(0, 6 + i);
		cout << "*";
	}

	SetPos(0, 15);
	cout << "*";

	SetPos(0, 19);
	cout << "*";

	SetPos(10, Y);
	for (int i = 0; i < 23; i++)
		cout << "*";

	SetPos(41, Y);
	for (int i = 0; i < 48; i++)
		cout << "*";

	SetPos(100, Y);
	for (int i = 0; i < 11; i++)
		cout << "*";

	for (int i = 0; i < 6; i++)
	{
		SetPos(X, 10 + i);
		cout << "*";
	}

	SetPos(X, 19);
	cout << "*";

	//внутрение стенки
	Setcolor(13, 13);

	SetPos(1, 6);
	for (int i = 1; i < X; i++)
		cout << "*";

	for (int i = 0; i < 14; i++)
	{
		SetPos(32, 1 + i);
		cout << "*";
	}

	for (int i = 0; i < 5; i++)
	{
		SetPos(41, 1 + i);
		cout << "*";
	}

	for (int i = 0; i < 8; i++)
	{
		SetPos(36, 7 + i);
		cout << "*";
	}

	SetPos(33, 14);
	cout << "***";

	SetPos(1, 19);
	for (int i = 0; i < 9; i++)
		cout << "*";

	for (int i = 0; i < 17; i++)
	{
		SetPos(10, 7 + i);
		cout << "*";
	}

	SetPos(16, 10);
	for (int i = 0; i < 12; i++)
		cout << "*";

	for (int i = 0; i < 13; i++)
	{
		SetPos(16, 11 + i);
		cout << "*";
	}

	for (int i = 0; i < 8; i++)
	{
		SetPos(27, 11 + i);
		cout << "*";
	}

	SetPos(27, 19);
	for (int i = 0; i < 15; i++)
		cout << "*";

	for (int i = 0; i < 8; i++)
	{
		SetPos(41, 11 + i);
		cout << "*";
	}

	SetPos(41, 10);
	for (int i = 0; i < 14; i++)
		cout << "*";

	SetPos(61, 10);
	for (int i = 0; i < 49; i++)
		cout << "*";

	for (int i = 0; i < 9; i++)
	{
		SetPos(54, 11 + i);
		cout << "*";
	}

	SetPos(55, 14);
	for (int i = 0; i < 28; i++)
		cout << "*";

	for (int i = 0; i < 5; i++)
	{
		SetPos(66, 19 + i);
		cout << "*";
	}

	for (int i = 0; i < 6; i++)
	{
		SetPos(82, 15 + i);
		cout << "*";
	}

	for (int i = 0; i < 6; i++)
	{
		SetPos(82, 15 + i);
		cout << "*";
	}

	for (int i = 0; i < 13; i++)
	{
		SetPos(88, 11 + i);
		cout << "*";
	}

	SetPos(100, 15);
	for (int i = 0; i < 10; i++)
		cout << "*";

	for (int i = 0; i < 8; i++)
	{
		SetPos(100, 16 + i);
		cout << "*";
	}

	//фальшивые стенки

	SetPos(55, 19);
	for (int i = 0; i < 11; i++)
		cout << "1";

	for (int i = 0; i < 4; i++)
	{
		SetPos(66, 15 + i);
		cout << "1";
	}

	//¬ыход
	if (coin == 3)
	{
		Setcolor(10, 10);
		for (int i = 0; i < 4; i++)
		{
			SetPos(0, i + 20);
			cout << '+';
		}
	}
	else
	{
		Setcolor(15, 15);
		for (int i = 0; i < 4; i++)
		{
			SetPos(0, i + 20);
			cout << '1';
		}
	}


	// монетки
	Setcolor(6, 6);

	for (int i = 0; i < 3; i++)
	{
		if (level2_coins[i][0] == 1)
		{
			SetPos(level2_coins[i][1], level2_coins[i][2]);
			cout << 0;
		}
	}

	//номер уровн€
	Setcolor(4, 4);

	for (int i = 0; i < 5; i++)
	{
		SetPos(71, 25 + i);
		cout << " ";
		SetPos(73, 25 + i);
		cout << " ";
	}

	Setcolor(15, 0);
}

int main()
{
	//logo();
	//name();
	//_getch();
	while (true)
	{
		logo();
		menu_choice = menu();
		if (!menu_choice)
		{
			SetPos(0, 30);
			return 0;
		}
		else
		{
			load();
			system("cls");
			ram();
			panel();
			if (menu_choice == 1) level1();
			else if(menu_choice == 2) level2();
			coins();

			if (menu_choice == 1)
			{
				posX = sposX;
				posY = sposY;
			}
			else if (menu_choice == 2)
			{
				posX = s2posX;
				posY = s2posY;
			}

			character_right(0);
			int ch = 1;

			do
			{
                if(_kbhit())
                {
                    ch = button();
                    move(ch);
                    if(k == 0)
                    {
                        temp_ch = ch;
                        bposY = posY - 3;
                        temp_direction = direction;
                        if(temp_direction == 1)
                            bposX = posX + 3;
                        else
                            bposX = posX - 1;
                    }
                }
				if (complete)
				{
					complete_menu();
					break;
				}
				if (ch == 2)
				{
					if (exit_menu())
					{
						if (menu_choice == 1) level1();
						else if (menu_choice == 2) level2();
						break;
					}
					else
					{
						if (menu_choice == 1) level1();
						else if (menu_choice == 2) level2();
						ch = 0;
					}

				}
			} while (true);

			if (menu_choice == 1)
			{
				for (int i = 0; i < 3; i++)
					level1_coins[i][0] = 1;
			}
			else if (menu_choice == 2)
			{
				for (int i = 0; i < 3; i++)
					level2_coins[i][0] = 1;
			}
			coin = 0;
			complete = false;
		}
	}
	SetPos(0, Y);

	SetPos(0, 30);
}
