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
	double number;    //����
	char opera;       //�����
	bool type;        //�ж��Ƿ�Ϊ����� true��ʾ�������
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
	int string_type = 0;//0��ʾ������1��ʾ��С����
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '.')
		{
			string_type = 1;
			break;
		}
	}
	if (string_type == 0)//������ʽ
	{
		double num = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			num *= 10;
			num += s[i] - '0';
		}
		return num;
	}
	else //string_type == 1 ,С������ʽ
	{
		double num = 0;//�������� 
		size_t i = 0;//����ѭ����Ҫ�õ���Ҫ��סλ��

		for (; i < s.size(); i++)//��������������
		{
			if (s[i] == '.')
				break;//break��i����������
			num *= 10;//ǰ�������*10
			num += s[i] - '0';//���ϵ�ǰ����
		}
		i++;
		double base = 0.1;
		for (; i < s.size(); i++)//����С��������
		{
			num += (s[i] - '0') * base;
			base /= 10;
		}
		return num;
	}
}
//stringת��Ϊdouble
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
	string number;    //������¼���������
	string var;       //������¼����
	queue<mydata>euqa;  //����������Ŵ���
	int  tooken;        //��¼����״̬ 0��ʾ���� 1��ʾ���� 2��ʾ����
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

	//�ҳ�ϵ��;
	double xindex=0;
	double numindex=0;
	int flag = 0;//������־ 0��ʾnumber��� 1��ʾnumber��ˣ�2��ʾx��� 3��ʾx���
	//"21*x*3+(3*5+1)+4*x+5=0";

	while (!euqa.empty())
	{
		if (!(euqa.front().type))                               //���Ϊ����
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
		if ((euqa.front().type) && judge(euqa.front().opera) == 3)//���Ϊ����
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