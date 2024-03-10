// ZBuffer.h: interface for the CZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
#define AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Bucket.h"//Ͱͷ�ļ�
#include "Vector.h"//ʸ��ͷ�ļ�
#include "Lighting.h"//��Դͷ�ļ�
#include "Material.h"//����ͷ�ļ�

class CZBuffer  //��Ȼ�����
{
public:
	CZBuffer();
    virtual ~CZBuffer();
	void SetPoint(CPi3 *,CVector *,int);
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddEt(CAET *);//�ϲ�ET��
	void EtOrder();//ET������
	void Phong(CDC *,CP3,CLighting *,CMaterial *);//���
    CVector Interpolation(double,double,double,CVector,CVector);//��ʸ���Բ�ֵ	
protected:
	int PNum;//����ĸ���
	CPi3 *P;//���㶯̬����
	CVector *VN;//����ķ�ʸ����̬����
	CAET *CurrentE,*HeadE,*Edge;//��Ч�߱���
	CBucket *CurrentB,*HeadB;//Ͱ����
};

#endif // !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
