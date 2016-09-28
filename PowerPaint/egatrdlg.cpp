// egatrdlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "egatrdlg.h"
#include "comobj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;
extern gdata   dbm;
char *dtp[]={"PT","�����","����,��բ","����","����","�翹","�ӵ�","�������ѹ��","�������ѹ��","��̬�޹�������","��䡢������"};
char *stpy[]={"�����Ǳ�","�豸","��վ","����","˫ͼģ����"};
/////////////////////////////////////////////////////////////////////////////
// egatrdlg dialog


egatrdlg::egatrdlg(int cursel,CWnd* pParent /*=NULL*/)
	: CDialog(egatrdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(egatrdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	sel=cursel;
}


void egatrdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(egatrdlg)
	DDX_Control(pDX, IDC_SITESUM, m_ssum);
	DDX_Control(pDX, IDC_SUBTYPE, m_stype);
	DDX_Control(pDX, IDC_TYPE, m_type);
	DDX_Control(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(egatrdlg, CDialog)
	//{{AFX_MSG_MAP(egatrdlg)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_BN_CLICKED(IDC_ANALYSE, OnAnalyse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// egatrdlg message handlers

BOOL egatrdlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_NAME,cobj.egp[sel].name);
	for(i=0;i<4;i++){
	  m_type.AddString(stpy[i]);
	}
	for(i=0;i<11;i++){
	  m_stype.AddString(dtp[i]);
	}
	m_type.SetCurSel(cobj.egp[sel].type);
	m_stype.SetCurSel(cobj.egp[sel].subtype);
	m_ssum.SetCurSel(cobj.egp[sel].sitesum);
	m_ssum.EnableWindow(false);	
	if(cobj.egp[sel].type==1){
		m_stype.EnableWindow(true);	
	}else{
		m_stype.EnableWindow(false);
	}
	return TRUE;
}

void egatrdlg::OnSelchangeType() 
{
	int k;
	k=m_type.GetCurSel();
	cobj.egp[sel].type=k;
	if(k==1){
		m_stype.EnableWindow(true);	
	}else{
		m_stype.EnableWindow(false);
	}
}

void egatrdlg::OnAnalyse() 
{
	N_ELEGRP *el;
	el=&cobj.egp[sel];
	switch(el->type)
	{
	case 0: //�����Ǳ�
		AnalyseMeter();
		break;
	case 1: //�����豸
		Analysedev();
		break;
	default:
		MessageBox("���Ǳ���豸���������");
		break;
	}
}

void egatrdlg::OnOK() 
{
	GetDlgItemText(IDC_NAME,cobj.egp[sel].name,15);
	cobj.egp[sel].type=m_type.GetCurSel();
	cobj.egp[sel].subtype=m_stype.GetCurSel();
	CDialog::OnOK();
}


//�����豸
void egatrdlg::Analysedev()
{
	int i,j,n,type;
	char p[100];
	CDRect  art;
	BASE0 *bs[3];
	N_ELEGRP *el;
	m_msg.ResetContent();
	m_msg.AddString("��ʼ����:");
	el=&cobj.egp[sel];
	el->sitesum=0;
	cobj.egp[sel].type=m_type.GetCurSel();
	cobj.egp[sel].subtype=m_stype.GetCurSel();
	//��������0
	for(i=0;i<el->bsum1;i++){
	  el->bs1[i].attr.belong=0;
	}
	for(i=0;i<el->bsum2;i++){
	  el->bs2[i].attr.belong=0;
	}
	for(i=0;i<el->bsum1;i++){
		if(el->bs1[i].attr.type==11){ //type=11Ϊ��������
			el->bs1[i].ort.GetDRECT(el->srt[el->sitesum]);
			el->bs1[i].attr.belong=el->sitesum+1;
			el->sitesum++;
		}
	  if(el->sitesum>=3) break;
	}
	sprintf(p,"�ҵ�����%d��",el->sitesum);
	m_msg.AddString(p);
	m_ssum.SetCurSel(cobj.egp[sel].sitesum);
	
	//������Ǳ�ѹ�������˳�����
	if(cobj.egp[sel].type!=1||(cobj.egp[sel].type==1&&
		cobj.egp[sel].subtype!=7&&cobj.egp[sel].subtype!=8))
	{
		m_msg.AddString("�������");
		for(i=0;i<el->bsum1;i++){
			el->bs1[i].attr.belong=1;
		}
		for(i=0;i<el->bsum2;i++){
			el->bs2[i].attr.belong=1;
		}
		return;
	}

	//�����ཻԲ
	n=0;
	/*for(i=0;i<el->sitesum;i++){
		for(j=0;j<el->bsum1;j++){
			type=el->bs1[j].attr.type;
		 if((type==3||type==6)&&el->bs1[j].attr.belong==0){
			 art.SetDRECT(el->srt[i]);
			 art&=el->bs1[j].ort;
			 if(!art.IsRectEmpty()){
				bs[i]=&el->bs1[j];
				bs[i]->attr.belong=i+1;
				n++;
				break;
			 }
			}
		}
	}*/
	for(i=0;i<el->sitesum;i++)
	{
		//�ȷ���Բ��
		for(j=0;j<el->bsum1;j++)
		{
			type=el->bs1[j].attr.type;
			if(type==3&&el->bs1[j].attr.belong==0)
			{
				art.SetDRECT(el->srt[i]);
				art&=el->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&el->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}
	for(i=n;i<el->sitesum;i++)
	{
		//�ȷ���Բ����
		for(j=0;j<el->bsum1;j++)
		{
			type=el->bs1[j].attr.type;
		    if(type==6&&el->bs1[j].attr.belong==0)
			{
				art.SetDRECT(el->srt[i]);
				art&=el->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&el->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}
	sprintf(p,"�ҵ�����Ҫ���Բ%d��",n);
	m_msg.AddString(p);
	switch(n){
	case 0:
		strcpy(p,"���󣺱�ѹ���޶���");
		break;
	case 1:
		strcpy(p,"����һ�����ӵı�ѹ�����޷�����");
		break;
	case 2:
		strcpy(p,"����һ��2����ı�ѹ��");
		cobj.egp[sel].subtype=7;
		break;
	case 3:
		strcpy(p,"����һ��3����ı�ѹ��");
		cobj.egp[sel].subtype=8;
		break;
	}
	m_msg.AddString(p);
	m_stype.SetCurSel(cobj.egp[sel].subtype);
	if(n!=el->sitesum){
		m_msg.AddString("���Ƶ�ͼ�β�����Ҫ��!");
		return;
	}
	CDRect rt1,rt2;
	CDPoint pt1,pt2;
	//��ʼ������ɫͼ��
	for(i=0;i<el->sitesum;i++)
	{
		rt1=bs[i]->ort;
		for(j=0;j<el->bsum1;j++)
		{
			if(el->bs1[j].attr.belong==0)
			{
				rt2=el->bs1[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) el->bs1[j].attr.belong=i+1;
			}
		}
	}
	for(i=0;i<el->sitesum;i++)
	{
		rt1=bs[i]->ort;
		rt1.left--;rt1.top--;
		rt1.right++;
		rt1.bottom++;
		for(j=0;j<el->bsum2;j++)
		{
			if(el->bs2[j].attr.belong==0)
			{
				rt2=el->bs2[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) el->bs2[j].attr.belong=i+1;
			}
		}
	}
	m_msg.AddString("�豸�������...");


}
//�����Ǳ�
void egatrdlg::AnalyseMeter()
{
	int i,n;
	BYTE ind[32];
	char p[100];
	CDRect  art;
	N_ELEGRP *el;
	m_msg.ResetContent();
	m_msg.AddString("��ʼ����:");
	el=&cobj.egp[sel];
	el->sitesum=0;
	//�����Ǳ�
	n=0;
	for(i=0;i<el->bsum1;i++)
	{
		switch(el->bs1[i].attr.type)
		{
		case 32:case 33:case 34:case 35:
		ind[n]=(BYTE)i;
		n++;
		break;
		}
		if(n>=32) break;
	}
	sprintf(p,"�ҵ��Ǳ���%d��",n);
	m_msg.AddString(p);
	if(n>8)	m_msg.AddString("�Ǳ�̫�ֻ࣬ȡǰ8���Ǳ���");
	m_msg.AddString("�������������");
	n=n>8 ? 8:n;
	el->sitesum=n;
	for(i=0;i<n;i++)
	{
		el->index[i]=ind[i];
	}
	m_msg.AddString("�Ǳ�������...");
}