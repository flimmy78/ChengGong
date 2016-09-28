// MemoryName.h: interface for the CMemoryName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_)
#define AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//using namespace std;
#include <vector>
#include <string>

typedef std::vector<std::string>  STRVTR;//�ִ�����

class CMemoryName  
{
public:
	//�����������
	void ResetName(){m_strVtr.clear();};
	//��������ָ��
	const char* GetNamePointer(char* pName);

	CMemoryName();
	virtual ~CMemoryName();
private:
	//�ַ�������
	STRVTR m_strVtr;
	//�����ֱȽ�
	static BOOL CompareByName(char* pOne,char* pTwo);

	const char* BinarySearch(char* pName);
};
 
#endif // !defined(AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_)
