// ScadaWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ScadaWin.h"
#include "comobj.h"
#include "middll.h"
#include "DObj.h"
#include "stflwdlg.h"
#include "sendlg.h"
#include "viewdev.h"
#include "math.h"
#include "CrossObj.h"
#include "bclass.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;		//��������
extern char *usertype[];
extern CMainFrame* pFrame;

extern char *buff;

char *stypenm[]={"�����","����","����","�������ѹ��","�������ѹ��"};





//int mk1=0;

DWORD WINAPI ReadRLtData(LPVOID arg) //��ȡʵʱƽ̨����
{   
	/*CClientDC dc(0);
	char p[100];*/
	ScadaWin *swin;
	swin=(ScadaWin*)arg;
    for(;;){
	   /*sprintf(p,"mk1=%d",mk1);
	   dc.TextOut(10,10,p);
	   mk1++;*/
	   if(swin->dbm.hisplay==1) //��ȡ��ʷ
	   {
			swin->ReadHisData();
	   }
	   
	   swin->UpdateAllData();
	   SuspendThread(swin->hThread_rd);
	}
	return 0;   
}

/////////////////////////////////////////////////////////////////////////////
// ScadaWin

ScadaWin::ScadaWin()
{
	winmode=0;
	t1=0;
	t2=0;
	mbg.Create(1,1);
	msr.Create(1,1);
	dbm.msr=&msr;
	dx=0;
	dy=0;
	wx=0;
	wy=0;
	enabletimer=1;
	r_cl=NULL;
	r_st=NULL;	
	r_bs=NULL;
	r_pe=NULL;
	r_ba=NULL;
	r_an=NULL;
	r_da=NULL;  
	r_tm=NULL;
	r_am=NULL;
	r_sc=NULL;
	r_sf=NULL;
	r_fw=NULL;
	r_ph=NULL;
	r_at=NULL;
	r_yb=NULL;
	r_fsh=NULL;
	r_ppie=NULL;
	r_sen=NULL;
	r_rv=NULL;
	r_tr=NULL;
	r_rs=NULL;
	r_zn=NULL;
	r_n1=NULL;
	r_sw=NULL;
	r_mt=NULL;	//�����ı�����
	r_spe=NULL; //ϵͳ��ͼ
	
	spesum=0;
	mtsum=0;	//����
	rssum=0;
	trsum=0;  
	rvsum=0;
	stsum=0;
	clsum=0;
	bssum=0;
	pesum=0;
	basum=0;
	ansum=0;
	dtsum=0;
	tmsum=0;
	amsum=0;
	scsum=0;
	sfsum=0;
	fwsum=0;
	phsum=0;
	atsum=0;
	ybsum=0;
	fssum=0;
	ppsum=0;
	sesum=0;
	znsum=0;
	n1sum=0;
	swsum=0;

	cursor=0;
	rcursor=0;
	dnbz=0;
	pb=NULL;
	dmsum=0; //������
	SetDgxParam();
	updatergn=NULL;

	hThread_rd=NULL;
	dwThreadID=0;
}

ScadaWin::~ScadaWin()
{
	
}


BEGIN_MESSAGE_MAP(ScadaWin, CWnd)
	//{{AFX_MSG_MAP(ScadaWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(IDC_VIEWDEV, OnViewdev)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_LOWZOOM, OnLowzoom)
	ON_COMMAND(1800, OnMainPage)
	ON_COMMAND(IDC_RESVJS, OnResvjs)
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(39000,39500,OnCommandRange)
	ON_COMMAND(IDC_AVCOPT, OnAvcopt)
	ON_COMMAND(IDC_PQVOPT, OnPqvopt)
	ON_COMMAND(IDC_N12EFT, OnN12eft)
	ON_COMMAND(IDC_N12EFT3D, OnN12eft3d)
	ON_COMMAND(IDC_GENMSG, OnGenmsg)
	ON_COMMAND(IDC_TRANMSG, OnTranmsg)
	ON_COMMAND(IDC_SVOPT, OnSvopt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//ON_COMMAND_RANGE(39000,39500,OnCommandRange)
/////////////////////////////////////////////////////////////////////////////
// ScadaWin message handlers

BOOL ScadaWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}


int ScadaWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	//�����ݿ�(����ʵʱ��)
	SetCurDbf(0);
	////////////��Ƶ�𵴴���///////////////////////////////////////
	lwin.rrd=&rrd;
	lwin.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,111);
	lwin.ShowWindow(SW_HIDE);
	///////////////////////////////////////////////////////////////
	dmwin.rrd=&rrd;
	dmwin.Create(IDD_DMDLG,this); 
	dmwin.ShowWindow(SW_HIDE); 
	///////////////////////////////////////////////////////////////
	//���ö�ʱ��
	SetTimer(101,UPDATETM,NULL);	  //�����͹����ı���ʱ
	SetTimer(102,1000,NULL);			  //ʱ����ʾ
	SetTimer(103,5000,NULL);		  //�Զ�ˢ������
	SetTimer(104,1000,NULL);		  //��ʷ�ط�
	//������ʾ��
	twin.Create("","",WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this,110);
	twin.ShowWindow(SW_HIDE);
	hThread_rd =CreateThread (NULL,0,ReadRLtData,this,CREATE_SUSPENDED,&dwThreadID);

	//������ѹ�����Ӵ���
	SvWnd=CreateSvigilWnd(this,TRUE);
	::GetWindowRect(SvWnd,&svcrt);
	::ShowWindow(SvWnd,SW_HIDE);
	int sw=GetSystemMetrics(SM_CXSCREEN);
	::MoveWindow(SvWnd,sw-svcrt.Width()-10,80,svcrt.Width(),svcrt.Height(),false);
	return 0;
}

void ScadaWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	if(cx>10&&cy>10) //��ʼ����ʱ����10*10�Ĵ��ڴ�С���������º���
	{
		if(dbm.lookdown==1)
		{
			ToMyZm(1.15);
			CreateAllrgn();
		}
		else if(dbm.page.head.showbyrt==0) SetFirstPosition();
		else if(dbm.page.head.showbyrt==1) ComputShowByRt();
		
		mbg.SizeChange(cx,cy);
		msr.SizeChange(cx,cy);
		sct.ScrSizeChange(wx,wy);
		if(dbm.scf.showdgx==1&&dbm.page.head.type>0) sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
		ShowA(mbg);
	}
}

void ScadaWin::OnPaint() 
{
	CRect *rt,rt1;
	RGNDATA *lp;
	int i,n,m,r,ks;
	CRgn rgn;
	rgn.CreateRectRgn(0,0,10,10);
	r=GetUpdateRgn( &rgn,FALSE);
	CPaintDC dc(this);
	ks=GetKeyState(VK_LCONTROL);
	if(r!=NULLREGION||r!=ERROR)
	{
		n=rgn.GetRegionData((LPRGNDATA)buff,65535);
		if(n!=ERROR||n!=NULLREGION)
		{
			lp=(RGNDATA*)buff;
			m=lp->rdh.nCount;
			rt=(CRect*)lp->Buffer;
			for(i=0;i<m;i++)
			{
				rt1=rt[i];
				if((ks<0||cursor==1)&&dnbz==1) Show(dc.m_hDC,rt1);
				else PaintShow(dc.m_hDC,rt1);
			}
		}
	}
	rgn.DeleteObject();
	dtupdate=1;   //ʱ����±�־
}


//��������ʱ����ʾ
void ScadaWin::EndShow()
{
	CRect rt;
	HDC hdc=::GetDC(m_hWnd);
	rt=srt;
	//��������ʾ��������
	ShowA(mbg);
	//����ʾ3D����
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,dx,dy,rt);
	Show3DObj(msr,rt);//����ͼ��ʾ
	//dbm.ShowTy(msr,dx,dy,srt);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBlt(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}
      
//��ʾ�ȸ���
void ScadaWin::ShowDgx(CDIB&mdc)    
{
	if(dbm.scf.showdgx==0||dbm.page.head.type<1)  return;
	Set3DEnv();//����3D����
	sct.DrawDGX(mdc); 
}
 
    

void ScadaWin::Show(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	dbm.ShowBkgd(msr,rt1);
	dbm.MSDownShow(msr,dx,dy,rt);
	Show3DObjj(msr,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

void ScadaWin::PaintShow(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,dx,dy,rt);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);//��ʾ���泱��
	Show3DObj(msr,rt);
	msr.BitBltRect(hdc,rt2,rt);
}


//����������ʾ3D����
void ScadaWin::Show3DObj(CDIB&mdc,CRect rt)
{
	int i;
	switch(dbm.scf.showrev)
	{
	case 1:		//������й�
		dbm.SHowRevBarP(mdc,rt,dx,dy,r_rv,rvsum);
		//ShowFuntTitle(mdc,rt,0);
		break;
	case 2:		//������޹�
		dbm.SHowGenBarQ(mdc,rt,dx,dy,r_rv,rvsum);
		//ShowFuntTitle(mdc,rt,1);
		break;
	case 3:		//��ѹ���й�
		dbm.ComputeTpzoom(r_tr,trsum,wy);
		dbm.SHowTranRevBarP(mdc,rt,dx,dy,r_tr,trsum);
		//ShowFuntTitle(mdc,rt,2);
		break;
	case 4:		//��ѹ���¶���ͼ
		dbm.ComputeTptzoom(r_tr,trsum,wy);
		//ShowFuntTitle(mdc,rt,7);
		break;
	case 5: case 6:case 7://n-1��������
		dbm.SHowN1Bar(mdc,rt,dx,dy,r_n1,n1sum);
	    //ShowFuntTitle(mdc,rt,dbm.scf.showrev+3);
		break;
	case 8:					//����SOE�ط�
		dbm.SHowSwtBar(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 9:					//��·����
		dbm.ShowSwtSccBar(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 10:   //������ͼ
		dbm.SHowZoneBar(mdc,rt,dx,dy,r_pe,pesum);
		break;
	case 11:   //ϵͳ��ͼ
		dbm.SHowSpieBar(mdc,rt,dx,dy,r_spe,spesum);
		break;
	case 12:   //N1Eft��ͼ
		dbm.SHowN1EftBar(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	} 
	if(dbm.scf.lmd!=0)
	{
		dbm.ComputeSenzomm(r_sen,sesum,wy);
		ShowSelFlag(mdc.m_hDC,dx,dy);
		dbm.SHowSenBar(mdc,rt,dx,dy,r_sen,sesum);
		i=sentype==0 ? 3:4;
		if(sentype>=0&&sentype<2)	ShowFuntTitle(mdc,rt,i);
	}
}

//��3Dͼ��
void ScadaWin::Show3DObjj(CDIB&mdc,CRect rt)
{
	if(dbm.lookdown==0) return;
	switch(dbm.scf.showrev)
	{
	case 1:
		dbm.SHowRevBarPj(mdc,rt,dx,dy,r_rv,rvsum);
		break;
	case 2:
		dbm.SHowGenBarQj(mdc,rt,dx,dy,r_rv,rvsum);
		break;
	case 3:
		dbm.ComputeTpzoom(r_tr,trsum,wy);
		dbm.SHowTranRevBarPj(mdc,rt,dx,dy,r_tr,trsum);
		break;
	case 4:
		dbm.ComputeTptzoom(r_tr,trsum,wy);
		dbm.SHowTranTBarj(mdc,rt,dx,dy,r_tr,trsum);
		break;
	case 5: case 6:case 7:
		dbm.SHowN1Barj(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	case 8:
		dbm.SHowSwtBarj(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 9:
		dbm.ShowSwtSccBarj(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 10:
		dbm.SHowZoneBarj(mdc,rt,dx,dy,r_pe,pesum);
		break;
	case 11:   //ϵͳ��ͼ
		dbm.SHowSpieBarj(mdc,rt,dx,dy,r_spe,spesum);
		break;
	case 12:
		dbm.SHowN1EftBarj(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	}
	if(dbm.scf.lmd!=0){
		dbm.ComputeSenzomm(r_sen,sesum,wy);
		ShowSelFlag(mdc.m_hDC,dx,dy);
		dbm.SHowSenBarj(mdc,rt,dx,dy,r_sen,sesum);
	}
}


//����ͼ����ʾ�������ϣ��Ա�������ʾ
void ScadaWin::ShowA(CDIB&mdc)
{
	CRect rt;
	rt=srt;
	rt.OffsetRect(-dx,-dy);
	dbm.ShowBkgd(mdc,rt);
	dbm.ShowBgDbx(mdc,dx,dy,srt,0);
	ShowDgx(mdc);
	dbm.ShowStatic(mdc,dx,dy,srt);
	dbm.ShowPlatte(mdc);
	ShowDmDraw(mdc.m_hDC,dmpt,segsum,dmsdot);
}

void ScadaWin::ShowC(HDC hdc,HRGN hrgn)
{
	int i,w,h;
	CRect rt,rt2;
	GetRgnBox(hrgn,rt);
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	OffsetRgn(hrgn,-rt.left,-rt.top);
	SaveDC(msr.m_hDC);
	SelectObject(msr.m_hDC,hrgn);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	RestoreDC(msr.m_hDC,-1);
	OffsetRgn(hrgn,rt.left,rt.top);
	dbm.ShowAct(msr,dx,dy,rt);
	for(i=0;i<atsum;i++)
	{
	   if(r_at[i].pt!=NULL&&r_at[i].ptsum!=0) ShowActObj(msr.m_hDC,-rt.left+dx,-rt.top+dy,i);
	}
	ShowSelFlag(msr.m_hDC,-rt.left+dx,-rt.top+dy);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBltRect(hdc,rt2,rt);
}


void ScadaWin::ShowC(HDC hdc,CRect rtshow)
{
	int i,w,h;
	CRect rt,rt2;
	rt=rtshow;
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,dx,dy,rt);
	for(i=0;i<atsum;i++)
	{
		if(r_at[i].pt!=NULL&&r_at[i].ptsum!=0) 
		 ShowActObj(msr.m_hDC,-rt.left+dx,-rt.top+dy,i);
	}
	Show3DObj(msr,rt);//����ͼ��ʾ
	ShowSelFlag(msr.m_hDC,-rt.left+dx,-rt.top+dy);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBltRect(hdc,rt2,rt);
}




void ScadaWin::DrawShow()
{
	CClientDC dc(this);
	Show(dc,CRect(0,0,wx+1,wy+1));
}


//���㾵ͷ���ĵ�
void ScadaWin::ComputZCenter()
{
	if(xmax<=0){
	  vx=(double)((-dx+wx/2)/dbm.curzoom);
	}else{
	  vx=(double)(dbm.page.head.width/(double)2);
	}
	if(ymax<=0){
	  vy=(double)((-dy+wy/2)/dbm.curzoom);
	}else{
	  vy=(double)(dbm.page.head.height/(double)2);	
	}
}

void ScadaWin::InitMoveObj(HISHMI *hmi,int mode)
{
	int   objsum[100];			
	enabletimer=0;
	dmsum=0;
	dbm.scf.lmd=0;
	dbm.lookdown=0;
	dbm.curang=0;
	cursor=0;
	rcursor=0;
	dbm.scf.showrev=0;
	dbm.TJObjSum(objsum);

	//������Ҫ����Ļ����
	ansum=objsum[64];				//ģ����
	if(ansum!=0) r_an=new RANL[ansum];
	mtsum=objsum[84];				//ģ����
	if(mtsum!=0) r_mt=new RMTXT[mtsum];
	rssum=objsum[65];				//ˮ��
	if(rssum!=0) r_rs=new RRES[rssum];
	stsum=objsum[66];				//״̬�����豸
	if(stsum!=0) r_st=new RSTA[stsum];
	ybsum=objsum[67];				//�Ǳ�
	if(ybsum>0) r_yb=new RMETER[ybsum];
	spesum=objsum[68];
	if(spesum>0) r_spe=new RSPIE[spesum];
	n_spe=spesum;
	basum=objsum[69];				//��ͼ
	if(basum!=0) r_ba=new RBAR[basum];
	pesum=objsum[70];				//��ͼ
	if(pesum!=0) r_pe=new RPIE[pesum];
	n_pie=pesum;
	dtsum=objsum[71];
	if(dtsum>0) r_da=new ROBJ[dtsum];   //����
	tmsum=objsum[72];
	if(tmsum>0) r_tm=new ROBJ[tmsum];	//ʱ��
	amsum=objsum[73];
	if(amsum>0) r_am=new RAML[amsum];	//GIF����
	scsum=objsum[74];
	if(scsum>0) r_sc=new RSCRTXT[scsum];//�����ı�
	phsum=objsum[75];
	if(phsum>0) r_ph=new RPUSH[phsum];	//��ť
	sfsum=objsum[76];
	if(sfsum>0) r_sf=new RSELFCTL[sfsum];//�����ؼ�
	fwsum=objsum[77];				//������ 
	if(fwsum>0) r_fw=new RFLOW[fwsum];   
	clsum=objsum[78];				//������
	if(clsum!=0) r_cl=new RCONL[clsum];
	bssum=objsum[79];				//ĸ��
	if(bssum!=0) r_bs=new RBUS[bssum];
	atsum=objsum[80];
	if(atsum>0) r_at=new RACTOBJ[atsum];//�����
	fssum=objsum[81];
	if(fssum>0) r_fsh=new RFLASH[fssum];//FLASH����
	ppsum=objsum[82];
	if(ppsum>0) r_ppie=new RPPIE[ppsum];//�ٷֱ�ͼ
	znsum=objsum[83];
	if(znsum>0) r_zn=new RZONE[znsum]; //����

	if(sfsum!=0||fssum!=0) dbm.page.head.type=0;
	//����̬�����ӹ���
	GetObjFromDbm();

	if(dbm.dbzt==1) RegistHis();
	//Ϊ���������ռ�����
	if(dbm.page.head.type>0) CollectDevice(); //�ǽ���ͼ��������ͼ
	//����Ҫ���ӵ�Ԫ���������
	GetRevSenSum();
	SetRRevSen();
	Order3dPos(); //����λ��
	oldsel=-1;

	GetDevSum();  //ͳ���豸����
	switch(mode)
	{
	case 0:
		dbm.ZoomPage(0);
		Set3DEnv();//����3D����
		SetFirstPosition();
		ComputZCenter();
		break;
	case 1:
		dx=hmi->dx;
		dy=hmi->dy;
		dbm.curzoom=hmi->zoom;
		dbm.scf.showdgx=hmi->showdgx;
		dbm.scf.showrev=hmi->showrev;
		dbm.scf.ctrtype=hmi->ctrtype;
		dbm.lookdown=hmi->lookdown;
		vx=hmi->vx;
		vy=hmi->vy;
		break;
	case 2:
		if(hmi->mode==0) break;
		dbm.curzoom=hmi->zoom;
		ComputMaxXY();
		dx=xmax/2;
		dy=ymax/2;
		ComputZCenter();
		break;
	}
	//���¼���ҳ���С
	ZoomChange();
	if(dbm.page.head.showbyrt==1)
	{
		ComputShowByRt();
	}
	//���õȸ��߲���
	SetDgxParam();
	SetContourParam();
	///////////////////////
	UpdateAllData();

	//����ʱ������
	enabletimer=1;
	t2=0;
	///////////////////////////////////////////////////////////////
	dtupdate=1;
	if(dbm.page.head.type==0)
	{
		if(cobj.nwin!=NULL) cobj.nwin->ShowWindow(SW_HIDE);
	}
	if(cobj.nwin!=NULL) cobj.nwin->PageChange();
	SetStatusZoom();
	//EndShow();
	//CreateAllrgn();
	//����ˢ�³���
	dbm.msdwn=0;
}


//���õȸ��߲���
void ScadaWin::SetContourParam()
{
	int i;
	CRect rt;
	switch(dbm.scf.ctrtype)
	{
	case 0:case 1:case 2:   //�ڵ��ѹ
		sct.csum=bssum>MAXCONTOUR ? MAXCONTOUR:bssum;
		for(i=0;i<bssum;i++)
		{
			r_bs[i].bs->ort.GetRECT(rt);
			sct.SetRectPos(rt,i);
		}     
		break;
	case 3:  //�����
	case 5:  //�����
		sct.csum=fwsum>MAXCONTOUR ? MAXCONTOUR:fwsum;
		for(i=0;i<fwsum;i++) sct.SetNPOINTPos(r_fw[i].flw->pt,r_fw[i].flw->ptsum,i);
		break;
	case 4:  //��ѹ��
		sct.csum=trsum>MAXCONTOUR ? MAXCONTOUR:trsum;
		for(i=0;i<trsum;i++)
		{
			r_tr[i].bs->ort.GetRECT(rt);
			sct.SetRectPos(rt,i);
		}
		break;
	}
	sct.MemSetPb();
}

int kk=0;
//ˢ������
bool ScadaWin::UpdateAllData()
{
	bool b=false;
	if(!cobj.dbok) return false;
	if(t2==1) return false;
	t2=1;
	b|=UpDateAnl();
	b|=UpDateMttxt();
	b|=UpDateBar();
	UpDateAct();
	b|=UpDatePPie();
	b|=UpDatePie();
	b|=UpDateSysPie();
	b|=UpdateFlow();
	b|=UpdateBus();
	b|=UpdateStatus();
	b|=UpdateTranformer();
	b|=UpdateDmData();
	UpdateGifaml();
	UpDateMeter();
	//���ݱ仯��Ĵ���
	if(b==true)
	{
		if(dbm.scf.showdgx==1)	sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
		nettp.CheckConlEle();
		allupdate=1;
	}
	t2=0;
	return  b;
}

//ˢ��ģ����
bool ScadaWin::UpDateAnl()
{
	int i;
	bool rtn=false;;
	READDEV ran; //ģ��������
	for(i=0;i<ansum;i++)
	{
	  if(r_an[i].anl->vr.did<0) continue;
	  ran=r_an[i].anl->vr;
	  if(!rrd.ReadDevData(ran)) continue;
	  rtn|=r_an[i].bs->SetAnlVal(ran);
	}
	return rtn;
}

//ˢ�¶����ı�
bool ScadaWin::UpDateMttxt()
{
	int i;
	bool rtn=false;;
	READDEV ran; //ģ��������
	for(i=0;i<mtsum;i++)
	{
	  if(r_mt[i].txt->did<0) continue;
	  ran.did=r_mt[i].txt->did;
	  ran.dtype=r_mt[i].txt->type;
	  ran.recno=r_mt[i].recno;
	  rrd.ReadDevData(ran);
	  if(ran.sta!=r_mt[i].txt->sta)
	  {
			r_mt[i].txt->sta=ran.sta;
			r_mt[i].recno=ran.recno;
			rtn=true;
	  }
	}
	return rtn;
}

//ˢ�°�ͼ
bool ScadaWin::UpDateBar()
{
	float fnewval;
	int i,j;
	READDEV ran;
	bool rtn=false;
	for(i=0;i<basum;i++)
	{
		if(r_ba[i].bar->dsrc.xsmode>0)//���ڶ�̬������Ϣ
		{
			rrd.SortPreDm();//��Ԥ������水��������
			break;
		}
	}
	rrd.SortPreDm();//��Ԥ������水��������
	for(i=0;i<basum;i++)
	{
		if(r_ba[i].bar->dsrc.xsmode>0)//��̬������Ϣ
		{
			rtn=rrd.GetDynPreDm(r_ba[i].bar->dsrc.xsmode,r_ba[i].bar);	
		}
		else //ָ������ֵ
		{
			j=r_ba[i].bar->dsrc.did;
			if(j<0) continue;
			ran.recno=r_ba[i].recno;
			ran.did=j;
			ran.dtype=r_ba[i].bar->dsrc.dtype;
			rrd.ReadDevData(ran);
			r_ba[i].recno=ran.recno;
			r_ba[i].bar->max=ran.value[2];
			r_ba[i].bar->min=ran.value[3];
			fnewval=GetSingleVal(ran,r_ba[i].bar->dsrc.xsmode);
			if(fabs(r_ba[i].bar->rval.curval-fnewval)>0.01)
				rtn=true;
			r_ba[i].bar->rval.curval=fnewval;
		}
  	}
	return rtn;
}



//ˢ���Ǳ�
void ScadaWin::UpDateMeter()
{
	int i,k;
	YBDATA tmp;
	for(i=0;i<ybsum;i++)
	{
		for(k=0;k<r_yb[i].mtr->dbsum;k++)
		{
			memset(&tmp,0,sizeof(YBDATA));
			tmp.did=r_yb[i].mtr->dbs[k].did;
			if(tmp.did<0) continue;
			tmp.recno=r_yb[i].recno[k];
			tmp.dtype=r_yb[i].mtr->dbs[k].dtype;
			tmp.vtype=r_yb[i].mtr->dbs[k].xsmode;
			
			rrd.ReadYbData(tmp);
			r_yb[i].recno[k]=tmp.recno;
			SetYbVal(r_yb[i].mtr[0],tmp,k);
		}
  	}
}

//ˢ�»����
void ScadaWin::UpDateAct()
{
	int i,j;
	float val;
	READDEV ran;
	for(i=0;i<atsum;i++)
	{
		if(r_at[i].pt==NULL||r_at[i].ptsum==0) continue;
		if(r_at[i].act->runmode!=1) continue;
		j=r_at[i].act->dsrc.did;
		if(j<0) continue;
		ran.recno=r_at[i].recno;
		ran.did=j;
		ran.dtype=r_at[i].act->dsrc.dtype;
		rrd.ReadDevData(ran);
		r_at[i].recno=ran.recno;
		val=GetSingleVal(ran,r_at[i].act->dsrc.xsmode);
		if(r_at[i].curval!=(double)val)
		{
			r_at[i].curval=(double)val;
			ComputActRect(i);
		}
	}
}

//ˢ�±�ͼ
bool ScadaWin::UpDatePie()
{
	bool rtn=false;
	int i,j;
	READDEV ran;
	for(i=0;i<pesum;i++){
		j=r_pe[i].pie->did;
		if(j<0) continue;
		ran.recno=r_pe[i].recno;
		ran.did=j;
		ran.dtype=0;
		ran.xsmode=r_pe[i].pie->type;
		if(rrd.ReadZoneAnl(ran))
		{
			r_pe[i].recno=ran.recno;
			if( r_pe[i].pie->pcur!=ran.value[0]||r_pe[i].pie->qcur!=ran.value[1]||r_pe[i].pie->maxv!=ran.value[2])
			{
				r_pe[i].pie->pcur=ran.value[0];
				r_pe[i].pie->qcur=ran.value[1];
				r_pe[i].pie->maxv=ran.value[2];
				rtn=true;
			}
		}
	}
	return rtn;
}

//ˢ�±�ͼ
bool ScadaWin::UpDateSysPie()
{
	bool rtn=false;
	int i;
	PWSYSSUM val;
	double vmax;
	rrd.ReadPwSys(val);
	for(i=0;i<spesum;i++){
		if(memcmp(&val,&r_spe[i].pie->val,sizeof(PWSYSSUM))==0) continue;
		rtn=true;
		r_spe[i].pie->val=val;
		switch(r_spe[i].pie->type)
		{
		case 0: //ϵͳ����
			r_spe[i].pie->num=3;
			vmax=val.GenMax;
			if(vmax==0) 
			{
				r_spe[i].pie->vl[0]=0;
				r_spe[i].pie->vl[1]=0;
				r_spe[i].pie->vl[2]=0;
				r_spe[i].pie->vl[3]=0;
				r_spe[i].pie->error=1; //��������
			}else{
				r_spe[i].pie->vl[0]=val.GenP/vmax;
				r_spe[i].pie->vl[1]=val.UpRes/vmax;
				r_spe[i].pie->vl[2]=val.StopP/vmax;
				r_spe[i].pie->vl[3]=val.DownRes/vmax;
				r_spe[i].pie->error=0;
			}
			break;
		case 1://ϵͳ����
			r_spe[i].pie->num=2;
			vmax=val.LoadMax;
			if(vmax==0) 
			{
				r_spe[i].pie->vl[0]=0;
				r_spe[i].pie->vl[1]=0;
				r_spe[i].pie->error=1; //��������
			}else{
				r_spe[i].pie->vl[0]=val.LoadP/vmax;
				r_spe[i].pie->vl[1]=1.00-r_spe[i].pie->vl[0];
				r_spe[i].pie->error=0;
			}
			break;
		}
		
	}
	return rtn;
}


//ˢ�°ٷֱ�ͼ
bool ScadaWin::UpDatePPie()
{
	int i,j;
	float mv,cv;
	double p,q,ps;
	bool rtn=false;
	READDEV ran;
	for(i=0;i<ppsum;i++)
	{
		j=r_ppie[i].ppe->did;
		if(j<0) continue;
		ran.recno=r_ppie[i].recno;
		ran.did=j;
		ran.dtype=r_ppie[i].ppe->type+1;
		if(rrd.ReadDevData(ran))
		{
			r_ppie[i].recno=ran.recno;
			if(dbm.scf.ftype<4)
			{
				mv=ran.value[4];
				p=ran.value[0];
				q=ran.value[1];
				ps=sqrt(p*p+q*q);
				cv=(float)ps;//ran.value[0];

			}else{
				mv=ran.value[6];
				cv=ran.value[7];
			}
			if(r_ppie[i].ppe->maxv!=mv){
				r_ppie[i].ppe->maxv=mv;
				rtn=true;
			};
			if(r_ppie[i].ppe->curval!=cv)
			{
				r_ppie[i].ppe->curval=cv;
				rtn=true;
			};
			r_ppie[i].recno=ran.recno;
		}else{
			r_ppie[i].ppe->curval=0;
		}
	}
	return rtn;
}



//ˢ�³���������
bool ScadaWin::UpdateFlow()
{
	bool bl,rtn=false;
	int i,j,k;
	READDEV  ran;
	k=dbm.scf.ctrtype;
	for(i=0;i<fwsum;i++)
	{
		j=r_fw[i].flw->did;

		if(j<0) continue;
		ran.recno=r_fw[i].recno;
		ran.did=j;
		ran.dtype=r_fw[i].flw->type+1; //������ֱ��
		if(!rrd.ReadDevData(ran)){
		   if(k==3 || k==5) rtn|=sct.SetContourEnable(i);
		   memset(&r_fw[i].flw->vr,0,sizeof(READDEV));
		}else{
	  	  bl=SetFlowData(i,ran);
		  if((k==3 ||k==5)&&bl) SetAContourVal(i); //�����3,���������ֵ
		  rtn|=bl;
		}
		r_fw[i].recno=ran.recno;
	}
	return rtn;
}


//ˢ��ĸ������
bool ScadaWin::UpdateBus()
{
	bool bl,rtn=false;
	int i,j,k;
	READDEV ran;//���ڶ�ȡĸ�ߵ�ѹ
	ran.dtype=3;
	k=dbm.scf.ctrtype;
	for(i=0;i<bssum;i++)
	{
		bl=false;
		j=r_bs[i].bus->did;
		if(j<0) continue;
		//����ĸ������
		ran.recno=r_bs[i].recno;
		ran.did=j;
		if(!rrd.ReadDevData(ran))
		{
		  if(k<3) rtn|=sct.SetContourEnable(i);
		  memset(&r_bs[i].bus->vr,0,sizeof(READDEV));
		}else{
			
			if(memcmp(&r_bs[i].bus->vr,&ran,sizeof(READDEV))!=0)
			{
				memcpy(&r_bs[i].bus->vr,&ran,sizeof(READDEV));
		    	if(k<3) SetAContourVal(i);
				rtn=true;
			}
			r_bs[i].recno=ran.recno;
		}
		
	}
	return rtn;
}

void ScadaWin::ChangeShow()//wd
{
	//if(bShowProcessData == false)
	for (int i=0;i<stsum;i++)
	{
		r_st[i].recno = -1;
	}
	
	for (i=0;i<fwsum;i++)//������
	{
		r_fw[i].recno=-1;
	}

	for (i=0; i<bssum; i++)//ĸ��
	{
		r_bs[i].recno = -1;
	}

	for (i=0; i<trsum; i++)//��ѹ������
	{
		r_tr[i].recno = -1;
	}

	for (i=0; i<swsum; i++)//����
	{
		r_sw[i].recno = -1;
	}

}

//ˢ�����ͼԪ��״̬
bool ScadaWin::UpdateStatus()
{
	int i,k;
	bool rtn=false;
	READDEV ran;
	READDEV_STA tmp;
	N_ELEGRPA *elg;	
	k=0;
	for(i=0;i<stsum;i++)
	{
		elg=r_st[i].elg;
		if (elg->type == 2)
		{
			//TRACE("111");
			ran.dtype=100;//elg->subtype;
			ran.recno=r_st[i].recno;
			ran.did = r_st[i].elg->did;
			
			if(rrd.ReadDevData(ran))
			{ //��ȡ�ɹ��󣬱�������
				r_st[i].recno=ran.recno;
				memcpy(&r_st[i].elg->vr, &ran, sizeof(READDEV));
			}
			else
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			
		}

		if(r_st[i].elg->type!=1) continue;
		elg=r_st[i].elg;
		tmp.did=elg->did;
		if(tmp.did<0)			 continue;
		
		switch(elg->subtype)
		{
		case 0:case 2:case 6: case 10://���ػ���ģ����װ��
			tmp.subtype=elg->subtype;
			tmp.recno=r_st[i].recno;
			if(rrd.ReadStaData(tmp)){ //��ȡ�ɹ��󣬱�������
				if(elg->vr.sta!=tmp.zt||elg->vr.ele!=tmp.ele)
				{
					elg->vr.sta=tmp.zt;
					elg->vr.ele=tmp.ele;
					rtn=true;
				}
				r_st[i].recno=tmp.recno;
			}else{
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			
			}
			
			break;
		case 1:case 3:case 4:case 5: case 9: //��ģ������װ��
			ran.did=elg->did;
			ran.recno=r_st[i].recno;
			ran.dtype=cobj.TypeTran(2,elg->subtype); //ת���ɿɶ�������
			if(ran.dtype==-1) break;
			if(rrd.ReadDevData(ran))
			{
				rtn|=r_st[i].bs->SetDevAnl(ran);
				r_st[i].recno=ran.recno;
			}else{
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			}
			break;
		}
	}
	return rtn;
}

//ˢ�³�վ����
bool ScadaWin::UpdateStation()
{
	return true;
}


//ˢ�±�ѹ������
bool ScadaWin::UpdateTranformer()
{
	int i;
	bool rtn=false;
	N_ELEGRPA *elg;	
	READDEV ran;
	for(i=0;i<trsum;i++)
	{
		if(r_tr[i].elg->type!=1) continue;
		elg=r_tr[i].elg;
		if(elg->did<0) continue;
		

		switch(elg->subtype)
		{
		case 7:case 8:
			ran.did=elg->did;
			ran.recno=r_tr[i].recno;
			ran.dtype=cobj.TypeTran(2,elg->subtype); //ת���ɿɶ�������
			if(ran.dtype==-1) break;
			if(rrd.ReadDevData(ran))
			{
				rtn|=r_tr[i].bs->SetDevAnl(ran,i);
				r_st[i].recno=ran.recno;
			}else{
				memset(&r_tr[i].elg->vr,0,sizeof(READDEV));
			}
			SetAContourVal(i);
			break;
		}
	}
	return rtn;
}



//ˢ�¶�����������
void ScadaWin::UpdateGifaml()
{
	int i,j;
	READDEV_STA tmp;
	for(i=0;i<amsum;i++)
	{
		r_am[i].zt=1;
		r_am[i].enable=1;
		j=r_am[i].ngf->dsrc.did;
		if(j<0) continue;
		tmp.did=j;
		switch(r_am[i].ngf->dsrc.dtype)
		{
		case 0: //�����
			tmp.subtype=1;
			break;
		case 1: //��·
			tmp.subtype=34;
			break;
		case 2: //ֱ����·
			tmp.subtype=35;
			break;
		case 3: //ĸ��
			tmp.subtype=33;
			break;
		case 4: //����
			tmp.subtype=3;
			break;
		}
		tmp.recno=r_am[i].recno;
		rrd.ReadStaData(tmp);
		r_am[i].zt=tmp.zt;
		r_am[i].enable=1;
		r_am[i].recno=tmp.recno;
	}
}

void ScadaWin::CreateAllrgn()  
{
	dbm.CreateFlwRgn(r_fw,fwsum); //������
	dbm.CreateResRgn(r_rs,rssum); //ˮ��
	if(dbm.lookdown==1)
	{
		switch(dbm.scf.showrev)          
		{
		case 1:case 2: 
			dbm.ComputePqZoom(r_rv,rvsum,wy);
			dbm.CreateRevRgn(r_rv,rvsum);
			break;
		case 3:
			dbm.ComputeTpzoom(r_tr,trsum,wy);
			dbm.CreateTranRevRgn(r_tr,trsum);
			break;
		case 4:
			dbm.ComputeTptzoom(r_tr,trsum,wy);
			dbm.CreateTranTRgn(r_tr,trsum);
			break;
		case 5: case 6:case 7:
			ComputeN1Zoom(r_n1,n1sum,dbm.n1zm,wy);
			dbm.CreateN1Rgn(r_n1,n1sum);
			break;
		case 8://����SOE
			dbm.CreateSwtRgn(r_sw,swsum);
			break;
		case 9://���ض�·����
			dbm.CreateSwtSccRgn(r_sw,swsum);
			break;
		case 10: //������ͼ
			dbm.ComputeZnZoom(r_pe,pesum,wy);
			dbm.CreateZnRgn(r_pe,pesum);
			break;
		case 11://ϵͳ��ͼ
			dbm.CreateSPieRgn(r_spe,spesum);
			break;
		case 12:
			ComputeN1Zoom(r_n1,n1sum,dbm.n1zm,wy);
			dbm.CreateN1EftRgn(r_n1,n1sum);
			break;

		}
		if(dbm.scf.lmd==1)  dbm.CreateSenRgn(r_sen,sesum);
	}
	CreatePaintRgn(); //���ɶ�̬ˢ������ֻ������ˢ��ʱ�򻷾��仯ʱ
}





BOOL ScadaWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		switch(cursor)
		{
		case 1:  SetCursor(cobj.hcur[0]);	return TRUE;
		case 2:  SetCursor(cobj.hcur[1]);	return TRUE;
		case 3:  SetCursor(cobj.hcur[2]);	return TRUE;
		case 4:  
		case 5:	 SetCursor(cobj.hcur[3]);	return TRUE;
		case 6:  case 9:
				 SetCursor(cobj.hcur[4]);	return TRUE;
		case 7:  SetCursor(cobj.hcur[7]);	return TRUE;
		case 8:  SetCursor(cobj.hcur[8]);	return TRUE;
		case 10: SetCursor(cobj.hcur[9]);	return TRUE;
		case 11: SetCursor(cobj.hcur[10]);	return TRUE;
		case 12: SetCursor(cobj.hcur[7]);	return TRUE;
		};
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void ScadaWin::OnTimer(UINT nIDEvent) 
{
	HDC hdc;
	if(!IsWindowVisible()) return;  //���ڲ��ɼ�ֱ�ӷ��أ���ʱ����Ч
	if(enabletimer==0) return;
	hdc=::GetDC(m_hWnd);
	switch(nIDEvent)
	{
	case 101:
		SetDynMeter();
		ShowDynObj(hdc); //����ʱ�Ķ�̬��ʾ
		break;
    case 102:
		Showdtime(hdc);
		CheckPopTips();  //��ʾ������
		break;
	case 103:			 //�Զ�ˢ������(5�붨ʱ��)
		if(dbm.hisplay==0&&dnbz==0&&dbm.curopzt!=5)
		{
			ResumeThread(hThread_rd);
		}
		break;
	case 104:  //��ʷ����
		if(dbm.hisplay==1&&dnbz==0) PlayHis(); //������ʷ����
		if(dbm.hisplay==2&&dnbz==0) PlaySoe(); //����SOE
		break;
	}
	::ReleaseDC(m_hWnd,hdc);
	CWnd::OnTimer(nIDEvent);
}

void ScadaWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SuspendThread(hThread_rd);
	if(twin.IsWindowVisible()) twin.ShowWindow(SW_HIDE);
	//////////////����ѹ��ǰ��״̬////////////////////
	dzoom=dbm.curzoom;			
	ddx=dx;
	ddy=dy;			
	dangle=dbm.curang;	
	dlk=dbm.lookdown;
	//////////////////////////////////////////////////
	
//	if(cursor!=0)
//	{
		enabletimer=0;
		dnbz=1;
		dbm.msdwn=1;
//	}
	MouseLBDown(point);
	//SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

//����������
void ScadaWin::MouseLBDown(CPoint point)
{
	int j,ks;
	pt1=point;
	pt2=point;
	oldpt=point;
	oldrt=CRect(0,0,0,0);
	oldang=dbm.curang;
	SetCapture();
	ks=GetKeyState(VK_LCONTROL);
	if(ks<0)
	{
		DrawShow();
		return;
	}
	//�Ȳ쿴�Ƿ��ڰ�ť��
	switch(cursor)
	{
	case 2: //�ֲ��Ŵ�
		DrawXorRect(CRect(pt1,pt2)); 
		break;
	case 6:  case 7: case 8: case 9: case 11:
		polysum=0;
		oldpt=point;
		AddPoint(point);
		break;
	case 1:case 3:
		DrawShow();
		break;
	default:
		j=IsInPush(point);
		if(j>=0){
			r_ph[j].psh->down=1;
			ShowPush(j);
		break;
		}
	}
}

void ScadaWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	enabletimer=1;
	dbm.msdwn=0;
	MouseLBUp(point);
	allupdate=0;
	t2=0;
	CWnd::OnLButtonUp(nFlags, point);
}

//�������ſ�
void ScadaWin::MouseLBUp(CPoint point)
{
	int j;
	CRect rt;
	ReleaseCapture();
	pt2=point;
	switch(cursor)
	{
	case 6: case 9://ͳ�ƶ��泱�����û��Զ������
		AddDmPt();
		break;
	case 7:case 8:
		ComputSen();
		break;
	case 10:
		Order3dPos(); //����λ��
		break;
	case 5: //�������ʱ
		j=IsInPush(point);
		if(j<0) break;
		r_ph[j].psh->down=0;
		ShowPush(j);
		RunPushCmd(j);
		break;
	case 2: //�ֲ��Ŵ�
		rt=CRect(pt1,pt2);
		rt.NormalizeRect();
		rt.OffsetRect(-dx,-dy);
		DrawXorRect(CRect(0,0,0,0));
		PartZoom(rt);
		break;
	case 12: //��·��������
		ComputScc();
		break;
	}  
	dnbz=0;
	if(NeedDrawDgx())  sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
	EndShow();
	CreateAllrgn();
	ResumeThread(hThread_rd);

}

void ScadaWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	int ks;
	cursor=GetCursor(point);
	MouseOnPush(nFlags,point);
	ks=GetKeyState(VK_LCONTROL);

	if(ks<0||cursor==1) MovePic(point);
	else MouseMove(point);
	CWnd::OnMouseMove(nFlags, point);
}

//���ֲ���
BOOL ScadaWin::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	/*double oldz;
	int mode;
	oldz=dbm.curzoom;
	mode=0;
	if(zDelta>0)  //�϶��Ŵ�
	{
		dbm.ZoomPage(1);
		mode=1;
	}else{//�϶���С
		dbm.ZoomPage(2);
		mode=2;
	}
	if(oldz!=dbm.curzoom){
		ZoomChange(); //�Ŵ��ļ���
		EndShow();
		CreateAllrgn();
	}
	SetStatusZoom();*/
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void ScadaWin::OnViewdev() 
{
	int type;
	char p[100];
	CViewDev dlg;
	dlg.rrd=&rrd;
	type=cobj.TypeTran(seltype,selsubtype);
	if(type==-1)
	{
		sprintf(p,"����=%s  ��ʶid=%d",selid,dsjlh);
		MessageBox(p,"�豸��Ϣ");
		return;
	}
	if(!dlg.SetParam(type,selid,dsjlh))
	{
		sprintf(p,"�豸:\n %s id:%d�����ݿ��в�����",selid,dsjlh);
		MessageBox(p,"����",MB_ICONSTOP);	
		return;
	}
	//��ʾ����
	dlg.DoModal();
}


void ScadaWin::OnCommandRange(UINT id)
{
	HWND hwnd;
	int  wparam;
	if(id<39300)
	{
		CloseLowfWin();
		cobj.GoToCMDPage(id);
		return;
	}
	if(id>=39300&&id<=39500)
	{
		if(dbm.GetChildSendMsg(id,wparam,hwnd))//�и�ID
		{ 
			::SendMessage(hwnd,WM_COMMAND,wparam,0);
 		}
	}
}

void ScadaWin::OnMainPage()
{
	CloseLowfWin();
	cobj.Mainpage(false);
}



void ScadaWin::CreatePaintRgn()
{
	HRGN hrgn,hrgn1=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	if(dbm.lookdown==0)
	{
		hrgn1=DY_GetActObjRgn(hrgn1,r_at,atsum,dx,dy,dbm.curzoom);
		hrgn1=DY_GetScrtxtRgn(hrgn1,r_sc,scsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetYBRgn(hrgn1,r_yb,ybsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetGifAmlRgn(hrgn1,r_am,amsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetGenRgn(msr,hrgn1,r_rv,rvsum,srt,dx,dy,dbm.scf.gendyn,dbm.curzoom);
	}
	//�ٿ�������
	if(dbm.curopzt==3) hrgn=GetLowUpdateRgn();
	else hrgn=GetFlowUpdateRgn();
	if(hrgn!=NULL) hrgn=GetLookDownRgn(hrgn);
	if(hrgn!=NULL) OffsetRgn(hrgn,dx,dy);
	if(hrgn==NULL&&hrgn1==NULL)
	{
		dbm.SignPaintObj(hrgn1,dx,dy);//�����Ҫˢ�µĶ���	
		return;
	}
	if(hrgn1==NULL) hrgn1=CreateRectRgn(0,0,1,1);
	CombineRgn(hrgn1,hrgn1,hrgn,RGN_OR);
	DeleteObject(hrgn);
	hrgn=CreateRectRgn(0,0,wx,wy);
	CombineRgn(hrgn1,hrgn1,hrgn,RGN_AND);
	DeleteObject(hrgn);
	updatergn=hrgn1;
	dbm.SignPaintObj(hrgn1,dx,dy);//�����Ҫˢ�µĶ���
}

//���ص�Ƶ����Ҫˢ�µ�����
HRGN ScadaWin::GetLowUpdateRgn()
{
	int i;
	CRect rt,rt3;
	N_FLOW *flw;
	HRGN hrgn=NULL;
	for(i=0;i<fwsum;i++)
	{
		flw=r_fw[i].flw;
		//if(r_fw[i].lfflag==0) continue;
		rt=r_fw[i].rt;
		rt3=srt;
		rt3.OffsetRect(-dx,-dy);
		rt&=rt3;
		if(!rt.IsRectEmpty())
		{
			if(hrgn==NULL)
			{
				hrgn=CreateRectRgn(0,0,1,1);
				CombineRgn(hrgn,r_fw[i].hrgn,hrgn,RGN_COPY);
			}else CombineRgn(hrgn,hrgn,r_fw[i].hrgn,RGN_OR);
		}
	}
	return hrgn;
}

HRGN ScadaWin::GetFlowUpdateRgn()
{
	int i;
	CRect rt,rt3;
	N_FLOW *flw;
	HRGN hrgn=NULL;
	for(i=0;i<fwsum;i++)
	{
		flw=r_fw[i].flw;
		rt=r_fw[i].rt;
		rt3=srt;
		rt3.OffsetRect(-dx,-dy);
		rt&=rt3;
		if(!rt.IsRectEmpty())
		{
			if(hrgn==NULL){
				hrgn=CreateRectRgn(0,0,1,1);
				CombineRgn(hrgn,r_fw[i].hrgn,hrgn,RGN_COPY);
			}
			else CombineRgn(hrgn,hrgn,r_fw[i].hrgn,RGN_OR);
		}
	}

	return hrgn;
}


HRGN ScadaWin::GetLookDownRgn(HRGN oldrgn)
{
	int i;
	HRGN hrgn=oldrgn;
	if(dbm.lookdown==0) return hrgn;
	if(dbm.scf.lmd!=1)
	{
		switch(dbm.scf.showrev)
		{
		case 1:case 2:
			for(i=0;i<rvsum;i++) if(r_rv[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_rv[i].hrgn,RGN_DIFF);
			break;
		case 3: case 4:
			for(i=0;i<trsum;i++) if(r_tr[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_tr[i].hrgn,RGN_DIFF);
			break;
		case 5: case 6:case 7: case 12:
			for(i=0;i<n1sum;i++) if(r_n1[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_n1[i].hrgn,RGN_DIFF);
			break;
		case 8: case 9:
			for(i=0;i<swsum;i++) if(r_sw[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_sw[i].hrgn,RGN_DIFF);
			break;
		case 10:
			for(i=0;i<pesum;i++) if(r_pe[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_pe[i].hrgn,RGN_DIFF);
			break;
		case 11:
			for(i=0;i<spesum;i++) if(r_spe[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_spe[i].hrgn,RGN_DIFF);
			break;
		}
	}
	if(dbm.scf.lmd==1)
	{
		for(i=0;i<sesum;i++) if(r_sen[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_sen[i].hrgn,RGN_DIFF);
	}
	return hrgn;
}



//����ƶ�
void ScadaWin::MouseMove(CPoint point)
{
	CPoint pt,ptt;
	CRect rt;
	if(dnbz==1){
     ptt=pt2;
	 pt2=point;
	 rt=CRect(pt1,pt2);
	 rt.NormalizeRect();
	 switch(cursor)
	 {
	 case 2: //�ֲ��Ŵ�
		DrawXorRect(rt);
		break;
	 case 3: //�϶��Ŵ�
		ZoomInOut();		
		break;
	 case 10://��ת
		Rotate();
		break;
	 case 6: case 7: case 8: case 9: case 11: case 12:
		AddPoint(point);
        DrawStatArea();
		break;
	   }
	}
}

void ScadaWin::MovePic(CPoint point)
{
	int x,y;
	int oldx,oldy,sx,sy;
	if(dnbz!=1||(xmax>0&&ymax>0)) return;
	oldx=dx;
	oldy=dy;
	if(xmax<0)
	{
		x=point.x-pt1.x;
		dx+=x;
		dx=dx>0 ? 0:dx;
		dx=dx<xmax ? xmax:dx;
	}
	if(ymax<0)
	{
		y=point.y-pt1.y;
		dy+=y;
		dy=dy>0 ? 0:dy;
		dy=dy<ymax ? ymax:dy;
	}
	sx=dx-oldx;
	sy=dy-oldy;
	if(sx!=0||sy!=0)	ScrollWindow(sx,sy,srt,srt);
	pt1=point;
	ComputZCenter();
	if(cobj.nwin!=NULL) cobj.nwin->MoveCvs();
};





///////////////�����Ӵ��ڷ�������Ϣ������Ӵ��ڵĶ���///////////////////
//message=1200  
//wParam=1   ���ص�ǰ������ģʽ��
//		 2   ȡ���ֵܿؼ��Ĵ��ھ��
//       3   �ҵ��ļ���ַ�����ظ����ó���
//		 4   ���ص�ǰʱ��
LRESULT ScadaWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char tnm[256];
	if(message==1200)
	{
		switch(wParam)
		{
		case 1:
			return 0;//��ǰ���з�ʽ��
		case 2:
			return (int)GetSlfCtl((int)lParam);
		case 3:
			cobj.SetToLocalFile((char *)lParam,tnm);
			strcpy((char*)lParam,tnm);
			return true;
		case 4:    //��������Ŀ¼
			strcpy((char*)lParam,cobj.startpath);
			return 0;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}


void ScadaWin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(dbm.curopzt==1) DmFlowSwitch();
	else RButtonMenu(point);
	CWnd::OnRButtonDown(nFlags, point);
}


//�����豸�����Ҽ��˵��Ĵ���
void ScadaWin::RButtonMenu(CPoint point)
{
	CMenu *mm;
	CPoint pt;
	pt=point;
	lfpos=pt;
	ClientToScreen(&pt);
	//���ȿ�N-1,N-2�Ҽ��˵�
	if(dbm.scf.showrev>=5&&dbm.scf.showrev<=7&&cursor==4)
	{
		mm=cobj.pmenu.GetSubMenu(1); //�������޸Ĳ˵�
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		return;
	}
	//�ٲ鿴�����ͼ�˵�
	if(seltype==13)
	{
		mm=cobj.pmenu.GetSubMenu(2); //�������޸Ĳ˵�
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		return;
	}
	//δѡ���豸��ĵ����˵�
	if(seltype==255)  //���������л��˵�
	{
		switch(winmode)
		{
		case 0:
			cobj.rmenu.TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
			return;
		case 1:
			mm=cobj.fmenu.GetSubMenu(0); //�������޸Ĳ˵�
			if(dbm.page.head.type>0&&n_ge>0) mm->EnableMenuItem(IDC_GENREV,0);
			else mm->EnableMenuItem(IDC_GENREV,1);
			if(dbm.page.head.type>0&&(n_ge>0||n_sh>0)) mm->EnableMenuItem(IDC_GENREVQ,0);
			else mm->EnableMenuItem(IDC_GENREVQ,1);
			if(dbm.page.head.type>0&&n_tr>0) mm->EnableMenuItem(IDC_BYQWD,0);
			else mm->EnableMenuItem(IDC_BYQWD,1);
			if(dbm.page.head.type>0&&n_tr>0) mm->EnableMenuItem(IDC_TRANREV,0);
			else mm->EnableMenuItem(IDC_TRANREV,1);
			
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_ROTATE,0);
			else mm->EnableMenuItem(ID_ROTATE,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_ZOOMIO,0);
			else mm->EnableMenuItem(ID_ZOOMIO,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_MOVEPIC,0);
			else mm->EnableMenuItem(ID_MOVEPIC,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(IDC_SHOWDGX,0);
			else mm->EnableMenuItem(IDC_SHOWDGX,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(IDC_BASFLOW,0);
			else mm->EnableMenuItem(IDC_BASFLOW,1);

			if(mm!=NULL) mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,cobj.mwin);
			return;
		}
	}
	mm=cobj.pmenu.GetSubMenu(0); //�������޸Ĳ˵�
	cursor=255;
	if(mm!=NULL)
	{
		if(SelIsTran()) mm->EnableMenuItem(IDC_AVCOPT,0);
		else mm->EnableMenuItem(IDC_AVCOPT,1);
		if(SelIsGen()) mm->EnableMenuItem(IDC_PQVOPT,0);
		else mm->EnableMenuItem(IDC_PQVOPT,1);
		if(SelIsTran()) mm->EnableMenuItem(IDC_SVOPT,0);
		else mm->EnableMenuItem(IDC_SVOPT,1);
		if(SelCanZoomLowF()) mm->EnableMenuItem(IDC_LOWZOOM,0);
		else mm->EnableMenuItem(IDC_LOWZOOM,1);
		if(seltype==6&&selsubtype==0) mm->EnableMenuItem(IDC_RESVJS,0);
		else mm->EnableMenuItem(IDC_RESVJS,1);
		if(seltype==2) mm->EnableMenuItem(ID_INPUTPARAM,0);
		else mm->EnableMenuItem(ID_INPUTPARAM,1);
		if(seltype==2) mm->EnableMenuItem(IDC_VIEWDEV,0);
		else mm->EnableMenuItem(IDC_VIEWDEV,1);
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	}
}


bool ScadaWin::UpdateDmData()
{
	int i,j;
	bool rtn=false;
	double I,v,pcur,ps,p,q;
	READDEV  ran;
	if(dbm.curopzt!=1) return false;
	//��ȡ���泱��
	for(j=0;j<dmsum;j++)
	{
		I=0;
		pcur=0;
		for(i=0;i<dms[j].lsum;i++)
		{
			ran.recno=dms[j].ls[i].jlh;
			ran.did=dms[j].ls[i].id;
			ran.dtype=dms[j].ls[i].type+1; //������ֱ��
			if(rrd.ReadDevData(ran))
			{
				v=ran.value[7];
				I+=v;
				p=ran.value[0];
				q=ran.value[1];
				ps=sqrt(p*p+q*q);//���ڹ���
				pcur+=ps;
			}
		}
		if(dms[j].Icur!=I)
		{
			dms[j].Icur=(float)I;
			rtn=true;
		}
		if(dms[j].Pcur!=pcur)
		{
			dms[j].Pcur=(float)pcur;
			rtn=true;
		}
	}

	return rtn;
}



//�Ƿ���Ҫ�л�����Ƶ�𵴻���
void ScadaWin::TurnToLowF()
{
	int i;
	if(dbm.curopzt==3) return; //�Ѿ����ڵ�Ƶ��
	//�л�����Ƶ��״̬
	cobj.SetToNeedMode(6);
	//�л�����Ƶ�𵴻���
	i=cobj.mwin->GetVWIndex(cobj.swin);
	if(i>=0) cobj.mwin->GoToPage(i);
}



//��Ƶ�𵴷Ŵ�
void ScadaWin::OnLowzoom() 
{
	int x,y;
	CRect rt;
	lwin.vpt=r_fw[seljlh].flw->fpt;
	lwin.vlen=r_fw[seljlh].flw->flen;
	lwin.sval=0;
	lwin.sfr=0;
	lwin.curtype=r_fw[seljlh].flw->type;
	lwin.curid=r_fw[seljlh].flw->did;
	strcpy(lwin.name,r_fw[seljlh].flw->dev_name);
	rt=CRect(lfpos.x,lfpos.y,lfpos.x+254,lfpos.y+144);
	x=wx-rt.right;
	y=wy-rt.bottom;
	x=x>0 ? 0:x;
	y=y>0 ? 0:y;
	rt.OffsetRect(x,y);
	lwin.SetFunct(2);
	lwin.MoveWindow(&rt);
}





void (WINAPI *TurnReservoir)(int id);

//ˮ�緢�����
void ScadaWin::OnResvjs()
{
	HINSTANCE hinst;
	char name[256];
	cobj.SetToLocalFile("turnresv.dll",name);
	hinst=LoadLibrary(name);
	if(hinst==NULL)
	{
		MessageBox("turnresv.dll�����ڣ����ܼ��㣡");
		return;
	}
	(FARPROC&)TurnReservoir=GetProcAddress(hinst,"TurnReservoir");
	if(TurnReservoir!=NULL) TurnReservoir(dsjlh);
	FreeLibrary(hinst);
}


void ScadaWin::SetDgxParam()
{
	sct.SetCfg(dbm.scf.smooth,dbm.scf.oneline,dbm.scf.tranbg,dbm.scf.ctrtype,dbm.scf.cr);
}

void ScadaWin::FlowSel(int sel)
{
	if(dbm.scf.ftype!=sel)
	{
		dbm.scf.ftype=sel;
		dbm.SaveShowSet();
	}
	EndShow();
}





//ע�������豸��ʷ�ط�
void ScadaWin::RegistHisAllDev()
{
	His_RegistFlow(r_fw,fwsum);
	His_RegistBus(r_bs,bssum);
	His_RegistDev(r_st,stsum);
}
//������ʷ
void ScadaWin::PlayHis()
{
	dbm.hisjs++;
	if(dbm.hisjs>dbm.hspeed)
	{
		if(dbm.curtm>=dbm.hsum)
		{
			dbm.hisplay=0;
			return;
		}
		dbm.hisjs=0;
	}
	ResumeThread(hThread_rd);
}

//������ʷSOE
void ScadaWin::PlaySoe()
{
	dbm.curtm++;
	if(dbm.curtm>=dbm.soesum)
	{
		dbm.hisplay=0;
		return;
	}
	//����һ��ֵ
	SetANewSoe(dbm.soe[dbm.curtm]);
	//��ʾ
	cobj.ebar->SetNewDate(dbm.soe[dbm.curtm].tm,dbm.soe[dbm.curtm].ms);
	Order3dPos();
	CreateAllrgn();
	EndShow();

}

//��ȡ��ʷ����
void ScadaWin::ReadHisData()
{
	time_t tm1,tm2;
	if(dbm.curtm<=dbm.hsum)
	{
		tm1=dbm.hlist[dbm.curtm];
		GetNextSection(tm1,tm2);
		SetCurHisDTime();
		dbm.curtm++;
	}
}

void ScadaWin::SetCurHisDTime()
{
	CTime tm;
	time_t tm1;
	if(dbm.curtm>=dbm.hsum) return;
	tm1=dbm.hlist[dbm.curtm];
	tm=CTime(tm1);
	cobj.hbar->SetDate(tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
}

void ScadaWin::RegistHis()
{
	//���ԭע��
	ClearAllRegData();
	//ע�᱾ҳ��
	RegistHisAllDev();
	BeginGettingData();
}

void ScadaWin::OnDestroy() 
{
	enabletimer=0;
	TerminateThread(hThread_rd,0);
	CloseHandle(hThread_rd);
	//���ö�ʱ��
	KillTimer(101);	 //�����͹����ı���ʱ
	KillTimer(102);	 //ʱ����ʾ
	KillTimer(103);  //������ʾ
	KillTimer(104);		
	FreeMem();		 //�ͷ��ڴ�
	////////////////////////
	if(pb!=NULL) delete pb;
	pb=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	CWnd::OnDestroy();
}

//��һ���ļ�
bool ScadaWin::FileOpen(char *filename,int pageno,HISHMI *hmi,int mode) 
{
	CloseLowfWin();
	allupdate=0;
	FreeMem();
	if(!dbm.OpenPwFile(filename,pageno))
	{
		MessageBox("�ļ������ڻ���˲�ʶ��İ汾��\n���ø�ʽת������ת����\n���ļ�ʧ��");
		return false;
	}
	InitMoveObj(hmi,mode);

	EndShow();
	CreateAllrgn();
	return true;
}

//�쿴ѡ����豸�Ƿ��Ǳ�ѹ��,�����
bool ScadaWin::SelIsTran()
{
	if(seltype!=2) return false;
	if(selsubtype!=7&&selsubtype!=8) return false;
	if(seljlh<0) return false;
	return true;
}

//�쿴ѡ����豸�Ƿ��Ǳ�ѹ��,�����
bool ScadaWin::SelIsGen()
{
	if(seltype!=2) return false;
	if(selsubtype!=1) return false;
	if(seljlh<0) return false;
	return true;
}

//��ѹ��AVC����
void ScadaWin::OnAvcopt() 
{
	int type,id;
	if(!SelIsTran()) return;
	type=selsubtype-6;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	//ShowAVCPQVWnd(id,type,TRUE);//ZQ 2009.12.20 delete temp
}

//�����PQV���߼���
void ScadaWin::OnPqvopt() 
{
	int type,id;
	if(!SelIsGen()) return;
	type=3;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	//ShowAVCPQVWnd(id,type,TRUE);//ZQ 2009.12.20 delete temp
}

void ScadaWin::SetCurFunction(FUN_STATUS newfun)
{
	m_PreFun=m_CurFun;	
	m_CurFun=newfun;
	cobj.funbar->ReDrawNewFt();
}

void ScadaWin::OnN12eft() 
{
	if(seljlh<0||seljlh>=n1sum) return;
	NT_ShowEffect(r_n1[seljlh].devid,r_n1[seljlh].type,dbm.dbzt==0 ? "visualpw":"studypw");
}

void ScadaWin::OnN12eft3d() 
{
	cobj.N12eft3d();
}

void ScadaWin::ReadN1EFT()
{
	int num,i,j;
	float v1,v2;
	N1Data data[100],td;

	int type=0;
	DWORD id=0;
	float fSec=0.0;
	char buff[32]={0};
	if(!GetN1Sel(id,type,fSec)) return;

	//���ԭ����
	SetN1EftData(data,0);
	if(!rrd.Readn1Eft((DWORD)id,type,num,data,100)) return;
	data[0].val=fSec;//��һ����ѡ�е��豸���ָ�ԭֵ
	for(i=0;i<num;i++)
	{
		v1=data[i].val;
		v1=v1<0 ? -v1:v1;
		for(j=i+1;j<num;j++)
		{
			v2=data[j].val;
			v2=v2<0 ? -v2:v2;
			if(v1>v2)
			{
				td=data[i];
				data[i]=data[j];
				data[j]=td;
				v1=v2;
			}
		}
	}

	//��������
	SetN1EftData(data,num);
}

bool ScadaWin::GetN1Sel(DWORD &dwID,int &type,float &fSec)
{
	if(seljlh<0||seljlh>=n1sum) return false;

	dwID=r_n1[seljlh].devid;
	type=r_n1[seljlh].type;
	fSec=r_n1[seljlh].vn1;
	return true;
}

void ScadaWin::SetN1EftData(N1Data *data,int num)
{
	int i,j,k,t;
	double a;
	for(j=0;j<n1sum;j++)
	{
		r_n1[j].vn1=0;//����0
		r_n1[j].index=0;
		r_n1[j].selbz=0;
	}
	if(num==0) return;
	a=100/num;
	for(i=0;i<num;i++)
	{
		k=data[i].id;
		t=data[i].type;
		for(j=0;j<n1sum;j++)
		{
			if(k==r_n1[j].devid&&t==r_n1[j].type)
			{
				r_n1[j].vn1=data[i].val;
				r_n1[j].index=i+1;
				if(data[i].Group==1) r_n1[j].selbz=1;
				else r_n1[j].selbz=0;
				switch(t)//�����//����//����//�������//�������//ĸ��//��·
				{
				case 0://�����
					r_n1[j].color=dbm.scf.sencolor[0];
					break;
				case 1://˫������
					r_n1[j].color=dbm.scf.sencolor[3];
					break;
				case 2://���Ʊ�
					r_n1[j].color=dbm.scf.sencolor[4];
					break;
				case 3://��·
					r_n1[j].color=dbm.scf.sencolor[6];
					break;
				case 4://����
					r_n1[j].color=dbm.scf.sencolor[1];
					break;
				case 5://����
					r_n1[j].color=dbm.scf.sencolor[2];
					break;
				case 6://ĸ��
					r_n1[j].color=dbm.scf.sencolor[5];
					break;
				}
				r_n1[j].Hbar=100+(int)(a*i);
				break;
			}
		}
	}
}

void ScadaWin::OnGenmsg() 
{
	int zid;
	//ȡ����ID
	if(seljlh<0||seljlh>=pesum) return;
	zid=r_pe[seljlh].pie->did;
	
	NT_Gen(zid);
}

void ScadaWin::OnTranmsg() 
{
	int zid;
	//ȡ����ID
	if(seljlh<0||seljlh>=pesum) return;
	zid=r_pe[seljlh].pie->did;
	NT_Tfm(zid);
}

void ScadaWin::OnSvopt() 
{
	int type,id;
	if(!SelIsTran()) return;
	type=selsubtype-7;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	ShowDynTrans(id,type,TRUE);
}
