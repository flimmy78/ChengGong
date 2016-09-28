#if !defined(AFX_PUBLICPW_H__INCLUDED_)
#define AFX_PUBLICPW_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//���վ����
/*const int STATION_W=1;		//ˮ��
const int STATION_H=2;		//���
const int STATION_T=3;		//���վ
const int STATION_C=4;		//����վ
const int STATION_O=5;		//����*/
typedef enum _ZONE_TYPE			//������
{
	ZONE_GEOGAREA=1,	//������
	ZONE_POROVINCE,		//ʡ����
	ZONE_REGION,		//��������
	ZONE_POWERSTATION	//�糧����
}ZONE_TYPE;

typedef enum _STATION_TYPE			//��վ�����
{
	STATION_W=1,		//ˮ��
	STATION_H,		//���
	STATION_F,		//���
	STATION_PH,		//���
	STATION_NU,		//�˵�
	STATION_T,		//���վ
	STATION_C,		//����վ
	STATION_V,		//����վ
	STATION_O		//����
}STATION_TYPE;

typedef enum _GEN_TYPE			//���������
{
	GEN_W=1,		//ˮ��
	GEN_H,			//���
	GEN_F,		//���
	GEN_PH,		//���
	GEN_NU,		//�˵�
	GEN_O		//����
}GEN_TYPE;

typedef enum _SWITCH_TYPE			//��������
{
	SWITCH_BREAK=1,		//��·��
	SWITCH_DISCON,		//��բ
	SWITCH_GROUND		//�ص�
}SWITCH_TYPE;

typedef enum _TRANSFORMER_TYPE			//��ѹ������
{
	TRANSFORMER_NORMAL=1,	//����
	TRANSFORMER_STATION		//վ�ñ�
}TRANSFORMER_TYPE;

typedef enum _CAPAC_TYPE			//�ݿ�����
{
	CAPAC_SERIES=1,		//����
	CAPAC_PARALLEL		//����
}CAPAC_TYPE;

//���������
//const int GEN_TYPE_UNKOWN=0;
//const int GEN_TYPE_THERMAL=1;		//������
//const int GEN_TYPE_HYDRO=2;		//ˮ�����

//�豸�Ӷ���
const int SUBEQUIP_NAME=0;  //�豸����
const int TRANSF_SUB_HIG=1;	//��ѹ���Ӷ��������
const int TRANSF_SUB_MID=2;	//��ѹ���Ӷ���������
const int TRANSF_SUB_LOW=3;	//��ѹ���Ӷ��������

//����λ��
const int MEAS_POS_FROMH=1;  //�豸�׶�/��ѹ����
const int MEAS_POS_TOL=2;	//�豸ĩ��/˫�Ʊ�ͣ����Ʊ�ѹ����
const int MEAS_POS_LOW=3;	//���Ʊ�ѹ����ѹ��

//��ѹ����������
const int WINDING_TYPE_HIGH=1;  //��
const int WINDING_TYPE_MID=2;  //��
const int WINDING_TYPE_LOW=3;  //��


//EQUIPMENT_STATE			�豸״̬����
const unsigned long EQUIPMENT_FIX_STATE=0xff;		//����״̬   0~7λΪ����״̬Ԥ��
const unsigned long EQUIPMENT_FIX_STATE_NOW=0x01;	//��ǰ����
const unsigned long EQUIPMENT_FIX_STATE_NEXT=0x02;	//���ռ���

const unsigned long EQUIPMENT_RELAY_STATE=0xff00;		//����״̬   8~15λΪ�̵籣��״̬Ԥ��
const unsigned long EQUIPMENT_RELAY_STATE_ON=0x0100;	//��������
const unsigned long EQUIPMENT_FAULT_STATE_ON=0x200;     //���Ϸ���
const unsigned long EQUIPMENT_RELAYDEV_STATE_ON=0x0400;	//�豸��������

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


//������������
/*const int EQUIP_TYPE_UNK=0;			//δ֪�豸
const int EQUIP_TYPE_PT=1;			//PT
const int EQUIP_TYPE_GEN=2;			//�����
const int EQUIP_TYPE_SWITCH=3;		//����
const int EQUIP_TYPE_LOAD=4;		//����
const int EQUIP_TYPE_SHUNT=5;		//�����޹��豸
const int EQUIP_TYPE_REACT=6;		//�翹��
const int EQUIP_TYPE_BITRS=7;		//˫�����
const int EQUIP_TYPE_TRITRS=8;		//�������
const int EQUIP_TYPE_SVC=9;			//��ֹ�޹�������
const int EQUIP_TYPE_BUS=10;		//ĸ��
const int EQUIP_TYPE_LINE=11;		//��·
const int EQUIP_TYPE_DCLINE=12;		//ֱ����·
const int EQUIP_TYPE_GROUP=13;		//�ӵ�
const int EQUIP_TYPE_AREA=14;		//����
const int EQUIP_TYPE_SUB=15;		//��վ
const int EQUIP_TYPE_SYSTEM=16;		//ϵͳ
const int EQUIP_TYPE_TERM=17;		 //�ն�
const int EQUIP_TYPE_BAY=18;		 //���
const int EQUIP_TYPE_SystemTarget=19; //ϵͳָ��
const int EQUIP_TYPE_MEASUREMENT=20; //�����ϵ
const int EQUIP_TYPE_UnDevMEASUR=21; //���豸�����ϵ
const int EQUIP_TYPE_Relation=22;	 //����
const int EQUIP_TYPE_DUMMY=23;		 //δ�豸*/

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
	EQUIP_ALARM_UNKONW       //�����
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
	EQUIP_TYPE_GND,	 //�ӵص���
	EQUIP_TYPE_DUMMY		 //δ�豸24
}EQUIP_TYPE;

const char tblname[EQUIP_TYPE_DUMMY][32]={"δ֪�豸","PT","�����","����","����","����","�翹",
				"2�����ѹ��","3�����ѹ��","��̬�޹�����װ��","ĸ��","������·","ֱ����·",
				"�ӵ�","����","��վ","ϵͳ","�ն�","���","ϵͳָ��","�����ϵ","���豸����",
				"Ԥ������","�Ӷ����"};

//�豸�������ͺ���ʾ��ʶ
enum GEN_MEASURE_TYPE
{
	GEN_MEASURE_TYPE_UN=0,	//ռλ	
	GEN_MEASURE_TYPE_P,	//�й�
	GEN_MEASURE_TYPE_Q,	//�޹�
	GEN_MEASURE_TYPE_Ang,	//����
	GEN_MEASURE_TYPE_AGC,	//AGC״̬
	GEN_MEASURE_TYPE_ContrlSpeed,	//��������
	GEN_MEASURE_TYPE_DownSpeed,	//����������
	GEN_MEASURE_TYPE_UpWhirl,	//��������
	GEN_MEASURE_TYPE_DownWhirl,	//��������
	GEN_MEASURE_TYPE_END	//��ֹ	
};
enum BUS_MEASURE_TYPE
{
	BUS_MEASURE_TYPE_UN=0,	//ռλ	
	BUS_MEASURE_TYPE_V,	//��ѹʵ��ֵ
	BUS_MEASURE_TYPE_PU,	//��ѹ����ֵ
	BUS_MEASURE_TYPE_AngF,	//�ǶȻ�Ƶ��
	BUS_MEASURE_TYPE_END	//��ֹ	
};
enum ACLine_MEASURE_TYPE
{
	ACLine_MEASURE_TYPE_UN=0,	//ռλ	
	ACLine_MEASURE_TYPE_Pf,	//�׶��й�
	ACLine_MEASURE_TYPE_Qf,	//�׶��޹�
	ACLine_MEASURE_TYPE_Pt,	//ĩ���й�
	ACLine_MEASURE_TYPE_Qt,	//ĩ���޹�
	ACLine_MEASURE_TYPE_I,	//����
	ACLine_MEASURE_TYPE_Par,//��ǰ������
	ACLine_MEASURE_TYPE_END	//��ֹ	
};
enum DCLine_MEASURE_TYPE
{
	DCLine_MEASURE_TYPE_UN=0,	//ռλ	
	DCLine_MEASURE_TYPE_P,	//�׶��й�
	DCLine_MEASURE_TYPE_Q,	//�׶��޹�
	DCLine_MEASURE_TYPE_I,	//����
	DCLine_MEASURE_TYPE_Par,//��ǰ������
	DCLine_MEASURE_TYPE_END	//��ֹ	
};
enum Trans2_MEASURE_TYPE
{
	Trans2_MEASURE_TYPE_UN=0,	//ռλ	
	Trans2_MEASURE_TYPE_Par,//��ǰ������
	Trans2_MEASURE_TYPE_Ph,	//��ѹ�й�
	Trans2_MEASURE_TYPE_Qh,	//��ѹ�޹�
	Trans2_MEASURE_TYPE_Ih,	//��ѹ����
	Trans2_MEASURE_TYPE_Tap,//��λ
	Trans2_MEASURE_TYPE_Pl,	//��ѹ�й�
	Trans2_MEASURE_TYPE_Ql,	//��ѹ�޹�
	Trans2_MEASURE_TYPE_Il,	//��ѹ����
	Trans2_MEASURE_TYPE_T,	//����
	Trans2_MEASURE_TYPE_END	//��ֹ	
};
enum Trans3_MEASURE_TYPE
{
	Trans3_MEASURE_TYPE_UN=0,	//ռλ	
	Trans3_MEASURE_TYPE_Par,//��ǰ������
	Trans3_MEASURE_TYPE_Ph,	//��ѹ�й�
	Trans3_MEASURE_TYPE_Qh,	//��ѹ�޹�
	Trans3_MEASURE_TYPE_Ih,	//��ѹ����
	Trans3_MEASURE_TYPE_Taph,//��ѹ��λ
	Trans3_MEASURE_TYPE_Pm,	//��ѹ�й�
	Trans3_MEASURE_TYPE_Qm,	//��ѹ�޹�
	Trans3_MEASURE_TYPE_Im,	//��ѹ����
	Trans3_MEASURE_TYPE_Tapm,//��ѹ��λ
	Trans3_MEASURE_TYPE_Pl,	//��ѹ�й�
	Trans3_MEASURE_TYPE_Ql,	//��ѹ�޹�
	Trans3_MEASURE_TYPE_Il,	//��ѹ����
	Trans3_MEASURE_TYPE_T,	//����
	Trans3_MEASURE_TYPE_END	//��ֹ	
};
enum Load_MEASURE_TYPE
{
	Load_MEASURE_TYPE_UN=0,	//ռλ	
	Load_MEASURE_TYPE_P,	//�й�
	Load_MEASURE_TYPE_Q,	//�޹�
	Load_MEASURE_TYPE_I,	//����
	Load_MEASURE_TYPE_END	//��ֹ	
};
enum Shunt_MEASURE_TYPE
{
	Shunt_MEASURE_TYPE_UN=0,	//ռλ	
	Shunt_MEASURE_TYPE_Q,	//�޹�
	Shunt_MEASURE_TYPE_I,	//����
	Shunt_MEASURE_TYPE_END	//��ֹ	
};
enum SVC_MEASURE_TYPE
{
	SVC_MEASURE_TYPE_UN=0,	//ռλ	
	SVC_MEASURE_TYPE_Q,	//�޹�
	SVC_MEASURE_TYPE_END	//��ֹ	
};
enum SYS_MEASURE_TYPE
{
	SYS_MEASURE_TYPE_UN=0,	//ռλ	
	SYS_MEASURE_TYPE_GenP,	//�������й�
	SYS_MEASURE_TYPE_GenQ,	//�������޹�
	SYS_MEASURE_TYPE_WhirlBack,	//��ת����
	SYS_MEASURE_TYPE_TotalRun,	//����������
	SYS_MEASURE_TYPE_LoadP,	//���й�����
	SYS_MEASURE_TYPE_LoadQ,	//���޹�����
	SYS_MEASURE_TYPE_END	//��ֹ	
};
enum Area_MEASURE_TYPE
{
	Area_MEASURE_TYPE_UN=0,	//ռλ	
	Area_MEASURE_TYPE_GenCapa,	//װ������
	Area_MEASURE_TYPE_TransCapa,	//�������
	Area_MEASURE_TYPE_GenP,	//�������
	Area_MEASURE_TYPE_LoadP,	//�ܸ���
	Area_MEASURE_TYPE_UpWhirl,	//��������
	Area_MEASURE_TYPE_DownWhirl,	//��������
	Area_MEASURE_TYPE_END	//��ֹ	
};
enum Station_MEASURE_TYPE
{
	Station_MEASURE_TYPE_UN=0,	//ռλ	
	Station_MEASURE_TYPE_LastPower,	//��úˮλ
	Station_MEASURE_TYPE_LastPowerT,	//��úˮλ����ʱ��
	Station_MEASURE_TYPE_END	//��ֹ	
};
enum Section_MEASURE_TYPE
{
	Section_MEASURE_TYPE_UN=0,	//ռλ	
	Section_MEASURE_TYPE_CurVal,	//��ǰֵ
	Section_MEASURE_TYPE_CurPar,	//��ǰ����
	Section_MEASURE_TYPE_Max,	//���ֵ
	Section_MEASURE_TYPE_Min,	//��Сֵ
	Section_MEASURE_TYPE_END	//��ֹ	
};
enum UnEquip_MEASURE_TYPE
{
	UnEquip_MEASURE_TYPE_UN=0,	//ռλ	
	UnEquip_MEASURE_TYPE_Value,	//��ǰֵ
	UnEquip_MEASURE_TYPE_END	//��ֹ	
};

//��������
enum MEASURE_TYPE
{
	MEASURE_TYPE_UN=0,
	MEASURE_TYPE_V=1,		//��ѹ  1
	MEASURE_TYPE_P=2,		//�й�  1
	MEASURE_TYPE_Q=3,		//�޹�  1
	MEASURE_TYPE_S=4,		//���ڹ���
	MEASURE_TYPE_I=5,		//����  1
	MEASURE_TYPE_Pf=6,		//��������  1
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
	MEASURE_TYPE_WINDDIR=23,	//����
	MEASURE_TYPE_WINDDEL=24,	//����
	MEASURE_TYPE_FIXVALUE=25,	//��ֵ
	MEASURE_TYPE_COUNT=26,	//����
	MEASURE_TYPE_UNSORT=27	//δ����
};

#endif // !defined(AFX_PUBLICPW_H__INCLUDED_)
