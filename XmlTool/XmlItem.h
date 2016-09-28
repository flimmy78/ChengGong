// XmlItem.h: interface for the CXmlItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLITEM_H__7443A91E_CDDD_4E79_916E_E2773FB66242__INCLUDED_)
#define AFX_XMLITEM_H__7443A91E_CDDD_4E79_916E_E2773FB66242__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MemoryName.h"

#define IsEnd(c)	(c=='\0')
#define IsNumber(c)	((c<='9' && c>='0') || c=='.')
#define IsLetter(c)	(c<='Z' && c>='A')||(c<='z' && c>='a')

const int XMLVALUE_MAX=32;//���ֵ����

class CXmlItem  
{
public:
	//���ַ���ȡֵ
	const char* GetValue(){return m_pValue;/*m_szValue;*/};
	//ȡ��
	const char* GetName(){return m_pszName;};
	//��ֵ�Ƿ�����
	BOOL ValIsNumber();
	//��������ֵ
	void SetItem(char* pszItem,char* pszVal);

	//�������
	static void ClearItem();
	//���ؿ���
	static CXmlItem* AllocItemMem(char* pszItem,char* pszVal);

	CXmlItem();
	CXmlItem(char* pszItem,char* pszVal);
	virtual ~CXmlItem();
private:
	static std::vector<CXmlItem*> m_MemItemVtr;
	static CMemoryName m_MemNM;
	static CXmlItem* m_pMemItem;
	static int m_memindex;

	const char* m_pszName;  //��������
	//char m_szValue[XMLVALUE_MAX];  //������ֵ
	char* m_pValue;
};

typedef std::vector<CXmlItem*> XMLITEMVTR;

#endif // !defined(AFX_XMLITEM_H__7443A91E_CDDD_4E79_916E_E2773FB66242__INCLUDED_)
