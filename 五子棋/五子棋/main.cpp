/***************************** 
       ��������Ϸ����
	   --Con_Techer
******************************/
#include<stdio.h>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")

//ȫ�ֱ���
//byte n = 0;//λ�򣬺ڰ�����Ҫ������֣�����������������⣬ֻ�ܳ����������ӣ��ѵ���ֻ�����ڽṹ���У�
int n = 0;
IMAGE Chess[2];//�洢�ڰ�����
int Num[25][25] = { 0 }; //������15*15�ģ�����Ϊ���жϣ�����Χ��һȦ
int i, j;//��¼����λ��

//����������
void Welcome();
void Textput();
void Draw();
void Play(int,int);
int Decta(int, int);

int main()
{
	//��������
	loadimage(&Chess[0], "./white.jpg", 50, 50);
	loadimage(&Chess[1], "./black.jpg", 50, 50);
	Welcome();
	Textput();
	Draw();
	MOUSEMSG Ms;
	while (1)
	{
		Ms = GetMouseMsg();
		if (Ms.x >= 25 && Ms.x <= 825 && Ms.y >= 25 && Ms.y <= 825) //��ֹ����Խ��
		{
			if (Ms.mkLButton == true) //�������
			{
				Play(Ms.x, Ms.y);
			}
		}
		if (Decta(i, j)==1)
		{
			if (MessageBox(0, "�Ƿ�����һ��","��ϲ��", MB_YESNO) == IDNO)
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
	//setorigin(50, 50);// ��������ԭ��,�������ﲻ����������ԭ�㣬��ΪҪ�ı�����
	//���Գ�������Ļ����ʾ��ǰ���λ��
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
//��ʼ��������ͼƬ
void Welcome()
{
	IMAGE Img;
	//��ʼ������
	initgraph(850, 850);
	mciSendString("open ./music.mp3 alias bk", 0, 0, 0);
	mciSendString("play bk repeat", 0, 0, 0);
	loadimage(&Img, "./begain1.jpg", 850, 850);
	putimage(0, 0, &Img);
	getchar();//�����������
}
//����˵��:����������ֶ���
void Textput()
{
	cleardevice();
	settextstyle(50, 0, "����");
	settextcolor(YELLOW);
	outtextxy(250, 100, "��˵���´���");
	Sleep(800);
	outtextxy(300, 180, "�־ñغ�");
	Sleep(800);
	outtextxy(300, 260, "�Ͼñط�");
	Sleep(800);
	outtextxy(300, 340, "Ⱥ����¹");
	Sleep(800);
	outtextxy(300, 420, "˭����ԭ");
	Sleep(500);
	settextstyle(30, 0, "����");
	settextcolor(RGB(128, 0, 255));
	outtextxy(400, 750, "���������ʼ��Ϸ......");
	getchar();
}
//�����̲���������ͼƬ
void Draw()
{
	//�������յ�ͼƬ���Ӳ���׼����ͼ������ѡ���Լ�������
	//IMAGE Img;
	//loadimage(&Img, "./����.jpg", 800, 800);
	//putimage(0, 0, &Img);
	cleardevice();
	setbkcolor(RGB(200, 200, 100));
	cleardevice(); //ע�����úñ�����ɫ��Ҫ��һ��cleardevice��ʾ�ø���ɫȥˢ�±���
	setbkmode(TRANSPARENT);
	setlinestyle(0,2,0,1);//��һ�������Ǹı���ɫ���ڶ����Ǹı��ϸ��������ΪNULL�����ĸ�Ϊ�ı�����ʵ��
	setlinecolor(BLACK);
	for (int i = 1; i <= 16; i++)
	{
		line(50, i * 50, 800, i * 50); //������
		line(i * 50, 50, i * 50, 800);//������
	}
	setlinestyle(0, 4, 0, 1);//�ı����ܵ��ߴ�ϸ
	line(50, 50, 800, 50);
	line(50, 50, 50, 800);
	line(50, 800, 800, 800);
	line(800, 50, 800, 800);
}
//��ʼ����Ϸ�����ˣ�
void Play(int x,int y)
{
	i = (y - 25) / 50;
	j = (x - 25) / 50;
	if (Num[i][j] == 0)
	{
		Num[i][j] = 1;
		putimage(j * 50 + 25, i * 50 + 25, &Chess[n]);
		n = !n;//״̬��ת
	}
}
//�ж���Ϸ�Ƿ����
int Decta(int x,int y)
{
	int flag = 0;//�а˸�����Ҫ�ж�
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