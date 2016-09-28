// SelAnlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelAnlDlg.h"
#include "dbapi.h"
#include "userapi.h"
#include "pysel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *tblnm[]={"Gen",		//�����
			   "Line",		//����
			   "DCLine",	//ֱ��
			   "Bus",		//ĸ��
			   "Load",		//����
			   "Tfm1",		//2�����ѹ��
			   "Tfm2",		//3�����ѹ��
			   "Shunt",		//����
			   "Sreact",	//�翹
			   "SVC",		//��̬�޹�����װ��
			   "Zone",		//����
			   "Grid",		//����
			   "Hvcondata", //�ظ�ѹ
			   "PreDefSF",	//Ԥ������
			   "Relation",	//��ϵ������
			   "UnEquMeas",	//���豸����
};	
char *fld[]={"intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "ID","Name"};
char *xs1[]={"��ѹ�ȼ�","��ѹ����ֵ","��ѹ����ֵ","�����ʾ"};//ĸ��
char *xs2[]={"ʼ���й����޹�","ĩ���й����޹�","����","���й�","���޹�","ĩ�й�","ĩ�й�"};//������·
char *xs3[]={"��ѹ����λ","�߶��й�","�߶��޹�","�߶˵���","�Ͷ��й�","�Ͷ��޹�","�Ͷ˵���","�ж��й�","�ж��޹�","�ж˵���"};//��ѹ��
char *xs4[]={"��ʾʼ���й�","��ʾĩ���й�","����"};//ֱ��
char *xs5[]={"Ͷ������","Ͷ������"};//����
char *xs6[]={"�й�����","�й�����","�й�����","Сʱ����"};//����
char *xs7[]={"�й�+j�޹���ʽ","�й�","�޹�"};//�����������
char *xs8[]={"ϵͳ�������й�","ϵͳ�������޹�","��ת����","����������","���й�����","���޹�����"};//����
char *xs9[]={"��ǰֵ","���ֵ","��Сֵ"};//����
/////////////////////////////////////////////////////////////////////////////
// SelAnlDlg dialog

SelAnlDlg::SelAnlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelAnlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelAnlDlg)
	//}}AFX_DATA_INIT
	num=0;
	def=NULL;
	numt=0;
	deft=NULL;
}

SelAnlDlg::~SelAnlDlg()
{
	if(def!=NULL) delete def;
	def=NULL;
	if(deft!=NULL) delete deft;
	deft=NULL;
}
void SelAnlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelAnlDlg)
	DDX_Control(pDX, IDC_XS, m_xs);
	DDX_Control(pDX, IDC_LDEV, m_ldev);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelAnlDlg, CDialog)
	//{{AFX_MSG_MAP(SelAnlDlg)
	ON_CBN_SELCHANGE(IDC_DEV, OnSelchangeDev)
	ON_EN_CHANGE(IDC_PYJS, OnChangePyjs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelAnlDlg message handlers

BOOL SelAnlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("���ݿ�ƽ̨δ����","����",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	m_dev.SetCurSel(ad.dtype);
	GetData(ad.dtype);
	SetToLst();
	m_ldev.SetCurSel(GetIndex(ad.did));
	SetXSMode();
	return TRUE;
}
//��������
void SelAnlDlg::GetData(int dtype)
{
	int i,j;
	DWORD idi;
	MEMTABLE *mtb;

	if(dtype==11){
		if(def!=NULL) delete def;
		def=NULL;
		num=0;
		return;
	}
	if(dtype<0||dtype>15) return;
	if(dtype>=13 && dtype<=15)
	{
		if(!LSI_GetTableID("common",tblnm[dtype],idi)) return;
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
	case 5: //2�Ʊ�
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 6: //���Ʊ�
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 7: //����
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 8: //�翹
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
	case 10: //����
		zon=(visualpw_Zone *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=zon[i].NU;
			strcpy(def[i].name,zon[i].Name);
		}
		break;
	case 12: //��ѹ����
		/*hvc=(visualpw_Hvcondata *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=hvc[i].ID;
			strcpy(def[i].name,hvc[i].Name1);
		}*/
		break;
	case 13: //Ԥ�������
		defsf=(common_PreDefSF *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=defsf[i].ID;
			strcpy(def[i].name,defsf[i].Name);
		}
		break;
	/*case 14: //ϵͳ
		sys=(visualpw_SysGD *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sys[i].ID;
			strcpy(def[i].name,sys[i].Name);
		}
		break;*/
	case 14: //�豸����
		rel=(common_Relation *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=rel[i].NU;
			strcpy(def[i].name,rel[i].MeasID);
		}
		break;
	case 15: //���豸����
		unequ=(common_UnEquMeas *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=unequ[i].NU;
			strcpy(def[i].name,unequ[i].Name);
		}
		break;
	}
}
//���õ��б��
void SelAnlDlg::SetToLst()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_ldev.AddString(p);
	}
}
//�������
int SelAnlDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}

void SelAnlDlg::OnSelchangeDev() 
{
	int i;
	i=m_dev.GetCurSel();
	ad.dtype=(BYTE)i;
	GetData(ad.dtype);
	SetToLst();
	m_ldev.SetCurSel(0);
	SetXSMode();
	if(ad.dtype==5 || ad.dtype==6)
		m_xs.SetCurSel(1);
	else
		m_xs.SetCurSel(0);

}

void SelAnlDlg::OnOK() 
{
	int i,n;
	ad.xsmode=m_xs.GetCurSel();
	i=m_ldev.GetCurSel();
	if(i==LB_ERR){
		if(ad.dtype==11){
			ad.did=0;
			strcpy(ad.name,"ϵͳͳ��");
		}else{
			ad.did=-1;
			strcpy(ad.name,"ûѡ���豸");
		}
		CDialog::OnOK();
		return;
	}
	if(deft!=NULL)
	{
		ad.did=deft[i].id;
		n=strlen(deft[i].name);
		n=n>23 ? 23:n;
		strncpy(ad.name,deft[i].name,n);
		ad.name[n]=0;
	}
	else
	{
		ad.did=def[i].id;
		n=strlen(def[i].name);
		n=n>23 ? 23:n;
		strncpy(ad.name,def[i].name,n);
		ad.name[n]=0;
	}
	CDialog::OnOK();
}

//������ʾģʽ
void SelAnlDlg::SetXSMode()
{
	int i;
	m_xs.ResetContent();
	switch(ad.dtype){
	case 0:
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs7[i]);
		break;
	case 1: //������·
		m_xs.EnableWindow(true);
		for(i=0;i<7;i++) m_xs.AddString(xs2[i]);
		break;
	case 2://ֱ����·
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs4[i]);
		break;
	case 3:  //�ڵ��ĸ��
		m_xs.EnableWindow(true);
		for(i=0;i<4;i++) m_xs.AddString(xs1[i]);
		break;
	case 4:  //����
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs7[i]);
		break;
	case 5:  //2�����ѹ��
		m_xs.EnableWindow(true);
		for(i=0;i<7;i++) m_xs.AddString(xs3[i]);
		break;
	case 6:  //3����
		m_xs.EnableWindow(true);
		for(i=0;i<10;i++) m_xs.AddString(xs3[i]);
		break;
	case 7:  case 8: //������ �翹��
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xs5[i]);
		break;
	case 9:
		m_xs.EnableWindow(false);
		m_xs.AddString("��̬�޹�Ͷ������");
		break;
	case 10:
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xs6[i]);
		break;
	case 11:
		m_xs.EnableWindow(true);
		for(i=0;i<6;i++) m_xs.AddString(xs8[i]);
		break;
	case 12:
		m_xs.EnableWindow(false);
		break;
	case 13://����
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs9[i]);
		break;
	case 14:
	case 15:
		m_xs.EnableWindow(false);
		m_xs.AddString("����ֵ");
		break;
	}
	m_xs.SetCurSel(ad.xsmode);
}

void SelAnlDlg::OnChangePyjs() 
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
	SetDevList();
}

void SelAnlDlg::SetDevList()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<numt;i++){
		sprintf(p,"ID:%d [%s]",deft[i].id,deft[i].name);
		m_ldev.AddString(p);
	}
}

//�豸����������
void SelAnlDlg::OrderDevByName()
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
