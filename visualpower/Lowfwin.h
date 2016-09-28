#if !defined(AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_)
#define AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lowfwin.h : header file
//

#include "jhsyslibl.h"
#include "clisock.h"
#include "pwptdef.h"
#include "readrltd.h"


typedef struct CONCFG //��������
{
	in_addr laddr;    //���ص�ַ
	in_addr saddr;	  //��������ַ
	WORD port;		  //�������ں�
}CONCFG;


typedef struct LFData
{
	int 	LineID;		//��·ID
	BYTE	Type;		//���ͽ�����ֱ��
	int     bsum;		//������������
	float   maxv;		//����޷�ֵ
	double  pha;		//��λ
	float   lastv;		//�ϴεķ�ֵ
	LFSDATA  data[8];	//���յ�����,���Ի���8������
	//BYTE valid;			//������Ч
}LFData;

/////////////////////////////////////////////////////////////////////////////
// Lowfwin window

class Lowfwin : public CWnd
{
// Construction
public:
	Lowfwin();
	clisock cliw;		//�ͻ�SOCK����
	CONCFG concfg[4];	//��������
	int  consum;		//��������
	int  curcon;		//��ǰ����
	int wx,wy;
	CDIB mdc;
	float sfr;			//��ǰƵ��
	float sval;			//��ǰ��ֵ
	int   curtype;		//��ǰ��ʾ������
	int   curid;		//��ǰID
	char  name[24];		//��·����
	float *vpt;			//��Ƶ������
	int	  vlen;			//��Ƶ�����ݳ���
	int   showbl;		//��ʾ�ı���
	int   curfct;		//��ǰ���ܣ�0=���� 1=��ʾ���ӷ�����״̬ 2=��ʾ����
	///////////////////////////////////////////////////////////////////////
	//����
	int nLine;			//��·��
	LFData lwf[MAXLWF];	//��ƴ������,���12
	int lbdown;			//���ѹ�±�־
	int islowf;			//�Ƿ��Ƶ��״̬
	ReadRltD  *rrd;
// Attributes
public:
	void SetFunct(int funct);
	bool GetABufData(LFSDATA &lfd,int id,int type);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Lowfwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	bool IsLowFLine(int id,int type);
	void EndLowf();
	void StartLowf();
	void LowFShow();
	virtual ~Lowfwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(Lowfwin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConnect();
	afx_msg void OnRecData();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckCon();
	void RecFlowLowF(char *buf,DWORD len);
	void SetLowFData(LFDATA &lfd);
	void DemoLowFData();
	void InitLowfLine();
	void DrawControll();
	void SendCheck();
	void LoginSvr();
	DWORD ChangeHL(DWORD param);
	void CreateConCfg();
	void Draw();
	LOGFONT lf;
	DWORD fcolor;
	CSliderCtrl sld;
	int svrchk;
	int sounding;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_)
