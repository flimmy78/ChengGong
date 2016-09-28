#if !defined(AFX_SENDLG_H__D91D05ED_AC37_439C_8CF1_51D63D2F68CD__INCLUDED_)
#define AFX_SENDLG_H__D91D05ED_AC37_439C_8CF1_51D63D2F68CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SenDlg.h : header file
//
#include "pwptdef.h"
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// SenDlg dialog

class SenDlg : public CDialog
{
// Construction
public:
	SenDlg(CWnd* pParent = NULL);   // standard constructor
	~SenDlg();
	gdata *dbm;
	char str[100];
	int  type;		//����������
	
	RFLOW *r_fw;	//������
	int fwsum;		//����
	RBUS  *r_bs;	//ĸ��
	int bssum;		//����
	POINT *pt;		//�����
	int ptsum;      //�������

	char name[24];  //ѡ���豸������
	int  id;		//ѡ���豸��ID
	int  linetype;	//��·���� 0=������ 1=ֱ����
	int  nodefrom;  //��·��ʼ�ڵ�
	//������̾��
	HANDLE hpr;
	//��ʱ����
	int  nt;
	//ѡ���
	DPOINT selpt;
// Dialog Data
	//{{AFX_DATA(SenDlg)
	enum { IDD = IDD_SENDLG };
	CStatic	m_type;
	CProgressCtrl	m_prg;
	CStatic	m_dev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void StartRun();
	void SaveDataFile();
	void CheckCompute();
	bool IsProcessActive();
	int  ReadLineNodeFrom();
	void CreateMacFile(char *filename);
	void ComputeBus();
	void ComputeBra();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDLG_H__D91D05ED_AC37_439C_8CF1_51D63D2F68CD__INCLUDED_)
