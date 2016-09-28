// NetTpy.h: interface for the CNetTpy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETTPY_H__6FACA772_9C63_49E4_850A_A1D5A5CB5033__INCLUDED_)
#define AFX_NETTPY_H__6FACA772_9C63_49E4_850A_A1D5A5CB5033__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pwptdef.h"
#include "jhsyslibl.h"



class CNetTpy  
{
public:
	void CheckConlEle();
	void ComputLineSiteRt();
	void CreateNode();
	void SetConLine(RCONL *r_cl , int nCln);
	void SetLine(RFLOW	 *r_fw , int nLine);
	void SetBus(RBUS    *r_bs , int nBus);
	void SetDevice(RSTA  *r_st , int nDev);
	void FreeMem();
	CNetTpy();
	virtual ~CNetTpy();
	//���²�������ͼ��������ɫ
	C_BUS  *bus;		//ĸ��
	C_LINE *line;		//��·
	C_DEV  *dev;		//�豸
	C_CONLINE *conl;	//������
	C_NODE  *node;		//�ڵ�
	int bussum,linsum,devsum,colsum,nodsum;
private:
	bool GetNodeEle(int nodeid);
	void FindDevOthSite(C_DEV  &odev,int nodid);
	void SerachDev(int nodeid);
	void CreateEleIsland();
	void ReSetEle();
	double GetSiteWidth();
	int  AddANode();
	void AloteSite();
	void ConnectSite(CDRect rt, BYTE vl,int nodeid);
	double  fwidth;//���ҵ��Ŀ��

};

#endif // !defined(AFX_NETTPY_H__6FACA772_9C63_49E4_850A_A1D5A5CB5033__INCLUDED_)
