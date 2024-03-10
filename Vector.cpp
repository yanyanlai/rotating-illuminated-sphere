// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Vector.h"
#include "Cmath"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{
	this->x=0;
	this->y=0;
	this->z=0;
}

CVector::~CVector()
{

}
CVector::CVector(CP3 &p)
{
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;	
}

CVector::CVector(CPi3 &p)
{
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;	
}

CVector::CVector(CP3 p1,CP3 p2)
{
	this->x=p2.x-p1.x;
	this->y=p2.y-p1.y;
	this->z=p2.z-p1.z;
}

void CVector::Set(CP3 p1,CP3 p2)
{
	this->x=p2.x-p1.x;
	this->y=p2.y-p1.y;
	this->z=p2.z-p1.z;
}

CVector::CVector(CPi3 p1,CPi3 p2)
{
	this->x=p2.x-p1.x;
	this->y=p2.y-p1.y;
	this->z=p2.z-p1.z;
}

double CVector::X()
{
	return this->x;
}

double CVector::Y()
{
	return this->y;
}
double CVector::Z()
{
	return this->z;
}

CVector CVector::Unit()//单位矢量
{
	CVector vector;
	double product=sqrt(x*x+y*y+z*z);
	if(product<1e-5)
		product=1.0;
	vector.x=x/product;
	vector.y=y/product;
	vector.z=z/product;
	return vector;
}

double CVector::Mold()//矢量的模
{
	double product=sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
	return product;
}

double Dot(CVector &v1,CVector &v2)//矢量的点积
{
	return(v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

CVector operator +(CVector &v1,CVector &v2)//矢量的和
{	
	CVector vector;
	vector.x=v1.x+v2.x;
	vector.y=v1.y+v2.y;
	vector.z=v1.z+v2.z;
	return vector;
}
CVector operator -(CVector &v1,CVector &v2)//矢量的差
{	
	CVector vector;
	vector.x=v1.x-v2.x;
	vector.y=v1.y-v2.y;
	vector.z=v1.z-v2.z;
	return vector;
}

CVector operator *(CVector &v,double k)//矢量和常量的积
{	
	CVector vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}
CVector operator /(CVector &v,double k)//向量数除
{
	CVector vector;
	vector.x=v.x/k;
	vector.y=v.y/k;
	vector.z=v.z/k;
	return vector;
}

CVector operator * (CVector &v1,CVector &v2)//矢量的叉积
{
	CVector vector;
	vector.x=v1.y*v2.z-v1.z*v2.y;
	vector.y=v1.z*v2.x-v1.x*v2.z;
	vector.z=v1.x*v2.y-v1.y*v2.x;
	return vector;
}

