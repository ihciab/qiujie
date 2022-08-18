#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<list>
#include <conio.h>
#include <stdio.h>
#include<string>
#include"analyze.h"
using namespace std;
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
};
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
void CreatTree(string euqation, TreeNode* root, int i)
{
	int k = getfirfuhao(euqation, i);
	string rjudge;
	string ljudge;
	if (k != 0)
	{
		//如果还能找到+ -操作符
		cout << "K的值" << k << endl;
		rjudge = euqation.substr(k + 1, i - k - 1);//右边子串
		cout << "右节点子串" << rjudge << "->" << endl;
		ljudge = euqation.substr(0, k);            //左边子串
		cout << "左节点子串" << ljudge << "->" << endl;

	}
	if (k == 0)
	{
		//如果找不到+- 操作符了 那么剩下子串为乘式
		rjudge = euqation.substr(k + 1, i - k - 1);
		ljudge = euqation.substr(0, k);

	}
	if (!rjudge.empty())
	{
		if (rjudge.size() == 1)

		{
			//若右子串只有一个数 则直接放入树中
			root->right = new TreeNode(euqation[k + 1]);
			cout << "右节点数:" << root->right->val;
		}
		if (rjudge.size() != 1)
		{
			//否则递归
			root->right = new TreeNode(euqation[getsecfuhao(rjudge, k)]);
			cout << "右节点数:" << root->right->val;
			CreatTree(rjudge, root->right, getsecfuhao(rjudge, k) - k);

		}
	}
	if (!ljudge.empty())
	{
		if (ljudge.size() == 1)

		{
			//若左子串只有一个数 则直接放入树中
			cout << ljudge.size();
			root->left = new TreeNode(euqation[k - 1]);
			cout << "左节点数:" << root->left->val;
		}
		if (ljudge.size() != 1)
		{
			//否则递归
			root->left = new TreeNode(euqation[getfirfuhao(ljudge, k)]);
			cout << "左节点数:" << root->left->val;
			CreatTree(ljudge, root->left, k);

		}
	}
	//若都结束 则左右节点置空
	root->left = nullptr;
	root->right = nullptr;
}
void main()
{
	/*TreeNode euqation;*/

	string test = "3+21.2*2*x1*3+(3*5+1)+4*x2+5=0";
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
	cout << endl;
	analyze(test);
	


	//cout << "选择方程种类";
	//一元多次 多元一次 多元多次 一元微分方程 矩阵方程    2*x+3*5+1=4*x-5
	//while (1)
	//{

	//	
	//	if (_kbhit())
	//	{
	//		char choose = _getch();
	//		
	//		switch (choose)
	//		{
	//		case'a':


	//		default:
	//			break;
	//		}
	//	}


}