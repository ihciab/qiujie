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
	int state = 0;//表示此时的状态，用于对括号的判断
	for (int i = len - 1; i >= 0; i--)//从右往左扫描
	{
		if (input[i] == ')')//如果找到了一个右括号，进入状态1
		{
			state = 1;//进入状态1
		}
		if (input[i] == '(' && state == 1)//在找到一个右括号的基础上找到了一个左括号
		{

			state = 0;//返回状态0
		}
		if ((input[i] == '+' || input[i] == '-') && state == 0)//如果找到了加减号,而且处于状态0（在括号的外面）
		{
			key = 1;//表示找到了+；
			mydata* newone_left = new mydata;
			mydata* newone_right = new mydata;//创建两个新的子节点
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
			//把input分成两个数组

			//char* left = new char[i];
			//for (int j = 0; j < i; j++)//对这个数组初始化
			//{
			//	left[j] = input[j];
			//}
			string left = input.substr(0, i);    //子串left为input从0到i
			if (left[0] == '(' && left[i - 1] == ')')
			{
				string newleft = left.substr(1, i - 2);   //子串newleft为left从1开始 长度i-2
				//char* newleft = new char[i - 2];//创建一个用于存储删去括号后数据的数组
				//for (int j = 0; j < i - 2; j++)//初始化这个数组
				//{
				//	newleft[j] = left[j + 1];
				//}
				createtree(newone_left, newleft, i - 2);//对这个删去括号的数组递归
			}
			else if (i == 1)//说明此时左字符串是一个数或者未知数x
			{
				if (left[0] == 'x')//如果这是一个未知数
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
			else//否则递归
			{
				createtree(newone_left, left, i);
			}

			string right = input.substr(i + 1, len - i - 1);
			//         char* right = new char[len - i - 1];
					 //for (int j = 0; j < len - i - 1; j++)//对这个数组初始化
					 //{
					 //	right[j] = input[i + j + 1];
					 //}

			if (right[0] == '(' && right[len - i - 2] == ')')
			{
				string newright = right.substr(1, len - i - 3);
				//char* newright = new char[len - i - 3];//创建一个用于存储删去括号后数据的数组
				//for (int j = 0; j < len - i - 3; j++)//初始化这个数组
				//{
				//	newright[j] = right[j + 1];
				//}
				createtree(newone_right, newright, len - i - 3);//对这个删去括号的数组递归
			}

			else if (i == len - 2)//说明此时右串是一个数或者是未知数x
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
			else//否则递归
			{
				createtree(newone_right, right, len - i - 1);
			}
		}
	}
	if (key == 0)//上述遍历没有找到一个+，key保持为0；
	{

		for (int i = len - 1; i >= 0; i--)
		{
			if (input[i] == ')')//如果找到了一个右括号，进入状态1
			{
				state = 1;//进入状态1
			}
			if (input[i] == '(' && state == 1)//在找到一个右括号的基础上找到了一个左括号
			{

				state = 0;//返回状态0
			}

			if ((input[i] == '*' || input[i] == '/') && state == 0)
			{
				mydata* newone_left = new mydata;
				mydata* newone_right = new mydata;//创建两个新的子节点
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
				//把input分成两个数组
				string left = input.substr(0, i);
				/*	char* left = new char[i];
					for (int j = 0; j < i; j++)
					{
						left[j] = input[j];
					}*/
				if (left[0] == '(' && left[i - 1] == ')')
				{
					string newleft = left.substr(1, i - 2);
					//char* newleft = new char[i - 2];//创建一个用于存储删去括号后数据的数组
					//for (int j = 0; j < i - 2; j++)//初始化这个数组
					//{
					//	newleft[j] = left[j + 1];
					//}
					createtree(newone_left, newleft, i - 2);//对这个删去括号的数组递归
				}
				else if (i == 1)//说明此时左字符串是一个数或者未知数x
				{
					if (left[0] == 'x')//如果这是一个未知数
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
				else//否则递归
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
					//char* newright = new char[len - i - 3];//创建一个用于存储删去括号后数据的数组
					//for (int j = 0; j < len - i - 3; j++)//初始化这个数组
					//{
					//	newright[j] = right[j + 1];
					//}
					createtree(newone_right, newright, len - i - 3);//对这个删去括号的数组递归
				}
				else if (i == len - 2)//说明此时右串是一个数或者是未知数x
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
				else//否则递归
				{
					createtree(newone_right, right, len - i - 1);
				}
			}
		}
	}
}

void show(mydata* T)//中序遍历二叉树
{
	if (T != NULL)
	{
		if (T->kind == 1)//该节点是未知数x
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
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '0' || a->right->kind != 0))//该节点的左子叶和右子叶都是一个常数或未知数x
			{
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;
			}
			if (a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/')//左边是一个符号,右边是常数或未知数，则递归后运算
			{
				Get_Coefficient(a->left);
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;

			}
			if (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/')//右边是一个符号，......
			{
				Get_Coefficient(a->right);
				a->number = a->left->number + a->right->number;
				a->kind = a->left->kind + a->right->kind;

			}

		}
		if (a->opera == '-')
		{
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '0' || a->right->kind != 0))//该节点的左子叶和右子叶都是一个常数或未知数x
			{
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
			if (a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/')//左边是一个符号,则递归
			{
				Get_Coefficient(a->left);
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
			if (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/')//右边是一个符号,则递归
			{
				Get_Coefficient(a->right);
				a->number = a->left->number - a->right->number;
				a->kind = a->left->kind - a->right->kind;
			}
		}
		if (a->opera == '*')
		{
			if (a->left->opera == '0' && (a->right->opera == '0' && a->right->kind != 0))//该节点的左子叶是一个常数，右子叶是常数或者未知数x
			{
				a->number = a->left->number * a->right->number;
				a->kind = a->left->number * a->right->kind;
			}
			if ((a->left->opera == '0' || a->left->kind != 0) && a->right->opera == '0')//该节点的左子叶是常数或未知数,右子叶都是一个常数
			{
				a->number = a->right->number * a->left->number;
				a->kind = a->right->number * a->left->kind;
			}
			if ((a->left->opera == '+' || a->left->opera == '-' || a->left->opera == '*' || a->left->opera == '/') && (a->right->opera == '0' && a->right->kind != 0))//左边是一个符号,右边是常数或未知数x,则递归后运算
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
			if ((a->left->opera == '0' || a->left->kind != 0) && (a->right->opera == '+' || a->right->opera == '-' || a->right->opera == '*' || a->right->opera == '/'))//左边是常数或未知数，右边是一个符号,则递归后运算
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
//	cout << "请输入表达式" << endl;
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
//	/*cout << "x的系数为" << root.judge << "常数项为" << root.data;*/
//	cout << "方程的解为" << -1 * root.data / root.judge;
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
	
	cout<<"解为:"<<newton(vec, calcaulator);
	//createtree(&root, test, test.size() - 2);
	//Get_Coefficient(&root);
	//cout<<"一次项系数："<<root.kind<<"常数项系数"<<root.number<<endl;
	//cout << "方程的解为" << -1 * root.number / root.kind;

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
		//		//如果还能找到+ -操作符
		//		cout << "K的值" << k << endl;
		//		rjudge = euqation.substr(k + 1, i - k - 1);//右边子串
		//		cout << "右节点子串" << rjudge << "->" << endl;
		//		ljudge = euqation.substr(0, k);            //左边子串
		//		cout << "左节点子串" << ljudge << "->" << endl;

		//	}
		//	if (k == 0)
		//	{
		//		//如果找不到+- 操作符了 那么剩下子串为乘式
		//		rjudge = euqation.substr(k + 1, i - k - 1);
		//		ljudge = euqation.substr(0, k);

		//	}
		//	if (!rjudge.empty())
		//	{
		//		if (rjudge.size() == 1)

		//		{
		//			//若右子串只有一个数 则直接放入树中
		//			root->right = new TreeNode(euqation[k + 1]);
		//			cout << "右节点数:" << root->right->val;
		//		}
		//		if (rjudge.size() != 1)
		//		{
		//			//否则递归
		//			root->right = new TreeNode(euqation[getsecfuhao(rjudge, k)]);
		//			cout << "右节点数:" << root->right->val;
		//			CreatTree(rjudge, root->right, getsecfuhao(rjudge, k) - k);

		//		}
		//	}
		//	if (!ljudge.empty())
		//	{
		//		if (ljudge.size() == 1)

		//		{
		//			//若左子串只有一个数 则直接放入树中
		//			cout << ljudge.size();
		//			root->left = new TreeNode(euqation[k - 1]);
		//			cout << "左节点数:" << root->left->val;
		//		}
		//		if (ljudge.size() != 1)
		//		{
		//			//否则递归
		//			root->left = new TreeNode(euqation[getfirfuhao(ljudge, k)]);
		//			cout << "左节点数:" << root->left->val;
		//			CreatTree(ljudge, root->left, k);

		//		}
		//	}
		//	//若都结束 则左右节点置空
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
//找到子串中是否有+-符号
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
		//是否有* /符号
		int getsecfuhao(string euqation, int i)
		{
			for (int j = 0; j < euqation.size(); j++)
			{
				if (euqation[j] == '*')
				{
					//这里返回的是子串中的位置j+传入的相对位置i
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

	//将树结构遍历放入vector 中
	/*push(vec, &euqation);
	cout << "vec：" << endl;
	for (vector<char>::iterator it = vec.begin(); it != vec.end(); it++)
	{

		cout << *it;

	}*/




	}
	;
}