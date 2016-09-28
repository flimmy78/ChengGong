// Processe.h: interface for the Processe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_)
#define AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct HWNDPID    //���ھ�������Ľ���ID
{
	HWNDPID(){memset(this,0,sizeof(HWNDPID));};
	HWND hWnd;
	DWORD dwID;
};

class CProcesse  
{
public:
	//���ҽ��̵�������
	static HWND FindProcHwnd(const char* pProcName);
	//���н���
	static BOOL RunProcess(const char* pWndName,WORD show=SW_SHOWNORMAL);
	//�򿪽��̴���
	static BOOL FindProcessID(const char* pProcName,DWORD &dwID); 
	
	CProcesse();
	virtual ~CProcesse();
	
};

//ö�ٴ��ڴ������
BOOL CALLBACK EnumCurWindowsProc(HWND hwnd,LPARAM lParam);

#endif // !defined(AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_)
