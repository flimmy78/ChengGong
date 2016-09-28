// StFlwDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "StFlwDlg.h"
#include "bclass.h"
#include "jhsyslibl.h"
#include "comobj.h"
#include "middll.h"
#include "dbapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;		//��������
/////////////////////////////////////////////////////////////////////////////
// StFlwDlg dialog


StFlwDlg::StFlwDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StFlwDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StFlwDlg)
	//}}AFX_DATA_INIT
	dmsum=0;
}

StFlwDlg::~StFlwDlg()
{
	
}
 
void StFlwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StFlwDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StFlwDlg, CDialog)
	//{{AFX_MSG_MAP(StFlwDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_MODIP, OnModip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StFlwDlg message handlers
HBRUSH StFlwDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR){
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xf0ffff); 
     	return (HBRUSH)B;
  	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}


BOOL StFlwDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LoadCfgS();
	AddList();
	SetDlgItemText(IDC_NAME,"�¶���");
	SetDlgItemInt(IDC_MAXP,100);
	return TRUE;  
}

void StFlwDlg::EnableItem(int id, bool enable)
{
	CWnd *wnd;
	wnd=GetDlgItem(id);
	if(wnd==NULL) return;
	wnd->EnableWindow(enable);
}
//�����Զ�������
void StFlwDlg::SaveCfgS()
{
	char name[256];
	FILE *fp;
	DMSAVE hd;
	dbm->GetSectFLwName(name);
	fp=fopen(name,"w+b");
	if(fp==NULL) return;
	hd.version=0x10;
	hd.flag=0xc0;
	hd.dmsum=(BYTE)dmsum;
	fwrite(&hd,sizeof(DMSAVE),1,fp);
	fwrite(dms,sizeof(DMSECT),dmsum,fp);
	fclose(fp);
	//�����Զ������
	LSI_SendHmiFile(name);
}
//װ���Զ����������
void StFlwDlg::LoadCfgS()
{
	char name[256];
	DMSAVE hd;
	FILE *fp;
	dmsum=0;
	dbm->GetSectFLwName(name);
	fp=fopen(name,"r+b");
	if(fp==NULL) return;
	fread(&hd,sizeof(DMSAVE),1,fp);
	if(hd.version!=0x10||hd.flag!=0xc0){ //�汾����,����
		fclose(fp);
		return;
	};
	dmsum=hd.dmsum;
	dmsum=dmsum>5 ? 5:dmsum;
	if(dmsum>0) fread(dms,sizeof(DMSECT),dmsum,fp);
	fclose(fp);
}
//���Զ����������б��
void StFlwDlg::AddList()
{
	int i;
	m_lst.ResetContent();
	for(i=0;i<dmsum;i++){
		m_lst.AddString(dms[i].name);
	}
	m_lst.SetCurSel(0);
}
//����ǰ��������Զ������
void StFlwDlg::OnAdd() 
{
	int i;
	char pm[16];
	float maxI;
	if(dmsum>=10){
		MessageBox("�û��Զ������������","����",MB_ICONSTOP|MB_OK);
		return;
	}
	GetDlgItemText(IDC_NAME,tmp.name,15);
	pm[0]=0;
	GetDlgItemText(IDC_MAXP,pm,15);
	maxI=(float)atof(pm);
	if(maxI<=0)
	{
		MessageBox("��������������һ������0�����֡�\n����������һ�����֣�","����",MB_ICONSTOP|MB_OK);
		return;
	}
	tmp.Imax=maxI;
	for(i=0;i<dmsum;i++){
		if(strcmp(tmp.name,dms[i].name)==0){
			MessageBox("�û��Զ�������Ѱ���������档\n����������һ�����֣�","����",MB_ICONSTOP|MB_OK);
			return;
		}
	}
	i=dmsum;
	dms[i]=tmp;
	i++;
	dmsum=i;
	AddList();
}

void StFlwDlg::OnDelete() 
{
	int i,n;
	n=m_lst.GetCurSel();
	if(n==LB_ERR) return;
	if(dmsum<=0)  return;
	if(MessageBox("ȷʵҪɾ���ö�����","��ʾ",MB_YESNO)!=IDYES) return;
	for(i=n;i<dmsum-1;i++){
		dms[i]=dms[i+1];
	}
	dmsum--;
	
	AddList();
}

void StFlwDlg::OnOK() 
{
	SaveCfgS();
	CDialog::OnOK();
}

void StFlwDlg::OnSelchangeList1() 
{
	int i;
	char p[100];
	i=m_lst.GetCurSel();
	if(i==LB_ERR) return;
	if(i<0||i>=dmsum) return;
	sprintf(p,"%2.2f",dms[i].Imax);
	SetDlgItemText(IDC_MAXP1,p);
}

void StFlwDlg::OnModip() 
{
	int i;
	char p[100];
	float maxp;
	i=m_lst.GetCurSel();
	if(i==LB_ERR) return;
	if(i<0||i>=dmsum) return;
	GetDlgItemText(IDC_MAXP1,p,16);
	maxp=(float)atof(p);
	if(maxp<=0)
	{
		MessageBox("��������������һ������0�����֡�\n����������һ�����֣�","����",MB_ICONSTOP|MB_OK);
		return;
	}
	dms[i].Imax=maxp;
	MessageBox("�Ѹ��Ķ���������");
}
