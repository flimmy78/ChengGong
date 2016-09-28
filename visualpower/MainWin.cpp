// MainWin.cpp : implementation of the CMainWin class
//

#include "stdafx.h"
#include "VisualPower.h"
#include "MainWin.h"
#include "comobj.h"
#include "middll.h"
#include "prtmode.h"
#include "cfgshow.h"
#include "layerdlg.h"
#include "logindlg.h"
#include "stflwdlg.h"
#include "sethisdlg.h"
#include "CfgAlmDlg.h"
#include "soeseldlg.h"
#include "ConfigTrans.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;	//��������

//int allupdate;

BOOL GetPw0File(char *filename,char *path,int &pageno,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// CMainWin

CMainWin::CMainWin()
{
	showmnwin=0;
	pagesum=0;
	page=NULL;
	curpage=0;
	fcolor=GetSysColor(COLOR_3DFACE);
	//AvchWnd=NULL;
	hHisWnd=NULL;
	m_bAutoShow=FALSE;
}

CMainWin::~CMainWin()
{
	//if(AvchWnd!=NULL) CloseAVCPQVWnd();
/*	if(hHisWnd!=NULL)
	{
		::SendMessage(hHisWnd,WM_CLOSE,0,0);
		CloseHandle(hHisWnd);
		hHisWnd=NULL;
	}*/
}


BEGIN_MESSAGE_MAP(CMainWin,CWnd )
	//{{AFX_MSG_MAP(CMainWin)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_MOVEPIC, OnMovepic)
	ON_COMMAND(ID_PARTZOOM, OnPartzoom)
	ON_COMMAND(ID_ZOOMIO, OnZoomio)
	ON_COMMAND(ID_ZOOMNML, OnZoomnml)
	ON_COMMAND(IDC_NAVIGATION, OnNavigation)
	ON_COMMAND(IDC_SAVETOBMP, OnSavetobmp)
	ON_COMMAND(IDC_SAVETOJPG, OnSavetojpg)
	ON_COMMAND(ID_ZOOMALL, OnZoomall)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_COMMAND(ID_LASTHMI, OnLasthmi)
	ON_COMMAND(IDC_SHOWDGX, OnShowdgx)
	ON_COMMAND(IDC_SECTFLW, OnSectflw)
	ON_COMMAND(IDC_DMFLOW, OnDmflow)
	ON_COMMAND(IDC_CFGATTR, OnCfgattr)
	ON_COMMAND(IDC_SENOPR, OnSenopr)
	ON_COMMAND(IDC_BUSSEN, OnBussen)
	ON_COMMAND(IDC_LINESEN, OnLinesen)
	ON_COMMAND(IDC_GENREV, OnGenrev)
	ON_COMMAND(IDC_GENREVQ, OnGenrevq)
	ON_COMMAND(IDC_SHOWCRMAP, OnShowcrmap)
	ON_COMMAND(IDC_BASFLOW, OnBasflow)
	ON_COMMAND(IDC_SHOWSYS, OnShowsys)
	ON_COMMAND(IDC_STARTHIS, OnStarthis)
	ON_COMMAND(IDC_ENDHIS, OnEndhis)
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_COMMAND(ID_FASTFW, OnFastfw)
	ON_COMMAND(ID_GOTOTOP, OnGototop)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_COMMAND(IDC_CTLLAYER, OnCtllayer)
	ON_COMMAND(ID_FASTREV, OnFastrev)
	ON_COMMAND(IDC_RELOGIN, OnRelogin)
	ON_COMMAND(IDC_TRANREV, OnTranrev)
	ON_COMMAND(IDC_SECTDF, OnSectdf)
	ON_COMMAND(IDC_MAINPAGE, OnMainpage)
	ON_COMMAND(IDC_SHOWSTF, OnShowstf)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_COMMAND(ID_NORMALNS, OnNormalns)
	ON_COMMAND(IDC_FULLSCR, OnFullscr)
	ON_COMMAND(ID_NOFULLSCR, OnNofullscr)
	ON_COMMAND(IDC_LOWF, OnLowf)
	ON_COMMAND(IDC_BYQWD, OnByqwd)
	ON_COMMAND(IDC_NEXTHMI, OnNexthmi)
	ON_COMMAND(IDC_NBUS, OnNbus)
	ON_COMMAND(IDC_NFLOW, OnNflow)
	ON_COMMAND(IDC_N1ALL, OnN1all)
	ON_COMMAND(IDC_NBUSF, OnNbusf)
	ON_COMMAND(IDC_NFLOWF, OnNflowf)
	ON_COMMAND(IDC_N1ALLF, OnN1allf)
	ON_COMMAND(IDC_SPDOWN, OnSpdown)
	ON_COMMAND(IDC_SPUP, OnSpup)
	ON_COMMAND(IDC_DEFINESECT, OnDefinesect)
	ON_COMMAND(IDC_PREDMJS, OnPredmjs)
	ON_UPDATE_COMMAND_UI(IDC_PREDMJS, OnUpdatePredmjs)
	ON_COMMAND(IDC_SHADOW, OnShadow)
	ON_COMMAND(IDC_CFGALM, OnCfgalm)
	ON_COMMAND(IDC_OPENMENUWIN, OnOpenmenuwin)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_NEWWINDOW, OnNewwindow)
	ON_COMMAND(IDC_OPENSOE, OnOpensoe)
	ON_COMMAND(IDC_CLOSESOE, OnClosesoe)
	ON_COMMAND(IDC_GETNEWSOE, OnGetnewsoe)
	ON_COMMAND(IDC_PLAYSOE, OnPlaysoe)
	ON_COMMAND(IDC_PAUSESOE, OnPausesoe)
	ON_COMMAND(ID_SOEGOTOTOP, OnSoegototop)
	ON_COMMAND(IDC_DLDLJS, OnDldljs)
	ON_COMMAND(IDC_MANUALDL, OnManualdl)
	ON_COMMAND(IDC_MSELLINE, OnMselline)
	ON_COMMAND(IDC_DLWF, OnDlwf)
	ON_COMMAND(ID_BTNRETURN, OnBtnreturn)
	ON_COMMAND(IDC_N1LIST, OnN1list)
	ON_COMMAND(IDC_CFGTRANS, OnCfgtrans)
	ON_COMMAND(IDC_ZONEBAR, OnZonebar)
	ON_COMMAND(IDC_SYSPIEBAR, OnSyspiebar)
	ON_COMMAND(IDC_SV_AUTO, OnSvAuto)
	ON_UPDATE_COMMAND_UI(IDC_SV_AUTO, OnUpdateSvAuto)
	ON_COMMAND(IDC_SVWIN, OnSvwin)
	ON_UPDATE_COMMAND_UI(IDC_SVWIN, OnUpdateSvwin)
	ON_COMMAND(ID_TOOL_HISTORY, OnToolHistory)
	ON_UPDATE_COMMAND_UI(ID_TOOL_HISTORY, OnUpdateToolHistory)
	ON_COMMAND(ID_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainWin message handlers

BOOL CMainWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void CMainWin::OnPaint() 
{
	CPaintDC dc(this); 
	dc.Draw3dRect(CRect(0,0,wx,wy),0,0xffffff);
	Draw(dc);
}


void CMainWin::Draw(CDC&dc)
{
	CRect rt,rt1;
	//��ʾ������
	if(showmnwin==1)
	{
		rt=CRect(lw-5,0,lw,wy);
		dc.FillSolidRect(rt,fcolor);
		GLLine(dc.m_hDC,rt.left,rt.top,rt.left,rt.bottom,0xffffff);
		GLLine(dc.m_hDC,rt.right-1,rt.top+24,rt.right-1,rt.bottom,0);
	}

}

//��ʾͷ
void CMainWin::ShowPageHead(CDC&dc)
{
	int i;
	DWORD color;
	CRect rt;
	color=GetSysColor(COLOR_3DFACE);
	for(i=0;i<pagesum;i++)
	{
		rt=page[i].rt;
		rt.right-=5;
		dc.Draw3dRect(rt,0xffffff,0);
		dc.FillSolidRect(rt,color);
		dc.Draw3dRect(rt,0xffffff,0);
	}
}

int CMainWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CChildFrm *win;
	int w,h;
	if (CWnd ::OnCreate(lpCreateStruct) == -1)		return -1;
	win=new CChildFrm;
	
	win->type=0; //����Ϊ���ǻ�����
	win->Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this);
	cobj.swin=(ScadaWin*)win->rc;
	cobj.dbm=&cobj.swin->dbm;
	cwin.scf=&cobj.dbm->scf;
	
	AddAWindow(win->m_hWnd,win,0);
	cobj.dbm->LoadShowSet();
	cobj.ReadDefColor();
	tmphwnd=m_hWnd;
	cobj.swin->rrd.RegistFileOK(tmphwnd);
	cobj.Mainpage();  //����ҳ,��һ�δ�
	//�����˵�������
	mnwin.Create("","",WS_VISIBLE|WS_CHILD|WS_VSCROLL,CRect(0,0,1,1),this,102);
	//�����澯����
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	//�澯����
	alwin.Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,100,400),this);
	alwin.ShowWindow(SW_HIDE);
	alwin.MoveWindow(w-280,25,280,42);
	cobj.vbar=&alwin;
	//����ҳ����ƴ���
	ptl.Create("","",WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this,107);
	//������������
	nwin.Createtun(WS_VISIBLE|WS_CLIPCHILDREN|WS_SYSMENU,CRect(0,0,100,401),this);
	nwin.ShowWindow(SW_HIDE);
	nwin.MoveWindow(10,100,320,240);
	cobj.nwin=&nwin;
	nwin.SetWindowText("������");
	
	//����ɫ�״���
	cwin.Createtun(WS_VISIBLE|WS_CLIPCHILDREN|WS_SYSMENU,CRect(0,0,100,402),this);
	cwin.ShowWindow(SW_HIDE);
	cwin.MoveWindow(5,100,130,190);
	cwin.SetWindowText("ɫ��");
	cobj.cwin=&cwin;
	//����AVC����
	//AvchWnd=CreateAVCPQVWnd(this); //ZQ 2009.12.20 delete temp
	hHisWnd=CreateDemoWnd(this,FALSE);
	::ShowWindow(hHisWnd,SW_HIDE);
	return 0;
}

void CMainWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	wx=cx;wy=cy;
	MoveChildWin();
}

//�ƶ��Ӵ���
void CMainWin::MoveChildWin()
{
	int i;
	CRect rt;
	//���˵����ڣ��������λ��
	if(showmnwin==1)
	{
		lw=mnwin.pw+5;
		mnwin.MoveWindow(CRect(1,1,lw-5,wy-1));
		mnwin.ShowWindow(SW_SHOW);
	}else{
		mnwin.ShowWindow(SW_HIDE);
		lw=1;
	}
	/*//��ָ�괰�ڣ������ұ�λ��
	if(showzbwin==1)
	{
		rw=ybwin.dbm.page.head.width-4;
		ybwin.MoveWindow(CRect(wx-rw+5,1,wx-1,wy-1));
		ybwin.ShowWindow(SW_SHOW);		
	}else{
		ybwin.ShowWindow(SW_HIDE);
		
	}*/
	rw=1;
	//�ƶ�ҳ�����
	rt=CRect(lw,0,wx-rw,25);
	ptl.MoveWindow(rt);
	ptl.ShowWindow(SW_SHOW);
	if(curpage<0||curpage>=pagesum) return;
	
	//�ƶ����洰��
	rt=CRect(lw,25,wx-rw,wy-1);
	ClientToScreen(&rt);
	//::MoveWindow(page[curpage].hwnd,rt.left,rt.top,rt.Width(),rt.Height(),TRUE);

	//�����Ƿ���google����
	for(i=0;i<pagesum;i++)
	{
		switch(page[i].type)
		{
		case 0: case 1:
			::MoveWindow(page[i].hwnd,rt.left,rt.top,rt.Width(),rt.Height(),TRUE);
			break;
		case 2:
			MoveEarthWnd(&rt,i==curpage ? TRUE:FALSE);
			break;
		}
	}
}


void CMainWin::OnFileOpen()
{
	int pageno;
	HISHMI newhmi;
	char fnm[512],path[256];
	cobj.swin->GetCurHmi(newhmi);
	strcpy(path,cobj.runpath);
	if(!GetPw0File(fnm,path,pageno,m_hWnd)) return;
	if(!cobj.swin->FileOpen(fnm,pageno)) return;
	cobj.dbm->AddOpenHmi(newhmi);
	ptl.DrawShow();
}

void CMainWin::OnFilePrint()	{	cobj.PrintPage();						}
void CMainWin::OnMovepic()		{	cobj.swin->CursorChange(1);				}
void CMainWin::OnPartzoom()		{	cobj.swin->CursorChange(2);				}
void CMainWin::OnZoomio()		{	cobj.swin->CursorChange(3);				}
void CMainWin::OnZoomnml()		{	cobj.Zoomnml();							}
void CMainWin::OnNavigation()	{	cobj.nwin->ShowWindow(SW_SHOW);			}
void CMainWin::OnSavetobmp()	{	cobj.Savetobmp();						}
void CMainWin::OnSavetojpg()	{	cobj.Savetojpg();						}
void CMainWin::OnZoomall()		{	cobj.Zoomall();							}
void CMainWin::OnNormal()		{	cobj.SetNewCursor(0);					}
void CMainWin::OnLasthmi()		{	cobj.Lasthmi();							}
void CMainWin::OnShowdgx()		{	cobj.OnShowdgx();						}
void CMainWin::OnSectflw()		{	cobj.swin->CursorChange(6);				}
void CMainWin::OnSectdf()		{	cobj.swin->CursorChange(9);				}
void CMainWin::OnDmflow()		{	cobj.Dmflow();							}
void CMainWin::OnCfgattr()		{	cobj.Cfgattr();							}
void CMainWin::OnSenopr()		{	cobj.Senopr();							}
void CMainWin::OnBussen()		{	cobj.Bussen();							}
void CMainWin::OnLinesen()		{	cobj.Linesen();							}
void CMainWin::OnGenrev()		{	cobj.Genrev();							}
void CMainWin::OnGenrevq()		{	cobj.Genrevq();							}
void CMainWin::OnTranrev()		{	cobj.Tranrev();							}
void CMainWin::OnByqwd()		{	cobj.Byqwd();							}
void CMainWin::OnNbus()			{	cobj.N_1Operator(5,0);					}
void CMainWin::OnNflow()		{	cobj.N_1Operator(6,1);					}
void CMainWin::OnN1all()		{	cobj.N_1Operator(7,2);					}
void CMainWin::OnBasflow()		{	cobj.ResetFunct(1,1);					}
void CMainWin::OnLowf()			{	cobj.ToLowf();							}
void CMainWin::OnNexthmi()		{	cobj.Nexthmi();							}
void CMainWin::OnNbusf()		{	cobj.N_1Operator(5,3);					}
void CMainWin::OnNflowf()		{	cobj.N_1Operator(6,4);					}
void CMainWin::OnN1allf()		{	cobj.N_1Operator(7,5);					}
void CMainWin::OnSpdown()		{	cobj.HisSpdown();						}
void CMainWin::OnSpup()			{	cobj.HisSpup();							}
void CMainWin::OnStarthis()		{	cobj.Starthis();						}
void CMainWin::OnEndhis()		{	cobj.CloseHisPrc();						}
void CMainWin::OnOpensoe()		{	cobj.StartSoe();						}
void CMainWin::OnClosesoe()		{	cobj.ResetFunct(0,1);						}
void CMainWin::OnDldljs()		{	cobj.DlDlperator();						}//��·��������
void CMainWin::OnManualdl()		{	cobj.ManuDlperator();					}//�ֶ���·��������
void CMainWin::OnMselline()		{	cobj.MdlSelLine();						}	


void CMainWin::OnShowcrmap() 
{
	if(cwin.IsWindowVisible())	cwin.ShowWindow(SW_HIDE);
	else  cwin.ShowWindow(SW_SHOW);
}



void CMainWin::OnShowsys() 
{
	if(alwin.IsWindowVisible()) alwin.ShowWindow(SW_HIDE);
	else alwin.ShowWindow(SW_SHOW);
}


void CMainWin::OnPlay() 
{
	cobj.swin->dbm.hisjs=0;
	cobj.swin->dbm.hisplay=1;
}


void CMainWin::OnFastrev() 
{
	cobj.swin->dbm.curtm=cobj.swin->dbm.curtm>5 ? cobj.swin->dbm.curtm-5:cobj.swin->dbm.curtm;
	cobj.swin->SetCurHisDTime();
}

void CMainWin::OnFastfw() 
{
	cobj.swin->dbm.curtm=cobj.swin->dbm.curtm<cobj.swin->dbm.hsum-5 ? cobj.swin->dbm.curtm+5:cobj.swin->dbm.curtm;
	cobj.swin->SetCurHisDTime();
}

void CMainWin::OnGototop() 
{
	cobj.swin->dbm.curtm=0;					//�ѵ���β
	cobj.swin->SetCurHisDTime();
}

void CMainWin::OnPause() 
{
	cobj.swin->dbm.hisplay=cobj.swin->dbm.hisplay==0 ? 1:0;	
}


BOOL CMainWin::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (ptl.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	if (cobj.swin->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)) return TRUE;
	return CWnd ::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainWin::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nFlags>=59&&nFlags<=67) //��F1-F9��
	{ 
		cobj.PutHotKeyPic(1,(BYTE)nChar);
	}
	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMainWin::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	cobj.PutHotKeyPic(0,(BYTE)nChar);
	CWnd ::OnChar(nChar, nRepCnt, nFlags);
}

void CMainWin::OnTimer(UINT nIDEvent) 
{
	
	CWnd ::OnTimer(nIDEvent);
}


LRESULT CMainWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char fnm[256];
	if(message==1310&&wParam==5)//�ļ����º��Ƿ���Ҫ���µ���
	{ 
		cobj.swin->rrd.GetLastRecFile(fnm);
		cobj.ReOpenFile(fnm);
	}
	return CWnd ::WindowProc(message, wParam, lParam);
}

void CMainWin::OnCtllayer() 
{
	CLayerDlg dlg;
	dlg.dbm=cobj.dbm;
	if(dlg.DoModal()==IDOK)
	{
		cobj.swin->ShowA(cobj.swin->mbg);
		cobj.swin->DrawShow();
	}
}

void CMainWin::ToolBarDgxSel() 
{
	cobj.swin->SetFirstPosition();
	cobj.dbm->SaveShowSet();
	cobj.swin->SetDgxParam();
	cobj.swin->ChangeDgxcfg();
	if(cobj.dbm->scf.showdgx==0) cwin.ShowWindow(SW_HIDE);
	else cwin.ReDraw();
}

void CMainWin::OnRelogin() 
{
	LoginDlg log;
	if(log.DoModal()==IDOK)
	{
		cobj.swin->SetStatusBarMsg();
	}
}


//ֱ�ӵ���ҳ
void CMainWin::OnMainpage() 
{
	cobj.Mainpage(false);
}

void CMainWin::OnShowstf() 
{
	cobj.SetNewCursor(0);
	cobj.swin->segsum=0;
	cobj.swin->LoadPreDefineSfw();
}


//������ת
void CMainWin::OnRotate() 
{
	cobj.swin->CursorChange(10);
}

//�ָ���������
void CMainWin::OnNormalns() 
{
	cobj.dbm->curang=0;
	cobj.swin->Set3DEnv();//����3D����
	if(cobj.dbm->scf.showdgx==1&&cobj.dbm->page.head.type>0) cobj.swin->sct.DrawDgxinMem(cobj.swin->msr,cobj.dbm->curzoom,cobj.swin->dx,cobj.swin->dy);
	cobj.swin->CreateAllrgn();
	cobj.swin->Order3dPos();
	cobj.swin->EndShow();
	cobj.SetNewCursor(0);
}


void CMainWin::OnFullscr() 
{
	CRect rt;
	int w,h;
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	cobj.swin->winmode=1;
	rt=CRect(0,0,w,h);
	page[curpage].cwin->MoveWindow(rt);
}

void CMainWin::OnNofullscr() 
{
	cobj.swin->winmode=0;
	MoveChildWin();
}



//����Ԥ������
void CMainWin::OnDefinesect() 
{
	char fnm[256];
	cobj.SetToLocalFile("seldev.dll",fnm);
	void (WINAPI*mfunct)();						//ģ�麯��
	HINSTANCE hinst=LoadLibrary(fnm);
	if(hinst==NULL)
	{
		MessageBox("ָ����ģ��seldev.dll�����ڣ�","����",MB_ICONERROR|MB_OK);
		return;
	}
	(FARPROC&)mfunct=GetProcAddress(hinst,"CfgSect");
	if(mfunct==NULL) 
	{
	   MessageBox("seldev.dll�в����ں���CfgSect��","����",MB_ICONERROR|MB_OK);
	   return;
	}
	mfunct();
	FreeLibrary(hinst);
}

void CMainWin::OnPredmjs() 
{
	BOOL a=::IsWindowVisible(cobj.swin->dmwin.m_hWnd);
	if(a) cobj.swin->dmwin.ShowWindow(SW_HIDE);
	else cobj.swin->dmwin.ShowWindow(SW_SHOW);
}

void CMainWin::OnUpdatePredmjs(CCmdUI* pCmdUI) 
{
	BOOL a=::IsWindowVisible(cobj.swin->dmwin.m_hWnd);
	pCmdUI->SetCheck(a==TRUE ? 1:0);
}

void CMainWin::OnShadow() 
{
	cobj.swin->CloseLowfWin();
	cobj.dbm->curopzt=0;
	cobj.dbm->scf.showrev=0; //N-1BUS
	cobj.dbm->n1bz=-1;
	cobj.dbm->scf.lmd=0;
	cobj.dbm->lookdown=1;
	cobj.dbm->GetDevObjToTy();
	//��ȡn-1���
	cobj.swin->CreateAllrgn();
	cwin.ShowWindow(SW_HIDE);
	cobj.FunctChange();
}
//����Ԥ������
void CMainWin::OnCfgalm() 
{
	CCfgAlmDlg dlg;
	dlg.tmp=alwin.alsv;
	if(dlg.DoModal()!=IDOK) return;
	alwin.alsv=dlg.tmp;	
}

void CMainWin::OnOpenmenuwin() 
{
	showmnwin=showmnwin==0 ? 1:0;
	MoveChildWin();
	Invalidate();
}

void CMainWin::OnDestroy() 
{
	int i;
	CWnd ::OnDestroy();
	//�ͷ���Դ
	for(i=0;i<pagesum;i++)
	{
		page[i].cwin->DelResource();
		delete page[i].cwin;
	}
	if(page!=NULL) free(page);
	page=NULL;
	pagesum=0;
}

//���һ������
void CMainWin::AddAWindow(HWND hwnd,CChildFrm *cw,int type)
{
	int n;
	n=pagesum;
	if(n==0)
	{
		page=new PAGEWIN;
	};
	if(n>0)
	{
		page=(PAGEWIN*)realloc(page,sizeof(PAGEWIN)*(n+1));
	};
	page[n].hwnd=hwnd;
	page[n].type=type;
	page[n].cwin=cw;
	pagesum++;
}

//����ҳ�������
void CMainWin::GetPageName(int j,char *txt)
{
	ScadaWin *win;
	CString str;
	if(j<0||j>=pagesum)
	{
		txt[0]=0;
		return;
	}
	switch(page[j].type)
	{
	case 0:
		win=(ScadaWin *)page[j].cwin->rc;
		strcpy(txt,win->dbm.page.head.Name);
		break;
	case 1:
		strcpy(txt,page[j].cwin->pagename);//"WEB���");
		break;
	case 2:
		strcpy(txt,page[j].cwin->pagename);
		break;
	default:
		strcpy(txt,"");
	}
}

void CMainWin::OnNewwindow() 
{
	CChildFrm *win;
	HideChildWin();
	win=new CChildFrm;
	win->type=0;
	win->Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this);
	cobj.swin=(ScadaWin*)win->rc;
	cobj.dbm=&cobj.swin->dbm;
	cwin.scf=&cobj.dbm->scf;
	HideChildWin();
	AddAWindow(win->m_hWnd,win,0);
	curpage=pagesum-1;
	cobj.dbm->LoadShowSet();
	cobj.Newpage();
	MoveChildWin();
	win->ShowWindow(SW_SHOW);
	ptl.DrawShow();
}

void CMainWin::NewEmptywindow() 
{
	CChildFrm *win;
	HideChildWin();
	win=new CChildFrm;
	win->type=0;
	win->Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this);
	cobj.swin=(ScadaWin*)win->rc;
	cobj.dbm=&cobj.swin->dbm;
	cwin.scf=&cobj.dbm->scf;
	HideChildWin();
	AddAWindow(win->m_hWnd,win,0);
	curpage=pagesum-1;
	cobj.dbm->LoadShowSet();
	ptl.DrawShow();
	MoveChildWin();
}

//�����Ӵ���
void CMainWin::HideChildWin()
{
	int i;
	for(i=0;i<pagesum;i++)
	{
		page[i].cwin->ShowWindow(SW_HIDE);
	}
}

//ֱ�ӵ�ĳһҳ��
void CMainWin::GoToPage(int j)
{
	ScadaWin *win;
	if(j<0||j>=pagesum) return;
	curpage=j;
	HideChildWin();
	switch(page[j].type)
	{
	case 0:
		win=(ScadaWin *)page[j].cwin->rc;
		cobj.dbm=&win->dbm;
		cobj.swin=win;
		cwin.scf=&cobj.dbm->scf;
		break;
	}
	page[j].cwin->ShowWindow(SW_SHOW);
	MoveChildWin();
	cobj.ReShowToolBar();
	ptl.Invalidate();
}

//��WEBҳ��
void CMainWin::OPenWeb(char *wwwstr,char *name)
{
	int i,j;
	CWebBrowser2 *web;
	char ul[512];
	HideChildWin();
	j=-1;
	//����WEBҳ��
	for(i=0;i<pagesum;i++)
	{
		if(page[i].type==1)
		{
			j=i;
			break;
		}
	}
	//����ҵ�
	if(j>=0)
	{
		curpage=j;
		web=(CWebBrowser2 *)page[i].cwin->rc;
		strcpy(page[i].cwin->pagename,name);
		page[i].cwin->ShowWindow(SW_SHOW);
		web->Navigate(wwwstr,0,NULL,NULL,NULL);
		MoveChildWin();
		ptl.DrawShow();
		return;
	}
	//δ�ҵ�
	HideChildWin();
	CChildFrm *win;
	win=new CChildFrm;
	win->type=1;
	win->Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this);
	strcpy(win->pagename,name);
	AddAWindow(win->m_hWnd,win,1);
	curpage=pagesum-1;
	web=(CWebBrowser2 *)win->rc;
	strcpy(ul,wwwstr);
	cobj.SetToLocalFile(wwwstr,ul);
	web->Navigate(ul,0,NULL,NULL,NULL);
	MoveChildWin();
	ptl.DrawShow();
}

//��Google earthҳ��
void CMainWin::OPenGoogleEarth(char *wwwstr,char *name)
{
	int i,j;
	HideChildWin();
	j=-1;
	//����googleҳ��
	for(i=0;i<pagesum;i++)
	{
		if(page[i].type==2)
		{
			j=i;
			break;
		}
	}
	//����ҵ�
	if(j>=0)
	{
		curpage=j;
		page[i].cwin->ShowWindow(SW_SHOW);
		MoveChildWin();
		ptl.DrawShow();
		return;
	}
	//δ�ҵ�
	HideChildWin();
	CChildFrm *win;
	win=new CChildFrm;
	win->type=2;
	win->Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this);
	strcpy(win->pagename,name);
	AddAWindow(win->m_hWnd,win,2);
	curpage=pagesum-1;
	MoveChildWin();
	ptl.DrawShow();
}

//����һ�����͵Ĵ��ڸ���
int CMainWin::GetTypeSum(int type)
{
	int i,n=0;
	for(i=0;i<pagesum;i++)
	{
		if(page[i].type==type) n++;
	}
	return n;
}


//ɾ����ǰ�Ӵ���
void CMainWin::DelCurChild()
{
	int i,j,k,n;
	PAGEWIN  tmp;
	ScadaWin *win;
	if(curpage<0||curpage>=pagesum) return;
	j=curpage;
	if(page[curpage].type==0)
	{
		n=GetTypeSum(0);
		if(n<=1) return;  //���һ�����ӻ����ڲ�����ɾ��
	}
	//���ɾ�����ǿ��ӻ�����,��Ҫ���⴦��
	k=-1;
	if(page[j].type==0)
	{
		for(i=0;i<pagesum;i++)
		{
			if(i==curpage) continue;
			if(page[i].type==0)
			{
				k=i;
				break;
			}
		}
		if(k==-1) return;
		win=(ScadaWin *)page[k].cwin->rc;
		cobj.swin=win;
		cobj.dbm=&win->dbm;
		cwin.scf=&cobj.dbm->scf;
	}
	tmp=page[curpage];
	for(i=curpage;i<pagesum-1;i++) 
	{
		page[i]=page[i+1];
	}
	pagesum--;
	//�쿴�Ƿ�curpage����
	if(curpage>=pagesum) curpage--;
	if(curpage<0||curpage>=pagesum) return;
	GoToPage(curpage);
	ptl.DrawShow();

	//���ɾ����Դ
	tmp.cwin->DelResource();
	delete tmp.cwin;
}

//��ǰ���ӻ����
int CMainWin::PCursor()
{
	return page[curpage].cwin->PCursor();
}
//��ǰͼ������
int CMainWin::PType()
{
	return page[curpage].cwin->PType();
}
//��ǰ���ӻ���Ƶ��״̬
int CMainWin::PLowf()
{
	return page[curpage].cwin->Lowf();
}
//��ǰ���ӻ���ʷ״̬
int CMainWin::PCurhmi()
{
	return page[curpage].cwin->PCurhmi();
}

//��ǰ�ȸ���״̬
int CMainWin::PDgx()
{
	return page[curpage].cwin->PDgx();
}
//��ǰ���泱��״̬
int CMainWin::PDmflow()
{
	return page[curpage].cwin->PDmflow();
}
//��ǰ������״̬
int CMainWin::PSen()
{
	return page[curpage].cwin->PSen();
}
//��ǰ�����ȱ�־״̬
int CMainWin::PSenflag()
{
	return page[curpage].cwin->PSenflag();
}
//��ǰ�ؼ��豸����
int CMainWin::PDevn(int sel)
{
	return page[curpage].cwin->PDevn(sel);
}
int CMainWin::PRev()
{
	return page[curpage].cwin->PRev();
}
BOOL CMainWin::PHdbok()
{
	return page[curpage].cwin->PHdbok();
}

int CMainWin::PDbzt()
{
	return page[curpage].cwin->PDbzt();
}

int CMainWin::PSoeSum()
{
	return page[curpage].cwin->PSoeSum();
}

int CMainWin::PHisplay()
{
	return page[curpage].cwin->PHisplay();
}
int CMainWin::PCtrtype()
{
	return page[curpage].cwin->PCtrtype();
}
int CMainWin::PCurrtn()
{
	return page[curpage].cwin->PCurrtn();
}
int CMainWin::PFtype()
{
	return page[curpage].cwin->PFtype();
}
int CMainWin::PN1bz()
{
	return page[curpage].cwin->PN1bz();
}
int CMainWin::PCurang()
{
	return page[curpage].cwin->PAngle();
}

int CMainWin::PSoebz()
{
	return page[curpage].cwin->Soebz();
}

//����SOEѡ��
void CMainWin::OnGetnewsoe() 
{
	NSOES  *sbuf;
	int     soen;
	soen=0;
	if(cobj.dbm->soe!=NULL) delete cobj.dbm->soe;
	cobj.dbm->soe=NULL;
	cobj.dbm->soesum=0;
	GetHisSoe((char**)&sbuf,&soen);
	if(soen<=0) return;
	cobj.dbm->soe=new NSOES[soen];
	cobj.dbm->soesum=soen;
	memcpy(cobj.dbm->soe,sbuf,sizeof(NSOES)*soen);
	cobj.swin->CleaseSwtSoe();
	cobj.dbm->curtm=-1;
	cobj.dbm->lookdown=1;
	cobj.swin->Set3DEnv();
	cobj.swin->EndShow();
	ReleaseHisSoe();//�ͷ��ڴ�
}

void CMainWin::OnPlaysoe() 
{
	cobj.swin->dbm.hisplay=2;
}

void CMainWin::OnPausesoe() 
{
	cobj.swin->dbm.hisplay=cobj.swin->dbm.hisplay==0 ? 2:0;	
}

//�ص���ʼ
void CMainWin::OnSoegototop() 
{
	cobj.swin->dbm.curtm=0;
	cobj.swin->CleaseSwtSoe();
}


//���ص�ǰcobj.swin��ʵ��λ��
int CMainWin::GetVWIndex(void *pswin)
{
	int i;
	for(i=0;i<pagesum;i++)
	{
		if(page[i].type!=0) continue;
		if(pswin==page[i].cwin->rc) return i;
	}
	return 0;
}


//������Ϣά��

void CMainWin::OnDlwf() 
{
	//ShowDlg_GZXXWH(true);
}

//����ͼ�����ͣ���SCADAWIN, WEB, GOOGLE=0,1,2
int CMainWin::GetCurpageType()
{
	return page[curpage].type;
}


void CMainWin::OnBtnreturn() 
{
	cobj.Btnreturn();
}


//��ʾ�����豸���Ϻ����ء������豸3D��ʾ

void CMainWin::OnN1list() 
{
	NT_ShowAllCtg();	
}

void CMainWin::OnCfgtrans() 
{
	CConfigTrans cfg;
	cfg.rrd=&cobj.swin->rrd;
	cfg.DoModal();	
}

void CMainWin::OnZonebar() 
{
	if(cobj.dbm->scf.showrev!=10)
		cobj.Zonebar();
	else
		cobj.ResetFunct(1,1);
}

void CMainWin::OnSyspiebar() 
{
	cobj.Syspiebar();
	
}

void CMainWin::OnSvAuto() 
{
	if(m_bAutoShow)
		m_bAutoShow=FALSE;
	else
		m_bAutoShow=TRUE;
	SetAutoShow(m_bAutoShow);
}

void CMainWin::OnUpdateSvAuto(CCmdUI* pCmdUI) 
{
	if(m_bAutoShow)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainWin::OnSvwin() 
{
	BOOL bShow=::IsWindowVisible(cobj.swin->SvWnd);
	ShowDynTrans(0,0,!bShow);
}

void CMainWin::OnUpdateSvwin(CCmdUI* pCmdUI) 
{
	BOOL bShow=::IsWindowVisible(cobj.swin->SvWnd);
	pCmdUI->SetCheck(bShow==TRUE ? 1:0);
}

void CMainWin::OnToolHistory() 
{
	if(hHisWnd!=NULL)
	{
		if(!::IsWindowVisible(hHisWnd))
		{
			::ShowWindow(hHisWnd,SW_SHOW);
		}
	}	
}

void CMainWin::OnUpdateToolHistory(CCmdUI* pCmdUI) 
{
	BOOL bShow=::IsWindowVisible(hHisWnd);
	pCmdUI->SetCheck(bShow==TRUE ? 1:0);
}

void CMainWin::OnChange() 
{
	// TODO: Add your command handler code here
	if(bShowProcessData == false)
		bShowProcessData = true;
	else
		bShowProcessData = false;
	
}
