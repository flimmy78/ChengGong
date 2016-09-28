// NetTpy.cpp: implementation of the CNetTpy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualpower.h"
#include "NetTpy.h"
#include "DObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetTpy::CNetTpy()
{
	//����ȱʡ����
	bus=NULL;		//ĸ��
	line=NULL;		//��·
	dev=NULL;		//�豸
	conl=NULL;	    //������
	node=NULL;		//�ڵ�

	bussum=0;
	linsum=0;
	devsum=0;
	colsum=0;
	nodsum=0;
	fwidth=5;
}

CNetTpy::~CNetTpy()
{
	FreeMem();
}

void CNetTpy::FreeMem()
{
	if(bus!=NULL)  delete []bus;		
	if(line!=NULL) delete []line;
	if(dev!=NULL)  delete []dev;
	if(conl!=NULL) delete []conl;
	if(node!=NULL) delete []node;

	bus=NULL;		
	line=NULL;
	dev=NULL;
	conl=NULL;
	node=NULL;

	bussum=0;
	linsum=0;
	devsum=0;
	colsum=0;
	nodsum=0;
}
//�ռ�״̬�㼴�豸
void CNetTpy::SetDevice(RSTA *r_st, int nDev)
{
	int i,j,k;
	CDRect art;
	if(dev!=NULL) delete []dev;
	dev=NULL;
	devsum=0;
	if(nDev<=0) return;
	dev=new C_DEV[nDev];
	for(i=0;i<nDev;i++){
		dev[i].bs=r_st[i].bs;
		dev[i].ele=r_st[i].elg;
		dev[i].type=dev[i].ele->subtype;
		k=dev[i].ele->sitesum;
		k=k>3 ? 3:k;
		dev[i].sitsum=k;
		for(j=0;j<k;j++){
			dev[i].msite[j].id=-1;
			dev[i].msite[j].nodeid=-1;
			art.SetDRECT(dev[i].ele->site[j].srt);
			art.Offset(dev[i].bs->ort.left,dev[i].bs->ort.top);
			art.GetDRECT(dev[i].msite[j].srt);
			if(dev[i].type==7||dev[i].type==8) 	dev[i].msite[j].vl=dev[i].ele->site[j].vl;
			else dev[i].msite[j].vl=dev[i].ele->site[0].vl;
		}
	}
	devsum=nDev;
}
//�ռ�ĸ��
void CNetTpy::SetBus(RBUS *r_bs, int nBus)
{
	int i;
	if(bus!=NULL) delete []bus;
	bus=NULL;
	bussum=0;
	if(nBus<=0) return;
	bus=new C_BUS[nBus];
	for(i=0;i<nBus;i++){
		bus[i].bs=r_bs[i].bs;
		bus[i].bus=r_bs[i].bus;
		bus[i].msite.id=-1;
		bus[i].msite.nodeid=-1;
		bus[i].msite.vl=bus[i].bus->vl;
		bus[i].bs->ort.GetDRECT(bus[i].msite.srt);
	}
	bussum=nBus;
}
//�ռ���·
void CNetTpy::SetLine(RFLOW *r_fw, int nLine)
{
	int i,j,k;
	if(line!=NULL) delete []line;
	line=NULL;
	linsum=0;
	if(nLine<=0) return;
	line=new C_LINE[nLine];
	for(i=0;i<nLine;i++){
		line[i].bs=r_fw[i].bs;
		line[i].lin=r_fw[i].flw;
		for(j=0;j<2;j++){
			line[i].msite[j].id=-1;
			line[i].msite[j].nodeid=-1;
			line[i].msite[j].vl=line[i].lin->vl;
		}
		k=line[i].lin->ptsum;
		line[i].msite[0].npt=line[i].lin->pt[0];
		line[i].msite[1].npt=line[i].lin->pt[k-1];
	}
	linsum=nLine;
}
//�ռ�������
void CNetTpy::SetConLine(RCONL *r_cl, int nCln)
{
	int i,j,k;
	if(conl!=NULL) delete []conl;
	conl=NULL;
	colsum=0;
	if(nCln<0) return;
	conl=new C_CONLINE[nCln];
	for(i=0;i<nCln;i++){
		conl[i].bs=r_cl[i].bs;
		conl[i].conl=r_cl[i].lin;
		for(j=0;j<2;j++){
			conl[i].msite[j].id=-1;
			conl[i].msite[j].nodeid=-1;
			conl[i].msite[j].vl=conl[i].conl->vl;
		}
		k=conl[i].conl->ptsum;
		conl[i].msite[0].npt=conl[i].conl->pt[0];
		conl[i].msite[1].npt=conl[i].conl->pt[k-1];
	}
	colsum=nCln;
}

//���һ���ڵ�
int CNetTpy::AddANode()
{
	int n;
	n=nodsum;
	if(n==0){
	  node=new C_NODE;
	};
	if(n>0){
	  node=(C_NODE*)realloc(node,sizeof(C_NODE)*(n+1));
	};
	node[n].nodeid=n;
	nodsum++;
	return n; //�����µ�ID
}

//����Ψһ�Ķ���ID
void CNetTpy::AloteSite()
{
	int i,j,n;
	n=0;
	for(i=0;i<bussum;i++){
		bus[i].msite.id=n;	
		n++;
	}
	for(i=0;i<linsum;i++){
		line[i].msite[0].id=n;
		n++;
		line[i].msite[1].id=n;
		n++;
	}
	for(i=0;i<devsum;i++) {
		for(j=0;j<dev[i].sitsum;j++){
			dev[i].msite[j].id=n;
			n++;
		}
	}
}


//����ĳҳ���ӵĿ��
double CNetTpy::GetSiteWidth()
{
	int i;
	double wd,hg;
	CDRect art;
	for(i=0;i<devsum;i++){
		if(dev[i].sitsum>0){
			art.SetDRECT(dev[i].msite[0].srt);
			wd=art.Width();
			hg=art.Height();
			fwidth=wd>hg ? hg:wd;
			fwidth=(double)(fwidth/2);
			fwidth=fwidth<0 ? -fwidth:fwidth;
			fwidth=fwidth==0 ? 5:fwidth;
			return fwidth;
		}
	}
	fwidth=5;
	return fwidth;
}

void CNetTpy::ComputLineSiteRt()
{
	int i,j;
	double w;
	CDRect art;
	DPOINT npt;
	//����������
	for(i=0;i<colsum;i++){
		w=GetSiteWidth();
		for(j=0;j<2;j++){
			npt=conl[i].msite[j].npt;
			art.left=npt.x-w;
			art.right=npt.x+w;
			art.top=npt.y-w;
			art.bottom=npt.y+w;
			art.GetDRECT(conl[i].msite[j].srt);
		}
	}
	//������·
	for(i=0;i<linsum;i++){
		w=GetSiteWidth();
		for(j=0;j<2;j++){
			npt=line[i].msite[j].npt;
			art.left=npt.x-w;
			art.right=npt.x+w;
			art.top=npt.y-w;
			art.bottom=npt.y+w;
			art.GetDRECT(line[i].msite[j].srt);
		}
	}
}


void CNetTpy::ConnectSite(CDRect rt, BYTE vl,int nodeid)
{
	int i,j,k;
	CDRect  trt;
	CDPoint apt;
	//ɨ���豸����
	for(i=0;i<devsum;i++){
		for(j=0;j<dev[i].sitsum;j++){
			trt.SetDRECT(dev[i].msite[j].srt);
			trt&=rt;
			if(dev[i].msite[j].nodeid<0&&dev[i].msite[j].vl==vl){  //û������
			  if(!trt.IsRectEmpty()){
				dev[i].msite[j].nodeid=nodeid;
			  }
			}
		}
	}
	//ɨ����·
	for(i=0;i<linsum;i++){
	 for(j=0;j<2;j++){
	  if(line[i].msite[j].nodeid<0&&line[i].msite[j].vl==vl){
		  trt.SetDRECT(line[i].msite[j].srt);
		  trt&=rt;
		  if(!trt.IsRectEmpty()){
			line[i].msite[j].nodeid=nodeid;
		  }
		}
	 }
	}
	//ɨ��������
	for(i=0;i<colsum;i++){
	  for(j=0;j<2;j++){
		if(conl[i].msite[j].nodeid<0){
		  trt.SetDRECT(conl[i].msite[j].srt);
		  trt&=rt;
		  if(!trt.IsRectEmpty()){
			conl[i].msite[j].nodeid=nodeid;
			k=j==0 ? 1:0;
	 		if(conl[i].msite[k].nodeid<0){ //�ݹ�
				conl[i].msite[k].nodeid=nodeid;
				trt.SetDRECT(conl[i].msite[k].srt);
				ConnectSite(trt,vl,nodeid);
				}
			  }
			}
		}
	}
}

//�����ڵ㲢��������
void CNetTpy::CreateNode()
{
	int i,j,n;
	CDRect art;
	if(node!=NULL) delete node; 
	node=NULL;
	//��һ��:��ɨ��ĸ��
	for(i=0;i<bussum;i++){
		n=AddANode();  //����һ���ڵ�
		bus[i].msite.nodeid=n;
		art.SetDRECT(bus[i].msite.srt);
		ConnectSite(art,bus[i].msite.vl,n);
	}
	//�ڶ���:��ɨ���豸
	for(i=0;i<devsum;i++){
		for(j=0;j<dev[i].sitsum;j++){
			if(dev[i].msite[j].nodeid<0){
				n=AddANode();  //����һ���ڵ�
				dev[i].msite[j].nodeid=n;
				art.SetDRECT(dev[i].msite[j].srt);
				ConnectSite(art,dev[i].msite[j].vl,n);
			}
		}
	}
	//������:ɨ����·
	for(i=0;i<linsum;i++){
	  for(j=0;j<2;j++){
			if(line[i].msite[j].nodeid<0){
				n=AddANode();
				line[i].msite[j].nodeid=n;
				art.SetDRECT(line[i].msite[j].srt);
				ConnectSite(art,line[i].msite[j].vl,n);
			}
		}
	}
}

//��λ����״̬
void CNetTpy::ReSetEle()
{


}

//���ɵ�����,ʱ�ô���״̬
void CNetTpy::CreateEleIsland()
{
	int i,j;
	CDRect art;
	//�Ӵ����豸��ʼ����
	//��һ��:��ɨ��ĸ��ȷ�����ӵ�Ĵ���״̬
	for(i=0;i<bussum;i++){
		if(bus[i].bus->vr.ele==1)
		{
		 SerachDev(bus[i].msite.nodeid);
		}
	}
	//�ڶ���:ɨ����·ȷ�����ӵ����״̬
	for(i=0;i<linsum;i++){
	  for(j=0;j<2;j++){
			if(line[i].lin->vr.ele==1){
				SerachDev(line[i].msite[j].nodeid);
			}
		}
	}

}

//���ݴ���ڵ������豸
void CNetTpy::SerachDev(int nodeid)
{
	int i,j;
	//�����豸
	for(i=0;i<devsum;i++){
		for(j=0;j<dev[i].sitsum;j++){
			if(dev[i].msite[j].nodeid==nodeid){
				if(dev[i].ele->vr.ele==1) continue;
				if(dev[i].ele->vr.ele==0){
					dev[i].ele->vr.ele=1;
					FindDevOthSite(dev[i],nodeid);//����������
				}
			}
		}
	}
	//����ĸ��
	for(i=0;i<bussum;i++){
		if(bus[i].msite.nodeid==nodeid){
			bus[i].bus->vr.ele=1;
		}
	}
	//������·
	for(i=0;i<linsum;i++){
		for(j=0;j<2;j++){
			if(line[i].msite[j].nodeid==nodeid){
				line[i].lin->vr.ele=1;
			}
		}
	}
	//����������
	for(i=0;i<colsum;i++){
		for(j=0;j<2;j++){
			if(conl[i].msite[j].nodeid=nodeid){
				conl[i].conl->el=1;
			}
		}
	}
}

void CNetTpy::FindDevOthSite(C_DEV &odev,int nodid)
{
	int i;
	for(i=0;i<odev.sitsum;i++){
		if(odev.msite[i].nodeid==nodid) continue;
		switch(odev.ele->type){
		case 1://�豸
			switch(odev.ele->subtype){
			case 2:
			  odev.ele->vr.ele=odev.ele->vr.ele; 
			  if(odev.ele->vr.ele==1) SerachDev(odev.msite[i].nodeid);
			  break;
		    default:
			odev.ele->vr.ele=1;
			SerachDev(odev.msite[i].nodeid);
			}
		}
	}
}


//ȷ�������ߴ���״̬
void CNetTpy::CheckConlEle()
{
	int i;
	for(i=0;i<colsum;i++){
		if(GetNodeEle(conl[i].msite[0].nodeid)){ //�ȿ���һ������
			conl[i].conl->el=1;
		}else{
			if(GetNodeEle(conl[i].msite[1].nodeid)){ //��������磬�ٿ��ڶ�������
			conl[i].conl->el=1;
			}
			conl[i].conl->el=0;
		}
	}
}


//���ؽڵ��Ƿ����
bool CNetTpy::GetNodeEle(int nodeid)
{
	int i,j;
	CDRect art;
	//��һ��:��ɨ��ĸ��
	for(i=0;i<bussum;i++){
		if(bus[i].msite.nodeid==nodeid){
			return bus[i].bus->vr.ele==0 ? false:true;
		}
	}
	//�ڶ���:��ɨ���豸
	for(i=0;i<devsum;i++){
		for(j=0;j<dev[i].sitsum;j++){
			if(dev[i].msite[j].nodeid==nodeid){
				return dev[i].ele->vr.ele==0 ? false:true;
			}
		}
	}
	//������:ɨ����·
	for(i=0;i<linsum;i++){
	  for(j=0;j<2;j++){
			if(line[i].msite[j].nodeid==nodeid){
				return line[i].lin->vr.ele==0 ? false:true;
			}
		}
	}
	return false;
}
