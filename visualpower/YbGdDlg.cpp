// YbGdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "YbGdDlg.h"
#include "comobj.h"
#include "DObj.h"
#include "bclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// YbGdDlg dialog


YbGdDlg::YbGdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(YbGdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(YbGdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	r_sf=NULL;
	r_ph=NULL;
	r_yb=NULL;
	r_fsh=NULL;
	

	sfsum=0;
	phsum=0;
	ybsum=0;
	fssum=0;

	allupdate=0;
	t1=0;
	t2=0;
	mbg.Create(1,1);
	msr.Create(1,1);
	dbm.msr=&msr;
	updatergn=NULL;
}

YbGdDlg::~YbGdDlg()
{
	KillTimer(101);
	KillTimer(103);
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	FreeMem(); //�ͷ��ڴ�

}

void YbGdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(YbGdDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(YbGdDlg, CDialog)
	//{{AFX_MSG_MAP(YbGdDlg)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// YbGdDlg message handlers

BOOL YbGdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(101,500,NULL);	  //�����͹����ı���ʱ
	SetTimer(103,5000,NULL);  //�Զ�ˢ������
	return TRUE;  
}

void YbGdDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	if(cx>10&&cy>10) //��ʼ����ʱ����10*10�Ĵ��ڴ�С���������º���
	{	
		mbg.SizeChange(cx,cy);
		msr.SizeChange(cx,cy);
		ShowA(mbg);
		CreateAllrgn();
	}
}

void YbGdDlg::OnPaint() 
{
	CRect rt;
	CPaintDC dc(this);
	rt=srt;
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBlt(dc.m_hDC,rt);

}

void YbGdDlg::OnTimer(UINT nIDEvent) 
{
	HDC hdc;
	if(!IsWindowVisible()) return;
	hdc=::GetDC(m_hWnd);
	switch(nIDEvent)
	{
	case 101:
		if(SetDynMeter()) ShowDynObj(hdc);
		break;
	case 103:
		UpdateAllData();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

//��һ���ļ�
void YbGdDlg::OPenFile(char *filename,int picno)
{
	char fnm[256];
	cobj.SetToLocalFile(filename,fnm);
	if(dbm.CheckFileIndex(fnm,picno))
	{
		FreeMem(); //�ͷ��ڴ�
		dbm.OpenPwFile(fnm,picno);
		InitMoveObj();
		return;
	}
}


//�ͷ���Դ
void YbGdDlg::FreeMem() //�ͷ��ڴ�
{
	int i;

	if(phsum!=0) delete []r_ph;
	if(ybsum!=0) delete []r_yb;
	
	r_ph=NULL;
	r_yb=NULL;	
	
	phsum=0;
	ybsum=0;
	

	//�ͷ������ؼ�
	for(i=0;i<sfsum;i++){
		
	   if(r_sf[i].stl->hwnd!=NULL&&r_sf[i].stl->hinst!=NULL&&
		   r_sf[i].stl->DfClose!=NULL)
	   {
			 ::SendMessage(r_sf[i].stl->hwnd,WM_CLOSE,0,0);
			 r_sf[i].stl->DfClose(r_sf[i].stl->rc);
			 r_sf[i].stl->hwnd=0;
			 r_sf[i].stl->rc=0;
		 }
	   if(r_sf[i].stl->hinst!=NULL){
		    if(r_sf[i].stl->hmenu!=NULL) DestroyMenu(r_sf[i].stl->hmenu);
 			FreeLibrary(r_sf[i].stl->hinst);
			r_sf[i].stl->hinst=0;
			r_sf[i].stl->hmenu=NULL;
	   }
	};

	if(sfsum!=0) delete []r_sf;
	r_sf=NULL;
	sfsum=0;

	//�ͷ�flash�ؼ�
	for(i=0;i<fssum;i++)	r_fsh[i].fshw.DestroyWindow();
	if(fssum>0) delete []r_fsh;
	r_fsh=NULL;
	fssum=0;
}

void YbGdDlg::InitMoveObj()
{
	int   objsum[100];			
	dbm.TJObjSum(objsum);

	//������Ҫ����Ļ����
	ybsum=objsum[67];				//�Ǳ�
	if(ybsum>0) r_yb=new RMETER[ybsum];
	phsum=objsum[75];
	if(phsum>0) r_ph=new RPUSH[phsum];	//��ť
	sfsum=objsum[76];
	if(sfsum>0) r_sf=new RSELFCTL[sfsum];//�����ؼ�
	fssum=objsum[81];
	if(fssum>0) r_fsh=new RFLASH[fssum];//FLASH����
	dbm.page.head.type=0;
	
	//����̬�����ӹ���
	GetObjFromDbm();
	
	dbm.lookdown=0;
	dbm.curang=0;
	dbm.scf.showrev=0;
	SetFirstPosition();
	Set3DEnv();//����3D����
	///////////////////////
	
	UpdateAllData();
	EndShow();
}


bool YbGdDlg::UpdateAllData()
{
	bool b=false;
	if(!cobj.dbok) return false;
	if(t2==1) return false;
	t2=1;
	b=UpDateMeter();
	//���ݱ仯��Ĵ���
	if(b==true)
	{
		allupdate=1;
	}
	t2=0;
	return  b;
}


//�ӿ�����ȡ����
void YbGdDlg::GetObjFromDbm()
{
	CRect rt;
	char fnm[256];
	N_layer *clay;
	R_FLW rfw;
	int i,j, csft,cpsh,cyb,cfsh;
	csft=0;	cpsh=0;	cyb=0;  cfsh=0;
	rfw.ele=1;
	//���������ؼ��˵�Ϊ0/////////////////////////
	dbm.cmsum=0;					//��ǰӦ������
	dbm.popsum=0;					//�����˵�����
	//////////////////////////////////////////////
	for(i=0;i<dbm.page.laysum;i++)
	{
	  clay=&dbm.page.layer[i];
	  for(j=0;j<clay->objnum;j++)
	  {
		switch(clay->obj[j].attr.type)
		{
		case 67:
			r_yb[cyb].bs=&clay->obj[j];
			r_yb[cyb].mtr=(N_ELEGRPYB *)r_yb[cyb].bs->buf;
			r_yb[cyb].rt=r_yb[cyb].bs->ort;
			memset(r_yb[cyb].recno,0,4*6);
			cyb++;
			break;
		case 75:
			r_ph[cpsh].bs=&clay->obj[j];
			r_ph[cpsh].rt=clay->obj[j].ort;
			r_ph[cpsh].psh=(N_PUSH*)clay->obj[j].buf;
			cpsh++;
			break;
        case 76:
			r_sf[csft].bs=&clay->obj[j];
			r_sf[csft].rt=clay->obj[j].ort;
			r_sf[csft].rt.GetRECT(rt);
			r_sf[csft].sid=clay->obj[j].attr.ID;
			r_sf[csft].cansize=1;
			r_sf[csft].stl=(N_SELFCTL*)clay->obj[j].buf;
			//����ģ��
			r_sf[csft].bs->InitSelfCtl();
			if(r_sf[csft].stl->hinst!=NULL&&r_sf[csft].stl->DfInit!=NULL){ 
				r_sf[csft].stl->rc=r_sf[csft].stl->DfInit(m_hWnd,r_sf[csft].stl->hwnd,
					rt,r_sf[csft].stl->id,r_sf[csft].stl->style,r_sf[csft].stl->lkbuf);
				}
				else r_sf[csft].stl->hwnd=NULL;
			GetSflRunParam(r_sf[csft].swp,r_sf[csft]);
			//׼���˵�			
			if(r_sf[csft].stl->hmenu!=NULL)
				dbm.SetChildMenu(r_sf[csft].stl->hwnd,r_sf[csft].stl->hmenu);
			/////////////////////
			csft++;
			break;
		case 81:
			clay->obj[j].ort.GetRECT(r_fsh[cfsh].rt);
			r_fsh[cfsh].fsh=(N_FLASH*)clay->obj[j].buf;
			r_fsh[cfsh].fshw.Create("",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,130+cfsh);
			cobj.SetToLocalFile(r_fsh[cfsh].fsh->fname,fnm);//�ҵ��ļ�
			r_fsh[cfsh].fshw.SetMovie(fnm);
			if(r_fsh[cfsh].fsh->playmode==1) r_fsh[cfsh].fshw.SetLoop(TRUE);
			cfsh++;
			break;
		 };
	   }
	};
}

//������һ�ε�λ��
void YbGdDlg::SetFirstPosition()
{
	dbm.scf.lmd=0;
	dbm.lookdown=0;
	dbm.curang=0;
	dbm.scf.showrev=0;
	dbm.curzoom=1;
	dbm.zw=dbm.page.head.width;
	dbm.zh=dbm.page.head.height;
	//���������ؼ��Ĵ��ڴ�С
	ChangeAllSft();
}

//����3D��������
void YbGdDlg::Set3DEnv()
{
	msr.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//����3D����
	mbg.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//����3D����
}

//��������ʱ����ʾ
void YbGdDlg::EndShow()
{
	CRect rt;
	HDC hdc=::GetDC(m_hWnd);
	rt=srt;
	//��������ʾ��������
	ShowA(mbg);
	//����ʾ3D����
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBlt(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}

//ˢ���Ǳ�
bool YbGdDlg::UpDateMeter()
{
	bool rtn=false;
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
			rtn|=SetYbVal(r_yb[i].mtr[0],tmp,k);
		}
  	}
	return rtn;
}

void YbGdDlg::ChangeAllSft()
{
	int i;
	CRect rt;
	for(i=0;i<sfsum;i++){
	  if(r_sf[i].cansize==1)  ChangeCtlSize(srt,r_sf[i].swp);
	};
	//����FLASHλ��
	for(i=0;i<fssum;i++){
		rt=r_fsh[i].rt;
		if(r_fsh[i].fsh->align_left==1) rt.left=0;
		if(r_fsh[i].fsh->align_top==1)  rt.top=0;
		if(r_fsh[i].fsh->align_right==1) rt.right=wx;
		if(r_fsh[i].fsh->align_buttom==1) rt.bottom=wy;
		r_fsh[i].fshw.MoveWindow(rt);
	}
}

//����ͼ����ʾ�������ϣ��Ա�������ʾ
void YbGdDlg::ShowA(CDIB&mdc)
{
	CRect rt;
	rt=srt;
	dbm.ShowBkgd(mdc,rt);
	dbm.ShowBgDbx(mdc,0,0,srt,0);
	dbm.ShowStatic(mdc,0,0,srt);
}


//�����Ըı䴰�ڵľ���
void YbGdDlg::ChangeCtlSize(CRect rtd,SUBW_PARAM&pas)
{
	int cdx,cdy,cx,cy;
	CRect rt;
	CDRect art;
	art=pas.rts;
	art.ActRtToScr(dbm.curzoom);
	art.GetRECT(rt);
	cdx=rtd.left;
	cdy=rtd.top;
	cx=rtd.Width();
	cy=rtd.Height();
	if(pas.left==1)		rt.left=0;
	if(pas.top==1)		rt.top=0;
	if(pas.right==1)	rt.right=cx;
	if(pas.bottom==1)	rt.bottom=cy;
	pas.rtw=rt;
	pas.rt=rt;
	if(pas.hwnd!=NULL) ::MoveWindow(pas.hwnd,(int)pas.rtw.left,(int)pas.rtw.top,
		 (int)pas.rtw.Width(),(int)pas.rtw.Height(),true);
}

//�����Ǳ�ֵ
bool YbGdDlg::SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j)
{
	bool rtn=false;
	if(j>7||j<0) return rtn;
	if(yb.umr[j].ptype==1) //ʹ�ö�ȡ�Ĳ���
	{
		yb.umr[j].vmax=data.vmax;
		yb.umr[j].vmin=data.vmin;
		yb.umr[j].val[0]=data.vmin1;
		yb.umr[j].val[1]=data.vmax1;
		yb.umr[j].val[2]=data.vmin2;
		yb.umr[j].val[3]=data.vmax2;
	}
	if(yb.newval[j]!=data.curval)
	{
		yb.newval[j]=data.curval;
		rtn=true;
	}
	return rtn;
}

void YbGdDlg::PaintShow(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	msr.BitBltRect(hdc,rt2,rt);
}

//���ö�̬�Ǳ�
bool YbGdDlg::SetDynMeter()
{
	bool rtn=false;
	int i,k,bz;
	float v1,v2,v3;
	for(i=0;i<ybsum;i++)
	{
		bz=0;
		for(k=0;k<r_yb[i].mtr->dbsum;k++)
		{
			v1=r_yb[i].mtr->newval[k];
			v2=r_yb[i].mtr->curval[k];
			if(v1==v2) continue;
			v3=v2-v1;
			v3=v3>0 ? v3:-v3;
			if(v3<0.01)
			{
				r_yb[i].mtr->curval[k]=r_yb[i].mtr->newval[k];
				
			}else{
				r_yb[i].mtr->curval[k]=(float)((r_yb[i].mtr->newval[k]+r_yb[i].mtr->curval[k])/2);
			}
			bz=1;
			rtn=true;
		}
		if(bz==1) r_yb[i].mtr->show=1;
  	}
	return rtn;
}

void YbGdDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int j;
	SetCapture();
	j=IsInPush(point);
	if(j>=0){
		r_ph[j].psh->down=1;
		ShowPush(j);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void YbGdDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int j;
	ReleaseCapture();
	j=IsInPush(point);
	if(j>=0)
	{
		r_ph[j].psh->down=0;
		ShowPush(j);
		RunPushCmd(j);
	}
	CDialog::OnLButtonUp(nFlags, point);
}


//�鿴�����Ƿ��ڰ�ť��
int YbGdDlg::IsInPush(CPoint point)
{
	int i;
	CDPoint apt;
	apt.SetPOINT(point);
	apt.ScrPtToAct(1);
	for(i=0;i<phsum;i++)
	{
	  if(r_ph[i].rt.PtInRect(apt)) return i;
	}
	return -1;
}

//��ʾ��ť
void YbGdDlg::ShowPush(int j)
{
	CRect rt;
	CDRect art;
	if(j<0||j>=phsum) return;
	CClientDC dc(this);
	r_ph[j].bs->ShowPush(dc.m_hDC,0,0);
}


//���а�ť����
void YbGdDlg::RunPushCmd(int j)
{
	HWND hw;
	switch(r_ph[j].psh->cmdtype)
	{
	case 0: WinExec(r_ph[j].psh->command,SW_SHOW); break;
	case 1: //�򿪻���
		break;
	case 2: //����CMD��Ϣ
		GetParent()->PostMessage(WM_COMMAND,r_ph[j].psh->cmdnum);
		break;
	case 3: 
		hw=GetSlfCtl(r_ph[j].psh->selfid);
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,r_ph[j].psh->cmdnum,0);
		break;
	case 4: //�˳�����
		break;
	case 5: //ִ�й���ģ��
		RunFunctModule(r_ph[j].psh->command);
		break;
	}
}

//���������ؼ��Ĵ���
HWND YbGdDlg::GetSlfCtl(int id)
{
	int i;
	for(i=0;i<sfsum;i++)
	{
		if(id==r_sf[i].stl->id)
		{
			return r_sf[i].stl->hwnd;
		}
	};
	return NULL;
}


void YbGdDlg::CreateAllrgn()  
{
	Set3DEnv();//����3D����
	CreatePaintRgn(); //���ɶ�̬ˢ������ֻ������ˢ��ʱ�򻷾��仯ʱ
}

void YbGdDlg::CreatePaintRgn()
{
	HRGN hrgn1=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	hrgn1=DY_GetYBRgn(hrgn1,r_yb,ybsum,srt,0,0,1);
	updatergn=hrgn1;
	dbm.SignPaintObj(hrgn1,0,0);//�����Ҫˢ�µĶ���
}

//int k1=0;

//��ʾ��̬����
void YbGdDlg::ShowDynObj(HDC hdc)
{

	if(t1==1) return;
	if(allupdate==1) //����ȫ����
	{
		ShowA(mbg);
		ShowC(hdc,srt);
		allupdate=0;
		return;
	}
	t1=1;
//	char p[100];
//	CClientDC dc(0);
	//HBRUSH hb=CreateSolidBrush(0xff);
	//ˢ�¿ͻ���
	if(updatergn!=NULL)
	{
		SaveDC(hdc);
		//FillRgn(hdc,updatergn,hb);
		SelectObject(hdc,updatergn);
		ShowC(hdc,updatergn);
		RestoreDC(hdc,-1);
		//sprintf(p,"k1=%d ",k1);
		//dc.TextOut(100,10,p);
		//k1++;
	}
	t1=0;
	//DeleteObject(hb);
}

void YbGdDlg::ShowC(HDC hdc,HRGN hrgn)
{
	int w,h;
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
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

void YbGdDlg::ShowC(HDC hdc,CRect rtshow)
{
	int w,h;
	CRect rt,rt2;
	rt=rtshow;
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

//���������仯֪ͨ�����ؼ�
void YbGdDlg::AreaChange()
{
	int i,wparam;
	HWND hw;
	wparam=2072;
	for(i=0;i<sfsum;i++)
	{
		hw=r_sf[i].stl->hwnd;
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,wparam,0);
	};
}