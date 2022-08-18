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
	string number;    //������¼���������
	string var;       //������¼����
	vector<mydata>euqa;  //����������Ŵ���
	int  tooken = 0;        //��¼����״̬ 0��ʾ���� 1��ʾ���� 2��ʾ����
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
				euqa.push_back(tem_x);
				var.clear();

			}
			if (!number.empty())
			{
				mydata tem_number(string_to_double(number));  //����ƴ��תΪdouble
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



	//�ҳ�ϵ��;
	int xrank = 0;                  //x�Ĵ���
	//	vector<vector<double>> xishu //ϵ���ɴ����͵��ߴ洢
	double xishu=1;
	int flag = 0;         //������־
	vector<mydata> tem_opera;
	/*"21*x*3+(3*5+1)+4*x+5=0";
	Ҫ������
	1. ������������ȼ�
	2.�ֿ鴦�� �����ڵĵ�������һ��vector �˺ŷֿ���㣻*/
	//3.����mydata type��Ϊint �������� ���� ���� 
	//4.���ݽ׳���˷� 5.begin������������Ҫ�޸�

	for (vector<mydata>::iterator it = euqa.begin(); it != euqa.end(); it++)
	{
		if (it->type || flag == 0)       //�Ƿ���
		{                  //�ȿ�������
			if (it->opera == '(')  //����������flag=0 ֱ���ҵ�������
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
				if (!(it - 1)->type && !(it + 1)->type && flag != 3)//�������඼Ϊ����
				{
					//ֱ�����㲢�������ִ�������������˺�
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * num2;
					it = euqa.erase(it, it + 2);
					*it = num3;
					flag = 4;

				}
				if (!(it - 1)->type && !(it + 1)->type && flag == 3)//�������඼Ϊ������Ϊxϵ�����ʱ
				{
					//ֱ�����㲢�������ִ�������������˺�
					it--;
					double num1 = (it)->number;
					double num2 = (it + 2)->number;
					double num3 = num1 * num2;
					it = euqa.erase(it, it + 2);
					*it = num3;
					xishu *= num3;

				}
				if ((it + 1)->opera == 'x' || ((it - 1)->opera == 'x'))//�б���
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
				//if ((it + 1)->type || ((it - 1)->type))//�б���
				//{
				//	flag = 3;
				//	xrank++;
				//	if (flag == 3)
				//	{
				//		if ((it + 1)->type)                          //�Ҳ��б���
				//		{

				//			double number0 = (it - 1)->number;
				//			it = euqa.erase(it - 1, it + 1);
				//			*it = number0;
				//			xishu[xrank] *= number0;

				//		
				//		}
				//		if ((it - 1)->type )                          //����б���
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


//	if (!(euqa.front().type))                               //���Ϊ����
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
//	if ((euqa.front().type) && judge(euqa.front().opera) == 3)//���Ϊ����
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



