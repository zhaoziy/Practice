// Maze.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

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
	Pos me;
	Pos top;
	int direct;
};

stack<MazeNode> path;

int ReadInfo(MazeNode *Maze)
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
			Maze[iLoop].me.x = col + 1;
			Maze[iLoop].me.y = row + 1;
			Maze[iLoop].top.x = 0;
			Maze[iLoop].top.y = 0;
			Maze[iLoop].direct = 1;   //1右，2下，3左，4上
			col++;
			iLoop++;
			count++;
		}
		row++;
	}
}

int Print(MazeNode *Maze)
{
	int count = 0;
	for (count = 0; count < 100; ++count)
	{
		if (Maze[count].flag == 1)
		{
			cout << '*';
			if ((count + 1) % 10 == 0)
			{
				cout << endl;
			}
		}
		else
		{
			cout << ' ';
			if ((count + 1) % 10 == 0)
			{
				cout << endl;
			}
		}
	}
	return 0;
}

int MakePath(MazeNode *Maze)
{
	return 0;
}

int main()
{
	MazeNode Maze[100];
	
	ReadInfo(Maze);
	MakePath(Maze);
	Print(Maze);
    return 0;
}
