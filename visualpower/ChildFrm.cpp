// ChildFrm.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ChildFrm.h"
#include "scadawin.h"
#include "webbrowser2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrm

CChildFrm::CChildFrm()
{
	hwnd=NULL;		//�Ӵ��ھ��
	type=0 ;		//��������  0=swin 1=webҳ�� 2=googleҳ��
	rc=NULL;		//��Դ��ַ
	pagename[0]=0;
}

CChildFrm::~CChildFrm()
{
}


BEGIN_MESSAGE_MAP(CChildFrm, CWnd)
	//{{AFX_MSG_MAP(CChildFrm)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildFrm message handlers

BOOL CChildFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

int CChildFrm::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//�������ʹ����Ӵ���
	switch(type)
	{
	case 0: //���ӻ�
		ScadaWin *win;
		win=new ScadaWin;
		win->Create("","",WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this,100);
		rc=win;
		hwnd=win->m_hWnd;
		break;
	case 1: //web���
		CWebBrowser2 *web;
		web=new CWebBrowser2;
		web->Create("",WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this,120);
		rc=web;
		hwnd=web->m_hWnd;
		break;
	case 2: //google earth
		AttachEarthClient(GetParent());
		rc=NULL;
		hwnd=0;
		break;
	}
	return 0;
}


void CChildFrm::OnSize(UINT nType, int cx, int cy) 
{
	CRect rt;
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;

	if(type==2)
	{
		rt=CRect(0,0,wx,wy);
		ClientToScreen(&rt);
		MoveEarthWnd(&rt);
	}else ::MoveWindow(hwnd,0,0,wx,wy,true);
	
}

BOOL CChildFrm::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (0, "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

//ɾ���������Ӵ���
void CChildFrm::DelResource()
{
	ScadaWin *win;
	CWebBrowser2  *web;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		win->DestroyWindow();
		delete  win;
		break;
	case 1:
		web=(CWebBrowser2 *)rc;
		delete web;
		break;
	case 2:
		DetachEarthClient();
		break;
	}
}

//�Ƿ��Ƶ��
int CChildFrm::Lowf()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curopzt==3 ? 1:0;;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//�򿪵�ͼ������
int CChildFrm::PType()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.page.head.type;
		break;
	default:
		rtn=0;
	}
	return rtn;
}



//�򿪵�ͼ������
int CChildFrm::PCursor()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->cursor;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//��ǰ��ʷ
int CChildFrm::PCurhmi()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curhmi;
		break;
	default:
		rtn=0;
	}
	return rtn;
}
//��ǰ��ʷ
int CChildFrm::PCurrtn()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.currtn;
		break;
	default:
		rtn=0;
	}
	return rtn;
}
//�ȸ���״̬
int CChildFrm::PDgx()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.scf.showdgx;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//���泱��״̬
int CChildFrm::PDmflow()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curopzt==1 ? 1:0;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//������״̬
int CChildFrm::PSen()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curopzt==2 ? 1:0;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//�����ȱ�־
int CChildFrm::PSenflag()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.page.head.senflag;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//�ؼ��豸����
int CChildFrm::PDevn(int sel)
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		switch(sel)
		{
		case 0:
			rtn=win->n_se;
			break;
		case 1:
			rtn=win->n_ge;
			break;
		case 2:
			rtn=win->n_sh;
			break;
		case 3:
			rtn=win->n_tr;
			break;
		case 4: //�����ͼ��
			rtn=win->n_pie;
			break;
		case 5: //ϵͳ��ͼ
			rtn=win->n_spe;
			break;
		default:
			rtn=0;
		}
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//����״̬
int CChildFrm::PRev()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.scf.showrev;
		break;
	default:
		rtn=0;
	}
	return rtn;
}
//��ʷ����OK
BOOL CChildFrm::PHdbok()
{
	BOOL rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.hdbok;
		break;
	default:
		rtn=FALSE;
	}
	return rtn;
}

//���ݿ�״̬״̬
int CChildFrm::PDbzt()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.dbzt;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//���ݿ�״̬״̬
int CChildFrm::PSoeSum()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.soesum;
		break;
	default:
		rtn=0;
	}
	return rtn;
}
//��ʷ����״̬
int CChildFrm::PHisplay()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.hisplay;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

//��ʷ����״̬
int CChildFrm::PCtrtype()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.scf.ctrtype;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

int CChildFrm::PFtype()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.scf.ftype;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

int CChildFrm::PN1bz()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.n1bz;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

int CChildFrm::Soebz()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curopzt==5 ? 1:0;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

int CChildFrm::PAngle()
{
	int rtn;
	ScadaWin *win;
	switch(type)
	{
	case 0:
		win=(ScadaWin*)rc;
		rtn=win->dbm.curang;
		break;
	default:
		rtn=0;
	}
	return rtn;
}

