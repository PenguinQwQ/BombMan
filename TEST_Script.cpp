#include <conio.h>
#include <iostream>
#include <windows.h>
#include <cstring>
using namespace std;
char g[51][51];
int n = 20, m = 20;
void deal_with_input()
{
	char ch;
	if(_kbhit())//¼ì²âÊäÈëÇé¿ö 
	{
		ch = _getch();
		cout << ch;
	}
}
void display()
{
	
	system("cls");//clear  screen
	for (int i = 1 ; i <= n ; i++)
	{
		for (int j = 1 ; j <= m ; j++)
			{
				putchar(g[i][j]);
			}
		putchar('\n');
	}
} 
int main()
{
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			g[i][j] = '@';
	int cnt = n * m;
	int x = 1, y = 1;
	while(cnt >= -1)
	{
	//	Sleep(100);
		display();
		bool flag = true;
		g[x][y] = '&';
		if(y < m)
			y++;
		else
		{
			x++;
			y = 1;
		}
		cnt--;
	}
//	deal_with_input();
		return 0;
}
