// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
#define AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Pi3.h"

class CVector  //矢量类
{
public:
	CVector();	
	CVector(CP3 &);
	CVector(CPi3 &);
	CVector(CP3,CP3);
	CVector(CPi3,CPi3);
	void Set(CP3,CP3);
	virtual ~CVector();
	CVector Unit();//单位向量
	double X();//向量的x坐标
	double Y();//向量的y坐标
	double Z();//向量的z坐标
	double Mold();//向量的模
	friend CVector operator +(CVector &,CVector &);//向量和
	friend CVector operator -(CVector &,CVector &);//向量差
	friend CVector operator *(CVector &,double);//向量数乘
	friend CVector operator /(CVector &,double);//向量数除
	friend double Dot(CVector &,CVector &);//向量点积
	friend CVector operator *(CVector &,CVector &);//向量叉积
private:
	double x,y,z;
};

#endif // !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
