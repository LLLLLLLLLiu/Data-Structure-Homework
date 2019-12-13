#pragma once
#include<iostream>
#include<string>
using namespace std;
#include<stack>

string postfix(string exp)
{
	char token;     //当前读取的字符 
	string s;
	stack<char>opStack;
	string postfixExp;  //目标后缀表达式
	for (int i = 0; i != exp.length(); i++)
	{
		token = (char)exp[i];
		switch (token)
		{
		case '(':
			opStack.push(token); //是 ( 则放入栈中 
			break;
		case ')':
			while (opStack.top() != '(') //将与之匹配的（之前的所有元素出栈 
			{
				s = opStack.top();
				postfixExp.append(s);
				opStack.pop();
			}
			opStack.pop();
			break;
		case '+'://若栈为空 或 栈顶为（ 或 当前为*/ 且栈顶为 +- （当前运算符优先级更高） 则直接入栈 
		case '-':
		case '*':
		case '/':
			if (opStack.empty() || opStack.top() == '(' || (token == '*' || token == '/') && (opStack.top() == '+' || opStack.top() == '-'))
			{
				opStack.push(token);
			}
			else //若优先级低于栈顶元素  
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
		default: //若为操作数则直接输出  
			s = token;
			postfixExp.append(s);
			break;
		}
	}
	while (!opStack.empty())   //将栈中剩余的元素依次输出  
	{
		s = opStack.top();
		postfixExp.append(s);
		opStack.pop();
	}
	return postfixExp;
};
