#if !defined(AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_)
#define AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// clisock.h : header file
//
#include <winsock2.h>
#define WSA_VERSION  0x101
#define WSA_ASYNC    WM_USER+1
#define MAXIN        64000 //���ݰ���С
#define RECDATA      1000  //����������ʱ�������յ�����Ϣ
#define SVRCLOSE     1101  //�������ر� 

typedef struct _DATAHEAD{
  char  flag1;              //��־=0x78
  WORD  len;                //����<MAXIN ���ݿ���ֽ���
  unsigned char compress:1; //ѹ����־ 0=δѹ�� 1=ѹ��
  unsigned char reserved:7; //δ�ã�����
  char  check;              //У�飺����
}DATAHEAD;

typedef struct NETBUFFC{ //���������嵥����
  BYTE   level;			//��������0,1,2,3
  DWORD  len;			//�ֽ���
  char   *buf;			//������
}NETBUFFC;

/////////////////////////////////////////////////////////////////////////////
// clisock window

class clisock : public CWnd
{
// Construction
public:
	clisock();
	int nAdapter;       //������
	in_addr ad[6];		//������ַ
	char connect_svr;
	char netstatus;
	int curnet;			//��ǰ���ӵ�������
// Attributes
public:
	char *GetRecBuf(DWORD &n);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(clisock)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int  GetData(char *buf,int n);
	int  senddata(char *buf,int len);
	void slogout();
	int  ReInitNet(in_addr laddr);   //���³�ʼ������
    virtual ~clisock();
	int Connect(in_addr laddr,WORD port);
	// Generated message map functions
protected:
	//{{AFX_MSG(clisock)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void rechead();
	BOOL Enumerate();
	void recdata();
	int  SendToNet(char *buf, int len);
	void SendBuffer();
	void DeleteNbuff(int j);
	bool AddToBuff(char *buf, int len,int level);
	int  onWSAEvent(UINT wParam,LONG lParam);
	NETBUFFC  nbuf[1024];		//���ͻ���
	int       bsum;				//��Ч��������
	char sbuffer[MAXIN+10];		//����������
	char rbuffer[MAXIN+10];     //����������
	int  dlen; 					//�����ܳ���
    int  rlen;                  //�Ѷ������ֽ���
	char hbuf[10];              //����ͷ���ջ�����
	char recflag;               //�ѽ��յ�ͷ��־
	HWND r_hWnd;                //������Ĵ��ھ��
    SOCKADDR_IN sd,svradd;
    SOCKET  sid;
    WSADATA wsadata;
    LPSTR IPAddrStr;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_)
