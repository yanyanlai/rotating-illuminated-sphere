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
	Ambient=CRGB(0.3,0.3,0.3);//环境光恒定不变
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
	for(int i=0;i<LightNum;i++)//来自光源
	{	
		Light[i].GlobalToXYZ();
		if(Light[i].L_OnOff)
		{		
			double IRed=0,IGreen=0,IBlue=0;
			//第一步，计算衰减因子
			double c0=Light[i].L_C0;
			double c1=Light[i].L_C1;
			double c2=Light[i].L_C2;
			CVector VL(Point,Light[i].L_Position);//指向光源的矢量
			double d=VL.Mold();//光传播的距离，等于向量VL的模
			double a=(1.0/(c0+c1*d+c2*d*d));//二次衰减函数
			a=MIN(1.0,a);				
			//第二步，加入漫反射光
			VL=VL.Unit();//光矢量单位化
			CVector VN=Normal;
			VN=VN.Unit();//法矢量单位化			
			double CosTheta=Dot(VL,VN);
			CosTheta=MAX(0.0,CosTheta);//theta大于PI/2照射不到
			IRed+=Light[i].L_Diffuse.red*pMaterial->M_Diffuse.red*CosTheta*a;
			IGreen+=Light[i].L_Diffuse.green*pMaterial->M_Diffuse.green*CosTheta*a;
			IBlue+=Light[i].L_Diffuse.blue*pMaterial->M_Diffuse.blue*CosTheta*a;
			//第三步，加入镜面反射光
			if(CosTheta>0 && CosTheta<PI/2)//光线可以照射到物体
			{
				CVector VS(Point,ViewPoint);//VS视矢量
				VS=VS.Unit();
				CVector VH=(VL+VS)/(VL+VS).Mold();//平分矢量	
				double n=pow(Dot(VH,VN),pMaterial->M_Exp);
				IRed+=Light[i].L_Specular.red*pMaterial->M_Specular.red*n*a;
				IGreen+=Light[i].L_Specular.green*pMaterial->M_Specular.green*n*a;
				IBlue+=Light[i].L_Specular.blue*pMaterial->M_Specular.blue*n*a;
			}
			//累加到最后的颜色
			LastR+=IRed;
			LastG+=IGreen;
			LastB+=IBlue;
		}
	}
	LastR+=Ambient.red*pMaterial->M_Ambient.red;//加入环境光
	LastG+=Ambient.green*pMaterial->M_Ambient.green;
	LastB+=Ambient.blue*pMaterial->M_Ambient.blue;
	LastR = (LastR < 0.0) ? 0.0 : ((LastR > 1.0) ? 1.0 : LastR);//颜色归一到[0,1]区间
	LastG = (LastG < 0.0) ? 0.0 : ((LastG > 1.0) ? 1.0 : LastG);
	LastB = (LastB < 0.0) ? 0.0 : ((LastB > 1.0) ? 1.0 : LastB);
	return CRGB(LastR,LastG,LastB);//颜色赋值
}