#pragma once

#include "stdafx.h"
#include <vector>

using namespace std;

struct wz{int x[3],y[3];};
vector<struct wz> s;
int px,py;

int cr(int x,int y,int t)
{
	struct wz a;
	for(int i=0,j=0; i<4; i++)
	{
		if(i!=t)
		{
			a.x[j]=x+i%2;
			a.y[j++]=y+i/2;
		}
	}
	s.push_back(a);
	return 0;
}

int qp(int k,int x,int y,int f)
{
	int zy(int f,int t,int x,int y,int k);
	if(k==1)
	{
		if(x==px&&y==py)return 1;
		else return 0;
	}
	if(f>-1)
	{
		cr(x+(k>>1)-1,y+(k>>1)-1,f);
		return zy(f,1,x,y,k);
	}
	if(qp((k>>1),x,y,-1))
	{
		cr(x+(k>>1)-1,y+(k>>1)-1,0);
		return zy(0,0,x,y,k);
	}
	else if(qp((k>>1),x+(k>>1),y,-1))
	{
		cr(x+(k>>1)-1,y+(k>>1)-1,1);
		return zy(1,0,x,y,k);
	}
	else if(qp((k>>1),x,y+(k>>1),-1))
	{
		cr(x+(k>>1)-1,y+(k>>1)-1,2);
		return zy(2,0,x,y,k);
	}
	else if(qp((k>>1),x+(k>>1),y+(k>>1),-1))
	{
		cr(x+(k>>1)-1,y+(k>>1)-1,3);
		return zy(3,0,x,y,k);
	}
}

int zy(int f,int t,int x,int y,int k)
{
	if(t>0)
	{
		if(f==0)qp((k>>1),x,y,f);
		if(f==1)qp((k>>1),x+(k>>1),y,f);
		if(f==2)qp((k>>1),x,y+(k>>1),f);
		if(f==3)qp((k>>1),x+(k>>1),y+(k>>1),f);
	}
	if(f!=0)qp((k>>1),x,y,3);
	if(f!=1)qp((k>>1),x+(k>>1),y,2);
	if(f!=2)qp((k>>1),x,y+(k>>1),1);
	if(f!=3)qp((k>>1),x+(k>>1),y+(k>>1),0);
	return 1;
}

int Calc(int k,int x, int y)
{
	s.clear();
	px = x;
	py = y;
	qp(1<<k,0,0,-1);

	return 0;
}