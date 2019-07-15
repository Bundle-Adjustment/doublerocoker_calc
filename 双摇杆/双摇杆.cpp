// 双摇杆.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "math.h"
#include "stdlib.h"

#define pi 3.1415926

/*用于确定O1O2距离，确定两个对应位置对应角度的双摇杆机构*/

typedef struct {
	/*a杆的长度*/
	float la;

	/*O1O2长度*/
	float d;

	/*O2B的两个角度	α1，2*/
	float angle[2];

	/*O1E的两个角度	Δ1，2*/
	float delta[2];

	/*中间系数*/
	float a[2],b,c[2];

	/*中间输出结果*/
	float x,y;

	/*最终输出结果*/
	float out[2];
}position_t;



float *drocker_calc(position_t position)
{
	/*弧度制转化为角度制系数*/
	float p = pi / 180;

	float matrix;
	float m1;
	float m2;

	printf("输入O1O2的距离,输入a的长度\n");
	scanf_s("%f %f",&position.d, &position.la);

	position.d = position.d / position.la;
 	position.b = 1;

	for (int i = 1; i <= 2; i++)
	{
		printf("输入O2B1和O1E1,O2B2和O1E2对应的角度\n");
		scanf_s("%f %f", &position.angle[i - 1], &position.delta[i - 1]);
		position.angle[i - 1] = position.angle[i - 1] * p;
		position.delta[i - 1] = position.delta[i - 1] * p;
		printf("%f,%f\n",position.angle[i - 1], position.delta[i - 1]);
		position.a[i - 1] = cos(position.delta[i - 1]) - cos((position.delta[i - 1] - position.angle[i - 1])) / position.d;
		position.c[i - 1] = cos(position.angle[i - 1]);
	}

	
	printf("a1 = %f, a2 = %f, c1 = %f, c2 = %f\n", position.a[0], position.a[1], position.c[0], position.c[1]);

	matrix = position.a[0] * position.b - position.a[1] * position.b;
	m1 = 1 * (position.b * position.c[1] - position.b * position.c[0]);
	m2 = position.a[0] * position.c[1] - position.a[1] * position.c[0];

	printf("matrix = %f, m1 = %f, m2 = %f\n",matrix, m1, m2);

	position.x = -m1 / matrix;
	position.y = m2 / matrix;

	printf("x = %f, y = %f\n", position.x,position.y);

	position.out[0] = position.x * position.la;	//c,连架杆
	position.out[1] =sqrt( position.d * position.d + position.x * position.x + 1 - 2 * position.d * position.y) * position.la;	//b，连杆
	printf("连架杆c = %f, 连杆(未开平方)b = %f\n", position.out[0], position.out[1]);

	return position.out;
}

position_t position;
int main()
{
	while (1) 
	{
		drocker_calc(position);
		//memcpy(out, drocker_calc(position), sizeof(drocker_calc(position)));

		system("pause");
	}
    return 0;

}

