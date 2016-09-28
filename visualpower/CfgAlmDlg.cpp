// CfgAlmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "CfgAlmDlg.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *alnm[]={"�����·Ԥ��","�����Ԥ��","��ѹ��Ԥ��","Ԥ�������Ԥ��","ĸ�ߵ�ѹԤ��","ACEԤ��","�ظ�ѹ����"};

char *lmtnm[]={"Ԥ����ϵͳ","�����","������·","ֱ����·","2�Ʊ�","3�Ʊ�","����"};
double lmtv[]={48,99,99,99,99,99,99,99};

extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// CCfgAlmDlg dialog


CCfgAlmDlg::CCfgAlmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgAlmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgAlmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(lmt,0,7*sizeof(common_PreLimit));
}


void CCfgAlmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgAlmDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgAlmDlg, CDialog)
	//{{AFX_MSG_MAP(CCfgAlmDlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_SOUND, OnSound)
	ON_BN_CLICKED(IDC_POP, OnPop)
	ON_BN_CLICKED(IDC_FLASH, OnFlash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgAlmDlg message handlers

BOOL CCfgAlmDlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	rrd.SetCurDbf(0);
	lmtsum=rrd.ReadLimit(lmt,7);
	for(i=0;i<5;i++) m_lst.AddString(alnm[i]);
	cursel=0;
	SetCurAalm();
	m_lst.SetCurSel(0);
	for(i=0;i<7;i++)
	{
		lmt[i].ID=i+1;
		strcpy(lmt[i].Name,lmtnm[i]);
		if(lmtsum<7) lmt[i].Value=(float)lmtv[i];
	}
	SetParam();
	return TRUE; 
}

void CCfgAlmDlg::SetCurAalm()
{
	int i=cursel;
	CheckDlgButton(IDC_SOUND,tmp.cfg[i].sound);
	CheckDlgButton(IDC_POP,tmp.cfg[i].pop);
	CheckDlgButton(IDC_FLASH,tmp.cfg[i].flash);
}

void CCfgAlmDlg::OnSelchangeList1() 
{
	int i=m_lst.GetCurSel();
	if(i==LB_ERR) return;
	cursel=i;
	SetCurAalm();
}

//���ñ仯
void CCfgAlmDlg::OnSound() 
{
	SetChange();
	
}

void CCfgAlmDlg::OnPop() 
{
	SetChange();
	
}

void CCfgAlmDlg::OnFlash() 
{
	SetChange();
}


void CCfgAlmDlg::SetChange()
{
	int i;
	if(cursel<0||cursel>6) return;
	i=cursel;
	tmp.cfg[i].pop=IsDlgButtonChecked(IDC_POP);
	tmp.cfg[i].flash=IsDlgButtonChecked(IDC_FLASH);
	tmp.cfg[i].sound=IsDlgButtonChecked(IDC_SOUND);
}


//char *lmtnm[]={"ACE","�����","ֱ����·","������·","2�Ʊ�","3�Ʊ�","����"};

void CCfgAlmDlg::SetParam()
{
	char p[100];
	/*sprintf(p,"%2.2f",lmt[0].Value);
	SetDlgItemText(IDC_ACE,p);*/
	sprintf(p,"%2.2f",lmt[1].Value);
	SetDlgItemText(IDC_GEN,p);
	sprintf(p,"%2.2f",lmt[2].Value);
	SetDlgItemText(IDC_LINE,p);
	sprintf(p,"%2.2f",lmt[3].Value);
	SetDlgItemText(IDC_DCLINE,p);
	sprintf(p,"%2.2f",lmt[4].Value);
	SetDlgItemText(IDC_TFM1,p);
	sprintf(p,"%2.2f",lmt[5].Value);
	SetDlgItemText(IDC_TFM2,p);
	sprintf(p,"%2.2f",lmt[6].Value);
	SetDlgItemText(IDC_DM,p);
}

void CCfgAlmDlg::GetParam()
{
	char p[100];
	/*GetDlgItemText(IDC_ACE,p,10);
	lmt[0].Value=(float)atof(p);*/

	lmt[0].Value=0;
	GetDlgItemText(IDC_GEN,p,10);
	lmt[1].Value=(float)atof(p);

	GetDlgItemText(IDC_LINE,p,10);
	lmt[2].Value=(float)atof(p);

	GetDlgItemText(IDC_DCLINE,p,10);
	lmt[3].Value=(float)atof(p);

	GetDlgItemText(IDC_TFM1,p,10);
	lmt[4].Value=(float)atof(p);

	GetDlgItemText(IDC_TFM2,p,10);
	lmt[5].Value=(float)atof(p);

	GetDlgItemText(IDC_DM,p,10);
	lmt[6].Value=(float)atof(p);

}

//�����˳�
void CCfgAlmDlg::OnOK() 
{
	GetParam();
	rrd.WriteLimit(lmt,7);
	//��������
	SaveCfg();
	CDialog::OnOK();
}


void CCfgAlmDlg::SaveCfg()
{
	FILE *fp;
	char name[256];
	sprintf(name,"%s\\%s",cobj.startpath,"almpara.cfg");
	fp=fopen(name,"w+b");
	if(fp==NULL) return;
	tmp.flag=0xd0d0;
	fwrite(&tmp,sizeof(ALMSAVE),1,fp);
	fclose(fp);
}
