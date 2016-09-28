// AlmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "AlmDlg.h"
#include "dbapi.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *title[]={"��·����Ԥ���б�","���������Ԥ���б�","��ѹ������Ԥ���б�","Ԥ�������Ԥ���б�","ĸ�ߵ�ѹԤ���б�"};
/////////////////////////////////////////////////////////////////////////////
// AlmDlg dialog


AlmDlg::AlmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AlmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AlmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AlmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AlmDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AlmDlg, CDialog)
	//{{AFX_MSG_MAP(AlmDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlmDlg message handlers

BOOL AlmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//������ݿ�ƽ̨�Ƿ�����
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("���ݿ�ƽ̨δ����");	
		return false;
	}
	LSI_CheckUser("sa","");
	//��ȡʵʱ��ID��ʵ�ʹ����ַ
	GetTableID();
	GetRltDbAdd();
	SetList();
	SetWindowText(title[type]);
	return TRUE;
}

//������Ҫ�ı�ID
void AlmDlg::GetTableID()
{
	DWORD idi;
	if(LSI_GetTableID("visualpw","Gen",idi))		gid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Tfm1",idi))		t1id=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Tfm2",idi))		t2id=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Bus",idi))		bid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Line",idi))		lid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","DCLine",idi))		dlid=LOWORD(idi);
	if(LSI_GetTableID("common","PreDefSF",idi))		pdid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","SysAlarm",idi))	almid=LOWORD(idi);	
}

void * AlmDlg::GetTblAdd(int tid,int &n,MEMTABLE **mm)
{
	MEMTABLE *tbl;
	n=0;
	if(tid==-1) return NULL;
	tbl=(MEMTABLE *)LSI_GetTableAdd(tid);
	if(tbl==NULL) return NULL; 
	n=tbl->userec;//ȡ�����ݿ��еļ�¼��
	*mm=tbl;
	return tbl->data;
}
//�������ݿ��ַ
void AlmDlg::GetRltDbAdd()
{
	gen=(visualpw_Gen  *)GetTblAdd(gid,gsum,&mgen);
	tfm1=(visualpw_Tfm1  *)GetTblAdd(t1id,tsum1,&mtf1);
	tfm2=(visualpw_Tfm2  *)GetTblAdd(t2id,tsum2,&mtf2);
	bus=(visualpw_Bus  *)GetTblAdd(bid,bsum,&mbus);
	line=(visualpw_Line  *)GetTblAdd(lid,lsum,&mlin);
	dcline=(visualpw_DCLine  *)GetTblAdd(dlid,dlsum,&mdlin);
	pdf=(common_PreDefSF  *)GetTblAdd(pdid,pdsum,&mpdf);
	alm=(visualpw_SysAlarm *)GetTblAdd(almid,amsum,&malm);
}

void AlmDlg::SetList()
{
	switch(type)
	{
	case 0: //��·
		SetLine();
		break;
	case 1: //�����
		SetGen();
		break;
	case 2: //��ѹ��
		SetTran();
		break;
	case 3: //����
		SetDM();
		break;
	case 4: //ĸ��
		SetBus();
		break;
	}

}


//������·
void AlmDlg::SetLine()
{
	int i,n;
	char p[100];
	double a,b;
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"��  ��",LVCFMT_LEFT,140,0);
	m_lst.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(2,"�й�(MW)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(3,"�޹�(MVar)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(4,"����(A)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(5,"����(MVA)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(6,"������%",LVCFMT_RIGHT,60,0);
	n=0;
    //�ȿ�����
	for(i=0;i<lsum;i++)
	{
		if(line[i].alarm==0) continue;
		m_lst.InsertItem(n,line[i].Name);
		sprintf(p,"%d",line[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",line[i].Pf);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",line[i].Qf);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",line[i].I);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",line[i].MaxP);
		m_lst.SetItemText(n,5,p);
		b=sqrt(line[i].Pf*line[i].Pf+line[i].Qf*line[i].Qf);
		if(line[i].MaxP!=0) a=b/line[i].MaxP;
		else a=0;
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,6,p);
	}
	//�ڿ�ֱ��
	for(i=0;i<dlsum;i++)
	{
		if(dcline[i].alarm==0) continue;
		m_lst.InsertItem(n,dcline[i].Name);
		sprintf(p,"%d",dcline[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",dcline[i].Pf);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",dcline[i].Qf);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",dcline[i].I);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",dcline[i].Maxp);
		m_lst.SetItemText(n,5,p);
		b=sqrt(dcline[i].Pf*dcline[i].Pf+dcline[i].Qf*dcline[i].Qf);
		if(dcline[i].Maxp!=0) a=b/dcline[i].Maxp;
		else a=0;
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,6,p);
	}
}

//���÷����
void AlmDlg::SetGen()
{
	int i,n;
	char p[100];
	double a,b;
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"��  ��",LVCFMT_LEFT,140,0);
	m_lst.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(2,"�й�(MW)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(3,"�޹�(MVar)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(4,"����(MW)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(5,"����(MW)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(6,"������%",LVCFMT_RIGHT,60,0);
	n=0;
    //�ȿ�����
	for(i=0;i<gsum;i++)
	{
		if(gen[i].alarm==0) continue;
		m_lst.InsertItem(n,gen[i].Name);
		sprintf(p,"%d",gen[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",gen[i].P);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",gen[i].Q);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",gen[i].Pchk);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",gen[i].MaxP);
		m_lst.SetItemText(n,5,p);
		b=gen[i].MaxP-gen[i].Pchk;
		if(b!=0) a=gen[i].P/b;
		else a=0;
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,6,p);
	}
	
}

//���ñ�ѹ��
void AlmDlg::SetTran()
{
	int i,n;
	char p[100];
	double a,b;
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"��  ��",LVCFMT_LEFT,140,0);
	m_lst.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(2,"�й�(MW)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(3,"�޹�(MVar)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(4,"����(A)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(5,"����(MVA)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(6,"������%",LVCFMT_RIGHT,60,0);
	n=0;
    //�ȿ�2�Ʊ�
	for(i=0;i<tsum1;i++)
	{
		if(tfm1[i].alarm==0) continue;
		m_lst.InsertItem(n,tfm1[i].Name);
		sprintf(p,"%d",tfm1[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",tfm1[i].P);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",tfm1[i].Q);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",tfm1[i].I);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",tfm1[i].Pmax);
		m_lst.SetItemText(n,5,p);
		b=sqrt(tfm1[i].P*tfm1[i].P+tfm1[i].Q*tfm1[i].Q);
		if(tfm1[i].Pmax!=0) a=b/tfm1[i].Pmax;
		else a=0;
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,6,p);
	}
	//�ȿ�2�Ʊ�
	for(i=0;i<tsum2;i++)
	{
		if(tfm2[i].alarm==0) continue;
		m_lst.InsertItem(n,tfm2[i].Name);
		sprintf(p,"%d",tfm2[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",tfm2[i].P);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",tfm2[i].Q);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",tfm2[i].I);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",tfm2[i].Pmax);
		m_lst.SetItemText(n,5,p);
		b=sqrt(tfm2[i].P*tfm2[i].P+tfm2[i].Q*tfm2[i].Q);
		if(tfm2[i].Pmax!=0) a=b/tfm2[i].Pmax;
		else a=0;
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,6,p);
	}
}


//����һ������ĸ澯
void AlmDlg::ComputDmAlm(DMLS*dl,int num,float &pl,float &ql,float &pqs)
{
	int i;
	float p,q;
	double pz,qz,psum,ps;
	pz=0;
	qz=0;
	psum=0;
	for(i=0;i<num;i++)
	{
		if(!GetLineDataPQ(p,q,dl[i].id,dl[i].type)) continue;
		pz+=p;
		qz+=q;
		ps=sqrt(p*p+q*q);
		psum+=ps;
	}
	pl=(float)pz;
	ql=(float)qz;
	pqs=(float)psum;
}


//������·��P,Qֵ
bool AlmDlg::GetLineDataPQ(float &Pcur,float &Qcur,int id,int type)
{
	int i;
	switch(type)
	{
	case 0://����
		for(i=0;i<lsum;i++)
		{
			if(id==(int)line[i].NU)
			{
				Pcur=line[i].Pf;
				Qcur=line[i].Qf;
				return true;
			}
		}
		break;
	case 1: //ֱ��
		for(i=0;i<dlsum;i++)
		{
			if(id==(int)dcline[i].NU)
			{
				Pcur=dcline[i].Pf;
				Qcur=dcline[i].Qf;
				return true;
			}
		}
		break;
	case 2: //���Ʊ�
		for(i=0;i<tsum2;i++)
		{
			if(id==(int)tfm2[i].NU)
			{
				Pcur=tfm2[i].P;
				Qcur=tfm2[i].Q;
				return true;
			}
		}
		break;
	}
	return true;
}

//���ö���
void AlmDlg::SetDM()
{
	int i,n,m;
	DMLS *dl;
	char *lp;
	float p,q,ps;
	char str[100];
	double a;
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"��  ��",LVCFMT_LEFT,140,0);
	m_lst.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(2,"�й�(MW)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(3,"�޹�(MVar)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(4,"����(MVA)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(5,"����(MVA)",LVCFMT_RIGHT,80,0);
	m_lst.InsertColumn(6,"������%",LVCFMT_RIGHT,60,0);
	n=0;
    //�ȿ�����
	for(i=0;i<pdsum;i++)
	{
		if(pdf[i].alarm==0) continue;
		lp=pdf[i].DevID+2;
		m=pdf[i].Nline;
		dl=(DMLS*)lp;
		ComputDmAlm(dl,m,p,q,ps);
		m_lst.InsertItem(n,pdf[i].Name);
		sprintf(str,"%d",pdf[i].ID);
		m_lst.SetItemText(n,1,str);
		sprintf(str,"%2.2f",p);
		m_lst.SetItemText(n,2,str);
		sprintf(str,"%2.2f",q);
		m_lst.SetItemText(n,3,str);
		sprintf(str,"%2.2f",ps);
		m_lst.SetItemText(n,4,str);
		sprintf(str,"%2.2f",pdf[i].Vmax);
		m_lst.SetItemText(n,5,str);
		if(pdf[i].Vmax!=0) a=ps/pdf[i].Vmax;
		else a=0;
		sprintf(str,"%2.2f",a*100);
		m_lst.SetItemText(n,6,str);
	}
}


//����ĸ��
void AlmDlg::SetBus()
{
	int i,n;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"��  ��",LVCFMT_LEFT,140,0);
	m_lst.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(2,"��ѹ����ֵ",LVCFMT_RIGHT,100,0);
	m_lst.InsertColumn(3,"��ѹ����ֵ(KV)",LVCFMT_RIGHT,100,0);
	m_lst.InsertColumn(4,"����(KV)",LVCFMT_RIGHT,60,0);
	m_lst.InsertColumn(5,"����(KV)",LVCFMT_RIGHT,80,0);
	n=0;
    //�ȿ�����
	for(i=0;i<bsum;i++)
	{
		if(bus[i].alarm==0) continue;
		m_lst.InsertItem(n,bus[i].Name);
		sprintf(p,"%d",bus[i].NU);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",bus[i].V);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",bus[i].Vb);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",bus[i].MaxV);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",bus[i].MinV);
		m_lst.SetItemText(n,5,p);
	}
}
