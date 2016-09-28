// gdata.h: interface for the gdata class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_)
#define AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pwptdef.h"


class gdata
{
public:
	gdata();
	virtual ~gdata();
public:
	void ShowTy(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowBgDbx(CDIB &mdc,int dx,int dy,CRect rt,int high);
	void ShowStatic(CDIB &mdc,int dx,int dy,CRect rt);
	void MSDownShow(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowAct(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowBkgd(CDIB&mdc,CRect rt);
	bool CheckFileIndex(char *filenm, int index);
	bool ZoomPage(int mode);
	bool OpenPwFile(char *fname,int pageno);
	bool OpenHisPwFile(char *hisfile,char *hmifile,int pageno);
	void FreeMem();
	int  GetMPICRecno(int id);
	int  GetPICRecno(int id);
	int  GetEGPRecNo(int id);
public:
	void ShowSwtSccBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void ShowSwtSccBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	bool IsOpenedFile(char *newfile);
	void GetDevObjToTy();
	void FreeMemTyLayer();
	void GetObjRect(CRect &rt);
	DWORD GetDefColor(int index,float val);
	void AddRtnHmi(HISHMI &newhmi);
	bool GetARtnHmi(HISHMI &hmi);
	void SignPaintObj(HRGN hrgn,int dx,int dy);
	void GetSectFLwName(char *nm);
	void Showdms(CDIB&mdc, int dx,int dy,DMSECT *dm,int dmsum,CDRect *srt);
	bool LastHmiIsMode1();
	void ComputeZnZoom(RPIE *r_pe, int pesum,int wy);
	void ComputeSenzomm(RSEN *r_sen,int sesum,int wy);
	void ComputeTpzoom(RREV *r_tr,int trsum,int wy);
	void ComputeTptzoom(RREV *r_tr, int trsum, int wy);
	void ComputePqZoom(RREV *r_rv,int rvsum,int wy);
	void CreateN1EftRgn(N1BAR *r_n1,int n1sum);
	void CreateSPieRgn(RSPIE  *r_spe,int spesum);
	void CreateZnRgn(RPIE  *r_pe,int pesum);
	void CreateSwtSccRgn(RSWT *r_sw,int swsum);
	void CreateSwtRgn(RSWT *r_sw,int swsum);
	void CreateN1Rgn(N1BAR *r_n1,int n1sum);
	void CreateFlwRgn(RFLOW *r_fw,int fwsum);
	void CreateResRgn(RRES  *r_rs,int  rssum);
	void CreateSenRgn(RSEN  *r_sen,int sesum);
	void CreateRevRgn(RREV  *r_rv,int rvsum);
	void CreateTranRevRgn(RREV  *r_tr,int trsum);
	void CreateTranTRgn(RREV  *r_tr,int trsum);
	void SHowN1EftBarj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowN1EftBar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowSpieBarj(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum);
	void SHowSpieBar(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum);
	void SHowZoneBarj(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum);
	void SHowZoneBar(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum);
	void SHowSwtBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void SHowSwtBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void SHowN1Barj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowN1Bar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowTranTBar(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranTBarj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowGenBarQ(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowGenBarQj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowSenBarj(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum);
	void SHowSenBar(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum);
	bool FindAGenCircle(int id,CDRect &rt,CDRect zrt);
	void TJObjSum(int *objsum);
	bool GetChildSendMsg(int id_in, int&id_out, HWND&hwnd);
	void SetChildMenu(HWND hwnd,HMENU hm);
	bool GetALastHmi(HISHMI &hmi);
	void AddOpenHmi(HISHMI &newhmi,char mode=0);
	void LoadShowSet();
	void SaveShowSet();
	void SaveToJpg(HWND hwnd,int width,int height,char *fname);
	void SaveToBmp(HWND hwnd,int width,int height,char *fname);
	void PrintShow(HDC hdc, BYTE pm, int dx, int dy);
	//���������
	N_PAGEPWF  page;			//�����ҳ��
	N_layer    *clayer;			//��ǰ��
	int		   curpage;			//��ǰҳ��
	N_APDINFO  apd;				//���ӿ�����Ϣ
	int        apdenable;		//������Ϣ�Ƿ���Ч
	////////////ͶӰ���豸////////////////////////
	N_LAYER  tylayer;			//ͶӰ��
	char       filename[256];	//�����ļ���
	//-------------------------------------------
	//�����е�״̬
	int selbz;					//��ѡ��Ķ���
	//��ʷ�򿪵Ľ���
	HISHMI  hishmi[32];			//���Է��ص�ǰ��32������
	int		curhmi;				//��ǰhmi
	HISHMI  rtnhmi[32];			//��Ҫ���صĽ���32��
	int     currtn;			    //��ǰ���ص�λ��
	//�ؼ��˵����ձ�
	CTLMENU   ctlmenu[200];		//���200��
	int cmsum;					//��ǰӦ������
	int popsum;					//�����˵�����
	//��ʼ���ļ�
	char curfile[256];			//��ǰ�����ļ��� 
	//����λͼͼ�λ��嶨��
	//СͼƬ
	N_SMALLPIC  spic[MAXSPIC];	//СͼƬ ���ΪMAXSPIC
	int spicsum;				//ͼƬ����
	//�ڴ�ͼƬ
	N_MemPic  mpic[100];		//�ڴ��е�ͼƬ
	int mpicsum;				//ͼƬ��,���=100
	//���ͼԪ
	N_ELEGRP egp[MAXEGRP];		//���ͼԪ
	int egpsum;					//��ǰ�����ͼԪ��
	//////��ʾ��������
	SHOWCFG  scf;				//��ʾ��������
	//������״̬
	int msdwn;					//�������Ƿ���0=δ���� 1=���� 
	//���ݿ�״̬
	int  dbzt;					//��ʷ�����״̬ 0=���� 1=�����ʷ
	//���ֱ�־
	////////��ǰ����ʾ����///////////////////////////////////
	double curzoom;				//��ǰ�ķŴ���
	int    zw,zh;				//��ǰ��ͼ�ο���
	int	   curang;				//��ǰ��ת�Ƕ�0-360;
	int    lookdown;			//���� 0=���� 1=����
	/////////////////////////////////////////////////////////
	//��������ð�ͼ�����Ŵ����
	float  pqzm;				//�Ŵ����
	float  hbas;				//�����߶�
	/////////////////////////////////////////////////////////
	int		n1bz;
	double	n1zm;			  //n-1ĸ��
//	double	n1linezm;         //n-1֧·
	/////////////////////////////////////////////////////////
	//��ʷ�طŲ���
	time_t hlist[2048]; //��ʷ�����б�
	int    hsum;		//��ʷ������
	int    hisjs;		//��ʷ�طż���
	int    hspeed;		//��ʷ�ط��ٶ�
	BOOL   hdbok;		//��ʷ����
	int    curtm;		//��ǰʱ��
	int    hisplay;		//���ڲ��ű�־
	/////////////////////////////////////////////////////////
	CDIB   *msr;        //����������ָ��
	/////////////////////////////////////////////////////////
	int     curopzt;	
	//��ǰ����״̬  0=���� 1=���泱�� 2=������ 3=��Ƶ�� 4=��ʷ�ط� 
	//				5=soe�ط� 6=��·���� 
	//////////////////SOE�ط�����////////////////////////////
	NSOES  *soe;	//SOE����
	int    soesum;	//SOE����
	/////////////////////////////////////////////////////////
	double znzoom;	//������ͼ�Ŵ���
private:
	void AddTyAObject(N_BASATTR &attr, void *obuf);
	bool PosIsOk(double x,double y,int start);
	void CreatePctpie();
	void AddCurLayerAObject(N_BASATTR &attr, void *obuf);
	void AddPctPie(double x,double y,int id,int lindex,char *name);
	void ShowDaoBan(CDIB&mdc,CRect rt);
	void SetScfDefaultvalue();
	void GetMenuItem(HWND hwnd,HMENU hmenu);
	void FillBgImg(HDC hdc,CRect rt,int k);
	void AddAEGP(int num, int index, N_BASATTR &attr, void *obuf);
	bool AddAEmptyEGP(int type);
	bool LoadPage(FILE *fp,WORD ver);
	void LoadMemPic(FILE *fp);
	void LoadEGP(FILE *fp,WORD ver);
	void LoadSPic(FILE *fp);
	void InitParam();
	void FreeEgp(int num, int index);

public:
	///////////////////������ʾ///////////////////////////////
	void DeletePlate(long id, BYTE newValue);
	void AddPlate(PlateInfo pltinfo);
	PlateInfo m_PlateInfo[MAXPLATE];		//������Ϣ��¼
	int m_PlateNum;							//������

	void ShowPlatte(CDIB& mdc);		//��ʾ����
};

#endif // !defined(AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_)
