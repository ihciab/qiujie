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
void CreatTree(string euqation, TreeNode* root, int i)
{
	int k = getfirfuhao(euqation, i);
	string rjudge;
	string ljudge;
	if (k != 0)
	{
		//��������ҵ�+ -������
		cout << "K��ֵ" << k << endl;
		rjudge = euqation.substr(k + 1, i - k - 1);//�ұ��Ӵ�
		cout << "�ҽڵ��Ӵ�" << rjudge << "->" << endl;
		ljudge = euqation.substr(0, k);            //����Ӵ�
		cout << "��ڵ��Ӵ�" << ljudge << "->" << endl;

	}
	if (k == 0)
	{
		//����Ҳ���+- �������� ��ôʣ���Ӵ�Ϊ��ʽ
		rjudge = euqation.substr(k + 1, i - k - 1);
		ljudge = euqation.substr(0, k);

	}
	if (!rjudge.empty())
	{
		if (rjudge.size() == 1)

		{
			//�����Ӵ�ֻ��һ���� ��ֱ�ӷ�������
			root->right = new TreeNode(euqation[k + 1]);
			cout << "�ҽڵ���:" << root->right->val;
		}
		if (rjudge.size() != 1)
		{
			//����ݹ�
			root->right = new TreeNode(euqation[getsecfuhao(rjudge, k)]);
			cout << "�ҽڵ���:" << root->right->val;
			CreatTree(rjudge, root->right, getsecfuhao(rjudge, k) - k);

		}
	}
	if (!ljudge.empty())
	{
		if (ljudge.size() == 1)

		{
			//�����Ӵ�ֻ��һ���� ��ֱ�ӷ�������
			cout << ljudge.size();
			root->left = new TreeNode(euqation[k - 1]);
			cout << "��ڵ���:" << root->left->val;
		}
		if (ljudge.size() != 1)
		{
			//����ݹ�
			root->left = new TreeNode(euqation[getfirfuhao(ljudge, k)]);
			cout << "��ڵ���:" << root->left->val;
			CreatTree(ljudge, root->left, k);

		}
	}
	//�������� �����ҽڵ��ÿ�
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

	//�����ṹ��������vector ��
	/*push(vec, &euqation);
	cout << "vec��" << endl;
	for (vector<char>::iterator it = vec.begin(); it != vec.end(); it++)
	{

		cout << *it;

	}*/
	cout << endl;
	analyze(test);
	


	//cout << "ѡ�񷽳�����";
	//һԪ��� ��Ԫһ�� ��Ԫ��� һԪ΢�ַ��� ���󷽳�    2*x+3*5+1=4*x-5
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