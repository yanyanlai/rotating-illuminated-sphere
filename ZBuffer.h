// ZBuffer.h: interface for the CZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
#define AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Bucket.h"//桶头文件
#include "Vector.h"//矢量头文件
#include "Lighting.h"//光源头文件
#include "Material.h"//材质头文件

class CZBuffer  //深度缓冲类
{
public:
	CZBuffer();
    virtual ~CZBuffer();
	void SetPoint(CPi3 *,CVector *,int);
	void CreateBucket();//创建桶
	void CreateEdge();//边表
	void AddEt(CAET *);//合并ET表
	void EtOrder();//ET表排序
	void Phong(CDC *,CP3,CLighting *,CMaterial *);//填充
    CVector Interpolation(double,double,double,CVector,CVector);//法矢线性插值	
protected:
	int PNum;//顶点的个数
	CPi3 *P;//顶点动态数组
	CVector *VN;//顶点的法矢量动态数组
	CAET *CurrentE,*HeadE,*Edge;//有效边表结点
	CBucket *CurrentB,*HeadB;//桶表结点
};

#endif // !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
