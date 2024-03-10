// Lighting.cpp: implementation of the CLighting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Lighting.h"
#include "cmath"
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLighting::CLighting()
{
	LightNum=1;
	Light=new CLight[LightNum];
	Ambient=CRGB(0.3,0.3,0.3);//������㶨����
}

CLighting::~CLighting()
{
	if(Light)
	{
		delete []Light;
		Light=NULL;
	}
}

CLighting::CLighting(int lightnum)
{
	LightNum=lightnum;
	Light=new CLight[lightnum];
	Ambient=CRGB(0.3,0.3,0.3);
}

CRGB CLighting::Lighting(CP3 ViewPoint,CP3 Point,CVector Normal,CMaterial *pMaterial)
{	
	double LastR=0.0,LastG=0.0,LastB=0.0;
	for(int i=0;i<LightNum;i++)//���Թ�Դ
	{	
		Light[i].GlobalToXYZ();
		if(Light[i].L_OnOff)
		{		
			double IRed=0,IGreen=0,IBlue=0;
			//��һ��������˥������
			double c0=Light[i].L_C0;
			double c1=Light[i].L_C1;
			double c2=Light[i].L_C2;
			CVector VL(Point,Light[i].L_Position);//ָ���Դ��ʸ��
			double d=VL.Mold();//�⴫���ľ��룬��������VL��ģ
			double a=(1.0/(c0+c1*d+c2*d*d));//����˥������
			a=MIN(1.0,a);				
			//�ڶ����������������
			VL=VL.Unit();//��ʸ����λ��
			CVector VN=Normal;
			VN=VN.Unit();//��ʸ����λ��			
			double CosTheta=Dot(VL,VN);
			CosTheta=MAX(0.0,CosTheta);//theta����PI/2���䲻��
			IRed+=Light[i].L_Diffuse.red*pMaterial->M_Diffuse.red*CosTheta*a;
			IGreen+=Light[i].L_Diffuse.green*pMaterial->M_Diffuse.green*CosTheta*a;
			IBlue+=Light[i].L_Diffuse.blue*pMaterial->M_Diffuse.blue*CosTheta*a;
			//�����������뾵�淴���
			if(CosTheta>0 && CosTheta<PI/2)//���߿������䵽����
			{
				CVector VS(Point,ViewPoint);//VS��ʸ��
				VS=VS.Unit();
				CVector VH=(VL+VS)/(VL+VS).Mold();//ƽ��ʸ��	
				double n=pow(Dot(VH,VN),pMaterial->M_Exp);
				IRed+=Light[i].L_Specular.red*pMaterial->M_Specular.red*n*a;
				IGreen+=Light[i].L_Specular.green*pMaterial->M_Specular.green*n*a;
				IBlue+=Light[i].L_Specular.blue*pMaterial->M_Specular.blue*n*a;
			}
			//�ۼӵ�������ɫ
			LastR+=IRed;
			LastG+=IGreen;
			LastB+=IBlue;
		}
	}
	LastR+=Ambient.red*pMaterial->M_Ambient.red;//���뻷����
	LastG+=Ambient.green*pMaterial->M_Ambient.green;
	LastB+=Ambient.blue*pMaterial->M_Ambient.blue;
	LastR = (LastR < 0.0) ? 0.0 : ((LastR > 1.0) ? 1.0 : LastR);//��ɫ��һ��[0,1]����
	LastG = (LastG < 0.0) ? 0.0 : ((LastG > 1.0) ? 1.0 : LastG);
	LastB = (LastB < 0.0) ? 0.0 : ((LastB > 1.0) ? 1.0 : LastB);
	return CRGB(LastR,LastG,LastB);//��ɫ��ֵ
}