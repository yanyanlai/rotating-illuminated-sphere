// Fill.cpp: implementation of the CFill class.
//
//////////////////////////////////////////////////////////////////////
/*
#include "stdafx.h"
#include "Test.h"
#include "Fill.h"
#define ROUND(x) int(x+0.5)//���������
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFill::CFill()
{

}

CFill::~CFill()
{

}

void CFill::SetPoint(CPi2 *p,int m)
{
	P=new CPi2[m];
	for(int i=0;i<m;i++)
	{
		P[i]=p[i];	
	}
	PNum=m;
}
void CFill::CreateBucket()//����Ͱ��
{
	int yMin,yMax;
	yMin=yMax=P[0].y;
	for(int i=0;i<PNum;i++)//���Ҷ���������ǵ���С�����ɨ����
	{
		if(P[i].y<yMin)
		{
			yMin=P[i].y;//ɨ���ߵ���Сֵ
		}
		if(P[i].y>yMax)
		{
			yMax=P[i].y;//ɨ���ߵ����ֵ
		}
	}
	for(int y=yMin;y<=yMax;y++)
	{
		if(yMin==y)//����Ͱͷ���
		{
			HeadB=new CBucket;//����Ͱ��ͷ���
			CurrentB=HeadB;//CurrentBΪCBucket��ǰ���ָ��
			CurrentB->ScanLine=yMin;
			CurrentB->pET=NULL;//û�����ӱ�����
			CurrentB->next=NULL;
		}
		else//����Ͱ���������
		{
			CurrentB->next=new CBucket;
			CurrentB=CurrentB->next;
			CurrentB->ScanLine=y;
			CurrentB->pET=NULL;
			CurrentB->next=NULL;
		}
	}
}

void CFill::CreateEdge()//�����߱�
{
	for(int i=0;i<PNum;i++)
	{
		CurrentB=HeadB;
		int j=(i+1)%PNum;//�ߵĵڶ������㣬P[i]��P[j]��Թ��ɱ�
		if(P[i].y<P[j].y)//�ߵ��յ������
		{
			Edge=new CAET;
			Edge->x=P[i].x;//����ET���ֵ
			Edge->yMax=P[j].y;
			Edge->k=(P[j].x-P[i].x)/(P[j].y-P[i].y);//����1/k
			Edge->pb=P[i];//�󶨶������ɫ
			Edge->pe=P[j];
			Edge->next=NULL;
			while(CurrentB->ScanLine!=P[i].y)//��Ͱ��Ѱ�ҵ�ǰ�ߵ�yMin
			{
				CurrentB=CurrentB->next;//�Ƶ�yMin���ڵ�Ͱ���
			}		
		}
		if(P[j].y<P[i].y)//�ߵ��յ������
		{
			Edge=new CAET;
			Edge->x=P[j].x;
			Edge->yMax=P[i].y;
			Edge->k=(P[i].x-P[j].x)/(P[i].y-P[j].y);
			Edge->pb=P[i];
			Edge->pe=P[j];
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

void CFill::Gouraud(CDC *pDC)//�������
{
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
			Edge->next=NULL;
			AddEt(Edge);
		}
		EtOrder();	
		T1=HeadE;
		if(T1==NULL)
		{
			return;
		}
		while(CurrentB->ScanLine>=T1->yMax)//�±��Ͽ�
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
			if(CurrentB->ScanLine>=T1->yMax)//�±��Ͽ�
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
		CRGB Ca,Cb,Cf;//Ca��Cb��������������ɫ��Cf����������������ɫ
		Ca=Interpolation(CurrentB->ScanLine,HeadE->pb.y,HeadE->pe.y,HeadE->pb.c,HeadE->pe.c);
		Cb=Interpolation(CurrentB->ScanLine,HeadE->next->pb.y,HeadE->next->pe.y,HeadE->next->pb.c,HeadE->next->pe.c);
		BOOL Flag=FALSE;
		double xb,xe;//ɨ���ߵ������յ�����
		for(T1=HeadE;T1!=NULL;T1=T1->next)
		{
			if(Flag==FALSE)
			{
				xb=T1->x;
				Flag=TRUE;
			}
			else
			{
				xe=T1->x;
				for(double x=xb;x<xe;x++)//����ҿ�
				{
					Cf=Interpolation(x,xb,xe,Ca,Cb);
					pDC->SetPixel(ROUND(x),CurrentB->ScanLine,RGB(Cf.red*255,Cf.green*255,Cf.blue*255));
				}
				Flag=FALSE;
			}
		}
		for(T1=HeadE;T1!=NULL;T1=T1->next)//�ߵ�������
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

void CFill::AddEt(CAET *NewEdge)//�ϲ�ET��
{
	CAET *CE;//��ǰ�߱�ָ��
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
void CFill::EtOrder()//�߱��ð�������㷨
{
	CAET *T1,*T2;
	int Count=1;
	T1=HeadE;
	if(T1==NULL)
	{
		return;
	}
	if(T1->next==NULL)//�����ET��û������ET��
	{
		return;//Ͱ���ֻ��һ���ߣ�����Ҫ����
	}
	while(T1->next!=NULL)//ͳ�ƽ��ĸ���
	{
		Count++;
		T1=T1->next;
	}
	for(int i=1;i<Count;i++)//ð������
	{
		T1=HeadE;
		if(T1->x>T1->next->x)//��x��С��������
		{
			T2=T1->next;
			T1->next=T2->next;
			T2->next=T1;
			HeadE=T2;
		}
		else
		{
			if(T1->x==T1->next->x)
			{
				if(T1->k>T1->next->k)//��б�ʵ�����С��������
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
			if(T1->x>T1->next->x)//��x��С��������
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
					if(T1->k>T1->next->k)//��б����С��������
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

CRGB CFill::Interpolation(double t,double t1,double t2,CRGB c1,CRGB c2)//���Բ�ֵ
{
	CRGB c;
	c=(t-t2)/(t1-t2)*c1+(t-t1)/(t2-t1)*c2;
	return c;
}
*/