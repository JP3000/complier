#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define PI 3.1415926
int main()
{
    double theta, x0, y0, x1, y1, x2, y2, r, l;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);//��ʼ������
    x0 = 180, y0 = 240; r = 100; l = 300;
    for(theta = 0; theta < 360; theta--)
    {
        setcolor(RED);
		setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);//������Ϊ����
        circle(x0, y0, r);
       
        setcolor(GREEN);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
        x1 = x0 + r*cos(theta*PI/180.0);
        y1 = y0 + r*sin(theta*PI/180.0);
		circle(x0, y0, 5);//�յ�һ
		circle(x1, y1, 5);//�յ��
    
        x2 = sqrt(l * l- r*r*sin(theta*PI/180.0)*sin(theta*PI/180.0)) + x1;
        y2 = y0;
		circle(x2, y2, 5);//�յ���
        
        line(x0, y0, x1, y1);
        line(x1, y1, x2, y2);
   
		rectangle(x2 - 10, y2 - 7.5, x2 + 10, y2 + 7.5);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		line(x0, y0 + 7.5, 600, y2 + 7.5);
        Sleep(50);//��ʱ50
        cleardevice();
        if(kbhit()) break;//�û��˳�ѭ��
		//system("pause");
    }
    closegraph();//�رջ���
} 