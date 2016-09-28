// XmlNode.h: interface for the CXmlNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_)
#define AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlTool.h"
#include "XmlItem.h"

class CXmlNode : public IXmlNode  
{
public:
	//�Ƿ������־
	BOOL IsEndFlag(char* pEnd);
	//ȡ����ֵ
	virtual const char* GetPropValue(const char* pName);
	//���ַ���ȡֵ
	virtual const char* GetValue();
	//ͨ����־�����ӽڵ�
	virtual IXmlNode* GetSubNodeByFlag(const char* pFlag,std::vector<IXmlNode*>* pSubVtr);
	//ͨ����־�����ӽڵ�ֵ
	virtual const char* GetSubValueByFlag(const char* pFlag);
	//�����׸��ӽڵ�λ��
	virtual int GetFirstSubNode();
	//���ص�ǰ�ӽڵ����һ���ӽڵ�λ��
	virtual IXmlNode* GetNextSubNode();
	//�����׸�����λ��
	virtual int GetFirstProp();
	//���ص�ǰ����
	virtual int GetNextProp(const char** pName,const char** pValue);
	//�Ƿ�ڵ��־
	virtual int IsKindof(const char* pFlag){if(strcmp(pFlag,m_pszFlag)==0) return TRUE;else return FALSE;};
	//���ر�־
	virtual const char* GetFlag(){return m_pszFlag;};

	//����ӽڵ�
	BOOL AddSubNode(CXmlNode* pNode);
	//���ýڵ�ֵ
	BOOL SetNodeValue(char* pValue);
	//���������Ŀ
	void AddPropItem(CXmlItem* pItem);
	//���ñ�־
	void SetNodeFlag(char* pFlag);

	//�������
	static void ClearNode();
	//����ڵ��ڴ�
	static CXmlNode* AllocNodeMem(char* pFlag);

	CXmlNode();
	CXmlNode(char* pFlag);
	virtual ~CXmlNode();
protected:
	//ͨ������ȡ����
	CXmlItem* GetPropByName(const char* pName);
	XMLITERATOR m_curitr;
	XMLITEMVTR::iterator m_propitr;

	const char* m_pszFlag;  //�ڵ��־
	char* m_pszValue;  //�ڵ�ֵ
	//char m_szValue[XMLVALUE_MAX];  //�ڵ�ֵ
	XMLNODEVTR m_SubVtr;//�ӽڵ�

	XMLITEMVTR m_propVtr;
private:
	static XMLNODEVTR m_MemNodeVtr;//�ڴ�ڵ�
	static CMemoryName m_MemNM;
	static CXmlNode* m_pMemNode;
	static int m_memindex;
};

#endif // !defined(AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_)
