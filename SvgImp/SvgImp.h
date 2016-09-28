
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SVGIMP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SVGIMP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SVGIMP_EXPORTS
#define SVGIMP_API __declspec(dllexport)
#else
#define SVGIMP_API __declspec(dllimport)
#endif

#include "..\PowerPaint\ptdefine.h"
#include <vector>

enum PWTYPE //PW0���ͣ�����N_BASATTR���type
{
	N_DBX_TYPE=1,
	N_RECT_TYPE=2,
	N_CIRCLE_TYPE=3,
	N_ARC_TYPE=6,
	N_TEXT_TYPE=10,	//�ı�
	N_ESITE_TYPE=11,//����
	N_IMG_TYPE=15,  //ͼ��
	N_SPIC_TYPE=17, //Сͼ
	N_ANL_TYPE=64,		//ģ����
	N_ELEGRPA_TYPE=66,
	N_PUSH_TYPE=75,		//��ť
	N_FLOW_TYPE=77,		//������
	N_CONLINE_TYPE=78,	//������
	N_BUS_TYPE=79		//ĸ��
};

//���ͼ�鰸�������ͣ�����N_ELEGRPA���type,��PWTYPE��Ϊ����         
//�豸���� 0=PT 1=����� 2=����,��բ 3=���� 4=���� 5=�翹 6=�ӵ� 7=�������ѹ��",8=�������ѹ��
enum EGPTYPE 
{
	EGP_PT=0,//0=PT
	EGP_GEN=1,//1=�����
	EGP_SWT=2,//2=����
	EGP_LOD=3,//3=����
	EGP_SHT=4,//4=������
	EGP_RTR=5,//5=�翹��
	EGP_ERH=6,//6=�ӵ�
	EGP_TF2=7,//7=2�����ѹ��
	EGP_TF3=8,//8=3�����ѹ��
	EGP_SVC=9,//9=��ֹ�޹�������
	EGP_CVT=10//10=��ֹ�޹�������
};

enum SYMTYPE //�Գ�����
{
	SYM_NONE=0,
	SYM_ORIG=1,
	SYM_YAXIS=2,
	SYM_XAXIS=3,
	SYM_YXPOS=4,
	SYM_YXNEG=5
};

SVGIMP_API typedef struct SVG_GRAPH //ͼ�Σ���ӦBASE0����
{
	N_BASATTR attr;
	void* graph;
	SYMTYPE sym;
	float fAngle;//ͼԪ��ת��
}SVG_GRAPH;
SVGIMP_API typedef std::vector<SVG_GRAPH*> SVGGRAPHVTR;

SVGIMP_API typedef struct SVG_ELEGRP //�ڴ�ͼԪ,��ӦN_ELEGRP
{
	WORD  id;				//�ڲ�ID��
	BYTE  type;				//����
	char  name[15];			//����
	BYTE  subtype;			//������
	BYTE  sitesum;			//������,�Ǳ�ʱ�����Ǳ�ĸ���
	DRECT srt[3];			//3������λ��

	SVGGRAPHVTR g1Vtr;
	DRECT rt1;				//ռ�õľ���
	SVGGRAPHVTR g2Vtr;
	DRECT rt2;				//ռ�õľ���
}SVG_ELEGRP;
SVGIMP_API typedef std::vector<SVG_ELEGRP*> SVGELEGRPVTR;

SVGIMP_API typedef struct SVG_LAYER //ͼ��,��ӦN_layer
{
	char szName[25];
	SVGGRAPHVTR gVtr;
}SVG_LAYER;

SVGIMP_API typedef struct SVG_PAGE  //����ҳ
{
	int dx;
	int dy;
	WORD width;		//��
	WORD height;	//��
	DWORD bgcolor;	//����ɫ

	SVGELEGRPVTR egrpVtr;  //ͼԪ
	SVG_LAYER layer[MAXLAYER]; //ͼ��
	int laynum;					//ͼ����
}SVG_PAGE;

//SVG���뺯��
SVGIMP_API int SvgImport(char* pSvgFile,char* pStyle,SVG_PAGE** page);
//�ͷ�SVG_PAGE����
SVGIMP_API void ReleaseSvgPage(SVG_PAGE* page);


