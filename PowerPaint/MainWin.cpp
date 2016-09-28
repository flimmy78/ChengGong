// MainWin.cpp : implementation of the CMainWin class
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "MainWin.h"
#include "gdata.h"
#include "comobj.h"
#include "prtmode.h"
#include "middll.h"
#include "bfcfgdlg.h"
#include "cfgzmdlg.h"
#include "GetNMDlg.h"
#include "GetIDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CImageList  othimg;
gdata	dbm;
comobj  cobj;

extern int testflag;
/////////////////////////////////////////////////////////////////////////////
// CMainWin

CMainWin::CMainWin()
{
	
}

CMainWin::~CMainWin()
{
	UnRegistFileOK(tmphwnd);
}


BEGIN_MESSAGE_MAP(CMainWin,CWnd )
	//{{AFX_MSG_MAP(CMainWin)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_PRINT, OnPrint)
	ON_COMMAND(IDC_TEST,  OnTest)
	ON_COMMAND(IDC_PUTOUT, OnPutout)
	ON_UPDATE_COMMAND_UI(IDC_PUTOUT, OnUpdatePutout)
	ON_COMMAND(IDC_TOHMIDIR, OnTohmidir)
	ON_COMMAND(IDC_BUSRALATE, OnBusralate)
	ON_COMMAND(IDC_ZMCTL, OnZmctl)
	ON_UPDATE_COMMAND_UI(IDC_TOSQRT, OnUpdateTosqrt)
	ON_COMMAND(IDC_GETNM, OnGetnm)
	ON_COMMAND(IDC_GETID, OnGetid)
	ON_COMMAND(IDC_OUTSVG, OnOutsvg)
	ON_COMMAND(IDC_LOADCIM, OnLoadcim)
	ON_COMMAND(IDC_SVGNAME, OnSvgname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainWin message handlers

BOOL CMainWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);

	return TRUE;
}

void CMainWin::OnPaint() 
{
	CPaintDC dc(this); 
	spl.OnPaint(dc);
}


int CMainWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	//����3d����Ϊƽ��//////////////////////////////////////////////////
	//Set3DEnv(0,1024,768,0);
	////////////////////////////////////////////////////////////////////

	othimg.Create(IDB_BITMAP4,32,0,RGB(255,0,255));
	
	tlw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,101);
	wkw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	

	spl.Create(this,&tlw,&wkw,NULL,0);
	spl.SetInitPosition(240);
	cobj.wwin=&wkw;
	cobj.tlsw=&tlw;
	//���ݿ����
	dbm.dbfok=InitMemDbf();
	if(!dbm.dbfok){
		MessageBox("�ڴ��ƽ̨δ��������Щǣ�浽���ݿ�Ĳ���������ֹ��","����",MB_ICONSTOP);
		return 0;
	}
	//��ȡ���ݿ���ɫ
	cobj.ReadDefColor();
	//ȡ�������ݿ���صĽ����ļ�Ŀ¼
	GetHmiPath(cobj.path[1].path);
	//ע���ļ�����֪ͨ
	RegistFileOK(m_hWnd);
	tmphwnd=m_hWnd;
	return 0;
}

void CMainWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	if(cx>10&&cy>10) spl.OnSize(cx,cy);
}

void CMainWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	spl.OnLButtonDown(point);
	
	CWnd ::OnLButtonDown(nFlags, point);
}

void CMainWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	spl.OnLButtonUp(point);
	CWnd ::OnLButtonUp(nFlags, point);
}

void CMainWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	spl.OnMouseMove(point);
		
	CWnd ::OnMouseMove(nFlags, point);
}

BOOL CMainWin::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (wkw.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	if (tlw.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CWnd ::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//ҳ��ı�
void CMainWin::PageChange(int page)
{
	dbm.GoToPage(page);
	cobj.cvs->PageChange();
	wkw.SetTitlename();
}

void CMainWin::OnPrint() 
{
	BYTE pm;
	char p[100];
	double zm,pdx,pdy;
	int i,j,mok,mx,my;
	int yl,w,h,kw,kh,dx,dy,ht,mh;
	DEVMODE *dev,devmode;
	double bl;
	CPrintDialog pdlg(true);
	if(pdlg.DoModal()==IDOK){
		dev=pdlg.GetDevMode();
		devmode=dev[0];
	}else return;

	PMODE lppm;
	CPrtMode pmdlg(&lppm);
	mok=pmdlg.DoModal();
	if(mok==IDCANCEL) return;
	if(lppm.mode<1) pm=1;else pm=0;


	HDC hdc=pdlg.CreatePrinterDC();
	if(hdc==NULL){
		MessageBox("��ǰѡ��Ĵ�ӡ��������\n������ѡ���ӡ������ʽ");	
		return;
	}
	kw=dbm.cpage->head.width;
	kh=dbm.cpage->head.height;
	yl=devmode.dmPrintQuality;
	
	if(devmode.dmOrientation==1){ //ȷ������1Ϊ��������
		w=devmode.dmPaperWidth-100;
		h=devmode.dmPaperLength-100;
	}else{
		h=devmode.dmPaperWidth-100;
		w=devmode.dmPaperLength-100;
	};
	

	//ÿҳֽ�����ش�С
	w=(int)(w*yl/255);
	h=(int)(h*yl/255);
	zm=cobj.curzoom;
	cobj.curzoom=1;
	bl=kw/(double)kh;
	ht=(int)(w/bl);


	//����ֽ�����⴦��ʽ
	if(lppm.px==0){
		if(ht<h){
			dx=0;
			dy=((h-ht)*kw/w)/2;
			h=ht;
		}else{	
			dy=0;
			dx=(int)(((w-h*bl)*kh/h)/2);
			w=(int)(h*bl);
		}
		//////////////// �� ӡ �� ֽ �� ///////////////////
		StartDoc(hdc,NULL);
		SetMapMode(hdc,MM_ISOTROPIC);
		SetWindowExtEx(hdc,kw,kh,NULL);
		SetViewportExtEx(hdc,w,h,NULL);
		StartPage(hdc);
		dbm.PrintShow(hdc,pm,dx,dy);
		EndPage(hdc);
		EndDoc(hdc);
		DeleteDC(hdc);
		///////////////////////////////////////////////////
	}
	//�Ŵ��ӡ
	if(lppm.px>0){
		mx=lppm.px+1;  //x�����ֽ����
		mh=ht*mx;	   //��Ҫ���ܸ߶�
		my=mh/h;	   //������������ֽ����
		j=mh-my*h;
		if(j>0) my++;
		sprintf(p,"����ֽ����:%d�š�\n�����ӡ��? ",mx*my);
		mok=MessageBox(p,"��ӡ���ȷ��",MB_YESNO);
		if(mok==IDNO) return;
		w=w*mx;
		pdx=(double)((double)kw/(double)mx);
		pdy=(double)((double)mh/(double)h);
		pdy=(double)((double)kh/pdy);

		
		for(i=0;i<my;i++){
			for(j=0;j<mx;j++){
				//////////////// �� ӡ �� ֽ �� ///////////////////
				dx=(int)(j*pdx);
				dy=(int)(i*pdy);
				StartDoc(hdc,NULL);
				SetMapMode(hdc,MM_ISOTROPIC);
				SetWindowExtEx(hdc,kw,kh,NULL);
				SetViewportExtEx(hdc,w,mh,NULL);
				StartPage(hdc);
				dbm.PrintShow(hdc,pm,-dx,-dy);
				EndPage(hdc);
				EndDoc(hdc);
				///////////////////////////////////////////////////
			}
		}
		DeleteDC(hdc);
	}
	cobj.curzoom=zm;
}

//���Դ���
void CMainWin::OnTest() 
{
	int w,h;
	testflag=1;
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	tstw.Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION,CRect(0,0,w,h),this);
	tstw.SetPage();
}

void CMainWin::OnUpdatePutout(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.filebz==1&&dbm.dbfok==true ? true:false);
}

//������ǰ�༭�ļ�
void CMainWin::OnPutout() 
{
	char fnm[256];
	if(MessageBox("ȷʵҪ�������漰������ļ�������","���������ļ�",MB_YESNO)!=IDYES) return;
	//������Ĺ����ļ�����������Ŀ¼
	dbm.CopyToHmiDir();
	//�ȱ��浱ǰ�ļ�
	wkw.OnFileSave();
	//����pw0�����ļ�
	strcpy(fnm,dbm.pwfname);
	MessageBox(fnm,"���淢��",MB_OK);
	dbm.CopyFileTo(fnm);
	//�����ļ���������
	dbm.SendHmiToSvr();
	MessageBox("�ļ��������!\n���ڵ��Ѿ����뱾����һ���Ľ��棡","���淢��",MB_OK);
}

void CMainWin::OnTohmidir() 
{
	char fnm[256];
	if(MessageBox("ȷʵҪ�������漰������ļ��ռ�������Ŀ¼��","�ռ������ļ�",MB_YESNO)!=IDYES) return;
	//������Ĺ����ļ�����������Ŀ¼
	dbm.CopyToHmiDir();
	//�ȱ��浱ǰ�ļ�
	wkw.OnFileSave();
	//����pw0�����ļ�
	strcpy(fnm,dbm.pwfname);
	dbm.CopyFileTo(fnm);
}


LRESULT CMainWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char fnm[256];
	if(message==1310&&wParam==5){ //�ļ����º��Ƿ���Ҫ���µ���
		GetLastRecFile(fnm);
		wkw.RecFileOkOpen(fnm);
	}
	return CWnd ::WindowProc(message, wParam, lParam);
}
//�༭ĸ�߶�̬����
void CMainWin::OnBusralate() 
{
	BFCfgDlg dlg;
	dlg.cpage=dbm.cpage;
	dlg.DoModal();
}
//����滥������
void CMainWin::OnZmctl() 
{
	int i;
	N_APDINFO tmp;
	CCfgZmDlg dlg;
	//��ȡ��ҳ�Ŀ�����Ϣ
	i=dbm.GetIndexOfAppInfo((BYTE)dbm.curpage);
	if(i>=0) tmp=dbm.apdinfo[i];			//���ڣ���ȡ��
	else memset(&tmp,0,sizeof(N_APDINFO));	//������������ʱ����
	dlg.tmp=tmp;
	if(dlg.DoModal()!=IDOK) return;

	//����༭�Ľ��
	tmp=dlg.tmp;
	tmp.pageno=(BYTE)dbm.curpage;
	if(tmp.enablein==0&&tmp.enableout==0) //ͬʱȡ��ʱ��ɾ��ԭ�еļ�¼
	{
		if(i>=0) dbm.DelAAppendInfo((BYTE)dbm.curpage);
		dbm.editbz=1;
		return;
	}
	if(i>=0) dbm.apdinfo[i]=tmp;
	else dbm.AddAppendInfo(tmp);
	dbm.editbz=1;
}

void CMainWin::OnUpdateTosqrt(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.GetFirstSelObj()<0 ? false:true);
	
}

void CMainWin::OnGetnm() 
{
	GetNMDlg dlg;
	dlg.dbm=&dbm;
	dlg.DoModal();
}

void CMainWin::OnGetid() 
{
	GetIdDlg dlg;
	dlg.dbm=&dbm;
	dlg.DoModal();
}

//���SVG��ʽ
void CMainWin::OnOutsvg() 
{
	char filter[256],path[256],title[64];
	char fnm[256];
	char *lp;
	strcpy(path,cobj.path[1].path);
	strcpy(title,"����ΪSVGͼ�θ�ʽ�ļ�");
	strcpy(filter,"SVG��ʽ�ļ�(*.svg)|*.svg");
	CFileDialog  fodlg(false,NULL,NULL,OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;
	fodlg.m_ofn.lpstrInitialDir=path;
	if(fodlg.DoModal()==IDOK)
	{
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".svg");
	  dbm.SaveFileSvg(fnm);
	};
}

//����CIMģ��
void CMainWin::OnLoadcim() 
{
	char filter[512],fnm[512],title[64];
	strcpy(title,"��CIM XML�ļ�");
	strcpy(filter,"CIM XML�ļ�(*.xml)|*.xml|");
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  ReadPowerCimFile(fnm);
	};
}

void CMainWin::OnSvgname() 
{
	if(!IsCimOpen())
	{
		MessageBox("CIMģ��δ�򿪣����ܽ������ָ���!","����",MB_OK|MB_ICONSTOP);
		return;
	}
	dbm.ExchangeCimName();
	MessageBox("��CIM�����豸������ɣ�\n֮�󣬲���[�Զ����豸������ID]�������SVGͼ����ά������.","��ʾ",MB_OK);
}
