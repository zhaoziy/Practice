// FullArray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


template <typename T>
inline void swap(T* array, unsigned int i, unsigned int j)
{
	T t = array[i];
	array[i] = array[j];
	array[j] = t;
}

/*
	* 递归输出序列的全排列
	*/
void FullArray(char* array, size_t array_size, unsigned int index)
{
	if (index >= array_size)
	{
		for (unsigned int i = 0; i < array_size; ++i)
		{
			cout << array[i] << ' ';
		}

		cout << '\n';

		return;
	}

	for (unsigned int i = index; i < array_size; ++i)
	{
		swap(array, i, index);

		FullArray1(array, array_size, index + 1);

		swap(array, i, index);
	}
}




int main()
{
	return 0;
}

