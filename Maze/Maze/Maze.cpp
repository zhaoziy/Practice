// Maze.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Pos
{
	int x;
	int y;
};

typedef struct MazeNode
{
	int ord;
	int flag;  // 1墙，0通道
	Pos seat;
	int direct;
};

MazeNode Maze[100];

int ReadInfo()
{
	ifstream ifile("d:\\Maze.txt");
	if (!ifile) 
	{
		cerr << "error." << endl;
		return -1;
	}
	string lineword;
	int iLoop = 0;
	int row = 0;
	int col = 0;
	while (getline(ifile, lineword, '\n')) 
	{
		col = 0;
		const char *p = NULL;
		p = lineword.c_str();
		int count = 0;
		while (count < 10)
		{
			Maze[iLoop].ord = iLoop + 1;
			Maze[iLoop].flag = *p - '0';
			*p++;
			Maze[iLoop].seat.x = col + 1;
			Maze[iLoop].seat.y = row + 1;
			Maze[iLoop].direct = 1;   //1右，2下，3左，4上
			col++;
			iLoop++;
			count++;
		}
		row++;
	}
}

int main()
{
	ReadInfo();
    return 0;
}

