// SglVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SglVDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *tblnm[];
extern char *fld[];

char *xsm0[]={"�й�","�޹�"};
char *xsm1[]={"����й�","����޹�","ĩ���й�","ĩ���޹�"};
char *xsm2[]={"��ѹ����ֵ"};
char *xsm3[]={"�й�","�޹�"};
char *xsm4[]={"�ߵ�λ�ֽ�ͷ","�е�λ�ֽ�ͷ"};
char *xsm5[]={"����й�","ĩ���й�"};
char *xsm6[]={"��ǰֵ","�����ʵ�һ","�����ʵڶ�","�����ʵ���","�����ʵ���","�����ʵ���","�����ʵ���","�����ʵ���","�����ʵڰ�","�����ʵھ�","�����ʵ�ʮ"};

/////////////////////////////////////////////////////////////////////////////
// SglVDlg dialog


SglVDlg::SglVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SglVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SglVDlg)
	//}}AFX_DATA_INIT
	num=0;
	def=NULL;
	defsf=NULL;
}
SglVDlg::~SglVDlg()
{
	if(def!=NULL) delete def;
}

void SglVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SglVDlg)
	DDX_Control(pDX, IDC_XS, m_xs);
	DDX_Control(pDX, IDC_DEV, m_dev);
	DDX_Control(pDX, IDC_LDEV, m_ldev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SglVDlg, CDialog)
	//{{AFX_MSG_MAP(SglVDlg)
	ON_CBN_SELCHANGE(IDC_DEV, OnSelchangeDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SglVDlg message handlers

BOOL SglVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("���ݿ�ƽ̨δ����","����",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	if(ad.dbs.dtype==13)
		m_dev.SetCurSel(5);
	else
		m_dev.SetCurSel(ad.dbs.dtype);
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(GetIndex(ad.dbs.did));
	SetXsMode();
	
	return TRUE; 
}

void SglVDlg::OnSelchangeDev() 
{
	int i;
	CString strSel;
	i=m_dev.GetCurSel();
	m_dev.GetLBText(i,strSel);
	if(strSel.Compare("Ԥ�������")==0)
		ad.dbs.dtype=13;
	else
		ad.dbs.dtype=(BYTE)i;
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(0);
	SetXsMode();
	m_xs.SetCurSel(0);
}

void SglVDlg::OnOK() 
{
	int i;
	ad.dbs.xsmode=m_xs.GetCurSel();
	i=m_ldev.GetCurSel();
	if(i==LB_ERR){
		i=-1;
		ad.dbs.did=-1;
		strcpy(ad.dbs.name,"ûѡ���豸");
		CDialog::OnOK();
	}
	ad.dbs.did=def[i].id;
	strcpy(ad.dbs.name,def[i].name);
	CDialog::OnOK();
}

void SglVDlg::GetData(int dtype)
{
	int i,j;
	DWORD idi;
	MEMTABLE *mtb;
	if(dtype<0||dtype>13) return;
	if(dtype==13)
	{
		if(!LSI_GetTableID("common","PreDefSF",idi)) return;
	}
	else
	{
		if(!LSI_GetTableID(ad.mdbnm,tblnm[dtype],idi)) return;
	}
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
	switch(dtype)
	{
	case 0: //�����
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gen[i].NU;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	case 1: //���������
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=line[i].NU;
			strcpy(def[i].name,line[i].Name);
		}
		break;
	case 2: //ֱ�������
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=dcl[i].NU;
			strcpy(def[i].name,dcl[i].Name);
		}
		break;
	case 3: //ĸ��
		bus=(visualpw_Bus *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=bus[i].NU;
			strcpy(def[i].name,bus[i].Name);
		}
		break;
	case 4: //����
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=load[i].NU;
			strcpy(def[i].name,load[i].Name);
		}
		break;
	case 13: //Ԥ�������
		defsf=(common_PreDefSF *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=defsf[i].ID;
			strcpy(def[i].name,defsf[i].Name);
		}
		break;
	}
}

void SglVDlg::SetToLst()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_ldev.AddString(p);
	}
}

void SglVDlg::SetXsMode()
{
	int i;
	m_xs.ResetContent();
	switch(ad.dbs.dtype)
	{
	case 0:  //�����
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xsm0[i]);
		break;
	case 1:  //��·
		m_xs.EnableWindow(true);
		for(i=0;i<4;i++) m_xs.AddString(xsm1[i]);
		break;
	case 2:  //ֱ��
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xsm5[i]);
		break;
	case 3:  //�ڵ��ĸ��
		m_xs.EnableWindow(true);
		for(i=0;i<1;i++) m_xs.AddString(xsm2[i]);
		break;
	case 4:  //�ڵ��ĸ��
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xsm3[i]);
		break;
	case 13:  //����
		m_xs.EnableWindow(true);
		for(i=0;i<11;i++) m_xs.AddString(xsm6[i]);
		break;
	default:
		m_xs.EnableWindow(false);
	}
	m_xs.SetCurSel(ad.dbs.xsmode);
}

//�������
int SglVDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}
