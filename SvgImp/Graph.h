// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_)
#define AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Figure.h"

typedef struct METADATA
{
	METADATA(){memset(this,0,sizeof(METADATA));};

	char szID[GNAME_MAX];
	char szName[GNAME_MAX];
}METADATA;

class CGraph  
{
public:
	//���Ƕ��ͼ��
	void AddGraph(CGraph* pg){m_GraphVtr.push_back(pg);};
	//���ù����豸��Ϣ
	void SetPSRRef(const char* pID,const char* pName);
	//���ù���������Ϣ
	void SetMeasRef(const char* pID,const char* pName);
	//����ͼԪ
	void SetFigureGroup(CFigureGroup* pGroup){m_pGroup=pGroup;};
	//������
	void SetClass(CSS_STYLE* pClass){m_pClass=pClass;};
	//���ñ任����
	void SetFigureMatrix(MATRIX* pMatrix);
	//����ͼԪλ��
	void SetFigureRect(CRect* pRect);
	//��ӻ���ͼ��
	void AddFigure(CFigure figure){m_FigureVtr.push_back(figure);};

	const METADATA* GetPSRRef(){return m_pPSRRef;};
	const METADATA* GetMeasRef(){return m_pMeasRef;};
	const char* GetName(){return m_szName;};
	const MATRIX* GetMatrix(){return m_pMatrix;};
	const CRect* GetRect(){return m_pRect;};
	const CFigureGroup* GetFigureGroup(){return m_pGroup;};
	const CSS_STYLE* GetClass(){return m_pClass;};

	BOOL GetFirstFigure()
	{
		m_figitr=m_FigureVtr.begin();
		if(m_figitr!=m_FigureVtr.end()) 
			return TRUE;
		return FALSE;
	};
	CFigure* GetNextFigure();

	BOOL GetFirstGraph()
	{
		m_grpitr=m_GraphVtr.begin();
		if(m_grpitr!=m_GraphVtr.end()) 
			return TRUE;
		return FALSE;
	};
	CGraph* GetNextGraph();

	CGraph(const char* pName);
	virtual ~CGraph();
private:
	METADATA* m_pPSRRef;
	METADATA* m_pMeasRef;

	char m_szName[GNAME_MAX];

	MATRIX* m_pMatrix;	//�任����
	CRect* m_pRect;		//ͼ��λ�ã�ͼԪͼ�β���
	CFigureGroup* m_pGroup; //ͼԪͼ��
	CSS_STYLE* m_pClass;

	std::vector<CGraph*> m_GraphVtr;//Ƕ��ͼ��
	std::vector<CGraph*>::iterator m_grpitr;
	FIGUREVTR m_FigureVtr;	//����ͼ����
	FIGUREVTR::iterator m_figitr;
};
typedef std::vector<CGraph*> GRAPHVTR;

#endif // !defined(AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_)
