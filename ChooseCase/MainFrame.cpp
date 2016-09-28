// MainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrame.h"
//#include "WelcomePage.h"
#include "FirstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}


BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	//������ݿ�ƽ̨�Ƿ�����
	if(!LSI_InitNTDbi()){
		MessageBox("���ݿ�ƽ̨δ����");	
		return -1;
	}
	LSI_CheckUser("sa","");

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect rect;
	this->GetClientRect(rect);

/*	m_capbitmap.LoadBitmap(IDB_BACK_BMP);
	BITMAP bitmap;
	m_capbitmap.GetBitmap(&bitmap);*/

	m_tab.AddView(&m_firsttab, IDD_FIRST_DIALOG, "��ӭ");
//	m_tab.AddView(&m_errortab, IDD_ERRORSHOWDLG_DIALOG, "����״̬��ʾ");
//	m_tab.AddView(&m_moditab, IDD_DIALOG_MODI, "��Ҫ��Ϣ�༭");

//	rect.top = bitmap.bmHeight;
	m_tab.Create(_T("STATIC"), "", WS_CHILD | WS_VISIBLE, CRect(rect.left, rect.top, rect.right, rect.bottom), this, 0x1006);
	m_tab.ShowWindow(SW_SHOW);
	return 0;
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
/*	CRect rect;
	this->GetClientRect(rect);

	//���Ʊ���
	CDC m_memdc;
	m_memdc.CreateCompatibleDC(&dc);
	CBitmap   *pOldBit=m_memdc.SelectObject(&m_capbitmap);   	

	BITMAP bitmap;
	m_capbitmap.GetBitmap(&bitmap);
	if(bitmap.bmWidth<rect.Width())
	{
		int lastx = rect.Width()-bitmap.bmWidth;
		//m_memdc.FillSolidRect(rect.top, lastx, bitmap.bmHeight, rect.right, RGB(1, 101, 51));
		//m_memdc.FillSolidRect(lastx, rect.top, bitmap.bmHeight, rect.right, RGB(1, 101, 51));
	}

	//ճ��˫����
	//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &m_memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_memdc, 0,0,SRCCOPY);
	m_memdc.SelectObject(pOldBit);
	m_memdc.DeleteDC();*/

	// Do not call CWnd::OnPaint() for painting messages
}
