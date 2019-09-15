#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define U 1
#define D 2
#define L 3
#define R 4

typedef struct BODY
{
	int x;
	int y;
	struct BODY *next;
} body;

using namespace std;

int score = 0, add = 10;         //分數
int status, sleeptime = 200;     //响应时间
body *q;                         //临时存放
body *food, *head;               //头，食物
int flag = 0;                    //1为撞墙 2为咬到自己 3自己退

void Pos();
void creatMap();   
void initSnake();   
void createFood();  
void hitWall();     
void snakeMove();   
void pause();       
void runGame();     
void endGame();     
void initGame();    
void gameStart();  

int biteSelf();

int main()
{
	gameStart();
	runGame();
	endGame();

	return 0;
}

void Pos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;

	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获得句柄

	SetConsoleCursorPosition(hOutput, pos);
}

void creatMap()
{
	for (int i = 0; i < 58; i += 2)
	{
		Pos(i, 0);
		printf("■");

		Pos(i, 26
);
		printf("■");
	}

	for (int i = 1; i < 26; i++)
	{
		Pos(0, i);
		printf("■");

		Pos(56, i);
		printf("■");
	}
}

void initSnake()//从尾开始 插蛇身
{
	body *tail;

	tail = (body *)malloc(sizeof(body));
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;

	for (int i = 1; i <= 4; i++)//初始长度 4
	{
		head = (body *)malloc(sizeof(body));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	
	while (tail != NULL)
	{
		Pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

void createFood()//随机出现食物
{
	body *food_1;

	srand(time(NULL));

	food_1 = (body*)malloc(sizeof(body));

	while ((food_1->x % 2) != 0)    //保证其为偶数，使得食物能与蛇头对其
	{
		food_1->x = rand() % 52 + 2;
	}

	food_1->y = rand() % 24 + 1;

	q = head;

	while (q->next == NULL)
	{
		if (q->x == food_1->x && q->y == food_1->y) //判断蛇身是否与食物重合
		{
			free(food_1);
			createFood();
		}
		q = q->next;
	}

	Pos(food_1->x, food_1->y);
	food = food_1;

	printf("■");
}

void hitWall()//不能穿墙
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		flag = 1;
		endGame();
	}
}

void snakeMove()  //蛇前进,上U,下D,左L,右R
{
	body * nexthead;
	hitWall();

	nexthead = (body*)malloc(sizeof(body));

	if (status == U)                            //连续重复4个方向
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food->x && nexthead->y == food->y)//如果下一个有食
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else                                               //如果没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food->x && nexthead->y == food->y)  //有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else                               //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else                                //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createFood();
		}
		else                                         //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteSelf() == 1)       //判断是否会咬到自己
	{
		flag = 2;
		endGame();
	}
}

void pause()
{
	while (1)
	{
		Sleep(300);

		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}

void runGame()//控制游戏        
{
	Pos(64, 15);
	printf("不能撞到墙壁，不能咬到自己\n");

	Pos(64, 16);
	printf("用↑.↓.←.→分别控制蛇的移动。");

	Pos(64, 17);
	printf("F1 为加速，F2 为减速\n");

	Pos(64, 18);
	printf("ESC ：退出游戏。 SPACE ：暂停游戏。");

	Pos(64, 20);
	printf("神兽出品！！");

	status = R;

	while (1)
	{
		Pos(64, 10);
		printf("得分：%d  ", score);

		Pos(64, 11);
		printf("每个食物得分：%d分", add);

		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}

		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}

		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}

		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}

		else if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}

		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 3;
			break;
		}

		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				sleeptime = sleeptime - 30;
				add = add + 2;
				if (sleeptime == 320)
				{
					add = 2;//防止减到1之后再加回来有错
				}
			}
		}

		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime < 350)
			{
				sleeptime = sleeptime + 30;
				add = add - 2;
				if (sleeptime == 350)
				{
					add = 1;  //保证最低分为1
				}
			}
		}

		Sleep(sleeptime);

		snakeMove();
	}
}

void initGame()//开始界面
{
	Pos(40, 12);

	system("title Happy snake.");

	printf("欢迎来到贪吃蛇游戏！");

	Pos(40, 25);
	printf("  嘿嘿嘿 我是神兽\n");

	system("pause");
	system("cls");

	Pos(25, 12);
	printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，F2 为减速\n");

	Pos(38, 13);
	printf("加速将能得到更高的分数。\n");

	putchar('\n'); putchar('\n'); putchar('\n'); putchar('\n'); putchar('\n'); 
	putchar('\n'); putchar('\n'); putchar('\n'); putchar('\n'); putchar('\n');

	system("pause");
	system("cls");
}

void endGame()//结束游戏
{
	system("cls");
	Pos(24, 12);

	if (flag == 1)
	{
		printf("对不起，您撞到墙了。游戏结束。");
	}

	else if (flag == 2)
	{
		printf("对不起，您咬到自己了。游戏结束。");
	}

	else if (flag == 3)
	{
		printf("您已经结束了游戏。");
	}

	Pos(24, 13);
	printf("您的得分是%d。\n", score);

	while (getchar() != 'y')
	{
		printf("按 Y 然后回车 关闭。");
	}

	exit(0);
}

void gameStart()//游戏初始化
{
	system("mode con cols=100 lines=30");
	initGame();
	creatMap();
	initSnake();
	createFood();
}

int biteSelf()
{
	body *self;
	
	self = head->next;

	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)
		{
			return 1;
		}
		self = self->next;
	}

	return 0;
}
