/*					       TETRIS V1.0
					A PROGRAM BY SARTHIK GARG
						1300 LINES OF CODE
						 MADE ON 1.1.2018
*/
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;
int pow_result;
//void intro();
int plant(int,int&, int [27][20]);
void move(int [27][20], int);
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
	int game = 1, input = 0, menu = 0, nxt = 0, map[27][20] = { 0 }, ori, point = 0,curr;
	ini(map);
	size(9, 1);
	curr = (rand() % 5) + 1;
	nxt = plant(curr ,ori, map);
	do {
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
					cout << "#";
				}
				if (!map[i][j])
				{
					cout << " ";
				}
			}
			if (i != 26)
				cout << endl;
		}
		//	FOR DISPLAYING UPCOMING SHAPES
		{
			gotoxy(30, 1);
			cout << "POINTS: " << point;
			gotoxy(30, 3);
			cout << "NEXT:";
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
		}
		Sleep(250 - (point / 10) * 50);
		if (_kbhit())
		{
			for (int i = 0; i < 50; i++)
			{
				if (_kbhit())
					input = _getch();
				if (input == 75 || input == 72 || input == 77 || input == 80)
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
				if (map[i][j] == 2)
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
						map[k][j] = map[k - 1][j] + map[k][j];
						map[k - 1][j] = map[k][j] - map[k - 1][j];
						map[k][j] = map[k][j] - map[k - 1][j];
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
						map[i][j] = 2;
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
int plant(int curr,int &ori, int map[27][20])
{
	//cout << "PLANT";
	if (curr == 1)
	{
		if ((map[2][9] != 2 && map[2][10] != 2) && (map[1][9] != 2 && map[1][10] != 2))
		{
			map[2][9] = map[2][10] = map[1][9] = map[1][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 2)
	{
		if ((map[2][7] != 2 && map[2][8] != 2) && (map[2][9] != 2 && map[2][10] != 2) && map[2][11] != 2)
		{
			map[2][7] = map[2][8] = map[2][9] = map[2][10] = map[2][11] = 1;
			ori = 0;
		}
		else
			return 0;
	}
	if (curr == 3)
	{
		if ((map[1][9] != 2 && map[2][8] != 2) && (map[2][9] != 2 && map[2][10] != 2))
		{
			map[1][9] = map[2][8] = map[2][9] = map[2][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 4)
	{
		if ((map[0][9] != 2 && map[0][10] != 2) && (map[1][10] != 2 && map[2][10] != 2))
		{
			map[0][9] = map[0][10] = map[1][10] = map[2][10] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 5)
	{
		if ((map[0][9] != 2 && map[0][10] != 2) && (map[1][9] != 2 && map[2][9] != 2))
		{
			map[0][9] = map[0][10] = map[1][9] = map[2][9] = 1;
			ori = 1;
		}
		else
			return 0;
	}
	if (curr == 6)
	{
		if ((map[0][9] != 2 && map[1][9] != 2) && (map[1][10] != 2 && map[2][10] != 2))
		{
			map[0][9] = map[1][9] = map[1][10] = map[2][10] = 1;
		}
		else
			return 0;
	}
	if (curr == 7)
	{
		if ((map[0][10] != 2 && map[1][9] != 2) && (map[1][10] != 2 && map[2][9] != 2))
		{
			map[0][10] = map[1][9] = map[1][10] = map[2][9] = 1;
		}
		else
			return 0;
	}
	return((rand() % 5) + 1);
}
bool rotatcheck(int map[27][20], int ori, int curr, int rot)
{
	//cout << "ROTATCHECK";
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
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					pow_result = pow(-1, ori);
					if (map[i + pow_result*ctr][j + ctr] == 2)
						return false;
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
								if (map[i + 1][j - pow_result] == 2)
									return false;
							}
						}
						else
						{
							if (ori == ctr)
							{
								pow_result = pow(-1, ori % 2);
								if (map[i + 1][j - pow_result] == 2)
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
								pow_result = pow(-1, !(ori % 2));
								if (map[i + pow_result][j - 1] == 2)
									return false;
							}
						}
						else
						{
							if (ctr == 1)
							{
								pow_result = pow(-1, ori % 2);
								if (map[i + pow_result][j + 1] == 2)
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
						if (map[i - 1][j - 2] == 2)
							return false;
					}
					if (((ctr == 1 || ctr == 2) && (ori == 3 && rot)) || ((ctr == 2 || ctr == 3) && (ori == 4 && !rot)))
					{
						if (map[i + 2][j - 1] == 2)
							return false;
					}
					if (((ctr == 3 || ctr == 2) && (ori == 2 && rot)) || ((ctr == 2 || ctr == 1) && (ori == 3 && !rot)))
					{
						if (map[i + 1][j + 2] == 2)
							return false;				
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 3 || ctr == 2) && (ori == 2 && !rot)))
					{
						if (map[i - 2][j + 1] == 2)
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
						if (map[i + 2][j + 1] == 2)
							return false;
					}
					if (((ctr == 1 || ctr == 3) && (ori == 3 && rot)) || ((ctr == 5 || ctr == 3) && (ori == 2 && !rot)))
					{
						if(map[i + 1][j - 2] == 2)
							return false;
					}
					if ((ctr == 3 || ctr == 4) && ((ori == 3 && !rot) || (ori == 4 && rot)))
					{
						if(map[i - 2][j - 1] == 2)
							return false;
					}
					if (((ctr == 4 || ctr == 3) && (ori == 1 && rot)) || ((ctr == 1 || ctr == 2) && (ori == 4 && !rot)))
					{
						if(map[i - 1][j + 2] == 2)
							return false;
					}
				}
			}
		}
	}
	return true;
}
void rotat(int map[27][20], int &ori, int curr, int rot)
{
	//cout << "ROTAT";
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
						map[i + pow_result*ctr][j - ctr] = 1;
						if (!(i + pow_result*ctr == i&&j - ctr == j))
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
								pow_result = pow(-1, (ori % 2));
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
}
bool movecheck(int map[27][20], int dir)
{
	//cout << "MOVECHECK";
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
					if (map[i][j - pow_result] == 2)
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
					if (map[i + 1][j] == 2)
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
	//cout << "MOVE";
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