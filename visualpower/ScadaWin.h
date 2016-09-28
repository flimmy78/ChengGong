#if !defined(AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_)
#define AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScadaWin.h : header file
//
#include "resource.h"
#include "mytips.h"
#include "gdata.h"
#include "nettpy.h"
#include "middll.h"
#include "Lowfwin.h"
#include "dmjsdlg.h"
#include "readrltd.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FUN_STATUS//���ӻ�����״̬
{
	FUN_BASE=0,		//��������״̬
	FUN_DGXBUS=1,	//ĸ�ߵȸ���
	FUN_DGXBUSL=2,	//ĸ�ߵȸ��ߵ�
	FUN_DGXBUSH=3,	//ĸ�ߵȸ��߸�
	FUN_DGXLINE=4,	//����ߵȸ���
	FUN_DGXTRAS=5,	//��ѹ���ȸ���
	FUN_DGXLOAD=6,	//���ɵȸ���
	FUN_DMFLOW=7,	//���泱��
	FUN_SENOPR=8,	//������
	FUN_REVGEN=9,	//���������
	FUN_REVGENQ=10,	//������޹�����
	FUN_REVTRANS=11,//��ѹ������
	FUN_TRANSTEMP=12,//��ѹ���¶�
	FUN_N1BUS=13,	//N1ĸ��
	FUN_N1BRA=14,	//N1֧·
	FUN_N1ALL=15,	//N1ȫ��
	FUN_N1BUSF=16,	//Ԥ��N1ĸ��
	FUN_N1BRAF=17,	//Ԥ��N1֧·
	FUN_N1ALLF=18,	//Ԥ��N1ȫ��
	FUN_N1EFT=19,	//N1Ӱ��
	FUN_ZONE=20	,	//������Ϣ
	FUN_SPIE=21,	//ϵͳ��ͼ
	FUN_SOE=22,		//SOE�ط�
	FUN_LOWF=23		//��Ƶ��
};
/////////////////////////////////////////////////////////////////////////////
// ScadaWin window

class ScadaWin : public CWnd
{
// Construction
public:
	ScadaWin();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Attributes
public:
	CDIB mbg;				//��������
	CDIB msr;				//��ʾ����
	int winmode;			//��ǰģʽ 0=�Ӵ��� 1=ȫ����ʽ
	int t1,t2;				
	int wx,wy;				//���ڳߴ�(���ص�λ)
	HWND   SvWnd;			//��ѹ����ʱ�޼��ӵĴ���
	CRect  svcrt;			//sv���ڵ�λ��
	MyTips   twin;			//��ʾ����
	DmJsDlg  dmwin;			//������Ӵ���
	int dx,dy;				//ͼ�κ���Ļ��ƫ����(���ص�λ)
	int cursor,rcursor;		//��ǰ���״̬
	int enabletimer;		//��ʱ���Ƿ���Թ���
	//ͼ���������ò���
	CNetTpy nettp;
	//�ȸ���
	BYTE *pb;				//����ĵȸ���ֵ
	//�ȸ���
	CSysContour sct;		//�ȸ��߲���
	//�����ȱ�ǵ�
	DPOINT  senpoint;
	int		sentype;		//��ǰ����������
	//��������
	CDRect  dmsrt[10];		//������ʾ�������ȷ��
	DMSECT  dms[10];		//����
	int     dmsum;			//������
	/////////��Ƶ�𵴷Ŵ󴰿�///////////
	POINT lfpos;			//��ʾλ��
	Lowfwin lwin;
	////////////////////////////////////
	//���ѹ��ǰ�Ĳ���
	double dzoom;			//ѹ��ǰ�ķŴ���
	int    ddx,ddy;			//ѹ��ǰ��ƫ����
	int    dangle;			//ѹ��ǰ�ĽǶ�
	int    dlk;				//ѹ��ǰ�ĸ���״̬
	//////���������˵����ܵĲ���///////////////////
	int n_ge;		//���������
	int n_tr;		//��ѹ������
	int n_sh;		//����������
	int n_se;		//��������ʾ
	int n_pie;		//�����ͼ
	int n_spe;		//ϵͳ��ͼ��
	//���泱��ͳ���û�ͼ����
	POINT ptpoly[300];//���300����
	int   polysum;	  //����ε���
	int   segsum;	  //����
	int   dmsdot[10]; //ÿ���յ㣬��һ�����Ϊ0 �ڶ������Ϊ��һ���յ�+1
	POINT dmpt[500];  //���300����
	/////////////////////////////////////////////////
	gdata dbm;       //���ݶ���
	ReadRltD rrd;	 //���ݿ��ȡ����
	//�߳̾������
	HANDLE  hThread_rd;
	DWORD   dwThreadID;
	int		allupdate;
	////////////////////////////////////////////////////////////
	FUN_STATUS m_PreFun;	
	FUN_STATUS m_CurFun;
	////////////////////////////////////////////////////////////
// Operations
public:
	void SetLineSccData(DLDL &sc);
	void SetSwtSccData(DLDL &sc);
	void CleaseDlFlash();
	void SetCurDbf(int newdbzt);
	bool FileOpen(char *filename,int pageno,HISHMI *hmi=NULL,int mode=0);
	void Set3DEnv();
	void ToMyZm(double zmx);
	void SetCurHisDTime();
	void ResetAllData(int ele=0);
	void ReadHisData();
	void RegistHisAllDev();
	void SetN1Data(int n1type,N1Data *data,int num);
	void FlowSel(int sel);
	void SetDgxParam();
	void CloseLowfWin();
	void InitLowFData();
	void InitLowFData(LFDATA* pLF);
	void FlwZoomChange();
	void SetStatusZoom();
	void SetStatusBarMsg();
	void CursorChange(int newcursor);
	void ChangeDgxcfg();
	void ZoomChange();
	void ShowActObj(HDC hdc,int x,int y,int k);
	void PrintPage(HDC hdc, BYTE pm, int dx, int dy);
	bool SetFlowData(int i,READDEV  &ran);
	void CreateAllrgn();
	bool UpdateAllData();
	void InitMoveObj(HISHMI *hmi=NULL,int mode=0);
	void ComputZCenter();
	void ShowA(CDIB&mdc);
	void SetFirstPosition();
	void FreeMem();
	void DrawShow();
	void EndShow();
	void Order3dPos();

	void Show3DObj(CDIB&mdc,CRect rt);
	void Show3DObjj(CDIB&mdc,CRect rt);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScadaWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReadN1EFT();
	void SetCurFunction(FUN_STATUS newfun);
	void CleaseSwtSoe();
	void CollectN1Device();
	void TurnToLowF();
	void LoadPreDefineSfw();
	void GetCurHmi(HISHMI &newhmi);
	virtual ~ScadaWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(ScadaWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewdev();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLowzoom();
	afx_msg void OnMainPage();
	afx_msg void OnResvjs();
	afx_msg void OnDestroy();
	afx_msg void OnCommandRange(UINT id);
	afx_msg void OnAvcopt();
	afx_msg void OnPqvopt();
	afx_msg void OnN12eft();
	afx_msg void OnN12eft3d();
	afx_msg void OnGenmsg();
	afx_msg void OnTranmsg();
	afx_msg void OnSvopt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetN1EftData(N1Data *data,int num);
	bool GetN1Sel(DWORD &dwID,int &type,float &fSec);
	void ComputScc();
	bool SelIsGen();
	bool SelIsTran();
	void SetANewSoe(NSOES &asoe);
	void DmFlowSwitch();
	void AddDmPt();
	void RegistHis();
	bool ComputShowByRt();
	//��ʾ�ȸ���
	void ShowDgx(CDIB&mdc);
	void Rotate();
	void ShowDynObj(HDC hdc);
	void ShowSelFlag(HDC hdc,int sx,int sy);
	void CollectDevice();
	
	void RButtonMenu(CPoint point);
	void DrawStatArea();
	void ZoomInOut();
	HWND GetSlfCtl(int id);
	void SetSenData(READSEN&sn);
	void MovePic(CPoint point);
	void MouseMove(CPoint point);
	void MouseOnPush(UINT nFlags,CPoint point);
	int  GetCursor(CPoint point);
	void PartZoom(CRect rt);
	void RunPushCmd(int j);
	void ComputSen();
	void UserSflw();
	void SectFlw();
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void AddPoint(CPoint point);
	void DrawXorRect(CRect rt);
	void MouseLBUp(CPoint point);
	void MouseLBDown(CPoint point);
	
	void CheckPopTips();

	CString PhraseType(BYTE bType, BYTE bSB);

	void CheckPopTips_WD();//wd 2015-07-09 add

	void Showdtime(HDC hdc);
	void ReSetAllContourVal();
	int  Getspeed(double value,int type=0);
	bool SetAContourVal(int i);
	void ComputActRect(int i);
	void GetActPicMsg(int i);
	bool UpDateSysPie();
	bool UpDateMttxt();
	bool UpDatePPie();
	void UpDateAct();
	bool UpDateBar();
	void UpDateMeter();
	void UpdateGifaml();
	bool UpdateStatus();
	bool UpdateTranformer();

	bool UpdateStation();

	bool UpdateBus();
	bool UpdateFlow();
	bool UpDateAnl();
	bool UpDatePie();
	bool UpdateDmData();
	void SetContourParam();
	void SetRRevSen();
	void GetRevSenSum();
	void GetObjFromDbm();
	void Show(HDC hdc, CRect rt);
	void PaintShow(HDC hdc, CRect rt);
	void ChangeAllSft();
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas);
	void ComputMaxXY();
	void ShowC(HDC hdc,HRGN hrgn);
	void ShowC(HDC hdc,CRect rtshow);
private:
	void  SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j);
	void  PlayHis();
	void  PlaySoe();
	void  AddN1Data(N1BAR &nbar);
	void  CreatePaintRgn();
	HRGN  GetLookDownRgn(HRGN oldrgn);
	HRGN  GetFlowUpdateRgn();
	HRGN  GetLowUpdateRgn();
	void  GetDevSum();
	void  SetDynMeter();
	bool  SelCanZoomLowF();
	void  UpdateLowFData(RFLOW &fw);
	bool  NeedDrawDgx();
	void  ShowFuntTitle(CDIB&mdc,CRect rt,int type);
	bool  ZoomInCheckBus();
	bool  PartZoomChkBus();
	bool  ZoomOutCheckBus();
	bool  ZoomOutApdOpen();
	bool  ZoomInApdOpen();
	

	double oldzm;	//ԭ�зŴ���
	double  vx,vy;	//�Ŵ����ĵ�
	int oldsel;
	CRect srt,oldrt;
	CPoint pt1,pt2,oldpt;
	int xmax,ymax;
	int dnbz;
	int oldang; //ԭ���ĽǶ�
	BYTE  seltype,selsubtype;//��ǰѡ�������
	int   seljlh;			 //��ǰѡ���¼��
	int   dsjlh;			 //ѡ���豸������Դ��¼��
	char  selid[32];		 //ѡ���źŵ�����
	//��������������ʾ������ʾ
	CPoint tpint;	  //��ʾ��ռλ��
	int otype,ostype; //ѡ��ľ���ʾ����
	int oldcur;		  //�ɹ��
	int oldjlh;		  //�ɼ�¼��
	
	//////////////����ʱ����ָ��/////////////////////
	RANL  *r_an;    //ģ����
	int   ansum;    //ģ��������
	RMTXT *r_mt;	//�����ı�����
	int   mtsum;	//����
	RRES  *r_rs;	//ˮ��
	int   rssum;	//ˮ������
	RSTA  *r_st;	//״̬���Ͳ����豸
	int	  stsum;	//����
	ROBJ  *r_da;	//���ڶ���  
	int   dtsum;	//����
	ROBJ  *r_tm;	//ʱ�����
	int   tmsum;	//����
	RAML  *r_am;	//��������
	int   amsum;	//����
	RSCRTXT *r_sc;	//�����ı�����
	int   scsum;	//����
	RSELFCTL *r_sf; //�����ؼ�
	int   sfsum;	//����
	RFLOW *r_fw;	//������
	int fwsum;		//����	
	RPUSH    *r_ph; //��ť
	int phsum;		//����
	RACTOBJ  *r_at; //�����
	int atsum;		//����
	RBAR     *r_ba; //��ͼ
	int basum;		//����
	RPIE     *r_pe; //��ͼ����
	int pesum;		//����
	RSPIE    *r_spe; //ϵͳ��ͼ
	int  spesum;
	RBUS     *r_bs; //ĸ��
	int bssum;		//����
	RCONL    *r_cl; //������
	int clsum;		//����
	RMETER   *r_yb; //�Ǳ�
	int ybsum;		//����
	RFLASH   *r_fsh;//FLASH����
	int fssum;		//����
	RPPIE    *r_ppie;//�ٷֱ�ͼ����
	int ppsum;		//����
	RSEN  *r_sen;	//������
	int    sesum;	//�����ȸ���
	RREV  *r_rv;	//��Ҫ����3DBAR��ʾ���� ���������,�����������豸(Ŀǰ)
	int    rvsum;	//���ö�����ʾ����
	RREV  *r_tr;	//��ѹ������
	int   trsum;    //��ѹ������
	RZONE  *r_zn;	//����
	int    znsum;	//�������
	RSWT   *r_sw;	//����
	int    swsum;	//��������
	int dtupdate;   //ʱ����±�־
	
	////////////////////////////////////////
	HRGN updatergn;	//ˢ������
	////////////////////////////////////////
	N1BAR   *r_n1;
	int     n1sum;
public:
	void ChangeShow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_)
