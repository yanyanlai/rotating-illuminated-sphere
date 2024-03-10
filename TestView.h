// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector.h"//����ʸ����
#include "Face.h"//��������
#include "Lighting.h"//����������
#include "Fill.h"//���������
#include "ZBuffer.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:
	void ReadPoint();//���붥���
	void ReadFace();//�������
	void InitParameter();//������ʼ��
	void PerProject(CP3);//͸��ͶӰ
	void DoubleBuffer();//˫����
	void DrawObject(CDC *);//����������		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double R,Theta,Phi;//�ӵ����û�����ϵ�е�������
	double d;//�Ӿ�
	double k[9];//���㳣��
	CP3 ViewPoint;//�ӵ�������
	CP3 ScreenP;//��Ļ����ϵ�Ķ�ά�����
	CP3 *P;//��Ķ���һά����
	CFace **F;//��Ķ�ά����
	int afa,beta,N1,N2;//�����
	int LightNum;//��Դ����
	CLighting *pLight;//���ջ���
	CMaterial *pMaterial;//�������
	BOOL Play;//��������
	CZBuffer zbuf;//�����
	// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMENUPlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateMENUPlay(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMENULRed();
	afx_msg void OnMENULGreen();
	afx_msg void OnMENULBlue();
	afx_msg void OnMENULWhite();
	afx_msg void OnMENUMGreen();
	afx_msg void OnMENUMBlue();
	afx_msg void OnMENUMWhite();
	afx_msg void OnMENUMRed();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMENUL2Red();
	afx_msg void OnMENUL2Green();
	afx_msg void OnMENUL2Blue();
	afx_msg void OnMENUL2White();
	afx_msg void OnMENUL3Red();
	afx_msg void OnMENUL3Green();
	afx_msg void OnMENUL3Blue();
	afx_msg void OnMENUL3White();
	afx_msg void OnMENUMGold();
	afx_msg void OnMENULClose();
	afx_msg void OnMENUL2Close();
	afx_msg void OnMENUL3Close();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument()
   { return (CTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
