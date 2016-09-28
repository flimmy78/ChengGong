// XmlParse.h: interface for the CXmlParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_)
#define AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlNode.h"

const int BRACKET_MAXLEN=2048;  //������������󳤶�

class CXmlParse  
{
public:
	BOOL NodeParse(CXmlNode* pNodeParent);
	//����XML�ַ���
	BOOL ParseXml(const char* pXmlStr,int len,const char* pRoot=NULL);
	//����XML�ļ�
	BOOL ParseXml(const char* pXmlFile,const char* pRoot=NULL);

	CXmlParse(XMLNODEVTR* pNodeVtr);
	virtual ~CXmlParse();
private:
	//ȡ����������
	CXmlNode* GotoBracket(int &end);
	//���ַ�λ��
	int GotoChar(const char end,char* pStr,int  max);
	//����������
	BOOL MainParse(const char* pRoot=NULL);
	//ȡ��һ���ַ�
	int GetChar();

	XMLNODEVTR* m_pNodeVtr;

	char m_Buffer[BRACKET_MAXLEN];
	const char *m_pSrc; //Դ��
	char *m_pCur; //��ǰλ��
	int m_iSrcLen; //Դ����
	FILE* m_pf; //�ļ�ָ��
};

#endif // !defined(AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_)
