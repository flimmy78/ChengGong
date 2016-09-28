#if !defined(AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_)
#define AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuWin.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// MenuWin window

class MenuWin : public CWnd
{
// Construction
public:
	MenuWin();
	int wx,wy;
	int pw,ph;				//ҳ��ĸ߶ȺͿ��
	int selpush;			//ѡ��İ�ť
	CDIB mbg;				//��������
	CDIB msr;				//��ʾ����
// Attributes
public:
	gdata dbm;       //���ݶ���
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MenuWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MenuWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(MenuWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ROBJ  *r_da;	//���ڶ���  
	int   dtsum;	//����
	ROBJ  *r_tm;	//ʱ�����
	int   tmsum;	//����
	RAML  *r_am;	//��������
	int   amsum;	//����
	RSCRTXT *r_sc;	//�����ı�����
	int   scsum;	//����
	RSELFCTL *r_sf; //�����ؼ�
	int   sfsum;	//����
	RFLASH   *r_fsh;//FLASH����
	int fssum;		//����
	RPUSH    *r_ph; //��ť
	int phsum;		//����

	void DrawShow();
	HWND GetSlfCtl(int id);
	void RunPushCmd(int j);
	void PaintShow(HDC hdc, CRect rt);
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void MouseLBUp(CPoint point);
	void MouseLBDown(CPoint point);
	int  GetCursor(CPoint point);
	void Set3DEnv();
	void GetObjFromDbm();
	void InitMoveObj();
	void FreeMem();
	void EndShow();
	void ShowA(CDIB&mdc);
	CRect srt;
	int dtupdate;   //ʱ����±�־
	int dx,dy;
	int cursor;
	int hmax,curpos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_)
