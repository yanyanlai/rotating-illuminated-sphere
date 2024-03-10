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

class CVector  //ʸ����
{
public:
	CVector();	
	CVector(CP3 &);
	CVector(CPi3 &);
	CVector(CP3,CP3);
	CVector(CPi3,CPi3);
	void Set(CP3,CP3);
	virtual ~CVector();
	CVector Unit();//��λ����
	double X();//������x����
	double Y();//������y����
	double Z();//������z����
	double Mold();//������ģ
	friend CVector operator +(CVector &,CVector &);//������
	friend CVector operator -(CVector &,CVector &);//������
	friend CVector operator *(CVector &,double);//��������
	friend CVector operator /(CVector &,double);//��������
	friend double Dot(CVector &,CVector &);//�������
	friend CVector operator *(CVector &,CVector &);//�������
private:
	double x,y,z;
};

#endif // !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
