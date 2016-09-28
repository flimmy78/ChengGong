#if !defined(AFX_DMJSDLG_H__5C21DF7B_43B3_4D1F_951A_E895C1949642__INCLUDED_)
#define AFX_DMJSDLG_H__5C21DF7B_43B3_4D1F_951A_E895C1949642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DmJsDlg.h : header file
//
#include "middll.h"
#include "readrltd.h"
#include "dbedit.h"
#include "math.h"

//��������ṹ
typedef struct PRESMDATA
{
	DWORD  ID;							//����ID
	char  Name[45];						//��������
	float  Vmax;						//��������ֵ
	float  Vmin;						//��������ֵ
	float  curval;						//��ǰ����ֵ
	float  Par;							//���渺���ʸ澯��
	float  fz;							//������
	char   gjstr[16];					//�澯��
	char   msg[45];						//��ע��Ϣ
	DWORD  color;						//��ʾ��ɫ
}PRESMDATA;
/////////////////////////////////////////////////////////////////////////////
// DmJsDlg dialog

class DmJsDlg : public CDialog
{
// Construction
public:
	DmJsDlg(CWnd* pParent = NULL);   // standard constructor
	~DmJsDlg();
	int wx,wy;
	common_PreDefSF  pdf[256];
	PRESMDATA        pdm[256]; //��ʾ��
	int num;
	ReadRltD  *rrd;
	dbedit  dbwin;	 //���ݴ���
// Dialog Data
	//{{AFX_DATA(DmJsDlg)
	enum { IDD = IDD_DMDLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DmJsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DmJsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetAllList();
	void TimeRead();
};

//Ϊ����Ƚϸ���
int CmpRateForSort(common_PreDefSF* pOne,common_PreDefSF* pTwo);
inline int CmpRateForSort(common_PreDefSF* pOne,common_PreDefSF* pTwo)
{
	double fRateOne=0.0f;
	double fRateTwo=0.0f;
	if(pOne->Vmax>0.0 && pOne->curval>0.0f)
		fRateOne=fabs(pOne->curval/pOne->Vmax);
	else if(pOne->curval<0.0 && pOne->Pcur<0.0)
		fRateOne=fabs(pOne->curval/pOne->Pcur);

	if(pTwo->Vmax>0 && pTwo->curval>0)
		fRateTwo=fabs(pTwo->curval/pTwo->Vmax);
	else if(pTwo->curval<0 && pTwo->Pcur<0)
		fRateTwo=fabs(pTwo->curval/pTwo->Pcur);

	if(fRateOne>fRateTwo)
		return TRUE;
	else
		return FALSE;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMJSDLG_H__5C21DF7B_43B3_4D1F_951A_E895C1949642__INCLUDED_)
