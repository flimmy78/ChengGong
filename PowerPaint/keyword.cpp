#include "stdafx.h"


//////////////////////////���ӻ��Զ���汾SVG�ؼ��ʶ���///////////////////////////////
//��ʽ:��ʼ����������
char *svgkwd[]={"<?xml","?>",       //index=0
				"<!DOCTYPE",">",	//index=1
				"<!--","-->",		//index=2
				"<svg",">",			//index=3
				"</svg",">",		//index=4
				"<title",">",		//index=5
				"</title",">",		//index=6
				"<defs",">",		//index=7
				"</defs",">",		//index=8
				"<g",">",			//index=9
				"</g",">",			//index=10
				"<rect","/>",		//index=11
				"<text",">",		//index=12
				"</text",">",		//index=13
				"<line","/>",		//index=14
				"<polyline","/>",	//index=15
				"<path","/>",		//index=16
				"<ellipse","/>",	//index=17
				"<circle","/>",		//index=18
				"<esite","/>",		//index=19
				"<egpmb","/>",		//index=20
				"<use","/>"			//index=21
				};

//���Թؼ���
char  *atrkwd[]={"id","attrib","fill","stroke","stroke-width","points",
				"x","y","cx","cy","r","rx","ry","width","height","d","fill-opacity",
				"font-family","font-size","writing-mode","text-anchor","font-style"};

//-------------------����汾�Ĺؼ���------------------------------------------------
//��ʽ:��ʼ����������
char *svgkwdn[]={"<?xml","?>",       //index=0
				"<!DOCTYPE",">",	//index=1
				"<!--","-->",		//index=2
				"<svg",">",			//index=3
				"</svg",">",		//index=4
				"<title",">",		//index=5
				"</title",">",		//index=6
				"<defs",">",		//index=7
				"</defs",">",		//index=8
				"<g",">",			//index=9
				"</g",">",			//index=10
				"<rect","/>",		//index=11
				"<text",">",		//index=12
				"</text",">",		//index=13
				"<line","/>",		//index=14
				"<polyline","/>",	//index=15
				"<path","/>",		//index=16
				"<ellipse","/>",	//index=17
				"<circle","/>",		//index=18
				"<esite","/>",		//index=19
				"<egpmb","/>",		//index=20
				"<use","/>",		//index=21
				"<style",">",		//index=22
				"</style",">",		//index=23
				"<symbol",">",		//index=24
				"</symbol",">",		//index=25
				"<polygon",">",		//26
				"<metadata",">",	//27
				"</metadata",">",	//28
				"<a",">",			//29
				"</a",">",			//30
};

char *svgsubkey[]={
				"<metadata",">",				//0
				"</metadata",">",				//1
				"<cge:PSR_Ref","/>",			//2
				"<cge:Meas_Ref","/>",			//3
				"<cge:MeasValSource_Ref","/>", //4
				"<cge:Layer_Ref","/>",			//5
				"<cge:CN_Ref","/>"				//6
};

//���Թؼ���
char  *atrkwdn[]={"id","attrib","fill","stroke","stroke-width","points",
				"x","y","cx","cy","r","rx","ry","width","height","d","fill-opacity",
				"font-family","font-size","writing-mode","text-anchor","font-style"};

//SVG����
char  *svgtype[]={"<!--Visual system By SICUAN UNIVERSITY  PowerGroup-->",//�Ĵ���ѧ
					""};


//��ѹ�ȼ�����
char *kvlev[]={
	"BV-6KV",
	"BV-10KV",
	"BV-14KV",
	"BV-15KV",
	"BV-18KV",
	"BV-20KV",
	"BV-35KV",
	"BV-66KV",
	"BV-110KV",
	"BV-220KV",
	"BV-330KV",
	"BV-500KV",
	"BV-750KV",
	"BV-1000KV",
	"kv-1"
	};

/*char *lst_vl[]={"1100kV","750kV","500kV","330kV","220kV","154kV","110kV",
			  "66kV","63kV","35kV","20kV","18kV","15.75kV","13.8kV",
			  "10kV","6kV","3kV","0.38kV","0.23kV","0.1kV","500kVֱ��"};*/

int kvn[]={15,14,13,12,11,10,9,7,6,4,3,2,1,0,0};


//�Ĵ�ʡ���豸�ؼ���

char *scdkey[]={"Brk",		//��·��
				"Switch",	//����
				"PT",		//PT
				"ground",	//�ӵ�
				"Generator",//�����
				"Tr_2W",	//2�ı�
				"Tr_3W",	//3�ı�
				"Reactor",	//�翹��
				"Capacitor" //������
				};
char *scskey[]={"SCADA",	//SCADAӦ��
				"NAS"		//�߼�Ӧ��
				};


char *DEVTYPEKEY[]={":LO",	//����
					":BUS",
					":ACL",
					":COG", //��緢���
					":TRF",
					":SHU", //���ݵ翹
					":HYG"  //ˮ��
};

//��Ӧ���豸����
int DEVNUM[]={4,3,1,0,6,7,0};


char *DEVXSTYPE[]={".MW",".MVAR","_P","_Q","_V",".KV"};
