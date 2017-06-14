/***************************** 
       五子棋游戏开发
	   --Con_Techer
******************************/
#include<stdio.h>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")

//全局变量
//byte n = 0;//位域，黑白棋子要交替出现，但是这里好像有问题，只能出现两个棋子，难道是只能用在结构体中？
int n = 0;
IMAGE Chess[2];//存储黑白棋子
int Num[25][25] = { 0 }; //本来是15*15的，但是为了判断，在周围加一圈
int i, j;//记录棋子位置

//函数申明区
void Welcome();
void Textput();
void Draw();
void Play(int,int);
int Decta(int, int);

int main()
{
	//加载棋子
	loadimage(&Chess[0], "./white.jpg", 50, 50);
	loadimage(&Chess[1], "./black.jpg", 50, 50);
	Welcome();
	Textput();
	Draw();
	MOUSEMSG Ms;
	while (1)
	{
		Ms = GetMouseMsg();
		if (Ms.x >= 25 && Ms.x <= 825 && Ms.y >= 25 && Ms.y <= 825) //防止数组越界
		{
			if (Ms.mkLButton == true) //左键按下
			{
				Play(Ms.x, Ms.y);
			}
		}
		if (Decta(i, j)==1)
		{
			if (MessageBox(0, "是否再来一局","恭喜你", MB_YESNO) == IDNO)
				break;
			else
			{
				cleardevice();
				Draw();
				for (int k = 0; k < 25; k++)
				{
					for (int m = 0; m < 25; m++)
						Num[k][m] = 0;
				}
				i = 0; j = 0;
			}
		}
	}
	//setorigin(50, 50);// 设置坐标原点,但是这里不能重置坐标原点，因为要改变数组
	//测试程序：在屏幕上显示当前鼠标位置
	/*MOUSEMSG Ms;
	while (1)
	{
		Ms = GetMouseMsg();
		char str[50];
		sprintf_s(str, "(%d,%d)", Ms.x, Ms.y);
		outtextxy(400, 600, str);
		cleardevice();
	}*/
	closegraph();
	return 0;
}
//初始化并加载图片
void Welcome()
{
	IMAGE Img;
	//初始化界面
	initgraph(850, 850);
	mciSendString("open ./music.mp3 alias bk", 0, 0, 0);
	mciSendString("play bk repeat", 0, 0, 0);
	loadimage(&Img, "./begain1.jpg", 850, 850);
	putimage(0, 0, &Img);
	getchar();//按任意键继续
}
//文字说明:如何设置文字动画
void Textput()
{
	cleardevice();
	settextstyle(50, 0, "隶书");
	settextcolor(YELLOW);
	outtextxy(250, 100, "话说天下大事");
	Sleep(800);
	outtextxy(300, 180, "分久必合");
	Sleep(800);
	outtextxy(300, 260, "合久必分");
	Sleep(800);
	outtextxy(300, 340, "群雄逐鹿");
	Sleep(800);
	outtextxy(300, 420, "谁主中原");
	Sleep(500);
	settextstyle(30, 0, "楷体");
	settextcolor(RGB(128, 0, 255));
	outtextxy(400, 750, "按任意键开始游戏......");
	getchar();
}
//画棋盘并加载所需图片
void Draw()
{
	//由于最终的图片格子不标准，贴图有误差，故选择自己画格子
	//IMAGE Img;
	//loadimage(&Img, "./棋盘.jpg", 800, 800);
	//putimage(0, 0, &Img);
	cleardevice();
	setbkcolor(RGB(200, 200, 100));
	cleardevice(); //注意设置好背景颜色后还要用一次cleardevice表示用该颜色去刷新背景
	setbkmode(TRANSPARENT);
	setlinestyle(0,2,0,1);//第一个参数是改变颜色，第二个是改变粗细，第三个为NULL，第四个为改变虚线实线
	setlinecolor(BLACK);
	for (int i = 1; i <= 16; i++)
	{
		line(50, i * 50, 800, i * 50); //画横线
		line(i * 50, 50, i * 50, 800);//画竖线
	}
	setlinestyle(0, 4, 0, 1);//改变四周的线粗细
	line(50, 50, 800, 50);
	line(50, 50, 50, 800);
	line(50, 800, 800, 800);
	line(800, 50, 800, 800);
}
//开始玩游戏（醉了）
void Play(int x,int y)
{
	i = (y - 25) / 50;
	j = (x - 25) / 50;
	if (Num[i][j] == 0)
	{
		Num[i][j] = 1;
		putimage(j * 50 + 25, i * 50 + 25, &Chess[n]);
		n = !n;//状态反转
	}
}
//判断游戏是否结束
int Decta(int x,int y)
{
	int flag = 0;//有八个方向要判断
	if (Num[x][y] == 1 && Num[x - 1][y] == 1 && Num[x - 2][y] == 1 && Num[x - 3][y] == 1 && Num[x - 4][y] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x + 1][y] == 1 && Num[x + 2][y] == 1 && Num[x + 3][y] == 1 && Num[x + 4][y] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x][y-1] == 1 && Num[x][y-2] == 1 && Num[x][y-3] == 1 && Num[x][y-4] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x][y + 1] == 1 && Num[x][y + 2] == 1 && Num[x][y + 3] == 1 && Num[x][y + 4] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x-1][y - 1] == 1 && Num[x-2][y - 2] == 1 && Num[x-3][y - 3] == 1 && Num[x-4][y - 4] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x+1][y + 1] == 1 && Num[x+2][y + 2] == 1 && Num[x+3][y + 3] == 1 && Num[x+4][y + 4] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x - 1][y+1] == 1 && Num[x - 2][y+2] == 1 && Num[x - 3][y+3] == 1 && Num[x - 4][y+4] == 1)
		flag = 1;
	if (Num[x][y] == 1 && Num[x+1][y - 1] == 1 && Num[x+2][y - 2] == 1 && Num[x+3][y - 3] == 1 && Num[x+4][y - 4] == 1)
		flag = 1;
	if (flag == 1)
		return 1;
	else
		return 0;
}