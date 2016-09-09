#pragma once
#include "Stack.h"
const int line = 10;
const int list = 10;

class Pos
{
public:
	Pos(int x = 0,int y = 0)
		:_x(x)
		, _y(y)
	{}
public:
	int _x;
	int _y;
};

int* InitMaze()
{
	FILE* pf = fopen("maze.txt","r");
	assert(pf);
	char c = 0;
	int* maze = new int[line * list];
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < list;)
		{
			c = fgetc(pf);
			if ((c == '0') || (c == '1'))
			{
				maze[i * list + j] = c - '0';
				j++;
			}
		}
	}
	fclose(pf);
	return maze;
}

void PrintMaze(int *maze)
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < list; j++)
		{
			cout << maze[i*list + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool IsValue(int *maze,const Pos& pos)
{
	if ((pos._x >= 0) && (pos._x < line) && (pos._y >= 0) && (pos._y < list) && (maze[pos._x * list + pos._y] == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FindPath(int *maze, const Pos& begin)
{
	Pos cur = begin;
	Stack <Pos> s;
	s.Push(cur);
	maze[cur._x * list + cur._y] = 2;
	while (!s.Empty())
	{
		cur = s.Top();
		if ((cur._x == 0) || (cur._x == line-1) || (cur._y == list-1))
		{
			return true;
		}
		Pos next = cur;
		//ио
		next._x--;
		if (IsValue(maze, next))
		{
			cur = next;
			maze[cur._x * list + cur._y] = 2;
			s.Push(cur);
			continue;
		}
		//об
		next = cur;
		next._x++;
		if (IsValue(maze, next))
		{
			cur = next;
			maze[cur._x * list + cur._y] = 2;
			s.Push(cur);
			continue;
		}
		//вС
		next = cur;
		next._y--;
		if (IsValue(maze, next))
		{
			cur = next;
			maze[cur._x * list + cur._y] = 2;
			s.Push(cur);
			continue;
		}
		//ср
		next = cur;
		next._y++;
		if (IsValue(maze, next))
		{
			cur = next;
			maze[cur._x * list + cur._y] = 2;
			s.Push(cur);
			continue;
		}
		s.Pop();
		maze[cur._x * list + cur._y] = 3;
		PrintMaze(maze);
	}	
	return false;
} 


void TestMaze()
{	
	int * maze = InitMaze();
	Pos begin(1, 0);
	PrintMaze(maze);
	cout << FindPath(maze, begin) << endl;
	PrintMaze(maze);

}
