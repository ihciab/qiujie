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
	int kind;     //����Ϊ����ʱkindΪ1 ����Ϊ0
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
	int string_type = 0;//0��ʾ������1��ʾ��С����
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
	string number;    //������¼���������
	string var;       //������¼����
	vector<mydata>euqa;  //����������Ŵ���
	int  tooken = judge(equation[0]);        //��¼����״̬ 0��ʾ���� 1��ʾ���� 2��ʾ����
	for (int i = 0; i < equation.size(); ++i)
	{
		// "21*x1*3+(3*5+1)+4*x2+5=0";

		switch (tooken)
		{
		case 0: number.push_back(equation[i]); //���ַ�����ʱ������

			tooken = judge(equation[i + 1]);
			break;
		case 1:
		{
			if (!var.empty())
			{
				mydata tem_x(string_to_char(var));  //����ƴ��
				tem_x.kind = 1;
				euqa.push_back(tem_x);
				var.clear();

			}
			if (!number.empty())
			{
				mydata tem_number(string_to_double(number));  //����ƴ��תΪdouble

				tem_number.kind = 0;
				euqa.push_back(tem_number);
				number.clear();
			}

			euqa.push_back(equation[i]);

			tooken = judge(equation[i + 1]);
			break;
		}

		case 2:var.push_back(equation[i]);
			if (judge(equation[i + 1]) == 0 || judge(equation[i + 1]) == 2)  //�����һ��Ϊ���ֻ���ĸ �����ִ�����2 ����Ϊ����ִ��case 1
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
	//�Ȱѱ����滻Ϊx��ֵ

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

	//Ҫ������
	//1. ������������ȼ�
	
	//4.���ݽ׳���˷� 
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{

		//�ȿ�������
		if (it->opera == '(')                       //����������flag=0 ֱ���ҵ�������
		{
			double tem_num = 0;
			tem_iter = it;                               //���������ŵĵ�����
			while (it->opera != ')')
			{
				tem_opera.push_back(*it);
				it++;
			}
			if (it->opera == ')')
			{
				

				//�ȴ��������ڵ�^��*����
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end(); iter++)
				{
					if (iter->opera == '^')
					{
						if (!(iter - 1)->type && !(iter + 1)->type)//�������඼Ϊ����
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

						if (!(iter - 1)->type && !(iter + 1)->type)//�������඼Ϊ����
						{
							//ֱ�����㲢�������ִ�������������˺�

							double num1 = (iter - 1)->number;
							double num2 = (iter + 1)->number;
							double num3 = num1 * num2;
		
							iter = tem_opera.erase(iter-1,iter+1);
							*iter = num3;
						}
					}
					
				}
				//��¼�µ�һ������
				for (vector<mydata>::iterator iter = tem_opera.begin(); iter != tem_opera.end(); iter++)
				{
					if (!iter->type)
					{
						tem_num = iter->number;
						break;
					}
					else tem_num = 0;
				}

				//�ٴ���+ -
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
		
			cout << "�����������ڵ�ֵΪ:" << tem_num;
			it = euqa.erase(tem_iter, it);
			*it = tem_num;
		}
	}

	cout << "ȥ���ŵ�ʽ��Ϊ:" << endl;
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		
		cout << *it<<"|";
	}
	//�ڴ���������
	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->opera == '^')
		{
			if (!(it - 1)->type && !(it + 1)->type)//�������඼Ϊ����
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
		if (it->type)       //�Ƿ���
		{

			if (it->opera == '*')
			{
				if (!(it - 1)->type && !(it + 1)->type)    //�������඼Ϊ����
				{
					//ֱ�����㲢�������ִ�������������˺�
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
				if (!(it - 1)->type && !(it + 1)->type)    //�������඼Ϊ����
				{
					//ֱ�����㲢�������ִ�������������˺�
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
	cout <<"����˷����ʽ��"<< endl;
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








