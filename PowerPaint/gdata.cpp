// gdata.cpp: implementation of the gdata class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gdata.h"
#include "comobj.h"
#include "middll.h"
#include "filev30.h"
#include "svgout.h"
#include "ImportSvg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern comobj cobj;

//ͼ��Ԫ�ر�����
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

gdata::gdata()
{
	InitParam();
	dbfok=false;							//���ݿ��Ƿ�ѡ���
}

gdata::~gdata()
{
	FreeMem();
}

//�ͷ���Դ
void gdata::FreeMem(){
	int i,j,k;
	//ɾ������
	for(i=0;i<pagesum;i++)
	{
		for(j=0;j<page[i].laysum;j++)
		{
		  if(page[i].layer[j].objnum>0)
		  {
			for(k=0;k<page[i].layer[j].objnum;k++)	page[i].layer[j].obj[k].FreeMem();	
			free(page[i].layer[j].obj);
			page[i].layer[j].obj=NULL;
		  }
		  page[i].layer[j].objnum=0;
		}
		page[i].laysum=0;
	};
	if(hrgn!=NULL) DeleteObject(hrgn);
	//�������������
	FreeCpyObj();
	//���������
	FreeGbObj();
	InitParam();
	//���������Ϣ��
	if(apdinfo!=NULL) delete apdinfo;
	apdinfo=NULL;
	apdsum=0;
	pagesum=0;

};

void gdata::InitParam()
{
	int i,j;
	for(i=0;i<MAXPAGE;i++)
	{
		page[i].index=(BYTE)i;
		page[i].zh=980;
		page[i].zw=1280;
		page[i].head.BgColor=0;			//0xc0c0c0;
		page[i].head.height=980;
		page[i].head.width=1280;
		page[i].head.imgID=-1;
		sprintf(page[i].head.Name,"�»���ҳ%d",i);
		page[i].laysum=1;
		page[i].curlay=0;
		page[i].head.type=1;
		for(j=0;j<MAXLAYER;j++)
		{
			sprintf(page[i].layer[j].name,"ͼ��%d",j);
			page[i].layer[j].select=1;
			page[i].layer[j].show=1;
			page[i].layer[j].obj=NULL;
			page[i].layer[j].objnum=0;
		}
	}
	curpage=0;
	cobj.curzoom=1;
	pagesum=1;
	nextstart=0;
	hrgn=NULL;
	movebz=0;
	ctndraw=0;
	cpyobj=NULL;
	cpysum=0;
	gbobj=NULL;
	gbsum=0;
	pwidth=10;
	pwfname[0]=0;
	filebz=0;
	dnbz=0;
	selbz=0;
	tptsum=0;
	selptsum=0;
	selrgn=0;
	firstsel=-1;
	drawbz=0;
	editbz=0;
	cpage=&page[0]; //��һ��������Ϊ��ǰҳ��
	clayer=&page[0].layer[0];
	apdinfo=NULL;
	apdsum=0;
	dx=0;
	dy=0;
	selnum=0;
}
//����һ��δ�õ�ID(Ψһ)
int gdata::GetNewID()
{
	int i,j;
	j=GetAllObjSum()+1;
	for(i=0;i<j;i++){
		if(!IsexistId(i+1)) return i+1;
	}
	return 1;
}

//�鿴��ID�Ƿ����
bool gdata::IsexistId(DWORD id)
{
	int i,j,k;
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].laysum;j++){
			for(k=0;k<page[i].layer[j].objnum;k++){
				if(page[i].layer[j].obj[k].attr.ID==id) return true;
			}
		}
	}
	return false;
}



//���ص�һ����ѡ�еļ�¼��
int gdata::GetFirstSelObj(int start)
{
	int i;
	for(i=start;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1) return i;
	};
	return -1;
}

//��ʾͼԪ
void gdata::Showobject(CDIB &mdc, int sdx, int sdy,CRect rt,int mode)
{
	//mode=0;ȫ��ʾ =1��ʾ���б�ѡ�еľ�ֹͣ
	//2=�ӱ�ѡ�еĵط�����ʾ
	DWORD color;
	int i,j,n,start,end,sno,ls,le;
	CDRect rt1,rt2;
	sno=GetFirstSelObj();
	sno=sno==-1 ? clayer->objnum:sno;
	rt1.SetCRect(rt);
	rt1.ScrRtToAct(cobj.curzoom);
	n=5;
	rt1.left-=n;
	rt1.top-=n;
	rt1.right+=n;
	rt1.bottom+=n;
	
	switch(mode)
	{
	 case 0: 
		 start=0;end=cpage->layer[cpage->curlay].objnum;
		 ls=0;le=cpage->laysum;
		 break;
	 case 1: start=0;end=sno;
		 ls=0;le=cpage->curlay+1;
		 break;
	 case 2: start=sno;end=cpage->layer[cpage->curlay].objnum;
		 ls=cpage->curlay;
		 le=cpage->laysum;
		 break;
	 default: return;
	};
	
	for(i=ls;i<le;i++)
	{	
		if(i==cpage->curlay)
		{
		 for(j=start;j<end;j++)
		 {
		  rt2=clayer->obj[j].ort;
		  rt2&=rt1;
		  if(!rt2.IsRectEmpty()) clayer->obj[j].Show(mdc,sdx,sdy);
		  if(clayer->obj[j].sel==1&&movebz==0&&selbz>1)
		  {
			if(j==firstsel) color=0xff0000;else color=0x7f;
			ShowObjSelState(mdc,clayer->obj[j],sdx,sdy,color);
		  }
		  }
		}
		if(i!=cpage->curlay)
		{
		 for(j=0;j<cpage->layer[i].objnum;j++)
		 {
			 if(cpage->layer[i].show==1)
			 {
				rt2=cpage->layer[i].obj[j].ort;
				rt2&=rt1;
			 if(!rt2.IsRectEmpty()) 
				 cpage->layer[i].obj[j].Show(mdc,sdx,sdy);
			 }
		 }

		}
	}
}


//��ʾ��ǰ��ͼ
void gdata::ShowLayer(CDIB &mdc,int nlayer, int sdx, int sdy)
{
	int i;
	if(nlayer<0||nlayer>=cpage->laysum) return;
	for(i=0;i<cpage->layer[nlayer].objnum;i++){
		  cpage->layer[nlayer].obj[i].Show(mdc,sdx,sdy);
	 }
}

//��ʾָ��ҳ��ͼ
void gdata::ShowPage(CDIB &mdc,int npage, int sdx, int sdy)
{
	int i,j;
	if(npage<0||npage>=pagesum) return;
	for(i=0;i<page[npage].laysum;i++){
		for(j=0;j<page[npage].layer[i].objnum;j++){
		  page[npage].layer[i].obj[j].Show(mdc,sdx,sdy);
		}
	 }
}

//������ʾ��ǰҳ
void gdata::TestShow(CDIB &mdc,int sdx,int sdy,CRect rt)
{
	int i,j,n;
	CDRect rt1,rt2;
	rt1.SetCRect(rt);
	rt1.ScrRtToAct(cobj.curzoom);
	n=5;
	rt1.left-=n;
	rt1.top-=n;
	rt1.right+=n;
	rt1.bottom+=n;
	for(i=0;i<cpage->laysum;i++){	
		for(j=0;j<cpage->layer[i].objnum;j++){
			rt2=cpage->layer[i].obj[j].ort;
			rt2&=rt1;
			if(!rt2.IsRectEmpty()){
				cpage->layer[i].obj[j].Show(mdc,sdx,sdy);
			}
		 }
	}
}

void gdata::TestShow2(CDIB &mdc,int sdx,int sdy,CRect rt)
{
	int i,j,n;
	CDRect rt1,rt2;
	rt1.SetCRect(rt);
	rt1.ScrRtToAct(cobj.curzoom);
	n=5;
	rt1.left-=n;
	rt1.top-=n;
	rt1.right+=n;
	rt1.bottom+=n;
	for(i=0;i<cpage->laysum;i++){	
		for(j=0;j<cpage->layer[i].objnum;j++){
			if(cpage->layer[i].obj[j].attr.type<64){
			rt2=cpage->layer[i].obj[j].ort;
			rt2&=rt1;
			if(!rt2.IsRectEmpty()){
				cpage->layer[i].obj[j].ShowBasGrp(mdc,sdx,sdy);
				}
			}
		 }
	}
}

void gdata::TestShow1(CDIB &mdc,int sdx,int sdy,CRect rt,int mode)
{
	int i,j,n;
	CDRect rt1,rt2;
	rt1.SetCRect(rt);
	rt1.ScrRtToAct(cobj.curzoom);
	n=5;
	rt1.left-=n;
	rt1.top-=n;
	rt1.right+=n;
	rt1.bottom+=n;
	for(i=0;i<cpage->laysum;i++){	
		for(j=0;j<cpage->layer[i].objnum;j++){
			if(cpage->layer[i].obj[j].attr.type>63){
			rt2=cpage->layer[i].obj[j].ort;
			rt2&=rt1;
			if(!rt2.IsRectEmpty()){
				cpage->layer[i].obj[j].ShowActGrp(mdc,sdx,sdy,mode);
				}
			}
		 }
	}
}

//��ʾ�����ѡ��״̬
void gdata::ShowObjSelState(CDIB &mdc, BASE0 &bs, int sdx, int sdy,DWORD color)
{
	CDRect art;
	CRect rt,rt1;
	if(bs.attr.type==32) return;
	art=bs.ort;
	art.ActRtToScr(cobj.curzoom);
	art.Offset(sdx,sdy);
	art.GetRECT(rt);
	rt1=CRect(rt.left-2,rt.top-2,rt.left+2,rt.top+2);
	mdc.CRectc(rt1,color,color,0);
	rt1=CRect(rt.right-2,rt.top-2,rt.right+2,rt.top+2);
	mdc.CRectc(rt1,color,color,0);
	rt1=CRect(rt.right-2,rt.bottom-2,rt.right+2,rt.bottom+2);
	mdc.CRectc(rt1,color,color,0);
	rt1=CRect(rt.left-2,rt.bottom-2,rt.left+2,rt.bottom+2);
	mdc.CRectc(rt1,color,color,0);
}
//��ʾ����
void gdata::ShowBkgd(CDIB&mdc,CRect rt,int npage)
{
	int w,h;
	N_PAGEPWF  *dpage;
	CDRect drt;
	CRect  rt2;
	if(npage==-1) dpage=cpage;
	if(npage!=-1) {
		if(npage<0||npage>=pagesum) return;
		dpage=&page[npage];
	}
	if(dpage->head.imgID<0)
	{
		w=rt.Width();
		h=rt.Height();
		mdc.CRectc(CRect(0,0,w,h),dpage->head.BgColor,dpage->head.BgColor,0);
	}

	if(dpage->head.imgID>=0){
		FillBgImg(mdc.m_hDC,rt,dpage->head.imgID);
	}

	if(cpage->head.showbyrt==1)//��ʾ��
	{
		drt.left=cpage->head.x1;
		drt.top=cpage->head.y1;
		drt.right=cpage->head.x2;
		drt.bottom=cpage->head.y2;
		drt.ActRtToScr(cobj.curzoom);
		drt.Offset(-rt.left,-rt.top);
		drt.GetRECT(rt2);
		mdc.CSetLineStyle(1); 
		mdc.CDraw3DRect(rt2,cobj.gcolor,cobj.gcolor);
		mdc.CSetLineStyle(0);
	}
	
}

//��Сͼ��䱳��
void gdata::FillBgImg(HDC hdc,CRect rt,int k)
{
	CRect rt1;
	int i,j,l,x,y,xoff,yoff,nx,ny,imgw,imgh,izw,izh,yx,yy,w,h;
	l=cobj.GetPICRecno(k);
	if(l<0) return;
	imgw=cobj.spic[l].img.nWidth;
	imgh=cobj.spic[l].img.nHeight;
	izw=(int)(imgw*cobj.curzoom);
	izh=(int)(imgh*cobj.curzoom);
	if(imgw<=0||imgh<=0) return;
	yx=abs(rt.left)%izw;
	yy=abs(rt.top)%izh;

	xoff=rt.left>0 ? yx:izw-yx;
	yoff=rt.top>0  ? yy:izh-yy;
	nx=rt.Width()/izw+1; //X������ʾ�ĸ���
	ny=rt.Height()/izh+1;//y������ʾ�ĸ���

	w=nx*izw-xoff;
	h=ny*izh-yoff;
	if(w<rt.Width()) nx++;
	if(h<rt.Height()) ny++;
	for(i=0;i<nx;i++)
	{
		x=i*izw-xoff;
		for(j=0;j<ny;j++)
		{
			y=j*izh-yoff;
			StretchBlt(hdc,x,y,izw,izh,cobj.spic[l].img.m_hDC,0,0,imgw,imgh,SRCCOPY);
 		}
	}
}

//�Ŵ���С mode=0�ָ�ԭʼ�ߴ� 1=�Ŵ� 2=��С
bool gdata::ZoomPage(int mode)
{
	double zr,oldzr;
	double maxzm;
	oldzr=cobj.curzoom;
	maxzm=2;
	switch(cpage->head.type){
	case 0: maxzm=4;  break;
	case 1: maxzm=30; break;
	case 2: maxzm=100;break;
	}
	switch(mode){
	case 0:	zr=1;		    break;
	case 1: 
		if(oldzr>maxzm) return false;
		zr=oldzr*1.1;  
		break;
	case 2: 
		if(oldzr<0.1) return false;
		zr=oldzr/1.1;
		break;
	default:return false;
	};
	cobj.curzoom=zr;
	if(oldzr!=cobj.curzoom){
	 cpage->zw=(int)(cpage->head.width*cobj.curzoom);
	 cpage->zh=(int)(cpage->head.height*cobj.curzoom);
	 return true;
	};
	return false;
}

void gdata::ParamChange()
{
	cobj.curzoom=1;
	cpage->zw=cpage->head.width;
	cpage->zh=cpage->head.height;
}

//��ʾˮ��
void gdata::ShowWaterLine(HDC hdc,int sdx,int sdy,CRect rt)
{
	int i,j,x,y,w,h,hw,mx,my,x1,y1,x2,y2;
	int m,n;
	CRect rt2;
	CDRect drt;
	hw=cobj.gwide;
	w=cpage->head.width;
	h=cpage->head.height;
	m=w/hw+1;
	n=h/hw+1;
	mx=(int)(w*cobj.curzoom+sdx);
	my=(int)(h*cobj.curzoom+sdy);
	w=rt.Width();
	h=rt.Height();
	switch(cobj.gstyle){
	case 0:
		y1=sdy-rt.top;
		y1=y1<0 ? 0:y1;
		y2=my;
		y2=y2>rt.bottom ? rt.bottom:y2;
		for(i=0;i<m;i++){
		 x=(int)((i*hw)*cobj.curzoom)+sdx-rt.left;
		 if(x>=0&&x<=w) GLLine(hdc,x,y1,x,y2,cobj.gcolor);
		 }
		x1=sdx-rt.left;
		x1=x1<0 ? 0:x1;
		x2=mx;
		x2=x2>rt.right ? rt.right:x2;
		for(i=0;i<n;i++){
		 y=(int)((i*hw)*cobj.curzoom)+sdy-rt.top;
		 if(y>=0&&y<=h) GLLine(hdc,x1,y,x2,y,cobj.gcolor);
		 }
	   break;
	case 1:
		for(i=0;i<m;i++){
		 x=(int)((i*hw)*cobj.curzoom)+sdx-rt.left;
		 if(x>=0&&x<=w){
		 for(j=0;j<n;j++){
		  y=(int)((j*hw)*cobj.curzoom)+sdy-rt.top;
		  if(y>=0&&y<=h) SetPixel(hdc,x,y,cobj.gcolor);
  		 }
		 }
		}
		break;
	}
	rt2.left=dx-rt.left;
	rt2.top=dy-rt.top;
	rt2.right=mx+1-rt.left;
	rt2.bottom=my+1-rt.top;
	GLDDraw3DRect(hdc,rt2,cobj.gcolor,cobj.gcolor,1);
	
}

//ֱ�ӵ�ĳһҳ
void  gdata::GoToPage(int pageno)
{
	if(pageno>=pagesum||pageno<0) return;
	//ɾ��������
	FreeGbObj();
	//ת��ָ��ҳ
	curpage=pageno;
	cobj.curzoom=0;
	cpage=&page[curpage];
	cpage->zw=cpage->head.width;
	cpage->zh=cpage->head.height;
	cpage->curlay=0;
	clayer=&cpage->layer[0];
	cobj.curzoom=1;
	selbz=0;
	cobj.layw->DrawLayerPic();
	//��������
	//1.���δ�õ��ڴ�ͼƬ
	DelNoUseMpic();
	//2.���UNDO����
	cobj.unp.FreeMem();
}

//�������������
void gdata::FreeGbObj()
{
	int i;
	if(gbsum<=0) return;
	for(i=0;i<gbsum;i++){
		 gbobj[i].FreeMem(); //�ͷ��ڴ�
		};
	delete gbobj;
	gbobj=NULL;
	gbsum=0;
}

//���ñ�����ɫ
void gdata::SetColorToBg(DWORD color)
{
	cpage->head.BgColor=color;
	if(cpage->head.imgID>=0)
		cobj.SpicAddSubUse(cpage->head.imgID,-1);
	cpage->head.imgID=-1;
}

//�鿴ĳID ��Сλͼ���꣩�Ƿ��ѱ�ʹ��:
//return:true=�� false=��
bool gdata::SpicInUse(int id)
{
	int i,j,k;
	N_SPIC *sp;
	N_PUSH *ph;
	for(i=0;i<pagesum;i++)
	{
		if(page[i].head.imgID==id) return true;
		for(j=0;j<page[i].laysum;j++)
		{
			for(k=0;k<page[i].layer[j].objnum;k++){
				switch(page[i].layer[j].obj[k].attr.type){
				case 12:
					sp=(N_SPIC*)page[i].layer[j].obj[k].buf;
					if(sp->picID==id) return true;
					break;
				case 76:
					ph=(N_PUSH*)page[i].layer[j].obj[k].buf;
					if(ph->spicid==id) return true;
					break;
			}
			}
		}
	}
	return false;
}

//����һ��Сͼ������
void gdata::SetImgToBg(int id)
{
	if(cpage->head.imgID>=0) 
		cobj.SpicAddSubUse(cpage->head.imgID,-1);
	cpage->head.imgID=id;
	if(id>=0) cobj.SpicAddSubUse(id,1);
}

//�����ѡ���
void gdata::ClearSelect()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		clayer->obj[i].ClearSel();
	};
	selbz=0;
}

//�����ѡ���
void gdata::ClearSelect2()
{
	int i,j,n;
	BASE0 *bs;
	if(cobj.mcline==0) return;
	for(i=0;i<cpage->laysum;i++)
	{
		bs=cpage->layer[i].obj;
		n=cpage->layer[i].objnum;
		for(j=0;j<n;j++)
		{
			if(bs[j].sel!=2) continue;
			bs[j].ClearSel();
		};
	}
}
//���һ������
void gdata::AddAObject(N_BASATTR &attr, void *obuf,int undo)
{
	int n,num;
	N_GIFAML *gl;
	n=clayer->objnum;
	if(n==0){
	  clayer->obj=new BASE0;
	};
	if(n>0){
	  clayer->obj=(BASE0*)realloc(clayer->obj,sizeof(BASE0)*(n+1));
	};
	clayer->obj[n].buf=NULL;
	clayer->obj[n].bakbuf=NULL;
	clayer->obj[n].AddObject(attr,obuf);

	//��Ҫ������������
	switch(clayer->obj[n].attr.type){
	case 73:
		gl=(N_GIFAML*)clayer->obj[n].buf;
		num=cobj.GetGifAnlRec(gl->fname);
		if(num>=0){
		 gl->rec=num;
		 cobj.AddGifAnlUse(num);
		}else{
		num=cobj.GetNoUseGal();
		if(num>=0){
          cobj.OpenGifAnl(num,gl->fname);
		  gl->rec=num;
		}else gl->rec=-1;
		}
		break;
	};
	clayer->objnum++;
	drawbz=1;
	editbz=1;
	//�Ƿ���ӵ�undo��
	if(undo==1)
	{
		cobj.unp.AddAUndoOp(attr, obuf,3);
	}
	
}


//ѡ��һ������
bool gdata::SelAObject(CPoint point,int k)
{
	int i;
	CRect rt;
	CPoint pt=point;
	if(clayer->objnum==0) return false;
	for(i=nextstart;i<clayer->objnum;i++){
		if(clayer->obj[i].PtInObject(pt)){
		  nextstart=i+1;	
		  clayer->obj[i].SetSelected();
		  SetOpPoint(clayer->obj[i]);
		  selnum=1;
		  if(k==0) firstsel=i;
		  if(k==1) ComputNewRect();
		  return true;
		};
	};
	for(i=0;i<nextstart;i++){
		if(i>=clayer->objnum){
			nextstart=0;
			break;
		}
		if(clayer->obj[i].PtInObject(pt)){
		  nextstart=i+1;	
		  clayer->obj[i].SetSelected();
		  SetOpPoint(clayer->obj[i]);
		  selnum=1;
		  if(k==0) firstsel=i;
		  if(k==1) ComputNewRect();
		  return true;
		};
	};
	return false;
}

//ѡ��������
bool gdata::SelManyObject(CRect rt)
{
	int i,n=0;
	CDRect rect;
	if(clayer->objnum==0) return false;
	rect.SetCRect(rt);
	rect.ScrRtToAct(cobj.curzoom);
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].RtInRect(rect)){
		  clayer->obj[i].SetSelected();
		  n++;
		  if(n==1) firstsel=i;
		  };
	};
	ComputNewRect();
	if(selbz>0) return true;
	return false;
}

//�����ƶ�����
void gdata::CreateMoveRgn()
{
	int i,n;
	CDRect art;
	CRect rt;
	if(hrgn!=NULL){
		DeleteObject(hrgn);
		hrgn=NULL;
	};
	n=GetSelSum();
	i=GetFirstSelObj();
	if(i<0) return;
	switch(selbz){
	case 1: hrgn=clayer->obj[i].CreateRGN();return;
	case 2:
		if(n==1){
			hrgn=clayer->obj[i].CreateRGN();return;
		}
		art=selrt;
		art.ActRtToScr(cobj.curzoom);
		art.GetRECT(rt);
		hrgn=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
		break;
	}
}

//����ѡ���
void gdata::SetOpPoint(BASE0&bs)
{
	int fill,close;
	CDPoint p1,p2;
	CDRect rt;
	spt=bs.GetObjectPt(selptsum,fill,close,0);
	selrt=bs.ort;
	selbz=1;
	objclose=close;
	//�����ĵ�����
	srt[0].x=selrt.left; srt[0].y=selrt.top;
	srt[1].x=selrt.right;srt[1].y=selrt.top;
	srt[2].x=selrt.right;srt[2].y=selrt.bottom;
	srt[3].x=selrt.left; srt[3].y=selrt.bottom;
}
//�����µľ������
void gdata::ComputNewRect()
{
	int i,n=0;
	CDRect rt,rtt;
	rt.SetRectEmpty();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1&&clayer->obj[i].attr.type!=32){
			rtt=clayer->obj[i].ort;
			if(rt.IsRectEmpty()) rt=rtt;
			else rt|=rtt;
			n++;
		};
	  };
	if(n>0)  selbz=2;
	if(n==0) selbz=0;
	srt[0].x=rt.left; srt[0].y=rt.top;
	srt[1].x=rt.right;srt[1].y=rt.top;
	srt[2].x=rt.right;srt[2].y=rt.bottom;
	srt[3].x=rt.left; srt[3].y=rt.bottom;
	selrt=rt;
	selnum=n;
	ComputRect();
}
//���ض�������
int gdata::GetObjSum()
{
	int i;
	int n=0;
	for(i=0;i<cpage->laysum;i++){
		n+=cpage->layer[i].objnum;
	}
	return n;
}

//����ҳ���������
int gdata::GetPageObjSum(int ip)
{
	int i;
	int n=0;
	if(ip<0||ip>=pagesum) return 0;
	for(i=0;i<page[ip].laysum;i++){
		n+=page[ip].layer[i].objnum;
	}
	return n;
}


//��������ϵͳ��������
int gdata::GetAllObjSum()
{
	int i,j;
	int n=0;
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].laysum;j++){
			n+=page[i].layer[j].objnum;
			}
	}
	return n;
}


//��ʾѡ�е�
void gdata::ShowSelectDot(CDIB&mdc,int sdx,int sdy)
{
	int i,w;
	DWORD c1;
	CRect rt;
	CPoint pt,p1;
	pt=CPoint(sdx,sdy);
	w=3;
	switch(selbz){
	case 1:
	  for(i=0;i<selptsum;i++){
		p1.x=(int)(spt[i].x*cobj.curzoom);
		p1.y=(int)(spt[i].y*cobj.curzoom);
		rt=CRect(p1.x-w,p1.y-w,p1.x+w,p1.y+w);
	    rt.OffsetRect(pt);
		c1=i==0||i==selptsum-1 ? 0xff0000:0xff;
		mdc.FillSolidRect(rt,c1);
		mdc.CDrawRect(rt,1,0xffff);
	  };
	  break;
	case 2:
	 for(i=0;i<cpsum;i++){
		p1.x=(int)(cp[i].x*cobj.curzoom);
		p1.y=(int)(cp[i].y*cobj.curzoom);
		rt=CRect(p1.x-w,p1.y-w,p1.x+w,p1.y+w);
	    rt.OffsetRect(pt);
		mdc.FillSolidRect(rt,0xff);
		mdc.CDrawRect(rt,1,0xffffff);
	 };
	 break;
	}
}

void gdata::ComputRect()
{
	cp[0]=srt[0];
	cp[1].x=(srt[0].x+srt[1].x)/2;
	cp[1].y=(srt[0].y+srt[1].y)/2;
	cp[2]=srt[1];
	cp[3].x=(srt[1].x+srt[2].x)/2;
	cp[3].y=(srt[1].y+srt[2].y)/2;
	cp[4]=srt[2];
	cp[5].x=(srt[2].x+srt[3].x)/2;
	cp[5].y=(srt[2].y+srt[3].y)/2;
	cp[6]=srt[3];
	cp[7].x=(srt[3].x+srt[0].x)/2;
	cp[7].y=(srt[3].y+srt[0].y)/2;
	cpsum=8;
}

//���ع��
int gdata::GetCursor(CPoint point)
{
	int i;
	CDRect  rt;
	CDPoint pt,pt2;
	if(selbz==0) return 0;
	pt.SetPOINT(point);
	pt.Offset(-dx,-dy);
	switch(selbz){
	case 1:
	 for(i=0;i<selptsum;i++){
		pt2.x=spt[i].x*cobj.curzoom;
		pt2.y=spt[i].y*cobj.curzoom;
		rt.left=pt2.x-3;
		rt.top=pt2.y-3;
		rt.right=pt2.x+3;
		rt.bottom=pt2.y+3;
		if(rt.PtInRect(pt)){
			selop=i+1;	//������
			return 101;
		};
	 };
	 break;
	case 2:
	 for(i=0;i<cpsum;i++){
		pt2.x=cp[i].x*cobj.curzoom;
		pt2.y=cp[i].y*cobj.curzoom;
		rt.left=pt2.x-3;
		rt.top=pt2.y-3;
		rt.right=pt2.x+3;
		rt.bottom=pt2.y+3;
		if(rt.PtInRect(pt)){
			selop=i+1;	//������
			return 101;
		};
	 }
	 break;
	}
	if(PtInRegion(hrgn,(int)pt.x,(int)pt.y)){
		selop=0;		//������
		return 100;
	};
	return 0;
}

//��һ���ƶ���ʽ(������)
void gdata::MoveObject1(double mx, double my)
{
	int i=GetFirstSelObj();
	if(i==-1) return;
	clayer->obj[i].MoveObject1(mx,my,selop);
	SetOpPoint(clayer->obj[i]);
	CreateMoveRgn();
	drawbz=1;
	editbz=1;
}

//�ƶ����ӵĶ���
void gdata::MoveConLine(double mx,double my)
{
	BASE0 *bs;
	int i,j,k;
	if(cobj.mcline==0) return;
	mselrt.left-=2;
	mselrt.top-=2;
	mselrt.right+=2;
	mselrt.bottom+=2;
	for(i=0;i<cpage->laysum;i++)
	{
		bs=cpage->layer[i].obj;
		k=cpage->layer[i].objnum;
		for(j=0;j<k;j++)
		{
			if(bs[j].sel==1) continue;
			switch(bs[j].attr.type)
			{
			case 77://������
			case 78://������
				MoveInLineDot(bs[j],mx,my);
				break;
			}
		}
	}
}

//�ƶ��ƶ�������
void gdata::MoveInLineDot(BASE0 &bs,double mx,double my)
{
	DPOINT *pt1;
	int ptsum,fill,close,kx,ky,kxy;
	pt1=bs.GetObjectPt(ptsum,fill,close,0);
	if(pt1==NULL) return;
	//�ȿ��׶�
	if(mselrt.PtInRect(pt1[0]))
	{
		bs.SetSelected(2);
		kx=abs((int)(pt1[1].x-pt1[0].x));
		ky=abs((int)(pt1[1].y-pt1[0].y));
		if(kx>ky) kxy=0;
		else kxy=1;
		pt1[0].x+=mx;
		pt1[0].y+=my;
		ChangeMoveDot(pt1,ptsum,0,kxy);
		return;
	}
	//Ȼ��ĩ��
	if(mselrt.PtInRect(pt1[ptsum-1]))
	{
		bs.SetSelected(2);
		kx=abs((int)(pt1[ptsum-2].x-pt1[ptsum-1].x));
		ky=abs((int)(pt1[ptsum-2].y-pt1[ptsum-1].y));
		if(kx>ky) kxy=0;
		else kxy=1;
		pt1[ptsum-1].x+=mx;
		pt1[ptsum-1].y+=my;
		ChangeMoveDot(pt1,ptsum,ptsum-1,kxy);
	}
}

//�ڶ����ƶ���ʽ
void gdata::MoveObject2(double mx, double my)
{
	double xl,yl;
	double w1,w2,h1,h2;
	int n,i,j;
	CDRect oldrt,nrt;
	oldrt=ComputOldRect();
	nrt=oldrt;
	//�����µľ��δ�С
	switch(selop){
		case 0:
		  nrt.Offset(mx,my);
		  break;
		case 1:
		 nrt.left+=mx;
		 nrt.top+=my;
		 break;
		case 2:
		 nrt.top+=my;
		 break;
		case 3:
		 nrt.top+=my;
		 nrt.right+=mx;
		 break;
		case 4:
		 nrt.right+=mx;
		 break;
		case 5:
		 nrt.right+=mx;
		 nrt.bottom+=my;
		 break;
		case 6:
		 nrt.bottom+=my;
		 break;
		case 7:
		 nrt.left+=mx;
		 nrt.bottom+=my;
		 break;
		case 8:
		 nrt.left+=mx;
		 break;
		};
	w1=oldrt.Width();
	h1=oldrt.Height();
	w2=nrt.Width();
	h2=nrt.Height();

	xl=w2/(double)w1;
	yl=h2/(double)h1;
	n=0;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
		  clayer->obj[i].MoveObject2(CDRect(oldrt.left,oldrt.top,nrt.left,nrt.top),xl,yl);
		  n++; j=i;
		};
	};
	nrt.NormalizeRect();
	srt[0].x=nrt.left; srt[0].y=nrt.top;
	srt[1].x=nrt.right;srt[1].y=nrt.top;
	srt[2].x=nrt.right;srt[2].y=nrt.bottom;
	srt[3].x=nrt.left; srt[3].y=nrt.bottom;
	selrt=nrt;
	ComputRect();
	CreateMoveRgn();
	drawbz=1;
	editbz=1;
}

//����ɵľ������
CDRect gdata::ComputOldRect()
{
	int i;
	CDRect rt,rtt;
	rt.SetRectEmpty();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			rtt=clayer->obj[i].CreateOldRect();
			if(rt.IsRectEmpty()) rt=rtt;
			else rt|=rtt;
		};
	  };
	return rt;
}

//�Զ����ƶ������⴦��(ƽ��)
void gdata::MoveEsite(BASE0&bs)
{
	int i;
	DPOINT ept,cpt;
	double dx,dy;
	N_ESITE *es;
	if(bs.attr.type!=11) return;
	es=(N_ESITE*)bs.buf;
	cpt=bs.ort.CenterPoint();
	if(FindALineDot(bs.ort,ept)){
		dx=ept.x-cpt.x;
		dy=ept.y-cpt.y;
		for(i=0;i<4;i++){
			es->pt[i].x+=dx;
			es->pt[i].y+=dy;
		}
	};
}

//�����ͼԪ�ƶ������⴦��(ƽ��)
void gdata::MoveEleGrp(BASE0&bs,int index)
{
	int i,j,n,ok;
	CDRect rt,rt1;
	D_SITEC sit;
	DPOINT ept;
	double dx,dy;
	N_ELEGRPA *el;
	if(bs.attr.type!=66) return;
	el=(N_ELEGRPA*)bs.buf;
	rt1=CreateNRt(4,el->pt);
	n=el->sitesum;
	n=n>3 ? 3:n;
	ok=0;
	for(i=0;i<n;i++){
		sit.etype=255;
		sit.jlh=index;
		sit.nlayer=cpage->curlay;
		rt.SetDRECT(el->site[i].srt);
		ept=rt.CenterPoint();
	    rt.Offset(rt1.left,rt1.top);
		rt.GetDRECT(sit.srt);
		ept.x=(double)(ept.x+rt1.left);
		ept.y=(double)(ept.y+rt1.top);
		sit.id=bs.attr.ID;
		sit.sitn=(BYTE)i;
		if(el->type==1&&(el->subtype==7||el->subtype==8))
		{
			sit.vl=el->site[i].vl;
		}
		else { sit.vl=el->site[0].vl;}
		el->site[i].id=-1;
		if(SerchConnect(sit))
		{
			el->site[i].id=sit.id;
			el->site[i].sitn=sit.sitn;
			el->site[i].vl=sit.vl;
			if(ok==0){
			  dx=(double)(ept.x-sit.cpt.x);
			  dy=(double)(ept.y-sit.cpt.y);
			  for(j=0;j<4;j++){
			    el->pt[j].x=(double)(el->pt[j].x-dx);
			    el->pt[j].y=(double)(el->pt[j].y-dy);
			  }
			}
			ok=1;
		}
	}
}

//�Գ����ߣ����ɣ��ƶ������⴦��(ƽ��)
void gdata::MoveFlow(BASE0&bs,int index)
{
	int i,j,ok;
	CDRect rt;
	D_SITEC sit;
	DPOINT ept;
	DPOINT tpt[2];
	double w,dx,dy;
	N_FLOW *fl;
	if(bs.attr.type!=77) return;
	fl=(N_FLOW*)bs.buf;
	tpt[0]=fl->pt[0];
	tpt[1]=fl->pt[fl->ptsum-1];
	ok=0;
	for(i=0;i<2;i++){
		sit.etype=255;
		sit.jlh=index;
		sit.nlayer=cpage->curlay;
		w=(double)(5/cobj.curzoom);
		rt.left=(double)(tpt[i].x-w);
		rt.top=(double)(tpt[i].y-w);
		rt.right=(double)(tpt[i].x+w);
		rt.bottom=(double)(tpt[i].y+w);
		rt.GetDRECT(sit.srt);
		sit.id=bs.attr.ID;
		sit.vl=fl->vl;
		sit.sitn=(BYTE)i;	
		ept=tpt[i];
		if(SerchConnect(sit))
		{
			fl->site[i].id=sit.id;
			fl->site[i].sitn=sit.sitn;
			//fl->vl=sit.vl;
			if(ok==0){
			 dx=(double)(ept.x-sit.cpt.x);
			 dy=(double)(ept.y-sit.cpt.y);
			 for(j=0;j<fl->ptsum;j++){
				fl->pt[j].x=(double)(fl->pt[j].x-dx);
				fl->pt[j].y=(double)(fl->pt[j].y-dy);
			 }
			}
			ok=1;
		}
	};
}

//�����������ƶ������⴦��(ƽ��)
void gdata::MoveConLine(BASE0&bs,int index)
{
	int i,j,ok;
	D_SITEC sit;
	CDRect rt;
	DPOINT ept;
	DPOINT tpt[2];
	double w,dx,dy;
	N_CONLINE *cn;
	if(bs.attr.type!=78) return;
	cn=(N_CONLINE*)bs.buf;
	tpt[0]=cn->pt[0];
	tpt[1]=cn->pt[cn->ptsum-1];
	cn->conobj=0;
	cn->el=0;
	ok=0;
	for(i=0;i<2;i++){
		sit.etype=255;
		sit.jlh=index;
		sit.nlayer=cpage->curlay;
		cn->lobj[i].jlh=-1;
		w=(double)(5/cobj.curzoom);
		rt.left=(double)(tpt[i].x-w);
		rt.top=(double)(tpt[i].y-w);
		rt.right=(double)(tpt[i].x+w);
		rt.bottom=(double)(tpt[i].y+w);
		rt.GetDRECT(sit.srt);
		sit.id=bs.attr.ID;
		sit.vl=-1;
		sit.sitn=0;
		ept=tpt[i];
		if(SerchConnect(sit))
		{
			if(ok==0){
			 dx=(double)(ept.x-sit.cpt.x);
			 dy=(double)(ept.y-sit.cpt.y);
			 for(j=0;j<cn->ptsum;j++){
				cn->pt[j].x=(double)(cn->pt[j].x-dx);
				cn->pt[j].y=(double)(cn->pt[j].y-dy);
			 }
			}
			if(sit.vl>=0)	cn->vl=sit.vl;
			cn->conobj=1; //��ʾ�����ӵ��豸
			ok=1;
			cn->lobj[i].jlh=(short)sit.jlh;
			cn->lobj[i].layer=sit.nlayer;
			cn->lobj[i].sitn=sit.sitn;
			break;
		}
	}
}

//�������ͼԪ���ӵ�ʵ��λ��
void gdata::ComputEsitRect(BASE0&sbs)
{
	BASE0 *bs,bbs;
	int i,j,k,n,in;
	double xl,yl,w1,w2,h1,h2,bl;
	CDRect rt,rt1,rt2;
	N_ELEGRPA *el;
	if(sbs.attr.type!=66) return;
	el=(N_ELEGRPA*)sbs.buf;
	in=cobj.GetEGPRecNo(el->egrpid);
	if(in<0) return;
	el->type=cobj.egp[in].type;
	el->subtype=cobj.egp[in].subtype;
	el->sitesum=cobj.egp[in].sitesum;
	bs=cobj.egp[in].bs1;
	j=cobj.egp[in].bsum1;
	rt1.SetDRECT(cobj.egp[in].rt1);
	if(bs==NULL||j<=0)	return;
	//������
	rt=CreateNRt(4,el->pt);
	h1=rt.Height();
	w1=rt.Width();
	//ԭ���Ŀ��
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=0;	rt2.bottom=0;
	xl=(double)w1/w2;
	yl=(double)h1/h2;
	bl=xl>yl ? yl:xl;
	bl=1/bl;
	k=-1;
	n=el->sitesum;
	n=n>3 ? 3:n;
	el->sitesum=n;
	for(i=0;i<j;i++){
	  if(bs[i].attr.type==11){ 
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		k++;
		if(k>n) break;
		bbs.ort.GetDRECT(el->site[k].srt);
		bbs.FreeMem();
	  }
	};
}

//�����ƶ�(δɾ��ѡ���־)
void gdata::EndMoveObject()
{
	int i;
	movebz=0;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1){
		   switch(clayer->obj[i].attr.type){
			case 11: //���ӣ��Զ�λ�ö���
				if(selbz==1) MoveEsite(clayer->obj[i]);
				break;
			case 66: //���ͼԪ���Զ�λ�ö��� 
				ComputEsitRect(clayer->obj[i]);  //���¼������λ��
				if(selbz==1) MoveEleGrp(clayer->obj[i],i);    //�ƶ����ͼԪ
				ComputEsitRect(clayer->obj[i]);
				break;
			case 78:
				if(selbz==1) MoveConLine(clayer->obj[i],i);
				break;
			case 77:
				//if(selbz==1) MoveFlow(clayer->obj[i],i);
				break;
		   }
		   clayer->obj[i].EndMOveObject();
		}
	}
	switch(selbz){
	case 1:	break;
	case 2:
		ComputNewRect();
		srt[0].x=selrt.left; srt[0].y=selrt.top;
		srt[1].x=selrt.right;srt[1].y=selrt.top;
		srt[2].x=selrt.right;srt[2].y=selrt.bottom;
		srt[3].x=selrt.left; srt[3].y=selrt.bottom;
		ComputRect();
		break;
	}
	if(HaveDevice()) CalRalation();  //�������ӹ�ϵ
}
//���ر�ѡ�ж���ĸ���
int gdata::GetSelSum()
{
	int i,n=0;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1) n++;
	}
	return n;
}

//����һ��ĳ��δ�õ�IDֵ
int gdata::GetNoUseID(int type)
{
	int i,j;
	DWORD max;
	N_PUSH *ph;
	N_SELFCTL *sf;
	//��ť����ID
	if(type==75){
		max=99;
		for(i=0;i<cpage->laysum;i++){
			for(j=0;j<cpage->layer[i].objnum;j++){
			if(cpage->layer[i].obj[j].attr.type==75)
			{
				ph=(N_PUSH*)cpage->layer[i].obj[j].buf;	
				if(ph->id>max) max=ph->id;
			}
			}
		};
		max++;
		return max;
	};
	//��������
	if(type==76){
		max=299;
		for(i=0;i<cpage->laysum;i++){
			for(j=0;j<cpage->layer[i].objnum;j++){
			if(cpage->layer[i].obj[j].attr.type==76)
			{
			sf=(N_SELFCTL*)cpage->layer[i].obj[j].buf;
			if((DWORD)sf->id>max) max=sf->id;
			}
			}
		}
		max++;
		return max;
	};
	return 100;
}


//��ѡ�еĶ����õ�������
void gdata::CopyToCpyBuf(HWND hwnd)
{
	int i,size;
	CLPDATA *clp;
	char *buf,*lp;
	HGLOBAL hglb;
	double x,y;
	//�ͷŶ���
	FreeCpyObj();
	//��Ӷ���
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1)
		{
		 AddCpyObj(clayer->obj[i].attr,clayer->obj[i].buf);
		};
	};
	//�����������
	x=selrt.left;
	y=selrt.top;
	for(i=0;i<cpysum;i++)
	{
		cpyobj[i].Offset(-x,-y);	  	
	};


	
	//�����ֽ���
	size=0;
	for(i=0;i<cpysum;i++)
	{
		size+=cpyobj[i].attr.size;
		size+=sizeof(N_BASATTR);
	}


	if(size==0) return;
	//�����ڴ�
	hglb=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,size+1024);
	if(hglb==NULL) 
	{
		MessageBox(0,"���ܽ��г���俽����","����",MB_OK|MB_ICONSTOP);
		return;
	}
	buf=(char*)GlobalLock(hglb);
	clp=(CLPDATA*)buf;
	clp->flag=0x1f9d3445;
	clp->objsum=cpysum;
	clp->objsize=size+sizeof(CLPDATA);
	lp=buf+sizeof(CLPDATA);
	for(i=0;i<cpysum;i++)
	{
		memcpy(lp,&cpyobj[i].attr,sizeof(N_BASATTR));
		lp+=sizeof(N_BASATTR);
		memcpy(lp,cpyobj[i].buf,cpyobj[i].attr.size);
		lp+=cpyobj[i].attr.size;
	}
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hglb1=SetClipboardData(cobj.clptype,hglb);
	CloseClipboard();
	FreeCpyObj();
}

//������������ݿ������ڴ�
void gdata::ClpToMem(HGLOBAL hglb)
{
	int i,size;
	CLPDATA *clp;
	N_BASATTR *atr;
	char *buf,*lp;
	buf=(char*)GlobalLock(hglb);
	if(buf==NULL) return;
	clp=(CLPDATA *)buf;
	if(clp->flag!=0x1f9d3445) return;
	size=sizeof(CLPDATA);
	FreeCpyObj();
	for(i=0;i<clp->objsum;i++)
	{
		if(size>clp->objsize) break;
		lp=buf+size;
		atr=(N_BASATTR*)lp;
		size+=sizeof(N_BASATTR);
		lp=buf+size;
		AddCpyObj(atr[0],lp);
		size+=atr[0].size;
	}
}

//�������������
void gdata::FreeCpyObj()
{
	int i;
	if(cpysum<=0||cpyobj==NULL) return;
	for(i=0;i<cpysum;i++)
	{
		 cpyobj[i].FreeMem(); //�ͷ��ڴ�
	};
	delete cpyobj;
	cpyobj=NULL;
	cpysum=0;
}

//���һ�����󵽿�����
void gdata::AddCpyObj(N_BASATTR &attr, void *obuf)
{
	int n;
	N_SELFCTL *sft;
	N_FLOW    *fl;
	N_BUS     *bs;
	N_ELEGRPA *el;
	n=cpysum;
	if(n==0)  cpyobj=new BASE0;
	if(n>0)  cpyobj=(BASE0*)realloc(cpyobj,sizeof(BASE0)*(n+1));
	cpyobj[n].buf=NULL;
	cpyobj[n].bakbuf=NULL;
	cpyobj[n].AddObject(attr,obuf,1);
	switch(attr.type)
	{
	case 76:  //�����ؼ�
		sft=(N_SELFCTL*)cpyobj[n].buf;
		sft->hinst=NULL;
		sft->DfGetVer=0;
		sft->DfDrawDemo=NULL;
		sft->DfInit=NULL;
		sft->DfClose=NULL;
		sft->DfAbout=NULL;
		sft->DfSetParam=NULL;
		break;
	case 77:  //FLOW
		fl=(N_FLOW *)cpyobj[n].buf;
		//fl->dev_name[0]=0;
		//fl->did=-1;
		break;
	case 79:  // BUS
		bs=(N_BUS *)cpyobj[n].buf;
		//bs->dev_name[0]=0;
		//bs->did=-1;
		break;
	case 66:  //�豸
		el=(N_ELEGRPA*)cpyobj[n].buf;
		//el->dev_name[0]=0;
		//el->did=-1;
		break;
	}
	cpysum++;
}

//ɾ��ѡ�ж���
void gdata::DelSelObj()
{
	int i;
	
	for(i=0;i<clayer->objnum;i++){
		if(i>=clayer->objnum) break;
		if(clayer->obj[i].sel==1){
		 DeleteAObject(i);
		 i--;
		};
	};
	selbz=0;
	nextstart=0;
}

//ɾ��һ����¼
void gdata::DeleteAObject(int j)
{
	int i,k;
	N_IMG *img;
	N_GIFAML *ga;
	N_SPIC  *ss;
	if(j<0||j>=clayer->objnum) return;
	//����ɾ����������������
	AddGbObj(clayer->obj[j].attr,clayer->obj[j].buf);
	
	//�����������
	switch(clayer->obj[j].attr.type)
	{
	case 17:
		ss=(N_SPIC*)clayer->obj[j].buf;
		cobj.SpicAddSubUse(ss->picID,-1);
		break;
	case 15:
		img=(N_IMG*)clayer->obj[j].buf;
		//cobj.MpicAddSubUse(img->imgID,-1);
		break;
	case 73:			//GIF����
		ga=(N_GIFAML*)clayer->obj[j].buf;
		cobj.DelAGifAnl(ga->rec);
		break;
	};
	clayer->obj[j].FreeMem(); //ɾ����Դ
	for(i=j;i<clayer->objnum-1;i++){
	  clayer->obj[i]=clayer->obj[i+1];
	};

	k=clayer->objnum-1;
	clayer->obj[k].buf=NULL;
	if(k>0)	clayer->obj=(BASE0*)realloc(clayer->obj,sizeof(BASE0)*k);
	else {
		delete clayer->obj;
		clayer->obj=NULL;
	};
	clayer->objnum=k;
}

//���һ����������������
void gdata::AddGbObj(N_BASATTR &attr, void *obuf)
{
	int n;
	N_SELFCTL *sft;
	n=gbsum;
	if(n==0){
	  gbobj=new BASE0;
	};
	if(n>0){
	  gbobj=(BASE0*)realloc(gbobj,sizeof(BASE0)*(n+1));
	};
	gbobj[n].buf=NULL;
	gbobj[n].bakbuf=NULL;
	gbobj[n].AddObject(attr,obuf,1);
	if(attr.type==76){  //����������ؼ�
		sft=(N_SELFCTL*)gbobj[n].buf;
		sft->hinst=NULL;
		sft->DfGetVer=0;
		sft->DfDrawDemo=NULL;
		sft->DfInit=NULL;
		sft->DfClose=NULL;
		sft->DfAbout=NULL;
		sft->DfSetParam=NULL;
	};
	gbsum++;
}


//��������ֱ
void gdata::StraightObj()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			clayer->obj[i].StraightObj();		
		}
	}
	CreateMoveRgn();
	drawbz=1;
	editbz=1;
}

//��������ֱ
void gdata::SqrtObj()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			clayer->obj[i].SqrtObj();		
		}
	}
	CreateMoveRgn();
	drawbz=1;
	editbz=1;
}

//�Ƿ�����ת
bool gdata::CanRotate()
{
	int i;
	if(selbz==0) return false;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			if(!clayer->obj[i].IsRotateObj()) return false;
		}
	}
	return true;	
}

//ճ������
void gdata::PasteObject(double nx,double ny)
{
	int i,j;
	BASE0 bast;
	N_IMG *img;
	N_GIFAML *gl;
	ClearSelect();
	for(i=0;i<cpysum;i++){
		cpyobj[i].attr.ID=GetNewID();
	  	AddAObject(cpyobj[i].attr,cpyobj[i].buf);
		if(cpyobj[i].attr.type==15){ //��Ϊͼ��ʱ,����ʹ�ô���
		  img=(N_IMG*)cpyobj[i].buf;
		  cobj.MpicAddSubUse(img->imgID,1);
		}
		if(cpyobj[i].attr.type==73){ //��ΪGIFͼ��ʱ,����ʹ�ô���
		  gl=(N_GIFAML*)cpyobj[i].buf;
		 }
		j=clayer->objnum-1;
		if(j>=0){
			clayer->obj[j].Offset(nx,ny);
		    clayer->obj[j].SetSelected();
		}
	};
	ComputNewRect();
	CreateMoveRgn();
	drawbz=1;
	editbz=1;
	//��ճ���Ķ������UNDO�����Ա�UNDO
	cobj.unp.AddAUndoOp(3);
}


//���ݼ�¼����������ʾͼԪ��(���ͼԪ�Ի���ר��)
void gdata::PreShowEGP(CDIB&mdc,int num, CRect rt,int index,DWORD color,int showsite)
{
	BASE0 *bs,bbs;
	double oldzoom;
	int i,j;
	double dw,dh,w1,w2,h1,h2;
	double xl,yl;
	CDRect rt1,rt2,rt3;
	switch(index){
	case 0:
		bs=cobj.egp[num].bs1;
		j=cobj.egp[num].bsum1;
		rt1.SetDRECT(cobj.egp[num].rt1);
		break;
	case 1:
		bs=cobj.egp[num].bs2;
		j=cobj.egp[num].bsum2;
		rt1.SetDRECT(cobj.egp[num].rt2);
		break;
	default:return;
	};
	if(bs==NULL||j<=0) return;
	oldzoom=cobj.curzoom;
	cobj.curzoom=1;
	w1=rt.Width();
	h1=rt.Height();
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2<=w1&&h2<=h1){ //����С�ڴ���(rt)
	  rt2.left=rt.left+(w1-w2)/2;
	  rt2.top=rt.top+(h1-h2)/2;
	  for(i=0;i<j;i++){
		  if(bs[i].attr.type==12) continue;
		  if(showsite==1){
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.SetSelected();
			bbs.MoveObject1(rt2.left,rt2.top,0);
			bbs.Show(mdc,0,0);
			bbs.FreeMem();
		  }else{
		   if(bs[i].attr.type!=11)
		   {
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.SetSelected();
			bbs.MoveObject1(rt2.left,rt2.top,0);
			bbs.Show(mdc,0,0);
			bbs.FreeMem();
		   }
		  }
	  };
	  cobj.curzoom=oldzoom;
	  return;
	  }
	dw=w1;
	dh=h1;
	if(w2>h2) dh=h2*w1/w2;
	if(w2<h2) dw=w2*h1/h2;
	rt2.left=rt.left+(w1-dw)/2;
	rt2.top=rt.top+(h1-dh)/2;
	rt2.right=rt2.left+dw;
	rt2.bottom=rt2.top+dh;
	w1=rt2.Width();
	h1=rt2.Height();
	if(w2==0||h2==0) return;
	rt3.left=rt1.left;
	rt3.top=rt1.top;
	rt3.right=rt2.left;
	rt3.bottom=rt2.top;
	xl=(double)w1/w2;
	yl=(double)h1/h2;
	for(i=0;i<j;i++){
		if(bs[i].attr.type==12) continue;
		if(showsite==1){
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.SetSelected();
			bbs.MoveObject2(rt3,xl,yl);
			bbs.SetSObjZM(xl);
			bbs.Show(mdc,0,0);
			bbs.FreeMem();
		}else{
		   if(bs[i].attr.type!=11)
		   {
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.SetSelected();
			bbs.MoveObject2(rt3,xl,yl);
			bbs.SetSObjZM(xl);
			bbs.Show(mdc,0,0);
			bbs.FreeMem();
		   }
		}
	};
	cobj.curzoom=oldzoom;
}


//�鿴ĳID �����ͼԪ�Ƿ��ѱ�ʹ��:
//return:true=�� false=��
bool gdata::EgrpInUse(int id)
{
	int i,j,k;
	N_ELEGRPA *egp;
	N_BUS     *bus;
	for(i=0;i<pagesum;i++)
	{
		for(j=0;j<page[i].laysum;j++)
		{
			for(k=0;k<page[i].layer[j].objnum;k++){
			  if(page[i].layer[j].obj[k].attr.type==66){
				egp=(N_ELEGRPA *)page[i].layer[j].obj[k].buf;
				if(egp->egrpid==id) return true;
			  }
			  if(page[i].layer[j].obj[k].attr.type==79){
				bus=(N_BUS   *)page[i].layer[j].obj[k].buf;
				if(bus->eid==id) return true;
			  }
			}
		}
	}
	return false;
}

void gdata::LayerChange(int newlayer)
{
	cpage->curlay=newlayer;
	clayer=&cpage->layer[newlayer];
}

//ѡ�ж�����ǰ
void gdata::SelObjToTOP()
{
	int i;
	for(i=0;i<clayer->objnum-1;i++){
		if(clayer->obj[i].sel==1){
			AObjToTop(i);
			i--;
		}
	}

	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==2){
			clayer->obj[i].sel=1;
		}
	}
}

//ѡ�ж����ú�
void gdata::SelObjToButtom()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			AObjToButtom(i);
		}
	}
}

//ѡ��һ�������ú�
void gdata::AObjToButtom(int j)
{
	int i;
	BASE0 tbas;
	tbas=clayer->obj[j];
	for(i=j;i>0;i--){
	  clayer->obj[i]=clayer->obj[i-1];
	};
	clayer->obj[0]=tbas;
	tbas.SetEmpty();
}

//ѡ��һ��������ǰ
void gdata::AObjToTop(int j)
{
	int i,k;
	BASE0 tbas;
	tbas=clayer->obj[j];
	tbas.sel=2;
	k=clayer->objnum-1;
	for(i=j;i<k;i++){
	  clayer->obj[i]=clayer->obj[i+1];
	};
	k=clayer->objnum-1;
	if(k>=0) clayer->obj[k]=tbas;
	tbas.SetEmpty();
	
}

//���浱ǰ���ļ�
void gdata::SaveFile(const char *fname)
{
	int i,size,sz,ys,zs,offset;
	char fbuf[132],ftmp[128],*buf1;
	N_PWFHEAD *ph;
	FILE *fp1,*fp2;
	offset=0;
	strcpy(ftmp,fname);
	strcat(ftmp,".tmp");
	fp1=fopen(ftmp,"w+b");
	if(fp1==NULL) return;
	//�����δ�õ��ڴ�ͼƬ
	DelNoUseMpic();
	//׼��ͷ����
	size=sizeof(N_PWFHEAD)+pagesum*sizeof(N_OBJSAVE);
	buf1=new char[size];
	offset=size;
	sz=size;
	ph=(N_PWFHEAD *)buf1;
	ph->spicsum=cobj.spicsum;
	if(cobj.spicsum>0){
	 ph->spic.offset=offset;
	 size=cobj.SaveSpic(fp1);
	 ph->spic.size=size;
	 offset+=size;
	}
	//�ڶ���:����mpic;
	ph->mpicsum=cobj.mpicsum;
	if(cobj.mpicsum>0){
	 ph->mpic.offset=offset;
	 size=cobj.SaveMPic(fp1);
	 ph->mpic.size=size;
	 offset+=size;
	}
	//������:����egrp
	ph->egpsum=cobj.egpsum;
	if(cobj.egpsum>0)
	{
	 ph->epic.offset=offset;
	 size=cobj.SaveEGrp(fp1);
	 ph->epic.size=size;
	 offset+=size;
	}
	
	//���Ĳ�:����apdinfo������Ϣ
	ph->apdsum=apdsum;
	ph->apdinfo.offset=offset;
	size=apdsum*sizeof(N_APDINFO);
	ph->apdinfo.size;
	offset+=size;
	fwrite(apdinfo,sizeof(N_APDINFO),apdsum,fp1);
	//���岽:����ҳ��(��ͼ��)
	ph->pagesum=pagesum;
	for(i=0;i<pagesum;i++){
	 ph->page[i].offset=offset;
	 size=SavePage(fp1,i);
	 ph->page[i].size=size;
	 offset+=size;
	 };
	ph->fsize=offset;
	ph->Version=3203; //V5�汾
	fclose(fp1);
	//���岽�����ļ��ϲ�
	fp2=fopen(fname,"w+b");
	fp1=fopen(ftmp,"r+b");
	if(fp2==NULL){
		delete buf1;
		fclose(fp1);
		return;
	};
	offset-=sz;
	fwrite(buf1,sz,1,fp2);
	zs=offset/128;
	ys=offset%128;
	//����ʱ�ļ�׷�ӵ������ļ�
	for(i=0;i<zs;i++){
	 fread(fbuf,128,1,fp1);
	 fwrite(fbuf,128,1,fp2);
	};
	if(ys>0){
	 fread(fbuf,ys,1,fp1);
	 fwrite(fbuf,ys,1,fp2);
	};
	fclose(fp1);
	fclose(fp2);
	remove(ftmp);
	strcpy(pwfname,fname);
	filebz=1;
	delete buf1;
	editbz=0;
}

//����һ��ҳ���������(���������棩
int gdata::SavePage(FILE *fp, int pg)
{
	FileV30 fv3;
	int  i,j,m,n,sz,size;
	char *lp;
	char *wbuf;     //д�뻺����
	char *pbuf;		//ѹ����Ļ�����
	N_SUBPWF head;  //ҳ���ƽṹ
	N_LAYERS ly;	//����ƽṹ
	N_LAYER  *cly;
	cmpress cps;
	head=page[pg].head;
	head.laysum=page[pg].laysum;
	head.flag=0xcccc;
	size=sizeof(N_SUBPWF);
	fwrite(&head,sizeof(N_SUBPWF),1,fp); //дͷ
	for(i=0;i<head.laysum;i++){
	  cly=&page[pg].layer[i]; //��ǰ����Ĳ���
	  ly.flag=0xffff;	
	  strcpy(ly.name,cly->name);
	  ly.objnum=cly->objnum;
	  //��һ��:����ͼԪ���ֽ���
	  n=cly->objnum;
	  if(n>0){  //���������
		m=0;
		for(j=0;j<n;j++) m+=fv3.GetV5Size(cly->obj[j]);
		ly.size=m;
		//�����ڴ�
		wbuf=new char[m+100];
		pbuf=new char[m+1000];
		//�������
		lp=wbuf;
		for(j=0;j<n;j++){
			sz=fv3.CopyV5Data(cly->obj[j],lp);
			lp+=sz;
		};
		//ѹ������
		cps.initdata();
		sz=cps.EEnCode(wbuf,pbuf,m,m+100);
		DWORD *dw=(DWORD*)pbuf;
		ly.psize=sz;
		//д������ļ�
		fwrite(&ly,sizeof(N_LAYERS),1,fp);	 //д��ͷ
		fwrite(pbuf,sz,1,fp);			     //д��ѹ������
		size+=sizeof(N_LAYERS);
		size+=sz;
		delete wbuf;
		delete pbuf;
	  }else{
		ly.psize=0;
		ly.size=0;
		fwrite(&ly,sizeof(N_LAYERS),1,fp);
		size+=sizeof(N_LAYERS);
	  }
	}
	return size;
}

//��pw��ʽ�ļ�
bool gdata::OpenPwFile(char *fname)
{
	N_APDINFO atmp;
	FILE *fp;
	char *buf1;
	int i,m,n;
	N_PWFHEAD *ph,head;
	fp=fopen(fname,"r+b");
	if(fp==NULL) return false;
	//��һ��:�����ļ�ͷ:
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	if(head.Version>3203)//!=3200&&head.Version!=3201&&head.Version!=3202)
	{
		fclose(fp);
		return false;
	}
	FreeMem(); //�ͷ�ԭ�е�ͼ������
	cobj.FreeMem();
	cobj.InitParam();
	n=head.pagesum;
	if(n>MAXPAGE)
	{
	 	fclose(fp);
	 	return false;
	};
	m=n*sizeof(N_OBJSAVE)+sizeof(N_PWFHEAD);
	buf1=new char[m+100];
	ph=(N_PWFHEAD*)buf1;
	fseek(fp,0,SEEK_SET);
	fread(buf1,m,1,fp);
	//��һ��������Сͼ��
	
	if(ph->spicsum>0)
	{
		fseek(fp,(long)ph->spic.offset,SEEK_SET);
		cobj.LoadSPic(fp);
	};
	
	//�ڶ������������ͼԪ
	if(ph->egpsum>0){
		fseek(fp,(long)ph->epic.offset,SEEK_SET);
		cobj.LoadEGP(fp,head.Version); //����汾��
	};
	//�������������ڴ�ͼԪ
	if(ph->mpicsum>0){
		fseek(fp,(long)ph->mpic.offset,SEEK_SET);
		cobj.LoadMemPic(fp);
	};

	//���Ĳ������븽����Ϣ
	if(ph->apdsum>0){
	 fseek(fp,(long)ph->apdinfo.offset,SEEK_SET);
	 for(i=0;i<ph->apdsum;i++){	
		 if(feof(fp)) break;
	     fread(&atmp,sizeof(N_APDINFO),1,fp);
		 AddAppendInfo(atmp);
	 }
	};
	//���岽������ҳ��ͼ�μ�����
	pagesum=head.pagesum;
	for(i=0;i<head.pagesum;i++)
	{
		fseek(fp,(long)ph->page[i].offset,SEEK_SET);
		LoadPage(fp,i,head.Version);
	};
	fclose(fp);
	delete buf1;
	strcpy(pwfname,fname);
	filebz=1;
	editbz=0;
	ReComputeAllSitePos();//���¼������ʵ��λ��
	return true;
}

//�����ҳ������
bool gdata::LoadPage(FILE *fp,int pg,WORD ver)
{
	FileV30  fv3;
	N_BASATTR btr;		//��������
	char  buf[MAXSIZE]; //��󻺳���10K
	int  i,j,m,sz,bsize;
	DWORD *dw;
	char *lp;
	char *src;     //Դ������
	char *des;	   //Ŀ�껺����
	N_SUBPWF head;
	N_LAYERS ly;	//����ƽṹ
	uncmpres upr;
	fread(&head,sizeof(N_SUBPWF),1,fp);			//��ҳ�����
	if(head.flag!=0xcccc)		return false;	//�����ͷ
	if(head.laysum>MAXLAYER)    return false;	//��̫��    
	page[pg].head=head;
	for(i=0;i<head.laysum;i++){
		fread(&ly,sizeof(N_LAYERS),1,fp);	//��������
		if(ly.flag!=0xffff) return false;	//�������
		strcpy(page[pg].layer[i].name,ly.name);
		clayer=&page[pg].layer[i];			//�趨��ǰ�㣬������Ӷ���
		page[pg].curlay=i;
		m=ly.psize;
		sz=ly.size;
		if(ly.objnum>0&&m>0&&sz>0)
		{
		 //�����ڴ�
		 src=new char[m+100];
		 des=new char[sz+100];
		 fread(src,m,1,fp);
		 //��ѹ����
		 dw=(DWORD*)src;
		 if(dw[0]==ly.size){ //�ֽ���ȫ��ȷ,���Խ�ѹ
			upr.initdata();
			upr.DDeCode(src+4,des,m,dw[0]); //��ѹ
			lp=des;
			for(j=0;j<ly.objnum;j++)
			{
				memset(buf,0,MAXSIZE);
				switch(ver)
				{
				case 3200: //V2�汾
					bsize=fv3.GetBsFromV2(lp,btr,buf);
					break;
				case 3201: //V3�汾
					bsize=fv3.GetBsFromV3(lp,btr,buf);
					break;
				case 3202: //V4�汾
					bsize=fv3.GetBsFromV4(lp,btr,buf);
					break;
				case 3203: //V5�汾
					bsize=fv3.GetBsFromV5(lp,btr,buf);
					break;
				default: continue;
				}
				AddAObject(btr,buf);

				lp+=bsize;
				if((DWORD)(lp-des)>ly.size)	break;
			}
		 }
		 delete src;
		 delete des;
		};
	}
	page[pg].laysum=head.laysum;
	cobj.curzoom=1;
	ZoomPage(0);
	return true;
}

void gdata::SaveToJpg(char *fname)
{
	JpegFile  jpg;
	char *buf;
	int size,i,j,w,h;
	char *src,*des;
	CDIB mdc;
	double oldz;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	//����Ŵ���
	oldz=cobj.curzoom;
	cobj.curzoom=1;
	w=cpage->head.width;
	h=cpage->head.height;
	mdc.Create(w,h);
	ShowBkgd(mdc,CRect(0,0,w,h));
	Showobject(mdc,0,0,CRect(0,0,w,h),0);
	size=h*w*3+100;
	buf=new char[size];
	for(i=0;i<h;i++){
		 src=(char*)mdc.dib+(h-i-1)*mdc.sPerline;
		 des=buf+i*w*3;
		 for(j=0;j<w;j++){
			des[j*3]=src[j*3+2];
			des[j*3+1]=src[j*3+1];
			des[j*3+2]=src[j*3];
		 };
		};
		jpg.RGBToJpegFile(fname,(BYTE*)buf,w,h,true,75);
		delete buf;
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	//�ָ��Ŵ���
	cobj.curzoom=oldz;
}

void gdata::SaveToBmp(char *fname)
{
	FILE *fp;
	CDIB mdc;
	int w,h;
	double oldz;
    BITMAPFILEHEADER bfhdr;
	BITMAPINFOHEADER bi;
	fp=fopen(fname,"w+b");
	if(fp==NULL) return;
	//����Ŵ���
	oldz=cobj.curzoom;
	cobj.curzoom=1;
	w=cpage->head.width;
	h=cpage->head.height;
	mdc.Create(w,h);
	ShowBkgd(mdc,CRect(0,0,w,h));
	Showobject(mdc,0,0,CRect(0,0,w,h),0);
	//////////////////////////
	bi.biSize=sizeof(BITMAPINFOHEADER);
    bi.biWidth=mdc.nWidth;
    bi.biHeight=mdc.nHeight; 
    bi.biPlanes=1;
    bi.biBitCount=24;
	bi.biCompression=BI_RGB; 
    bi.biXPelsPerMeter=0; 
    bi.biYPelsPerMeter=0; 
    bi.biClrUsed=0; 
    bi.biClrImportant=0; 
	bi.biSizeImage=mdc.nHeight*mdc.sPerline; 
    bfhdr.bfType = ('M' << 8) | 'B';
    bfhdr.bfReserved1 = 0;
    bfhdr.bfReserved2 = 0;
    bfhdr.bfOffBits = sizeof(BITMAPFILEHEADER) +
                       sizeof(BITMAPINFOHEADER);
    bfhdr.bfSize = (long)mdc.nHeight*mdc.sPerline+bfhdr.bfOffBits;
    fwrite((unsigned char*)&bfhdr,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite((unsigned char*)&bi,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(mdc.dib,mdc.dibsize,1,fp);
	fclose(fp);
	//�ָ��Ŵ���
	cobj.curzoom=oldz;
}

//���һ����ҳ��
bool gdata::AddNewPage()
{
	int n;
	if(pagesum>=MAXPAGE){
		MessageBox(0,"ҳ��������������ӣ�","����",MB_OK|MB_ICONERROR);	
		return false; //����
	}
	page[pagesum].laysum=1;
	page[pagesum].curlay=0;
	page[pagesum].head.BgColor=0;
	page[pagesum].head.height=768;
	page[pagesum].head.width=1024;
	page[pagesum].head.imgID=-1;
	strcpy(page[pagesum].head.Name,"�µĽ����ļ�");
	cobj.curzoom=1;
	page[pagesum].zw=page[pagesum].head.width;
	page[pagesum].zh=page[pagesum].head.height;
	n=pagesum;
	pagesum++; //������һ
	GoToPage(n);
	return true;
}

//���һ���²���
bool gdata::AddNewLayer()
{
	int n;
	if(cpage->laysum>MAXLAYER){
		MessageBox(0,"����������������ӣ�","����",MB_OK|MB_ICONERROR);	
		return false; //����
	}
	n=cpage->laysum;
	strcpy(cpage->layer[n].name,"�²���");
	cpage->layer[n].obj=NULL;
	cpage->layer[n].objnum=0;
	cpage->layer[n].show=1;
	cpage->layer[n].select=1;
	cpage->laysum++;
	clayer=&cpage->layer[n];
	cpage->curlay=n;
	return true;
}

//ȡ�ô����ͼ�ε�ַ
bool gdata::GetProcImgBuf(BYTE **buf, int &w, int &h)
{
	int j,id;
	N_IMG *img;
	j=GetFirstSelObj();
	if(j<0) return false;
	if(clayer->obj[j].attr.type!=15) return false;
	img=(N_IMG*)clayer->obj[j].buf;
	id=img->imgID;
	j=cobj.GetMPICRecno(id);
	if(j<0) return false;
	*buf=(BYTE*)cobj.mpic[j].dc.dib;
	w=cobj.mpic[j].dc.nWidth;
	h=cobj.mpic[j].dc.nHeight;
	return true;
}

bool gdata::SelIsThisType(BYTE type) //�Ƿ�ǰѡ��Ķ�����ͼ��
{
	int j;
	j=GetFirstSelObj();
	if(j<0) return false;
	if(clayer->obj[j].attr.type==type) return true;
	return false;
}

//���һ��ճ����λͼ
void gdata::AddPasteImg(HBITMAP hbmp)
{
	N_BASATTR attr;
	N_IMG pimg;
	RECT rt;
	int w,h,w1,h1,id;
	BITMAP bm;
	HDC hdc;
	if(cobj.mpicsum>=100) return;
    GetObject(hbmp, sizeof(bm),(LPSTR)&bm);
	w=bm.bmWidth;
	h=bm.bmHeight;
	if(w==0||h==0) return;
	id=cobj.GetANoUseMPICID();
	cobj.mpic[cobj.mpicsum].id=id;
	cobj.mpic[cobj.mpicsum].inuse=1;
	cobj.mpic[cobj.mpicsum].trancolor=1;
	cobj.mpic[cobj.mpicsum].tranmode=0;
	cobj.mpic[cobj.mpicsum].dc.Create(w,h);
	hdc=CreateCompatibleDC(NULL);
	SelectObject(hdc,hbmp);
	BitBlt(cobj.mpic[cobj.mpicsum].dc.m_hDC,0,0,w,h,hdc,0,0,SRCCOPY);
	DeleteDC(hdc);
	attr.ID=100;
	attr.size=sizeof(N_IMG);
	attr.type=15;
	w1=page[curpage].head.width;
	h1=page[curpage].head.height;
	rt.left=(w1-w)/2;
	rt.top=(h1-h)/2;
	rt.right=rt.left+w;
	rt.bottom=rt.top+h;
	pimg.pt[0].x=rt.left;pimg.pt[0].y=rt.top;
	pimg.pt[1].x=rt.right;pimg.pt[1].y=rt.top;
	pimg.pt[2].x=rt.right;pimg.pt[2].y=rt.bottom;
	pimg.pt[3].x=rt.left;pimg.pt[3].y=rt.bottom;
	pimg.imgID=id;
	pimg.depth=0;
	pimg.shadow=0;
	pimg.zoom=0;
	cobj.mpicsum++;
	AddAObject(attr,&pimg,1);
}

//�û������ѡ��ͼƬ�����С�����ñ������
void gdata::ClearImgBg(CPoint point)
{
	int x,y,mode;
	CPoint pt[2];
	HDC hdc=GetProcImgDC(mode,x,y);
	if(hdc==NULL) return;
	pt[0]=point;
	pt[1]=oldpt1;
	pt[0].Offset(-dx-x,-dy-y);
	pt[1].Offset(-dx-x,-dy-y);
	oldpt1=point;
	if(mode==1){ //��ͼ���ϻ�
		BDrawDbx(hdc,2,pt,pwidth,1,0,0,0,0);
	};
}

//ȡ�ô����ͼ��DC
HDC gdata::GetProcImgDC(int&mode,int &x,int &y)
{
	int j,id;
	N_IMG *img;
	j=GetFirstSelObj();
	mode=0;
	x=0;
	y=0;
	if(clayer->obj[j].attr.type!=15)  return NULL;
	img=(N_IMG*)clayer->obj[j].buf;
	x=(int)img->pt[0].x;
	y=(int)img->pt[0].y;
	id=img->imgID;
	j=cobj.GetMPICRecno(id);
	if(j<0) return NULL;
	mode=1;
	return cobj.mpic[j].dc.m_hDC;
}

//��ȥһ��ͼ��
CRect gdata::CutImage(CPoint point)
{
	int i,j,x,y,id;
	CPoint pt;
	CRect rt;
	N_IMG *img;
	rt.SetRectEmpty();
	i=GetFirstSelObj();

	
	if(clayer->obj[i].attr.type!=15)  return rt;
	

	img=(N_IMG*)clayer->obj[i].buf;
	id=img->imgID;
	j=cobj.GetMPICRecno(id);
	if(j<0) return rt;
	
	

	pt=point;
	x=(int)img->pt[0].x;
	y=(int)img->pt[0].y;;
	pt.Offset(-x,-y);
	pt.Offset(-dx,-dy);
	cobj.mpic[j].dc.FloodFill(pt);
	clayer->obj[i].ort.GetRECT(rt);
	return rt;
}

CRect gdata::TranImage(CPoint point)
{
	int i,j,x,y,id;
	RGB24 color;
	CPoint pt;
	CRect rt;
	N_IMG *img;
	rt.SetRectEmpty();
	i=GetFirstSelObj();
	if(clayer->obj[i].attr.type!=15)  return rt;
	img=(N_IMG*)clayer->obj[i].buf;
	id=img->imgID;
	j=cobj.GetMPICRecno(id);
	if(j<0) return rt;
	pt=point;
	x=(int)img->pt[0].x;
	y=(int)img->pt[0].y;
	pt.Offset(-x,-y);
	pt.Offset(-dx,-dy);
	if(!cobj.mpic[j].dc.GetPixel(pt.x,pt.y,color)) return rt;
	cobj.mpic[j].dc.TranImage(RGB(color.r,color.g,color.b),0x101010);
	clayer->obj[i].ort.GetRECT(rt);
	return rt;
}

//��ˢ��ˢͼ��
CRect gdata::BrushImage(CPoint point,DWORD color)
{
	int i,j,x,y,id,r;
	CPoint pt;
	CRect rt;
	N_IMG *img;
	rt.SetRectEmpty();
	i=GetFirstSelObj();
	r=32;
	if(clayer->obj[i].attr.type==15){
		img=(N_IMG*)clayer->obj[i].buf;
		id=img->imgID;
		j=cobj.GetMPICRecno(id);
		if(j<0) return rt;
		pt=point;
		pt.Offset(-dx,-dy);
		x=(int)img->pt[0].x;
		y=(int)img->pt[0].y;
		pt.Offset(-x,-y);
		cobj.mpic[j].dc.PenBrush(pt.x,pt.y,r,color);
		rt=CRect(point.x-r,point.y-r,point.x+r,point.y+r);
		return rt;
	}
	pt=point;
	pt.Offset(-dx,-dy);
	rt=CRect(point.x-r,point.y-r,point.x+r,point.y+r);
	return rt;
}

//ͼ�μ���
CRect gdata::AddBrightImg(CPoint point)
{
	int i,j,x,y,id,r;
	CPoint pt;
	CRect rt;
	N_IMG *img;
	rt.SetRectEmpty();
	i=GetFirstSelObj();
	r=32;
	if(clayer->obj[i].attr.type==15){
		img=(N_IMG*)clayer->obj[i].buf;
		id=img->imgID;
		j=cobj.GetMPICRecno(id);
		if(j<0) return rt;
		pt=point;
		x=(int)img->pt[0].x;
		y=(int)img->pt[0].y;
		pt.Offset(-x,-y);
		pt.Offset(-dx,-dy);
		cobj.mpic[j].dc.AddPenBrush(pt.x,pt.y,r);
		rt=CRect(point.x-r,point.y-r,point.x+r,point.y+r);
		return rt;
	}
	pt=point;
	pt.Offset(-dx,-dy);
	rt=CRect(point.x-r,point.y-r,point.x+r,point.y+r);
	return rt;
}

//��ʾ��������
void gdata::ShowRgn(HDC hdc, int style,int sdx,int sdy)
{
	int i;
	CPoint pt,pt1;
	HPEN hpen,oldp;
	if(selrgn==0) return;
	hpen=CreatePen(PS_DOT,1,style==0 ? 0:0xffffff);
	oldp=(HPEN)SelectObject(hdc,hpen);
	DWORD oldb=SetBkColor(hdc,style==0 ? 0xffffff:0);
	pt1=tpt[0];
	pt1.Offset(sdx,sdy);
	MoveToEx(hdc,pt1.x,pt1.y,NULL);
	for(i=1;i<tptsum;i++){
	  pt=tpt[i];
	  pt.Offset(sdx,sdy);
	  LineTo(hdc,pt.x,pt.y);
	};
	LineTo(hdc,pt1.x,pt1.y);
	SelectObject(hdc,oldp);
	SetBkColor(hdc,oldb);
	DeleteObject(hpen);
};

//����ͼƬ��һ������
void gdata::CutImgRgn()
{
	int i,j,k,id,x,y,n;
	CPoint *pt;
	N_IMG *img;
	j=GetFirstSelObj();
	if(clayer->obj[j].attr.type!=15) return;
	img=(N_IMG*)clayer->obj[j].buf;
	id=img->imgID;
	k=cobj.GetMPICRecno(id);
	if(k<0) return;
	x=(int)img->pt[0].x;
	y=(int)img->pt[0].y;
	n=tptsum;
	pt=new CPoint[n+1];
	for(i=0;i<n;i++){
		pt[i]=tpt[i];
		pt[i].Offset(-x,-y);
	};
	GLPolygonc(cobj.mpic[k].dc.m_hDC,pt,n,1,1,0);
	delete pt;
}

//ȥ��ͼ����δ�ò��֣�����ͼ�οռ䣩
void gdata::CutMpicNoUse()
{
	int i,j;
	N_IMG *im;
	i=GetFirstSelObj();
	if(i<0) return;
	if(clayer->obj[i].attr.type!=15) return;
	 im=(N_IMG*)clayer->obj[i].buf;
	j=cobj.GetMPICRecno(im->imgID);
	if(j>=0){
	 cobj.mpic[j].dc.CutNoUse();
	};
}

//�ҵ�һ���ڶ����ϵ��ߵĶ˵㣬�Ա�����������
bool gdata::FindALineDot(CDRect ert,DPOINT &ept)
{
	int i,j,k;
	CDPoint ap;
	N_DBX  *dbx;
	N_ARROW *arr;
	for(i=0;i<cpage->laysum;i++){
		for(j=0;j<cpage->layer[i].objnum;j++){
			if(cpage->layer[i].obj[j].attr.type==1){ //�����
				dbx=(N_DBX*)cpage->layer[i].obj[j].buf;
				ap.x=dbx->pt[0].x;
				ap.y=dbx->pt[0].y;
				if(ert.PtInRect(ap)){
					ept.x=ap.x;
					ept.y=ap.y;
					return true;
				}
				k=dbx->ptsum;
				k=k-1;
				if(k>=1){
					ap.x=dbx->pt[k].x;
					ap.y=dbx->pt[k].y;
					if(ert.PtInRect(ap)){
					ept.x=ap.x;
					ept.y=ap.y;
					return true;
				}
				}

			}
			if(cpage->layer[i].obj[j].attr.type==7){ //��ͷ
				arr=(N_ARROW*)cpage->layer[i].obj[j].buf;
				ap.x=arr->pt[0].x;
				ap.y=arr->pt[0].y;
				if(ert.PtInRect(ap)){
					ept.x=ap.x;
					ept.y=ap.y;
					return true;
				}
			}
		}
	}
	return false;
}

//�������ϼ�һ��
bool gdata::AddLineDot(CPoint point)
{
	
	N_DBX		*dbx;
	N_CONLINE	*cn;
	N_FLOW		*fl;
	N_PATH		*ph;
	N_ZONE		*zn;
	int i,j,n,k,size;
	HRGN	trgn;
	CPoint *cpt,pt;
	CDPoint apt;
	DPOINT *npt;
	apt.SetPOINT(point);
	apt.Offset(-dx,-dy);
	apt.GetPOINT(pt);
	j=GetFirstSelObj();
	if(j<0) return false;
	switch(clayer->obj[j].attr.type){
		case 1:
			dbx=(N_DBX*)clayer->obj[j].buf;
			npt=dbx->pt;
			n=dbx->ptsum;
			break;
		case 16:
			ph=(N_PATH*)clayer->obj[j].buf;
			npt=ph->pt;
			n=ph->ptsum;
			break;
	    case 77:
			fl=(N_FLOW*)clayer->obj[j].buf;
			npt=fl->pt;
			n=fl->ptsum;
		    break;
	    case 78:
			cn=(N_CONLINE*)clayer->obj[j].buf;
			npt=cn->pt;
			n=cn->ptsum;
		    break;
		case 83:
			zn=(N_ZONE*)clayer->obj[j].buf;
			npt=zn->pt;
			n=zn->ptsum;
			break;
	   default:return false;
	}
	cpt=new CPoint[n+2];
	for(i=0;i<n;i++){
		cpt[i].x=(int)(npt[i].x*cobj.curzoom);
		cpt[i].y=(int)(npt[i].y*cobj.curzoom);
	}
	trgn=NULL;
	k=-1;
	for(i=0;i<n-1;i++){
		trgn=BCreateLineRGN(cpt[i],cpt[i+1],10);
		if(PtInRegion(trgn,pt.x,pt.y)){
			k=i;
			break;
		}
	}
	if(k!=-1){
		//����UNDO����
		cobj.unp.AddAUndoOp(1);
		switch(clayer->obj[j].attr.type){
		case 1:
			size=sizeof(N_DBX)+(n+1)*sizeof(DPOINT);
			clayer->obj[j].buf=(void*)realloc(clayer->obj[j].buf,size);
			dbx=(N_DBX*)clayer->obj[j].buf;
			dbx->ptsum=(WORD)(n+1);
			npt=dbx->pt;
			break;
		case 16:
			size=sizeof(N_PATH)+(n+1)*sizeof(DPOINT);
			clayer->obj[j].buf=(void*)realloc(clayer->obj[j].buf,size);
			ph=(N_PATH*)clayer->obj[j].buf;
			ph->ptsum=(WORD)(n+1);
			npt=ph->pt;
			break;
		case 77:
			size=sizeof(N_FLOW)+(n+1)*sizeof(DPOINT);
			clayer->obj[j].buf=(void*)realloc(clayer->obj[j].buf,size);
			fl=(N_FLOW*)clayer->obj[j].buf;
			fl->ptsum=(WORD)(n+1);
			npt=fl->pt;
			break;
		case 78:
			size=sizeof(N_CONLINE)+(n+1)*sizeof(DPOINT);
			clayer->obj[j].buf=(void*)realloc(clayer->obj[j].buf,size);
			cn=(N_CONLINE*)clayer->obj[j].buf;
			cn->ptsum=(WORD)(n+1);
			npt=cn->pt;
			break;
		case 83:
			size=sizeof(N_ZONE)+(n+1)*sizeof(DPOINT);
			clayer->obj[j].buf=(void*)realloc(clayer->obj[j].buf,size);
			zn=(N_ZONE*)clayer->obj[j].buf;
			zn->ptsum=(WORD)(n+1);
			npt=zn->pt;
			break;
		}
		clayer->obj[j].attr.size=size;
		apt.ScrPtToAct(cobj.curzoom);
		for(i=n;i>k;i--) npt[i]=npt[i-1];
		npt[k+1].x=apt.x;
		npt[k+1].y=apt.y;
		SetOpPoint(clayer->obj[j]);
		clayer->obj[j].SetSelected();
	}
	delete cpt;
	if(k==-1) return false;
	return true;
}

bool gdata::SubLineDot(CPoint point)
{
	N_DBX		*dbx;
	N_CONLINE	*cn;
	N_FLOW		*fl;
	N_PATH		*ph;
	N_ZONE      *zn;
	int i,j,n,k,size;
	DPOINT *npt;
	j=GetFirstSelObj();
	if(j<0) return false;
	switch(clayer->obj[j].attr.type){
		case 1:
			dbx=(N_DBX*)clayer->obj[j].buf;
			npt=dbx->pt;
			n=dbx->ptsum;
			break;
		case 16:
			ph=(N_PATH*)clayer->obj[j].buf;
			npt=ph->pt;
			n=ph->ptsum;
			break;
	    case 77:
			fl=(N_FLOW*)clayer->obj[j].buf;
			npt=fl->pt;
			n=fl->ptsum;
		    break;
	    case 78:
			cn=(N_CONLINE*)clayer->obj[j].buf;
			npt=cn->pt;
			n=cn->ptsum;
		    break;
		case 83:
			zn=(N_ZONE*)clayer->obj[j].buf;
			npt=zn->pt;
			n=zn->ptsum;
			break;
	   default:return false;
	}
	if(n<3) return false;
	if(GetCursor(point)!=101) return false;
	if(selop<1||selop>n) return false;
	//����UNDO����
	cobj.unp.AddAUndoOp(1);

	k=selop-1;
	switch(clayer->obj[j].attr.type){
	case 1:
		size=sizeof(N_DBX)+(n-1)*sizeof(DPOINT);
		dbx->ptsum=n-1;
		break;
	case 16:
		size=sizeof(N_PATH)+(n-1)*sizeof(DPOINT);
		ph->ptsum=n-1;
		break;
	case 77:
		size=sizeof(N_FLOW)+(n-1)*sizeof(DPOINT);
		fl->ptsum=n-1;
		break;
	case 78:
		size=sizeof(N_CONLINE)+(n-1)*sizeof(DPOINT);
		cn->ptsum=n-1;
		break;
	case 83:
		size=sizeof(N_ZONE)+(n-1)*sizeof(DPOINT);
		zn->ptsum=n-1;
		break;
	}
	for(i=k;i<n;i++) npt[i]=npt[i+1];
	clayer->obj[j].attr.size=size;
	SetOpPoint(clayer->obj[j]);
	clayer->obj[j].SetSelected();
	
	return true;
}

//���ͼԪ��
void gdata::SingleEGrp()
{
	N_ELEGRPA *eg;
	N_ELEGRPYB *yb;
	CDRect rt1,rt2;
	CPoint pt;
	double xl,yl,w1,w2,h1,h2,x,y;
	int i,j,k,l,id,no;
	j=GetFirstSelObj();
	if(j<0) return;

	rt2=clayer->obj[j].ort;
	switch(clayer->obj[j].attr.type)
	{
	case 66:
		eg=(N_ELEGRPA*)clayer->obj[j].buf;
		id=eg->egrpid;
		no=eg->showno;
		break;
	case 67:
		yb=(N_ELEGRPYB*)clayer->obj[j].buf;
		id=yb->egrpid;
		no=0;
		break;
	default:
		return;
	}

	l=cobj.GetEGPRecNo(id);
	if(l<0) return;
	if(no==0) rt1.SetDRECT(cobj.egp[l].rt1);else rt1.SetDRECT(cobj.egp[l].rt2);
	k=no==0 ? cobj.egp[l].bsum1:cobj.egp[l].bsum2;
	if(k<=0) return;
	//�����ȿ�����������
	FreeCpyObj();
	for(i=0;i<k;i++){
		if(no==0) AddCpyObj(cobj.egp[l].bs1[i].attr,cobj.egp[l].bs1[i].buf);
		else AddCpyObj(cobj.egp[l].bs2[i].attr,cobj.egp[l].bs2[i].buf);
	}
	//�����������С
	w1=rt2.Width();
	h1=rt2.Height();
	w2=rt1.Width(); 
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	xl=(double)w1/w2;
	yl=(double)h1/h2;
	rt1=CDRect(0,0,w1,h1);
	for(i=0;i<cpysum;i++){
		cpyobj[i].SetSelected();
		cpyobj[i].MoveObject2(rt1,xl,yl);
	};
	x=cpyobj[0].ort.left;
	y=cpyobj[0].ort.top;
	for(i=1;i<cpysum;i++){
		if(cpyobj[i].ort.left<x) x=cpyobj[i].ort.left;
		if(cpyobj[i].ort.top<y)  y=cpyobj[i].ort.top;
	};
	for(i=0;i<cpysum;i++){
		cpyobj[i].Offset(-x,-y);
	};
	//��ճ����ԭ��λ��
	x=rt2.left;
	y=rt2.top;
	PasteObject(x,y);
	//ɾ��ԭ�������ͼ
	DeleteAObject(j);//ע�⣺���в����ƶ���PasteObject()��ǰ�棬����ƶ��ᷢ������
}


//����λ�����������ӵĵ�,����������Ϣ
bool gdata::SerchConnect(D_SITEC&sit)
{
	int i,j,k,n;
	BYTE vl;
	double w,h;
	N_ELEGRPA *el;
	N_FLOW    *fl;
	N_CONLINE *cn;
	N_BUS     *bus;
	CDRect  srt;
	CPoint point;
	DPOINT tpt[2];
	CDRect  rt,rt1;
	BASE0  *tbs;
	bool   cancmp; //�Ƿ���Ҫ�Ƚ�
	D_SITEC tsit;
	//�ڶ��������¼������ӹ�ϵ
	tsit=sit;
	srt.SetDRECT(sit.srt);
	srt.NormalizeRect();
	//������ĸ�߱Ƚ�
	for(k=0;k<cpage->laysum;k++){ 
		for(i=0;i<cpage->layer[k].objnum;i++){
			tbs=&cpage->layer[k].obj[i];
			if(k==tsit.nlayer&&i==tsit.jlh) cancmp=false;else cancmp=true;
			if(cancmp&&tbs->attr.type!=tsit.etype){
			if(tbs->attr.type==79){
				sit=tsit;
				bus=(N_BUS*)tbs->buf;
				//if(bus->type==3) continue;
				rt1=CreateNRt(4,bus->pt);
				w=rt1.Width();
				h=rt1.Height();
				rt=rt1;
				rt&=srt;
				sit.cpt=rt1.CenterPoint();
				if(sit.vl==-1) sit.vl=bus->vl;
				if(!rt.IsRectEmpty()){
					if(bus->type<2){
					  if(w>h)	sit.cpt.x=(double)((srt.left+srt.right)/2);	
					  else sit.cpt.y=(double)((srt.top+srt.bottom)/2);
					}
					sit.sitn=0;
					sit.id=tbs->attr.ID;
					sit.nlayer=(BYTE)k;
					sit.jlh=i;
					sit.vl=bus->vl;
					return true;
				}	
			}
			}
		}
	}
	//���ͼԪ
	for(k=0;k<cpage->laysum;k++){
		for(i=0;i<cpage->layer[k].objnum;i++){
			tbs=&cpage->layer[k].obj[i];
			if(k==tsit.nlayer&&i==tsit.jlh) cancmp=false;else cancmp=true;
			if(cancmp==true&&tbs->attr.type!=tsit.etype){
			switch(tbs->attr.type){
			 case 66:
				el=(N_ELEGRPA *)tbs->buf;
				n=el->sitesum;
				n=n>3 ? 3:n;
				for(j=0;j<n;j++){
					sit=tsit;
					rt.SetDRECT(el->site[j].srt);
					rt.NormalizeRect();
					sit.cpt=rt.CenterPoint();
					rt1=CreateNRt(4,el->pt);
					rt.Offset((double)rt1.left,(double)rt1.top);
					sit.cpt.x=(double)(sit.cpt.x+rt1.left);
					sit.cpt.y=(double)(sit.cpt.y+rt1.top);
					rt&=srt;
					vl=el->site[0].vl;
					if(el->type==1&&(el->subtype==7||el->subtype==8)) vl=el->site[j].vl;
					if(sit.vl==-1) sit.vl=vl;
					if(!rt.IsRectEmpty()/*&&vl==sit.vl*/){
						el->site[j].id=sit.id;
						el->site[j].sitn=sit.sitn;
						sit.sitn=j;
						sit.nlayer=(BYTE)k;
						sit.jlh=i;
						sit.id=tbs->attr.ID;
						sit.vl=vl;
						return true;
					}
				}
				break;
			case 78:
				cn=(N_CONLINE*)tbs->buf;
				w=srt.Width();
				h=srt.Height();
				for(j=0;j<cn->ptsum;j++){
					sit=tsit;
					rt1.left=(double)(cn->pt[j].x-w);
					rt1.top=(double)(cn->pt[j].y-h);
					rt1.right=(double)(cn->pt[j].x+w);
					rt1.bottom=(double)(cn->pt[j].y+h);
					sit.cpt=cn->pt[j];
					rt1&=srt;
					if(sit.vl==-1) sit.vl=cn->vl;
					if(!rt1.IsRectEmpty()/*&&(BYTE)sit.vl==cn->vl*/){
						sit.id=tbs->attr.ID;
						sit.sitn=j;
						sit.nlayer=(BYTE)k;
						sit.jlh=i;
						sit.vl=cn->vl;
						return true;
					}
				}
				break;
			case 77:
				fl=(N_FLOW*)tbs->buf;
				srt.SetDRECT(sit.srt);
				w=srt.Width();
				h=srt.Height();
				tpt[0]=fl->pt[0];
				tpt[1]=fl->pt[fl->ptsum-1];
				for(j=0;j<2;j++){
					sit=tsit;
					rt1.left=(double)(tpt[j].x-w);
					rt1.top=(double)(tpt[j].y-h);
					rt1.right=(double)(tpt[j].x+w);
					rt1.bottom=(double)(tpt[j].y+h);
					sit.cpt=tpt[j];
					rt1&=srt;
					if(sit.vl==-1) sit.vl=fl->vl;
					if(!rt1.IsRectEmpty()/*&&(BYTE)sit.vl==fl->vl*/){
						fl->site[j].sitn=sit.sitn;
						fl->site[j].id=sit.id;
						sit.id=tbs->attr.ID;
						sit.sitn=j;
						sit.nlayer=(BYTE)k;
						sit.jlh=i;
						sit.vl=fl->vl;
						return true;
					}
				}
				break;
			}
			}
		}
	}
	sit.jlh=-1;
	sit.id=-1;
	return false;
}

//������ӹ�ϵ
void gdata::ClearRalation()
{

	N_ELEGRPA *el;
	N_FLOW    *fl;
	N_CONLINE *cn;
	int i,j,k;
	for(i=0;i<cpage->laysum;i++){
	  for(j=0;j<cpage->layer[i].objnum;j++){
		switch(cpage->layer[i].obj[j].attr.type){
		case 66:
			el=(N_ELEGRPA *)cpage->layer[i].obj[j].buf;
			for(k=0;k<el->sitesum;k++){
				el->site[k].id=-1;
				el->site[k].sitn=0;
			}		
			break;
		case 77:
			fl=(N_FLOW*)cpage->layer[i].obj[j].buf;
			fl->site[0].id=-1;
			fl->site[1].id=-1;
			break;
		case 78:
			cn=(N_CONLINE*)cpage->layer[i].obj[j].buf;
			cn->lobj[0].jlh=-1;
			cn->lobj[1].jlh=-1;
			cn->conobj=0;
			cn->el=0;
			break;
		};
	  }
	}
}


//�������ӹ�ϵ(�ڲ�ͼ��֮��)�����������ӵ�ID
void gdata::CalRalation()
{
	int i,j,k;
	double w;
	DPOINT tpt[2];
	CDRect rt,rt1;
	D_SITEC sit;
	N_ELEGRPA *el;
	N_FLOW    *fl;
	N_CONLINE *cn;
	CPoint point;
	BASE0  *tbs;
	//��һ�������ԭ�е����ӹ�ϵ
	ClearRalation();
	//�ڶ��������¼������ӹ�ϵ
	for(i=0;i<cpage->laysum;i++){
	  for(j=0;j<cpage->layer[i].objnum;j++){
		tbs=&cpage->layer[i].obj[j];
		switch(tbs->attr.type){
		case 66:
			el=(N_ELEGRPA *)tbs->buf;
			rt1=CreateNRt(4,el->pt);
			for(k=0;k<el->sitesum;k++){
				sit.etype=255;
				sit.jlh=j;
				sit.nlayer=i;
				rt.SetDRECT(el->site[k].srt);
				rt.Offset(rt1.left,rt1.top);
				rt.GetDRECT(sit.srt);
				sit.id=tbs->attr.ID;
				sit.sitn=k;
				if(el->type==1&&(el->subtype==7||el->subtype==8)) sit.vl=el->site[k].vl;
				else sit.vl=el->site[0].vl;
				if(SerchConnect(sit))
				{
					el->site[k].id=sit.id;
					el->site[k].sitn=sit.sitn;
					el->site[k].vl=sit.vl;
				}
			}
			break;
		case 77:
			fl=(N_FLOW*)tbs->buf;
			tpt[0]=fl->pt[0];
			tpt[1]=fl->pt[fl->ptsum-1];
			for(k=0;k<2;k++){
				sit.etype=255;
				sit.jlh=j;
				sit.nlayer=i;
				w=(double)(5/cobj.curzoom);
				rt.left=(double)(tpt[k].x-w);
				rt.top=(double)(tpt[k].y-w);
				rt.right=(double)(tpt[k].x+w);
				rt.bottom=(double)(tpt[k].y+w);
				rt.GetDRECT(sit.srt);
				sit.id=tbs->attr.ID;
				sit.vl=fl->vl;
				sit.sitn=(BYTE)k;	
				if(SerchConnect(sit))
				{
					fl->site[k].id=sit.id;
					fl->site[k].sitn=sit.sitn;
					//fl->vl=sit.vl;
				}
			};
			break;
		case 78:
			cn=(N_CONLINE*)tbs->buf;
			tpt[0]=cn->pt[0];
			tpt[1]=cn->pt[cn->ptsum-1];
			cn->conobj=0;
			cn->el=0;
			for(k=0;k<2;k++){
				sit.etype=255;
				sit.jlh=j;
				sit.nlayer=(BYTE)i;
				cn->lobj[k].jlh=-1;
				w=(double)(5/cobj.curzoom);
				rt.left=(double)(tpt[k].x-w);
				rt.top=(double)(tpt[k].y-w);
				rt.right=(double)(tpt[k].x+w);
				rt.bottom=(double)(tpt[k].y+w);
				rt.GetDRECT(sit.srt);
				sit.id=tbs->attr.ID;
				if(cn->conobj==0) sit.vl=-1;
				sit.sitn=0;
				if(SerchConnect(sit))
				{
					cn->conobj=1; //��ʾ�����ӵ��豸
					//cn->vl=sit.vl;
					cn->lobj[k].layer=sit.nlayer;//���ڲ�
					cn->lobj[k].jlh=(short)sit.jlh;	//��¼��
					cn->lobj[k].sitn=sit.sitn;		//���ӵĶ���
				}
			} 
			break;
		}
	  }
	}
}

//��������
void gdata::AlignLeft()
{
	int i,k;
	double dx;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			dx=(double)(rt1.left-rt.left);
			clayer->obj[i].Offset(-dx,0);
		}
	};
	EndMoveObject();
}

//�Ҷ������
void gdata::AlignRight()
{
	int i,k;
	double dx;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			dx=(double)(rt1.right-rt.right);
			clayer->obj[i].Offset(-dx,0);
		}
	};
	EndMoveObject();
}

//�϶������
void gdata::AlignTop()
{
	int i,k;
	double dy;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			dy=rt1.top-rt.top;
			clayer->obj[i].Offset(0,-dy);
		}
	};
	EndMoveObject();
}
//�¶������
void gdata::AlignBottom()
{
	int i,k;
	double dy;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			dy=rt1.bottom-rt.bottom;
			clayer->obj[i].Offset(0,-dy);
		}
	};
	EndMoveObject();
}
//�ȿ�
void gdata::AlignWidth()
{
	int i,k;
	double w1,w2,xl;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	w1=rt.Width();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			w2=rt1.Width();
			if(w2!=0){
			  xl=(double)(w1/w2);
			  rt1.right=rt1.left;
			  rt1.bottom=rt1.top;
			  clayer->obj[i].MoveObject2(rt1,xl,1);
			}
		}
	};
	EndMoveObject();
}
//�ȸ�
void gdata::AlignHeight()
{
	int i,k;
	double h1,h2,yl;
	CDRect rt,rt1;
	k=firstsel;
	if(k<0||k>=clayer->objnum) return;
	rt=clayer->obj[k].GetObjRect();
	h1=(double)rt.Height();
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1)
		{
			rt1=clayer->obj[i].GetObjRect();
			h2=(double)rt1.Height();
			if(h2!=0){
			  yl=(double)(h1/h2);
			  rt1.right=rt1.left;
			  rt1.bottom=rt1.top;
			  clayer->obj[i].MoveObject2(rt1,1,yl);
			}
		}
	};
	EndMoveObject();
}

typedef struct Dstxy{
	int jlh;    //��¼��
	double pos; //λ��
}Dstxy;
//X�Ⱦ�
void gdata::AlignDstX()
{
	int i,j,k,n;
	double w,xl,dx;
	Dstxy xy[100],tmp;
	n=GetSelSum();
	if(n<3) return;  //����3��û��Ҫ����
	n=n>100 ? 100:n;
	j=-1;
	//�Ѽ�λ��
	for(i=0;i<clayer->objnum;i++){
		if(j>=n) break;
		if(clayer->obj[i].sel==1){
			j++;
			xy[j].jlh=i;
			xy[j].pos=clayer->obj[i].ort.left;
		}
	};
	//λ������
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(xy[i].pos>xy[j].pos){
				tmp=xy[i];
				xy[i]=xy[j];
				xy[j]=tmp;
			}
		}
	}
	w=xy[n-1].pos-xy[0].pos;
	xl=(double)(w/(n-1));
	//����λ��
	for(i=1;i<n-1;i++){
		dx=(double)(xy[0].pos+xl*i-xy[i].pos);	
		k=xy[i].jlh;
		clayer->obj[k].MoveObject1(dx,0,0);
	}
	EndMoveObject();
}

//X�Ⱦ�
void gdata::AlignDstY()
{
	int i,j,k,n;
	double h,yl,dy;
	Dstxy xy[100],tmp;
	n=GetSelSum();
	if(n<3) return;  //����3��û��Ҫ����
	n=n>100 ? 100:n;
	j=-1;
	//�Ѽ�λ��
	for(i=0;i<clayer->objnum;i++){
		
		if(j>=n) break;
		if(clayer->obj[i].sel==1){
			j++;
			xy[j].jlh=i;
			xy[j].pos=clayer->obj[i].ort.top;
		}
	};
	//λ������
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(xy[i].pos>xy[j].pos){
				tmp=xy[i];
				xy[i]=xy[j];
				xy[j]=tmp;
			}
		}
	}
	h=xy[n-1].pos-xy[0].pos;
	yl=(double)(h/(n-1));
	//����λ��
	for(i=1;i<n-1;i++){
		dy=(double)(xy[0].pos+yl*i-xy[i].pos);	
		k=xy[i].jlh;
		clayer->obj[k].MoveObject1(0,dy,0);
	}
	EndMoveObject();
}

BASE0* gdata::FindObject(DWORD id)
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].attr.ID==id) 
		return &clayer->obj[i]; //���ض����ַ
	}
	return NULL;
}


int gdata::GetObjectNo(DWORD id)
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].attr.ID==id) 
		return i; //���ض����ַ
	}
	return -1;
}

//��������
bool gdata::CutLine(CPoint point)
{
	N_BASATTR   attr;
	char		*buf;
	N_DBX		*dbx,*dbx1;
	N_CONLINE	*cn,*cn1;
	N_FLOW		*fl,*fl1;
	N_PATH		*ph,*ph1;
	int i,j,m,n,k,size;
	j=GetFirstSelObj();
	if(j<0) return false;
	switch(clayer->obj[j].attr.type){
		case 1:
			dbx=(N_DBX*)clayer->obj[j].buf;
			n=dbx->ptsum;
			break;
		case 16:
			ph=(N_PATH*)clayer->obj[j].buf;
			n=ph->ptsum;
			break;
	    case 77:
			fl=(N_FLOW*)clayer->obj[j].buf;
			n=fl->ptsum;
		    break;
	    case 78:
			cn=(N_CONLINE*)clayer->obj[j].buf;
			n=cn->ptsum;
		    break;
	   default:return false;
	}
	if(n<3) return false;
	if(GetCursor(point)!=101) return false;
	if(selop<2||selop>=n) return false;

	k=selop-1;
	m=n-k;
	//�����µĶ���
	attr=clayer->obj[j].attr;
	attr.ID=GetNewID();
	switch(attr.type){
	case 1:	size=sizeof(N_DBX)+m*sizeof(DPOINT);	break;
	case 16:size=sizeof(N_PATH)+m*sizeof(DPOINT);	break;
	case 77:size=sizeof(N_FLOW)+m*sizeof(DPOINT);	break;
	case 78:size=sizeof(N_CONLINE)+m*sizeof(DPOINT);break;
	}
	attr.size=size;
	buf=new char[attr.size+100];
	memcpy(buf,clayer->obj[j].buf,size); //����ԭ�е�����
	switch(clayer->obj[j].attr.type){
		case 1:
			dbx1=(N_DBX*)buf;
			dbx1->ptsum=m;
			for(i=0;i<m;i++) dbx1->pt[i]=dbx->pt[i+k];
			break;
		case 16:
			ph1=(N_PATH*)buf;
			ph1->ptsum=m;
			for(i=0;i<m;i++) ph1->pt[i]=ph->pt[i+k];
			break;
	    case 77:
			fl1=(N_FLOW*)buf;
			fl1->ptsum=m;
			for(i=0;i<m;i++) fl1->pt[i]=fl->pt[i+k];
		    break;
	    case 78:
			cn1=(N_CONLINE*)buf;
			cn1->ptsum=m;
			for(i=0;i<m;i++) cn1->pt[i]=cn->pt[i+k];
		    break;
		}
	AddAObject(attr,buf,1); //�Ѽ�UNDO����
	delete buf;
	//����UNDO����
	cobj.unp.AddAUndoOp(clayer->obj[j].attr,clayer->obj[j].buf,1);
	//����ԭ����
	m=selop;
	switch(clayer->obj[j].attr.type){
	case 1:
		size=sizeof(N_DBX)+m*sizeof(DPOINT);
		dbx->ptsum=m;
		break;
	case 16:
		size=sizeof(N_PATH)+m*sizeof(DPOINT);
		ph->ptsum=m;
		break;
	case 77:
		size=sizeof(N_FLOW)+m*sizeof(DPOINT);
		fl->ptsum=m;
		break;
	case 78:
		size=sizeof(N_CONLINE)+m*sizeof(DPOINT);
		cn->ptsum=m;
		break;
	}
	clayer->obj[j].attr.size=size;
	SetOpPoint(clayer->obj[j]);
	clayer->obj[j].SetSelected();
	return true;
}

//�쿴�Ƿ���Ժϲ�
bool gdata::CanBindlineSel()
{
	WORD  type=0;
	int i,n;
	if(selbz!=2) return false;
	n=0;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1)
		{
			if(type==0) type=clayer->obj[i].attr.type;
			if(type>0&&type!=clayer->obj[i].attr.type) return false;
			n++;
			if(n>2) return false;
		}
	}
	if(n!=2) return false;
	if(type==1||type==16||type==77||type==78||type==83) return  true;
	return false;
}


typedef struct DSTS
{
	BYTE n;
	double dst;
}DSTS;
//�ϲ�����
bool gdata::BindLine()
{
	BASE0 *bs1,*bs2;
	N_DBX		*dbx;
	N_CONLINE	*cn;
	N_FLOW		*fl;
	N_PATH		*ph;
	N_ZONE      *zn;
	int i,j,k,m,size;
	DSTS dst[4],dtmp;
	int  fill1,close1,ptsum1,fill2,close2,ptsum2;
	DPOINT *pt1,*pt2,*tp,*npt;
	i=GetFirstSelObj();
	if(i<0) return false;
	bs1=&clayer->obj[i];
	k=GetFirstSelObj(i+1);
	if(k<0) return false;
	bs2=&clayer->obj[k];
	if(bs1->attr.type!=bs2->attr.type) return false;
	pt1=bs1->GetObjectPt(ptsum1,fill1,close1,0);
	pt2=bs2->GetObjectPt(ptsum2,fill2,close2,0);
	if(pt1==NULL||pt2==NULL) return false;
	if(close1==1||close2==1) return false; //����Ƿ��ͼ�Σ��˳�
	//����˵�����
	dst[0].dst=GetLength(pt1[0],pt2[0]);
	dst[1].dst=GetLength(pt1[0],pt2[ptsum2-1]);
	dst[2].dst=GetLength(pt1[ptsum1-1],pt2[0]);
	dst[3].dst=GetLength(pt1[ptsum1-1],pt2[ptsum2-1]);
	for(i=0;i<4;i++) dst[i].n=i;
	//����
	for(i=0;i<4;i++){
		for(j=i+1;j<4;j++){
			if(dst[i].dst>dst[j].dst){
				dtmp=dst[i];
				dst[i]=dst[j];
				dst[j]=dtmp;
			}
		}
	}
	m=ptsum1+ptsum2;
	tp=new DPOINT[m];
	switch(dst[0].n){
	case 0:
		for(i=0;i<ptsum1;i++)   tp[i]=pt1[ptsum1-i-1];
		for(i=0;i<ptsum2;i++)	tp[i+ptsum1]=pt2[i];
		break;
	case 1:
		for(i=0;i<ptsum2;i++)   tp[i]=pt2[i];
		for(i=0;i<ptsum1;i++) tp[i+ptsum2]=pt1[i];
		break;
	case 2:
		for(i=0;i<ptsum1;i++)   tp[i]=pt1[i];
		for(i=0;i<ptsum2;i++) tp[i+ptsum1]=pt2[i];
		break;
	case 3:
		for(i=0;i<ptsum1;i++)   tp[i]=pt1[i];
		for(i=0;i<ptsum2;i++)   tp[i+ptsum1]=pt2[ptsum2-i-1];
		break;
	}
	switch(bs1->attr.type){
		case 1:
			size=sizeof(N_DBX)+m*sizeof(DPOINT);
			bs1->buf=(void*)realloc(bs1->buf,size);
			dbx=(N_DBX*)bs1->buf;
			dbx->ptsum=(WORD)m;
			npt=dbx->pt;
			break;
		case 16:
			size=sizeof(N_PATH)+m*sizeof(DPOINT);
			bs1->buf=(void*)realloc(bs1->buf,size);
			ph=(N_PATH*)bs1->buf;
			ph->ptsum=(WORD)m;
			npt=ph->pt;
			break;
		case 77:
			size=sizeof(N_FLOW)+m*sizeof(DPOINT);
			bs1->buf=(void*)realloc(bs1->buf,size);
			fl=(N_FLOW*)bs1->buf;
			fl->ptsum=(WORD)m;
			npt=fl->pt;
			break;
		case 78:
			size=sizeof(N_CONLINE)+m*sizeof(DPOINT);
			bs1->buf=(void*)realloc(bs1->buf,size);
			cn=(N_CONLINE*)bs1->buf;
			cn->ptsum=(WORD)m;
			npt=cn->pt;
			break;
		case 83:
			size=sizeof(N_ZONE)+m*sizeof(DPOINT);
			bs1->buf=(void*)realloc(bs1->buf,size);
			zn=(N_ZONE*)bs1->buf;
			zn->ptsum=(WORD)m;
			npt=zn->pt;
			break;
		}
	for(i=0;i<m;i++) npt[i]=tp[i];
	bs1->attr.size=size;
	DeleteAObject(k);
	ComputNewRect();
	SetOpPoint(bs1[0]);
	bs1->SetSelected();

	delete tp;
	return true;
}


//��Ӹ�����Ϣ
void gdata::AddAppendInfo(N_APDINFO&inf)
{
	int n;
	n=apdsum;
	if(n==0){
	  apdinfo=new N_APDINFO;
	};
	if(n>0){
	  apdinfo=(N_APDINFO*)realloc(apdinfo,sizeof(N_APDINFO)*(n+1));
	};
	memcpy(&apdinfo[n],&inf,sizeof(N_APDINFO));
	apdsum++;
	editbz=1;
}

//����һ��ID�ĸ�����Ϣ
int gdata::GetIndexOfAppInfo(BYTE pageno)
{
	int i;
	for(i=0;i<apdsum;i++){
		if(apdinfo[i].pageno==pageno) return i;
	}
	return -1;
}

void gdata::DelAAppendInfo(BYTE pageno)
{
	int i,j,k;
	j=GetIndexOfAppInfo(pageno);
	if(j>=0){
		for(i=j;i<apdsum-1;i++)	apdinfo[i]=apdinfo[i+1];
		k=apdsum-1;
		if(k>0)	apdinfo=(N_APDINFO*)realloc(apdinfo,sizeof(N_APDINFO)*k);
		else {
			delete apdinfo;
			apdinfo=NULL;
		};
		apdsum=k;
	}
}
//���¼����λ��
void gdata::ReComputeSitePos()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		ComputEsitRect(clayer->obj[i]);
	}
}

//���¼����λ��
void gdata::ReComputeAllSitePos()
{
	int i,j,k;
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].laysum;i++){
			for(k=0;k<page[i].layer[j].objnum;k++){
				ComputEsitRect(page[i].layer[j].obj[k]);
			}
		}
	}
}


void gdata::PrintShow(HDC hdc, BYTE pm, int dx, int dy)
{
	int i,j,n;
	N_layer  *mlay;
	for(i=0;i<cpage->laysum;i++){
		n=cpage->layer[i].objnum;
		mlay=&cpage->layer[i];
		for(j=0;j<n;j++){
			mlay->obj[j].Print(hdc,pm,dx,dy);
		}
	}
}

//����ĳ����������
int gdata::GetObjSum(int type)
{
	int i,j,n;
	n=0;
	for(i=0;i<cpage->laysum;i++){
		for(j=0;j<cpage->layer[i].objnum;j++){
		  if(cpage->layer[i].obj[j].attr.type==type) n++;
		}
	}
	return n;
}

//����ĳ����������
int gdata::HaveDevice()
{
	int i;
	for(i=0;i<clayer->objnum;i++){
		if(clayer->obj[i].sel==1){
			if(clayer->obj[i].IsDeviceObj()) return true;
		}
	}
	return false;
}




//ɾ����ǰҳ��
bool gdata::DelCurPage()
{
	int i;
	if(pagesum<=1) {
		MessageBox(0,"���һ��ҳ�治����ɾ����","����",MB_OK|MB_ICONERROR);	
		return false; //һ��ҳ��ʱ��������ɾ��
	}
	//ɾ��������Ϣ
	DelAAppendInfo((BYTE)curpage);
	//��>pageno�����pageno��1
	for(i=0;i<apdsum;i++){
		if(apdinfo[i].pageno>curpage) apdinfo[i].pageno-=1; 
	}
	//ɾ��ÿһ��
	for(i=0;i<cpage->laysum;i++)    DelLayer(cpage->layer[i]);  
	for(i=curpage;i<pagesum-1;i++)  page[i]=page[i+1];
	pagesum--;
	i=curpage>=pagesum ? curpage-1:curpage;
	GoToPage(i);
	return true;
}
//ɾ����ǰ����
bool gdata::DelCurLayer()
{
	int i,n;
	if(cpage->laysum<=1){
		MessageBox(0,"���һ�����治����ɾ����","����",MB_OK|MB_ICONERROR);		
		return false;
	}
	n=cpage->curlay;
	if(n<0||n>=cpage->laysum) return false;
	DelLayer(cpage->layer[n]);
	for(i=n;i<cpage->laysum-1;i++){
		cpage->layer[i]= cpage->layer[i+1];//cpage[i].layer[i+1];
	}
	cpage->laysum--;
	i=n>=cpage->laysum ? n-1:n;
	clayer=&cpage->layer[i];
	cpage->curlay=i;
	return true;
}

void gdata::DelLayer(N_layer&dlayer)
{
	int i;
	N_IMG *img;
	N_GIFAML *ga;
	N_SPIC  *ss;
	for(i=0;i<dlayer.objnum;i++){
		switch(dlayer.obj[i].attr.type)
		{
		case 17:
			ss=(N_SPIC*)dlayer.obj[i].buf;
			cobj.SpicAddSubUse(ss->picID,-1);
			break;
		case 15:
			img=(N_IMG*)dlayer.obj[i].buf;
			cobj.MpicAddSubUse(img->imgID,-1);
			break;
		case 73:			//GIF����
			ga=(N_GIFAML*)dlayer.obj[i].buf;
			cobj.DelAGifAnl(ga->rec);
			break;
		};
		dlayer.obj[i].FreeMem(); //ɾ����Դ
	};
	free(dlayer.obj);
	dlayer.obj=NULL;
	dlayer.objnum=0;
}
//ѡ��Ķ������õ�ѹ�ȼ�
void gdata::SetVLevel(BYTE vl)
{
	int i;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1){
			clayer->obj[i].SetVLevel(vl);
		}
	}
}

void gdata::SetFont(LOGFONT &lf)
{
	int i;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1){
			clayer->obj[i].SetFont(lf);
		}
	}
}

void gdata::SetColor(DWORD color)
{
	int i;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].sel==1){
			clayer->obj[i].SetColor(color);
		}
	}
}

//�����뱾������ص��ļ�������Ŀ¼��
void gdata::CopyToHmiDir()
{
	int i,j,k,n;
	char fnm[256];
	N_FLASH		*fh;  //type=73
	N_SELFCTL	*sf;  //type=76
	N_GIFAML	*gf;  //type=81
	BASE0  *bs;
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].head.laysum;j++){
			n=page[i].layer[j].objnum;
			bs=page[i].layer[j].obj;
			for(k=0;k<n;k++){
				switch(bs[k].attr.type)
				{
				case 73://FLASH
					fh=(N_FLASH	*)bs[k].buf;
					strcpy(fnm,fh->fname);
					CopyFileTo(fnm);
					strcpy(fh->fname,fnm);
					break;
				case 76: //�����ؼ�
					sf=(N_SELFCTL *)bs[k].buf;
					strcpy(fnm,sf->dllname);
					CopyFileTo(fnm);
					strcpy(sf->dllname,fnm);
					break;
				case 81: //GIF����
					gf=(N_GIFAML *)bs[k].buf;
					strcpy(fnm,gf->fname);
					CopyFileTo(fnm);
					strcpy(gf->fname,fnm);
					break;
				}
			}
		}
	}
}
//���ļ�������HMIĿ¼
void gdata::CopyFileTo(char *filename)
{
	char hfnm[256]; //Ŀ���ļ���
	char lfnm[256];
	char *p1;
	p1=strrchr(filename,'\\');
	if(p1!=NULL) p1++;
	else p1=filename;
	sprintf(hfnm,"%s\\%s",cobj.path[1].path,p1);
	if(cobj.IsFileExist(filename)) strcpy(lfnm,filename);
	else cobj.SetToLocalFile(filename,lfnm);
	if(strcmp(lfnm,hfnm)==0){
		strcpy(filename,p1);
		return; //Ŀ¼��ͬû�б�Ҫ����
	}
	CopyFile(lfnm,hfnm,FALSE);
	strcpy(filename,p1);
}

//����
void gdata::SendHmiToSvr()
{
	int i,j,k,n;
	char fnm[256];
	N_FLASH		*fh;  //type=73
	N_SELFCTL	*sf;  //type=76
	N_GIFAML	*gf;  //type=81
	BASE0  *bs;
	//���͹����ļ�
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].head.laysum;j++){
			n=page[i].layer[j].objnum;
			bs=page[i].layer[j].obj;
			for(k=0;k<n;k++){
				switch(bs[k].attr.type)
				{
				case 73://FLASH
					fh=(N_FLASH	*)bs[k].buf;
					strcpy(fnm,fh->fname);
					SendFileTo(fnm);
					break;
				case 76: //�����ؼ�
					sf=(N_SELFCTL *)bs[k].buf;
					strcpy(fnm,sf->dllname);
					SendFileTo(fnm);
					break;
				case 81: //GIF����
					gf=(N_GIFAML *)bs[k].buf;
					strcpy(fnm,gf->fname);
					SendFileTo(fnm);
					break;
				}
			}
		}
	}
	//���������ļ�
	SendFileTo(pwfname);
	//����ĸ�߹��������ļ�
	SendFileTo("bsralate.cfg");
}

void gdata::SendFileTo(char *filename)
{
	char hfnm[256]; //Ŀ���ļ���
	char *p1;
	p1=strrchr(filename,'\\');
	if(p1!=NULL) p1++;
	else p1=filename;
	sprintf(hfnm,"%s\\%s",cobj.path[1].path,p1);
	if(!cobj.IsFileExist(hfnm)) return;
	SendHmiFile(hfnm);
}

//�쿴�Ƿ��ڴ�ͼ����ʹ��
bool gdata::IsMpicIsInUse(WORD id)
{
	N_IMG *img;
	int i,j,k;
	for(i=0;i<pagesum;i++){
		for(j=0;j<page[i].laysum;i++){
			for(k=0;k<page[i].layer[j].objnum;k++){
				if(page[i].layer[j].obj[k].attr.type!=15) continue;
				img=(N_IMG*)page[i].layer[j].obj[k].buf;
				if(id==img->imgID) return true;
			}
		}
	}
	return false;
}



//ɾ��δ�õ�Mpicͼ��
void gdata::DelNoUseMpic()
{
	int i;
	for(i=0;i<cobj.mpicsum;i++)
	{
		if(!IsMpicIsInUse(cobj.mpic[i].id))
		{
			cobj.DelAMpic(i);
			i--;
		}
	}
}


void gdata::DeleteObjectByid(DWORD id)
{
	int i;
	i=GetObjectNo(id);
	if(i<0) return;
	DeleteAObject(i);
}

//�޸�ѡ����������
void gdata::ModiFont(LOGFONT&lf)
{
	N_TEXT *txt;
	N_ANL  *anl;
	N_DATE *dat;
	N_ZONE *zn;
	N_PUSH *psh;
	int i,j;
	for(i=0;i<cpage->laysum;i++){
	  for(j=0;j<cpage->layer[i].objnum;j++){
		if(cpage->layer[i].obj[j].sel!=1) continue;
		switch(cpage->layer[i].obj[j].attr.type){
		case 10:
			txt=(N_TEXT *)cpage->layer[i].obj[j].buf;
			txt->font=lf;	
			break;
		case 64:
			anl=(N_ANL*)cpage->layer[i].obj[j].buf;
			anl->lf=lf;
			break;
		case 71: case 72:
			dat=(N_DATE*)cpage->layer[i].obj[j].buf;
			dat->font=lf;
			break;
		case 83:   
			zn=(N_ZONE*)cpage->layer[i].obj[j].buf;
			zn->lf=lf;
			break;
		case 75:
			psh=(N_PUSH*)cpage->layer[i].obj[j].buf;
			psh->lf=lf;
			break;
		};
	  }
	}

}


//����ΪSVG��ʽ�ļ�
void gdata::SaveFileSvg(char *filename)
{
	SvgOut svg;
	if(!svg.OpenWFile(filename)) return;
	//��ͼ�ε�ַ���͸�SVGOUT
	svg.cpage=cpage;
	svg.egp=cobj.egp;
	svg.egpsum=cobj.egpsum;
	//д��SVGͷ
	svg.WriteSvgHead();
	//�������ͼԪ
	svg.DefineEleGrp();
	//д��ͼ�ζ���
	svg.DrawOnSvgFile();
	//д�������</svg>,�ر��ļ�
	svg.CloseFile();


}


//��ȡSVG��ʽ�ļ�
void gdata::ImportSvgFile(char *filename)
{
	//�ͷ�ԭ���ڴ�
	FreeMem();
	cobj.FreeMem();

	//��ʼ��ȡͼ��
	CImportSvg svg;
	svg.ReadSvg(filename);
	//�ر��ļ�
	CalRalation();
}

//�������һ����¼������
void gdata::SetLastDevName(char *name,char *pname,int type,int subtype)
{
	N_ANL *anl;
	int j,msgtype,xs,xstype;
	if(clayer->objnum<=0) return;
	j=clayer->objnum-1;
	clayer->obj[j].SetDevName(name,type,subtype);
	if(clayer->obj[j].attr.type==64)
	{
		msgtype=GetMsgType(name);
		xstype=GetXsType(pname);
		xs=SvgAnlTypeToXs(msgtype,xstype);
		anl=(N_ANL *)clayer->obj[j].buf;
		strcpy(anl->dev_name,name);
		anl->dtype=msgtype;
		anl->xsmode=xs;
	}
}

//����CIM����
void gdata::ExchangeCimName()
{
	BYTE type,subtype,vl;
	char dev_name[48],newname[64];
	int i,j,vl1,vl2,vl3,k,m,djlh,n=0;
	BASE0 *obj;
	for(i=0;i<pagesum;i++)
	{
		for(j=0;j<page[i].laysum;j++)
		{
			m=page[i].layer[j].objnum;
			obj=page[i].layer[j].obj;
			for(k=0;k<m;k++)
			{
				switch(obj[k].attr.type)
				{
				case 64:
					if(!obj[k].GetAnlDevType(dev_name,type)) continue;
					if(SVGAnlNameToCim(dev_name,newname,type))
					{
						obj[k].SetDevName_VL(newname,vl1,vl2,vl3);	
					}
					break;
				default:
					if(!obj[k].GetDevType(type,subtype,vl,dev_name,djlh)) continue;
					if(type!=2) continue;
					vl1=0;vl2=0;vl3=0;
					if(SVGNameToCim(dev_name,newname,subtype,vl1,vl2,vl3))	//��������Դ���ó���
					{
						newname[23]=0;
						obj[k].SetDevName_VL(newname,vl1,vl2,vl3);	
					}
					break;
				}
			}
		}
	}
}


void gdata::GetEleFromClipboard(HWND hwnd)
{
	HGLOBAL hglb;
	//�쿴�Ƿ����������
	if(OpenClipboard(hwnd))
	{
		hglb=GetClipboardData(cobj.clptype);
		if(hglb!=NULL) //������д���ڴ�
		{
			ClpToMem(hglb);
		}
		CloseClipboard();
	}
}

bool gdata::LoadSvgAndSave(const char *pSvg, const char *pPw0)
{
	char fnm[256];
	//�ͷ�ԭ���ڴ�
	FreeMem();
	cobj.FreeMem();

	CImportSvg  svg;
	//��ʼ��ȡͼ��
	svg.ReadSvg(pSvg);

	CalRalation();
	SaveFile(pPw0);

	strcpy(fnm,pPw0);
	CopyFileTo(fnm);
	//�����ļ���������
	SendHmiToSvr();

	return true;
}
