/***********************************************
                生命游戏开发
                  --Con_Techer
1.初始化：创建界面，音乐，随机生成初始位置
2.贴图和划线
3.开始玩：获取鼠标消息
4.判断输赢
************************************************/

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsyscom.h>
#pragma comment(lib,"winmm.lib")

//全局变量
int num[7][7] = { 0 }; //要多加一圈,5*5
int  i, j; 
IMAGE black, white;
MOUSEMSG Msg;//鼠标消息

//函数申明
void Intial();
void Draw();
void Play(int, int);
bool Judge();
void Begain();

int main()
{
	srand(time(NULL));
	Begain();
	_getch(); //可以模拟按任意键继续的作用（这里的_kbhit()好像不行）
	cleardevice();
	Intial();
	Draw();
	while (1)
	{
		FlushBatchDraw();//防止贴图时的闪屏
		Msg = GetMouseMsg();
		if (Msg.mkLButton == true)//鼠标左键按下进入(这里好像不能直接用WM_LBUTTONDOWN，因为这个是Msg.uMsg中的，这里并未用uMsg)
		{
			Play((int)Msg.x, (int)Msg.y);
			cleardevice();
		}
		Draw();
		BeginBatchDraw();
		if (Judge() == true) //如果成功就进入
		{
			if (MessageBox(0, "恭喜你，你赢了！", "是否再来一局？", MB_YESNO) == IDYES)
			{
				//状态重置
				for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					num[i][j] = 0;
				Intial();
				Draw();
			}
		}
	}
	getchar();
	closegraph();
	return 0;
}

//初始化
void Intial()
{
	//i,j的范围是1-5
	i = rand() % 4 + 1;
	j = rand() % 4 + 1;
	num[i][j] = 1;
	//加载图片
	loadimage(&black, "black.jpg", 160, 160);
	loadimage(&white, "white.jpg", 160, 160);
}
//贴图
void Draw()
{
	setlinecolor(RED);
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			if (num[i][j] == 0)
			{
				putimage((j - 1) * 160, (i - 1) * 160, &white, SRCCOPY);
			}
			else
			{
				putimage((j - 1) * 160, (i - 1) * 160, &black, SRCCOPY);
			}
		}
	}
	//画线
	for (int i = 1; i < 6; i++)
	{
		line(0, 160 * (i - 1), 800, 160 * (i - 1));
		line(160 * i, 0, 160 * i, 800);
	}
}
//开始玩游戏,鼠标点击时开始进入
void Play(int x,int y)
{
	int j = x / 160 + 1;
	int i = y / 160 + 1;
	num[i][j] = !num[i][j];
	num[i-1][j] = !num[i-1][j];
	num[i+1][j] = !num[i+1][j];
	num[i][j+1] = !num[i][j+1];
	num[i][j-1] = !num[i][j-1];
}
//判断是否成功
bool Judge()
{
	int flag1 = 0, flag2 = 0;
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			if (num[i][j] == 0)
				flag1++;
			else
				flag2++;
		}
	}
	if (flag1 == 25 || flag2 == 25)
		return true;
	else
		return false;
}
//开始的游戏说明
void Begain()
{
	initgraph(800, 800);
	mciSendString("open ./music.mp3 alias bk", 0, 0, 0);
	mciSendString("play bk repeat", 0, 0, 0);
	IMAGE begain;
	loadimage(&begain,"./begain.jpg", 800, 800);
	putimage(0, 0, &begain);
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(50,0,"华文彩云");
	outtextxy(50, 200, "游戏说明 ：");
	settextstyle(30, 0, "楷体");
	outtextxy(100, 300, "鼠标点击格子，格子及其上下左右的格子颜色都改变");
	outtextxy(100, 400, "直到所有的格子都变为同一种颜色");
	settextstyle(50, 0, "华文彩云");
	outtextxy(300, 600, "按任意键进入游戏....");
}



