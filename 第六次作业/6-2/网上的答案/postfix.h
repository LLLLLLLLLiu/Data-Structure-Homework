#pragma once
#include<iostream>
#include<string>
using namespace std;
#include<stack>

string postfix(string exp)
{
	char token;     //��ǰ��ȡ���ַ� 
	string s;
	stack<char>opStack;
	string postfixExp;  //Ŀ���׺���ʽ
	for (int i = 0; i != exp.length(); i++)
	{
		token = (char)exp[i];
		switch (token)
		{
		case '(':
			opStack.push(token); //�� ( �����ջ�� 
			break;
		case ')':
			while (opStack.top() != '(') //����֮ƥ��ģ�֮ǰ������Ԫ�س�ջ 
			{
				s = opStack.top();
				postfixExp.append(s);
				opStack.pop();
			}
			opStack.pop();
			break;
		case '+'://��ջΪ�� �� ջ��Ϊ�� �� ��ǰΪ*/ ��ջ��Ϊ +- ����ǰ��������ȼ����ߣ� ��ֱ����ջ 
		case '-':
		case '*':
		case '/':
			if (opStack.empty() || opStack.top() == '(' || (token == '*' || token == '/') && (opStack.top() == '+' || opStack.top() == '-'))
			{
				opStack.push(token);
			}
			else //�����ȼ�����ջ��Ԫ��  
			{
				s = opStack.top();
				postfixExp.append(s);
				opStack.pop();
				if (opStack.top() == '+' || opStack.top() == '-')
				{
					s = opStack.top();
					postfixExp.append(s);
					opStack.pop();
				}
				opStack.push(token);
			}
			break;
		default: //��Ϊ��������ֱ�����  
			s = token;
			postfixExp.append(s);
			break;
		}
	}
	while (!opStack.empty())   //��ջ��ʣ���Ԫ���������  
	{
		s = opStack.top();
		postfixExp.append(s);
		opStack.pop();
	}
	return postfixExp;
};
