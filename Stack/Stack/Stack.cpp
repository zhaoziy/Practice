// Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <stack>

using namespace std;

int TenToEight(int number)
{
	int eightNum = 0;
	stack<int> eight;
	while (number)
	{
		int mod = 0;
		mod = number % 8;
		eight.push(mod);
		number = (number-mod) / 8;
	}
	while (1)
	{
		eightNum += eight.top();
		eight.pop();
		if (!eight.empty())
		{
			eightNum *= 10;
		}
		else
		{
			break;
		}
	}
	return eightNum;
}

int main()
{
	int a = 0;
	a = TenToEight(1348);
    return 0;
}

