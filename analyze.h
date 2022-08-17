#pragma once
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class mydata
{
public:
	double number;    //数字
	char opera;       //运算符
	bool type;        //判断是否为运算符 true表示是运算符
	mydata(double a)
	{
		number = a;
		type = false;
	}
	mydata(char ope)
	{
		opera = ope;
		type = true;
	}


};
ostream& operator<<(ostream& o, mydata& data)
{
	if (data.type)
	{
		o << data.opera;
		return o;
	}
	else if (!data.type)
	{
		o << data.number;
		return o;
	}
}


double string_to_double(string s)
{
	int string_type = 0;//0表示整数，1表示带小数点
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '.')
		{
			string_type = 1;
			break;
		}
	}
	if (string_type == 0)//整数形式
	{
		double num = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			num *= 10;
			num += s[i] - '0';
		}
		return num;
	}
	else //string_type == 1 ,小数点形式
	{
		double num = 0;//整数部分 
		size_t i = 0;//两个循环都要用到，要记住位置

		for (; i < s.size(); i++)//计算整数的数字
		{
			if (s[i] == '.')
				break;//break后i并不会自增
			num *= 10;//前面的数字*10
			num += s[i] - '0';//加上当前数字
		}
		i++;
		double base = 0.1;
		for (; i < s.size(); i++)//计算小数的数字
		{
			num += (s[i] - '0') * base;
			base /= 10;
		}
		return num;
	}
}
//string转化为double
double string_to_double(const char* char_s)
{
	string s(char_s);
	return string_to_double(s);
}
char string_to_char(string s)
{
	char* tem = new char[s.size() + 1];
	for (int i = 0; i < s.size(); ++i)
	{
		tem[i] = s[i];
	}

	return *tem;
}
int judge(char tem)
{

	if (tem == '+' || tem == '-' || tem == '*' || tem == '/' || tem == '^' || tem == '!' || tem == '(' || tem == ')'  )
		return 1;
	if (tem >= '0' && tem <= '9')
		return 0;
	if (tem >= 'a' && tem <= 'z')
		return 2;
	return 3;
}
void analyze(string equation)
{
	string number;    //用来记录连起的数字
	string var;       //用来记录变量
	queue<mydata>euqa;  //队列用来存放词语
	int  tooken;        //记录处理状态 0表示数字 1表示符号 2表示变量
	for (int i = 0; i < equation.size(); ++i)
	{
		// "2*x*3+3*5+1+4*x+5=0";
		tooken = judge(equation[i]);
		switch (tooken)
		{
		case 0: number.push_back(equation[i]);	break;
		case 1:
		{
			if (!var.empty())
			{
				mydata tem_x(string_to_char(var));
				euqa.push(tem_x);
				var.clear();

			}
			if (!number.empty())
			{
				mydata tem_number(string_to_double(number));
				euqa.push(tem_number);
				number.clear();
			}
			euqa.push(equation[i]);
		}
		break;
		case 2:var.push_back(equation[i]);	break;
		case 3:if (!var.empty())
		{
			mydata tem_x(string_to_char(var));
			euqa.push(tem_x);
			var.clear();

		}

			  if (!number.empty())
			  {
				  mydata tem_number(string_to_double(number));
				  euqa.push(tem_number);
				  number.clear();
			  }break;
		default:
			break;
		}
	}

	//找出系数;
	double xindex=0;
	double numindex=0;
	int flag = 0;//操作标志 0表示number相加 1表示number相乘；2表示x相加 3表示x相乘
	//"21*x*3+(3*5+1)+4*x+5=0";

	while (!euqa.empty())
	{
		if (!(euqa.front().type))                               //如果为数字
		{
			switch (flag)
			{
			case 0:
				flag = 5;
				while(flag!=0)
			{
					double tem_number = 0;
					if (!(euqa.front().type))
					{
						tem_number = euqa.front().number;

					}
				xindex += euqa.front().number; break;
				euqa.pop();
			}
			case 1:xindex *= euqa.front().number; euqa.pop(); break;
			default:
				break;
			}
			


		}
		if ((euqa.front().type) && judge(euqa.front().opera) == 3)//如果为变量
		{


		}
		if (euqa.front().type)
		{
			if (euqa.front().opera == '+')
			{
				flag = 0;
				euqa.pop();
			}
			if (euqa.front().opera == '*')
			{
				flag = 1;
				euqa.pop();
			}
			



        	}


		/*cout << euqa.front()<<"|";
		euqa.pop();*/

	}
}