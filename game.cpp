#include <conio.h>
#include <iostream>
#include <windows.h>
#include <cstring>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
const int ONE_SECOND = 1e6;

class Bomb
{
	private:
		int x, y;//���������
		int t;//ʣ��ı�ըʱ�䡣 
		char symbol;//ը���ķ��ű��
		int damage;
		int own;
	public:
		Bomb()
		{x = -1;y = -1;t = -1;symbol = '&';damage = 1;own = 0;}
		Bomb(int x1,int y1,int ti,char ch,int d,int val)
		:x(x1),y(y1),t(ti),symbol(ch),damage(d),own(val)
		{}//���캯��
		~Bomb()//�������� 
		{
			return;
		} 
		void blow();//��ը���� 
		void bomb_clock_minus();
		int bomb_clock();
		int getx();
		int gety();
		int getd();
		int gett();
		void hurt(int x1, int x2);
};

class Player
{
private:
	int x, y;
	char sym;//�ַ���ʾ��ҵ���ʾ��ʽ 
	int health;
	int type;
	int d;
	int block;
	int score;
public:
	Player(int x1, int y1, char ch, int h,int ty,int da,int b,int val)	//���캯��������һ����� 
	:x(x1),y(y1),sym(ch),health(h),type(ty),d(da),block(b),score(val)
	{}
	~Player()//��������
	{
		return;
	}
	void P1_move(char t);//�ƶ����� 
	void P2_move(char t);//�ƶ����� 
	void upd_pos(int x1,int y1);//������º�������Ԫ��(x1,y1)������ı��Ȩֵ����Ϊ���֣�
	//��(-1,0),��(1,0),��(0,-1),��(0,1) 
	int get_x();//���x����
	int get_y();
	void setBomb();
	void hurt(int d);
	int get_h();
	void upd_d();
	void upd_s();
	int get_b();
	void upd_score(int v);
	int get_score();
};

class robot
{
	private:
  int x, y;
  int health;
  public:
  robot(int x1,int y1,int h)
	:x(x1),y(y1),health(h)
	{}
	~robot()
	{ return; }
  	void setBomb();
	bool check();
	void move(char t);
  	bool upd_pos(int x1,int y1);
	int get_x(){
	return this->x;
		}
	int get_y(){
	return this->y;
	}
	int get_h();
	void hurt(int d);
	void action();
};
Player P1(3, 11, '@', 2, 1, 1, 5000, 0);
Player P2(8,11, 'X', 2, 2, 1, 5000, 0);
robot R1(4,4,2);
robot R2(9,3,2);
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
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
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

inline int Bomb::gett()
{
	return this->t;
}
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
inline void Bomb::bomb_clock_minus()//��ը����ʱ 
{
	this->t = this->t - 1;
	return;
}
void Bomb::hurt(int x,int y)
{
	if(P1.get_x() == x && P1.get_y() == y && P1.get_h() != 0)
		{
			P1.hurt(1);
			P1.upd_score(-200);
			if(this->own == 2)
				P2.upd_score(100);
		}
	if(P2.get_x() == x && P2.get_y() == y && P2.get_h() != 0)
		{
			P2.hurt(1);
			P2.upd_score(-200);
			if(this->own == 1)
				P1.upd_score(100);
		}
	if(R1.get_x() == x && R1.get_y() == y && R1.get_h() > 0)
		{
			R1.hurt(1);
			if(this->own == 1)
				P1.upd_score(100);
			if(this->own == 2)
				P2.upd_score(100);
		}
	if(R2.get_x() == x && R2.get_y() == y && R2.get_h() > 0)
		{
			R2.hurt(1);
			if(this->own == 1)
				P1.upd_score(100);
			if(this->own == 2)
				P2.upd_score(100);
		}
}
void Bomb::blow()
{
	int d = this->damage;
	int x = this->x, y = this->y;
	g[x][y] = '&';
	this->hurt(x, y);
	for (int i = x + 1 ; i <= min(x + d, 14); i++)
		{
			this->hurt(i , y);
			if(g[i][y] == ' ')
				g[i][y] = '|';
			if(g[i][y] == '*')
				{
					if(this->own == 1)
						P1.upd_score(10);
					if(this->own == 2)
						P2.upd_score(10);
					g[i][y] = '|';
					int tmp = rand();
					tmp %= 5;
					if(tmp == 1)
						g[i][y] = '1';
					if(tmp == 2)
						g[i][y] = '2';
					break;
				}
			if(g[i][y] == '#')
				break;
		}
	for (int i = x - 1 ; i >= max(x - d, 0); i--)
		{
			this->hurt(i , y);
			if(g[i][y] == ' ')
				g[i][y] = '|';
			if(g[i][y] == '*')
				{
				if(this->own == 1)
						P1.upd_score(10);
				if(this->own == 2)
						P2.upd_score(10);
					g[i][y] = '|';
					int tmp = rand();
					tmp %= 5;
					if(tmp == 1)
						g[i][y] = '1';
					if(tmp == 2)
						g[i][y] = '2';
					break;
				}
			if(g[i][y] == '#')
				break;
		}
	for (int i = y + 1 ; i <= min(y + d, 14); i++)
		{
			this->hurt(x , i);
			if(this->own == 1)
					P1.upd_score(10);
			if(this->own == 2)
					P2.upd_score(10);
			if(g[x][i] == ' ')
				g[x][i] = '-';
			if(g[x][i] == '*')
				{
					if(this->own == 1)
						P1.upd_score(10);
					if(this->own == 2)
						P2.upd_score(10);
					g[x][i] = '-';
					int tmp = rand();
					tmp %= 5;
					if(tmp == 1)
						g[x][i] = '1';
					if(tmp == 2)
						g[x][i] = '2';
					break;
				}
			if(g[x][i] == '#')
				break;
		}
	for (int i = y - 1 ; i >= max(y - d, 0); i--)
		{
			this->hurt(x , i);
			if(this->own == 1)
					P1.upd_score(10);
			if(this->own == 2)
					P2.upd_score(10);
			if(g[x][i] == ' ')
				g[x][i] = '-';
			if(g[x][i] == '*')
				{
					if(this->own == 1)
						P1.upd_score(10);
					if(this->own == 2)
						P2.upd_score(10);
					g[x][i] = '-';
					int tmp = rand();
					tmp %= 5;
					if(tmp == 1)
						g[x][i] = '1';
					if(tmp == 2)
						g[x][i] = '2';
					break;
				}
			if(g[x][i] == '#')
				break;
		}
}

class BombRemove
{
	private:
		int x, y, t, r;
	public:
		BombRemove()
		{x = -1;y = -1;t = -1;r=-1;}
		BombRemove(int x1,int y1,int t1,int R)
		:x(x1),y(y1),t(t1),r(R)
		{}//���캯��
		~BombRemove()//�������� 
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
void BombRemove::bombremove()//��������ĺ��� 
{
	int x = this->x, y = this->y, r = this->r;
	g[x][y] = ' ';
	for (int i = x + 1 ; i <= min(x + r, 14); i++)
		{
			if(g[i][y] == '|')
				g[i][y] = ' ';
			if(g[i][y] == '#')
				break;
		}
	for (int i = x - 1 ; i >= max(x - r, 0); i--)
		{
			if(g[i][y] == '|')
				g[i][y] = ' ';
			if(g[i][y] == '#')
				break;
		}
	for (int i = y + 1 ; i <= min(y + r, 14); i++)
		{
			if(g[x][i] == '-')
				g[x][i] = ' ';
			if(g[x][i] == '#')
				break;
		}
	for (int i = y - 1 ; i >= max(y - r, 0); i--)
		{
			if(g[x][i] == '-')
				g[x][i] = ' ';
			if(g[x][i] == '#')
				break;
		}
}
//�ٿ������������:
Bomb b[10];
BombRemove br[10];
int nb, nbr;//����Ԫ����β�� 

inline int Player::get_score()
{
	return this->score;
}
inline void Player::upd_d()
{
	this->d = this->d + 1;
	return;
}
inline void Player::upd_score(int v)
{
	this->score = this->score + v;
	return;
}
inline int Player::get_b()
{
	return this->block;
}
inline void Player::upd_s() 
{
	this->block = max(this->block - 1000, 2000);
	return;
}
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
	if(x < 0 || y < 0 || x > 14 || y > 14)
		return;//�������ߣ���ֱ�ӷ��ؼ��ɣ�����Ҫ����λ������ 
	if(g[x][y] == '*' || g[x][y] == '#')
		return;
	if(g[x][y] == '1')
	{
		this->upd_s();
		this->upd_score(20); 
	}
	if(g[x][y] == '2')
	{
		this->upd_d();
		this->upd_score(20); 
	}
	g[this->x][this->y] = ' ';
	g[x][y] = this->sym;
	this->x = x;
	this->y = y;
}
void Player::P1_move(char t) 
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
void Player::P2_move(char t) 
{
	if(t == 'i')
		upd_pos(-1,0);
	if(t == 'k')
		upd_pos(1,0);
	if(t == 'j')
		upd_pos(0,-1);
	if(t == 'l')
		upd_pos(0,1);
	return;
}
void Player::setBomb()
{
	Bomb bomb(this->x, this->y, 4, '&', this->d, this->type);
	b[++nb] = bomb;
	BombRemove clearbomb(this->x, this->y, 6, this->d);
	br[++nbr] = clearbomb;
//	bomb.blow();
}
//����ʱ����С� 





bool robot::upd_pos(int x1,int y1)
{
	int x = this->get_x() + x1, y = this->get_y() + y1;
  if(x < 0 || x > 14 || y < 0 || y > 14 || g[x][y] == '*' || g[x][y] == '#')
			return false;
	g[this->x][this->y] = ' ';
	g[x][y] = '%';
	this->x = x;
	this->y = y;	
	return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}

void robot::move(char t)//simple move
{
	if(t == 'w')
		this->upd_pos(-1,0);
	if(t == 's')
		this->upd_pos(1,0);
	if(t == 'a')
		this->upd_pos(0,-1);
	if(t == 'd')
		this->upd_pos(0,1);
	return;
}
void robot::action()
{
	if(check())
		return;//����Ѿ������ˣ�ֱ�ӷ��ء�
	else
		{
			int dir = rand() % 5, rdBomb = rand() % 10;
			if(rdBomb == 1)
			{
				this->setBomb();
				return; 
			}
			else
				{
					if(dir == 0)
						return;
					if(dir == 1)
						{
							move('w');
							return;
						}
					if(dir == 2)
						{
							move('a');
							return;
						}
					if(dir == 3)
						{
							move('s');
							return;
						}
					if(dir == 4)
						{
							move('d');
							return;
						}
				}
		 } 
}
bool robot::check()//�����ǵ�һ���Ե�ǰ״̬����в��ը�����б���в�Ŀ��ܾ��� 
//û�б���в�Ŀ��ܣ�������ƶ��� 
//����ƶ�һ�����򣬻��߷�ը���� 
{
	Bomb tmp;
	int val = 5;
	int x = this->x, y = this->y;
	for (int i = 1 ; i <= nb; i++)
		{
				int x1 = b[i].getx(), y1 = b[i].gety(), r = b[i].getd();
				if(x1 == x && (y <= y1 + r && y >= y1 - r)) //��ͬһ�����꣬���һᱻ������ 
					{
						//�ȿ����������ƶ�
						//�ٿ����������ƶ�
						if(upd_pos(-1,0) || upd_pos(1,0))
							return true;
						if(y <= y1 && upd_pos(0,-1))
							return true;
						if(y > y1 && upd_pos(0,1))
							return true;
					}
				 if(y1 == y && (x <= x1 + r && x >= x1 - r))
				 	{
				 		if(upd_pos(0,1) || upd_pos(0,-1))
							return true;
						if(x <= x1 && upd_pos(-1,0))
							return true;
						if(x > x1 && upd_pos(1,0))
							return true;
					 }
	  }
	return false;
}

void robot::setBomb()
{
	Bomb bomb(this->x, this->y, 4 , '&', 1, 0);
	b[++nb] = bomb;
	BombRemove clearbomb(this->x, this->y, 6, 1);
  	br[++nbr] = clearbomb;
}
inline int robot::get_h()
{
	return this->health;
}
inline void robot::hurt(int d)
{
	this->health = this->health - d;
	return;
}

bool flag1 = true, flag2 = true;
void deal_with_input()
{
	if(_kbhit())//���������� 
	{
		char ch;
		ch = _getch();
	//	cout << ch << endl;
		if(P1.get_h() != 0 && flag1 && (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == ' '))
		{
		if(ch != ' ')
			P1.P1_move(ch);
		else
			P1.setBomb();
		flag1 = false;
		}
		if(P2.get_h() != 0 && flag2 && (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 13))
		{
		if(ch != 13)
			P2.P2_move(ch);
		else
			P2.setBomb();
		flag2 = false;
		}
		return;
	}
}
int count = 0;
/*
����ʱ���йصĲ��֣�
��1��ը����ը����ʱ ����2s 
��2��ը����ը��������ʧ ����3s 
��3������ƶ�������������ÿ�ƶ�һ�ΰѱ�ǹص�0.3s��  
���������Կ�һ�����У� 
*/
bool flag = true, win = false;
void deal_with_time()
{
	//ը����ը���� 
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
	//ը������������� 
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
}
int main()
{
	g[3][11] = '@';
	g[8][11] = 'X';
	g[9][3] = '%';
	g[4][4] = '%';
	display();
	while(1)
	{
		deal_with_input();
		count++;
		if(count % P1.get_b() == 0)
			{
				flag1 = true;
			}
		if(count % P2.get_b() == 0)
			{
				flag2 = true;
			}
		if(count == 10000)
			{
				deal_with_time();
				display();
				if(P1.get_h())
					printf("\n P1 Blood is : %d \n", P1.get_h());
				if(P2.get_h())
					printf("\n P2 Blood is : %d \n", P2.get_h());
				if(R1.get_h())
					printf("\n R1 's Blood is : %d \n", R1.get_h());
				if(R2.get_h())
					printf("\n R2 's Blood is : %d \n", R2.get_h());
				printf("\n P1 Total Score is : %d \n", P1.get_score());
				printf("\n P2 Total Score is : %d \n", P2.get_score());
				if(P1.get_h() == 0)
					{
						printf("\n P1 DIED!!!\n");
					}
				if(P2.get_h() == 0)
					{
						printf("\n P2 DIED!!!\n");
					}
				if(R1.get_h() == 0 && R2.get_h() == 0)
					{
						printf("\n YOU WIN!!!\n");
						break;
					}
				if(P1.get_h() == 0 && P2.get_h() == 0)
					{
						printf("\n YOU LOSE!!!\n");
						break;
					}
				count = 0;
				if(R1.get_h() > 0)
					R1.action();
				if(R2.get_h() > 0) 
					R2.action();
			}
		
	}
		return 0;
}
