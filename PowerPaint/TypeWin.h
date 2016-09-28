#if !defined(AFX_TYPEWIN_H__49896D9B_330F_46FC_A2C5_9E67E6707CC2__INCLUDED_)
#define AFX_TYPEWIN_H__49896D9B_330F_46FC_A2C5_9E67E6707CC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TypeWin.h : header file
//
#include "jhsyslibl.h"

typedef struct _TYPESEL{
	char name[32];  //����
	char sel;		//ѡ��״̬
	int  COMMAND;   //����
	int  start;		//��ʼλ��
	int  len;		//λ�ÿ��
}TYPESEL;
/////////////////////////////////////////////////////////////////////////////
// CTypeWin window

class CTypeWin : public CWnd
{
// Construction
public:
	CTypeWin();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReDraw();
	void SetCursel(int index);
	bool AddSelStr(char *name,int cmd);
	virtual ~CTypeWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTypeWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Show();
	CDIB mdc;
	CScrollBar xbar;
	int wx,wy;
	LOGFONT lf;
	DWORD fcolor;
	TYPESEL  tsl[32]; //������32��ѡ��
	int ssum;		  //��ǰѡ����
	int cursel;		  //��ǰѡ��
	int dx;			  //��ǰ��ʾ��DXλ��
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPEWIN_H__49896D9B_330F_46FC_A2C5_9E67E6707CC2__INCLUDED_)
