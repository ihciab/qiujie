#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<list>
#include <conio.h>
#include <stdio.h>
#include<string>
#include"analyze.h"
#include"euqation.h"
#define e 2.7182818
using namespace std;

void createtree(mydata* root, string input, int len)
{
	int key = 0;
	int state = 0;//��ʾ��ʱ��״̬�����ڶ����ŵ��ж�
	for (int i = len - 1; i >= 0; i--)//��������ɨ��
	{
		if (input[i] == ')')//����ҵ���һ�������ţ�����״̬1
		{
			state = 1;//����״̬1
		}
		if (input[i] == '(' && state == 1)//���ҵ�һ�������ŵĻ������ҵ���һ��������
		{

			state = 0;//����״̬0
		}
		if ((input[i] == '+' || input[i] == '-') && state == 0)//����ҵ��˼Ӽ���,���Ҵ���״̬0�������ŵ����棩
		{
			key = 1;//��ʾ�ҵ���+��
			mydata* newone_left = new mydata;
			mydata* newone_right = new mydata;//���������µ��ӽڵ�
			root->left = newone_left;
			root->right = newone_right;
			root->number = 0;
			if (input[i] == '+')
			{
				root->opera = '+';
			}
			else
			{
				root->opera = '-';
			}
			//��input�ֳ���������

			//char* left = new char[i];
			//for (int j = 0; j < i; j++)//����������ʼ��
			//{
			//	left[j] = input[j];
			//}
			string left = input.substr(0, i);    //�Ӵ�leftΪinput��0��i
			if (left[0] == '(' && left[i - 1] == ')')
			{
				string newleft = left.substr(1, i - 2);   //�Ӵ�newleftΪleft��1��ʼ ����i-2
				//char* newleft = new char[i - 2];//����һ�����ڴ洢ɾȥ���ź����ݵ�����
				//for (int j = 0; j < i - 2; j++)//��ʼ���������
				//{
				//	newleft[j] = left[j + 1];
				//}
				createtree(newone_left, newleft, i - 2);//�����ɾȥ���ŵ�����ݹ�
			}
			else if (i == 1)//˵����ʱ���ַ�����һ��������δ֪��x
			{
				if (left[0] == 'x')//�������һ��δ֪��
				{
					newone_left->number = 0;
					newone_left->opera = 'x';
					newone_left->left = NULL;
					newone_left->right = NULL;
					newone_left->kind = 1;
				}
				else
				{
					newone_left->number = input[i - 1] - '0';
					newone_left->opera = '0';
					newone_left->left = NULL;
					newone_left->right = NULL;
					newone_left->kind = 0;
				}

			}
			else//����ݹ�
			{
				createtree(newone_left, left, i);
			}

			string right = input.substr(i + 1, len - i - 1);
			//         char* right = new char[len - i - 1];
					 //for (int j = 0; j < len - i - 1; j++)//����������ʼ��
					 //{
					 //	right[j] = input[i + j + 1];
					 //}

			if (right[0] == '(' && right[len - i - 2] == ')')
			{
				string newright = right.substr(1, len - i - 3);
				//char* newright = new char[len - i - 3];//����һ�����ڴ洢ɾȥ���ź����ݵ�����
				//for (int j = 0; j < len - i - 3; j++)//��ʼ���������
				//{
				//	newright[j] = right[j + 1];
				//}
				createtree(newone_right, newright, len - i - 3);//�����ɾȥ���ŵ�����ݹ�
			}

			else if (i == len - 2)//˵����ʱ�Ҵ���һ����������δ֪��x
			{
				if (right[0] == 'x')
				{
					newone_right->number = 0;
					newone_right->opera = 'x';
					newone_right->left = NULL;
					newone_right->right = NULL;
					newone_right->kind = 1;
				}
				else
				{
					newone_right->number = input[i + 1] - '0';
					newone_right->opera = '0';
					newone_right->left = NULL;
					newone_right->right = NULL;
					newone_right->kind = 0;
				}

			}
			else//����ݹ�
			{
				createtree(newone_right, right, len - i - 1);
			}
		}
	}
	if (key == 0)//��������û���ҵ�һ��+��key����Ϊ0��
	{

		for (int i = len - 1; i >= 0; i--)
		{
			if (input[i] == ')')//����ҵ���һ�������ţ�����״̬1
			{
				state = 1;//����״̬1
			}
			if (input[i] == '(' && state == 1)//���ҵ�һ�������ŵĻ������ҵ���һ��������
			{

				state = 0;//����״̬0
			}

			if ((input[i] == '*' || input[i] == '/') && state == 0)
			{
				mydata* newone_left = new mydata;
				mydata* newone_right = new mydata;//���������µ��ӽڵ�
				root->left = newone_left;
				root->right = newone_right;
				root->number = 0;
				if (input[i] == '*')
				{
					root->opera = '*';
				}
				else
				{
					root->opera = '/';
				}
				//��input�ֳ���������
				string left = input.substr(0, i);
				/*	char* left = new char[i];
					for (int j = 0; j < i; j++)
					{
						left[j] = input[j];
					}*/
				if (left[0] == '(' && left[i - 1] == ')')
				{
					string newleft = left.substr(1, i - 2);
					//char* newleft = new char[i - 2];//����һ�����ڴ洢ɾȥ���ź����ݵ�����
					//for (int j = 0; j < i - 2; j++)//��ʼ���������
					//{
					//	newleft[j] = left[j + 1];
					//}
					createtree(newone_left, newleft, i - 2);//�����ɾȥ���ŵ�����ݹ�
				}
				else if (i == 1)//˵����ʱ���ַ�����һ��������δ֪��x
				{
					if (left[0] == 'x')//�������һ��δ֪��
					{
						newone_left->number = 0;
						newone_left->opera = 'x';
						newone_left->left = NULL;
						newone_left->right = NULL;
						newone_left->kind = 1;
					}
					else
					{
						newone_left->number = input[i - 1] - '0';
						newone_left->opera = '0';
						newone_left->left = NULL;
						newone_left->right = NULL;
						newone_left->kind = 0;
					}

				}
				else//����ݹ�
				{
					createtree(newone_left, left, i);
				}
				string right = input.substr(i + 1, len - i - 1);
				/*char* right = new char[len - i - 1];
				for (int j = 0; j < len - i - 1; j++)
				{
					right[j] = input[i + j + 1];
				}*/
				if (right[0] == '(' && right[len - i - 2] == ')')
				{
					string newright = right.substr(1, len - i - 3);
					//char* newright = new char[len - i - 3];//����һ�����ڴ洢ɾȥ���ź����ݵ�����
					//for (int j = 0; j < len - i - 3; j++)//��ʼ���������
					//{
					//	newright[j] = right[j + 1];
					//}
					createtree(newone_right, newright, len - i - 3);//�����ɾȥ���ŵ�����ݹ�
				}
				else if (i == len - 2)//˵����ʱ�Ҵ���һ����������δ֪��x
				{
					if (right[0] == 'x')
					{
						newone_right->number = 0;
						newone_right->opera = 'x';
						newone_right->left = NULL;
						newone_right->right = NULL;
						newone_right->kind = 1;
					}
					else
					{
						newone_right->number = input[i + 1] - '0';
						newone_right->opera = '0';
						newone_right->left = NULL;
						newone_right->right = NULL;
						newone_right->kind = 0;
					}

				}
				else//����ݹ�
				{
					createtree(newone_right, right, len - i - 1);
				}
			}
		}
	}
}

void show(mydata* T)//�������������
{
	if (T != NULL)
	{
		if (T->kind == 1)//�ýڵ���δ֪��x
		{
			cout << T->opera << endl;
		}
		else
		{
			if (T->opera == '0')
			{
				cout << T->number << endl;
			}
			else
			{
				cout << T->opera << endl;
			}
		}
		show(T->left);
		show(T->right);
	}
	else return;
}


//ostream& operator<<(ostream& o, mydata& a)
//{
//	if (a.left == NULL)
//	{
//		o << "NULL";
//		return o;
//	}
//	else
//	{
//		o << "symbol=" << a.opera << "data=" << a.number << endl;
//		return o;
//	}
//}

void Get_Coefficient(mydata* a)
{
	if (a->left != NULL)
	{
		if (a->opera == '+')
		{
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '0' || a->right->kind != 0))//�ýڵ������Ҷ������Ҷ����һ��������δ֪��x
			{
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;
			}
			if (a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/')//�����һ������,�ұ��ǳ�����δ֪������ݹ������
			{
				Get_Coefficient(a->left);
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;

			}
			if (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/')//�ұ���һ�����ţ�......
			{
				Get_Coefficient(a->right);
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;

			}

		}
		if (a->opera == '-')
		{
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '0' || a->right->kind != 0))//�ýڵ������Ҷ������Ҷ����һ��������δ֪��x
			{
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
			if (a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/')//�����һ������,��ݹ�
			{
				Get_Coefficient(a->left);
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
			if (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/')//�ұ���һ������,��ݹ�
			{
				Get_Coefficient(a->right);
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
		}
		if (a->opera == '*')
		{
			if (a->left->opera == '0' && (a->right->opera == '0' && a->right->kind != 0))//�ýڵ������Ҷ��һ������������Ҷ�ǳ�������δ֪��x
			{
				a->number = a->left->number * a->right->number;
				a->kind = a->left->number * a->right->kind;
			}
			if ((a->left->opera == '0' || a->left->kind != 0) && a->right->opera == '0')//�ýڵ������Ҷ�ǳ�����δ֪��,����Ҷ����һ������
			{
				a->number = a->right->number * a->left->number;
				a->kind = a->right->number * a->left->kind;
			}
			if ((a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/') && (a->right->opera == '0' && a->right->kind != 0))//�����һ������,�ұ��ǳ�����δ֪��x,��ݹ������
			{
				Get_Coefficient(a->left);
				if (a->left->kind != 0)
				{
					a->number = a->right->number * a->left->number;
					a->kind = a->right->number * a->left->kind;
				}
				else
				{
					a->number = a->left->number * a->right->number;
					a->kind = a->left->number * a->right->kind;
				}

			}
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/'))//����ǳ�����δ֪�����ұ���һ������,��ݹ������
			{
				Get_Coefficient(a->right);
				if (a->right->kind != 0)
				{
					a->number = a->left->number * a->right->number;
					a->kind = a->left->number * a->right->kind;
				}
				else
				{
					a->number = a->right->number * a->left->number;
					a->kind = a->right->number * a->left->kind;
				}
			}
		}
		if (a->opera == '/')
		{

		}
	}
}




//int main()
//{
//	cout << "��������ʽ" << endl;
//	char equation[100];
//	int i = 0;
//	cin >> equation;
//	int len = strlen(equation);
//	char* equation_left = new char[len - 2];
//	for (int j = 0; j < len - 2; j++)
//	{
//		equation_left[j] = equation[j];
//	}
//	treenode root;
//	createtree(&root, equation_left, len - 2);
//	Get_Coefficient(&root);
//	/*cout << "x��ϵ��Ϊ" << root.judge << "������Ϊ" << root.data;*/
//	cout << "���̵Ľ�Ϊ" << -1 * root.data / root.judge;
//	return 0;
//
//}


void main()
{


	string test = "x^3+e^x-(3*5)=0";
	mydata root;
	vector<mydata>vec;
	analyze(test,vec);
	for (vector<mydata>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it<<"|";


	}
	
	cout<<"��Ϊ:"<<newton(vec, calcaulator);
	//createtree(&root, test, test.size() - 2);
	//Get_Coefficient(&root);
	//cout<<"һ����ϵ����"<<root.kind<<"������ϵ��"<<root.number<<endl;
	//cout << "���̵Ľ�Ϊ" << -1 * root.number / root.kind;

}
void other()
{




	class TreeNode {
	public:
		char val;
		TreeNode* left;
		TreeNode* right;
		TreeNode()
		{
			this->val = '0';
			left = nullptr;
			right = nullptr;
		}
		TreeNode(char x)
		{
			this->val = x;
			left = nullptr;
			right = nullptr;
		}

		TreeNode(char x, TreeNode* l, TreeNode* r)
		{
			this->val = x;
			left = l;
			right = r;
		}
		//void CreatTree(string euqation, TreeNode* root, int i)
		//{
		//	int k = getfirfuhao(euqation, i);
		//	string rjudge;
		//	string ljudge;
		//	if (k != 0)
		//	{
		//		//��������ҵ�+ -������
		//		cout << "K��ֵ" << k << endl;
		//		rjudge = euqation.substr(k + 1, i - k - 1);//�ұ��Ӵ�
		//		cout << "�ҽڵ��Ӵ�" << rjudge << "->" << endl;
		//		ljudge = euqation.substr(0, k);            //����Ӵ�
		//		cout << "��ڵ��Ӵ�" << ljudge << "->" << endl;

		//	}
		//	if (k == 0)
		//	{
		//		//����Ҳ���+- �������� ��ôʣ���Ӵ�Ϊ��ʽ
		//		rjudge = euqation.substr(k + 1, i - k - 1);
		//		ljudge = euqation.substr(0, k);

		//	}
		//	if (!rjudge.empty())
		//	{
		//		if (rjudge.size() == 1)

		//		{
		//			//�����Ӵ�ֻ��һ���� ��ֱ�ӷ�������
		//			root->right = new TreeNode(euqation[k + 1]);
		//			cout << "�ҽڵ���:" << root->right->val;
		//		}
		//		if (rjudge.size() != 1)
		//		{
		//			//����ݹ�
		//			root->right = new TreeNode(euqation[getsecfuhao(rjudge, k)]);
		//			cout << "�ҽڵ���:" << root->right->val;
		//			CreatTree(rjudge, root->right, getsecfuhao(rjudge, k) - k);

		//		}
		//	}
		//	if (!ljudge.empty())
		//	{
		//		if (ljudge.size() == 1)

		//		{
		//			//�����Ӵ�ֻ��һ���� ��ֱ�ӷ�������
		//			cout << ljudge.size();
		//			root->left = new TreeNode(euqation[k - 1]);
		//			cout << "��ڵ���:" << root->left->val;
		//		}
		//		if (ljudge.size() != 1)
		//		{
		//			//����ݹ�
		//			root->left = new TreeNode(euqation[getfirfuhao(ljudge, k)]);
		//			cout << "��ڵ���:" << root->left->val;
		//			CreatTree(ljudge, root->left, k);

		//		}
		//	}
		//	//�������� �����ҽڵ��ÿ�
		//	root->left = nullptr;
		//	root->right = nullptr;
		//}
//void push(vector<char> v, TreeNode* tem)
//{
//	v.push_back(tem->val);
//	TreeNode* lfind = tem->left;
//	TreeNode* rfind = tem->right;
//	if (lfind != NULL)
//	{
//		push(v, lfind);
//	}
//	if (rfind != NULL)
//	{
//
//		push(v, rfind);
//	}
//
//
//}
//�ҵ��Ӵ����Ƿ���+-����
		int getfirfuhao(string euqation, int i)
		{
			for (int j = i; j > 0; j--)
			{
				if (euqation[j] == '+')
				{
					return j;

				}
				if (euqation[j] == '-')
				{
					return j;

				}

			}
			return 0;
		}
		//�Ƿ���* /����
		int getsecfuhao(string euqation, int i)
		{
			for (int j = 0; j < euqation.size(); j++)
			{
				if (euqation[j] == '*')
				{
					//���ﷵ�ص����Ӵ��е�λ��j+��������λ��i
					return j + i;

				}
				if (euqation[j] == '/')
				{
					return j + i;

				}
			}
			return 0;
		}
		int getroot(string euqation)
		{
			for (int i = 0; i < euqation.size(); ++i)
			{
				if (euqation[i] == '=')
				{
					return i;
				}

			}
		}
		//"2*x*3+3*5+1+4*x+1+1+5=0";
/*euqation.val = '=';
	euqation.right = new TreeNode('0');
	euqation.left = new TreeNode('+');
	CreatTree(test, euqation.left, test.size() - 2);*/
	/*vector<char> vec;*/

	//�����ṹ��������vector ��
	/*push(vec, &euqation);
	cout << "vec��" << endl;
	for (vector<char>::iterator it = vec.begin(); it != vec.end(); it++)
	{

		cout << *it;

	}*/




	}
	;
}