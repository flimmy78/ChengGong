#if !defined(AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_)
#define AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestWin.h : header file
//
#include "base0.h"
#include "jhsyslibl.h"
#include "shockwaveflash.h"
#include "closewin.h"

typedef struct SUBW_PARAM{//�����Ӵ������Զ���
	HWND  hwnd;			//����
	CRect rts;			//����ԭʼ��С
	CRect rt;			//ռ�õľ���
	CRect rtw;			//���ھ���
	BYTE  outline;		//�����
    BYTE  left;			//�����
    BYTE  right;		//�Ҷ���
    BYTE  top;			//�϶���
    BYTE  bottom;		//�¶���
	BYTE  mode;			//ģʽ
}SUBW_PARAM;

typedef struct ROBJ{	//���ж���
	BASE0 *bs;		  	//�����ַ
}ROBJ;
typedef struct RAML{	//��������
	BASE0 *bs;			//�����ַ
	CRect rt;			//ռ�õľ�����
	CGIFAnm gfaml;	    //���Ե�ַ
}RAML;

typedef struct RSCRTXT{	//�����ı�����
	BASE0 *bs;			//�����ַ
	N_SRLTEXT *stx;		//���Ե�ַ
	CRect rt;			//ռ�õľ�����
	int xl,yl;			//��ǰλ��
	int w,h;			//����
}RSCRTXT;

typedef struct RSELFCTL{
	CRect rt;			//ռ�õľ�����
	int   sid;			//��������ID
	BYTE  cansize;		//�ܷ�ı��С
	SUBW_PARAM swp;		//������ز���  
	N_SELFCTL *stl;		//���Ե�ַ
}RSELFCTL;

typedef struct RFLOW{	//�����߶���
	BASE0  *bs;			//�����ַ
	N_FLOW *flw;		//���Ե�ַ
	HRGN  hrgn;			//����
	int   ptsum;		//����
	POINT pt[20];		//��
	CRect rt;			//ռ�õľ�����
}RFLOW;

/*typedef struct RTREND{	//�����߶���
	BASE0  *bs;			//�����ַ
	N_TREND *td;		//���Ե�ַ
	BYTE jg;			//���
	BYTE seg;			//����
	BYTE js;			//��ǰ����
	CRect rt;			//ռ�õľ�����
}RTREND;*/


//��ť�������в�����ʽ
typedef struct RPUSH{	//76
	BASE0  *bs;			//�����ַ
	CRect  rt;			//ռ�õľ�����
	N_PUSH *psh;		//���Ե�ַ
}RPUSH;

typedef struct RACTOBJ{	//�����
	BASE0    *bs;		//�����ַ
	N_ACTOBJ *act;		//���Ե�ַ
	CRect  rt;			//ռ�õľ�����
	double curval;		//ʵʱֵ
	double maxv;		//���ֵ
	double minv;		//��Сֵ
	CDRect  oldrt;		//ԭ����λ��
	CDRect  currt;		//��ǰλ��
	WORD   picw,pich;	//��ʾͼƬ�Ŀ��
	short  picj;		//ͼƬ�ļ�¼��
	BYTE   js;			//��ǰ����
	DPOINT  *pt;			//·��
	int    ptsum;		//����
}RACTOBJ;



typedef struct RFLASH{
	CRect rt;			//ռ�õľ�����
	N_FLASH *fsh;		//���Ե�ַ
	CShockwaveFlash fshw;//flash����
}RFLASH;
/////////////////////////////////////////////////////////////////////////////
// TestWin window

class TestWin : public CWnd
{
// Construction
public:
	TestWin();

// Attributes
public:

// Operations
public:
	void SetPage();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TestWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TestWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(TestWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void pqjs(int i);
	void ComputZoom();
	void EndTest();
	void GetActPicMsg(int i);
	void CreateFlwRgn(int j);
	void GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas);
	void ClrStrEnter(char *str);
	int  GetLineNum(char *str);
	void GetObjFromDbm();
	
	void MovePic(CPoint point);
	void RunFunctModule(char *mstring);
	HWND GetSlfCtl(int id);
	void RunPushCmd(int j);
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void AutoSetActValue(int i);
	void ShowD(HDC hdc, CRect rt);
	void ShowC();
	void ShowB(HDC hdc,CRect rt);
	void ShowA();
	void demodtime(HDC hdc);
	void ShowAFlow(HDC hdc);
	void ShowFlow(HDC hdc);
	void demoactobj(HDC hdc);
	void ShowScrTxt(HDC hdc);
	void ShowAScrTxt(HDC hdc, int j,int mode=0);
	void ShowGifAml(HDC hdc);
	void DemoStatus(HDC hdc,int enable=1);
	void DemoAnalog(HDC hdc,int enable=1);
	void FreeMem();
	void ShowActObj(HDC hdc,int x,int y,int k);
	void Show(HDC hdc, CRect rt);
	void ComputMaxXY();
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas,int ly=1);
	CDIB mbg; //��������
	CDIB msr; //��ʾ����
	CDIB mtp; //�м仭��
	double oldzm; //ԭ�зŴ���
	int oldsel;
	CRect srt;
	CPoint pt1;
	int xmax,ymax;

	int dnbz;
	int dx,dy;
	int wx,wy;
	int wd,hg;  //����Ŀ��
	int cp;
	int flwjg;  //�����߶�̬���
	//////////////����ʱ����ָ��/////////////////////
	ROBJ *r_da;		//���ڶ���  
	int dtsum;		//����
	ROBJ *r_tm;		//ʱ�����
	int tmsum;		//����
	RAML *r_am;		//��������
	int amsum;		//����
	RSCRTXT *r_sc;	//�����ı�����
	int scsum;		//����
	RSELFCTL *r_sf; //�����ؼ�
	int sfsum;		//����
	RFLOW    *r_fw; //������
	int fwsum;		//����	
	RPUSH    *r_ph; //��ť
	int phsum;		//����
	RACTOBJ  *r_at; //�����
	int atsum;		//����
	RFLASH   *r_fsh;//FLASH����
	int fssum;		//����


	CCloseWin clsw;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_)
