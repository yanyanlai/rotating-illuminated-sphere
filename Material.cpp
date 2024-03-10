// Material.cpp: implementation of the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Material.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaterial::CMaterial()
{
	M_Ambient=CRGB(1.0,1.0,1.0);//���ʶԻ�����ķ�����
	M_Diffuse=CRGB(1.0,1.0,1.0);//���ʶ��������ķ�����
	M_Specular=CRGB(1.0,1.0,1.0);//���ʶԾ��淴���ķ�����
	M_Exp=1.0;//�߹�ָ��
}

CMaterial::~CMaterial()
{

}

void CMaterial::SetAmbient(CRGB c)
{
	M_Ambient=c;
}

void CMaterial::SetDiffuse(CRGB c)
{
	M_Diffuse=c;
}

void CMaterial::SetSpecular(CRGB c)
{
	M_Specular=c;
}

void CMaterial::SetExp(double Exp)
{
	M_Exp=Exp;
}