// determinant.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int CalcDeterminant(int determinant[10][10], int degree)
{
	int determinant_temp[10][10] = { 0 };  //储存去掉某行列后的矩阵，用于下一步的迭代
	int determinant_in[100] = { 0 };  //临时转存数据(线性数据)，用于转存为矩阵形式
	int sum = 0;  //求和
	
	if (degree < 3)
	{
		sum = determinant[0][0] * determinant[1][1] - determinant[0][1] * determinant[1][0];
	}
	else
	{
		for (int nLoop = 0; nLoop < degree; ++nLoop)
		{
			if (0 == determinant[nLoop][0])
			{
				continue;  //如果为零，则不进行以下步骤，加速计算
			}
			int count = 0;
			for (int iLoop = 0; iLoop < degree; ++iLoop)
			{
				for (int jLoop = 0; jLoop < degree; ++jLoop)
				{
					if (iLoop != nLoop && jLoop != 0)
					{
						determinant_in[count++] = determinant[iLoop][jLoop]; //将某行列去掉，存入线性数组中
					}
				}
			}
			int icount = 0;
			for (int iLoop = 0; iLoop < (degree - 1); ++iLoop)
			{
				for (int jLoop = 0; jLoop < (degree - 1); ++jLoop)
				{
					determinant_temp[iLoop][jLoop] = determinant_in[icount++]; //将线性数据重新还原回矩阵形式
				}
			}
			int coef = (int)pow(-1, nLoop);   //系数，用于判断正负
			sum += coef * determinant[nLoop][0] * CalcDeterminant(determinant_temp, (degree - 1)); //递归计算
		}
	}
	return sum;
}

int main()
{
	int degree = 0;
	int determinant[10][10] = { 0 };
	int result = 0;
	cout << "输入要计算行列式的阶数：";
	//cin >> degree;
	cout << "输入数据：" << endl;
	for (int iLoop = 0; iLoop < degree; ++iLoop)
	{
		for (int jLoop = 0; jLoop < degree; ++jLoop)
		{
			//cin >> determinant[iLoop][jLoop];
		}
	}

	/*degree = 5;
	determinant[0][0] = 5;
	determinant[0][1] = 8;
	determinant[0][2] = 5;
	determinant[0][3] = 7;
	determinant[0][4] = 1;
	determinant[1][0] = 9;
	determinant[1][1] = 1;
	determinant[1][2] = 7;
	determinant[1][3] = 9;
	determinant[1][4] = 2;
	determinant[2][0] = 3;
	determinant[2][1] = 7;
	determinant[2][2] = 4;
	determinant[2][3] = 9;
	determinant[2][4] = 3;
	determinant[3][0] = 3;
	determinant[3][1] = 5;
	determinant[3][2] = 7;
	determinant[3][3] = 2;
	determinant[3][4] = 4;
	determinant[4][0] = 5;
	determinant[4][1] = 6;
	determinant[4][2] = 8;
	determinant[4][3] = 7;
	determinant[4][4] = 6;*/
	//测试数据

	result = CalcDeterminant(determinant, degree);
	cout << " 结果是：" << result << endl;
	return 0;
}

