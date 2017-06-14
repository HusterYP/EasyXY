/*
2048 游戏开发
Win32控制台  图形库
1.外部展示部分
2.内在部分 游戏过程
载体 数组
1.随机生成 2
2.操作 用户输入wasd
3.执行操作
4.判断输赢 赢 2048
输 格子满掉   不能移动

---Huster
*/

#include<stdio.h>
#include<time.h>  //生成随机数
#include<conio.h> // getch()函数  （不同于getchar()）
#include<graphics.h> //图形库 生成界面
#include<stdlib.h>

void game();
void show(int map[][5]);
void fun(int &a,int &b,int &c,int &d);  //操作wasd,形参无法改变实参，故用引用做，也可以用指针

int main()
{
	initgraph(640,640);   //建立一个窗口
	setbkmode(TRANSPARENT);  //也可以setbkmode(1),设置背景透明，不然的话在字体后面会有一个黑框
	settextstyle(32, 0, "黑体");//设置字体样式
	settextcolor(LIGHTRED); //设置字体颜色，有一个表
	while (1)
	{
		game();
		if (MessageBox(0, "是否要放弃2048","放弃继续？", MB_YESNO) == IDOK)
			break;
	}
	closegraph();      //关闭窗口
	return 0;
}

void game()
{
	int map[5][5] = { 0 };   //地图，数组
	int i, j;      // 作为坐标使用
	int  flag = 1;
	int flag2 = 0;
	srand((unsigned)time(NULL));
	while (1)  //循环玩游戏
	{
		if (flag == 1)
		{
			do
			{
				i = rand() % 4;
				j = rand() % 4;  //随机生成一个坐标

			} while (map[i][j] != 0);  //当随机生成的位置处不是0时要再次生成位置，只有该处位0时才能进行map[i][j] = 2; 
			//if(rand()%2==0)  随机生成2和4
			map[i][j] = 2;
			show(map);
		}

// 操作wasd方向不同，内容一样，故用一个函数
		switch (_getch())   // C++中要用_getch()
		{
		case 'W':   //上移
		case 'w':
			/*for (j = 0; j < 4; j++)
			{
				fun(map[0][j], map[1][j], map[2][j], map[3][j]);
			}*/
			for (i = 0; i < 4; i++)
			{
			fun(map[i][0], map[i][1], map[i][2], map[i][3]);
			}
			break;

		case 'A':   //左移
		case 'a':
			for (j = 0; j < 4; j++)
			{
				fun(map[0][j], map[1][j], map[2][j], map[3][j]);
			}
			/*for (i = 0; i < 4; i++)
			{
				fun(map[i][0], map[i][1], map[i][2], map[i][3]);
			}*/
			break;

		case 'S':   //下移
		case 's':
			/*for (j = 0; j < 4; j++)
			{
				fun(map[3][j], map[2][j], map[1][j], map[0][j]);
			}*/
			for (i = 0; i < 4; i++)
			{
			fun(map[i][3], map[i][2], map[i][1], map[i][0]);
			}
			break;

		case 'D':   //右移
		case 'd':
			///*for (i = 0; i < 4; i++)
			//{
			//	fun(map[i][3], map[i][2], map[i][1], map[i][0]);
			//}*/
			for (j = 0; j < 4; j++)
			{
				fun(map[3][j], map[2][j], map[1][j], map[0][j]);
			}
			break;

		default:
			break;
		}

		//判断输赢
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (map[i][j] >= 2048)  //赢，不用判断输了
					//这里要跳出大循环（最好不要用goto），容易使代码错乱
					//可以用return，但是这里只要求跳出大循环，不要求退出主函数，故重新编写一个函数

				{
					show(map);
					MessageBox(0, "你赢了", "NICE", MB_OK);  //屏幕上显示赢了的内容
					return;
				}
			}
		}


		flag = 0;  //先赋值为0，以便判断是否满了
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			if (map[i][j] == 0)  //还没输
			{
				flag = 1;
			}

		}

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (map[i][j] == map[i][j + 1] || map[i][j] == map[i + 1][j])  // 有就没有输
				{
					flag2 = 1;  //表示还没有输
				}
			}
		}
		if (flag || flag2)   //只要有一个成立，就可以继续玩
		{
			continue;
		}
		else // 输了
		{
			show(map);
			MessageBox(0, "你输了", "SORRY", MB_OK);
			return;
		}
	}
}

//展示内容
void show(int map[][5])
{
	IMAGE img;
	loadimage(&img, "1.jpg", 640, 640);  //加载照片，照片必须放在程序文件夹下，照片名为"1.jpg"
	putimage(0, 0, &img);
	char num[7];
	int i, j;
	for (i = 0; i < 4; i++)
	{
		line(0, 160 * i, 640, 160 * i);
		line(160 * i, 0, 160 * i, 640);
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			//数组每次要清0
			for (int k = 0; k < 7; k++)
			{
				num[k] = '\0';
			}
			sprintf_s(num, "%d", map[i][j]);
			outtextxy(i * 160 + 40, j * 160 + 40, num);  //指定位置输出函数
			//printf("%3d", map[i][j]);
		}
		//printf("\n");
	}
	//printf("-----------------分界线--------------------\n");
}

void fun(int &a, int &b, int &c, int &d)
{
	//排掉中间的0，更好操作，用类似冒泡法
	int arr[4] = { a, b, c, d };  //初始化数组
	int brr[4] = { 0 };   // 排掉0的数组
	int  i, j;
	for (i = 0, j = 0; i < 4; i++)
	{
		if (arr[i] != 0)
		{
			brr[j++] = arr[i];   // 使0全部到后面
		}
	}
		//合并操作
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (brr[j] == brr[j + 1])
				{
					brr[j] = brr[j] * 2;
					//brr[j+1] = 0移到后面去
					for (int k = j + 1; k < 3; k++)
					{
						brr[k] = brr[k + 1];
					}
					brr[3] = 0; //把最后一个赋值为0
				}
			}
		}
	a = brr[0];
	b = brr[1];
	c = brr[2];
	d = brr[3];

}