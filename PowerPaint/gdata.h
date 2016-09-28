// gdata.h: interface for the gdata class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDATA_H__241A9042_8DEB_4462_BD92_5872D20842FC__INCLUDED_)
#define AFX_GDATA_H__241A9042_8DEB_4462_BD92_5872D20842FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ptdefine.h"
#include "base0.h"



class gdata  
{
public:
	gdata();
	virtual ~gdata();
	int  dx,dy;				//��ĻX,Y�����ƫ����
	CPoint mpoint;			//��ǰ���λ��

	int  dnbz;
	char drawbz;			//������־
	char editbz;			//�༭����־
	int  ctndraw;			//�������Ʊ�־


	CDRect  selrt,mselrt;
	CDPoint srt[4];			//ѡ��������


	CPoint tpt[1000];		//���400��,��̬��ʾ������
	int  tptsum;			//tpt�ĵ���

	CDPoint cp[8];			//ѡ��ĵ�
	int    cpsum;			//����ѡ�����
	DPOINT *spt;			//ѡ������
	int  selptsum;			//ѡ�����
	int  objclose;			//����ķ��״̬

	int  selbz;				//��ѡ��Ķ��� 0=û�� 1=���ѡ����� 2=����
	int  selop;				//����0-8;
	int  selrgn;			//�����־

	CPoint oldpt1;			//�ɵĵ�
	
	//�������󻺳���
	BASE0 *cpyobj;			//�������󻺳���
	int  cpysum;			//�����������
	//����������
	BASE0 *gbobj;			//�������󻺳���
	int   gbsum;			//�����������
	int   pwidth;			//��ʴ�С

	int  firstsel;			//��һ��ѡ��Ķ���
	int  selnum;			//ѡ��Ķ������
	int  nextstart;			//�´�ѡ��Ŀ�ʼ��
	HRGN hrgn;				//�м��ƶ�����������
	int  movebz;			//�༭״̬
	//�ļ�
	char pwfname[512];		//�ļ���
	char filebz;			//�ļ���Ч��־
	//��ǰ���ݿ�
	bool  dbfok;			//���ݿ��Ƿ�ѡ��� false=ƽ̨δ���� true=ƽ̨�ɹ�


public:
	bool LoadSvgAndSave(const char* pSvg,const char* pPw0);
	void GetEleFromClipboard(HWND hwnd);
	void ExchangeCimName();
	void SetLastDevName(char *name,char *pname,int type=-1,int subtype=-1);
	void ClpToMem(HGLOBAL hglb);
	void ImportSvgFile(char *filename);
	void SaveFileSvg(char *filename);
	void ClearSelect2();
	void MoveConLine(double mx,double my);
	void ModiFont(LOGFONT&lf);
	void DeleteObjectByid(DWORD id);
	void DelNoUseMpic();
	bool IsMpicIsInUse(WORD id);
	void SendFileTo(char *filename);
	void SendHmiToSvr();
	void CopyFileTo(char *filename);
	void CopyToHmiDir();
	void SetColor(DWORD color);
	void SetFont(LOGFONT &lf);
	void SetVLevel(BYTE vl);
	void ReComputeAllSitePos();
	bool DelCurLayer();
	bool DelCurPage();
	int  GetObjSum(int type);
	void TestShow(CDIB &mdc,int sdx,int sdy,CRect rt);
	void TestShow1(CDIB &mdc,int sdx,int sdy,CRect rt,int mode=0);
	void TestShow2(CDIB &mdc,int sdx,int sdy,CRect rt);
	void PrintShow(HDC hdc, BYTE pm, int dx, int dy);
	void ReComputeSitePos();

	void DelAAppendInfo(BYTE pageno);
	int  GetIndexOfAppInfo(BYTE pageno);
	void AddAppendInfo(N_APDINFO&inf);

	BASE0 *FindObject(DWORD id);
	int  GetObjectNo(DWORD id);
	void ComputNewRect();
	void AlignDstY();
	void AlignDstX();
	void AlignHeight();
	void AlignWidth();
	void AlignBottom();
	void AlignTop();
	void AlignRight();
	void AlignLeft();
	void CalRalation();
	bool CanBindlineSel();
	void SingleEGrp();
	bool BindLine();
	bool CutLine(CPoint point);
	bool SubLineDot(CPoint point);
	bool AddLineDot(CPoint point);
	bool FindALineDot(CDRect ert,DPOINT &ept);
	void CutMpicNoUse();
	void CutImgRgn();
	void ShowRgn(HDC hdc, int style,int sdx,int sdy);
	CRect AddBrightImg(CPoint point);
	CRect BrushImage(CPoint point,DWORD color);
	CRect TranImage(CPoint point);
	CRect CutImage(CPoint point);
	void ClearImgBg(CPoint point);
	void AddPasteImg(HBITMAP hbmp);
	bool SelIsThisType(BYTE type);
	bool GetProcImgBuf(BYTE **buf, int &w, int &h);
	bool AddNewLayer();
	bool AddNewPage();
	void SaveToBmp(char *fname);
	void SaveToJpg(char *fname);
	bool OpenPwFile(char *fname);
	void SaveFile(const char *fname);
	void FreeMem();
	void SelObjToButtom();
	void SelObjToTOP();
	void ShowPage(CDIB &mdc,int npage, int sdx, int sdy);
	void ShowLayer(CDIB &mdc,int nlayer, int sdx, int sdy);
	void LayerChange(int newlayer);
	bool EgrpInUse(int id);
	void PreShowEGP(CDIB&mdc,int num, CRect rt,int index,DWORD color=0,int showsite=0);
	void PasteObject(double nx,double ny);
	bool CanRotate();
	void SqrtObj();
	void StraightObj();
	void DelSelObj();
	void CopyToCpyBuf(HWND hwnd);
	int  GetSelSum();
	int  GetNoUseID(int type);
	void EndMoveObject();
	void MoveObject2(double mx,double my);
	void MoveObject1(double mx,double my);
	int  GetCursor(CPoint point);
	void ShowSelectDot(CDIB&mdc,int sdx,int sdy);
	int  GetPageObjSum(int ip);
	int  GetObjSum();
	void CreateMoveRgn();
	bool SelManyObject(CRect rt);
	bool SelAObject(CPoint point,int k);
	void ClearSelect();
	void SetImgToBg(int id);
	int  GetFirstSelObj(int start=0);
	bool SpicInUse(int id);
	void SetColorToBg(DWORD color);
	void GoToPage(int pageno);
	void ShowWaterLine(HDC hdc,int sdx,int sdy,CRect rt);
	void ParamChange();
	bool ZoomPage(int mode);
	void InitParam();
	void ShowBkgd(CDIB&mdc,CRect rt,int npage=-1);
	void Showobject(CDIB &mdc, int sdx, int sdy,CRect rt,int mode);
	void AddAObject(N_BASATTR &attr, void *obuf,int undo=0);
	bool IsexistId(DWORD id);
	int  GetNewID();
	N_PAGEPWF  page[MAXPAGE];   //���MAXPAGE��
	char       pagesel[MAXPAGE];//ͼ��ѡ���־
	N_PAGEPWF  *cpage;			//��ǰҳ���ַ
	N_layer    *clayer;			//��ǰ��
	N_APDINFO  *apdinfo;		//������Ϣ
	int  curpage;				//��ǰҳ��
	int  pagesum;				//ҳ������
	int  apdsum;				//������Ϣ����
private:
	void MoveInLineDot(BASE0 &bs,double mx,double my);
	void DelLayer(N_layer&dlayer);
	int  HaveDevice();
	int  GetAllObjSum();
	void ClearRalation();
	bool SerchConnect(D_SITEC&sit);
	void MoveConLine(BASE0&bs,int index);
	void MoveFlow(BASE0&bs,int index);
	void MoveEleGrp(BASE0&bs,int index);
	void ComputEsitRect(BASE0&bs);
	void MoveEsite(BASE0&bs);
	HDC  GetProcImgDC(int&mode,int &x,int &y);
	bool LoadPage(FILE *fp,int pg,WORD ver);
	int  SavePage(FILE *fp, int pg);
	void AObjToTop(int j);
	void AObjToButtom(int j);
	void AddGbObj(N_BASATTR &attr, void *obuf);
	void DeleteAObject(int j);
	void AddCpyObj(N_BASATTR &attr, void *obuf);
	void FreeCpyObj();
	void ShowObjSelState(CDIB &mdc, BASE0 &bs, int dx, int dy,DWORD color);
	CDRect ComputOldRect();
	void ComputRect();
	void SetOpPoint(BASE0&bs);
	void FreeGbObj();
	void FillBgImg(HDC hdc,CRect rt,int k);
};

#endif // !defined(AFX_GDATA_H__241A9042_8DEB_4462_BD92_5872D20842FC__INCLUDED_)
