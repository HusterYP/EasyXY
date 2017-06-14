/*
2048 ��Ϸ����
Win32����̨  ͼ�ο�
1.�ⲿչʾ����
2.���ڲ��� ��Ϸ����
���� ����
1.������� 2
2.���� �û�����wasd
3.ִ�в���
4.�ж���Ӯ Ӯ 2048
�� ��������   �����ƶ�

---Huster
*/

#include<stdio.h>
#include<time.h>  //���������
#include<conio.h> // getch()����  ����ͬ��getchar()��
#include<graphics.h> //ͼ�ο� ���ɽ���
#include<stdlib.h>

void game();
void show(int map[][5]);
void fun(int &a,int &b,int &c,int &d);  //����wasd,�β��޷��ı�ʵ�Σ�������������Ҳ������ָ��

int main()
{
	initgraph(640,640);   //����һ������
	setbkmode(TRANSPARENT);  //Ҳ����setbkmode(1),���ñ���͸������Ȼ�Ļ�������������һ���ڿ�
	settextstyle(32, 0, "����");//����������ʽ
	settextcolor(LIGHTRED); //����������ɫ����һ����
	while (1)
	{
		game();
		if (MessageBox(0, "�Ƿ�Ҫ����2048","����������", MB_YESNO) == IDOK)
			break;
	}
	closegraph();      //�رմ���
	return 0;
}

void game()
{
	int map[5][5] = { 0 };   //��ͼ������
	int i, j;      // ��Ϊ����ʹ��
	int  flag = 1;
	int flag2 = 0;
	srand((unsigned)time(NULL));
	while (1)  //ѭ������Ϸ
	{
		if (flag == 1)
		{
			do
			{
				i = rand() % 4;
				j = rand() % 4;  //�������һ������

			} while (map[i][j] != 0);  //��������ɵ�λ�ô�����0ʱҪ�ٴ�����λ�ã�ֻ�иô�λ0ʱ���ܽ���map[i][j] = 2; 
			//if(rand()%2==0)  �������2��4
			map[i][j] = 2;
			show(map);
		}

// ����wasd����ͬ������һ��������һ������
		switch (_getch())   // C++��Ҫ��_getch()
		{
		case 'W':   //����
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

		case 'A':   //����
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

		case 'S':   //����
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

		case 'D':   //����
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

		//�ж���Ӯ
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (map[i][j] >= 2048)  //Ӯ�������ж�����
					//����Ҫ������ѭ������ò�Ҫ��goto��������ʹ�������
					//������return����������ֻҪ��������ѭ������Ҫ���˳��������������±�дһ������

				{
					show(map);
					MessageBox(0, "��Ӯ��", "NICE", MB_OK);  //��Ļ����ʾӮ�˵�����
					return;
				}
			}
		}


		flag = 0;  //�ȸ�ֵΪ0���Ա��ж��Ƿ�����
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			if (map[i][j] == 0)  //��û��
			{
				flag = 1;
			}

		}

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (map[i][j] == map[i][j + 1] || map[i][j] == map[i + 1][j])  // �о�û����
				{
					flag2 = 1;  //��ʾ��û����
				}
			}
		}
		if (flag || flag2)   //ֻҪ��һ���������Ϳ��Լ�����
		{
			continue;
		}
		else // ����
		{
			show(map);
			MessageBox(0, "������", "SORRY", MB_OK);
			return;
		}
	}
}

//չʾ����
void show(int map[][5])
{
	IMAGE img;
	loadimage(&img, "1.jpg", 640, 640);  //������Ƭ����Ƭ������ڳ����ļ����£���Ƭ��Ϊ"1.jpg"
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
			//����ÿ��Ҫ��0
			for (int k = 0; k < 7; k++)
			{
				num[k] = '\0';
			}
			sprintf_s(num, "%d", map[i][j]);
			outtextxy(i * 160 + 40, j * 160 + 40, num);  //ָ��λ���������
			//printf("%3d", map[i][j]);
		}
		//printf("\n");
	}
	//printf("-----------------�ֽ���--------------------\n");
}

void fun(int &a, int &b, int &c, int &d)
{
	//�ŵ��м��0�����ò�����������ð�ݷ�
	int arr[4] = { a, b, c, d };  //��ʼ������
	int brr[4] = { 0 };   // �ŵ�0������
	int  i, j;
	for (i = 0, j = 0; i < 4; i++)
	{
		if (arr[i] != 0)
		{
			brr[j++] = arr[i];   // ʹ0ȫ��������
		}
	}
		//�ϲ�����
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (brr[j] == brr[j + 1])
				{
					brr[j] = brr[j] * 2;
					//brr[j+1] = 0�Ƶ�����ȥ
					for (int k = j + 1; k < 3; k++)
					{
						brr[k] = brr[k + 1];
					}
					brr[3] = 0; //�����һ����ֵΪ0
				}
			}
		}
	a = brr[0];
	b = brr[1];
	c = brr[2];
	d = brr[3];

}