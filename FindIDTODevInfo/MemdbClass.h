// MemdbClass.h: interface for the CMemdbClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_)
#define AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemdbClass  
{
public:
	CMemdbClass();
	virtual ~CMemdbClass();

	bool GetMemdata(LPCSTR pmemtype,LPCSTR ptablename);		//ȡ�ڴ������
public:
	char* m_memdata;		//�ڴ�ⷵ������ָ���ַ,����ʱ���õ�ַ�任Ϊʵ���豸����ʹ��
	MEMTABLE* m_memtable;	//��ǰ�豸�ڴ������ṹ
	int m_datatnum;			//��ǰ�����������

private:

};

void* GetMemTable(char* pDB,char* table,MEMTABLE**  pTable);

#endif // !defined(AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_)
