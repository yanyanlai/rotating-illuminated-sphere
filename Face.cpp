// Face.cpp: implementation of the CFace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Face.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFace::CFace()
{

}

CFace::CFace(int *pindex,int en)
{
	this->En=en;
	this->pIndex=new int[en];
	for(int i=0;i<en;i++)
	{
		pIndex[i]=pindex[i];
	}
}

CFace::~CFace()
{

}

void CFace::SetNormal(CP3 pt1,CP3 pt2,CP3 pt3)//求小面法矢量
{
	CVector V12(pt1,pt2);
	CVector V23(pt2,pt3);
	this->Normal=V12*V23;
}