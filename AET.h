// AET.h: interface for the CAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_)
#define AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector.h"

class CAET  //有效边表类
{
public:
	CAET();
	virtual ~CAET();
public:
	double x;//当前x
	int    yMax;//边的最大y值
	double k;//斜率的倒数(x的增量)
	CPi3    pb;//起点坐标
	CPi3    pe;//终点坐标
	CVector vb;//起点矢量
	CVector ve;//终点矢量
	CAET   *next;
};

#endif // !defined(AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_)
