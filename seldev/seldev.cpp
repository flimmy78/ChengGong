// seldev.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "seldev.h"
#include "mstruct.h"
#include "selanldlg.h"
#include "sglvDlg.h"
#include "stadlg.h"
#include "szonedlg.h"
#include "SelDVDlg.h"
#include "ZoneDlg.h"
#include "stationdlg.h"
#include "SelPie.h"
#include "selrevdlg.h"
#include "defdmdlg.h"
#include "almdlg.h"
#include "YbSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool GetDevNameByID(SELECTDEV&dev);
bool GetDevIDByName(SELECTDEV&dev);

/////////////////////////////////////////////////////////////////////////////
//				����������ѡ���豸����Դ
//				��̣��½� 2004.10.18
//
/////////////////////////////////////////////////////////////////////////////
// CSeldevApp

BEGIN_MESSAGE_MAP(CSeldevApp, CWinApp)
	//{{AFX_MSG_MAP(CSeldevApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeldevApp construction

CSeldevApp::CSeldevApp()
{
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSeldevApp object


CSeldevApp theApp;

//ѡ��һ������ģ������ʾ���豸������ʾ������
//�����������

bool WINAPI SelAnlSHow(SELDATA_DEV &indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	SelAnlDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//ѡ��һ����ֵ����ԴSELSINGLE_DEV;
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	SglVDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//ѡ��һ����ֵ����ԴSELSINGLE_DEV;
bool WINAPI SelDevSta(SELSINGLE_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	StaDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}


//ѡ��һ����ͼ����;
bool WINAPI SelPie(SELECTPIE&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	CSelPie dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//ѡ��һ����������������ʾ;
bool WINAPI SelZone(SELDATA_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	SZoneDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}
//����һ���豸
bool WINAPI  Select_device(SELECTDEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	SelDVDlg dlg;
	dlg.sd=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.sd;
		return true;
	}
	return false;
}

//ѡ��һ��ˮ��;
bool WINAPI SelReservoir(SELRESERVOIR&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	SelRevDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}



//���ö���;
bool WINAPI CfgSect()
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	DefdmDlg dlg;
	if(dlg.DoModal()==IDOK){
		return true;
	};
	return false;
}

//��ʾ�澯��Ϣ
void WINAPI ShowAlarm(int type)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	AlmDlg dlg;
	dlg.type=type;
	dlg.DoModal();
}


//��ʾ�Ǳ���Ϣ
bool WINAPI SelYbDbs(SINGLEDBS&meter)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //���б���
	YbSelDlg dlg;
	dlg.tmp=meter;
	if(dlg.DoModal()==IDOK){
		meter=dlg.tmp;
		return true;
	}
	return false;
}


//����һ���豸
bool WINAPI  GetNameByID(SELECTDEV&dev)
{
	return GetDevNameByID(dev);
}

//����һ���豸
bool WINAPI  GetIDByName(SELECTDEV&dev)
{
	return GetDevIDByName(dev);
}

BOOL CSeldevApp::InitInstance() 
{
	
	::CoInitialize(NULL); 
	return CWinApp::InitInstance();
}

int CSeldevApp::ExitInstance() 
{
	
	::CoUninitialize();
	return CWinApp::ExitInstance();
}


