// undoop.cpp: implementation of the undoop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "undoop.h"
#include "comobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern comobj cobj;
extern gdata dbm;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

undoop::undoop()
{
	memset(ustp,0,sizeof(UNDOSTEP)*MAXUNDO);
	curstep=0;
}

undoop::~undoop()
{
	FreeMem();
}

//�ͷ�ռ�õ��ڴ�
void undoop::FreeMem()
{
	int i;
	for(i=0;i<MAXUNDO;i++)	FreeAMem(i);
	curstep=0;
}

//�ͷ�ռ�õ��ڴ�
void undoop::FreeAMem(int i)
{
	int j;
	for(j=0;j<ustp[i].objsum;j++){
	   ustp[i].bakbs[j].FreeMem(); //�ͷŶ���
	}
	if(ustp[i].bakbs!=NULL) delete []ustp[i].bakbs;
	ustp[i].bakbs=NULL;
	ustp[i].type=0;
	ustp[i].objsum=0;
}

//����һ��UNDO����
void undoop::AddUndoObj(BASE0&bs,int i)
{
	int n;
	n=ustp[i].objsum;
	if(n==0){
	  ustp[i].bakbs=new BASE0;
	};
	if(n>0){
	  ustp[i].bakbs=(BASE0*)realloc(ustp[i].bakbs,sizeof(BASE0)*(n+1));
	};
	ustp[i].bakbs[n].buf=NULL;
	ustp[i].bakbs[n].bakbuf=NULL;
	ustp[i].bakbs[n].attr=bs.attr;
	if(bs.attr.size>0){
		ustp[i].bakbs[n].buf=new char[bs.attr.size+8];
		memcpy(ustp[i].bakbs[n].buf,bs.bakbuf,bs.attr.size);
	}
	ustp[i].objsum++;
}




//����һ��UNDO����
void undoop::AddAUndoOp(BYTE type)
{
	int i,j,n;
	if(type<1||type>5) return; //��Ч������
	if(curstep>=MAXUNDO){
		FreeAMem(0);
		n=curstep;
		for(i=0;i<n-1;i++)	ustp[i]=ustp[i+1];
		ustp[n-1].bakbs=NULL;
		ustp[n-1].objsum=0;
		ustp[n-1].type=0;
		j=n-1;
	}else{
		j=curstep;
		FreeAMem(j);
	}
	//����UNDO����
	ustp[j].type=type;
	switch(type){
	case 1:case 2:case 3:
		for(i=0;i<dbm.clayer->objnum;i++){
			if(dbm.clayer->obj[i].sel==1){
				AddUndoObj(dbm.clayer->obj[i],j);
			}
		}
		break;
	}
	curstep=curstep<MAXUNDO ? curstep+1:MAXUNDO;
}



//����һ��UNDO����
void undoop::AddAUndoOp(N_BASATTR &attr, void *obuf,BYTE type)
{
	BASE0 bs;
	int i,j,n;
	if(type<1||type>5) return; //��Ч������
	if(curstep>=MAXUNDO){
		FreeAMem(0);
		n=curstep;
		for(i=0;i<n-1;i++)	ustp[i]=ustp[i+1];
		ustp[n-1].bakbs=NULL;
		ustp[n-1].objsum=0;
		ustp[n-1].type=0;
		j=n-1;
	}else{
		j=curstep;
		FreeAMem(j);
	}
	//����UNDO����
	bs.AddObject(attr,obuf);
	bs.SetSelected();
	ustp[j].type=type;
	switch(type){
	case 1:case 2:case 3:
		AddUndoObj(bs,j);
		break;
	}
	curstep=curstep<MAXUNDO ? curstep+1:MAXUNDO;
}


//UNDOһ��
void undoop::UnDOAStep()
{
	int i,j;
	BASE0 *bs;
	if(curstep==0) return;
	j=curstep-1;
	for(i=0;i<ustp[j].objsum;i++){
		switch(ustp[j].type){
		case 1: //�ı�Ϊԭ������
			bs=dbm.FindObject(ustp[j].bakbs[i].attr.ID);
			if(bs!=NULL){
				bs->ReSetValue(ustp[j].bakbs[i].attr,ustp[j].bakbs[i].buf);
			}
			break;
		case 2: //�ָ�ɾ���Ķ���
		   ustp[j].bakbs[i].attr.ID=dbm.GetNewID();
		   dbm.AddAObject(ustp[j].bakbs[i].attr,ustp[j].bakbs[i].buf);
		   break;
		case 3: //ɾ����ӵĶ���
			dbm.DeleteObjectByid(ustp[j].bakbs[i].attr.ID);
			break;
		}
	}
	FreeAMem(j);
	curstep--;
	dbm.ComputNewRect();
}



