// SelDVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelDVDlg.h"
#include "dbapi.h"
#include "userapi.h"
#include "pysel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//�豸�������ͱ�
/*
0="PT" 1="�����" 2="����,��բ",3="����",4="����",5="�翹",6="�ӵ�",7="�������ѹ��"
8="�������ѹ��",9="��̬�޹�������",10="��䡢������"
33=ĸ�� 34=���� 35=ֱ��
*/
char *devtbl[]={"PT",		//PT
				"Gen",		//�����
				"Switch",   //����
				"Load",		//����
				"Shunt",	//����
				"Sreact",	//�翹
				"GND",		//�ӵ�
				"Tfm1",		//2�����ѹ��
			    "Tfm2",		//3�����ѹ��
			    "SVC",		//��̬�޹�����װ��
				"CVT",		//�����
				"Bus",		//ĸ��
			    "Line",		//����
			    "DCLine",	//ֱ��
				}; 


char *dvnm[]={"PT","�����","����,��բ","����","����","�翹","�ӵ�","�������ѹ��",
"�������ѹ��","��̬�޹�������","��䡢������","ĸ��","����","ֱ��"};
/////////////////////////////////////////////////////////////////////////////
// SelDVDlg dialog

SelDVDlg::SelDVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelDVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelDVDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	num=0;
	stsum=0;
	numt=0;
	font.CreateFont(30,15,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"����" );
	def=NULL;
	st=NULL;
	deft=NULL;
	dbok=false;
}

SelDVDlg::~SelDVDlg()
{

	if(def!=NULL)	delete def;
	if(st!=NULL)	delete st;
	if(deft!=NULL)	delete deft;
	font.DeleteObject();
}


void SelDVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelDVDlg)
	DDX_Control(pDX, IDC_LIST2, m_lst2);
	DDX_Control(pDX, IDC_LIST1, m_lst);
	DDX_Control(pDX, IDC_DTYPE, m_dtype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelDVDlg, CDialog)
	//{{AFX_MSG_MAP(SelDVDlg)
	ON_BN_CLICKED(IDC_SHOWALL, OnShowall)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList2)
	ON_EN_CHANGE(IDC_PYJS, OnChangePyjs)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelDVDlg message handlers

BOOL SelDVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("���ݿ�ƽ̨δ����","����",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	DWORD sty=m_lst.GetExtendedStyle();
	m_lst.SetExtendedStyle(sty|LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_FULLROWSELECT);
	m_lst.SetBkColor(0xf0ffff);
	m_lst.SetTextBkColor(0xf0ffff);
	m_lst.SetTextColor(0);
	m_lst.InsertColumn(0,"�豸���(ID)",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  �豸����",LVCFMT_LEFT,220,0);

	ti=sd.dtype>=33 ? sd.dtype-22:sd.dtype;
	if(ti>13||ti<0){
		MessageBox("�豸���Ͳ����ڣ�");	
		return false;
	}
	m_dtype.SetFont(&font);
	GetStation();
	SetToSTLst();
	GetData();
	SetDlgItemInt(IDC_NU,sd.did);
	SetDlgItemText(IDC_NAME,sd.name);
	OnShowall();
	return TRUE; 
}


void SelDVDlg::GetStation()
{
	DWORD idi;
	MEMTABLE *mtb;
	visualpw_Station *ss;
	int i,j;
	if(!LSI_GetTableID(sd.dbname,"Station",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	stsum=mtb->userec;
	if(st!=NULL) delete st;
	st=new STATION[stsum];
	if(st==NULL)
	{
		stsum=0;
		return;
	}
	ss=(visualpw_Station*)mtb->data;
	for(i=0;i<stsum;i++)
	{
		st[i].id=ss[i].NU;
		strcpy(st[i].name,ss[i].Name);
	}
	OrderStationByName();
}

//��ȡ����
void SelDVDlg::GetData()
{
	DWORD idi;
	MEMTABLE *mtb;
	int t,i,j;
	char sql[256];
	num=0;
	t=ti;
	if(t>13||t<0) return;
	
	if(!LSI_GetTableID(sd.dbname,devtbl[t],idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	num=mtb->userec;
	if(def!=NULL) delete def;
	def=new DEVDEF[num];
	if(def==NULL){
		num=0;
		return;
	}
	switch(t)
	{
	case 0: //PT
		pt=(visualpw_PT *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=pt[i].NU;
			def[i].stno=pt[i].Station;
			strcpy(def[i].name,pt[i].Name);
		}
		break;
	case 1: //����� 
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gen[i].NU;
			def[i].stno=gen[i].Station;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	case 2:	//���أ���բ
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=swt[i].NU;
			def[i].stno=swt[i].Station;
			strcpy(def[i].name,swt[i].Name);
		}
		break;
	case 3: //����
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=load[i].NU;
			def[i].stno=load[i].Station;
			strcpy(def[i].name,load[i].Name);
		}
		break;
	case 4:  //����
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			def[i].stno=sht[i].Station;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 5:  //�翹
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=srt[i].NU;
			def[i].stno=srt[i].Station;
			strcpy(def[i].name,srt[i].Name);
		}
		break;
	case 6:  //�ӵ�
		gnd=(visualpw_GND *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gnd[i].NU;
			def[i].stno=gnd[i].Station;
			strcpy(def[i].name,gnd[i].Name);
		}
		break;

	case 7: //2�Ʊ�
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			def[i].stno=tfm1[i].Station;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 8: //���Ʊ�
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			def[i].stno=tfm2[i].Station;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=svc[i].NU;
			def[i].stno=svc[i].Station;
			strcpy(def[i].name,svc[i].Name);
		}
		break;
	case 10://�����
		cvt=(visualpw_CVT *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=cvt[i].NU;
			def[i].stno=cvt[i].Station;
			strcpy(def[i].name,cvt[i].Name);
		}
		break;
	case 11: //ĸ��
		bus=(visualpw_Bus *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=bus[i].NU;
			def[i].stno=bus[i].Station;
			strcpy(def[i].name,bus[i].Name);
		}
		break;
	case 12: //���������
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=line[i].NU;
			def[i].stno=line[i].Stationf;
			strcpy(def[i].name,line[i].Name);
		}
		break;
	case 13: //ֱ�������
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=dcl[i].NU;
			def[i].stno=dcl[i].Stationf;
			strcpy(def[i].name,dcl[i].Name);
		}
		break;
	}
	sprintf(sql,"ѡ����豸����:%s",dvnm[t]);
	m_dtype.SetWindowText(sql);
}

//���õ��б��
void SelDVDlg::SetToLst()
{
	int i;
	char p[128];
	m_lst.DeleteAllItems( );
	
	for(i=0;i<numt;i++){
		sprintf(p,"%d",deft[i].id);
		m_lst.InsertItem(i,p);
		m_lst.SetItemText(i,1,deft[i].name);
	}
	i=GetItemIndex(sd.did);
	if(i>=0){
		m_lst.SetHotItem(i);
		m_lst.SetSelectionMark(i);
	}
}

//���õ��б��
void SelDVDlg::SetToSTLst()
{
	int i;
	m_lst2.ResetContent();
	for(i=0;i<stsum;i++){
		m_lst2.AddString(st[i].name);
	}
}

void SelDVDlg::OnOK() 
{
	int i=m_lst.GetSelectionMark();
	if(i==-1){
		MessageBox("δѡ��һ���豸�����ܱ��棡\n��ѡ��ȡ���˳���","����",MB_ICONSTOP);
		return;
	}
	strcpy(sd.name,deft[i].name);
	sd.did=deft[i].id;
	CDialog::OnOK();
}

int SelDVDlg::GetItemIndex(int id)
{
	int i;
	for(i=0;i<numt;i++)
	{
		if(id==deft[i].id) return i;
	}
	return -1;
}


//ȫ����ʾ
void SelDVDlg::OnShowall() 
{
	numt=num;
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[numt];
	memcpy(deft,def,numt*sizeof(DEVDEF));
	SetToLst();
}

void SelDVDlg::OnSelchangeList2() 
{
	int i,j,m,n,stnu;
	m_lst.DeleteAllItems( );
	m=m_lst2.GetCurSel();
	if(m==LB_ERR) return;
	stnu=st[m].id;
	n=0;
	for(i=0;i<num;i++) if(def[i].stno==stnu) n++;
	if(n==0) return;
	numt=n;
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[n];
	j=0;
	for(i=0;i<num;i++)
	{
		if(def[i].stno==stnu)
		{
			deft[j]=def[i];
			j++;
		}
	}
	OrderDevByName();
	SetToLst();
}

//վ����������
void SelDVDlg::OrderStationByName()
{
	int i,j;
	STATION tmp;
	for(i=0;i<stsum-1;i++)
	{
		for(j=i+1;j<stsum;j++)
		{
			if(strcmp(st[i].name,st[j].name)>0)
			{
				tmp=st[i];
				st[i]=st[j];
				st[j]=tmp;
			}

		}
	}
}


//�豸����������
void SelDVDlg::OrderDevByName()
{
	int i,j;
	DEVDEF tmp;
	for(i=0;i<numt-1;i++)
	{
		for(j=i+1;j<numt;j++)
		{
			if(strcmp(deft[i].name,deft[j].name)>0)
			{
				tmp=deft[i];
				deft[i]=deft[j];
				deft[j]=tmp;
			}

		}
	}
}

//�豸��ID����
void SelDVDlg::OrderDevByID()
{
	int i,j;
	DEVDEF tmp;
	for(i=0;i<numt-1;i++)
	{
		for(j=i+1;j<numt;j++)
		{
			if(deft[i].id>deft[j].id)
			{
				tmp=deft[i];
				deft[i]=deft[j];
				deft[j]=tmp;
			}

		}
	}
}

void SelDVDlg::OnChangePyjs() 
{
	int i,n;
	PySel psl;
	char str[16];
	if(num==0) return;
	GetDlgItemText(IDC_PYJS,str,10);
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[num];
	n=0;
	for(i=0;i<num;i++)
	{
		if(psl.IsThisPy(str,def[i].name))
		{
			deft[n]=def[i];
			n++;
		}
	}
	numt=n;
	OrderDevByName();
	SetToLst();
	
}

void SelDVDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	i=pNMListView ->iSubItem; //���µ���
	switch(i)
	{
	case 0:
		OrderDevByID();
		break;
	case 1:
		OrderDevByName();
		break;
	}
	SetToLst();
	*pResult = 0;
}
