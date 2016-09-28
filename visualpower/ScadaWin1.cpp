#include "stdafx.h"
#include "VisualPower.h"
#include "ScadaWin.h"
#include "comobj.h"
#include "middll.h"
#include "DObj.h"
#include "stflwdlg.h"
#include "sendlg.h"
#include "viewdev.h"
#include "math.h"
#include "CrossObj.h"
#include "bclass.h"
#include "Processe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *usertype[];
extern comobj  cobj;		//��������

//������ScadaWin��ĺ���

//���ص�ǰ���
int ScadaWin::GetCursor(CPoint point)
{
	int i,n;
	CPoint pt,pt1;
	CDPoint apt;
	if((cursor>5&&cursor<=10)||(cursor>=1&&cursor<4)) return cursor;
	pt=point;
	pt.Offset(-dx,-dy);
	apt.SetPOINT(pt);
	apt.ScrPtToAct(dbm.curzoom);
	seltype=255;
	seljlh=-1;
	tpint=point;
	if(dbm.lookdown==0)//ƽ��ʱ���豸��ѯ
	{ 
		//�ڶ��泱����
		if(dbm.curopzt==1)
		{
			for(i=0;i<dmsum;i++)
			{
				if(dmsrt[i].PtInRect(apt))
				{
					seltype=254;
					seljlh=i;
					return 4;
				}
			}
		}

		for(i=pesum-1;i>=0;i--){
			if(r_pe[i].bs->PtIsInObj(pt))
			{
				r_pe[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}

		for(i=spesum-1;i>=0;i--){
			if(r_spe[i].bs->PtIsInObj(pt))
			{
				r_spe[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}

		for(i=0;i<rssum;i++)//ˮ��
		{ 
			if(PtInRegion(r_rs[i].hrgn,point.x-dx,point.y-dy))
			{
				if(r_rs[i].res->did==-1) continue;
				r_rs[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}
		for(i=0;i<stsum;i++)
		{
			if(r_st[i].bs->PtIsInObj(pt))
			{
				if(r_st[i].elg->did==-1) continue;
				r_st[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}
		for(i=0;i<bssum;i++)
		{
			if(r_bs[i].bs->PtIsInObj(pt))
			{
				if(r_bs[i].bus->did==-1) continue;
				r_bs[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}
		for(i=0;i<fwsum;i++)
		{
			if(dbm.curopzt==3&&r_fw[i].lfflag==0) continue;
			if(PtInRegion(r_fw[i].hrgn,point.x-dx,point.y-dy))
			{
				if(r_fw[i].flw->did==-1) continue;
				r_fw[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		} 
		for(i=0;i<basum;i++)
		{
			if(r_ba[i].bs->PtIsInObj(pt))
			{
				if(r_ba[i].bar->dsrc.did==-1) continue;
				r_ba[i].bs->GetType(seltype,selsubtype,selid,dsjlh);
				seljlh=i;
				return 4;
			}
		}
		for(i=0;i<phsum;i++)   if(r_ph[i].bs->PtIsInObj(pt)) return 5;
	}

	if(dbm.lookdown==1) //����ʱ����ʾ��ѯ
	{
	    if(dbm.scf.showrev==1||dbm.scf.showrev==2){//����ͼ����²�ѯ����
		  n=rvsum-1;
		  for(i=n;i>=0;i--)
		  {
			if(PtInRegion(r_rv[i].hrgn,point.x-dx,point.y-dy))
			{
				seljlh=i;
				return 4;
			}
		  }
		}

	    if(dbm.scf.showrev==3||dbm.scf.showrev==4){//����ͼ����²�ѯ����
		  n=trsum-1;
		  for(i=n;i>=0;i--)
		  {
			if(PtInRegion(r_tr[i].hrgn,point.x-dx,point.y-dy))
			{
				seljlh=i;
				return 4;
			}
		  }
		}
		if(dbm.scf.showrev>=5&&dbm.scf.showrev<=7){//����ͼ����²�ѯ����
		  for(i=0;i<n1sum;i++)
		  {
			if(PtInRegion(r_n1[i].hrgn,point.x-dx,point.y-dy))
			{
				seljlh=i;
				return 4;
			}
		   }
		}
		if(dbm.scf.showrev==8||dbm.scf.showrev==9){//����ͼ�����SOE�ط�
		  for(i=0;i<swsum;i++)
		  {
			if(PtInRegion(r_sw[i].hrgn,point.x-dx,point.y-dy))
			{
				seljlh=i;
				return 4;
			}
		   }
		}

		//��ͼ
		if(dbm.scf.showrev==10){//����ͼ
		  for(i=pesum-1;i>=0;i--){
			if(PtInRegion(r_pe[i].hrgn,point.x-dx,point.y-dy)){
				seljlh=i;
				seltype=13;
				return 4;
			}
		   }
		}
		if(dbm.scf.showrev==11){//����ͼ
		  for(i=spesum-1;i>=0;i--){
			if(PtInRegion(r_spe[i].hrgn,point.x-dx,point.y-dy)){
				seljlh=i;
				seltype=15;
				return 4;
			}
		   }
		}

	    if(dbm.scf.lmd>0){//����ͼ����²�ѯ������
		   for(i=0;i<sesum;i++)
		   {
			if(PtInRegion(r_sen[i].hrgn,point.x-dx,point.y-dy))
			{
				seljlh=i;
				return 4;
			}
		   }
		}
	}
	if(cursor>=4&&cursor<=5) return 0;
	return rcursor;
}



void ScadaWin::CheckPopTips_WD()
{
	
}

//3D��������֤�Ƿ񵯳���Ϣ��
void ScadaWin::CheckPopTips()
{
	int i,j;
	N_FLOW *flw;
	double a,b,c,d,vmax,v1,v2,v3,v4;
	CRect rt;
	char sstr[256];

	if(dbm.curopzt==3) return;
	if(oldcur==cursor&&oldjlh==seljlh) return;
	oldcur=cursor;
	oldjlh=seljlh;
	if(cursor!=4)
	{
		twin.ShowWindow(SW_HIDE);
		return;
	}
	sstr[0]=0;
	i=seljlh;

	if(dbm.lookdown==1) //���ӵ����
	{
		switch(dbm.scf.showrev)
		{
		case 1:   //������й�����
			if(i<0||i>=rvsum) return;
			a=r_rv[i].elg->vr.value[0];
			b=r_rv[i].elg->vr.value[2];
			c=r_rv[i].elg->vr.value[3];
			d=b-a-c;
			d=d<0  ? 0:d;
			sprintf(sstr,"%s \n����:%2.0fMW ����:%2.0fMW \n����:%2.0fMW ������:%2.0fMW",r_rv[i].elg->dev_name,a,d,c,b);
			break;
		case 2:   //������޹�����
			if(i<0||i>=rvsum) return;
			switch(r_rv[i].elg->subtype)
			{
			case 1: //�����
				sprintf(sstr,"%s \n�޹�:%2.2fMVar",r_rv[i].elg->dev_name,r_rv[i].elg->vr.value[1]);
				break;
			case 4: //������
				sprintf(sstr,"%s \n�޹�:%2.2fMVar ����:%2.2fMVar",r_rv[i].elg->dev_name,r_rv[i].elg->vr.value[0],
				r_rv[i].elg->vr.value[2]-r_rv[i].elg->vr.value[0]);
				break;
			}
			break;
		case 3:   //��ѹ������
			if(i<0||i>=trsum) return;
			if(r_tr[i].subtype==7){
				a=r_tr[i].elg->vr.value[3];
				b=r_tr[i].elg->vr.value[1];

			}else{
				a=r_tr[i].elg->vr.value[5];
				b=r_tr[i].elg->vr.value[3];
			}
			if(a>0)
			{
				sprintf(sstr,"%s \n����:%2.2fMVA ������:%2.2fMVA ����ʱ��:%2.0f��",
					r_tr[i].elg->dev_name,r_tr[i].elg->Ps,b,a);
			}else{
				sprintf(sstr,"%s \n����:%2.2fMVA ������:%2.2fMVA",r_tr[i].elg->dev_name,
					r_tr[i].elg->Ps,b);
			}
			break;
		case 4:
			if(i<0||i>=trsum) return;
			if(r_tr[i].subtype==7){
				a=r_tr[i].elg->vr.value[4];
				b=r_tr[i].elg->vr.value[5];
			}else{
				a=r_tr[i].elg->vr.value[6];
				b=r_tr[i].elg->vr.value[7];
			}
			sprintf(sstr,"%s \n�¶�:%2.2f�� \n�������¶�:%2.2f��",r_tr[i].elg->dev_name,a,b);
			break;
		case 5:case 6:case 7: //n-1����
			if(i<0||i>=n1sum) return;
			sprintf(sstr,"%s\n��Ϊָ��:%2.6f",r_n1[i].name,r_n1[i].vn1);
			break;
		case 8: //SOE����
			if(i<0||i>=swsum) return;
			GetSoeStr(sstr,r_sw[i].soe,r_sw[i].soesum,r_sw[i].order,r_sw[i].elg->dev_name);
			break;
		case 9: //��·����
			strcpy(sstr,"��·������Ϣδ��");
			break;
		case 10:
			if(i<0||i>=pesum) return;
			a=r_pe[i].pie->pcur;
			b=r_pe[i].pie->maxv;
			if(r_pe[i].pie->maxv==0) return;
			c=(a/b)*100;
			c=c<0 ? -c:c;
			switch(r_pe[i].pie->type)
			{
			case 0:
				sprintf(sstr,"%s����:%2.2fMW   ���رȣ�%2.2f��",r_pe[i].pie->name,a,c);
				break;
			case 1:
				sprintf(sstr,"%s�õ�:%2.2fMW   Ͷ���:%2.2f��\n��ѹ�������ܼ�:%2.2fMW",r_pe[i].pie->name,a,c,b);
				break;
			case 2:
				sprintf(sstr,"%s����:%2.2fMW   ���ر�:%2.2f��\n����������ֵ=%2.2fMW",r_pe[i].pie->name,a,c,b);
				break;
			}
			break;
		case 11: //ϵͳ��ͼ
			if(i<0||i>=spesum) return;
			switch(r_spe[i].pie->type)
			{
			case 0:
				sprintf(sstr,"��װ��:%2.2fMW  �ܷ���:%2.2fMW\n����ת����:%2.0fMW  ͣ������:%2.2fMW",
				r_spe[i].pie->val.GenMax,r_spe[i].pie->val.GenP,r_spe[i].pie->val.UpRes,r_spe[i].pie->val.StopP);
				break;
			case 1:
				sprintf(sstr,"ȫ����Ƹ���:%2.2fMW  ȫ������:%2.2fMW",r_spe[i].pie->val.LoadMax,r_spe[i].pie->val.LoadP);
				break;
			}

		}
		if(dbm.scf.lmd==1)	//������
		{ 
			if(i<0||i>=sesum) return;
			j=r_sen[i].rtype;
			switch(r_sen[i].elg->subtype)
			{
			case 1: //�����
				if(sentype==0) sprintf(sstr,"%s ������:%2.4fMVA/MW ",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				else sprintf(sstr,"%s ������:%2.4fkV/MW",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				break;
			case 3: //����
				if(sentype==0) sprintf(sstr,"%s ������:%2.4fMVA/MW",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				else sprintf(sstr,"%s ������:%2.4fkV/MW",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				break;
			case 4: //����
				if(sentype==0)  sprintf(sstr,"%s ������:%2.4fMVA/MVar",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				else sprintf(sstr,"%s ������:%2.4fkV/MVar",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				break;
			case 7: //2�Ʊ�
				if(sentype==0)  sprintf(sstr,"%s ������:%2.4fMVA/kV",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				else sprintf(sstr,"%s ������:%2.4fkV/kV",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				break;
			case 8: //3�Ʊ�
				if(sentype==0)  sprintf(sstr,"%s ������:%2.4fMVA/KV ",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				else sprintf(sstr,"%s ������:%2.4fkV/kV",r_sen[i].elg->dev_name,r_sen[i].senvalue);
				break;
			}
		}
	}
	if(dbm.lookdown==0&&dbm.curopzt==1&&seltype==254) //ƽ������
	{
	   if(i<0||i>=dmsum) return;
	   switch(dbm.scf.ftype)
	   {
	   case 0:case 1:case 2:case 3:
			sprintf(sstr,"�����й�:%2.2fMW  \n��������:%2.2fMVA",dms[i].Pcur,dms[i].Pmax);
			break;
	   case 4:
			sprintf(sstr,"���泱��:%2.2fA  \n��������:%2.2fA",dms[i].Icur,dms[i].Imax);
			break;
	   }
	}

	if(dbm.lookdown==0&&seltype==3) //��վ
	{
		if (selsubtype == 100)
		{
			if(i<0||i>=stsum) return;
			sprintf(sstr, "����:%s \n%s", r_st[i].elg->dev_name, PhraseType(r_st[i].elg->vr.alarmband, 1));//, r_st[i].elg->vr);
		}
	}

	if(dbm.lookdown==0&&seltype==2) //���������豸�����
	{
		switch(selsubtype)
		{
		case 33: //ĸ��
			if(i<0||i>=bssum) return;
			if(bShowProcessData == false)
				sprintf(sstr,"ĸ��:%s ��ѹ:%2.2fkV\n����:%2.2fkV ����:%2.2fkV",r_bs[i].bus->dev_name,r_bs[i].bus->vr.value[7],r_bs[i].bus->vr.value[3],r_bs[i].bus->vr.value[4]);
			else
				sprintf(sstr,"ĸ��:%s\n��ѹ:%2.2fkV ���:%2.2f\nSe��ѹ:%2.2fkV Se���:%2.2f\nOpf��ѹ:%2.2fkV Opf���:%2.2f\n%s",
				r_bs[i].bus->dev_name,
				r_bs[i].bus->vr.value[7],r_bs[i].bus->vr.value[11],
				r_bs[i].bus->vr.value[12],r_bs[i].bus->vr.value[13],
				r_bs[i].bus->vr.value[14],r_bs[i].bus->vr.value[15],
				PhraseType(r_bs[i].bus->vr.alarmband, 2));
			
			break;
		case 34: //��·
			if(i<0||i>=fwsum) return;
			flw=(N_FLOW*)r_fw[i].flw;
			if(dbm.scf.ftype<4)
			{
				b=flw->ps;
				c=flw->vr.value[4];
			}else{
				b=flw->vr.value[7];
				c=flw->vr.value[6];
			}
			if(c!=0) a=b*100/c;
			else a=0;
			v1=flw->vr.value[0];
			v2=flw->vr.value[1];
			v3=flw->vr.value[7];
			v4=flw->vr.value[4];
			v1=v1<0 ? -v1:v1;
			v2=v2<0 ? -v2:v2;
			v3=v3<0 ? -v3:v3;
			v4=v4<0 ? -v4:v4;
			if(bShowProcessData == false)
				sprintf(sstr,"�����:%s \n�й�:%2.2fMW,�޹�:%2.2fMVar \n���ڹ���:%2.2fMVA ����:%2.2fMVA  %2.2f��",flw->dev_name,
					v1,v2,flw->ps,v4,a);
			else
				sprintf(sstr,"�����:%s \n�й�:%2.2fMW,�޹�:%2.2fMVar \nSe�й�:%2.2fMW,Se�޹�:%2.2fMVar \nOpf�й�:%2.2fMW,Opf�޹�:%2.2fMVar",flw->dev_name,
					flw->vr.value[0], flw->vr.value[1],
					flw->vr.value[5], flw->vr.value[6],
					flw->vr.value[11], flw->vr.value[12]);
			break;
		case 35: //��·
			if(i<0||i>=fwsum) return;
			flw=(N_FLOW*)r_fw[i].flw;
			if(dbm.scf.ftype<4)
			{
				b=flw->ps;
				c=flw->vr.value[4];
			}else{
				b=flw->vr.value[7];
				c=flw->vr.value[6];
			}
			if(c!=0) a=b*100/c;
			else a=0;
			v1=flw->vr.value[0];
			v2=flw->vr.value[1];
			v3=flw->vr.value[7];
			v4=flw->vr.value[4];
			v1=v1<0 ? -v1:v1;
			v2=v2<0 ? -v2:v2;
			v3=v3<0 ? -v3:v3;
			v4=v4<0 ? -v4:v4;
			sprintf(sstr,"ֱ����:%s \n�й�:%2.2fMW, ����:%2.2fMVA  %2.2f��",flw->dev_name,v1,v4,a);
			break;
		case 1: //�����
			if(i<0||i>=stsum) return;
			if(bShowProcessData == false)
				sprintf(sstr,"�����:%s \n%2.2fMW  %2.2fMVar",r_st[i].elg->dev_name,r_st[i].elg->vr.value[0],r_st[i].elg->vr.value[1]);
			else
				sprintf(sstr,"�����:%s \n�й�:%2.2fMW  �޹�:%2.2fMVar\nSe�й�:%2.2fMW  Se�޹�:%2.2fMVar\nOpf�й�:%2.2fMW  Opf�޹�:%2.2fMVar",
				r_st[i].elg->dev_name,r_st[i].elg->vr.value[0],r_st[i].elg->vr.value[1],
				r_st[i].elg->vr.value[5],r_st[i].elg->vr.value[6],
				r_st[i].elg->vr.value[7],r_st[i].elg->vr.value[8]);
			break;
		case 2:
			if(i<0||i>=stsum) return;
			sprintf(sstr,"����:%s",r_st[i].elg->dev_name);
			break;
		case 3: //����
			if(i<0||i>=stsum) return;
			if(bShowProcessData == false)
				sprintf(sstr,"����:%s \n%2.2fMW,%2.2fMVar",r_st[i].elg->dev_name,r_st[i].elg->vr.value[0],r_st[i].elg->vr.value[1]);
			else
				sprintf(sstr,"����:%s \n%�й�:2.2fMW,%�޹�:2.2fMVar\n%Se�й�:2.2fMW,%Se�޹�:2.2fMVar\n%Opf�й�:2.2fMW,%Opf�޹�:2.2fMVar\n",
				r_st[i].elg->dev_name,r_st[i].elg->vr.value[0],r_st[i].elg->vr.value[1],
				r_st[i].elg->vr.value[4],r_st[i].elg->vr.value[5],
				r_st[i].elg->vr.value[6],r_st[i].elg->vr.value[7]
				);
			break;
		case 4: //����
			if(i<0||i>=stsum) return;
			if(bShowProcessData==false)
				sprintf(sstr,"����:%s \n%2.2fMVar",r_st[i].elg->dev_name,r_st[i].elg->vr.value[0]);
			else
				sprintf(sstr,"����:%s \n�޹�:%2.2fMVar\nSe�޹�:%2.2fMVar\nOpf�޹�:%2.2fMVar\n%s",
				r_st[i].elg->dev_name,r_st[i].elg->vr.value[0],r_st[i].elg->vr.value[3],r_st[i].elg->vr.value[4],
				PhraseType(r_st[i].elg->vr.alarmband, 4));
			break;
		case 5: //�翹
			if(i<0||i>=stsum) return;
			sprintf(sstr,"�翹:%s \n%2.2f",r_st[i].elg->dev_name,r_st[i].elg->vr.value[0]);
			break;
		case 6: //�ӵ�
			if(i<0||i>=stsum) return;
			sprintf(sstr,"�ӵ�:%s",r_st[i].elg->dev_name);
			break;
		case 7:case 8: //��ѹ��wd
			if(i<0||i>=stsum) return;
			if(selsubtype==7) vmax=r_st[i].elg->vr.value[1];
			else vmax=r_st[i].elg->vr.value[3];
			if(bShowProcessData==false)//11111
			{
				if(selsubtype==7)//�������ѹ��
					sprintf(sstr,"��ѹ��:%s \n%2.2fMVA ����:%2.2fMVA\n��ѹ���й�%2.2f ��ѹ���޹�%2.2f\n��ѹ���й�%2.2f ��ѹ���޹�%2.2f",
					r_st[i].elg->dev_name,r_st[i].elg->Ps,vmax,
					r_st[i].elg->vr.value[2],r_st[i].elg->vr.value[6],
					r_st[i].elg->vr.value[7],r_st[i].elg->vr.value[8]);
				else
					sprintf(sstr,"��ѹ��:%s \n%2.2fMVA ����:%2.2fMVA\n��ѹ���й�%2.2f ��ѹ���޹�%2.2f\n��ѹ���й�%2.2f ��ѹ���޹�%2.2f\n��ѹ���й�%2.2f ��ѹ���޹�%2.2f",
					r_st[i].elg->dev_name,r_st[i].elg->Ps,vmax,
					r_st[i].elg->vr.value[4],r_st[i].elg->vr.value[8],
					r_st[i].elg->vr.value[9],r_st[i].elg->vr.value[10],
					r_st[i].elg->vr.value[11],r_st[i].elg->vr.value[12]);
			}
			else
			{
				if(selsubtype==7)//�������ѹ��
					sprintf(sstr,"��ѹ��:%s \n%2.2fMVA ����:%2.2fMVA \n�й�%2.2f,�޹�%2.2f \nSe�й�%2.2f,Se�޹�%2.2f \n Opf�й�%2.2f,Opf�޹�%2.2f\n%s",
					r_st[i].elg->dev_name,r_st[i].elg->Ps,vmax,
					r_st[i].elg->vr.value[2],r_st[i].elg->vr.value[6],
					r_st[i].elg->vr.value[11],r_st[i].elg->vr.value[12],
					r_st[i].elg->vr.value[16],r_st[i].elg->vr.value[17],
					PhraseType(r_st[i].elg->vr.alarmband, 3));
				else
					sprintf(sstr,"��ѹ��:%s \n%2.2fMVA ����:%2.2fMVA \n�й�%2.2f,�޹�%2.2f \nSe�й�%2.2f,Se�޹�%2.2f \n Opf�й�%2.2f,Opf�޹�%2.2f\n%s",
					r_st[i].elg->dev_name,r_st[i].elg->Ps,vmax,
					r_st[i].elg->vr.value[4],r_st[i].elg->vr.value[8],
					r_st[i].elg->vr.value[16],r_st[i].elg->vr.value[19],
					r_st[i].elg->vr.value[24],r_st[i].elg->vr.value[27],
					PhraseType(r_st[i].elg->vr.alarmband, 3));

			}
			
			break;
		case 9:  //��̬�޹�����װ��
			if(i<0||i>=stsum) return;
			sprintf(sstr,"SVC:%s \n%2.2",r_st[i].elg->dev_name,r_st[i].elg->vr.value[0]);
			break;
		case 10: //������
			if(i<0||i>=stsum) return;
			sprintf(sstr,"������:%s",r_st[i].elg->dev_name);
			break;
		default:
			if(i<0||i>=stsum) return;
			sprintf(sstr,"%s",r_st[i].elg->dev_name);
		}
	}
	if(dbm.lookdown==0&&seltype==13)
	{
		if(i<0||i>=pesum) return;
		a=r_pe[i].pie->pcur;
		b=r_pe[i].pie->maxv;
		if(r_pe[i].pie->maxv==0) return;
		c=(a/b)*100;
		c=c<0 ? -c:c;
		switch(r_pe[i].pie->type)
		{
		case 0:
			sprintf(sstr,"%s����:%2.2fMW   ���رȣ�%2.2f��",r_pe[i].pie->name,a,c);
			break;
		case 1:
			sprintf(sstr,"%s�õ�:%2.2fMW   Ͷ���:%2.2f��\n��ѹ�������ܼ�:%2.2fMW",r_pe[i].pie->name,a,c,b);
			break;
		case 2:
			sprintf(sstr,"%s����:%2.2fMW   ���ر�:%2.2f��\n����������ֵ=%2.2fMW",r_pe[i].pie->name,a,c,b);
			break;
		}
	}
	if(dbm.lookdown==0&&seltype==14)
	{
		if(i<0||i>=basum) return;
		float fMax=r_ba[i].bar->max;
		float fCur=r_ba[i].bar->rval.curval;
		if(r_ba[i].bar->min<0 && fCur<0)
			fMax=r_ba[i].bar->min;
		if(fMax==0) return;
		sprintf(sstr,"%s ��ֵ��%.2f~%.2f\n��ǰֵ��%.2f  �����ʣ�%.2f��",r_ba[i].bar->dsrc.name,r_ba[i].bar->min,r_ba[i].bar->max,fCur,fabs(100*fCur/fMax));
	}
	if(dbm.lookdown==0&&seltype==15)
	{
		if(i<0||i>=spesum) return;
		switch(r_spe[i].pie->type)
		{
			case 0:
				sprintf(sstr,"��װ��:%2.2fMW  �ܷ���:%2.2fMW\n����ת����:%2.0fMW  ͣ������:%2.2fMW",
				r_spe[i].pie->val.GenMax,r_spe[i].pie->val.GenP,r_spe[i].pie->val.UpRes,r_spe[i].pie->val.StopP);
				break;
			case 1:
				sprintf(sstr,"ȫ����Ƹ���:%2.2fMW  ȫ������:%2.2fMW",r_spe[i].pie->val.LoadMax,r_spe[i].pie->val.LoadP);
				break;
		}

	}
	if(strlen(sstr)==0) return;//����ַ���Ϊ��
	twin.mpt=tpint;
	twin.mpt.Offset(6,-4);
	twin.SetText(sstr);
	twin.ShowWindow(SW_SHOW);
	cobj.fwin->m_wndStatusBar.SetWindowText(sstr);
}


CString ScadaWin::PhraseType(BYTE bType, BYTE bSB)
{
	CString szTmp;
	switch(bSB)
	{
	case 1://��վ
		{
			if((bType&RUNDATA_STA_OldVolOut)==RUNDATA_STA_OldVolOut)
			{
				if((bType&RUNDATA_STA_VolOut)==RUNDATA_STA_VolOut)
					szTmp="\n��ѹԽ������";
				else
					szTmp="\n��ѹԽ����ʧ";
			}
			else if((bType&RUNDATA_STA_VolOut)==RUNDATA_STA_VolOut)
				szTmp="\n������ѹԽ��";
	
			if((bType&RUNDATA_STA_OldCosOut)==RUNDATA_STA_OldCosOut)
			{
				if((bType&RUNDATA_STA_CosOut)==RUNDATA_STA_CosOut)
					szTmp+="\n�޹�Խ������";
				else
					szTmp+="\n�޹�Խ����ʧ";
			}
			else if((bType&RUNDATA_STA_CosOut)==RUNDATA_STA_CosOut)
				szTmp+="\n�����޹�Խ��";

			if((bType&RUNDATA_STA_CtrlCmd)==RUNDATA_STA_CtrlCmd)
				szTmp+="\n���ɿ���ָ��";
		}break;
	case 2://ĸ��
		{
			switch(bType)
			{
			case 1:szTmp="\n��ѹԽ����ʧ";break;
			case 2:szTmp="\n������ѹԽ��";break;
			case 3:szTmp="\n��ѹԽ������";break;
			}
		}break;
	case 3://��ѹ��
		{
			if((bType&RUNDATA_TFM_OldCosOut)==RUNDATA_TFM_OldCosOut)
			{
				if((bType&RUNDATA_TFM_CosOut)==RUNDATA_TFM_CosOut)
					szTmp+="\n�޹�Խ������";
				else
					szTmp+="\n�޹�Խ����ʧ";
			}
			else if((bType&RUNDATA_TFM_CosOut)==RUNDATA_TFM_CosOut)
				szTmp+="\n�����޹�Խ��";
			
			if((bType&CTRLDATA_TFM_TfmDn)==CTRLDATA_TFM_TfmDn)
				szTmp+="\n���ɽ�������ָ��";
			if((bType&CTRLDATA_TFM_TfmUp)==CTRLDATA_TFM_TfmUp)
				szTmp+="\n������������ָ��";
			
		}break;
	case 4://����
		{
			if((bType&CTRLDATA_SHUNT_ShuntClose)==CTRLDATA_SHUNT_ShuntClose)
				szTmp+="\n�����˳�����ָ��";
			if((bType&CTRLDATA_SHUNT_ShuntOpen)==CTRLDATA_SHUNT_ShuntOpen)
				szTmp+="\n����Ͷ�����ָ��";
			
		}break;
	}

	return szTmp;
}


//�ͷ���Դ
void ScadaWin::FreeMem() //�ͷ��ڴ�
{
	int i;
	if(clsum!=0) delete []r_cl;
	if(stsum!=0) delete []r_st;
	if(bssum!=0) delete []r_bs;
	if(basum!=0) delete []r_ba;
	if(ansum!=0) delete []r_an;
	if(dtsum!=0) delete []r_da;
	if(tmsum!=0) delete []r_tm;
	if(scsum!=0) delete []r_sc;
	if(phsum!=0) delete []r_ph;
	if(atsum!=0) delete []r_at;
	if(ybsum!=0) delete []r_yb;
	if(ppsum!=0) delete []r_ppie;
	if(mtsum!=0) delete []r_mt;
	
	r_mt=NULL;
	
	r_cl=NULL;
	r_st=NULL;
	r_bs=NULL;
	r_ba=NULL;
	r_an=NULL;
	r_da=NULL;
	r_tm=NULL;
	
	r_sc=NULL;
	r_ph=NULL;
	r_at=NULL;
	r_yb=NULL;
	r_ppie=NULL;
	
	
	clsum=0;
	stsum=0;
	bssum=0;
	basum=0;
	ansum=0;
	dtsum=0;
	tmsum=0;
	scsum=0;
	phsum=0;
	atsum=0;
	ybsum=0;
	ppsum=0;
	mtsum=0;
	

	//�ͷŶ���
	for(i=0;i<amsum;i++)	r_am[i].gfaml.FreeMem();
	if(amsum!=0) delete []r_am;
	r_am=NULL;
	amsum=0;
	for(i=0;i<n1sum;i++)
	{
		if(r_n1[i].hrgn!=NULL)		DeleteObject(r_n1[i].hrgn);
	}
	if(n1sum!=0) free(r_n1);
	r_n1=NULL;
	n1sum=0;
	//�ͷ������ؼ�
	for(i=0;i<sfsum;i++){
		
	   if(r_sf[i].stl->hwnd!=NULL&&r_sf[i].stl->hinst!=NULL&&
		   r_sf[i].stl->DfClose!=NULL)
	   {
			 ::SendMessage(r_sf[i].stl->hwnd,WM_CLOSE,0,0);
			 r_sf[i].stl->DfClose(r_sf[i].stl->rc);
			 r_sf[i].stl->hwnd=0;
			 r_sf[i].stl->rc=0;
		 }
	   if(r_sf[i].stl->hinst!=NULL){
		    if(r_sf[i].stl->hmenu!=NULL) DestroyMenu(r_sf[i].stl->hmenu);
 			FreeLibrary(r_sf[i].stl->hinst);
			r_sf[i].stl->hinst=0;
			r_sf[i].stl->hmenu=NULL;
	   }
	};

	if(sfsum!=0) delete []r_sf;
	r_sf=NULL;
	sfsum=0;

	//�ͷ�flash�ؼ�
	for(i=0;i<fssum;i++)	r_fsh[i].fshw.DestroyWindow();
	if(fssum>0) delete []r_fsh;
	r_fsh=NULL;
	fssum=0;

	//�ͷų���
	for(i=0;i<fwsum;i++)
	{
		if(r_fw[i].hrgn!=NULL)		DeleteObject(r_fw[i].hrgn);
		if(r_fw[i].flw->fpt!=NULL)	delete r_fw[i].flw->fpt;
	}

	if(fwsum!=0) delete []r_fw;
	r_fw=NULL;
	fwsum=0;

	//�ͷ�����
	for(i=0;i<znsum;i++)
	{
		if(r_zn[i].hrgn!=NULL)		DeleteObject(r_zn[i].hrgn);
	}
	if(znsum!=0) delete []r_zn;
	r_zn=NULL;
	znsum=0;


	//�ͷ�ˮ��
	for(i=0;i<rssum;i++)
	{
		if(r_rs[i].hrgn!=NULL)		DeleteObject(r_rs[i].hrgn);
	}
	if(rssum!=0) delete []r_rs;
	r_rs=NULL;
	rssum=0;

	//�ͷ�������
	for(i=0;i<sesum;i++) if(r_sen[i].hrgn!=NULL) DeleteObject(r_sen[i].hrgn);
	if(sesum!=0) delete []r_sen;
	r_sen=NULL;
	sesum=0;

	//�ͷ��豸3DBAR����,���������,������,����,2�Ʊ�,3�Ʊ�
	for(i=0;i<rvsum;i++) if(r_rv[i].hrgn!=NULL) DeleteObject(r_rv[i].hrgn);
	if(rvsum!=0) delete []r_rv;
	rvsum=0;
	//�ͷű�ѹ��������ض���
	for(i=0;i<trsum;i++) if(r_tr[i].hrgn!=NULL) DeleteObject(r_tr[i].hrgn);
	if(trsum!=0) delete []r_tr;
	trsum=0;  

	//�ͷſ��ض���
	for(i=0;i<swsum;i++) if(r_sw[i].hrgn!=NULL) DeleteObject(r_sw[i].hrgn);
	if(swsum!=0) delete []r_sw;
	r_sw=NULL;
	swsum=0; 

	//�ͷű�ͼ
	for(i=0;i<pesum;i++) if(r_pe[i].hrgn!=NULL) DeleteObject(r_pe[i].hrgn);
	if(pesum!=0) delete []r_pe;
	pesum=0; 
	//�ͷű�ͼ
	for(i=0;i<spesum;i++) if(r_spe[i].hrgn!=NULL) DeleteObject(r_spe[i].hrgn);
	if(spesum!=0) delete []r_spe;
	spesum=0; 
}

//�ӿ�����ȡ����
void ScadaWin::GetObjFromDbm()
{
	CRect rt;
	char fnm[256];
	N_layer *clay;
	R_FLW rfw;
	int i,j, canl,crat,csta,cgif,ccom,csft,cpsh,cdat,ctim,ctrd,cstx,cyk;
	int cflw,cspl,cact,cba, cpie,cls, cbs,cyb,cfsh,cppe,cdbx,crs,czn,cmt,spe;

	canl=0;	crat=0;	csta=0;	cgif=0;	ccom=0;	csft=0;
	cpsh=0;	cdat=0;	ctim=0;	ctrd=0;	cstx=0; cyk=0;
	cflw=0; cspl=0; cact=0; cba=0;  cpie=0; cls=0;
	cbs=0;  cyb=0;  cfsh=0; cppe=0; cdbx=0; crs=0;czn=0;
	rfw.ele=1;cmt=0;spe=0;
	//���������ؼ��˵�Ϊ0/////////////////////////
	dbm.cmsum=0;					//��ǰӦ������
	dbm.popsum=0;					//�����˵�����
	//////////////////////////////////////////////
	for(i=0;i<dbm.page.laysum;i++)
	{
	  clay=&dbm.page.layer[i];
	  for(j=0;j<clay->objnum;j++)
	  {
		switch(clay->obj[j].attr.type)
		{
		case 64:
			r_an[canl].rt=clay->obj[j].ort;
			r_an[canl].bs=&clay->obj[j];
			r_an[canl].anl=(N_ANL*)clay->obj[j].buf;
			canl++;
			break;
		case 65:
			r_rs[crs].bs=&clay->obj[j];
			r_rs[crs].res=(N_RESERVOIR*)clay->obj[j].buf;
			r_rs[crs].hrgn=NULL;
			crs++;
			break;
		case 66:
			r_st[csta].rt=clay->obj[j].ort;
			r_st[csta].bs=&clay->obj[j];
			r_st[csta].elg=(N_ELEGRPA*)clay->obj[j].buf; 
			csta++;
			break;
		case 67:
			r_yb[cyb].bs=&clay->obj[j];
			r_yb[cyb].mtr=(N_ELEGRPYB *)r_yb[cyb].bs->buf;
			r_yb[cyb].rt=r_yb[cyb].bs->ort;
			memset(r_yb[cyb].recno,0,4*6);
			cyb++;
			break;
		case 68:
			r_spe[spe].bs=&clay->obj[j];
			r_spe[spe].pie=(N_SYSPIE *)r_spe[spe].bs->buf;
			r_spe[spe].rt=	r_spe[spe].bs->ort;
			r_spe[spe].hrgn=NULL;
			r_spe[spe].opt=r_spe[spe].rt.CenterPoint(); //ȡ�е�
			spe++;
			break;
		case 69:
			r_ba[cba].bs=&clay->obj[j];
			r_ba[cba].bar=(N_BAR *)r_ba[cba].bs->buf;
			r_ba[cba].rt=r_ba[cba].bs->ort;
			r_ba[cba].bar->rval.curval=0;
			cba++;
			break;
		case 70:
			r_pe[cpie].bs=&clay->obj[j];
			r_pe[cpie].pie=(N_PIE *)r_pe[cpie].bs->buf;
			r_pe[cpie].rt=	r_pe[cpie].bs->ort;
			r_pe[cpie].hrgn=NULL;
			r_pe[cpie].opt=r_pe[cpie].rt.CenterPoint(); //ȡ�е�
			cpie++;
			break;
		case 71:
			r_da[cdat].bs=&clay->obj[j];
			cdat++;
			break;
		case 72:
			r_tm[ctim].bs=&clay->obj[j];
			ctim++;
			break;
		case 73:
			r_am[cgif].bs=(DObj*)&clay->obj[j];
			r_am[cgif].rt=r_am[cgif].bs->ort;
			r_am[cgif].ngf=(N_GIFAML *)r_am[cgif].bs->buf;
			cobj.SetToLocalFile(r_am[cgif].ngf->fname,fnm);
			r_am[cgif].gfaml.ReadGifFile(fnm);
			r_am[cgif].ngf->gfm=&r_am[cgif].gfaml;
			if(r_am[cgif].ngf->type==4){
				r_am[cgif].zt=1;
				r_am[cgif].enable=1;
			}else {
				r_am[cgif].zt=0;
				r_am[cgif].enable=1;
			}
			cgif++;
			break;
		case 74:
			r_sc[cstx].rt=clay->obj[j].ort;
			r_sc[cstx].bs=(DObj*)&clay->obj[j];
			r_sc[cstx].stx=(N_SRLTEXT*)clay->obj[j].buf;
			if(r_sc[cstx].stx->direct==2||r_sc[cstx].stx->direct==4){
			 ClrStrEnter(r_sc[cstx].stx->text);
			 };
			cstx++;
			break;
		case 75:
			r_ph[cpsh].bs=&clay->obj[j];
			r_ph[cpsh].rt=clay->obj[j].ort;
			r_ph[cpsh].psh=(N_PUSH*)clay->obj[j].buf;
			cpsh++;
			break;
        case 76:
			r_sf[csft].bs=&clay->obj[j];
			r_sf[csft].rt=clay->obj[j].ort;
			r_sf[csft].rt.GetRECT(rt);
			r_sf[csft].sid=clay->obj[j].attr.ID;
			r_sf[csft].cansize=1;
			r_sf[csft].stl=(N_SELFCTL*)clay->obj[j].buf;
			//����ģ��
			r_sf[csft].bs->InitSelfCtl();
			if(r_sf[csft].stl->hinst!=NULL&&r_sf[csft].stl->DfInit!=NULL){ 
				r_sf[csft].stl->rc=r_sf[csft].stl->DfInit(m_hWnd,r_sf[csft].stl->hwnd,
					rt,r_sf[csft].stl->id,r_sf[csft].stl->style,r_sf[csft].stl->lkbuf);
				}
				else r_sf[csft].stl->hwnd=NULL;
			GetSflRunParam(r_sf[csft].swp,r_sf[csft]);
			//׼���˵�			
			if(r_sf[csft].stl->hmenu!=NULL)
				dbm.SetChildMenu(r_sf[csft].stl->hwnd,r_sf[csft].stl->hmenu);
			/////////////////////
			csft++;
			break;
		case 77:
			r_fw[cflw].bs=&clay->obj[j];
			r_fw[cflw].flw=(N_FLOW*)clay->obj[j].buf;
			r_fw[cflw].flw->rf.pjs=0;
			r_fw[cflw].flw->rf.qjs=0;
			r_fw[cflw].hrgn=NULL;
			r_fw[cflw].flw->pv=0;
			r_fw[cflw].flw->qv=0;
			r_fw[cflw].curdot=0;		//��ǰ��¼��
			r_fw[cflw].lfflag=0;		//��Ƶ�𵴱��
			r_fw[cflw].mdot=6;			//ÿ50�������
			cflw++;
			break;
		case 78:
			r_cl[cls].bs=&clay->obj[j];
			r_cl[cls].rt=clay->obj[j].ort;
			r_cl[cls].lin=(N_CONLINE*)clay->obj[j].buf;
			cls++;
			break;
		case 79:
			r_bs[cbs].bs=&clay->obj[j];
			r_bs[cbs].rt=clay->obj[j].ort;
			r_bs[cbs].bus=(N_BUS*)clay->obj[j].buf;
			r_bs[cbs].hrgn=NULL;
			cbs++;
			break;
		case 80:
			clay->obj[j].ort.GetRECT(r_at[cact].rt);
			r_at[cact].oldrt=CDRect(-1000,-100,0,0);
			r_at[cact].currt=CDRect(-1000,-1000,0,0);
			r_at[cact].js=0;
			r_at[cact].act=(N_ACTOBJ*)clay->obj[j].buf;
			GetActPicMsg(cact);
			r_at[cact].curval=0;
			cact++;
			break;
		case 81:
			clay->obj[j].ort.GetRECT(r_fsh[cfsh].rt);
			r_fsh[cfsh].fsh=(N_FLASH*)clay->obj[j].buf;
			r_fsh[cfsh].fshw.Create("",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,130+cfsh);
			cobj.SetToLocalFile(r_fsh[cfsh].fsh->fname,fnm);//�ҵ��ļ�
			r_fsh[cfsh].fshw.SetMovie(fnm);
			if(r_fsh[cfsh].fsh->playmode==1) r_fsh[cfsh].fshw.SetLoop(TRUE);
			cfsh++;
			break;
		case 82:
			r_ppie[cppe].bs=&clay->obj[j];
			r_ppie[cppe].rt=clay->obj[j].ort;
			r_ppie[cppe].ppe=(N_PCTPIE*)clay->obj[j].buf;
			r_ppie[cppe].ppe->maxv=0;
			r_ppie[cppe].ppe->curval=0;
			r_ppie[cppe].ppe->showdl=0;
			cppe++;
			break;
		case 83:
			r_zn[czn].bs=&clay->obj[j];
			r_zn[czn].rt=clay->obj[j].ort;
			r_zn[czn].zon=(N_ZONE*)clay->obj[j].buf;
			r_zn[czn].hrgn=NULL;
			czn++;
			break;
		case 84:
			r_mt[cmt].bs=&clay->obj[j];
			r_mt[cmt].rt=clay->obj[j].ort;
			r_mt[cmt].txt=(N_MTTEXT*)clay->obj[j].buf;
			r_mt[cmt].recno=0;
			r_mt[cmt].txt->lstsum=GetLstSource(r_mt[cmt].txt->text,r_mt[cmt].txt->offset,64);
			cmt++;
			break;
		 };
	   }
	};
}

//��3d����λ�ý��������Ա���ʾ
void ScadaWin::Order3dPos()
{
	CDPoint dpt;
	int i,j;
	RSEN stmp;
	RREV rtmp;
	N1BAR ntmp;
	RSWT  wtmp;
	RPIE  petmp;
	RSPIE sptmp;
	if(dbm.lookdown==0) return;
	switch(dbm.scf.showrev)
	{
	case 1: case 2: //������͵���
		//����λ��
		for(i=0;i<rvsum;i++)
		{
			dpt=r_rv[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_rv[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<rvsum;i++)
		{
			for(j=i+1;j<rvsum;j++)
			{
				if(r_rv[i].deep<r_rv[j].deep)
				{
					rtmp=r_rv[i];
					r_rv[i]=r_rv[j];
					r_rv[j]=rtmp;
				}
			}
		}
		break;
	case 3: case 4: //��ѹ��
		//����λ��
		for(i=0;i<trsum;i++)
		{
			dpt=r_tr[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_tr[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<trsum;i++)
		{
			for(j=i+1;j<trsum;j++)
			{
				if(r_tr[i].deep<r_tr[j].deep)
				{
					rtmp=r_tr[i];
					r_tr[i]=r_tr[j];
					r_tr[j]=rtmp;
				}
			}
		}
		break;
	case 5:case 6:case 7: case 12:
		//����λ��
		for(i=0;i<n1sum;i++)
		{
			dpt=r_n1[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_n1[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<n1sum;i++){
			for(j=i+1;j<n1sum;j++)
			{
				if(r_n1[i].deep<r_n1[j].deep)
				{
					ntmp=r_n1[i];
					r_n1[i]=r_n1[j];
					r_n1[j]=ntmp;
				}
			}
		}
		break;
	case 8:
		//����λ��
		for(i=0;i<swsum;i++)
		{
			dpt=r_sw[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_sw[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<swsum;i++){
			for(j=i+1;j<swsum;j++)
			{
				if(r_sw[i].deep<r_sw[j].deep)
				{
					wtmp=r_sw[i];
					r_sw[i]=r_sw[j];
					r_sw[j]=wtmp;
				}
			}
		}
		break;
	case 10: //�����ͼ
		for(i=0;i<pesum;i++)
		{
			dpt=r_pe[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_pe[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<pesum;i++){
			for(j=i+1;j<pesum;j++){
				if(r_pe[i].deep<r_pe[j].deep){
					petmp=r_pe[i];
					r_pe[i]=r_pe[j];
					r_pe[j]=petmp;
				}
			}
		}
		break;
	case 11: //ϵͳ��ͼ
		for(i=0;i<spesum;i++)
		{
			dpt=r_spe[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_spe[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//���豸����
		for(i=0;i<spesum;i++){
			for(j=i+1;j<spesum;j++){
				if(r_spe[i].deep<r_spe[j].deep){
					sptmp=r_spe[i];
					r_spe[i]=r_spe[j];
					r_spe[j]=sptmp;
				}
			}
		}
		break;

	}
	if(dbm.scf.lmd==1)
	{
	//������λ��
		for(i=0;i<sesum;i++)
		{
			dpt=r_sen[i].opt;
			dpt.ActPtToScr(dbm.curzoom);
			r_sen[i].deep=msr.GetDeep(dpt.x,dpt.y);
		}
		//��������λ������
		for(i=0;i<sesum;i++){
			for(j=i+1;j<sesum;j++){
				if(r_sen[i].deep<r_sen[j].deep)
				{
					stmp=r_sen[i];
					r_sen[i]=r_sen[j];
					r_sen[j]=stmp;
				}
			}
		}
	}
}

//�������
void ScadaWin::AddDmPt()
{
	int i,n,m;
	if(segsum>=10) return;
	n=0;
	for(i=0;i<segsum;i++)
	{
		n+=dmsdot[i];
	}
	m=500-n;
	if(polysum>=m) polysum=m;
	if(polysum<2) return;
	for(i=0;i<polysum;i++) dmpt[n+i]=ptpoly[i];
	dmsdot[segsum]=polysum;
	segsum++;
	polysum=0;
}

//����3D��������
void ScadaWin::Set3DEnv()
{
	msr.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//����3D����
	mbg.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//����3D����
}

//��0ȫ������
void ScadaWin::ResetAllData(int ele)
{
	int i;
	READDEV  ran;
	memset(&ran,0,sizeof(READDEV));
	ran.ele=ele;
	//����·
	for(i=0;i<fwsum;i++) r_fw[i].flw->vr=ran;
	//��ĸ��
	for(i=0;i<bssum;i++) r_bs[i].bus->vr=ran;
	//���豸
	for(i=0;i<stsum;i++) 
	{
		r_st[i].elg->vr=ran;
		r_st[i].elg->Ps=0;
	}
	//ģ����
	for(i=0;i<ansum;i++) r_an[i].anl->vr=ran;
	//�ٷֱ�ͼ
	for(i=0;i<ppsum;i++) r_ppie[i].ppe->curval=0;
}



//�����Ǳ�ֵ
void ScadaWin::SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j)
{
	if(j>7||j<0) return;
	if(yb.umr[j].ptype==1) //ʹ�ö�ȡ�Ĳ���
	{
		yb.umr[j].vmax=data.vmax;
		yb.umr[j].vmin=data.vmin;
		yb.umr[j].val[0]=data.vmin1;
		yb.umr[j].val[1]=data.vmax1;
		yb.umr[j].val[2]=data.vmin2;
		yb.umr[j].val[3]=data.vmax2;
	}
	yb.newval[j]=data.curval;
}

//����N-1����ֵ
void ScadaWin::SetN1Data(int n1type,N1Data *data,int num)
{
	int i,j,k,t;
	for(j=0;j<n1sum;j++){
		r_n1[j].vn1=0;//����0
		r_n1[j].index=0;
	}
	for(i=0;i<num;i++)
	{
		k=data[i].id;
		t=data[i].type;
		for(j=0;j<n1sum;j++)
		{
			if(k==r_n1[j].devid&&t==r_n1[j].type)
			{
				r_n1[j].vn1=data[i].val;
				r_n1[j].index=i+1;
				break;
			}
		}
	}
}


//���ÿ��ض�·��������ֵ
void ScadaWin::SetSwtSccData(DLDL &sc)
{
	int i;

	for(i=0;i<swsum;i++)
	{
		if((DWORD)r_sw[i].elg->did==sc.SwtNU)
		{
			r_sw[i].dl=sc;
			break;
		}
	}
}

//������·��·��������ֵ
void ScadaWin::SetLineSccData(DLDL &sc)
{
	int i;

	for(i=0;i<ppsum;i++)
	{
		if((DWORD)r_ppie[i].ppe->did==sc.LineNU)
		{
			r_ppie[i].ppe->showdl=1;
			break;
		}
	}
}

//���һ��N-1�������ݶ���
void ScadaWin::AddN1Data(N1BAR &nbar)
{
	int n;
	n=n1sum;
	if(n==0)
	{
	  r_n1=(N1BAR*)malloc(sizeof(N1BAR));
	};
	if(n>0)
	{
	  r_n1=(N1BAR*)realloc(r_n1,sizeof(N1BAR)*(n+1));
	};
	r_n1[n]=nbar;
	n1sum++;
}



//�ռ�N1�豸
void ScadaWin::CollectN1Device()
{
	int i,j;
	N1BAR nbar;
	if(n1sum>0) return;//�����ռ�
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type!=1)  continue;
		j=r_st[i].elg->subtype;
		switch(j)
		{
		  case 1: 
			nbar.type=0;
			nbar.devid=r_st[i].elg->did;
			strcpy(nbar.name,r_st[i].elg->dev_name);
			nbar.opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
			nbar.hrgn=NULL;
			nbar.vn1=0;
			AddN1Data(nbar);
			break;
		  case 3:
			nbar.type=1;
			nbar.devid=r_st[i].elg->did;
			strcpy(nbar.name,r_st[i].elg->dev_name);
			nbar.opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
			nbar.hrgn=NULL;
			nbar.vn1=0;
			AddN1Data(nbar);
			break;
		  case 7: case 8:
			nbar.devid=r_st[i].elg->did;
			strcpy(nbar.name,r_st[i].elg->dev_name);
			nbar.type=2;
		    nbar.opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
		    nbar.hrgn=NULL;
		    nbar.vn1=0;
		    AddN1Data(nbar);
		    break;
		}
	}
	//�ӱ�ͼȡ��·
	for(i=0;i<ppsum;i++)
	{
		nbar.devid=r_ppie[i].ppe->did;
		strcpy(nbar.name,r_ppie[i].ppe->dev_name);
		nbar.type=3;
		nbar.hrgn=NULL;
		nbar.vn1=0;
		nbar.opt=r_ppie[i].rt.CenterPoint();
		AddN1Data(nbar);
	}
}


//������豸����
void ScadaWin::GetDevSum()
{
	int i;
	n_ge=0;		//���������
	n_tr=0;		//��ѹ������
	n_sh=0;		//����������
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type!=1) continue;
		switch(r_st[i].elg->subtype)
		{
		case 1: 
			n_ge++;
			break;
		case 4:
			n_sh++;
			break;
		case 7:case 8:
			n_tr++;
			break;
		}
	}
	n_se=bssum;
}

//������һ�ε�λ��
void ScadaWin::SetFirstPosition()
{
	double a1,a2;
	a1=(double)wx/(double)wy;
	a2=(double)dbm.page.head.width/(double)dbm.page.head.height;
	if(a1>a2)
	{
		dbm.curzoom=(double)wy/(double)dbm.page.head.height;
	}else{
		dbm.curzoom=(double)wx/(double)dbm.page.head.width;
	}
	ComputMaxXY();
	dx=xmax/2;
	dy=ymax/2;
	//���������ؼ��Ĵ��ڴ�С
	ChangeAllSft();
	if(cobj.nwin!=NULL) cobj.nwin->WinSizeChange(wx,wy);
	CreateAllrgn();
}



//���㰴ָ����Сʱ�ķŴ�������ز���
bool ScadaWin::ComputShowByRt()
{
	double w1,h1;
	double a1,a2;
	if(dbm.page.head.showbyrt==0) return false;
	w1=dbm.page.head.x2-dbm.page.head.x1;
	h1=dbm.page.head.y2-dbm.page.head.y1;
	if(w1<=0||h1<=0) return false;
	a1=(double)wx/(double)wy;
	a2=w1/h1;
	if(a1>a2)
	{
		dbm.curzoom=(double)wy/h1;
	}else{
		dbm.curzoom=(double)wx/w1;
	}
	ComputMaxXY();
	dx=(int)(-dbm.page.head.x1*dbm.curzoom);
	dy=(int)(-dbm.page.head.y1*dbm.curzoom);
	ComputZCenter();
	ChangeAllSft();
	if(cobj.nwin!=NULL) cobj.nwin->WinSizeChange(wx,wy);
	CreateAllrgn();
	return true;
}


char *ftle[]={"������й����������ü���",
			  "�޹����������ü���",
			  "��ѹ��������",
			  "��·��������",
			  "�ڵ��ѹ������",
			  "������������",
			  "��Ƶ�𵴼���",
			  "��ѹ���¶ȼ���",
			  "���ڽڵ��ѹԽ�޳̶ȵ�Ԥ���¹�����",
			  "����֧·����Խ�޳̶ȵ�Ԥ���¹�����",
			  "�ۺϻ��ڽڵ��ѹ��֧·����Խ�޳̶ȵ�Ԥ���¹�����"
 };
//��ʾ���ܱ���
void ScadaWin::ShowFuntTitle(CDIB&mdc,CRect rt,int type)
{
	SIZE sz;
	CRect rt1;
	LOGFONT font;
	if(dbm.page.head.type==0) return;
	font=cobj.font1;
	font.lfHeight=36;
	font.lfWidth=18;
	strcpy(font.lfFaceName,"����");
	if(type<0||type>10) return;
	sz=GLDGetTextSize(msr.m_hDC,&font,ftle[type]);
	rt1=CRect(10,10,sz.cx+20,50);
	rt1.OffsetRect(-rt.left,-rt.top);
	GLRectc(mdc.m_hDC,rt1,dbm.page.head.BgColor,dbm.page.head.BgColor,5);
	mdc.ShadowRect(rt1,0);
	GLDDrawText(mdc.m_hDC,&rt1,&font,ftle[type],0xff,0);
}

//����x,y��������ƶ�����
void ScadaWin::ComputMaxXY()
{
	dbm.zw=(int)((double)(dbm.page.head.width*dbm.curzoom));
	dbm.zh=(int)((double)(dbm.page.head.height*dbm.curzoom));
	xmax=wx-dbm.zw;
	ymax=wy-dbm.zh;
	Set3DEnv();//����3D����
}



void ScadaWin::ToMyZm(double zmx)
{
	int w,h,x,y;
	CPoint cpt;
	double z1,z2,zm;
	CRect rt;
	rt=CRect(0,0,0,0);
	dbm.GetObjRect(rt);
	rt.NormalizeRect();
	w=rt.Width();
	h=rt.Height();
	if(w==0||h==0) return;
	z1=(double)wx/(double)w;
	z2=(double)wy/(double)h;
	zm=z1>z2 ? z2:z1;
	dbm.curzoom=zm*zmx;
	dbm.zw=(int)((double)(dbm.page.head.width*dbm.curzoom));
	dbm.zh=(int)((double)(dbm.page.head.height*dbm.curzoom));
	xmax=wx-dbm.zw;
	ymax=wy-dbm.zh;
	w=(int)(w*dbm.curzoom);
	h=(int)(h*dbm.curzoom);
	cpt=rt.CenterPoint();

	dx=xmax/2;
	dy=ymax;
	x=(int)(cpt.x*dbm.curzoom);
	y=(int)(cpt.y*dbm.curzoom);
	ComputZCenter();
}

void ScadaWin::ChangeAllSft()
{
	int i;
	CRect rt;
	for(i=0;i<sfsum;i++){
	  if(r_sf[i].cansize==1)  ChangeCtlSize(srt,r_sf[i].swp);
	};
	//����FLASHλ��
	for(i=0;i<fssum;i++){
		rt=r_fsh[i].rt;
		rt.OffsetRect(dx,dy);
		if(r_fsh[i].fsh->align_left==1) rt.left=0;
		if(r_fsh[i].fsh->align_top==1)  rt.top=0;
		if(r_fsh[i].fsh->align_right==1) rt.right=wx;
		if(r_fsh[i].fsh->align_buttom==1) rt.bottom=wy;
		r_fsh[i].fshw.MoveWindow(rt);
	}
}


//�����Ըı䴰�ڵľ���
void ScadaWin::ChangeCtlSize(CRect rtd,SUBW_PARAM&pas)
{
	int cdx,cdy,cx,cy;
	CRect rt;
	CDRect art;
	art=pas.rts;
	art.ActRtToScr(dbm.curzoom);
	art.Offset(dx,dy);
	art.GetRECT(rt);
	cdx=rtd.left;
	cdy=rtd.top;
	cx=rtd.Width();
	cy=rtd.Height();
	if(pas.left==1)		rt.left=0;
	if(pas.top==1)		rt.top=0;
	if(pas.right==1)	rt.right=cx;
	if(pas.bottom==1)	rt.bottom=cy;
	pas.rtw=rt;
	rt.OffsetRect(-dx,-dy);
	pas.rt=rt;
	if(pas.hwnd!=NULL) ::MoveWindow(pas.hwnd,(int)pas.rtw.left,(int)pas.rtw.top,
		 (int)pas.rtw.Width(),(int)pas.rtw.Height(),true);
}

//ȡ�ñ��ݼ���������ʾ�Ķ���
void ScadaWin::GetRevSenSum()
{
	int i,j;
	//ȡ��������ʾ����
	sesum=0;
	swsum=0;
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			j=r_st[i].elg->subtype;
			switch(j){
			case 1:	case 3:case 4:case 7:case 8:
				sesum++;
				break;
			case 2:
				swsum++;
				break;
			}
		}
	}
	//sesum=bssum;
	r_sen=NULL;
	if(sesum>0)	r_sen=new  RSEN[sesum];
	if(r_sen==NULL) sesum=0;


	//��ȡ����
	r_sw=NULL;
	if(swsum>0)	r_sw=new  RSWT[swsum];
	if(r_sw==NULL) swsum=0;

	//ȡ������͵�����
	rvsum=0;
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			j=r_st[i].elg->subtype;
			if(j==1||j==4) 	rvsum++;
		}
	}
	r_rv=NULL;
	if(rvsum>0) r_rv= new RREV[rvsum];
	if(r_rv==NULL) rvsum=0;
	//ȡ��ѹ��
	trsum=0;
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			j=r_st[i].elg->subtype;
			if(j==7||j==8) 	trsum++;
		}
	}
	r_tr=NULL;
	if(trsum>0) r_tr= new RREV[trsum];
	if(r_tr==NULL) trsum=0;
}

//���ñ��ݼ�������
void ScadaWin::SetRRevSen()
{
	int i,n1,n2,n3,n4;
	n1=0;
	n2=0;
	n3=0;
	n4=0;
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			switch(r_st[i].elg->subtype)
			{
			case 1:	case 3: case 4: case 7: case 8:
				r_sen[n2].rtype=r_st[i].elg->subtype;
				r_sen[n2].bs=r_st[i].bs;
				r_sen[n2].elg=r_st[i].elg;
				r_sen[n2].did=r_st[i].elg->did;
				r_sen[n2].opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
				r_sen[n2].hrgn=NULL;
				n2++;
				break;
			}
		}
	}

	//���������
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			switch(r_st[i].elg->subtype)
			{
			case 1:	case 4:
				r_rv[n3].bs=r_st[i].bs;
				r_rv[n3].elg=r_st[i].elg;
				r_rv[n3].subtype=r_st[i].elg->subtype;
				r_rv[n3].opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
				r_rv[n3].hrgn=NULL;
				n3++;
				break;
			}
		}
	}
	//��ѹ������
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			switch(r_st[i].elg->subtype)
			{
			case 7:	case 8:
				r_tr[n4].bs=r_st[i].bs;
				r_tr[n4].elg=r_st[i].elg;
				r_tr[n4].subtype=r_st[i].elg->subtype;
				r_tr[n4].opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
				r_tr[n4].hrgn=NULL;
				n4++;	
				break;
			}
		}
	}
	//ȡ����
	for(i=0;i<stsum;i++)
	{
		if(r_st[i].elg->type==1)
		{
			switch(r_st[i].elg->subtype)
			{
			case 2:
				r_sw[n1].bs=r_st[i].bs;
				r_sw[n1].elg=r_st[i].elg;
				r_sw[n1].subtype=2;
				r_sw[n1].opt=r_st[i].bs->ort.CenterPoint(); //ȡ�е�
				r_sw[n1].hrgn=NULL;
				r_sw[n1].order=-1;
				r_sw[n1].soesum=0;
				memset(r_sw[n1].soe,0,4*sizeof(CTime));
				memset(&r_sw[n1].dl,0,sizeof(DLDL));
				n1++;	
				break;
			}
		}
	}
}

//����ͼƬ��Ϣ
void ScadaWin::GetActPicMsg(int i)
{
	int j,k,w,h,w1,h1;
	j=dbm.GetPICRecno(r_at[i].act->gid);
	r_at[i].picj=j;
	if(j<0)
	{
		r_at[i].picw=24;
		r_at[i].pich=16;
	}else{
		w=r_at[i].rt.Width();
		h=r_at[i].rt.Height();
		w1=dbm.spic[j].img.nWidth;
		h1=dbm.spic[j].img.nHeight;
		w=w1>w ? w:w1;
		h=h1>h ? h:h1;
		r_at[i].picw=w;
		r_at[i].pich=h;
	}
	r_at[i].curval=0;	//ʵʱֵ
	r_at[i].maxv=100;	//���ֵ
	r_at[i].minv=0;		//��Сֵ
	//����·��
	N_PATH *ph;
	r_at[i].pt=NULL;
	r_at[i].ptsum=0;
	for(k=0;k<dbm.page.laysum;k++){
	for(j=0;j<dbm.page.layer[k].objnum;j++){
		if(dbm.page.layer[k].obj[j].attr.type==16){
		ph=(N_PATH*)dbm.page.layer[k].obj[j].buf;
		if(ph->ID==r_at[i].act->pathid){
			r_at[i].pt=ph->pt;
			r_at[i].ptsum=ph->ptsum;
			r_at[i].curval=ph->start;	//ʵʱֵ
			r_at[i].maxv=ph->end;		//���ֵ
			r_at[i].minv=ph->start;		//��Сֵ
			break;
		}
		}
	}
	}
}



//����ActObj�ľ���λ�ã�ʵ�ʾ��Σ�
void ScadaWin::ComputActRect(int i)
{
	int w,h;
	if(r_at[i].pt==NULL||r_at[i].ptsum==0) return;
	DPOINT pt=GetPosition(r_at[i].pt,r_at[i].ptsum,r_at[i].minv,r_at[i].maxv,r_at[i].curval);
	r_at[i].oldrt=r_at[i].currt;
	w=r_at[i].picw/2;
	h=r_at[i].pich/2;
	r_at[i].currt=CDRect(pt.x-w,pt.y-h,pt.x+w,pt.y+h);
}



//���ü����㳱������
bool ScadaWin::SetFlowData(int i, READDEV  &ran)
{
	int dr;
	N_FLOW *flw;
	flw=r_fw[i].flw;
	if(memcmp(&flw->vr,&ran,sizeof(READDEV))==0) return false;
	flw->vr=ran;
	flw->ps=(float)sqrt(flw->vr.value[0]*flw->vr.value[0]+flw->vr.value[1]*flw->vr.value[1]);
	flw->pv=Getspeed(ran.value[0],0);
	flw->qv=Getspeed(ran.value[1],1);
	flw->iv=Getspeed(ran.value[7],2);

	if(ran.value[0]>0) dr=0;else dr=1; 
	if(flw->direct==0) dr=dr;else dr=dr==0 ? 1:0;
	flw->rf.pdir=dr;
	if(ran.value[1]>0) dr=0;else dr=1; 
	if(flw->direct==0) dr=dr;else dr=dr==0 ? 1:0;
	flw->rf.qdir=dr;

	flw->rf.idir=flw->rf.pdir;

	if(ran.ele==1&&(ran.value[0]!=0||ran.value[1]!=0||ran.value[7])) flw->rf.canrun=1;
	else flw->rf.canrun=0;
	r_fw[i].ptime=0;
	r_fw[i].qtime=0;
	r_fw[i].itime=0;
	return true;
}




//������ͷ�Ŵ��ʷ����仯
void ScadaWin::FlwZoomChange()
{
	int i;
	for(i=0;i<fwsum;i++)
	{
		r_fw[i].flw->pv=Getspeed(r_fw[i].flw->vr.value[0],0);
		r_fw[i].flw->qv=Getspeed(r_fw[i].flw->vr.value[1],1);
	}
}


//����һ�������ĵȸ���ֵ
bool ScadaWin::SetAContourVal(int i)
{
	double p,vmax,a;
	switch(dbm.scf.ctrtype)
	{
	case 0:case 1:case 2: 
		if(i>=bssum) return false;
		if(r_bs[i].bus->vr.value[1]==0)	return sct.SetContourEnable(i);
		return sct.SetVal(i,r_bs[i].bus->vr.value[1]);
	case 3:
	case 5:
		if(i>=fwsum) return false;
		vmax=r_fw[i].flw->vr.value[4];
		if(r_fw[i].flw->vr.ele==0||vmax==0) return sct.SetContourEnable(i);
		vmax=vmax<0 ? -vmax:vmax;
		p=r_fw[i].flw->ps;//>vr.value[0];
		p=p<0 ? -p:p;
		a=p*100/vmax;
		return sct.SetVal(i,a);
	case 4: //���ñ�ѹ���ȸ���ֵ iΪtrsum�еı��
		if(i>=trsum) return false;
		switch(r_tr[i].elg->subtype)
		{  
		case 7:  
			vmax=r_tr[i].elg->vr.value[1];
			p=r_tr[i].elg->Ps;//>vr.value[2];
			break;
		case 8:
			vmax=r_tr[i].elg->vr.value[3];
			p=r_tr[i].elg->Ps;//vr.value[4];
			break;
		 
		} 
		if(r_tr[i].elg->vr.sta==0||vmax==0) return sct.SetContourEnable(i);
		vmax=vmax<0 ? -vmax:vmax;
		
		p=p<0 ? -p:p;
		a=p/vmax;
		
		return sct.SetVal(i,a);
	}
	return false;
}

int ScadaWin::Getspeed(double value,int type)
{
	int c;
	double v,vm;
	switch(type)
	{
	case 0: //�й�
		vm=dbm.scf.Pref;
		break;
	case 1: //�޹�
		vm=dbm.scf.Qref;
		break;
	case 2: //����
		vm=dbm.scf.Iref;
		break;
	}
	vm=vm<0 ? -vm:vm;
	v=value>0 ? value:-value;
	vm=vm==0 ? 300:vm;
	if(v>vm) v=vm;
	c=(int)((5.0*v)/vm);
	if(c==0&&value!=0) c=1;
	return 5-c;
}

void ScadaWin::PrintPage(HDC hdc, BYTE pm, int sdx, int sdy)
{
	/*CDC dc;
	dc.Attach(hdc);
	dc.Ellipse(100,100,600,600);
	dc.Detach();
	return;*/

	int i;
	dbm.PrintShow(hdc,pm,sdx,sdy);
	for(i=0;i<atsum;i++)
	{
		ShowActObj(hdc,sdx,sdy,i);
	}
}

//��ʾСͼ��
void ScadaWin::ShowActObj(HDC hdc,int sdx,int sdy,int k)
{
	int i,w,h;
	CPoint cpt;
	CRect rt;
	CDRect art;
	DPOINT npt;
	if(r_at[k].pt==NULL||r_at[k].ptsum==0)  return;
	art=r_at[k].currt;
	art.ActRtToScr(dbm.curzoom);
	art.Offset(sdx,sdy);
	art.GetRECT(rt);
	npt=art.CenterPoint();
	cpt.x=(int)npt.x;
	cpt.y=(int)npt.y;
	i=r_at[k].picj;
	if(i<0)
	{
		cobj.ShowSimg(hdc,cpt.x-8,cpt.y-8,12);
		return;
	}
	w=dbm.spic[i].img.nWidth;
	h=dbm.spic[i].img.nHeight;
	w=w>(rt.right-rt.left) ? rt.right-rt.left:w;
	h=h>(rt.bottom-rt.top) ? rt.bottom-rt.top:h;
	dbm.spic[i].img.Show(hdc,cpt.x-w/2,cpt.y-h/2,w,h);
}



//��ͷ�����仯
void ScadaWin::ZoomChange()
{
	double x,y,width,height;
	ComputMaxXY();
	width=dbm.zw;
	height=dbm.zh;
	x=(double)(vx*dbm.curzoom);
	y=(double)(vy*dbm.curzoom);
	dx=(int)(wx/2-x);
	dy=(int)(wy/2-y);
	if(xmax>=0) dx=(int)((wx-width)/2);
	if(ymax>=0) dy=(int)((wy-height)/2);
	if(xmax<0&&dx>0) dx=0;
	if(ymax<0&&dy>0) dy=0;
	ComputZCenter();
	if(cobj.nwin!=NULL) cobj.nwin->ZoomChange();
}

//�ı�ȸ�������
void ScadaWin::ChangeDgxcfg()
{
	//��������仯
	if(dbm.scf.showdgx==1&&dbm.page.head.type>0)
	{
		SetContourParam();
		ReSetAllContourVal();
		sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
	}
	EndShow();
}

//�������еĵȸ���ֵ
void ScadaWin::ReSetAllContourVal()
{
	int i,n=0;
	switch(dbm.scf.ctrtype)
	{
	case 0:case 1:case 2: 
		n=bssum;
		break;
	case 3:
		n=fwsum;
		break;
	case 4:
		n=trsum;
		break;
	case 5:
		n=fwsum;
		break;
	}
	for(i=0;i<n;i++)  SetAContourVal(i);
}

//���仯
void ScadaWin::CursorChange(int newcursor)
{
	if(cursor==newcursor)
	{
		cursor=0;
		rcursor=0;
	}else {
		cursor=newcursor;
		rcursor=newcursor;
	}
	polysum=0;
	segsum=0;
}

//����״̬����Ϣ
void ScadaWin::SetStatusBarMsg()
{
	char p[256];
	int i;
	i=cobj.utype;
	if(i<0||i>3) i=3;
	sprintf(p,"��¼�û�:[%s]-[%s]",cobj.curnm,usertype[i]);
	cobj.tbar->SetPaneText(2,p);
	//�������ݿ�
	sprintf(p,"��ǰ��: %s",dbm.dbzt==0 ? "ʵʱ̬":"�о�̬");
	cobj.tbar->SetPaneText(1,p);
}


//��ʾ��̬����
void ScadaWin::ShowDynObj(HDC hdc)
{
	int i;
	if(dbm.msdwn==1) return;
	if(t1==1) return;
	if(allupdate==1) //����ȫ����
	{
		ShowA(mbg);
		if(dbm.lookdown==1&&(dbm.scf.showrev==2||dbm.scf.showrev==8)) CreateAllrgn();
		ShowC(hdc,srt);
		allupdate=0;
		return;
	}
	t1=1;
	//��̬����
	ComputGenJs(r_rv,rvsum);
	ComputGifAmlJs(r_am,amsum);
	if(dbm.curopzt==3) //��Ƶ��ʱ
	{
		for(i=0;i<fwsum;i++)
		{
			if(r_fw[i].lfflag==0) continue;
			UpdateLowFData(r_fw[i]);
		}
		
	}else  //�������
	{
		ComputFlowJs(r_fw,fwsum,dbm.scf.ftype);
	}
	//HBRUSH hb=CreateSolidBrush(0xff);
	//ˢ�¿ͻ���
	if(updatergn!=NULL)
	{
		SaveDC(hdc);
		//FillRgn(hdc,updatergn,hb);
		SelectObject(hdc,updatergn);
		ShowC(hdc,updatergn);
		RestoreDC(hdc,-1);
	}
	t1=0;
	//DeleteObject(hb);
}


//���ö�̬�Ǳ�
void ScadaWin::SetDynMeter()
{
	int i,k,bz;
	float v1,v2,v3;
	for(i=0;i<ybsum;i++)
	{
		bz=0;
		for(k=0;k<r_yb[i].mtr->dbsum;k++)
		{
			v1=r_yb[i].mtr->newval[k];
			v2=r_yb[i].mtr->curval[k];
			if(v1==v2) continue;
			v3=v2-v1;
			v3=v3>0 ? v3:-v3;
			if(v3<0.01)
			{
				r_yb[i].mtr->curval[k]=r_yb[i].mtr->newval[k];
				bz=1;
			}else{
				r_yb[i].mtr->curval[k]=(float)((r_yb[i].mtr->newval[k]+r_yb[i].mtr->curval[k])/2);
				bz=1;
			}
		}
		if(bz==1) r_yb[i].mtr->show=1;
  	}
}


//��ʱ��ʾ����ʱ��
void ScadaWin::Showdtime(HDC hdc)
{
	int i;
	DPOINT dpt[4];
	POINT  ipt[4];
	CRect rt;
	CDRect art;
	N_DATE *d;
	N_TIME *t;
	int day,sec;
	CTime tm;
	tm=CTime::GetCurrentTime();
	day=tm.GetDay();
	sec=tm.GetSecond();
	for(i=0;i<dtsum;i++)
	{
		d=(N_DATE*)r_da[i].bs->buf;
		if(d->tm.GetDay()!=day||dtupdate!=0)
		{
			d->tm=tm;
			if(!r_da[i].bs->ObjIsInRect(srt)) continue;
			d=(N_DATE *)r_da[i].bs->buf;
			PointActToScr(d->pt,dpt,4,dbm.curzoom);
			msr.DPtToScrPt(dpt,ipt,4,dx,dy);
			rt=CreateCRt(4,ipt);
			rt&=srt;
			if(!rt.IsRectEmpty()) ShowC(hdc,rt);
		}
	}
	for(i=0;i<tmsum;i++)
	{
		t=(N_TIME*)r_tm[i].bs->buf;
		if(t->tm.GetSecond()!=sec||dtupdate!=0)
		{
			t->tm=tm;
			if(!r_tm[i].bs->ObjIsInRect(srt)) continue;
			d=(N_DATE *)r_tm[i].bs->buf;
			PointActToScr(d->pt,dpt,4,dbm.curzoom);
			msr.DPtToScrPt(dpt,ipt,4,dx,dy);
			rt=CreateCRt(4,ipt);
			rt&=srt;
			if(!rt.IsRectEmpty()) ShowC(hdc,rt);
		}
	}
	dtupdate=0;
}



void ScadaWin::DrawXorRect(CRect rt)
{
	CClientDC dc(this);
	dc.DrawDragRect(&rt,CSize(1,1),&oldrt,CSize(1,1));
	oldrt=rt;
}

//��ӵ�
void ScadaWin::AddPoint(CPoint point)
{
	double d;
	if(polysum>=299) return;
	if(polysum==0){
		ptpoly[polysum].x=point.x;
		ptpoly[polysum].y=point.y;
		polysum++;
		return;
	}
	DPOINT np1,np2;
	np1.x=point.x;np1.y=point.y;
	np2.x=ptpoly[polysum-1].x;np2.y=ptpoly[polysum-1].y;
	d=GetLength(np1,np2);
	if(d<5) return;
	ptpoly[polysum].x=point.x;
	ptpoly[polysum].y=point.y;
	polysum++;
}

//�鿴�����Ƿ��ڰ�ť��
int ScadaWin::IsInPush(CPoint point)
{
	int i;
	CDPoint apt;
	apt.SetPOINT(point);
	apt.Offset(-dx,-dy);
	apt.ScrPtToAct(dbm.curzoom);
	for(i=0;i<phsum;i++)
	{
	  if(r_ph[i].rt.PtInRect(apt)) return i;
	}
	return -1;
}

//��ʾ��ť
void ScadaWin::ShowPush(int j)
{
	CRect rt;
	CDRect art;
	if(j<0||j>=phsum) return;
	CClientDC dc(this);
	art=r_ph[j].rt;
	art.ActRtToScr(dbm.curzoom);
	art.Offset(dx,dy);
	art.GetRECT(rt);
	rt&=srt;	
	if(!rt.IsRectEmpty()) PaintShow(dc.m_hDC,rt);
}
//�û��Զ������
void ScadaWin::UserSflw()
{
	int i,n;
	DMSECT  dmstmp;
	StFlwDlg dlg;
	CCrossObj rss;
	if(segsum<=0) return;
	//��ʼ������
	rss.fwsum=fwsum;
	rss.r_fw=r_fw;
	rss.pt=dmpt;
	rss.segsum=segsum;
	rss.dmdot=dmsdot;
	rss.dbm=&dbm;
	n=0;
	for(i=0;i<segsum;i++) n+=dmsdot[i];
	for(i=0;i<n;i++)
	{
	   dmpt[i].x-=dx;
	   dmpt[i].y-=dy;
	}
	

	if(!rss.GetCrossLine(dmstmp))
	{
		MessageBox("��û��ѡ��һ������ߣ�\n��������һ�¡�","���泱��ѡ�����",MB_ICONSTOP);
		EndShow();
		polysum=0;
		return;	
	}
	
	//////////////////
	dlg.dbm=&dbm;
	dlg.tmp=dmstmp;
	dlg.DoModal();
	polysum=0;
	segsum=0;
	cursor=0;
	rcursor=0;
	LoadPreDefineSfw();
}



//���泱��(���߷�ʽ)
//������
void ScadaWin::SectFlw()
{
	int i,n;
	CCrossObj rss;
	if(segsum<=0) return;
	//��ʼ������
	rss.fwsum=fwsum;
	rss.r_fw=r_fw;
	rss.pt=dmpt;
	rss.segsum=segsum;
	rss.dmdot=dmsdot;
	rss.dbm=&dbm;
	n=0;
	for(i=0;i<segsum;i++) n+=dmsdot[i];
	for(i=0;i<n;i++)
	{
	   dmpt[i].x-=dx;
	   dmpt[i].y-=dy;
	}


	if(!rss.GetCrossLine(dms[0])){
		MessageBox("��û��ѡ��һ������ߣ�\n��������һ�¡�","���泱��ѡ�����",MB_ICONSTOP);
		dmsum=0;	
	}else dmsum=1;
	if(dms[0].Pmax==0)
	{
		MessageBox("���е���·�й�����֮��Ϊ0��������ȷ��ʾ���泱��\n�������ݿ������·��Pmax�Ƿ�Ϊ0","���泱������",MB_OK);
		dmsum=0;
		return;
	}
	polysum=0;
	segsum=0;
	cursor=0;
	rcursor=0;
	EndShow();
}


//����������
void ScadaWin::ComputSen()
{
	int i;
	READSEN sn;
	SenDlg dlg;
	dlg.dbm=&dbm;
	if(polysum<=2) return;
	if(cursor!=7&&cursor!=8) return;
	for(i=0;i<sesum;i++) r_sen[i].senvalue=0;
	//��ʼ������
	dlg.fwsum=fwsum;dlg.r_fw=r_fw;
	dlg.bssum=bssum;dlg.r_bs=r_bs;
	dlg.pt=ptpoly;
	dlg.ptsum=polysum;
	for(i=0;i<polysum;i++)
	{
	   ptpoly[i].x-=dx;
	   ptpoly[i].y-=dy;
	}
	dlg.type=cursor-7;
	sentype=dlg.type;
	if(dlg.DoModal()==IDCANCEL)
	{  
		DrawShow();		
		return;
	}
	senpoint=dlg.selpt;
	dbm.lookdown=1;
	dbm.scf.lmd=1;
	Set3DEnv();//����3D����
	if(rrd.ReadSenData(sn)) SetSenData(sn);

	/*CClientDC dc(0);
	char p[100];
	for(i=0;i<sn.ssum;i++)
	{
		sprintf(p,"i=%d id=%d type=%d  val=%2.2f",i,sn.se[i].NU,sn.se[i].type,sn.se[i].senval);
		dc.TextOut(10,10+i*20,p);
	}*/
	//////////////////////////�Զ�����������//////////////////////////////////
	//���Զ�����������
	/*int a,b;
	float s;

	for(i=0;i<6;i++){ //����5��������
		if(sesum==0) break;
		a=rand();
		b=a/sesum;
		a=a-b*sesum;
		b=rand()%100;
		s=(float)((double)b/100.00);
		s=i%2==0 ? s:-s;
		if(a>=0&&a<sesum)
		{
			r_sen[a].senvalue=s;
		}
	}*/
	//////////////////////////////////////////
	polysum=0;
	cursor=0;
	rcursor=0;
	if(NeedDrawDgx())  sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
	EndShow();
	CreateAllrgn();
}

//�����·����
void ScadaWin::ComputScc()
{
	int id,linetype;
	if(polysum<=2) return;
	ComputeSelBra(id,linetype,r_fw,fwsum,ptpoly,polysum,dbm.curzoom);
	if(id==-1)
	{
		MessageBox("û��ѡ��һ����·���޷����м��㣡",MB_OK);
		return;
	}

	/*char p[100];
	sprintf(p,"id=%d ",id);
	MessageBox(p);*/
	/////////////////�˴������ƹ��ĶԻ�����㲢���ؽ��///////////////////////
	NT_DLSJ((BYTE)(linetype+1),(DWORD)id);
	//////////////////////////////////////////
	polysum=0;
	cursor=0;
	rcursor=0;
	/*dbm.lookdown=1;
	if(NeedDrawDgx())  sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
	EndShow();
	CreateAllrgn();*/
}

//���а�ť����
void ScadaWin::RunPushCmd(int j)
{
	HWND hw;
	char fm[256];
	char fnm[64];
	int n,index,mode;
	HISHMI newhmi;
	switch(r_ph[j].psh->cmdtype)
	{
	case 0: 
		{
			HWND hWnd=CProcesse::FindProcHwnd(r_ph[j].psh->command);
			if(hWnd==NULL)
				CProcesse::RunProcess(r_ph[j].psh->command);
			else
				::BringWindowToTop(hWnd);
			//WinExec(r_ph[j].psh->command,SW_SHOW); 
		}
		break;
	case 1: //�򿪻���
		n=sscanf(r_ph[j].psh->command,"%s %d",fnm,&index);
		mode=r_ph[j].psh->tosta;
		if(n==2)//������Ч
		{  
			GetCurHmi(newhmi);
			cobj.SetToLocalFile(fnm,fm);
			if(dbm.CheckFileIndex(fm,index))
			{
				FreeMem();
				dbm.OpenPwFile(fm,index);
				InitMoveObj();
				dbm.AddOpenHmi(newhmi);
				cobj.mwin->ptl.DrawShow();
				cobj.SetToNeedMode(mode);  
				return;
			}
		}
		break;  
	case 2: //����CMD��Ϣ
		GetParent()->PostMessage(WM_COMMAND,r_ph[j].psh->cmdnum);
		break;
	case 3: 
		hw=GetSlfCtl(r_ph[j].psh->selfid);
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,r_ph[j].psh->cmdnum,0);
		break;
	/*case 4: //�˳�����
		GetParent()->GetParent()->PostMessage(WM_CLOSE);
		break;
	case 5:   //ִ�й���ģ��
		RunFunctModule(r_ph[j].psh->command);
		break;*/
	}
}

//�ֲ��Ŵ�
void ScadaWin::PartZoom(CRect rt)
{
	double xl,yl,a,k;
	int w,h;
	CRect rt1;
	CPoint pt;
	rt1=rt;
	rt1.NormalizeRect();
	pt=rt1.CenterPoint();
	w=rt1.Width(); 
	h=rt1.Height();
	if(w==0||h==0) return;
	vx=(int)(pt.x/dbm.curzoom);
	vy=(int)(pt.y/dbm.curzoom);
	xl=(double)(wx/(double)w);
	yl=(double)(wy/(double)h);
	a=xl<yl ? xl:yl;
	k=dbm.curzoom;
	k=(double)(k*a);
	switch(dbm.page.head.type)
	{
		case 0: k=k>1	? 1:k;	break;
		case 1: k=k>3	? 3:k;	break;
		case 2: k=k>100  ? 10:k; break;
		default:return;
	}
	if(k<0.1) return;
	dbm.curzoom=k;
	ZoomChange();
	if(PartZoomChkBus()) return;
}



//�쿴�Ƿ��ڰ�ť��
void ScadaWin::MouseOnPush(UINT nFlags,CPoint point)
{
	int j,k;
	j=IsInPush(point);
	if(oldsel!=j){
		if(oldsel>=0&&oldsel<phsum) r_ph[oldsel].psh->down=0;
		ShowPush(oldsel);
	}
	if(cursor==2||cursor==6) return;
	if(j>=0){
		k=r_ph[j].psh->style;
		if(nFlags==MK_LBUTTON) r_ph[j].psh->down=1;
		else if(k==1||k==2||k==4||k==6) r_ph[j].psh->down=1;
		if(j!=oldsel) ShowPush(j);
		oldsel=j;
	}else{
		oldsel=-1;
	}
}

//��������������
int type1[]={1,3,4,7,8};
//0=����� 1=���� 2=���� 3=�������ѹ�� 4=�������ѹ��
void ScadaWin::SetSenData(READSEN&sn)
{

	int i,j,k,type;
	for(i=0;i<sn.ssum;i++)
	{
		k=sn.se[i].type;
		if(k>4||k<0) continue;
		type=type1[k];
		for(j=0;j<sesum;j++)
		{
			if(type==r_sen[j].elg->subtype&&sn.se[i].NU==(DWORD)r_sen[j].did)
			{
				r_sen[j].senvalue=sn.se[i].senval;
				r_sen[j].rtype=k;
				break;
			}
		}
	}
}

//���������ؼ��Ĵ���
HWND ScadaWin::GetSlfCtl(int id)
{
	int i;
	for(i=0;i<sfsum;i++){
		if(id==r_sf[i].stl->id)
			return r_sf[i].stl->hwnd;
	};
	return NULL;
}

//�϶�����
void ScadaWin::ZoomInOut()
{
	double oldz;
	int x,y,mode;
	oldz=dbm.curzoom;
	x=pt2.x-pt1.x;
	y=pt2.y-pt1.y;
	pt1=pt2;
	mode=0;
	if(x<0&&y<0)  //�϶��Ŵ�
	{
		dbm.ZoomPage(1);
		Set3DEnv();//����3D����
		mode=1;
	}
	if(x>0&&y>0)  //�϶���С
	{
		if(dbm.zw<wx/2&&dbm.zh<wy/2) return;
		dbm.ZoomPage(2);
		Set3DEnv();//����3D����
		mode=2;
	}
	if(oldz!=dbm.curzoom){
		ZoomChange(); //�Ŵ��ļ���
		Set3DEnv();
		DrawShow();
	}
	if(dbm.lookdown==0){
		switch(mode)
		{
		case 1:
			if(ZoomOutCheckBus()) return;		//�����Ƿ��ƻ���
			break;
		case 2:
			if(ZoomInCheckBus()) return;		//�����Ƿ񷵻��Ƴ�ǰ����
			break;
		}	
	}
	SetStatusZoom();
}

//��תͼ��
void ScadaWin::Rotate()
{
	int a1,a2,a;
	CPoint p1,p2,p3;
	p3.x=(int)dbm.zw/2;
	p3.y=(int)dbm.zh/2;
	p1=pt1;
	p2=pt2;
	p1.Offset(-dx,-dy);
	p2.Offset(-dx,-dy);
	a1=(int)GetAngle(p3,p1);
	a2=(int)GetAngle(p3,p2);
	a=a2-a1;
	dbm.curang=oldang+a;
	dbm.curang=dbm.curang%360;
	if(a!=0)
	{
		Set3DEnv();//����3D����	
		DrawShow();
	}
}


//������ͳ�ƶ�����
void ScadaWin::DrawStatArea()
{
	LOGBRUSH  lp;
	CRect rt;
	HPEN oldpen,pen;
	CClientDC dc(this);
	lp.lbColor=0xff;
	lp.lbHatch=0;
	lp.lbStyle=PS_SOLID;
	pen=ExtCreatePen(PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_ROUND,1,&lp,0,NULL);
	oldpen=(HPEN)SelectObject(dc.m_hDC,pen);
	Polyline(dc.m_hDC,ptpoly,polysum);
	SelectObject(dc.m_hDC,oldpen);
	DeleteObject(pen);
}

//////////////////////////////////////////////////////////////////////////////////////
//                               ���´�������ʵ��ͼ��������ɫ
//////////////////////////////////////////////////////////////////////////////////////
//�ռ��豸����
void ScadaWin::CollectDevice()
{
	nettp.SetDevice(r_st,stsum);
	nettp.SetBus(r_bs,bssum);
	nettp.SetLine(r_fw,fwsum);
	nettp.SetConLine(r_cl,clsum);
	nettp.ComputLineSiteRt();
	nettp.CreateNode();
}

//�������
void ScadaWin::DmFlowSwitch()
{
	switch(cursor)
	{
	case 6: //���泱��
		SectFlw();
		break;
	case 9: //�Զ�����泱��
		UserSflw();
		break;
	}
}

//��ʾѡ����
void ScadaWin::ShowSelFlag(HDC hdc,int sx,int sy)
{
	DPOINT dpt[2];
	POINT  tp[2];
	if(dbm.scf.lmd==0) return;
	PointActToScr(&senpoint,dpt,1,dbm.curzoom);
	msr.DPtToScrPt(dpt,tp,1,sx,sy);
	cobj.ShowSimg(hdc,tp[0].x-4,tp[0].y-27,6);
}

void ScadaWin::GetCurHmi(HISHMI &newhmi)
{
	strcpy(newhmi.filename,dbm.curfile);
	newhmi.picno=dbm.curpage;
	newhmi.zoom=dbm.curzoom;
	newhmi.dx=dx;
	newhmi.dy=dy;
	newhmi.showdgx=dbm.scf.showdgx;
	newhmi.showrev=dbm.scf.showrev;
	newhmi.ctrtype=dbm.scf.ctrtype;
	newhmi.lookdown=dbm.lookdown;
	newhmi.vx=vx;
	newhmi.vy=vy;
	newhmi.cursor=cursor;				//��ǰ���
}

//����ʱ��֤ĸ���Ƿ���Ҫ�Ƴ�����
bool ScadaWin::ZoomOutCheckBus()
{
	int i,id,pno;
	HISHMI newhmi;
	char grpname[25],filename[256];
	double w1,w2,h1,h2,dis,d,x,y;
	DPOINT cpt1,cpt2;
	CDRect rt1,rt2,rt3;
	//���ȿ��Ƿ��п����ƻ���
	if(ZoomOutApdOpen()) return true; //�Ƴ��ɹ����˳�
	/////////////////////////
	//Ȼ�����ж��Ƿ���Ҫͨ��ĸ�߹����ƻ���
	rt1=CDRect(0,0,(double)wx,(double)wy);
	rt1.Offset(-dx,-dy);
	rt1.ScrRtToAct(dbm.curzoom);
	cpt1=rt1.CenterPoint();
	w1=rt1.Width()*0.7;
	h1=rt1.Height()*0.7;
	id=-1;
	dis=10000;
	for(i=0;i<bssum;i++)
	{	
		rt2=r_bs[i].bs->ort;
		rt3=r_bs[i].bs->ort;
		rt2&=rt1;
		if(rt2.IsRectEmpty()) continue;
		w2=rt3.Width();
		h2=rt3.Height();
		cpt2=rt3.CenterPoint();
		if(w2>w1||h2>h1)
		{
			x=cpt2.x-cpt1.x;
			y=cpt2.y-cpt2.y;
			d=sqrt(x*x+y*y);
			if(d<dis){
			  id=r_bs[i].bus->did;
			  dis=d;
			}
		}
	}
	if(id<0) return false;
	if(!cobj.GetBusGrp(id,grpname,pno)) return false;
	cobj.SetToLocalFile(grpname,filename);
	if(strcmp(filename,dbm.curfile)==0&&pno==dbm.curpage) return false; 
	if(dbm.CheckFileIndex(filename,pno)){
		GetCurHmi(newhmi);
		FreeMem();
		dbm.OpenPwFile(filename,pno);
		InitMoveObj();
		dbm.AddOpenHmi(newhmi,1);
		return true;
	}
	return false;
}

bool ScadaWin::PartZoomChkBus()
{
	int i,n,id,pno;
	HISHMI newhmi;
	char grpname[25],filename[256];
	CDRect rt1,rt2;
	rt1=CDRect(0,0,wx,wy);
	rt1.Offset(-dx,-dy);
	rt1.ScrRtToAct(dbm.curzoom);
	id=-1;
	n=0;
	for(i=0;i<bssum;i++)
	{	
		rt2=r_bs[i].bs->ort;
		rt2&=rt1;
		if(rt2.IsRectEmpty()) continue;
		id=r_bs[i].bus->did;
		n++;
		if(n>1) return false;
	}
	if(id<0||n>1) return false;
	if(!cobj.GetBusGrp(id,grpname,pno)) return false;
	cobj.SetToLocalFile(grpname,filename);
	if(strcmp(filename,dbm.curfile)==0&&pno==dbm.curpage) return false; 
	if(dbm.CheckFileIndex(filename,pno)){
		CloseLowfWin();
		GetCurHmi(newhmi);
		FreeMem();
		dbm.OpenPwFile(filename,pno);
		InitMoveObj();
		dbm.AddOpenHmi(newhmi,1);
		return true;
	}
	return false;
}
//��Сʱ��ȷ�Ϸ��ػ���
bool ScadaWin::ZoomInCheckBus()
{
	char fnm[256];
	HISHMI hmi;
	//���Ȳ쿴�Ƿ��п����ƻ���
	if(ZoomInApdOpen()) return true; //�Ƴ��ɹ����˳�
	//Ȼ���ٸ��ݷŴ����쿴�Ƿ�÷���
	if(dbm.curzoom>=0.3)			return false;
	if(!dbm.LastHmiIsMode1())		return false;
	if(dbm.GetALastHmi(hmi)==false) return false;
	cobj.SetToLocalFile(hmi.filename,fnm);
	if(dbm.CheckFileIndex(fnm,hmi.picno))
	{
		CloseLowfWin();
		FreeMem();
		dbm.OpenPwFile(fnm,hmi.picno);
		InitMoveObj(&hmi,1);
		return true;
	}
	return false;
}
//����Ԥ����Ķ�������
void ScadaWin::LoadPreDefineSfw()
{
	int i,j;
	READDEV  ran;
	char name[256];
	double I,v,pcur,ps,p,q;
	DMSAVE hd;
	FILE *fp;
	dmsum=0;
	dbm.GetSectFLwName(name);
	fp=fopen(name,"r+b");
	if(fp==NULL){
		MessageBox("��ҳ�治����Ԥ����Ķ���!");	
		return;
	}
	fread(&hd,sizeof(DMSAVE),1,fp);
	if(hd.version!=0x10||hd.flag!=0xc0){ //�汾����,����
		fclose(fp);
		return;
	};
	dmsum=hd.dmsum;
	dmsum=dmsum>10 ? 10:dmsum;
	if(dmsum>0) fread(dms,sizeof(DMSECT),dmsum,fp);
	fclose(fp);
	//��ȡ���泱��
	for(j=0;j<dmsum;j++)
	{
		I=0;
		pcur=0;
		for(i=0;i<dms[j].lsum;i++)
		{
			ran.recno=dms[j].ls[i].jlh;
			ran.did=dms[j].ls[i].id;
			ran.dtype=dms[j].ls[i].type+1; //������ֱ��
			if(rrd.ReadDevData(ran))
			{
				v=ran.value[7];
				I+=v;
				p=ran.value[0];
				q=ran.value[1];
				ps=sqrt(p*p+q*q);//���ڹ���
				pcur+=ps;
			}
		}
		dms[j].Icur=(float)I;
		dms[j].Pcur=(float)pcur;
	}
	EndShow();
}
//�Ƿ���������ƻ���
bool ScadaWin::ZoomOutApdOpen()
{
	int pno;
	HISHMI newhmi,thm;
	char grpname[25],filename[256];
	if(dbm.apdenable==0||dbm.apd.enableout==0) return false; //û�п����ƻ���
	if(dbm.curzoom<dbm.apd.outstart) return false;
	strcpy(grpname,dbm.apd.outname);
	pno=dbm.apd.outno;
	if(dbm.apd.defzm1==1)
	{
			thm.mode=1;
			thm.zoom=dbm.apd.zm1;
	}else thm.mode=0;
	cobj.SetToLocalFile(grpname,filename);
	if(dbm.CheckFileIndex(filename,pno)){
		CloseLowfWin();
		GetCurHmi(newhmi);
		FreeMem();
		dbm.OpenPwFile(filename,pno);
		InitMoveObj(&thm,2);
		dbm.AddOpenHmi(newhmi);
		return true;
	}
	return false;
}

//�Ƿ���������ƻ���
bool ScadaWin::ZoomInApdOpen()
{
	int pno;
	HISHMI newhmi,thm;
	char grpname[25],filename[256];
	if(dbm.apdenable==0||dbm.apd.enablein==0) return false; //û�п����ƻ���
	if(dbm.curzoom>dbm.apd.instart) return false;
	strcpy(grpname,dbm.apd.inname);
	pno=dbm.apd.inno;
	if(dbm.apd.defzm2==1)
	{
		thm.mode=1;
		thm.zoom=dbm.apd.zm2;
	}else thm.mode=0;
	cobj.SetToLocalFile(grpname,filename);
	if(dbm.CheckFileIndex(filename,pno))
	{
		CloseLowfWin();
		GetCurHmi(newhmi);		
		FreeMem();
		dbm.OpenPwFile(filename,pno);
		InitMoveObj(&thm,2);
		dbm.AddOpenHmi(newhmi);
		return true;
	}
	return false;
}


//����״̬����Ϣ
void ScadaWin::SetStatusZoom()
{
	char p[256];
	sprintf(p,"�Ŵ���:%2.2f",dbm.curzoom);
	if(cobj.tbar!=NULL) cobj.tbar->SetPaneText(3,p);
}

bool ScadaWin::NeedDrawDgx()
{
	if(dzoom!=dbm.curzoom||ddx!=dx||ddy!=dy||dangle!=dbm.curang||dbm.lookdown!=dlk)
	{
		if(dbm.scf.showdgx==1) return true;
	}
	return false;
}


BOOL ScadaWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (0, "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

//��ʼ����Ƶ������
void ScadaWin::InitLowFData()
{
	/*int i,n;
	DPOINT dpt[21];
	N_FLOW *fw;	
	for(i=0;i<fwsum;i++)
	{
		fw=r_fw[i].flw;
		r_fw[i].lfflag=0;
		fw->lowfbz=0;
		if(!lwin.IsLowFLine(fw->did,fw->type)) continue;
		r_fw[i].curdot=0;			//��ǰ����
		r_fw[i].lfflag=1;			//��Ƶ�𵴱��
		fw->lowfbz=1;
		if(fw->fpt!=NULL) delete fw->fpt;
		fw->fpt=NULL;
		n=fw->ptsum;
		n=n>20 ? 20:n;
		PointActToScr(fw->pt,dpt,n,dbm.curzoom);
		msr.DPtToActPt(dpt,dpt,n,0,0,0);
		fw->flen=GetLineLength(dpt,n);
		if(fw->flen<300) fw->flen=300;
		if(fw->flen>0) fw->fpt=new float[fw->flen];
		if(fw->fpt==NULL) fw->flen=0;
		else memset(fw->fpt,0,sizeof(float)*fw->flen);
		r_fw[i].curdot=200;
	}*/
	//����Ƶ�𵴴�����ʾ
	lwin.SetFunct(0);
	lwin.ShowWindow(SW_SHOW);
}

//��ʼ����Ƶ������
void ScadaWin::InitLowFData(LFDATA* pLF)
{
	int i,n;
	DPOINT dpt[21];
	N_FLOW *fw;	
	for(i=0;i<fwsum;i++)
	{
		fw=r_fw[i].flw;
		if(fw->did==pLF->LineID && fw->type==pLF->Type)
		{
			if(r_fw[i].lfflag==0)
			{
				r_fw[i].curdot=0;			//��ǰ����
				r_fw[i].lfflag=1;			//��Ƶ�𵴱��
				fw->lowfbz=1;
				if(fw->fpt!=NULL) delete fw->fpt;
				fw->fpt=NULL;
				n=fw->ptsum;
				n=n>20 ? 20:n;
				PointActToScr(fw->pt,dpt,n,dbm.curzoom);
				msr.DPtToActPt(dpt,dpt,n,0,0,0);
				fw->flen=GetLineLength(dpt,n);
				if(fw->flen<300) fw->flen=300;
				if(fw->flen>0) fw->fpt=new float[fw->flen];
				if(fw->fpt==NULL) fw->flen=0;
				else memset(fw->fpt,0,sizeof(float)*fw->flen);
				r_fw[i].curdot=200;
			}
			break;
		}
	}
}

//�Զ���������
void ScadaWin::UpdateLowFData(RFLOW &fw)
{
	int i,j,a,n,start,end;
	float *v;
	a=fw.flw->flen;
	if(a<=0) return;
	if(fw.curdot>=20) //����������꣬����ȡһ�����ݵ���ʱ������
	{
		if(!lwin.GetABufData(fw.lfdcur,fw.flw->did,fw.flw->type)) return;
		fw.curdot=0;
	}

	v=fw.flw->fpt;
	start=(int)(LOWFSTEP*fw.curdot);
	end=(int)(LOWFSTEP*(fw.curdot+1));
	n=end-start;
	j=a-n-1;
	
	//������Ҫ�ߵĵ���	
	for(i=a-1;i>=n;i--)
	{
		v[i]=v[i-n];
	}	
	for(i=0;i<n;i++)
	{
		j=start+i;
		v[n-i-1]=fw.lfdcur.lfd[j];
	}
	fw.curdot++;
	if(lwin.lbdown==0) lwin.LowFShow();
}



//�쿴ѡ�����·�Ƿ��������Ƶ�𵴷Ŵ�
bool ScadaWin::SelCanZoomLowF()
{
	if(dbm.curopzt!=3) return false;
	if(seltype!=2) return false;
	if(selsubtype<34||selsubtype>35) return false;
	if(seljlh<0) return false;
	if(r_fw[seljlh].lfflag==0) return false;
	return true;
}

void ScadaWin::CloseLowfWin()
{
	lwin.ShowWindow(SW_HIDE);
	lwin.EndLowf(); //�ر�����
	dbm.curopzt=0;
}


void ScadaWin::SetCurDbf(int newdbzt)
{
	dbm.dbzt=newdbzt;			//0=���� 1=�����ʷ
	rrd.SetCurDbf(newdbzt);
}


//����һ���µ�SOE
void ScadaWin::SetANewSoe(NSOES &asoe)
{
	CTimeSpan ts;
	int i,j,n,bz,m;
	CTime t1,t2;
	int s1,s2;
	RSWT   tmp;
	//����ID
	j=-1;
	for(i=0;i<swsum;i++)
	{
		if(asoe.swtid==(DWORD)r_sw[i].elg->did)
		{
			j=i;
			break;
		}
	}
	if(j==-1) return;
	//��ӵ�����
	//���Ȳ鿴�Ƿ��Ѿ��У�������2����
	bz=0;
	if(r_sw[j].soesum>=1)
	{
		ts=asoe.tm-r_sw[j].soe[0].tm;
		m=ts.GetTotalSeconds();
		m=m<0 ? -m:m;
		if(m<=2) bz=1;
	}
	if(bz==1)
	{
		for(i=3;i>0;i--)
		{
			r_sw[j].soe[i]=r_sw[j].soe[i-1];
		}
	}else r_sw[j].soesum=0;

	r_sw[j].soe[0]=asoe;
	if(r_sw[j].soesum<3) r_sw[j].soesum++;
	r_sw[j].elg->vr.sta=asoe.sta;
	r_sw[j].elg->vr.ele=1;
	//���ض�������
	for(i=0;i<swsum-1;i++)
	{
		for(j=i;j<swsum;j++)
		{
			t1=r_sw[i].soe[0].tm;
			t2=r_sw[j].soe[0].tm;
			s1=r_sw[i].soe[0].ms;
			s2=r_sw[j].soe[0].ms;
			if(t1<t2||(t1==t2&&s1<s2))//����λ��
			{
				tmp=r_sw[i];
				r_sw[i]=r_sw[j];
				r_sw[j]=tmp;
			}
		}
	}
	n=0;
	for(i=0;i<swsum;i++)
	{
		if(r_sw[i].soesum!=0) n++;
		if(n>=10) break;
	}
	dbm.scf.swtsum=n;
	//��Ǵ���
	for(i=0;i<swsum;i++)
	{
		if(i<n) {r_sw[i].order=i;}
		if(i>=n){
			r_sw[i].order=-1;
			r_sw[i].soesum=0;
			if(i==0) MessageBox("i=0");
		}
	}
	/*CClientDC dc(0);
	char p[100];
	for(i=0;i<swsum;i++)
	{
		t1=r_sw[i].soe[0].tm;
		sprintf(p,"i=%d order=%d soesum=%d swtsum=%d  %d:%d:%d",i,r_sw[i].order,r_sw[i].soesum,n,t1.GetHour(),t1.GetMinute(),t1.GetSecond());
		dc.TextOut(10,10+i*20,p);



	}*/
}

//����Ѳ��ŵ�
void ScadaWin::CleaseSwtSoe()
{
	int i;
	for(i=0;i<swsum;i++)
	{
		r_sw[i].order=-1;
		r_sw[i].soesum=0;
		memset(r_sw[i].soe,0,4*sizeof(CTime));
	}
}


//������еĶ�·����������ʾ��־
void ScadaWin::CleaseDlFlash()
{
	int i;
	//������������־
	for(i=0;i<ppsum;i++)
	{
		r_ppie[i].ppe->showdl=0;
	}
	//��������ϵ�����
	for(i=0;i<swsum;i++)
	{
		r_sw[i].dl.enable=0;
		r_sw[i].order=-1;
		r_sw[i].dl.high=0;
	}
}
