// ChooseCase.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ChooseCase.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CChooseCaseApp

BEGIN_MESSAGE_MAP(CChooseCaseApp, CWinApp)
	//{{AFX_MSG_MAP(CChooseCaseApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseCaseApp construction

CChooseCaseApp::CChooseCaseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CChooseCaseApp object

CChooseCaseApp theApp;
BOOL threadQuit;


BOOL CChooseCaseApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetDialogBkColor(RGB(241,254,253));
	return CWinApp::InitInstance();
}

//���ذ汾��F1
int WINAPI DfGetVer()
{
	return 2009;
}

//�༭̬��ʾ��ͼ��F2
void WINAPI DfDrawDemo(HDC hdc,RECT rt,DWORD style,char *buf)
{
	CDC dc;
	dc.Attach(hdc);
	dc.DrawEdge(&rt,EDGE_ETCHED,BF_RECT);
	dc.TextOut(rt.right/2, rt.bottom/2, "ѡ���г���2015");
	dc.Detach();
}

//��ʼ��F3
void* WINAPI DfInit(HWND hWndParent,HWND &hw,RECT rt,int nID,DWORD style,char *buf)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CMainFrame* pFram=new CMainFrame();
	if(pFram != NULL)
	{
		if(!pFram->Create(NULL, "", WS_CHILD|WS_BORDER|WS_VISIBLE,rt,
			CWnd::FromHandle(hWndParent), nID))
		{
			return NULL;
		}
		CWnd* pWnd=CWnd::FromHandle(hWndParent);
		CFont* pFont=pWnd->GetFont();
		pFram->SetFont(pFont);
		
		hw=pFram->GetSafeHwnd();
		pFram->ShowWindow(SW_SHOW);
	}
	
	return pFram;
}

//�ر��˳�F4
void WINAPI DfClose(void *rc)
{
	//	ReleaseAreaStatDB();
	threadQuit = FALSE;
	Sleep(1000);
	CMainFrame* pFram=(CMainFrame*)rc;
	if(pFram!=NULL)
		delete pFram;
	pFram=NULL;
}

//����F5
void WINAPI DfAbout()
{
	MessageBox(0,"����һ���������з�ʽ�������������ؼ�\n���������ؼ�2.01��ģ��","���ڱ༭̬",MB_OK);
}

//��������F6
void WINAPI DfSetParam(DWORD &style,char *buf)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

//װ��˵�F7
HMENU WINAPI DfLoadMenu()
{
	return NULL;
}


void* GetRealRecords(char *table,MEMTABLE** pMem,char *db)
{
	DWORD idi;
	if(!LSI_GetTableID(db,table,idi)) return NULL;
	(*pMem)=(MEMTABLE *)LSI_GetTableAdd(LOWORD(idi));
	if((*pMem)==NULL)
	{
		return NULL;
	}
//	recn=(*pMem)->userec;
//	if(recn==0)
//		return NULL;
	
	return (*pMem)->data;
}

//��ѯ��¼
void* QueryRecord(char* pszTable, char* pszWhere,int &num,char* pszDB)
{
	if(pszDB==NULL || pszTable==NULL)
		return FALSE;
	
	num=0;
	void* pReturn=NULL;
	if(pszWhere!=NULL)
	{
		//char chSql[256];	
		//sprintf(chSql,"TABLE(%s.%s),WHERE(%s)",pszDB,pszTable,pszWhere);
		
		//TABLE(���ݿ���.����)��WHERE(����=XXX)
		int error;
		char* pRec=(char*)LSI_QueryRecord(pszWhere,num,error,TRUE);
		pReturn=(void*)(pRec+num*2*sizeof(char));
	}
	else
	{
		DWORD idi;
		MEMTABLE *mtb;
		if(!LSI_GetTableID(pszDB,pszTable,idi)) return 0;
		int addr=LOWORD(idi);
		mtb=(MEMTABLE *)LSI_GetTableAdd(addr);
		if(mtb!=NULL)
		{
			num=mtb->userec;
			pReturn=mtb->data;
		}
	}
	return pReturn;
}

//�޸ļ�¼
BOOL UpdateRecord(char* pszTable, char* pszWhere,void* pRecVal,char* pszDB)
{
	if(pszDB==NULL || pszTable==NULL || pRecVal==NULL)
		return FALSE;
	
	//	char chSql[256];	
	//	sprintf(chSql,"TABLE(%s.%s),WHERE(%s)",pszDB,pszTable,pszWhere);
	
	int recno=LSI_GetFirstRecno(pszWhere);
	if(recno>=0)//�޸�
	{
		char chUpdate[256];	
		sprintf(chUpdate,"%s.%s",pszDB,pszTable);
		LSI_UpdateARecord(chUpdate, pRecVal, recno);
		//	DWORD dwtid=0;
		//	if(LSI_GetTableIDExt(chUpdate,dwtid))
		//		LSI_SetChanged(dwtid,recno);
		return TRUE;
	}
	return FALSE;
}