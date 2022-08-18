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

	if (tem == '+' || tem == '-' || tem == '*' || tem == '/' || tem == '^' || tem == '!' || tem == '(' || tem == ')')
		return 1;
	if (tem >= '0' && tem <= '9' || tem == '.')
		return 0;
	if (tem >= 'a' && tem <= 'z')
		return 2;
	return 3;
}
void analyze(string equation)
{
	string number;    //用来记录连起的数字
	string var;       //用来记录变量
	vector<mydata>euqa;  //容器用来存放词语
	int  tooken = 0;        //记录处理状态 0表示数字 1表示符号 2表示变量
	for (int i = 0; i < equation.size(); ++i)
	{
		// "21*x1*3+(3*5+1)+4*x2+5=0";

		switch (tooken)
		{
		case 0: number.push_back(equation[i]); //数字放入临时数字中

			tooken = judge(equation[i + 1]);
			break;
		case 1:
		{
			if (!var.empty())
			{
				mydata tem_x(string_to_char(var));  //变量拼接
				euqa.push_back(tem_x);
				var.clear();

			}
			if (!number.empty())
			{
				mydata tem_number(string_to_double(number));  //数字拼接转为double
				euqa.push_back(tem_number);
				number.clear();
			}
			euqa.push_back(equation[i]);

			tooken = judge(equation[i + 1]);
			break;
		}

		case 2:var.push_back(equation[i]);
			if (judge(equation[i + 1]) == 0 || judge(equation[i + 1]) == 2)  //如果下一个为数字或字母 则继续执行情况2 否则为符号执行case 1
			{
				tooken = 2;

			}
			else tooken = 1;	break;
		case 3:if (!var.empty())
		{
			mydata tem_x(string_to_char(var));
			euqa.push_back(tem_x);
			var.clear();

		}

			  if (!number.empty())
			  {
				  mydata tem_number(string_to_double(number));
				  euqa.push_back(tem_number);
				  number.clear();
			  }break;
		default:
			break;
		}
	}

	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		cout << *it << "|";
	}
	cout << endl;



	//找出系数;
	int xrank = 0;                  //x的次数
	//	vector<vector<double>> xishu //系数由次数低到高存储
	double xishu=1;
	int flag = 0;         //操作标志
	vector<mydata> tem_opera;
	/*"21*x*3+(3*5+1)+4*x+5=0";
	要做的事
	1. 定义运算符优先级
	2.分块处理 括号内的单独进入一个vector 乘号分块计算；*/
	//3.对于mydata type改为int 区分数字 符号 变量 
	//4.兼容阶乘与乘方 5.begin（）处报错需要修改

	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->type || flag == 0)       //是符号
		{                  //先考虑括号
			if (it->opera == '(')  //是左括号则flag=0 直到找到右括号
			{
				tem_opera.push_back(*it);
				flag = 0;
				continue;

			}
			if (it->opera == ')')
			{



				flag = 1;
			}
			if (it->opera == '*')
			{
				if (!(it - 1)->type && !(it + 1)->type && flag != 3)//左右两侧都为数字
				{
					//直接运算并且用数字代替左右数字与乘号
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * num2;
					it = euqa.erase(it, it + 2);
					*it = num3;
					flag = 4;

				}
				if (!(it - 1)->type && !(it + 1)->type && flag == 3)//左右两侧都为数字且为x系数求解时
				{
					//直接运算并且用数字代替左右数字与乘号
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * num2;
					it = euqa.erase(it, it + 2);
					*it = num3;
					xishu *= num3;

				}
				if ((it + 1)->opera == 'x' || ((it - 1)->opera == 'x'))//有变量
				{
					flag = 3;
					xrank++;
					if (flag == 3)
					{

						double num0 = (it - 1)->number;
						it = euqa.erase(it - 1, it + 1);
						*it = num0;
						xishu *= num0;

					}
				}
				//if ((it + 1)->type || ((it - 1)->type))//有变量
				//{
				//	flag = 3;
				//	xrank++;
				//	if (flag == 3)
				//	{
				//		if ((it + 1)->type)                          //右侧有变量
				//		{

				//			double number0 = (it - 1)->number;
				//			it = euqa.erase(it - 1, it + 1);
				//			*it = number0;
				//			xishu[xrank] *= number0;

				//		
				//		}
				//		if ((it - 1)->type )                          //左侧有变量
				//		{
				//		
				//			double number0 = (it - 1)->number;
				//			it = euqa.erase(it - 1, it + 1);
				//			*it = number0;
				//			xishu[xrank] *= number0;
				//			
				//			
				//		}
				//	}
				//}

			}
			if (it->opera == '+' || it->opera == '-')
			{

				flag = 1;

				continue;
			}
		}
	}
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		cout << *it;
	}
}


//	if (!(euqa.front().type))                               //如果为数字
//	{
//		switch (flag)
//		{
//		case 0:
//			flag = 5;
//			while(flag!=0)
//		{
//				double tem_number = 0;
//				if (!(euqa.front().type))
//				{
//					tem_number = euqa.front().number;

//				}
//			xindex += euqa.front().number; break;
//			euqa.pop();
//		}
//		case 1:xindex *= euqa.front().number; euqa.pop(); break;
//		default:
//			break;
//		}
//		


//	}
//	if ((euqa.front().type) && judge(euqa.front().opera) == 3)//如果为变量
//	{


//	}
//	if (euqa.front().type)
//	{
//		if (euqa.front().opera == '+')
//		{
//			flag = 0;
//			euqa.pop();
//		}
//		if (euqa.front().opera == '*')
//		{
//			flag = 1;
//			euqa.pop();
//		}
//		



