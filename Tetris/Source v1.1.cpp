/*					       TETRIS V1.2
					A PROGRAM BY SARTHIK GARG
						1300 LINES OF CODE
						 MADE ON 1.1.2018
		
		THIS VERSION ADDS TWO MORE SHAPES AND HAVE COLORS COMBINATIONS
*/
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;
int pow_result;
int plant(int,int&, int [27][20]);
void move(int [27][20], int);
void instructions(int);
void menucall(int [27][20],int& ,int& , int&, int&);
void print(int[27][20]);
void gotoxy(short, short);
void size(int, int);
bool movecheck(int[27][20], int);
void ini(int [27][20]);
bool rotatcheck(int[27][20], int, int, int);
void rotat(int[27][20], int&, int, int);
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
void main()
{
	srand((unsigned)time(NULL));
	SetConsoleTextAttribute(out, 15);
	size(9, 1);
	int game = 1, input = 0, nxt = 0, map[27][20] = { 0 }, ori, point = 0,curr;
	instructions(1);
	ini(map);
	curr = (rand() % 7) + 1;
	nxt = plant(curr ,ori, map);
	do {
		print(map);
		//	FOR DISPLAYING UPCOMING SHAPES
		{
			gotoxy(30, 1);
			SetConsoleTextAttribute(out, 14);
			cout << "POINTS: " << point;
			SetConsoleTextAttribute(out, 15);
			gotoxy(30, 3);
			cout << "NEXT:";
			SetConsoleTextAttribute(out, 2);
			if (nxt == 1)
			{
				gotoxy(33, 6);
				cout << "##";
				gotoxy(33, 7);
				cout << "##";
			}
			if (nxt == 2)
			{
				gotoxy(33, 6);
				cout << "#####";
			}
			if (nxt == 3)
			{
				gotoxy(34, 6);
				cout << "#";
				gotoxy(33, 7);
				cout << "###";
			}
			if (nxt == 4)
			{
				gotoxy(33, 6);
				cout << "##";
				gotoxy(34, 7);
				cout << "#";
				gotoxy(34, 8);
				cout << "#";
			}
			if (nxt == 5)
			{
				gotoxy(33, 6);
				cout << "##";
				gotoxy(33, 7);
				cout << "#";
				gotoxy(33, 8);
				cout << "#";
			}
			if (nxt == 6)
			{
				gotoxy(33, 6);
				cout << "#";
				gotoxy(33, 7);
				cout << "##";
				gotoxy(34, 8);
				cout << "#";
			}
			if (nxt == 7)
			{
				gotoxy(34, 6);
				cout << "#";
				gotoxy(33, 7);
				cout << "##";
				gotoxy(33, 8);
				cout << "#";
			}
			SetConsoleTextAttribute(out, 15);
		}
		if (point < 60)
			Sleep(300 - point * 5);
		else
			Sleep(50);
		if (_kbhit())
		{
			for (int i = 0; i < 100; i++)
			{
				if (_kbhit())
					input = _getch();
				if (input == 75 || input == 72 || input == 77 || input == 80 || input == 27)
				{
					if (input == 75 || input == 77)
					{
						if (movecheck(map, input))
						{
							move(map, input);
						}
					}
					else
					{
						if (input == 72 || input == 80)
						{
							if (rotatcheck(map, ori, curr, input))
								rotat(map, ori, curr, input);
						}
						else
						{
							if (input == 27)
							{
								menucall(map,curr,nxt,ori,point);
								print(map);
							}
						}
					}
					i = 0;
				}
				input = 0;
			}
		}
		int ctr = 0;
		for (int i = 25; i >= 3; i--)
		{
			ctr = 0;
			for (int j = 1; j < 19; j++)
			{
				if (map[i][j] == 3)
				{
					ctr++;
				}
			}
			if (ctr == 18)
			{
				point++;
				for (int j = 1; j < 19; j++)
				{
					map[i][j] = 0;
				}
				for (int k = i; k >= 4; k--)
				{
					for (int j = 1; j < 19; j++)
					{
						if (map[k-1][j] == 3)
						{
							map[k][j] = map[k - 1][j] + map[k][j];
							map[k - 1][j] = map[k][j] - map[k - 1][j];
							map[k][j] = map[k][j] - map[k - 1][j];
						}
					}
				}
				
			}
		}
		if (movecheck(map, 0))
		{
			for (int i = 0; i < 27; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if (map[i][j] == 1)
					{
						map[i][j] = 3;
					}
				}
			}
			curr = nxt;
			nxt = plant(curr, ori, map);
			if (nxt == 0)
				game = 0;
		}
		else
		{
			for (int i = 26; i >= 0; i--)
			{
				for (int j = 0; j < 20; j++)
				{
					if (map[i][j] == 1)
					{
						map[i + 1][j] = 1;
						map[i][j] = 0;
					}
				}
			}
		}
	} while (game != 0);
	gotoxy(30, 10);
	cout << "---GAME OVER---";
	_getch();
}
void gotoxy(short x, short y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(out, c);
}
void size(int ratio, int bold)
{
	bold *= 100;
	int x = 2 * ratio, y = 2 * ratio;
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = y;
	info.dwFontSize.X = x;
	info.FontWeight = bold;
	SetCurrentConsoleFontEx(out, NULL, &info);
}
void ini(int map[27][20])
{
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if ((i == 2 || i == 26 || j == 0 || j == 19)&&i>1)
			{
				if (!(i == 2 && (j > 6 && j < 13)))
				{
					map[i][j] = 2;
				}
			}
		}
	}
}
void print(int map[27][20])
{
	system("cls");
	for (int i = 2; i < 27; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 2)
			{
				cout << "*";
			}
			if (map[i][j] == 1)
			{
				SetConsoleTextAttribute(out, 2);
				cout << "#";
				SetConsoleTextAttribute(out, 15);
			}
			if (map[i][j] == 3)
			{
				SetConsoleTextAttribute(out, 4);
				cout << "#";
				SetConsoleTextAttribute(out, 15);
			}
			if (!map[i][j])
			{
				cout << " ";
			}
		}
		if (i != 26)
			cout << endl;
	}
}
int plant(int curr,int &ori, int map[27][20])
{
	if (curr == 1)
	{
		if ((map[2][9] < 2 && map[2][10] < 2) && (map[1][9] < 2 && map[1][10] < 2))
		{
			map[2][9] = map[2][10] = map[1][9] = map[1][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 2)
	{
		if ((map[2][7] < 2 && map[2][8] < 2) && (map[2][9] < 2 && map[2][10] < 2) && map[2][11] < 2)
		{
			map[2][7] = map[2][8] = map[2][9] = map[2][10] = map[2][11] = 1;
			ori = 0;
		}
		else
			return 0;
	}
	if (curr == 3)
	{
		if ((map[1][9] < 2 && map[2][8] < 2) && (map[2][9] < 2 && map[2][10] < 2))
		{
			map[1][9] = map[2][8] = map[2][9] = map[2][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 4)
	{
		if ((map[0][9] < 2 && map[0][10] < 2) && (map[1][10] < 2 && map[2][10] < 2))
		{
			map[0][9] = map[0][10] = map[1][10] = map[2][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 5)
	{
		if ((map[0][9] < 2 && map[0][10] < 2) && (map[1][9] < 2 && map[2][9] < 2))
		{
			map[0][9] = map[0][10] = map[1][9] = map[2][9] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 6)
	{
		if ((map[0][9] < 2 && map[1][9] < 2) && (map[1][10] < 2 && map[2][10] < 2))
		{
			map[0][9] = map[1][9] = map[1][10] = map[2][10] = 1;
			ori = 0;
		}
		else
			return 0;
	}
	if (curr == 7)
	{
		if ((map[0][10] < 2 && map[1][9] < 2) && (map[1][10] < 2 && map[2][9] < 2))
		{
			map[0][10] = map[1][9] = map[1][10] = map[2][9] = 1;
			ori = 0;
		}
		else
			return 0;
	}
	return((rand() % 7) + 1);
}
bool rotatcheck(int map[27][20], int ori, int curr, int rot)
{
	if (rot == 72)
	{
		rot = 0;
	}
	if (rot == 80)
	{
		rot = 1;
	}
	if (curr == 2)
	{
		int ctr = -2;
		int ctrd = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					pow_result = pow(-1, ori);
					if (map[i + pow_result*ctr][j - pow_result*ctr] > 1)
						return false;
					ctr++;
				}
			}
		}
	}
	if (curr == 3)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (rot)
					{
						if (ori == 1 || ori == 2)
						{
							if ((ori == 1 && ctr == 2) || (ori == 2 && ctr == 1))
							{
								pow_result = pow(-1, ori % 2);
								if (map[i + 1][j - pow_result] > 1)
									return false;
							}
						}
						else
						{
							if (ori == ctr)
							{
								pow_result = pow(-1, ori % 2);
								if (map[i - 1][j + pow_result] > 1)
									return false;
							}
						}
					}
					else
					{
						if (ori == 1 || ori == 2)
						{
							if (ctr == 4)
							{
								pow_result = pow(-1, ori % 2);
								if (map[i - pow_result][j - 1] > 1)
									return false;
							}
						}
						else
						{
							if (ctr == 1)
							{
								pow_result = pow(-1, ori % 2);
								if (map[i + pow_result][j + 1] > 1)
									return false;
							}
						}
					}
				}
			}
		}
	}
	if (curr == 4)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (((ctr == 3 || ctr == 2) && (ori == 4 && rot)) || ((ctr == 4 || ctr == 3) && (ori == 1 && !rot)))
					{
						if (map[i - 1][j - 2] > 1)
							return false;
					}
					if (((ctr == 1 || ctr == 2) && (ori == 3 && rot)) || ((ctr == 2 || ctr == 3) && (ori == 4 && !rot)))
					{
						if (map[i + 2][j - 1] > 1)
							return false;
					}
					if (((ctr == 3 || ctr == 2) && (ori == 2 && rot)) || ((ctr == 2 || ctr == 1) && (ori == 3 && !rot)))
					{
						if (map[i + 1][j + 2] > 1)
							return false;				
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 3 || ctr == 2) && (ori == 2 && !rot)))
					{
						if (map[i - 2][j + 1] > 1)
							return false;
					}
				}
			}
		}
	}
	if (curr == 5)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if ((ctr == 1 || ctr == 2) && ((ori == 1 && !rot) || (ori == 2 && rot)))
					{
						if (map[i + 2][j + 1] > 1)
							return false;
					}
					if (((ctr == 1 || ctr == 2) && (ori == 3 && rot)) || ((ctr == 4 || ctr == 3) && (ori == 2 && !rot)))
					{
						if(map[i + 1][j - 2] > 1)
							return false;
					}
					if ((ctr == 3 || ctr == 4) && ((ori == 3 && !rot) || (ori == 4 && rot)))
					{
						if(map[i - 2][j - 1] > 1)
							return false;
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 1 || ctr == 2) && (ori == 4 && !rot)))
					{
						if(map[i - 1][j + 2] > 1)
							return false;
					}
				}
			}
		}
	}
	if (curr == 6)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (ori)
					{
						if (ctr == 1)
						{
							if (map[i + 2][j] > 1)
								return false;
						}
						if (ctr == 2)
						{
							if (map[i][j - 2] > 1)
								return false;
						}
					}
					else
					{
						if (ctr == 1)
						{
							if (map[i][j + 2] > 1)
								return false;
						}
						if (ctr == 4)
						{
							if (map[i - 2][j] > 1)
								return false;
						}
					}
				}
			}
		}
	}
	if (curr == 7)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (ori)
					{
						if (ctr == 2)
						{
							if (map[i + 2][j] > 1)
								return false;
						}
						if (ctr == 1)
						{
							if (map[i][j + 2] > 1)
								return false;
						}
					}
					else
					{
						if (ctr == 1)
						{
							if (map[i][j - 2] > 1)
								return false;
						}
						if (ctr == 4)
						{
							if (map[i - 2][j] > 1)
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}
void rotat(int map[27][20], int &ori, int curr, int rot)
{
	if(rot == 72)
	{
		rot = 0;
	}
	if (rot == 80)
	{
		rot = 1;
	}
	if (curr == 2)
	{
		int ctr = -2;
		int ctrd = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctrd++;
					pow_result = pow(-1, ori);
					if (!((ctrd == 3 || ctrd == 4) && ori))
					{
						map[i + pow_result*ctr][j - pow_result*ctr] = 1;
						if (!(i + pow_result*ctr == i&&j - pow_result*ctr == j))
							map[i][j] = 0;
						ctr++;
					}
				}
				if (ctr == 3)
					break;
			}
			if (ctr == 3)
				break;
		}
		ori = !ori;
	}
	if (curr == 3)
	{
		int ctr = 0, flag = 1;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (rot)
					{
						if (ori == 1 || ori == 2)
						{
							if ((ori == 1 && ctr == 2) || (ori == 2 && ctr == 1))
							{
								pow_result = pow(-1, ori % 2);
								map[i + 1][j - pow_result] = 1;
								map[i][j] = 0;
								flag = 0;
							}
						}
						else
						{
							if (ori == ctr)
							{
								pow_result = pow(-1, ori % 2);
								map[i - 1][j + pow_result] = 1;
								map[i][j] = 0;
								flag = 0;
								//cout << ori << ctr<<" "<<i-1<<j-pow_result<<" "<<i<<j;
								//_getch();
							}
						}
					}
					else
					{
						if (ori == 1 || ori == 2)
						{
							if (ctr == 4)
							{
								pow_result = pow(-1, ori % 2);
								map[i - pow_result][j - 1] = 1;
								map[i][j] = 0;
								flag = 0;
							}
						}
						else
						{
							if (ctr == 1)
							{
								pow_result = pow(-1, ori % 2);
								map[i + pow_result][j + 1] = 1;
								map[i][j] = 0;
								flag = 0;
							}
						}
					}
				}
				if (!flag)
					break;
			}
			if (!flag)
				break;
		}
		if (rot)
		{
			if (ori != 4)
				ori++;
			else
				ori = 1;
		}
		else
		{
			if (ori != 1)
				ori--;
			else
				ori = 4;
		}
	}
	if (curr == 4)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (((ctr == 3 || ctr == 2) && (ori == 4 && rot)) || ((ctr == 4 || ctr == 3) && (ori == 1 && !rot)))
					{
						map[i - 1][j - 2] = 1;
						map[i][j] = 0;
					}
					if (((ctr == 1 || ctr == 2) && (ori == 3 && rot)) || ((ctr == 2 || ctr == 3) && (ori == 4 && !rot)))
					{
						map[i + 2][j - 1] = 1;
						map[i][j] = 0;
					}
					if (((ctr == 3 || ctr == 2) && (ori == 2 && rot)) || ((ctr == 2 || ctr == 1) && (ori == 3 && !rot)))
					{
						map[i + 1][j + 2] = 1;
						map[i][j] = 0;
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 3 || ctr == 2) && (ori == 2 && !rot)))
					{
						map[i - 2][j + 1] = 1;
						map[i][j] = 0;
					}
				}
			}
		}
		if (rot)
		{
			if (ori != 4)
				ori++;
			else
				ori = 1;
		}
		else
		{
			if (ori != 1)
				ori--;
			else
				ori = 4;
		}
	}
	if (curr == 5)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if ((ctr == 1 || ctr == 2) && ((ori == 1 && !rot) || (ori == 2 && rot)))
					{
						map[i + 2][j + 1] = 1;
						map[i][j] = 0;
					}
					if (((ctr == 1 || ctr == 3) && (ori == 3 && rot)) || ((ctr == 5 || ctr == 3)&&(ori == 2 && !rot)))
					{
						map[i + 1][j - 2] = 1;
						map[i][j] = 0;
					}
					if ((ctr == 3 || ctr == 4) && ((ori == 3 && !rot) || (ori == 4 && rot)))
					{
						map[i - 2][j - 1] = 1;
						map[i][j] = 0;
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 1 || ctr == 2) && (ori == 4 && !rot)))
					{
						map[i - 1][j + 2] = 1;
						map[i][j] = 0;
					}
				}
			}
		}
		if (rot)
		{
			if (ori != 4)
				ori++;
			else
				ori = 1;
		}
		else
		{
			if (ori != 1)
				ori--;
			else
				ori = 4;
		}
	}
	if (curr == 6)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (ori)
					{
						if (ctr == 1)
						{
							map[i + 2][j] = 1;
							map[i][j] = 0;
						}
						if (ctr == 2)
						{
							map[i][j - 2] = 1;
							map[i][j] = 0;
						}
					}
					else
					{
						if (ctr == 1)
						{
							map[i][j + 2] = 1;
							map[i][j] = 0;
						}
						if (ctr == 5)
						{
							map[i - 2][j] = 1;
							map[i][j] = 0;
						}
					}
				}
			}
		}
		ori = !ori;
	}
	if (curr == 7)
	{
		int ctr = 0;
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					ctr++;
					if (ori)
					{
						if (ctr == 2)
						{
							map[i + 2][j] = 1;
							map[i][j] = 0;
						}
						if (ctr == 1)
						{
							map[i][j + 2] = 1;
							map[i][j] = 0;
						}
					}
					else
					{
						if (ctr == 1)
						{
							map[i][j - 2] = 1;
							map[i][j] = 0;
						}
						if (ctr == 4)
						{
							map[i - 2][j] = 1;
							map[i][j] = 0;
						}
					}
				}
			}
		}
		ori = !ori;
	}
}
bool movecheck(int map[27][20], int dir)
{
	if (dir == 75)
	{
		dir = 1;
	}
	if (dir == 77)
	{
		dir = 2;
	}
	if (dir)
	{
		dir--;
		int pow_result = pow(-1, dir);
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					if (map[i][j - pow_result] > 1)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else
	{
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					if (map[i + 1][j] > 1)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
}
void move(int map[27][20], int dir)
{
	if (dir == 75)
	{
		dir = 0;
		int pow_result = pow(-1, dir);
		for (int i = 26; i >= 0; i--)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					map[i][j - pow_result] = 1;
					map[i][j] = 0;
				}
			}
		}
	}
	if (dir == 77)
	{
		dir = 1;
		int pow_result = pow(-1, dir);
		for (int i = 26; i >= 0; i--)
		{
			for (int j = 19; j >= 0; j--)
			{
				if (map[i][j] == 1)
				{
					map[i][j - pow_result] = 1;
					map[i][j] = 0; 
				}
			}
		}
	}
}
void menucall(int map[27][20],int &curr, int &nxt,int &ori,int &point)
{
	int input = 0;
	int menux = 1;
	int exitpg = 1;
	static int fontsize = 9, fontwt = 1, fontcl = 15, options = 2;
	do {
		system("cls");
		gotoxy(35, 10);
		if (menux == 1)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Resume";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 11);
		if (menux == 2)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Restart";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 12);
		if (menux == 3)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Font";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 13);
		if (menux == 4)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Instructions";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 14);
		if (menux == 5)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "About";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 15);
		if (menux == 6)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Exit";
		SetConsoleTextAttribute(out, fontcl);
		input = _getch();
		if (input == 72)
		{
			if (menux > 1)
			{
				menux--;
			}
		}
		if (input == 80)
		{
			if (menux < 6)
			{
				menux++;
			}
		}
		if (input == 13)
		{
			if (menux == 1)
			{
				exitpg = 0;
			}
			if (menux == 2)
			{
				menux = 1;
				do {
					system("cls");
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(0, 8);
					for (int j = 0; j<75; j++)
					{
						cout << "-";
					}
					gotoxy(35, 9);
					cout << "ARE YOU SURE?\n";
					for (int j = 0; j<75; j++)
					{
						cout << "-";
					}
					if (!menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(35, 12);
					cout << "YES";
					SetConsoleTextAttribute(out, fontcl);
					if (menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(45, 12);
					cout << "NO";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 75)
					{
						if (menux)
							menux--;
					}
					if (input == 77)
					{
						if (!menux)
							menux++;
					}
					if (input == 13)
					{
						if (!menux)
						{
							for (int i = 0; i < 27; i++)
							{
								for (int j = 0; j < 20; j++)
								{
									if (map[i][j] == 3 || map[i][j] == 1)
									{
										map[i][j] = 0;
									}
								}
							}
							curr = rand() % 7 + 1;
							nxt = plant(curr, ori, map);
							point = 0;
						}
						menux = 6;
					}
				} while (menux != 6 && input != 27);
				menux = 2;
			}
			if (menux == 3)
			{
				menux = 1;
				do {
					system("cls");
					gotoxy(20, 1);
					SetConsoleTextAttribute(out, fontcl);
					cout << "FONTS\n";
					for (int i = 0; i < 80; i++)
						cout << "-";
					gotoxy(5, 6);
					if (menux == 1)
						SetConsoleTextAttribute(out, options);
					cout << "FONT SIZE";
					gotoxy(30, 6);
					cout << "< " << fontsize + 1 << " >";
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(5, 8);
					if (menux == 2)
						SetConsoleTextAttribute(out, options);
					cout << "FONT WEIGHT";
					gotoxy(30, 8);
					cout << "< " << fontwt;
					gotoxy(34, 8);
					cout << " >";
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(18, 19);
					if (menux == 3)
						SetConsoleTextAttribute(out, options);
					cout << "<- BACK";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 72)
					{
						if (menux > 1)
							menux--;
					}
					if (input == 80)
					{
						if (menux < 3)
							menux++;
					}
					if (input == 77)
					{
						if (menux == 1)
						{
							if (fontsize < 19)
								fontsize++;
						}
						if (menux == 2)
						{
							if (fontwt < 10)
								fontwt++;
						}
					}
					if (input == 75)
					{
						if (menux == 1)
						{
							if (fontsize > 9)
								fontsize--;
						}
						if (menux == 2)
						{
							if (fontwt > 1)
								fontwt--;
						}
					}
					if (input == 13)
					{
						if (menux == 3)
							exitpg = 0;
					}
					if (input == 27)
					{
						exitpg = 0;
					}
					size(fontsize, fontwt);
				} while (exitpg);
				exitpg = 1;
				menux = 3;
			}
			if (menux == 4)
			{
				instructions(0);
				menux = 4;
			}
			if (menux == 5)
			{
				do {
					system("cls");
					gotoxy(35, 5);
					SetConsoleTextAttribute(out, 14);
					cout << "T";
					SetConsoleTextAttribute(out, 5);
					cout << "E";
					SetConsoleTextAttribute(out, 14);
					cout << "T";
					SetConsoleTextAttribute(out, 4);
					cout << "R";
					SetConsoleTextAttribute(out, 2);
					cout << "I";
					SetConsoleTextAttribute(out, 1);
					cout << "S";
					gotoxy(27, 10);
					SetConsoleTextAttribute(out, 4);
					cout << "A Program by SARTHIK GARG";
					gotoxy(30, 12);
					cout << "1300 Lines of Code";
					gotoxy(31, 13);
					cout << "Made On 1.1.2018";
					gotoxy(35, 20);
					SetConsoleTextAttribute(out, 2);
					cout << "<- BACK";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
				} while (input != 13 && input != 27);
			}
			if (menux == 6)
			{
				menux = 1;
				do {
					system("cls");
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(0, 8);
					for (int j = 0; j<75; j++)
					{
						cout << "-";
					}
					gotoxy(35, 9);
					cout << "ARE YOU SURE?\n";
					for (int j = 0; j<75; j++)
					{
						cout << "-";
					}
					if (!menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(35, 12);
					cout << "YES";
					SetConsoleTextAttribute(out, fontcl);
					if (menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(45, 12);
					cout << "NO";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 75)
					{
						if (menux)
							menux--;
					}
					if (input == 77)
					{
						if (!menux)
							menux++;
					}
					if (input == 13)
					{
						if (!menux)
							exit(0);
						else
							menux = 6;
					}
				} while (menux != 6 && input != 27);
				menux = 6;
			}
			input = 0;
		}
		if (input == 27)
		{
			exitpg = 0;
		}
	} while (exitpg);
}
void instructions(int opt)
{
	system("cls");
	int input = 0;

	system("cls");
	SetConsoleTextAttribute(out, 15);
	cout << "\t\t\t   !!!INSTRUCTIONS!!!\n\n";
	for (int i = 0; i < 80; i++)
		cout << "-";
	cout << "\n\n\n\t\tUSE ";
	SetConsoleTextAttribute(out, 4);
	cout << "UP ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " To ROTATE THE SHAPE ANIT-CLOCKWISE";
	cout << "\n\n\n\t\tUSE ";
	SetConsoleTextAttribute(out, 4);
	cout << "DOWN ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " To ROTATE THE SHAPE CLOCKWISE";
	cout << "\n\n\n\t\tUSE ";
	SetConsoleTextAttribute(out, 4);
	cout << "LEFT ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " To MOVE THE SHAPE TOWARDS LEFT ";
	cout << "\n\n\n\t\tUSE ";
	SetConsoleTextAttribute(out, 4);
	cout << "RIGHT ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " To MOVE THE SHAPE TOWARDS RIGHT \n\n\n\n\t\t\t";
	if (opt)
	{
		cout << "PRESS ";
		SetConsoleTextAttribute(out, 2);
		cout << "ENTER";
		SetConsoleTextAttribute(out, 15);
		cout << " TO CONTINUE";
		cout << "\n\t\t\tPRESS ";
		SetConsoleTextAttribute(out, 2);
		cout << "ESC";
		SetConsoleTextAttribute(out, 15);
		cout << " TO EXIT";
	}
	else
	{
		SetConsoleTextAttribute(out, 2);
		cout << "\t<- BACK";
	}
	SetConsoleTextAttribute(out, 15);
	do {
		input = _getch();
		if (input == 27&&opt)
			exit(0);
	} while (!(input == 13||input == 27));
}