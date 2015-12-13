// determinant.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int CalcDeterminant(int determinant[10][10], int degree)
{
	int determinant_temp[10][10] = { 0 };  //����ȥ��ĳ���к�ľ���������һ���ĵ���
	int determinant_in[100] = { 0 };  //��ʱת������(��������)������ת��Ϊ������ʽ
	int sum = 0;  //���
	
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
				continue;  //���Ϊ�㣬�򲻽������²��裬���ټ���
			}
			int count = 0;
			for (int iLoop = 0; iLoop < degree; ++iLoop)
			{
				for (int jLoop = 0; jLoop < degree; ++jLoop)
				{
					if (iLoop != nLoop && jLoop != 0)
					{
						determinant_in[count++] = determinant[iLoop][jLoop]; //��ĳ����ȥ������������������
					}
				}
			}
			int icount = 0;
			for (int iLoop = 0; iLoop < (degree - 1); ++iLoop)
			{
				for (int jLoop = 0; jLoop < (degree - 1); ++jLoop)
				{
					determinant_temp[iLoop][jLoop] = determinant_in[icount++]; //�������������»�ԭ�ؾ�����ʽ
				}
			}
			int coef = (int)pow(-1, nLoop);   //ϵ���������ж�����
			sum += coef * determinant[nLoop][0] * CalcDeterminant(determinant_temp, (degree - 1)); //�ݹ����
		}
	}
	return sum;
}

int main()
{
	int degree = 0;
	int determinant[10][10] = { 0 };
	int result = 0;
	cout << "����Ҫ��������ʽ�Ľ�����";
	//cin >> degree;
	cout << "�������ݣ�" << endl;
	for (int iLoop = 0; iLoop < degree; ++iLoop)
	{
		for (int jLoop = 0; jLoop < degree; ++jLoop)
		{
			//cin >> determinant[iLoop][jLoop];
		}
	}

	degree = 5;
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
	determinant[4][4] = 6;
	//��������

	result = CalcDeterminant(determinant, degree);
	cout << " ����ǣ�" << result << endl;
	return 0;
}
