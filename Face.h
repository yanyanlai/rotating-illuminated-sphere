// Face.h: interface for the CFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE_H__288D3AA0_BB35_4E92_9AE4_4939AE57DEC9__INCLUDED_)
#define AFX_FACE_H__288D3AA0_BB35_4E92_9AE4_4939AE57DEC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Vector.h"

class CFace  //����
{
public:
	CFace();
	CFace(int*,int);
	virtual ~CFace();
	void SetNormal(CP3,CP3,CP3);//��С�淨ʸ��
	int En;//��ı���
	int *pIndex;//�涥�������Ŷ�̬����
	CVector Normal;//��ķ�ʸ��
};

#endif // !defined(AFX_FACE_H__288D3AA0_BB35_4E92_9AE4_4939AE57DEC9__INCLUDED_)
