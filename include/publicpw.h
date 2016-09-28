#if !defined(AFX_PUBLICPW_H__INCLUDED_)
#define AFX_PUBLICPW_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//���վ����
const int STATION_W=1;		//ˮ��
const int STATION_H=2;		//���
const int STATION_T=3;		//���վ
const int STATION_C=4;		//����վ
const int STATION_O=5;		//����

//���������
const int GEN_TYPE_UNKOWN=0;
const int GEN_TYPE_THERMAL=1;		//������
const int GEN_TYPE_HYDRO=2;		//ˮ�����

//��ѹ���Ӷ���
const int SUBEQUIP_NAME=0;
const int TRANSF_SUB_HIG=1;	//��ѹ���Ӷ��������
const int TRANSF_SUB_MID=2;	//��ѹ���Ӷ���������
const int TRANSF_SUB_LOW=3;	//��ѹ���Ӷ��������

/*
//������������
const int EQUIP_TYPE_UNK=0;//δ֪�豸
const int EQUIP_TYPE_GEN=1;	//�����
const int EQUIP_TYPE_BUS=2;	//ĸ��
const int EQUIP_TYPE_LINE=3;	//��·
const int EQUIP_TYPE_BITRS=4;	//˫�����
const int EQUIP_TYPE_TRITRS=5;//�������
const int EQUIP_TYPE_LOAD=6;	//����
const int EQUIP_TYPE_SHUNT=7;	//�����޹��豸
const int EQUIP_TYPE_SWITCH=8;//����
const int EQUIP_TYPE_DCLINE=9;//ֱ����·
const int EQUIP_TYPE_REACT=10;//�翹��
const int EQUIP_TYPE_SVC=11; //��ֹ�޹�������
const int EQUIP_TYPE_MEASUREMENT=12; //�����ϵ
const int EQUIP_TYPE_SUB=20; //��վ
const int EQUIP_TYPE_TERM=21; //�ն�
const int EQUIP_TYPE_BAY=22; //���
const int EQUIP_TYPE_AREA=23; //����
*/

typedef enum _EQUIP_ALARM
{
	EQUIP_ALARM_NORMAL=0,     //����
	EQUIP_ALARM_STOP,       //ͣ��
	EQUIP_ALARM_G,          //����
	EQUIP_ALARM_GND,        //�ӵ�
	EQUIP_ALARM_HOT,        //�ȱ���
	EQUIP_ALARM_QUIT,       //�˳�����
	EQUIP_ALARM_REPAIR,     //����
	EQUIP_ALARM_CHARGE,     //���
	EQUIP_ALARM_COLD,        //�䱸��
	EQUIP_ALARM_UNKONW       //δ֪
}EQUIP_ALARM;
typedef enum _EQUIP_TYPE
{
	EQUIP_TYPE_UNK=0,			//δ֪�豸
	EQUIP_TYPE_PT,			//PT
	EQUIP_TYPE_GEN,			//�����
	EQUIP_TYPE_SWITCH,		//����
	EQUIP_TYPE_LOAD,		//����
	EQUIP_TYPE_SHUNT,		//�����޹��豸
	EQUIP_TYPE_REACT,		//�翹��
	EQUIP_TYPE_BITRS,		//˫�����
	EQUIP_TYPE_TRITRS,		//�������
	EQUIP_TYPE_SVC,			//��ֹ�޹�������
	EQUIP_TYPE_BUS,		//ĸ��
	EQUIP_TYPE_LINE,		//��·
	EQUIP_TYPE_DCLINE,		//ֱ����·
	EQUIP_TYPE_GROUP,		//�ӵ�
	EQUIP_TYPE_AREA,		//����
	EQUIP_TYPE_SUB,		//��վ
	EQUIP_TYPE_SYSTEM,		//ϵͳ
	EQUIP_TYPE_TERM,		 //�ն�
	EQUIP_TYPE_BAY,		 //���
	EQUIP_TYPE_SystemTarget, //ϵͳָ��
	EQUIP_TYPE_MEASUREMENT, //�����ϵ
	EQUIP_TYPE_UnDevMEASUR, //���豸�����ϵ
	EQUIP_TYPE_Relation,	 //����
	EQUIP_TYPE_SubObject,	 //�Ӷ����
	EQUIP_TYPE_GND,			//�ӵص�բ
	EQUIP_TYPE_DUMMY		 //δ�豸24
}EQUIP_TYPE;

const char tblname[EQUIP_TYPE_DUMMY][32]={"δ֪�豸","PT","�����","����","����","����","�翹",
				"2�����ѹ��","3�����ѹ��","��̬�޹�����װ��","ĸ��","������·","ֱ����·",
				"�ӵ�","����","��վ","ϵͳ","�ն�","���","ϵͳָ��","�����ϵ","���豸����",
				"Ԥ������","�Ӷ����","�ӵص�բ"};

//EQUIPMENT_STATE			�豸״̬����
const unsigned long EQUIPMENT_FIX_STATE=0xff;		//����״̬   0~7λΪ����״̬Ԥ��
const unsigned long EQUIPMENT_FIX_STATE_NOW=0x01;	//��ǰ����
const unsigned long EQUIPMENT_FIX_STATE_NEXT=0x02;	//���ռ���
const unsigned long EQUIPMENT_BACKUP_STATE_COLD=0x11;	//�䱸			�䱸���ȱ�ʱ��·�����磬sta ele��Ϊ0�� �������·����sta=0, ele=1
const unsigned long EQUIPMENT_BACKUP_STATE_CHAGING=0x12;	//���
const unsigned long EQUIPMENT_BACKUP_STATE_HOT=0x13;	//�ȱ�
const unsigned long EQUIPMENT_BACKUP_STATE_RUN=0x14;	//����

const unsigned long EQUIPMENT_RELAY_STATE=0xff00;		//����״̬   8~15λΪ�̵籣��״̬Ԥ��
const unsigned long EQUIPMENT_RELAY_STATE_ON=0x0100;	//��������
const unsigned long EQUIPMENT_FAULT_STATE_ON=0x0200;	//���Ϸ���
const unsigned long EQUIPMENT_RELAYDEV_STATE_ON=0x0400;	//�����豸��������

const unsigned long EQUIPMENT_GROUP_STATE=0xff0000;		//�ӵ�״̬   16~23λΪ�ӵ�״̬Ԥ��
const unsigned long EQUIPMENT_GROUP_STATE_ON=0x010000;	//�ӵط���

const unsigned long EQUIPMENT_DEV_STATE=0xff000000;		//�豸����״̬   16~23λΪ�ӵ�״̬Ԥ��
const unsigned long EQUIPMENT_DEV_STATE_VUP=0x01000000;		//��ѹԽ����
const unsigned long EQUIPMENT_DEV_STATE_VDOWN=0x02000000;	//��ѹԽ����
const unsigned long EQUIPMENT_DEV_STATE_SUP=0x04000000;		//����Խ��
const unsigned long EQUIPMENT_DEV_STATE_IUP=0x08000000;		//����Խ��
const unsigned long EQUIPMENT_DEV_STATE_TUP=0x10000000;		//�¶�Խ��
const unsigned long EQUIPMENT_DEV_STATE_CHANGE=0x20000000;	//״̬�仯
//=============EQUIPMENT_STATE			�豸״̬����



//��������
enum MEASURE_TYPE
{
	MEASURE_TYPE_UN=0,		
	MEASURE_TYPE_V=1,		//��ѹ
	MEASURE_TYPE_P=2,		//�й�
	MEASURE_TYPE_Q=3,		//�޹�
	MEASURE_TYPE_S=4,		//���ڹ���
	MEASURE_TYPE_I=5,		//����
	MEASURE_TYPE_Pf=6,		//��������
	MEASURE_TYPE_T=7,		//�¶�
	MEASURE_TYPE_Pos=8,		//��λ
	MEASURE_TYPE_f=9,		//Ƶ��
	MEASURE_TYPE_Ang=10,	//���
	MEASURE_TYPE_YX=11,		//ң��
	MEASURE_TYPE_Va=12,		//a���ѹ
	MEASURE_TYPE_Vb=13,		//b���ѹ
	MEASURE_TYPE_Vc=14,		//c���ѹ
	MEASURE_TYPE_Vab=15,		//ab�ߵ�ѹ
	MEASURE_TYPE_Vbc=16,		//bc�ߵ�ѹ
	MEASURE_TYPE_Vca=17,		//ca�ߵ�ѹ
	MEASURE_TYPE_Ia=18,		//a�����
	MEASURE_TYPE_Ib=19,		//b�����
	MEASURE_TYPE_Ic=20,		//c�����
	MEASURE_TYPE_Rl=21,		//�����ź�
	MEASURE_TYPE_ETS=22,	//�¹����ź�
	MEASURE_TYPE_UNSORT=23	//δ����
};

#endif // !defined(AFX_PUBLICPW_H__INCLUDED_)
