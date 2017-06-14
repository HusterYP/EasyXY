/***********************************************
                ������Ϸ����
                  --Con_Techer
1.��ʼ�����������棬���֣�������ɳ�ʼλ��
2.��ͼ�ͻ���
3.��ʼ�棺��ȡ�����Ϣ
4.�ж���Ӯ
************************************************/

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsyscom.h>
#pragma comment(lib,"winmm.lib")

//ȫ�ֱ���
int num[7][7] = { 0 }; //Ҫ���һȦ,5*5
int  i, j; 
IMAGE black, white;
MOUSEMSG Msg;//�����Ϣ

//��������
void Intial();
void Draw();
void Play(int, int);
bool Judge();
void Begain();

int main()
{
	srand(time(NULL));
	Begain();
	_getch(); //����ģ�ⰴ��������������ã������_kbhit()�����У�
	cleardevice();
	Intial();
	Draw();
	while (1)
	{
		FlushBatchDraw();//��ֹ��ͼʱ������
		Msg = GetMouseMsg();
		if (Msg.mkLButton == true)//���������½���(���������ֱ����WM_LBUTTONDOWN����Ϊ�����Msg.uMsg�еģ����ﲢδ��uMsg)
		{
			Play((int)Msg.x, (int)Msg.y);
			cleardevice();
		}
		Draw();
		BeginBatchDraw();
		if (Judge() == true) //����ɹ��ͽ���
		{
			if (MessageBox(0, "��ϲ�㣬��Ӯ�ˣ�", "�Ƿ�����һ�֣�", MB_YESNO) == IDYES)
			{
				//״̬����
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

//��ʼ��
void Intial()
{
	//i,j�ķ�Χ��1-5
	i = rand() % 4 + 1;
	j = rand() % 4 + 1;
	num[i][j] = 1;
	//����ͼƬ
	loadimage(&black, "black.jpg", 160, 160);
	loadimage(&white, "white.jpg", 160, 160);
}
//��ͼ
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
	//����
	for (int i = 1; i < 6; i++)
	{
		line(0, 160 * (i - 1), 800, 160 * (i - 1));
		line(160 * i, 0, 160 * i, 800);
	}
}
//��ʼ����Ϸ,�����ʱ��ʼ����
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
//�ж��Ƿ�ɹ�
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
//��ʼ����Ϸ˵��
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
	settextstyle(50,0,"���Ĳ���");
	outtextxy(50, 200, "��Ϸ˵�� ��");
	settextstyle(30, 0, "����");
	outtextxy(100, 300, "��������ӣ����Ӽ����������ҵĸ�����ɫ���ı�");
	outtextxy(100, 400, "ֱ�����еĸ��Ӷ���Ϊͬһ����ɫ");
	settextstyle(50, 0, "���Ĳ���");
	outtextxy(300, 600, "�������������Ϸ....");
}



