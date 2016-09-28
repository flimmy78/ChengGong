#if !defined(AFX_MSTRUCT_H__INCLUDED_)
#define AFX_MSTRUCT_H__INCLUDED_



typedef struct _DEVDEF{	//�豸
	char name[64];		//�豸��
	int  id;			//�豸ID
	int  stno;			//վ��
}DEVDEF;	


typedef struct _SELRESERVOIR{	//�豸
	char name[64];		//�豸��
	int  id;			//�豸ID
}SELRESERVOIR;

typedef struct _STATION
{
	char name[64];		//�豸��
	int  id;			//�豸ID
}STATION;
//������������ʵ������ѡ��
typedef struct _SELDATA_DEV{ //���ݽ����ṹ
	char mdbnm[256];		 //���ݿ���
	char name[64];			 //�豸��
	int  did;				 //�豸ID
	BYTE dtype;				 //�豸����
	BYTE xsmode;			 //��ʾģʽ
	/*
	xsmode���壺
	�ڵ㣺  0=����ѹ�ȼ��ͱ���ֵ��ʾ 1=��ʾ��ѹ����ֵ�����
	��·��  0=ʼ��   1=ĩ��
	��ѹ����0=������ 1=������
	*/
	BYTE tseg;				 //ʱ��
	char extend[128];		 //����
}SELDATA_DEV;

//���嵥������Դ��ֻ��ѡ������һ������)
typedef struct _SINGLEDBS{   //��������Դ
	char  name[64];			 //�豸����
	int   did;				 //�豸ID
	BYTE  dtype;			 //�豸����0=����� 1=������· 2=ֱ����· 3=ĸ�� 4=���� 5=Ԥ�������
	BYTE  xsmode;			 //ֵ����
}SINGLEDBS;

/*  xsmode��dtype�Ĺ�ϵ
	dtype=0:       �����
	     xsmode=0  �й�
		 xsmode=1  �޹�
	dtype=1:	   ��·
		 xsmode=0  ����й�
		 xsmode=1  ����޹�
		 xsmode=2  ĩ���й�
		 xsmode=3  ĩ���޹�
	dtype=2:	   ��·
		 xsmode=0  ����й�
		 xsmode=1  ĩ���й�
	dtype=3:	   ĸ��	
	     xsmode=0  ��ѹ����ֵ
		 xsmode=1  ��ѹ����ֵ
		 xsmode=2  ���
	dtype=4:	   ����
		 xsmode=0  �й�
		 xsmode=1  �޹�
*/


typedef struct _SELSINGLE_DEV //��ֵ���ݽ����ṹ
{
	char mdbnm[256];		 //���ݿ���
	SINGLEDBS dbs;			 //����Դ
	char extend[128];		 //����
}SELSINGLE_DEV;


typedef struct _SELECTDEV    //ѡ���豸����
{
	char  dbname[256];		 //���ݿ���
	char  name[64];			 //�豸����
	int   did;				 //�豸ID
	BYTE  type;				 //������
	BYTE  dtype;			 //�豸���� type=2ʱ
	/*
	0="PT" 1="�����" 2="����,��բ",3="����",4="����",5="�翹",
	6="�ӵ�",7="�������ѹ��"
	8="�������ѹ��",9="��̬�޹�������",10="��䡢������"
	33=ĸ�� 34=���� 35=ֱ��
	*/ 
}SELECTDEV;


typedef struct _SELECTPIE    //ѡ��ٷֱ�ͼ����
{
	char  dbname[256];		 //���ݿ���
	char  name[64];			 //�豸����
	int   did;				 //�豸ID
	BYTE  dtype;			 //�豸����	0=������· 1=ֱ����· 2=����� 
}SELECTPIE;

typedef struct _DMLS
{
	int id;			//��·ID
	BYTE type:4;	//��·����
	BYTE ys:1;		//���㷽�� 0=+ 1=-
	BYTE nouse:3;	//δ��
}DMLS;

#endif;