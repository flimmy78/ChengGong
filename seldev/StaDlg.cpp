// StaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "StaDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *tblnms[]={"Gen",		//�����
			   "Line",		//����
			   "DCLine",	//ֱ��
			   "Bus",		//ĸ��
			   "Load",		//����
			   "Tfm1",		//2�����ѹ��
			   "Tfm2",		//3�����ѹ��
			   "Shunt",		//����
			   "Sreact",	//�翹
			   "SVC",		//��̬�޹�����װ��
			   "Switch"};   //����
/////////////////////////////////////////////////////////////////////////////
// StaDlg dialog


StaDlg::StaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	def=NULL;
}

StaDlg::~StaDlg()
{
	if(def!=NULL) delete def;
}
void StaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StaDlg)
	DDX_Control(pDX, IDC_LDEV, m_ldev);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StaDlg, CDialog)
	//{{AFX_MSG_MAP(StaDlg)
	ON_CBN_SELCHANGE(IDC_DEV, OnSelchangeDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StaDlg message handlers

BOOL StaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("���ݿ�ƽ̨δ����","����",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	m_dev.SetCurSel(ad.dbs.dtype);
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(GetIndex(ad.dbs.did));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void StaDlg::GetData(int dtype)
{

	DWORD idi;
	MEMTABLE *mtb;
	int t,i,j;
	num=0;
	t=dtype;
	if(t>10||t<0) return;
	if(!LSI_GetTableID(ad.mdbnm,tblnms[t],idi)) return;
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
		
	case 2:	//ֱ�������
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
	case 5://2�Ʊ�
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 6://���Ʊ�
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 7://����
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 8://�翹
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=srt[i].NU;
			strcpy(def[i].name,srt[i].Name);
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=svc[i].NU;
			strcpy(def[i].name,svc[i].Name);
		}
		break;
	case 10://���أ���բ
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=swt[i].NU;
			strcpy(def[i].name,swt[i].Name);
		}
		break;
	}
}

void StaDlg::SetToLst()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_ldev.AddString(p);
	}
}

void StaDlg::OnSelchangeDev() 
{
	int i;
	i=m_dev.GetCurSel();
	ad.dbs.dtype=(BYTE)i;
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(0);
}

//�������
int StaDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}

void StaDlg::OnOK() 
{
	int i;
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
