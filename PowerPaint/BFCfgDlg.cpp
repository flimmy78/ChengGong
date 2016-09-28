// BFCfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "BFCfgDlg.h"
#include "base0.h"
#include "comobj.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;

BOOL GetPw0ile(char *filename,char *path,int &pageno,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// BFCfgDlg dialog


BFCfgDlg::BFCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BFCfgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BFCfgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	gbus=NULL; //ͼ���е�BUSδ����
	fbus=NULL; //�ѹ���
	fsum=0;
	gsum=0;
}

BFCfgDlg::~BFCfgDlg()
{
	if(gbus!=NULL) delete []gbus;
	if(fbus!=NULL) delete []fbus; 
}


void BFCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BFCfgDlg)
	DDX_Control(pDX, IDC_PAGENO, m_pno);
	DDX_Control(pDX, IDC_RALATED, m_rf);
	DDX_Control(pDX, IDC_BUS, m_bus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BFCfgDlg, CDialog)
	//{{AFX_MSG_MAP(BFCfgDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_OPENPWF, OnOpenpwf)
	ON_CBN_SELCHANGE(IDC_PAGENO, OnSelchangePageno)
	ON_BN_CLICKED(IDC_CLEARRA, OnClearra)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BFCfgDlg message handlers

BOOL BFCfgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetBus();
	ReadCfg();
	//��ʾ��ͷ
	m_rf.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_MULTIWORKAREAS);
	m_rf.InsertColumn(0,"ĸ������",LVCFMT_LEFT,120,0);
	m_rf.InsertColumn(1,"ID",LVCFMT_LEFT,60,0);
	m_rf.InsertColumn(2,"ͼ���ļ�",LVCFMT_LEFT,140,0);
	m_rf.InsertColumn(3,"ҳ��",LVCFMT_LEFT,50,0);
	AddToListCtl(); //�����б���
	return TRUE; 
}

void BFCfgDlg::OnSelchangePageno() 
{
	int n;
	n=m_pno.GetCurSel();
	SetDlgItemInt(IDC_INDEX,n);
}

 
//ȡ�����е�ĸ��
void BFCfgDlg::GetBus()
{
	int i,j,n;
	GBUS newbus;
	BASE0   *obj;
	N_BUS   *bus;
	for(i=0;i<cpage->laysum;i++){
		n=cpage->layer[i].objnum;
		obj=cpage->layer[i].obj;
		for(j=0;j<n;j++){
			if(obj[j].attr.type!=79) continue;
			bus=(N_BUS*)obj[j].buf;
			if(bus->did<0) continue;
			strcpy(newbus.name,bus->dev_name);
			newbus.id=bus->did;
			if(!IsInGBus(newbus.id)) AddABus(newbus);
		}
	}
	AddToGBusList();
}


//����һ��ĸ��
bool BFCfgDlg::AddABus(GBUS &newbus)
{
	int n;
	n=gsum;
	if(n==0)   gbus=new GBUS;
	else  gbus=(GBUS*)realloc(gbus,sizeof(GBUS)*(n+1));
	if(gbus==NULL){
		gsum=0;
		return false;
	}
	gbus[n]=newbus;
	gsum++;
	return true;
}
//����ͼ��ĸ���б��
void BFCfgDlg::AddToGBusList()
{
	int i;
	char p[100];
	m_bus.ResetContent();
	for(i=0;i<gsum;i++){
		sprintf(p,"%s:%d",gbus[i].name,gbus[i].id);
		m_bus.AddString(p);
	}
	m_bus.SetCurSel(0);
}

void BFCfgDlg::ReadCfg()
{
	char name[256];
	int i;
	BFHEAD head;
	BUSFILE bfile;
	FILE *fp;
	strcpy(name,cobj.path[1].path);
	strcat(name,"\\bsralate.cfg");
	fp=fopen(name,"r+b");
	if(fp==NULL) return;
	fread(&head,sizeof(BFHEAD),1,fp);
	if(head.flag!=0xd0||head.version!=0x10)
	{
		fclose(fp);
		return;
	}
	for(i=0;i<head.sum;i++){
		if(feof(fp)) break;
		fread(&bfile,sizeof(BUSFILE),1,fp);
		AddFBus(bfile);
	}
	fclose(fp);
}

bool BFCfgDlg::AddFBus(BUSFILE &nbfile)
{
	int n;
	n=fsum;
	if(n==0)   fbus=new BUSFILE;
	else  fbus=(BUSFILE*)realloc(fbus,sizeof(BUSFILE)*(n+1));
	if(fbus==NULL){
		fsum=0;
		return false;
	}
	fbus[n]=nbfile;
	fsum++;
	return true;
}

//�쿴ĸ���Ƿ�����ͼ����(����ĸ���ظ�)
bool BFCfgDlg::IsInGBus(long id)
{
	int i;
	for(i=0;i<gsum;i++) 
	{
		if(id==gbus[i].id) return true;
	}
	return false;
}
//�쿴ĸ���Ƿ����ڹ�����ϵ��
bool BFCfgDlg::IsInFBus(long id)
{
	int i;
	for(i=0;i<fsum;i++)
	{
		if(fbus[i].id==id) return true;
	}
	return false;
}

void BFCfgDlg::DelAGbusRec(int j)
{
	int i,k;
	if(gsum<=0) return;
	for(i=j;i<gsum-1;i++){
		gbus[i]=gbus[i+1];
	}
	k=gsum-1;
	if(k>0)	gbus=(GBUS*)realloc(gbus,sizeof(GBUS)*k);
	else {
		delete gbus;
		gbus=NULL;
	};
	gsum=k;
}

void BFCfgDlg::DelAFbusRec(int j)
{
	int i,k;
	if(fsum<=0||j<0||j>=fsum) return;
	for(i=j;i<fsum-1;i++)
	{
		fbus[i]=fbus[i+1];
	}
	k=fsum-1;
	if(k>0)	fbus=(BUSFILE*)realloc(fbus,sizeof(BUSFILE)*k);
	else {
		delete fbus;
		fbus=NULL;
	};
	fsum=k;
}

//�������ļ����뵽�б����
void BFCfgDlg::AddToListCtl()
{
	int i;
	char p[100];
	for(i=0;i<fsum;i++){
	  m_rf.InsertItem(i,fbus[i].name);
	  sprintf(p,"%d",fbus[i].id);
	  m_rf.SetItemText(i,1,p);
	  m_rf.SetItemText(i,2,fbus[i].grpfile);
	  sprintf(p,"%d",fbus[i].index);
	  m_rf.SetItemText(i,3,p);
	}
}
//��������
void BFCfgDlg::SaveCfg()
{
	char name[256];
	BFHEAD head;
	FILE *fp;
	strcpy(name,cobj.path[1].path);
	strcat(name,"\\bsralate.cfg");
	fp=fopen(name,"r+b");
	if(fp==NULL) return;
	head.flag=0xd0;
	head.version=0x10;
	head.sum=fsum;
	fwrite(&head,sizeof(BFHEAD),1,fp);
	fwrite(fbus,sizeof(BUSFILE),fsum,fp);
	fclose(fp);
}

void BFCfgDlg::OnAdd() 
{
	int n,m;
	char p[100];
	BUSFILE nbfile;
	char fname[32];
	n=m_bus.GetCurSel();
	if(n==LB_ERR){
		MessageBox("����ѡ��һ��ĸ�ߣ�","����",MB_OK|MB_ICONSTOP);
		return;
	}
	GetDlgItemText(IDC_FILENAME,fname,32);
	if(strlen(fname)>23){
		MessageBox("�ļ���̫����ӦС��23�ַ���","����",MB_OK|MB_ICONSTOP);
		return;
	}
	if(strlen(fname)<4){
		MessageBox("�ļ�������ȷ��Ϊ�գ���������ȷ���ļ�����","����",MB_OK|MB_ICONSTOP);
		return;
	}
	strcpy(nbfile.name,gbus[n].name);
	nbfile.id=gbus[n].id;
	strcpy(nbfile.grpfile,fname);
	m=GetDlgItemInt(IDC_INDEX);
	if(m<0||m>255){
		MessageBox("ҳ��Ų���ȷ��Ӧ��0-255�ڣ�","����",MB_OK|MB_ICONSTOP);
		return;
	}
	if(IsInFBus(nbfile.id)){
		MessageBox("��ĸ�ߵ�ID�ѹ������棬�����ٴι�����\n������ɾ���ѹ����","����",MB_OK|MB_ICONSTOP);
		return;
	}
	nbfile.index=(BYTE)m;
	AddFBus(nbfile);
	n=m_rf.GetItemCount();
	m_rf.InsertItem(n,nbfile.name);
	sprintf(p,"%d",nbfile.id);
	m_rf.SetItemText(n,1,p);
	m_rf.SetItemText(n,2,nbfile.grpfile);
	sprintf(p,"%d",nbfile.index);
	m_rf.SetItemText(n,3,p);
}

void BFCfgDlg::OnDelete() 
{
	int n;
	POSITION m;
	m=m_rf.GetFirstSelectedItemPosition();
	if(m==NULL) return;
	n=(int)m-1;
	m_rf.DeleteItem(n);
	DelAFbusRec(n);
}
//��һ�������ļ���ȡ��ҳ�����
void BFCfgDlg::OnOpenpwf()
{
	int i,m,n,pno;
	char *lp;
	N_PWFHEAD *ph,head;
	N_SUBPWF hd;
	char *buf1;
	FILE *fp;
	char fnm[256],path[256];
	//���ҵ����ڵ��ļ���
	strcpy(path,cobj.path[1].path);
	if(!GetPw0ile(fnm,path,pno,m_hWnd)) return;
	//
	m_pno.ResetContent();
	//���ļ�
	fp=fopen(fnm,"r+b");
	if(fp==NULL) return;
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	if(head.Version>3203)//!=3200&&head.Version!=3201&&head.Version!=0x3202){ //��֤�汾
	{
		fclose(fp);
		return;
	};
	n=head.pagesum;
	m=n*sizeof(N_OBJSAVE)+sizeof(N_PWFHEAD);
	buf1=new char[m+100];
	ph=(N_PWFHEAD*)buf1;
	fseek(fp,0,SEEK_SET);
	fread(buf1,m,1,fp);
	for(i=0;i<n;i++)
	{
		fseek(fp,(long)ph->page[i].offset,SEEK_SET);
		fread(&hd,sizeof(N_SUBPWF),1,fp);
		if(hd.flag!=0xcccc)	continue;	//�����
		m_pno.AddString(hd.Name);
	};
	fclose(fp);
	delete buf1;
	m_pno.SetCurSel(pno);
	SetDlgItemInt(IDC_INDEX,pno);
	lp=strrchr(fnm,'\\');
	if(lp!=NULL) lp++;
	else lp=fnm;
	SetDlgItemText(IDC_FILENAME,lp);
}

//�����˳�
void BFCfgDlg::OnOK() 
{
	char name[256];
	BFHEAD head;
	FILE *fp;
	strcpy(name,cobj.path[1].path);
	strcat(name,"\\bsralate.cfg");
	fp=fopen(name,"w+b");
	if(fp==NULL) return;
	head.flag=0xd0;
	head.version=0x10;
	head.sum=fsum;
	fwrite(&head,sizeof(BFHEAD),1,fp);
	fwrite(fbus,sizeof(BUSFILE),fsum,fp);
	fclose(fp);
	MessageBox("������ϣ�\n����ͨ���������淢�������ļ���");
	CDialog::OnOK();
}

//ɾ���ѹ�����ĸ��
void BFCfgDlg::OnClearra() 
{
	int i;
	for(i=0;i<gsum;i++){
		if(IsInFBus(gbus[i].id))
		{
			DelAGbusRec(i);
			i--;
		}
	}
	AddToGBusList();
}
