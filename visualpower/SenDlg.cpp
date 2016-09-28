// SenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SenDlg.h"
#include "comobj.h"
#include "middll.h"
#include "bclass.h"
#include "DObj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *typestr[]={"����������:\n������͸��ɶ���·�������ȡ�",
"����������:\n��������������ͱ�ѹ���Խڵ��ѹ�������ȡ�"};

extern comobj  cobj;
/////////////////////////////////////////////////////////////////////////////
// SenDlg dialog

SenDlg::SenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	type=0;
	hpr=0;
	selpt.x=0;
	selpt.y=0;
}
SenDlg::~SenDlg()
{
	KillTimer(100);
}

void SenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SenDlg)
	DDX_Control(pDX, IDC_SENTYPE, m_type);
	DDX_Control(pDX, IDC_PROGRESS1, m_prg);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SenDlg, CDialog)
	//{{AFX_MSG_MAP(SenDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SenDlg message handlers

BOOL SenDlg::OnInitDialog() 
{
	char p[100];
	CDialog::OnInitDialog();
	
	//��ȡѡ����豸ID��
	if(type>=0&&type<2) m_type.SetWindowText(typestr[type]);
	switch(type)
	{
	case 0: //��·
		ComputeBra();
			break;
	case 1:
		ComputeBus();
		break;
	}
	if(id==-1){
		MessageBox(str,"������ѡ�����",MB_ICONSTOP);
		CDialog::OnCancel();
		return false;
	}
	if(type==0&&id>=0)
	{
		nodefrom=ReadLineNodeFrom(); //��ȡ��·��ʼ�ڵ�
		id=NT_GetDevID(id,2);
		if(nodefrom==-1){
			sprintf(p,"��%s��·�����ݿ��в����ڣ�\n����֤���ݿ��еĸ�����¼��",type==0 ? "����":"ֱ��");
			MessageBox(p,"����",MB_ICONSTOP);
			CDialog::OnCancel();
			return false;
		}
	}
	//��ʾʾʱ�ã���ʽ�汾��������ȥ��
	//CDialog::OnOK();
	//return true;
	
	
	
	StartRun();
	return TRUE; 
}

void SenDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==100)	CheckCompute();
	CDialog::OnTimer(nIDEvent);
}

void SenDlg::OnCancel() 
{
	KillTimer(100);
	CDialog::OnCancel();
}

//�����ཻĸ��
void SenDlg::ComputeBra()
{
	int i,j,n,rtn;
	CRect rt;
	POINT pt1[20],ptt;
	HRGN hrgn1,hrgn2;
	CDPoint apt;
	id=-1;
	name[0]=0;
	hrgn1=SCreateLineRGN(pt,ptsum);
	hrgn2=NULL;
	for(i=0;i<fwsum;i++){
		n=r_fw[i].ptsum;
		n=n>20 ? 20:n;
		for(j=0;j<n;j++){
			pt1[j].x=(int)((double)(r_fw[i].flw->pt[j].x*dbm->curzoom));
			pt1[j].y=(int)((double)(r_fw[i].flw->pt[j].y*dbm->curzoom));
		}
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=SCreateLineRGN(pt1,n);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){
			id=r_fw[i].flw->did;
			strcpy(name,r_fw[i].flw->dev_name);
			linetype=r_fw[i].flw->type;
			GetRgnBox(hrgn2,&rt);
			ptt=rt.CenterPoint();
			apt.x=(double)ptt.x;
			apt.y=(double)ptt.y;
			apt.ScrPtToAct(dbm->curzoom);
			selpt.x=apt.x;
			selpt.y=apt.y;
			break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
	if(id!=-1) sprintf(str,"ѡ�����·:��·id=%d  ��·��=%s",id,name);
	else strcpy(str,"û��ѡ����·,������ѡ��");
	m_dev.SetWindowText(str);
}

//�����ཻĸ�ߣ��ڵ㣩
void SenDlg::ComputeBus()
{
	int id1;
	HRGN hrgn1,hrgn2;
	CDRect art;
	CRect crt;
	int i,rtn;
	id=-1;
	id1=-1;
	name[0]=0;
	hrgn1=SCreateLineRGN(pt,ptsum);
	hrgn2=NULL;
	for(i=0;i<bssum;i++){
		art=CreateDrawNRt(4,r_bs[i].bus->pt,dbm->curzoom);
		art.GetRECT(crt);
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=CreateRectRgn(crt.left,crt.top,crt.right,crt.bottom);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){
			id1=r_bs[i].bus->did;
			id=NT_GetDevID(id1,1);
			strcpy(name,r_bs[i].bus->dev_name);
			selpt=r_bs[i].bs->ort.CenterPoint();
			break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
	if(id!=-1) sprintf(str,"ѡ���ĸ��:ĸ��id=%d  ĸ����=%s",id,name);
	else if(id1>=0) strcpy(str,"����û��ѡ�񵽵�ĸ��,������ѡ��!");
	else strcpy(str,"û��ѡ��ĸ��,������ѡ��!");
	m_dev.SetWindowText(str);
}


//��ȡ��·��ʼ�ڵ�
int SenDlg::ReadLineNodeFrom()
{
	int nf,nt;
	LinData  acdata;//����
	DLinData dcdata;//ֱ��
	switch(linetype){
	case 0: //����
		memset(&acdata,0,sizeof(LinData));
		acdata.lid=id;
		NT_GetDevBusID(id,2,nf,nt);
		return nf;
	case 1: //ֱ��
		memset(&dcdata,0,sizeof(DLinData));
		dcdata.lid=id;
		NT_GetDevBusID(id,2,nf,nt);
		return nf;
	}
	return -1;
}


//��ʼ����
void SenDlg::StartRun()
{
	PROCESS_INFORMATION li;
	STARTUPINFO  st;
	//������Ŀ¼(����Ϊ����Ŀ¼)
	SetCurrentDirectory(cobj.startpath);
	//���ACSOPF02.EXE�Ƿ����
	if(!cobj.IsFileExist("ACSOPF02.exe"))
	{
		MessageBox("acsopf02.exe��������ļ������ڣ����ܽ��������ȼ��㣡","����",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	//������׼���������ع���
	//����DAT�ļ�
	NT_CreateDAT("tmp.dat");
	//���ɺ��ļ�
	CreateMacFile("tmp.mac");
	//2.ִ�м���
	memset(&li,0,sizeof(PROCESS_INFORMATION));
	memset(&st,0,sizeof(STARTUPINFO));
	st.cb=sizeof(STARTUPINFO);
	st.wShowWindow=SW_HIDE;
	st.dwFlags=STARTF_USESHOWWINDOW;
	CreateProcess(NULL,"CMD.EXE /c ACSOPF02.exe<tmp.mac",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	hpr=(HANDLE)li.hProcess;
	nt=0;
	m_prg.SetRange(0,100);
	SetTimer(100,150,NULL);
}


extern char *lsenstr[];
extern char *nsenstr[];
//���ɺ��ļ�
void SenDlg::CreateMacFile(char *filename)
{
	FILE *fp;
	fp=fopen(filename,"w+t");
	if(fp==NULL) return;
	switch(type)
	{
	case 0: //��·
		fprintf(fp,"%s",lsenstr[0]);
		fprintf(fp,"%d\n",nodefrom);
		fprintf(fp,"%d\n",id);
		fprintf(fp,"%s",lsenstr[3]);
		break;
	case 1: //�ڵ�
		fprintf(fp,"%s",nsenstr[0]);
		fprintf(fp,"%d\n",id);
		fprintf(fp,"%s",nsenstr[2]);
		break;
	}
	fclose(fp);
}


//�쿴�����Ƿ�������
bool SenDlg::IsProcessActive()
{
	DWORD ex;
	if(hpr==0) return false;
	int b=GetExitCodeProcess(hpr,&ex);
	if(b==0) return false;
	if(b==1&&ex==0) return false;
	return true;
}
//����������Ƿ��ڽ���
void SenDlg::CheckCompute()
{
	nt+=12;
	if(nt>60) nt=60;
	m_prg.SetPos(nt);
	if(IsProcessActive()) return; //��ʾ��������
	KillTimer(100);
	//��������ת��
	//1.������������
	if(NT_FileConvertInput("CONVERGE.OUT")!=0)//������
	{ 
		MessageBox("��������������\n������ص������ݿ��ʵʱ�����Ƿ���ȷ��","����",MB_ICONSTOP);	
		SaveDataFile();
		CDialog::OnCancel();
		return;
	}
	m_prg.SetPos(80);
	if(!cobj.IsFileExist("tmp.out"))
	{
		MessageBox("û�в����������ļ������ܵõ������Ƚ����\n�������ݿ��Ƿ���ȷ��","����",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	if(NT_FileOutInput("tmp.out",type)!=0)
	{
		MessageBox("������ת������\n�������ݿ��Ƿ���ȷ��","����",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	m_prg.SetPos(100);
	CDialog::OnOK();
}

//��������������ʱ����data�ļ�
void SenDlg::SaveDataFile()
{
	char desnm[512];
	CTime tm=CTime::GetCurrentTime();
	sprintf(desnm,"%s\\sen_%d��%d��%d��%d��%d��%d��.dat",cobj.senfilepath,tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	CopyFile("tmp.dat",desnm,false);
}


