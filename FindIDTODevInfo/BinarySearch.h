// BinarySearch.h: interface for the CBinarySearch class.
//���������ַ������ֻ����ֲ���
//���ߣ���ǿ zhqi_ang@yeah.net
//���ڣ�2009.7.1
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_)
#define AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdio.h"
#include <afx.h>

#include <vector>
#include <algorithm>

struct BINARYMAP
{
	BINARYMAP(){memset(this,0,sizeof(BINARYMAP));};
	int NU;		//���
	char szName[32];//����
	void* pRec;//��¼
	int idx;
};
typedef std::vector<BINARYMAP*> BMAPVTR;

enum SORTTYPE
{
	SORT_UN=0, //δ����
	SORT_NM=1, //����������
	SORT_ID=2  //��ID����
};

class CBinarySearch  
{
public:
	//���ò���
	void ResetSearch();
	//���Ӱ�����
	BINARYMAP* AddMap(char* pName,void* pMap,int idx=0);
	//���Ӱ�����
	void AddMap(int NU,char* pName,void* pMap,int idx=0);
	//�����ֲ��ҷ��ؼ�¼
	void* Search(const char* pName);
	//����ŷ��ؼ�¼
	void* Search(int NU);

	CBinarySearch();
	virtual ~CBinarySearch();
private:
	//�Ƚ�����map�����֣�������
	static int CmpSearchByName(BINARYMAP* pOne,BINARYMAP* pTwo);
	//�Ƚ�����map����ţ�������
	static int CmpSearchByNU(BINARYMAP* pOne,BINARYMAP* pTwo);
	//�����ֱȽϣ�������
	static int CmpMapByName(BINARYMAP* pMap,const char* pName);
	//����űȽϴ�С��������
	static int CmpMapByIndex(BINARYMAP* pOne,int NU);

	BMAPVTR m_MapVtr;
	int m_iIndex;
	//��������
	SORTTYPE m_SortType;
};

#endif // !defined(AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_)
