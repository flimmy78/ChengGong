// clisock.cpp : implementation file
//

#include "stdafx.h"
#include "clisock.h"
#include <memory.h>
#include "jhdclib3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// clisock

clisock::clisock()
{
	//��ʼ������
	netstatus=0;
	connect_svr=0;
    sid=INVALID_SOCKET;
    rlen=0;
    dlen=0;
	recflag=0;
 	r_hWnd=NULL;
	bsum=0;
	curnet=0;
}

clisock::~clisock()
{
	int i;
	for(i=0;i<bsum;i++) delete nbuf[i].buf;
	if(sid!=INVALID_SOCKET) closesocket(sid);
    if(netstatus==1) WSACleanup();
}


BEGIN_MESSAGE_MAP(clisock, CWnd)
	//{{AFX_MSG_MAP(clisock)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// clisock message handlers
BOOL clisock::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	return TRUE;
}

LRESULT clisock::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int n;
    if(message==WSA_ASYNC){
		n=onWSAEvent(wParam,lParam);
        if(n==1) ::SendMessage(r_hWnd,WM_COMMAND,RECDATA,NULL); //����������
		if(n==2) ::SendMessage(r_hWnd,WM_COMMAND,1001,NULL);    //���ӷ������ɹ�
	};	
	return CWnd::WindowProc(message, wParam, lParam);
}

int clisock::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int rtn;
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	rtn=WSAStartup(WSA_VERSION,&wsadata);
	if(rtn!=0)			return 0; //���粻����
	if(!Enumerate())	return 0; //û������
	netstatus=1;				  //�������
	r_hWnd=GetParent()->m_hWnd;   //��������ȡ�ر���
	return 0;
}

void clisock::slogout(){  //�ѻ�����
	 if(netstatus==0) return; 
	 if(sid!=INVALID_SOCKET){  //�رձ���SOCKET
		closesocket(sid);
		sid=INVALID_SOCKET;
	 };
     connect_svr=0;
	 rlen=0;
};

int clisock::ReInitNet(in_addr laddr){ //���³�ʼ������
	int rtn,b;
	SOCKADDR_IN  sd;

	if(sid!=INVALID_SOCKET)	closesocket(sid); //�������Ч���ȹر�	
	sid=socket(AF_INET,SOCK_STREAM,0);
	if(sid==INVALID_SOCKET) return -1;
	
	sd.sin_family=PF_INET;
    sd.sin_addr=laddr;
    sd.sin_port=0;
    rtn=bind(sid,(sockaddr*)&sd,sizeof(SOCKADDR_IN));
	
    if(rtn==SOCKET_ERROR){
      closesocket(sid);
	  return 0;          //ʧ�ܷ���0
	};
	rtn=WSAAsyncSelect(sid,m_hWnd,WSA_ASYNC,FD_READ|FD_CONNECT|FD_CLOSE|FD_WRITE);
	if(rtn==SOCKET_ERROR){
      closesocket(sid);
	  sid=INVALID_SOCKET;
      return -2;
    };
    b=MAXIN+10;
	setsockopt(sid,SOL_SOCKET,SO_RCVBUF,(char*)&b,sizeof(int));
    setsockopt(sid,SOL_SOCKET,SO_SNDBUF,(char*)&b,sizeof(int));

	return 1; //�ɹ���ʼ��
};


int clisock::Connect(in_addr laddr,WORD port){
	int rtn;
	if(netstatus==0||sid==INVALID_SOCKET) return 0; //���粻����

	memset(&svradd,0,sizeof(SOCKADDR_IN));
	svradd.sin_addr=laddr;
    svradd.sin_family=AF_INET;
    svradd.sin_port=htons(port);
	rtn=connect(sid,(LPSOCKADDR)&svradd,sizeof(SOCKADDR_IN));
    if(rtn!=0){   
		if(WSAGetLastError()!=WSAEWOULDBLOCK){
			closesocket(sid);
		}
		
      return 0;
    };
  	return 1;   //��ʼ����
};

int clisock::onWSAEvent(UINT wParam,LONG lParam){

    WORD WSAEvent;
    if(WSAGETSELECTERROR(lParam)!=0){
		return -1;   //�д�
	}
    WSAEvent=WSAGETSELECTEVENT(lParam);
    switch(WSAEvent){
	case FD_READ:		  //�����ݵ���
		if(recflag==0) rechead(); 
		if(recflag==1) recdata();
		if(recflag==1&&dlen==rlen){    //�����ݵ��������
			recflag=0;
			return 1; 
		};
		break;
	case FD_CONNECT:
		{
			connect_svr=1;
			return 2;
		}
		break;
	case FD_CLOSE:                             //�ͻ��ѹر�
		closesocket(sid);
		connect_svr=0;
		sid=INVALID_SOCKET;
		rlen=0;
        break;
	case FD_WRITE:
		SendBuffer();
		break;
	  };
    return 0;
};

int clisock::senddata(char *buf,int len){    //��ǰID��������
	int l,i,rtn,n;
	char a;
	DATAHEAD *head=(DATAHEAD*)sbuffer;
	if(sid==INVALID_SOCKET) return -1;
	l=len>MAXIN ? MAXIN:len;
	memcpy(&sbuffer[sizeof(DATAHEAD)],buf,l);
	head->flag1=0x78;
	head->compress=0;
	head->len=(WORD)len;
	a=0;
    for(i=0;i<4;i++) a^=sbuffer[i];
	head->check=a;
	n=len+sizeof(DATAHEAD);
	rtn=SendToNet(sbuffer,n);
	if(rtn==-1){ //�����������;ͱ����ڻ�����
		AddToBuff(sbuffer,n,0);
	}
	
	return l;
};




int clisock::GetData(char *buf, int n) //�ⲿ�����������
{
	int l;
	l=rlen;
	memcpy(buf,rbuffer,l);
	rlen=0;
	return l;
}

char *clisock::GetRecBuf(DWORD &n) //�������ݻ�������ַ�������ֽ���
{
	n=rlen;
	rlen=0;
	return rbuffer;
}

void clisock::rechead() //���մ�����ͷ5�ֽ�
{
   int i,s,n;
   char a,tbuf[100];
   DATAHEAD *head;
   s=0;
   n=recv(sid,hbuf,sizeof(DATAHEAD),0);
   if(n==0||n==SOCKET_ERROR) return;
   head=(DATAHEAD*)hbuf;
   for(;;){
	   s++;
	   if(s>=100){
	   for(;;){
		     n=recv(sid,tbuf,100,0); 
             if(n==0||n==SOCKET_ERROR) return;
		   };
	   };
	   if(head->flag1==0x78){
       a=0;
       for(i=0;i<sizeof(DATAHEAD);i++) a^=hbuf[i];  //У����
       if(a==0){
	   dlen=head->len;
       rlen=0;
       recflag=1;
	   return;
	   };
	   }
	   for(i=0;i<9;i++) hbuf[i]=hbuf[i+1];
	   n=recv(sid,tbuf,1,0);
	   hbuf[4]=tbuf[0];
	   if(n!=1) return;
   };
}


void clisock::recdata()  //��������
{
	int n,k;
	n=dlen-rlen;
	if(n==0) return;
	k=recv(sid,&rbuffer[rlen],n,0);
	if(k!=SOCKET_ERROR) rlen+=k;
};


//���������ݷŵ�������
bool clisock::AddToBuff(char *buf, int len,int level)
{
	if(bsum>=1024||len>MAXIN) return false; //��û�л�����
	if(len<=0) return false;
	nbuf[bsum].buf=new char[len+10];
	nbuf[bsum].len=len;
	nbuf[bsum].level=level;
	memcpy(nbuf[bsum].buf,buf,len);
	bsum++;
	return true;
}

//ɾ��һ������
void clisock::DeleteNbuff(int j)
{
	int i;
	if(bsum<=0) return;
	if(j>=bsum||j<0) return;
	delete nbuf[j].buf;
	nbuf[j].buf=NULL;
	for(i=j;i<bsum-1;i++){
	  nbuf[i]=nbuf[i+1];
	}
	bsum--;
}
//���ͻ���������
void clisock::SendBuffer()
{
	int rtn;
	if(bsum<=0) return;
	rtn=SendToNet(nbuf[0].buf,nbuf[0].len);
	if(rtn==0)	DeleteNbuff(0);
}

//��������
int clisock::SendToNet(char *buf,int len)
{
	int rtn;
	rtn=send(sid,buf,len,0); //����
	if(rtn==SOCKET_ERROR) return -1;
	else WSAAsyncSelect(sid,m_hWnd,WSA_ASYNC,FD_READ|FD_WRITE|FD_CLOSE);
	return 0;
}


BOOL clisock::Enumerate()
{
  char szHostname[256];
  nAdapter = 0;
  if (gethostname(szHostname, 256)!=0) return FALSE;
  HOSTENT* pHostEnt = gethostbyname(szHostname);
  if (pHostEnt == NULL) return FALSE;
  
  if (pHostEnt->h_length != 4) return FALSE;
  while (pHostEnt->h_addr_list[nAdapter]&&nAdapter<6)
  {
	CopyMemory(&ad[nAdapter].S_un.S_addr, pHostEnt->h_addr_list[nAdapter], pHostEnt->h_length);	
	nAdapter++;
  }
  //ֻȡǰ����
  nAdapter=nAdapter>2 ? 2:nAdapter;
  return TRUE;
}