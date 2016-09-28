#if !defined(AFX_MIDDLL_H__INCLUDED_)
#define AFX_MIDDLL_H__INCLUDED_


///////////////////////////////////////////////////////////////////

typedef struct _SELRESERVOIR{	//�豸
	char name[64];		//�豸��
	int  id;			//�豸ID
}SELRESERVOIR;	
//һ����������ʵ������ѡ��
typedef struct _SELDATA_DEV{	//���ݽ����ṹ
	char mdbnm[256];			//���ݿ���
	char name[64];				//�豸��
	int  did;					//�豸ID
	BYTE dtype;					//�豸����
	BYTE xsmode;				//��ʾģʽ
	/*
	xsmode���壺
	�ڵ㣺  0=����ѹ�ȼ��ͱ���ֵ��ʾ 1=��ʾ��ѹ����ֵ�����
	��·��  0=ʼ��   1=ĩ��
	��ѹ����0=������ 1=������
	*/
	BYTE tseg;					//ʱ��
	char extend[128];			//����
}SELDATA_DEV;



typedef struct _SELSINGLE_DEV{	//��ֵ���ݽ����ṹ
	char mdbnm[256];			//���ݿ���
	SINGLEDBS dbs;				//����Դ
	char extend[128];			//����
}SELSINGLE_DEV;


typedef struct _SELECTDEV		//ѡ������豸
{
	char  dbname[256];			//���ݿ���
	char  name[64];				//�豸����
	int   did;					//�豸ID
	BYTE  type;					//������
	BYTE  dtype;				//�豸���� type=2ʱ
	/*
	0="PT" 1="�����" 2="����,��բ",3="����",4="����",5="�翹",
	6="�ӵ�",7="�������ѹ��"
	8="�������ѹ��",9="��̬�޹�������",10="��䡢������"
	33=ĸ�� 34=���� 35=ֱ��
	*/ 
}SELECTDEV;

typedef struct _SELECTPIE		//ѡ��ٷֱ�ͼ����
{
	char  dbname[256];			//���ݿ���
	char  name[64];				//�豸����
	int   did;					//�豸ID
	BYTE  dtype;				//�豸����	0=������· 1=ֱ����· 2=����� 
}SELECTPIE;

typedef struct my_user
{
	WORD  id;					//�û�ID
	char  Name[15];				//�û���
	char  password[16];			//�û�����
	char  type;					//�û�����
	char  exp[32];				//ע��
}my_user;

//PMUSVR�ṹ
typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;

//seldev.dll�����ӿ�
bool WINAPI Select_device(SELECTDEV&indata);	
bool WINAPI SelAnlSHow(SELDATA_DEV &indata);
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata);
bool WINAPI SelDevSta(SELSINGLE_DEV&indata);
bool WINAPI SelZone(SELDATA_DEV&indata);
bool WINAPI GetNameByID(SELECTDEV&dev);
bool WINAPI GetIDByName(SELECTDEV&dev);
bool WINAPI SelPie(SELECTPIE&indata);
bool WINAPI SelReservoir(SELRESERVOIR&indata);
bool WINAPI SelYbDbs(SINGLEDBS&meter);
//readdata.dll�����ӿ�
bool WINAPI InitMemDbf();
bool WINAPI ReadColorData(DEFCOLOR*cr,int &crsum);
bool WINAPI SetColorData(char *vname,BYTE R,BYTE G,BYTE B);
bool WINAPI GetHmiPath(char  *path);
void WINAPI RegistFileOK(HWND hwnd);
void WINAPI UnRegistFileOK(HWND hwnd);
bool WINAPI GetLastRecFile(char *filename);
bool WINAPI SendHmiFile(char *filename);
bool WINAPI ReadDevViewMsg(void *data,int dtype);
bool WINAPI ReadStaData(READDEV_STA&data);
bool WINAPI ReadDevData(READDEV&data);
void WINAPI SetCurDbf(char *dbfname);
void WINAPI SetSenDemo(int type);
bool WINAPI ReadSenData(READSEN&sn);
bool WINAPI ReadPwSys(PWSYSSUM&ps);
bool WINAPI IsLowFLine(DWORD lineid,int type);
int  WINAPI ReadPmuSvrIpPort(PSvrIpPort *pip);




//CUserApi.dll�����ӿ�
bool WINAPI V_GetAllUSer(my_user *usr, int &un, int usrmax);
void WINAPI V_Encryptpwd(char *pwd,char *name,char *encrypt);
bool WINAPI V_CheckUser(char *name, char *pw,int &type);
bool WINAPI V_ChangePassword(char *name, char *newpw);
bool WINAPI V_DeleteAUser(char *name);
bool WINAPI V_AddNewUser(void *usrdata);
bool WINAPI V_CanUse();
////////////////////////////////////////////////////////////////////////////////
//�ӿ�AVCProperty.dll
//�豸���Ͷ���
#define DEV_TRANS2 1			//˫�����豸
#define DEV_TRANS3 2			//�������豸
#define DEV_GEN 3				//����豸

//��ͼ���ߣ���ѹ��AVC�����趨
//�༭̬��ʾ��ͼ�Σ�byType=2,�����飻byType=1,������
void WINAPI OpenPropertyDlg(DWORD dwTransNo,BYTE byType);


//���������AVC��PQV�ӿ�
//��������(����������ʱ����)
HWND WINAPI	CreateAVCPQVWnd(CWnd* pParent);
//��ʾ����(�Ҽ��豸�Ҽ��˵�����)
BOOL WINAPI	ShowAVCPQVWnd(DWORD devnu,BYTE devtype,BOOL bShow=TRUE);
//�رմ���(������ر�ʱ����)
void WINAPI	CloseAVCPQVWnd();
//////////////////////////////////////////////////////////////////////////////////

//CimRead.dll�ӿں���
bool WINAPI IsCimOpen();
void WINAPI FreeCim();
bool WINAPI ReadPowerCimFile(char *filename);
bool WINAPI CimSwitch(char *oldname,char *newname,int &vl);

bool WINAPI Cimtransformer(char *oldname,char *newname);
bool WINAPI CimGenerator(char *oldname,char *newname,int &vl);
bool WINAPI CimConpensator(char *oldname,char *newname);
bool WINAPI CimAcLine(char *oldname,char *newname,int &vl);

bool WINAPI CimBusName(char *oldname,char *newname,int &vl);
bool WINAPI CimLoadName(char *oldname,char *newname);

//��CIM����ID
char* WINAPI IDtoNuName(DWORD ID,int Type,DWORD &iNU);

#endif