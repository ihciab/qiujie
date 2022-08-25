#pragma once
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>
#include"analyze.h"
double qiudao(vector<mydata>vec, double x ,double f(vector<mydata>, double ))
{
	double daoshu = (f(vec, x + 0.00001) - f(vec, x - 0.00001)) / 0.00002;
	return daoshu;
}
double find_x(vector<mydata>vec, double x, double f(vector<mydata>, double))
{
	int times = 0;
	while (times <= 100)
	{
		if (f(vec, x) * f(vec, x + 0.1) <= 0)  //сп╫Б
		{
			return x;
		}
		else if (f(vec, x) * f(vec, x + 0.1) >= 0)
		{
			times++;
			x = pow(-1, times) * 0.1*((times+1.00)/2);
			
		}
	}
	return -1;
}
double newton(vector<mydata>vec, double f(vector<mydata>,double))
{
	double x = 1;
	x = find_x(vec,1,f);
	while (true)
	{
		
		x = x -  f(vec, x)/(qiudao(vec, x, f));
		if (fabs(f(vec, x) / (qiudao(vec, x, f)) <= 1e-6))
			break;
	}
	if (x < 1e-10)
	{
		return 0;
	}
	else 
	return x;
}
