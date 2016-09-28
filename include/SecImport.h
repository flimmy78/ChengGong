// SecImport.h: interface for the SecImport.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_)
#define AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786) 

#include <vector>
#include <string>
using namespace std;

//ȡ�ö�������
int __stdcall GetSectionList(const char* pSecFile,vector<string> &secVtr);
//���������Ϣ
int __stdcall ImportSection(const void* pImport,long tStart);
//��������ӳ�䵽�����(bySect=0:SCADA���棬bySect=1:״̬���ƶ��棬bySect=2:��������)
int __stdcall MapSectionToObj(const void* pDB,unsigned char bySect);

#endif // !defined(AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_)
