// Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <stack>

using namespace std;

long long TenConvert(int number, int jinzhi)
{
	long long endNum = 0;
	stack<int> endjinzhi;
	while (number)
	{
		int mod = 0;
		mod = number % jinzhi;
		endjinzhi.push(mod);
		number = (number-mod) / jinzhi;
	}
	while (1)
	{
		endNum += endjinzhi.top();
		endjinzhi.pop();
		if (!endjinzhi.empty())
		{
			endNum *= 10;
		}
		else
		{
			break;
		}
	}
	return endNum;
}

int main()
{
	long long a = 0;
	a = TenConvert(3, 2);
    return 0;
}

