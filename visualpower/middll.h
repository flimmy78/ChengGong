#if !defined(AFX_MIDDLL_H__INCLUDED_)
#define AFX_MIDDLL_H__INCLUDED_

#include "pwptdef.h"
#include "visualdb.h"
#include "PublicAvcDef.h"
///////////////////////////////////////////////////////////////////
typedef struct _DEVDEF{	//�豸
	char name[24];		//�豸��
	int  id;			//�豸ID
}DEVDEF,SELRESERVOIR;	
//һ����������ʵ������ѡ��
typedef struct _SELDATA_DEV{	//���ݽ����ṹ
	char mdbnm[256];			//���ݿ���
	char name[24];				//�豸��
	int  did;					//�豸ID
	BYTE dtype;					//�豸����
	BYTE xsmode;				//��ʾģʽ
	/*
	xsmode���壺
	�ڵ㣺  0=����ѹ�ȼ��ͱ���ֵ��ʾ 1=��ʾ��ѹ����ֵ�����
	��·��  0=ʼ��   1=ĩ��
	��ѹ����0=������ 1=������
	*/
	BYTE yh;					//�Ż�ǰ��
	BYTE tseg;					//ʱ��
	int  mtype;					//���з�ʽ
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
	char  name[24];				//�豸����
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
	char  name[24];				//�豸����
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
/*typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;



//��Ƶ�𵴲�����ȡ��ʽ
typedef struct LowFLPam
{
	DWORD  LineID;						//��·ID
	BYTE  Type;							//���ͽ�����ֱ��
	BYTE  UnitNo;						//װ�ú�
	BYTE  Index;						//�������
	BYTE  DotPs;						//ԭʼ���ݵ���/ÿ��
	float  MaxV;						//����ֵ����
}LowFLPam;


/////////////////////////////////////////////////////////////////////////////////////////
//n-1���϶�ȡ���ݽṹ
typedef struct N1Data{
	int  id;			//�豸ID
	char type;			//��������
	float val;			//ֵ
}N1Data;
//�澯���
typedef struct SYSALARM
{
	WORD  Alarm;						//�澯״̬0,1
	WORD  num;							//�����澯���豸����
	char  picname[32];					//�Ƴ���������
	WORD  picno;						//�Ƴ��������
}SYSALARM;
*/


//seldev.dll�����ӿ�	
bool WINAPI Select_device(SELECTDEV&indata);
bool WINAPI SelAnlSHow(SELDATA_DEV &indata);
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata);
bool WINAPI SelDevSta(SELSINGLE_DEV&indata);
bool WINAPI SelZone(SELDATA_DEV&indata);
bool WINAPI GetNameByID(SELECTDEV&dev);
bool WINAPI SelPie(SELECTPIE&indata);
bool WINAPI SelReservoir(SELRESERVOIR&indata);

//BJ_SCFileDLL.dll�����ӿ�
//itypeΪ1��line,2=bus
void WINAPI NT_GetDevBusID(DWORD inu,BYTE itype,int &nf,int &nt);
//itypeΪ1��bus,2=line
int WINAPI NT_GetDevID(DWORD inu,BYTE itype);
BOOL WINAPI NT_Tfm(int ZoneNU);
BOOL WINAPI NT_Gen(int ZoneNU);

BOOL WINAPI NT_ShowEffect(int iCtgDev,BYTE byType,char* pDirDB);
BOOL WINAPI NT_ShowAllCtg();

//�����ȼ������ؽӿ�BJ_SCFileDLL.dll�����ӿ�
int  WINAPI NT_CreateDAT(char *FileNameDat);
int  WINAPI NT_FileOutInput(char *FileNameOut,int sentype);
int  WINAPI NT_FileConvertInput(char *FileConvert);

//CUserApi.dll�����ӿ�
bool WINAPI V_GetAllUSer(my_user *usr, int &un, int usrmax);
void WINAPI V_Encryptpwd(char *pwd,char *name,char *encrypt);
bool WINAPI V_CheckUser(char *name, char *pw,int &type);
bool WINAPI V_ChangePassword(char *name, char *newpw);
bool WINAPI V_DeleteAUser(char *name);
bool WINAPI V_AddNewUser(void *usrdata);
bool WINAPI V_CanUse();




/////////////////////////////////////////////////////////////////////////////
// CHisProvider
// See HisProvider.cpp for the implementation of this class
//
//��ʷ�������Ͷ���
const int HIS_GEN=0;		//�����
const int HIS_LOAD=1;		//����
const int HIS_SHUNT=2;		//����
const int HIS_SREACT=3;		//�翹
const int HIS_TFM1=4;		//˫�����
const int HIS_TFM2=5;		//�������
const int HIS_BUS=6;		//ĸ��
const int HIS_LINE=7;		//������·
const int HIS_SWITCH=8;		//����
const int HIS_DCLINE=9;		//ֱ����·
const int HIS_GND=10;		//�ӵ�
const int HIS_RUNTYPE=11;	//���з�ʽ
const int HIS_SEN=12;		//������
const int HIS_SVC=13;		//��̬�޹�����
const int HIS_STATION=14;	//���վ
const int HIS_ZONE=15;		//����
const int HIS_BUSV=16;		//��ѹ��������
const int HIS_PT=17;		//PT
const int HIS_CVT=18;		//CTV
const int HIS_END=19;		//���һ����ʷ����ţ�����±�˱�˳�ӣ�����
//�������ṩ��,��ʼ�����ݿ�����
BOOL WINAPI IniProvider();

//�ر������ṩ��
void WINAPI	CloseProvider();
//***********************************************************************************//
//�ȵ�IniProvider,�ڵ��ú���ĺ���,������Ҫ�˿���CloseProvider�ر����ݿ�����,�ͷ��ڴ�//
//***********************************************************************************//

//������ʷ����
void WINAPI	SaveHisData();

//***********************************************************************************//
//������������ʷ���ݲ��ź����ӿ�,��˳�����,GetNextSection��tmCur,����GetFirstSection//
//��tmList�е�ֵ����ѡȡ                                                             //
//***********************************************************************************//
//ע����Ҫ���ŵ�����(pRecord:���ݼ�¼ָ�룬num:������type:����)
int WINAPI RegPlayData(DWORD* pRecord,int num,int type);

//��ȡ��ʷ���ݶ�����(tmStart:��ʼʱ�䣬tmEnd:������ʱ�䣬tmList:������ʱ���б�iMaxSection:tmList�ɷ��������)(��δʵ��)
int WINAPI GetSectionList(time_t tmStart,time_t tmEnd,time_t* pList,int iMaxSection);

//��ʼ��ȡ����
BOOL WINAPI	BeginGettingData();

//��ȡ��ʷ���ݶ��棬�������ڴ���ʷ��(tmCur:Ҫ���ŵ����ݶ�ʱ�䣬tmNext:��һ��Ҫ���ŵ�ʱ���)(��δʵ��)
BOOL WINAPI	GetNextSection(time_t tmCur,time_t &tmNext);

//��ȡ��ʷ���ݶ��棬�������ڴ���ʷ��(tmCur:Ҫ���ŵ����ݶ�ʱ�䣬tmNext:��һ��Ҫ���ŵ�ʱ���)(��δʵ��)
BOOL WINAPI	GetPreSection(time_t tmCur,time_t &tmNext);

//���ȫ��ע������
void WINAPI ClearAllRegData();

//google earth�ӿ�
//����google earth
BOOL WINAPI AttachEarthClient(CWnd* pParent);
//�ͷ�google earth
BOOL WINAPI DetachEarthClient();
//��λ����λ��
BOOL WINAPI MoveEarthWnd(CRect* pRect,BOOL bShow=TRUE);
//////////////////////////////////////////////////////////////////////////////////////////
//AVCProperty.dll
//�豸���Ͷ���
#define DEV_TRANS2 1			//˫�����豸
#define DEV_TRANS3 2			//�������豸
#define DEV_GEN 3				//����豸

//��ͼ���ߣ���ѹ��AVC�����趨
//�༭̬��ʾ��ͼ�Σ�byType=2,�����飻byType=1,������
void WINAPI OpenPropertyDlg(DWORD dwTransNo,BYTE byType);

//VisAVCPQVDll.dll
//���������AVC��PQV�ӿ�
//��������(����������ʱ����)
HWND WINAPI	CreateAVCPQVWnd(CWnd* pParent);
//��ʾ����(�Ҽ��豸�Ҽ��˵�����)
BOOL WINAPI	ShowAVCPQVWnd(DWORD devnu,BYTE devtype,BOOL bShow=TRUE);
//�رմ���(������ر�ʱ����)
void WINAPI	CloseAVCPQVWnd();
//////////////////////////////////////////////////////////////////////////////////////////
//VisHisSOE.dll
void WINAPI LoadNewSOEFile(char* filepath);				//�����µ�SOE�����ļ���������������
void WINAPI GetHisSoe(char** phissoe, int* soelen);		//�����ʷ��¼��ѯ�ͽ���ռ䷵�� soelenָ�ռ��ܳ���, ������ٸ�SoeInfo�ṹ����ĿΪ��soenum/sizeof(SoeInfo)
void WINAPI ReleaseHisSoe();

//��ѹ����ʱ�޼���DynMonitorCli.dll
//��������
HWND  WINAPI CreateSvigilWnd(CWnd* pParent,BOOL bShow);
//��ʾָ����ѹ��
BOOL WINAPI ShowDynTrans(DWORD dwTrans,BYTE byThreeWind,BOOL bShow);
void WINAPI SetAutoShow(BOOL bShow);

//��·�������㼰ά��ģ��(�ƹ���д��)
//scswitch.dll
//����GD�ļ�����--�̶������ļ�
int WINAPI CreateGDFile(char *mFileName,BYTE itype,BYTE bySign);
//itype =1 ΪLINE�� itype=2 ΪDCLine,����ֵ=0 Ϊ�ɹ�������Ϊʧ��
bool WINAPI  NT_DLSJ(BYTE itype,DWORD linenu);
//������Ϣά��	
void WINAPI ShowDlg_GZXXWH(BOOL Module = FALSE);

//������ʷ�ط�EstDemo.dll
HWND  WINAPI CreateDemoWnd(CWnd* pParent,BOOL bShow);

#endif