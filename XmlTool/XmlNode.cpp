// XmlNode.cpp: implementation of the CXmlNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlNode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemoryName CXmlNode::m_MemNM;
XMLNODEVTR CXmlNode::m_MemNodeVtr;//�ڴ�ڵ�
CXmlNode* CXmlNode::m_pMemNode=NULL;
int CXmlNode::m_memindex=0;

CXmlNode::CXmlNode(char* pFlag)
{
	if(pFlag[0]=='/')
		m_pszFlag=m_MemNM.GetNamePointer(pFlag+1);
	else
		m_pszFlag=m_MemNM.GetNamePointer(pFlag);

	m_pszValue=NULL;
	m_curitr=NULL;
	m_propitr=NULL;

	//memset(m_szValue,0,XMLVALUE_MAX);
}

CXmlNode::CXmlNode()
{
	m_pszFlag=NULL;
	m_pszValue=NULL;
	m_curitr=NULL;
	m_propitr=NULL;
	//memset(m_szValue,0,XMLVALUE_MAX);
}

CXmlNode::~CXmlNode()
{
	if(m_pszValue!=NULL)
	{
		delete []m_pszValue;
		m_pszValue=NULL;
	}

	//for(XMLITEMVTR::iterator i=m_propVtr.begin();i!=m_propVtr.end();++i)
	//	delete (*i);
	m_propVtr.clear();

	//for(XMLNODEVTR::iterator j=m_SubVtr.begin();j!=m_SubVtr.end();++j)
	//	delete (*j);
	m_SubVtr.clear();
}

//ȡ����ֵ
const char* CXmlNode::GetPropValue(const char* pName)
{
	CXmlItem* pItem=GetPropByName(pName);
	if(pItem==NULL)
		return NULL;

	return pItem->GetValue();
}

//���ַ���ȡֵ
const char* CXmlNode::GetValue()
{
	if(m_pszValue!=NULL)
		return m_pszValue;
	//else if(strlen(m_szValue)>0)	
	//	return m_szValue;
	return NULL;
}

//ͨ����־�����ӽڵ�
IXmlNode* CXmlNode::GetSubNodeByFlag(const char* pFlag,std::vector<IXmlNode*>* pSubVtr)
{
	for(XMLNODEVTR::iterator j=m_SubVtr.begin();j!=m_SubVtr.end();++j)
	{
		if((*j)->IsKindof(pFlag))
		{
			if(pSubVtr!=NULL)
				pSubVtr->push_back(*j);
			else
				return (*j);
		}
	}
	return NULL;
}

//ͨ����־�����ӽڵ�ֵ
const char* CXmlNode::GetSubValueByFlag(const char* pFlag)
{
	IXmlNode* pNode=GetSubNodeByFlag(pFlag,NULL);
	if(pNode!=NULL)
		return pNode->GetValue();
	else
		return NULL;
}

//�����׸��ӽڵ�λ��
int CXmlNode::GetFirstSubNode()
{
	if(m_SubVtr.size()==0)
		return FALSE;
	m_curitr=m_SubVtr.begin();
	return TRUE;
}

//���ص�ǰ�ӽڵ����һ���ӽڵ�λ��
IXmlNode* CXmlNode::GetNextSubNode()
{
	if(m_curitr==NULL)
		return NULL;
	if(m_curitr!=m_SubVtr.end())
	{
		IXmlNode* pNode=*m_curitr;
		m_curitr++;
		return pNode;
	}
	else 
		return NULL;
}

//����ӽڵ�
BOOL CXmlNode::AddSubNode(CXmlNode* pNode)
{
	if(m_pszValue!=NULL)
	{
		delete []m_pszValue;
		m_pszValue=NULL;
	}

	m_SubVtr.push_back(pNode);
	return TRUE;
}

//���ýڵ�ֵ
BOOL CXmlNode::SetNodeValue(char* pValue)
{
	//if(strlen(pValue)>=XMLVALUE_MAX)
	//{
		if(m_pszValue!=NULL)
			delete []m_pszValue;
		m_pszValue=new char[strlen(pValue)+1];
		strcpy(m_pszValue,pValue);
	/*}
	else
		strcpy(m_szValue,pValue);*/

	return TRUE;
}

//���������Ŀ
void CXmlNode::AddPropItem(CXmlItem* pItem)
{
	m_propVtr.push_back(pItem);
}

//ͨ������ȡ����
CXmlItem* CXmlNode::GetPropByName(const char* pName)
{
	for(XMLITEMVTR::iterator i=m_propVtr.begin();i!=m_propVtr.end();++i)
	{
		if(strcmp((*i)->GetName(),pName)==0)
			return *i;
	}
	return NULL;
}

BOOL CXmlNode::IsEndFlag(char *pEnd)
{
	if(strlen(pEnd)==0)
		return FALSE;

	char* pStart=pEnd;
	while(pStart[0]==' ' && pStart[0]!=0)
		pStart++;

	if(pStart[0]=='/')
		pStart++;
	if(strlen(pStart)>0)
	{
		if(strcmp(m_pszFlag,pStart)==0)
			return TRUE;
	}
	return FALSE;
}

	//�����׸�����λ��
int CXmlNode::GetFirstProp()
{
	m_propitr=m_propVtr.begin();
	if(m_propitr==m_propVtr.end())
		return FALSE;
	else
		return TRUE;
}
	//���ص�ǰ����
int CXmlNode::GetNextProp(const char** pName,const char** pValue)
{
	if(m_propitr==NULL)
		return NULL;
	if(m_propitr!=m_propVtr.end())
	{
		CXmlItem* pItem=*m_propitr;
		m_propitr++;
		*pName=pItem->GetName();*pValue=pItem->GetValue();
		if(*pName!=NULL && *pValue!=NULL)
			return TRUE;
		else
			return FALSE;
	}
	else 
		return 0;
}

//���ñ�־
void CXmlNode::SetNodeFlag(char* pFlag)
{
	if(pFlag[0]=='/')
		m_pszFlag=m_MemNM.GetNamePointer(pFlag+1);
	else
		m_pszFlag=m_MemNM.GetNamePointer(pFlag);
}

CXmlNode* CXmlNode::AllocNodeMem(char* pFlag)
{
	CXmlNode* pNode=NULL;
	if(m_memindex==0)
	{
		m_pMemNode=new CXmlNode[32];
		m_MemNodeVtr.push_back(m_pMemNode);
	}
	
	if(strlen(pFlag)>0)
	{
		pNode=&m_pMemNode[m_memindex++];
		pNode->SetNodeFlag(pFlag);
	}
	if(m_memindex>=32)
		m_memindex=0;
	return pNode;
}

void CXmlNode::ClearNode()
{
	m_pMemNode=NULL;
	m_memindex=0;
	for(XMLNODEVTR::iterator j=m_MemNodeVtr.begin();j!=m_MemNodeVtr.end();++j)
		delete [](*j);
	m_MemNodeVtr.clear();
	m_MemNM.ResetName();
};
