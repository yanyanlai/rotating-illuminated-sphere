// Fill.h: interface for the CFill class.
//
//////////////////////////////////////////////////////////////////////
/*
#if !defined(AFX_FILL_H__EDD87BAB_FC56_479F_9769_F92E81FDBCAC__INCLUDED_)
#define AFX_FILL_H__EDD87BAB_FC56_479F_9769_F92E81FDBCAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Bucket.h"

class CFill  //�����
{
public:
	CFill();
	virtual ~CFill();
	void SetPoint(CPi2 *p,int);//��ĳ�ʼ��
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddEt(CAET *);//�ϲ�ET��
	void EtOrder();//ET������
	void Gouraud(CDC *);//�������
    CRGB Interpolation(double,double,double,CRGB,CRGB);//���Բ�ֵ
	protected:
	int     PNum;//�������
	CPi2    *P;//�������궯̬����
	CAET    *HeadE,*CurrentE,*Edge;//��Ч�߱���ָ��
	CBucket *HeadB,*CurrentB;//Ͱ����ָ��
};

#endif // !defined(AFX_FILL_H__EDD87BAB_FC56_479F_9769_F92E81FDBCAC__INCLUDED_)
*/