// Translator.h: interface for the CTranslator class.
//˵����������ҪΪDF8003���ף���ӦCSvgDF8003��������Ҫ�̳и�д
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_)
#define AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"

struct SVG_PAGE;
struct SVG_LAYER;
struct SVG_GRAPH;
struct SVG_ELEGRP;


class CTranslator  
{
public:
	//ת��ͼԪ
	virtual BOOL TranslateSymbol(FIGUREELEVTR* pEleGrpVtr);
	//��̬��ͼ��
	virtual BOOL LayerDynmic(CLayer *pLayer);
	//��̬��ͼ��
	virtual BOOL LayerCompensator(CLayer *pLayer);
	//�翹ͼ��
	virtual BOOL LayerReactor(CLayer *pLayer);
	//����ͼ��
	virtual BOOL LayerLoad(CLayer *pLayer);
	//������ͼ��
	virtual BOOL LayerPowerLine(CLayer *pLayer);
	//��բͼ��
	virtual BOOL LayerDisconnector(CLayer *pLayer);

	virtual BOOL LayerGroundDisconnector(CLayer *pLayer);
	//������ͼ��
	virtual BOOL LayerConnectLine(CLayer* pLayer);
	//����ͼ��
	virtual BOOL LayerBreaker(CLayer *pLayer);
	//�������ѹ��ͼ��
	virtual BOOL LayerTransformer2(CLayer *pLayer);
	//�������ѹ��ͼ��
	virtual BOOL LayerTransformer3(CLayer *pLayer);
	//ĸ��ͼ��
	virtual BOOL LayerBus(CLayer *pLayer);
	//�����ͼ��
	virtual BOOL LayerGenerator(CLayer *pLayer);
	//����ͼ��
	virtual BOOL LayerMeasure(CLayer *pLayer);
	//�ı�ͼ��
	virtual BOOL LayerText(CLayer *pLayer);
	//��ťͼ��
	virtual BOOL LayerButton(CLayer *pLayer);
	//ͷͼ��
	virtual BOOL LayerHead(CLayer *pLayer,CRect *pVBox);
	//һ��ͼ��
	virtual BOOL LayerGeneric(CLayer* pLayer);
	//ͨ��ͼԪͼ��ͼ��
	virtual BOOL LayerEleGeneric(CLayer *pLayer,unsigned char etype);

	CTranslator(SVG_PAGE* page);
	virtual ~CTranslator();
protected:
	void SetEleMatrixTfm(SVG_GRAPH* pGraph,MATRIX* pMatrix);
	//ͼԪͼ��
	virtual BOOL LayerEleGrp(CLayer* pLayer,unsigned char etype,MATRIX* pVbMatrix);
	//ת��һ��ͼԪ
	virtual BOOL TranslateSymGrp(CFigureGroup *pGroup,void* pSvgVtr);
	//�������ͼԪ
	SVG_GRAPH* GetEleGraph(CGraph* pGraph,unsigned char etype,MATRIX* pVbMatrix);
	//ͼԪ���
	unsigned long GetGraphID(){return ++m_lgid;};

	//SVG����ͼת��Ϊ���ӻ�����ͼ��
	virtual SVG_GRAPH* FigureToGraph(CFigure* pFigure,MATRIX* pMtx);
	//SVG����ͼת��Ϊ���ӻ�������
	virtual SVG_GRAPH* FigureToFlow(CFigure* pFigure,MATRIX* pMtx);
	//SVG����ͼ��ת��Ϊ���ӻ�������
	virtual SVG_GRAPH* FigureToConnect(CFigure* pFigure,MATRIX* pMtx);
	//SVG����ͼ����ת��Ϊ���ӻ�����ͼ��
	virtual BOOL CGraphToGraph(CGraph *pGraph, void* pSvgVtr,MATRIX* pMtx);
	//SVG����ͼ����ת��Ϊ���ӻ���ť
	virtual SVG_GRAPH* FigureToButton(CFigure* pFigure,MATRIX* pMtx);
	//SVG����ͼ����ת��Ϊģ����
	virtual SVG_GRAPH* FigureToAnalog(CGraph *pGraph, MATRIX *pMtx);
	//SVG����ͼ����ת��Ϊĸ��
	virtual SVG_GRAPH* FigureToBus(CGraph *pGraph, MATRIX *pMtx);

	//ת��Ϊϵͳ��ʶ��ĺ��ֿ���
	void ChangeFontFaceName(char *oldname,char *newname);
	//ȡ��ģ��������
	const char* GetAnalogAtr(const char *objectid,long &id,BYTE &type,BYTE &mode);

	//�����ͼ��ҳ
	SVG_PAGE* m_page;
	SVG_LAYER* m_pCurLayer;
private:
	unsigned long m_lgid;//ͼ��ID
	MATRIX m_vbMatrix;
};

#endif // !defined(AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_)
