// ZBuffer.cpp: implementation of the CZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "ZBuffer.h"
#define ROUND(a) int(a+0.5)
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZBuffer::CZBuffer()
{

}

CZBuffer::~CZBuffer()
{
	delete []P;
}

void CZBuffer::SetPoint(CPi3 *p,CVector *vn,int m)
{
	P=new CPi3[m];
	VN=new CVector[m];
    for(int i=0;i<m;i++)
	{
		P[i]=p[i];	
		VN[i]=vn[i];
	}
	PNum=m;
}

void CZBuffer::CreateBucket()//创建桶表
{
	int yMin,yMax;
	yMin=yMax=P[0].y;
	for(int i=0;i<PNum;i++)//查找多边形所覆盖的最小和最大扫描线
	{
		if(P[i].y<yMin)
		{
			yMin=P[i].y;//扫描线的最小值
		}
		if(P[i].y>yMax)
		{
			yMax=P[i].y;//扫描线的最大值
		}
	}
	for(int y=yMin;y<=yMax;y++)
	{
		if(yMin==y)//建立桶头结点
		{
			HeadB=new CBucket;//建立桶的头结点
			CurrentB=HeadB;//CurrentB为CBucket当前结点指针
			CurrentB->ScanLine=yMin;
			CurrentB->pET=NULL;//没有连接边链表
			CurrentB->next=NULL;
		}
		else//建立桶的其它结点
		{
			CurrentB->next=new CBucket;
			CurrentB=CurrentB->next;
			CurrentB->ScanLine=y;
			CurrentB->pET=NULL;
			CurrentB->next=NULL;
		}
	}
}

void CZBuffer::CreateEdge()//创建边表
{
	for(int i=0;i<PNum;i++)
	{
		CurrentB=HeadB;
		int j=(i+1)%PNum;//边的第二个顶点，P[i]和P[j]构成边
		if(P[i].y<P[j].y)//边的终点比起点高
		{
			Edge=new CAET;
			Edge->x=P[i].x;//计算ET表的值
			Edge->yMax=P[j].y;
			Edge->k=(P[j].x-P[i].x)/(P[j].y-P[i].y);//代表1/k
			Edge->pb=P[i];//绑定顶点和颜色
			Edge->pe=P[j];
			Edge->vb=VN[i];//绑定顶点法矢量
			Edge->ve=VN[j];
			Edge->next=NULL;
			while(CurrentB->ScanLine!=P[i].y)//在桶内寻找该边的yMin
			{
				CurrentB=CurrentB->next;//移到yMin所在的桶结点
			}		
		}
		if(P[j].y<P[i].y)//边的终点比起点低
		{
			Edge=new CAET;
			Edge->x=P[j].x;
			Edge->yMax=P[i].y;
			Edge->k=(P[i].x-P[j].x)/(P[i].y-P[j].y);
			Edge->pb=P[i];
			Edge->pe=P[j];
			Edge->vb=VN[i];//绑定顶点法矢量
			Edge->ve=VN[j];
			Edge->next=NULL;
			while(CurrentB->ScanLine!=P[j].y)
			{
				CurrentB=CurrentB->next;
			}
		}
		if(P[j].y!=P[i].y)
		{
			CurrentE=CurrentB->pET;
			if(CurrentE==NULL)
			{
				CurrentE=Edge;
				CurrentB->pET=CurrentE;
			}
			else
			{
				while(CurrentE->next!=NULL)
				{
					CurrentE=CurrentE->next;
				}
				CurrentE->next=Edge;
			}
		}
	}
}

void CZBuffer::Phong(CDC *pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial)//填充多边形
{
	double	z=0.0;//当前扫描线的z
	double	zStep=0.0;//当前扫描线随着x增长的z步长
	double	A,B,C,D;//平面方程Ax+By+Cz＋D=0的系数
	CVector V21(P[1],P[2]),V10(P[0],P[1]);
	CVector VN=V21*V10;
	A=VN.X();B=VN.Y();C=VN.Z();
	D=-A*P[1].x-B*P[1].y-C*P[1].z;
	//计算curDeep;从x=xMin开始计算，此时针对yi
	zStep=-A/C;//计算直线z增量
	CAET *T1,*T2;
	HeadE=NULL;	
	for(CurrentB=HeadB;CurrentB!=NULL;CurrentB=CurrentB->next)
	{
		for(CurrentE=CurrentB->pET;CurrentE!=NULL;CurrentE=CurrentE->next)
		{
			Edge=new CAET;
			Edge->x=CurrentE->x;
			Edge->yMax=CurrentE->yMax;
			Edge->k=CurrentE->k;
			Edge->pb=CurrentE->pb;
			Edge->pe=CurrentE->pe;
			Edge->vb=CurrentE->vb;
			Edge->ve=CurrentE->ve;
			Edge->next=NULL;
			AddEt(Edge);
		}
		EtOrder();	
		T1=HeadE;
		if(T1==NULL)
		{
			return;
		}
		while(CurrentB->ScanLine>=T1->yMax)//下闭上开
		{
			T1=T1->next;
			HeadE=T1;
			if(HeadE==NULL)
				return;
		}
		if(T1->next!=NULL)
		{
			T2=T1;
			T1=T2->next;
		}
		while(T1!=NULL)
		{
			if(CurrentB->ScanLine>=T1->yMax)//下闭上开
			{
				T2->next=T1->next;
				T1=T2->next;
			}
			else
			{
				T2=T1;
				T1=T2->next;
			}
		}
		CVector na,nb,nf;//na、nb代表边上任意点的法矢量，nf代表面上任意点的法矢量
		na=Interpolation(CurrentB->ScanLine,HeadE->pb.y,HeadE->pe.y,HeadE->vb,HeadE->ve);
		nb=Interpolation(CurrentB->ScanLine,HeadE->next->pb.y,HeadE->next->pe.y,HeadE->next->vb,HeadE->next->ve);
		BOOL Flag=FALSE;
		double xb,xe;//扫描线的起点和终点坐标
		for(T1=HeadE;T1!=NULL;T1=T1->next)
		{
			if(Flag==FALSE)
			{
				xb=T1->x;
				z=-(xb*A+CurrentB->ScanLine*B+D)/C;//z=-(Ax+By-D)/C
				Flag=TRUE;
			}
			else
			{
				xe=T1->x;
				for(double x=xb;x<xe;x++)//左闭右开
				{
					nf=Interpolation(x,xb,xe,na,nb);	
					CRGB c=pLight->Lighting(ViewPoint,CP3(ROUND(x),CurrentB->ScanLine,z),nf,pMaterial);		
					pDC->SetPixel(ROUND(x),CurrentB->ScanLine,RGB(c.red*255,c.green*255,c.blue*255));
					z+=zStep;					
				}
				Flag=FALSE;
			}
		}
		for(T1=HeadE;T1!=NULL;T1=T1->next)//边的连续性
		{
			T1->x=T1->x+T1->k;
		}
		
	}
	delete HeadB;
	delete HeadE;
	delete CurrentE;
	delete CurrentB;
	delete Edge;	
}

void CZBuffer::AddEt(CAET *NewEdge)//合并ET表
{
	CAET *CE;
	CE=HeadE;
	if(CE==NULL)
	{
		HeadE=NewEdge;
		CE=HeadE;
	}
	else
	{
		while(CE->next!=NULL)
		{
			CE=CE->next;
		}
		CE->next=NewEdge;
	}
}
void CZBuffer::EtOrder()//边表的冒泡排序算法
{
	CAET *T1,*T2;
	int Count=1;
	T1=HeadE;
	if(T1==NULL)
	{
		return;
	}
	if(T1->next==NULL)//如果该ET表没有再连ET表
	{
		return;//桶结点只有一条边，不需要排序
	}
	while(T1->next!=NULL)//统计结点的个数
	{
		Count++;
		T1=T1->next;
	}
	for(int i=1;i<Count;i++)//冒泡排序
	{
		T1=HeadE;
		if(T1->x>T1->next->x)//按x由小到大排序
		{
			T2=T1->next;
			T1->next=T1->next->next;
			T2->next=T1;
			HeadE=T2;
		}
		else
		{
			if(T1->x==T1->next->x)
			{
				if(T1->k>T1->next->k)//按斜率由小到大排序
				{
					T2=T1->next;
					T1->next=T1->next->next;
					T2->next=T1;
					HeadE=T2;
				}
			}
		}
		T1=HeadE;
		while(T1->next->next!=NULL)
		{
			T2=T1;
			T1=T1->next;
			if(T1->x>T1->next->x)//按x由小到大排序
			{
				T2->next=T1->next;
				T1->next=T1->next->next;
				T2->next->next=T1;
				T1=T2->next;
			}
			else
			{
				if(T1->x==T1->next->x)
				{
					if(T1->k>T1->next->k)//按斜率由小到大排序
					{
						T2->next=T1->next;
						T1->next=T1->next->next;
						T2->next->next=T1;
						T1=T2->next;
					}
				}
			}
		}
	}
}

CVector CZBuffer::Interpolation(double t,double t1,double t2,CVector v1,CVector v2)//矢量线性插值
{
	CVector v;
	v=v1*(t-t2)/(t1-t2)+v2*(t-t1)/(t2-t1);
	return v;
}

