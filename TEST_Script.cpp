#include <conio.h>
#include <iostream>
#include <windows.h>
#include <cstring>
using namespace std;
//����Ϊ��ͼ������ݣ��ȿ����ʵ��  
const int ONE_SECOND = 1e6;
char g[15][15] = {
{' ','*','*','#','*','*','*','#','*','#','*',' ',' ','*',' '},
{'#','*','*',' ','*','#','*',' ','*',' ',' ','*','#','*',' '},
{'*',' ','#',' ','#','*','*','#','#',' ','#',' ','#','*','#'},
{'#','*',' ',' ',' ','*','#',' ','*','*',' ',' ',' ','*','*'},
{'*','*','#',' ','#',' ','*',' ','#','*','#',' ','#',' ','#'},
{' ','*','*','*','*',' ',' ',' ','#','*','#','*','*','*','*'},
{'#','#','*','#',' ','#','#','#','*','*',' ','*','#',' ','#'},
{'*','*',' ',' ','*',' ',' ','*','*','#','#','*','*',' ',' '},
{'*','#','#',' ','#','*','*','#','*','*','#',' ','#',' ','#'},
{' ','*',' ',' ',' ',' ','#','#','#','*',' ',' ',' ',' ',' '},
{'*','*','#',' ','#',' ','*','*',' ',' ','#',' ','#','*','*'},
{'#',' ','#','*','#',' ','#','*','#','*','*',' ','#','#','*'},
{'*','*',' ',' ',' ','*','#',' ','*',' ','#','*',' ','*','*'},
};
int n = 15, m = 15;

void display()
{
	system("cls");//clear  screen
	for (int i = 0 ; i <= 14 ; i++)
	{
		for (int j = 0 ; j <= 14 ; j++)
			{
				putchar(g[i][j]);
			}
		putchar('\n');
	}
} 

//�ٿ������������:

class Player
{
private:
	int x, y;
	char sym;//�ַ���ʾ��ҵ���ʾ��ʽ 
	
public:
	Player(int x1, int y1, char ch)	//���캯��������һ����� 
	:x(x1),y(y1),sym(ch)
	{}
	~Player()//��������
	{
		return;
	}
	void move(char t);//�ƶ����� 
	void upd_pos(int x1,int y1);//������º�������Ԫ��(x1,y1)������ı��Ȩֵ����Ϊ���֣�
	//��(-1,0),��(1,0),��(0,-1),��(0,1) 
	int get_x();//���x���� 
	int get_y();
};
inline int Player::get_x()
{
	return this->x;
}
inline int Player::get_y()
{
	return this->y;
}
void Player::upd_pos(int x1,int y1)
{
	int x = this->get_x() + x1, y = this->get_y() + y1;
	if(x < 0 || y < 0 || x > 14 || y > 14 || g[x][y] != ' ')
		return;//�������ߣ���ֱ�ӷ��ؼ��ɣ�����Ҫ����λ������ 
	g[this->x][this->y] = ' ';
	g[x][y] = '@';
	this->x = x;
	this->y = y;
}
void Player::move(char t)
{
	if(t == 'w')
		upd_pos(-1,0);
	if(t == 's')
		upd_pos(1,0);
	if(t == 'a')
		upd_pos(0,-1);
	if(t == 'd')
		upd_pos(0,1);
	return;
}


Player P(3, 11, '@');
void deal_with_input()
{
	if(_kbhit())//���������� 
	{
		char ch;
		ch = _getch();
		cout << ch << endl;
		P.move(ch);
		return;
	}
}
int count = 0;
int main()
{
	g[3][11] = '@';
	display();
	while(1)
	{
		deal_with_input();
		count++;
		if(count == 200)
			{
			//	deal_with_time();
				display();
				count = 0;
			}
	}

		return 0;
}
