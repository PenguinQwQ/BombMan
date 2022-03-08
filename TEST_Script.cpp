#include <conio.h>
#include <iostream>
#include <windows.h>
#include <cstring>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
//以下为地图类的内容：先靠打表实现  


const int ONE_SECOND = 1e6;
 class Player
{
private:
	int x, y;
	char sym;//字符表示玩家的显示形式 
	int health;
public:
	Player(int x1, int y1, char ch, int h)	//构造函数，构造一个玩家 
	:x(x1),y(y1),sym(ch),health(h)
	{}
	~Player()//析构函数
	{
		return;
	}
	void move(char t);//移动函数 
	void upd_pos(int x1,int y1);//坐标更新函数，二元组(x1,y1)代表方向改变的权值，分为四种：
	//上(-1,0),下(1,0),左(0,-1),右(0,1) 
	int get_x();//获得x坐标
	int get_y();
	void setBomb();
	void hurt(int d);
	int get_h();
};
Player P(3, 11, '@', 2);
char g[15][15] = {
{' ','*','*','#','*','*','*','#','*','#','*',' ',' ','*',' '},
{'#','*','*',' ','*','#','*',' ','*',' ',' ',' ','#','*',' '},
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
int xp = 3, yp = 11;
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
class Bomb
{
	private:
		int x, y;//定义的坐标
		int t;//剩余的爆炸时间。 
		char symbol;//炸弹的符号标记
		int damage;
	public:
		Bomb()
		{x = -1;y = -1;t = -1;symbol = '&';damage = 1;}
		Bomb(int x1,int y1,int ti,char ch,int d)
		:x(x1),y(y1),t(ti),symbol(ch),damage(d)
		{}//构造函数
		~Bomb()//析构函数 
		{
			return;
		} 
		void blow();//爆炸函数 
		void bomb_clock_minus();
		int bomb_clock();
		int getx();
		int gety();
		int getd();
};
inline int Bomb::getd()
{
	return this->damage;
}
inline int Bomb::getx()
{
	return this->x;
}
inline int Bomb::gety()
{
	return this->y;
}
inline int Bomb::bomb_clock()
{
	return this->t;
}
inline void Bomb::bomb_clock_minus()//爆炸倒计时 
{
	this->t = this->t - 1;
	return;
}
void Bomb::blow()
{
	int x = this->x, y = this->y;
	g[x][y] = '&';
	if(xp == x && yp == y)
		{
			P.hurt(this->damage);
		}
	for (int i = x + 1 ; i <= min(x + 2, 14); i++)
		{
			if(xp == i && yp == y)
			{
				P.hurt(this->damage);
			}
			if(g[i][y] == ' ')
				g[i][y] = '|';
			if(g[i][y] == '*')
				{
					g[i][y] = '|';
					break;
				}
			if(g[i][y] == '#')
				break;
		}
	for (int i = x - 1 ; i >= max(x - 2, 0); i--)
		{
			if(xp == i && yp == y)
			{
				P.hurt(this->damage);
			}
			if(g[i][y] == ' ')
				g[i][y] = '|';
			if(g[i][y] == '*')
				{
					g[i][y] = '|';
					break;
				}
			if(g[i][y] == '#')
				break;
		}
	for (int i = y + 1 ; i <= min(y + 2, 14); i++)
		{
			if(xp == x && yp == i)
			{
				P.hurt(this->damage);
			}
			if(g[x][i] == ' ')
				g[x][i] = '-';
			if(g[x][i] == '*')
				{
					g[x][i] = '-';
					break;
				}
			if(g[x][i] == '#')
				break;
		}
	for (int i = y - 1 ; i >= max(y - 2, 0); i--)
		{
			if(xp == x && yp == i)
			{
				P.hurt(this->damage);
			}
			if(g[x][i] == ' ')
				g[x][i] = '-';
			if(g[x][i] == '*')
				{
					g[x][i] = '-';
					break;
				}
			if(g[x][i] == '#')
				break;
		}
}

class BombRemove
{
	private:
		int x, y, t;
	public:
		BombRemove()
		{x = -1;y = -1;t = -1;}
		BombRemove(int x1,int y1,int t1)
		:x(x1),y(y1),t(t1)
		{}//构造函数
		~BombRemove()//析构函数 
		{
			return;
		} 
		void bombremove();
		int clear_clock();
		void clear_clock_minus();
};
inline int BombRemove::clear_clock()
{
	return this->t;
}
inline void BombRemove::clear_clock_minus()
{
	this->t = this->t - 1;
	return;
}
void BombRemove::bombremove()//清除光束的函数 
{
	int x = this->x, y = this->y;
	g[x][y] = ' ';
	for (int i = x + 1 ; i <= min(x + 2, 14); i++)
		{
			if(g[i][y] == '|')
				g[i][y] = ' ';
			if(g[i][y] == '#')
				break;
		}
	for (int i = x - 1 ; i >= max(x - 2, 0); i--)
		{
			if(g[i][y] == '|')
				g[i][y] = ' ';
			if(g[i][y] == '#')
				break;
		}
	for (int i = y + 1 ; i <= min(y + 2, 14); i++)
		{
			if(g[x][i] == '-')
				g[x][i] = ' ';
			if(g[x][i] == '#')
				break;
		}
	for (int i = y - 1 ; i >= max(y - 2, 0); i--)
		{
			if(g[x][i] == '-')
				g[x][i] = ' ';
			if(g[x][i] == '#')
				break;
		}
}
//再考虑制作玩家类:
Bomb b[10];
BombRemove br[10];
int nb, nbr;//队列元素首尾！ 


inline int Player::get_h()
{
	return this->health;
}
inline void Player::hurt(int d)
{
	this->health = this->health - d;
	return;
}
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
		return;//若不能走，则直接返回即可，不需要更新位置坐标 
	g[this->x][this->y] = ' ';
	g[x][y] = '@';
	this->x = x;
	this->y = y;
	xp = x;
	yp = y;
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
void Player::setBomb()
{
	Bomb bomb(this->x, this->y, 4, '&', 1);
	b[++nb] = bomb;
	BombRemove clearbomb(this->x, this->y, 6);
	br[++nbr] = clearbomb;
//	bomb.blow();
}
//两个时间队列。 





void deal_with_input()
{
	if(_kbhit())//检测输入情况 
	{
		char ch;
		ch = _getch();
	//	cout << ch << endl;
		if(ch != ' ')
			P.move(ch);
		else
			P.setBomb();
		return;
	}
}
int count = 0;
/*
考虑时间有关的部分：
（1）炸弹爆炸的延时 设置2s 
（2）炸弹爆炸光束的消失 设置3s 
（3）玩家移动：不能连按，每移动一次把标记关掉0.3s！  
方法：各自开一个队列！ 

*/
bool flag = true;
void deal_with_time()
{
	//炸弹爆炸部分 
	for (int i = 1 ; i <= nb ; i++)
		{
			b[i].bomb_clock_minus();
			if(b[i].bomb_clock() == 0)
				{
					b[i].blow();
					for (int j = i + 1 ; j <= nb ; j++)
						b[j - 1] = b[j];
					nb--;
				}
			else
				{
					g[b[i].getx()][b[i].gety()] = '&';
				}
		}
	//炸弹光束清除部分 
	for (int i = 1 ; i <= nbr ; i++)
		{
			br[i].clear_clock_minus();
			if(br[i].clear_clock() == 0)
				{
					br[i].bombremove();
					for (int j = i + 1 ; j <= nbr ; j++)
						br[j - 1] = br[j];
					nbr--;
				}
		}
	if(P.get_h() == 0)
		{
			flag = false;
		}
}
int main()
{
	g[3][11] = '@';
	display();
	while(1)
	{
		deal_with_input();
		count++;
		if(count == 1500)
			{
				deal_with_time();
				display();
				printf("\n Your Blood is : %d \n", P.get_h());
				if(!flag)
					{
						printf("\n YOU DIED!!!\n");
						return 0;
					}
				count = 0;
			}
	}
		return 0;
}
