#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<iomanip>
using namespace std;
class Tnode
{
public:
	char value;
	Tnode* left, * right;
	Tnode() {}
	Tnode(const char value, Tnode* left = NULL, Tnode* right = NULL) :value(value), left(left), right(right)
	{}
	Tnode* buildTree(string exp);//后缀表达式生成二叉树
	int depth(Tnode* root);//返回树高
	void print(Tnode* node_ptr, int depth);//转向打印二叉树(逆时针转90度打印)
   // void inorderOutput(Tnode *t);
};
//后缀表达式生成二叉树
Tnode* Tnode::buildTree(string exp)
{
	Tnode* ptr=0;
	stack<Tnode*>nodeStack;
	char c;
	int i = 0;
	c = exp[i++];
	while (c != '\0')
	{
		if (c != '+' && c != '-' && c != '*' && c != '/')
		{
			ptr = new Tnode(c);
			nodeStack.push(ptr);
			c = exp[i++];
		}
		else
		{
			ptr = new Tnode(c);
			if (!nodeStack.empty())
			{
				ptr->right = nodeStack.top();
				nodeStack.pop();
			}
			if (!nodeStack.empty())
			{
				ptr->left = nodeStack.top();
				nodeStack.pop();
			}
			nodeStack.push(ptr);
			c = exp[i++];
		}
	}
	return ptr;
}

//返回树高  
int Tnode::depth(Tnode* root)
{
	int i, j;
	if (root == NULL)
		return 0;
	i = depth(root->left);
	j = depth(root->right);
	return i > j ? i + 1 : j + 1;
}




void Tnode::print(Tnode* node_ptr, int depth)//逆时针90度打印二叉树(直接输出)
{
	if (node_ptr != NULL)
	{
		print(node_ptr->right, depth + 1);
		cout << setw(3 * depth) << " ";
		cout << node_ptr->value << endl;
		print(node_ptr->left, depth + 1);
	}
}
