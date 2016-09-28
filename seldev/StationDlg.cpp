// StationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "StationDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StationDlg dialog


StationDlg::StationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	zone=NULL;//������
	zsum=0;	 //������
	sta=NULL;//վ
	snum=0;	 //վ����
	mode=0;
}

StationDlg::~StationDlg()
{
	if(zone!=NULL) delete zone;
	if(sta!=NULL) delete sta;
	zsum=0;
	snum=0;
	zone=NULL;
	sta=NULL;
}
void StationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StationDlg)
	DDX_Control(pDX, IDC_SZONE, m_szone);
	DDX_Control(pDX, IDC_LIST1, m_lst);
	DDX_Control(pDX, IDC_MODE, m_mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StationDlg, CDialog)
	//{{AFX_MSG_MAP(StationDlg)
	ON_CBN_SELCHANGE(IDC_MODE, OnSelchangeMode)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MODI, OnModi)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StationDlg message handlers

BOOL StationDlg::OnInitDialog() 
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
	m_lst.InsertColumn(0,"��վ���",LVCFMT_LEFT,80,0);
	m_lst.InsertColumn(1,"  ��վ����",LVCFMT_LEFT,160,0);
	m_lst.InsertColumn(2,"  ��������",LVCFMT_LEFT,154,0);
	m_mode.SetCurSel(0);
	GetZone();
	SetZoneList();
	ReadStation();
	SetStationList();
	OnSelchangeMode();
	return TRUE; 
}

void StationDlg::EnableItem(int id,bool enable)
{
	CWnd* wnd=GetDlgItem(id); 
	if(wnd!=NULL) wnd->EnableWindow(enable);
}

void StationDlg::OnSelchangeMode() 
{
	int i=m_mode.GetCurSel();
	switch(i){
	case 0: //�༭
		EnableItem(IDC_DELETE,false);
		EnableItem(IDC_CREATE,false);
		EnableItem(IDC_MODI,true);
		EnableItem(IDC_NU,false);
		EnableItem(IDC_NAME,true);
		m_lst.EnableWindow(true);
		m_szone.EnableWindow(true);
		break;
	case 1: //���
		EnableItem(IDC_DELETE,false);
		EnableItem(IDC_CREATE,true);
		EnableItem(IDC_MODI,false);
		EnableItem(IDC_NU,true);
		EnableItem(IDC_NAME,true);
		m_lst.EnableWindow(false);
		m_szone.EnableWindow(true);
		break;
	case 2: //ɾ��
		EnableItem(IDC_DELETE,true);
		EnableItem(IDC_CREATE,false);
		EnableItem(IDC_MODI,false);
		EnableItem(IDC_NU,false);
		EnableItem(IDC_NAME,false);
		m_lst.EnableWindow(true);
		m_szone.EnableWindow(false);
		break;
	}
	mode=i;
}

//������������
void StationDlg::GetZone()
{
	int i,j;
	DWORD idi;
	visualpw_Zone *zn;
	MEMTABLE *mtb;
	zsum=0;
	if(!LSI_GetTableID(dbfile,"Zone",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	zsum=mtb->userec;
	if(zone!=NULL) delete zone;
	zone=new visualpw_Zone[zsum];
	if(zone==NULL){
		zsum=0;
		return;
	}
	zn=(visualpw_Zone*)mtb->data;
	for(i=0;i<zsum;i++)	zone[i]=zn[i];
}

void StationDlg::SetZoneList()
{
	int i;
	for(i=0;i<zsum;i++){
		m_szone.AddString(zone[i].Name);
	}
}

int StationDlg::GetZoneIndex(int id)
{
	int i;
	for(i=0;i<zsum;i++){
		if(id==(int)zone[i].NU) return i;
	}
	return -1;
}

char *sfld[]={"intNU","strName","intZoneNU"};
//����վ����
void StationDlg::ReadStation()
{
	int i,j;
	DWORD idi;
	visualpw_Station *zn;
	MEMTABLE *mtb;
	snum=0;
	if(!LSI_GetTableID(dbfile,"Station",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	snum=mtb->userec;
	if(sta!=NULL) delete sta;
	sta=new visualpw_Station[snum];
	if(sta==NULL){
		snum=0;
		return;
	}
	zn=(visualpw_Station*)mtb->data;
	for(i=0;i<snum;i++)	sta[i]=zn[i];
}

void StationDlg::SetStationList()
{
	int i,j;
	char p[128];
	m_lst.DeleteAllItems( );
	for(i=0;i<snum;i++){
		sprintf(p,"%d",sta[i].NU);
		m_lst.InsertItem(i,p);
		m_lst.SetItemText(i,1,sta[i].Name);
		j=GetZoneIndex(sta[i].zoneNU);
		if(j>=0){
			m_lst.SetItemText(i,2,zone[j].Name);
		}else m_lst.SetItemText(i,2,"δ����");
	}
}

void StationDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
}
//����¼�¼
void StationDlg::OnCreate() 
{
	int i;
	char p[100];
	visualpw_Station tmp;
	tmp.NU=GetDlgItemInt(IDC_NU);
	GetDlgItemText(IDC_NAME,tmp.Name,24);
	i=m_szone.GetCurSel();
	if(i>=0&&i<zsum) tmp.zoneNU=zone[i].NU;
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
	ReadStation();
	SetStationList();
}
//ɾ����¼
void StationDlg::OnDelete() 
{
	char sql[256];
	int n=m_lst.GetSelectionMark();
	if(n==-1||n>=snum){
		MessageBox("δѡ��һ����վ��ɾ����","����",MB_ICONSTOP);	
		return;
	}
	sprintf(sql,"%s.%s",dbfile,"Station");
	if(LSI_DeleteRecord(sql,n)==0){ //ɾ���ɹ�
		sprintf(sql,"�ɹ�ɾ��[%s]���豸���Ϊ%d��¼!",dbfile,zone[n].NU);
		MessageBox(sql);
		ReadStation();
		SetStationList();
	}
}
//�޸ļ�¼
void StationDlg::OnModi() 
{
	int i,j;
	char p[100];
	visualpw_Station tmp;
	j=m_lst.GetSelectionMark();
	if(j==-1||j>=snum){
		MessageBox("δѡ��һ����վ��ɾ����","����",MB_ICONSTOP);	
		return;
	}
	tmp=sta[j];
	tmp.NU=GetDlgItemInt(IDC_NU);
	GetDlgItemText(IDC_NAME,tmp.Name,24);
	i=m_szone.GetCurSel();
	if(i>=0&&i<zsum) tmp.zoneNU=zone[i].NU;
	GetDlgItemText(IDC_NU,p,24);
	if(strlen(p)==0){
		MessageBox("�����Ϊ��,�����û����ѡ��һ��վ���༭��","����",MB_ICONSTOP);
		return;
	}
	GetDlgItemText(IDC_NAME,p,80);
	if(strlen(p)>23||strlen(p)==0){
		MessageBox("���Ƴ���>23�ַ��������ֶ�Ϊ�գ������޸ģ�","����",MB_ICONSTOP);
		return;
	}
	ModiData(j,tmp);
	ReadStation();
	SetStationList();
}

//�Ƿ��id�Ѵ���
bool StationDlg::IsExistID(int id)
{
	int i;
	for(i=0;i<snum;i++){
		if(id==(int)sta[i].NU) return true;
	}
	return false;
}

//��������
void StationDlg::ModiData(int j,visualpw_Station &tmp)
{
	char sql[256];
	visualpw_Station st;
	st=tmp;
	sprintf(sql,"%s.%s",dbfile,"Station");
	LSI_UpdateARecord(sql,&st,j);
}

//��������
void StationDlg::AppendData(visualpw_Station &tmp)
{
	char sql[256];
	visualpw_Station st;
	st=tmp;
	sprintf(sql,"%s.%s",dbfile,"Station");
	LSI_AppendRec(sql,&st);
}

void StationDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int j,n;
	if(mode==0){
		n=m_lst.GetSelectionMark();
		if(n!=-1&&n>=0&&n<snum){
			SetDlgItemInt(IDC_NU,sta[n].NU);
			SetDlgItemText(IDC_NAME,sta[n].Name);
			j=GetZoneIndex(sta[n].zoneNU);
			m_szone.SetCurSel(j);
		}
	}
	
	*pResult = 0;
}
