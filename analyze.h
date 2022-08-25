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

using namespace std;
class mydata
{
public:
	char opera;
	double  number;
	int kind;     //类型为变量时kind为1 否则为0
	mydata* left;
	mydata* right;
	bool type;
	mydata(double num)
	{
		number = num;
		kind = 0;
		type = false;

	}
	mydata(char sym)
	{

		opera = sym;
		if (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^' || sym == '!'||sym=='('||sym==')')
		{
			kind = 0;
			type = true;

		}
		else
		{
			kind = 1;
			type = true;
		}
	}
	mydata()
	{

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
		if (*it == 'e')
		{
			return 2.7182818;


		}

	}



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
	if (tem >= '0' && tem <= '9' || tem == '.' || tem =='e')
		return 0;

	if ((tem >= 'a' && tem < 'e')||(tem>'e'&&tem<='z'))
		return 2;
	return 3;
}
void analyze(string equation, vector<mydata>& vec)
{
	string number;    //用来记录连起的数字
	string var;       //用来记录变量
	vector<mydata>euqa;  //容器用来存放词语
	int  tooken = judge(equation[0]);        //记录处理状态 0表示数字 1表示符号 2表示变量
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
				tem_x.kind = 1;
				euqa.push_back(tem_x);
				var.clear();

			}
			if (!number.empty())
			{
				mydata tem_number(string_to_double(number));  //数字拼接转为double

				tem_number.kind = 0;
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
				break;
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
				  tem_number.kind = 0;
				  euqa.push_back(tem_number);
				  number.clear();
			  }break;
		default:
			break;
		}
	}
	vec = euqa;
}
double calcaulator(vector<mydata>euqa, double x)
{
	//先把变量替换为x的值

	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->kind==1)
		{
			it->number = x;
			it->opera = '0';
			it->kind = 0;
			it->type = false;
		}
	}
	vector<mydata> tem_opera;
	vector<mydata>::iterator tem_iter;

	//要做的事
	//1. 定义运算符优先级
	
	//4.兼容阶乘与乘方 
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		//先考虑括号
		if (it->opera == '(')                       //是左括号则flag=0 直到找到右括号
		{
			double tem_num = 0;
			tem_iter = it;                               //保存左括号的迭代器
			while (it->opera != ')')
			{
				tem_opera.push_back(*it);
				it++;
			}
			if (it->opera == ')')
			{
				

				//先处理括号内的^与*内容
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end(); iter++)
				{
					if (iter->opera == '^')
					{
						if (!(iter - 1)->type && !(iter + 1)->type)//左右两侧都为数字
						{
							double num1 = (iter - 1)->number;
							double num2 = (iter + 1)->number;
							double num3 = pow(num1, num2);
							iter = tem_opera.erase(iter - 1, iter + 1);
							*iter = num3;
						}
					}

				}
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end();iter++ )
				{
					if (iter->opera == '*')
					{

						if (!(iter - 1)->type && !(iter + 1)->type)//左右两侧都为数字
						{
							//直接运算并且用数字代替左右数字与乘号

							double num1 = (iter - 1)->number;
							double num2 = (iter + 1)->number;
							double num3 = num1 * num2;
		
							iter = tem_opera.erase(iter-1,iter+1);
							*iter = num3;
						}
					}
					
				}
				//记录下第一个数字
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end(); iter++)
				{
					if (!iter->type)
					{
						tem_num = iter->number;
						break;
					}
					else tem_num = 0;
				}

				//再处理+ -
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end(); iter++)
				{
					if (iter->opera == '+')
					{
						if (!(iter - 1)->type && !(iter + 1)->type)
						{
							double num1 = (iter - 1)->number;
							double num2 = (iter + 1)->number;
							
							double num3 = num1 + num2;
							iter = tem_opera.erase(iter - 1, iter + 1);
							*iter = num3;
							tem_num += num2;
							

							


						}
					}
					if (iter->opera == '-')
					{
						if (!(iter - 1)->type && !(iter + 1)->type)
						{
							double num1 = (iter - 1)->number;
							double num2 = (iter + 1)->number;
							double num3 = num1 - num2;
							iter = tem_opera.erase(iter - 1, iter + 1);
							*iter = num3;
							tem_num -= num2;
						}
					}

				}
			}
		
			cout << "经运算括号内的值为:" << tem_num;
			it = euqa.erase(tem_iter, it);
			*it = tem_num;
		}
	}

	cout << "去括号的式子为:" << endl;
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		
		cout << *it<<"|";
	}
	//在处理括号外
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->opera == '^')
		{
			if (!(it - 1)->type && !(it + 1)->type)//左右两侧都为数字
			{
				double num1 = (it - 1)->number;
				double num2 = (it + 1)->number;
				double num3 = pow(num1, num2);
				it = euqa.erase(it - 1, it + 1);
				*it = num3;
			}
		}

	}
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->type)       //是符号
		{

			if (it->opera == '*')
			{
				if (!(it - 1)->type && !(it + 1)->type)    //左右两侧都为数字
				{
					//直接运算并且用数字代替左右数字与乘号
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * num2;
					it = euqa.erase(it, it + 2);
					*it = num3;
				}
			}
			if (it->opera == '/')
			{
				if (!(it - 1)->type && !(it + 1)->type)    //左右两侧都为数字
				{
					//直接运算并且用数字代替左右数字与乘号
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * (1.00/num2);
					it = euqa.erase(it, it + 2);
					*it = num3;
				}
			}
		}
	}
	cout <<"运算乘法后的式子"<< endl;
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		cout << *it << "|";
	}
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		if (it->opera == '+')
		{
			if (!(it - 1)->type && !(it + 1)->type)
			{
				double num1 = (it - 1)->number;
				double num2 = (it + 1)->number;
				double num3 = num1 + num2;
				it = euqa.erase(it - 1, it + 1);
				*it = num3;
			}
		}
		if (it->opera == '-')
		{
			if (!(it - 1)->type && !(it + 1)->type)
			{
				double num1 = (it - 1)->number;
				double num2 = (it + 1)->number;
				double num3 = num1 - num2;
				it = euqa.erase(it - 1, it + 1);
				*it = num3;
			}
		}


	}
	cout << euqa[0].number;
	return euqa[0].number;
}








