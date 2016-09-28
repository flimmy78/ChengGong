// ZoneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "ZoneDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoneDlg dialog


CZoneDlg::CZoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoneDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	num=0;
	zone=NULL;
	mode=0;
}

CZoneDlg::~CZoneDlg()
{
	if(num!=0&&zone!=NULL) delete zone;
	num=0;
	zone=NULL;
}

void CZoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoneDlg)
	DDX_Control(pDX, IDC_COMBO1, m_mode);
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoneDlg, CDialog)
	//{{AFX_MSG_MAP(CZoneDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MODI, OnModi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoneDlg message handlers
BOOL CZoneDlg::OnInitDialog() 
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
	m_lst.InsertColumn(0,"������",LVCFMT_LEFT,80,0);
	m_lst.InsertColumn(1,"  ��������",LVCFMT_LEFT,162,0);
	m_mode.SetCurSel(0);
	ModeChange();
	GetData();
	SetToList();
	return TRUE; 
}

void CZoneDlg::EnableItem(int id,bool enable)
{
	CWnd* wnd=GetDlgItem(id); 
	if(wnd!=NULL) wnd->EnableWindow(enable);
}
//ģʽ�仯
void CZoneDlg::ModeChange()
{
	int i=m_mode.GetCurSel();
	switch(i){
	case 0: //�༭
		EnableItem(IDC_DELETE,false);
		EnableItem(IDC_CREATE,false);
		EnableItem(IDC_MODI,true);
		EnableItem(IDC_NU,false);
		EnableItem(IDC_NAME,true);
		EnableItem(IDC_PNU,true);
		EnableItem(IDC_LNU,true);
		m_lst.EnableWindow(true);
		break;
	case 1: //���
		EnableItem(IDC_DELETE,false);
		EnableItem(IDC_CREATE,true);
		EnableItem(IDC_MODI,false);
		EnableItem(IDC_NU,true);
		EnableItem(IDC_NAME,true);
		EnableItem(IDC_PNU,true);
		EnableItem(IDC_LNU,true);
		m_lst.EnableWindow(false);
		break;
	case 2: //ɾ��
		EnableItem(IDC_DELETE,true);
		EnableItem(IDC_CREATE,false);
		EnableItem(IDC_MODI,false);
		EnableItem(IDC_NU,false);
		EnableItem(IDC_NAME,false);
		EnableItem(IDC_PNU,false);
		EnableItem(IDC_LNU,false);
		m_lst.EnableWindow(true);
		break;
	}
	mode=i;
}

void CZoneDlg::OnSelchangeCombo1() 
{
	ModeChange();
}
//��ȡ��������
void CZoneDlg::GetData()
{
	int i,j;
	DWORD idi;
	visualpw_Zone *zn;
	MEMTABLE *mtb;
	num=0;
	if(!LSI_GetTableID(dbfile,"Zone",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	num=mtb->userec;
	if(zone!=NULL) delete zone;
	zone=new visualpw_Zone[num];
	if(zone==NULL){
		num=0;
		return;
	}
	zn=(visualpw_Zone*)mtb->data;
	for(i=0;i<num;i++)	zone[i]=zn[i];
}

void CZoneDlg::SetToList()
{
	int i;
	char p[128];
	m_lst.DeleteAllItems( );
	for(i=0;i<num;i++){
		sprintf(p,"%d",zone[i].NU);
		m_lst.InsertItem(i,p);
		m_lst.SetItemText(i,1,zone[i].Name);
	}
}

void CZoneDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int n;
	if(mode==0){
		n=m_lst.GetSelectionMark();
		if(n!=-1&&n>=0&&n<num){
			SetDlgItemInt(IDC_NU,zone[n].NU);
			SetDlgItemText(IDC_NAME,zone[n].Name);
		}
	}
	*pResult = 0;
}

//��������
void CZoneDlg::OnCreate() 
{
	visualpw_Zone tmp;
	char p[100];
	tmp.NU=GetDlgItemInt(IDC_NU);
	GetDlgItemText(IDC_NAME,tmp.Name,24);
	GetDlgItemText(IDC_NU,p,24);
	if(strlen(p)==0){
		MessageBox("�����Ϊ��,���ܴ�����","����",MB_ICONSTOP);
		return;
	}
	GetDlgItemText(IDC_NAME,p,80);
	if(strlen(p)>23||strlen(p)==0){
		MessageBox("���Ƴ���>23�ַ��������ֶ�Ϊ�գ����ܴ�����","����",MB_ICONSTOP);
		return;
	}
	if(IsExistID(tmp.NU)){
		MessageBox("��ID�Ѵ��ڣ����ܴ�����","����",MB_ICONSTOP);
		return;
	}
	AppendData(tmp);
	GetData();
	SetToList();
}

//ɾ������
void CZoneDlg::OnDelete() 
{
	char sql[256];
	int n=m_lst.GetSelectionMark();
	if(n==-1||n>=num){
		MessageBox("δѡ��һ��������ɾ����","����",MB_ICONSTOP);	
		return;
	}
	sprintf(sql,"%s.%s",dbfile,"Zone");
	if(LSI_DeleteRecord(sql,n)==0){ //ɾ���ɹ�
		sprintf(sql,"�ɹ�ɾ��[%s]���豸���Ϊ%d��¼!",dbfile,zone[n].NU);
		MessageBox(sql);
		GetData();
		SetToList();
	}
}
//�޸�
void CZoneDlg::OnModi() 
{
	int i;
	visualpw_Zone tmp;
	char p[100];
	i=m_lst.GetSelectionMark();
	if(i==-1||i>=num)
	{
		MessageBox("δѡ��һ���������޸ģ�","����",MB_ICONSTOP);	
		return;
	}
	tmp=zone[i];
	tmp.NU=GetDlgItemInt(IDC_NU);
	GetDlgItemText(IDC_NAME,tmp.Name,24);
	GetDlgItemText(IDC_NU,p,24);
	if(strlen(p)==0)
	{
		MessageBox("�����Ϊ��,�����û����ѡ��һ���������༭��","����",MB_ICONSTOP);
		return;
	}
	GetDlgItemText(IDC_NAME,p,80);
	if(strlen(p)>23||strlen(tmp.Name)==0)
	{
		MessageBox("���Ƴ���>23�ַ��������ֶ�Ϊ�գ������޸ģ�","����",MB_ICONSTOP);
		return;
	}
	ModiData(i,tmp);
	GetData();
	SetToList();
}
//�Ƿ��Ѵ��ڸ�ID
bool CZoneDlg::IsExistID(int id)
{
	int i;
	for(i=0;i<num;i++)
	{
		if(id==(int)zone[i].NU) return true;
	}
	return false;
}

//��������(�¼Ӽ�¼)
void CZoneDlg::ModiData(int i,visualpw_Zone &tmp)
{
	char sql[256];
	visualpw_Zone zn;
	zn=tmp;
	sprintf(sql,"%s.%s",dbfile,"Zone");
	LSI_UpdateARecord(sql,&zn,i);
}

//�������(�¼Ӽ�¼)
void CZoneDlg::AppendData(visualpw_Zone &tmp)
{
	/*char sql[256];
	visualpw_Zone zn;
	zn.NU=tmp.NU;
	strcpy(zn.Name,tmp.Name);
	zn.total_gen=0;
	zn.demand=0;
	zn.total_los=0;
	sprintf(sql,"%s.%s",dbfile,"Zone");
	LSI_AppendRec(sql,&zn);*/
}