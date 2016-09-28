// SvgBase.h: interface for the CSvgBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_)
#define AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\XmlTool\XmlTool.h"
#include "Translator.h"

struct SVG_PAGE;
struct PATHINFO	//·����Ϣ
{
	PATHINFO(){memset(this,0,sizeof(PATHINFO));};
	char cmd;//·������
	BYTE byCnt;//��������
	float argv[16];//����ֵ
};

class CSvgBase  
{
public:
	//����SVG�ļ�
	virtual BOOL SvgParse(char* pFile,SVG_PAGE* page)=0;

	CSvgBase();
	virtual ~CSvgBase();

protected:
	//����������
	virtual BOOL MainParse(IXmlNode* pNode);

	//****���뺯��*****//
	//���ر�������
	unsigned char GetCodeStyle(const char* pStyle){if(strcmp(pStyle,"UTF-8")==0) return 1;else return 0;};
	//������ͼ��
	virtual BOOL GetViewBox(const char* pView,CRect* pRect);
	//ȡ��ͼԪ
	virtual BOOL GetSymbol(IXmlNode* pNode);
	//��ѹ����
	virtual BOOL GetStyle(IXmlNode* pNode);
	//����ͼ��
	virtual BOOL GetLayer(IXmlNode* pNode);
	//����Ƕ��ͼ
	virtual BOOL GetGraph(IXmlNode *pNode,CGraph* pg);
	//����ͼ��
	virtual BOOL GetFigure(IXmlNode* pNode,FIGUREVTR* pFigVtr);
	//����use��ʶ��Ϣ
	virtual BOOL GetUse(IXmlNode* pNode,CGraph* pg);
	//����metadata��ʶ��Ϣ
	virtual BOOL GetMetaData(IXmlNode* pNode,CGraph* pg);

	//****�������ͼ��Ԫ��*****//
	//������
	virtual BOOL GetSvgLine(IXmlNode* pNode,G_LINE* pLine);
	//���ؾ���
	virtual BOOL GetSvgRect(IXmlNode* pNode,G_RECT* pRect);
	//��������
	virtual BOOL GetSvgPolyl(IXmlNode* pNode,G_POLYLINE* pPolyline);
	//���ض��
	virtual BOOL GetSvgPolyn(IXmlNode* pNode,G_POLYGON* pPolygon);
	//����Բ
	virtual BOOL GetSvgCircle(IXmlNode* pNode,G_CIRCLE* pCircle);
	//������Բ
	virtual BOOL GetSvgEllipse(IXmlNode* pNode,G_ELLIPSE* pEllips);
	//�����ı�
	virtual BOOL GetSvgText(IXmlNode* pNode,G_TEXT* pText);
	//����ͼ��
	virtual BOOL GetSvgImage(IXmlNode* pNode,G_IMAGE* pImage);
	//����·��
	virtual BOOL GetSvgPath(IXmlNode* pNode,G_PATH* pPath);
	//���ػ���ͼ������
	virtual BOOL GetSvgSymUse(IXmlNode* pNode,G_GUSE* pGUse);

	//����ͼ�α任����
	BOOL GetTransform(const char* pTrans,int len,MATRIX* pMatrix);
	//����·��ͼ��
	BOOL GetPathFigure(G_PATH *path,FIGUREVTR* pFigVtr);

	//****��������*****//
	//UTFתASCII
	int Utf8ToASCII(const unsigned char* pUtf,int len,char *pASCII,int maxbuf);
	//����class
	CSS_STYLE* SearchCssStyle(const char* pClass);
	//����ͼԪ
	CFigureGroup* SearchFigureGroup(const char* pid);
	//ͼ����,��״̬���ͼԪ
	BOOL PolyOneGroup(CFigureGroup* pGroup,char* pFalse,char* pTrue,FIGUREELE* pEle);
	//ͼ����,�๹�����ͼԪ
	BOOL PolyOneGroup(CFigureGroup* pGroup,FIGUREELE* pEle);


	//��ͼ����
	CRect m_viewBox;
	//���뷽ʽ0=ASCII,1=UTF8
	unsigned char m_byCode;
	//ͼԪ
	FIGUREELEVTR m_EleGrpVtr;
	//ͼԪ��
	FIGUREGRPVTR m_FigureGrpVtr;
	//���Ͷ����
	CSSSTYLEVTR m_CssStyleVtr;
	//ͼ���
	LAYERVTR m_LayerVtr;
	//ת����
	CTranslator* m_pTranslator;
private:
	//ȡ��·����Ϣ
	int GetPathInfo(const char* pPath,PATHINFO *pInfo, int max);
	//ת��ͼ��
	virtual BOOL Translate(SVG_PAGE* page)=0;
	//��̬ͼԪ����
	virtual BOOL PolyFigureGroup()=0;
	//��������ȡ�õ�ѹ�ȼ�
	virtual BOOL GetVolLevelByStyle(const char* pStype,BYTE &volLevel);
	//����RGB��ɫ
	DWORD GetRGB(const char* pRGB);
};

template<class T> int SplitStr(const char* pScr,char split,T* pRet,int count)
{
	int i=0;
	const char* pStart=pScr;
	char buffer[256];
	while(strlen(pStart)>0 && i<count)
	{
		char* pEnd=NULL;
		int len=strlen(pStart);		
		for(int j=0;j<len;j++)
		{
			if(pStart[j]==split || pStart[j]==' ')//Ĭ�Ͽո��Ƿָ��
			{
				pEnd=(char*)&pStart[j];
				break;
			}
		}

		len=pEnd-pStart;
		if(pEnd!=NULL && len<256 && len>0)
		{
			strncpy(buffer,pStart,len);
			buffer[len]=0;
			pRet[i++]=(T)atof(buffer);
			pEnd++;
			pStart=pEnd;
		}
		else
		{
			pRet[i++]=(T)atof(pStart);
			break;
		}
	}
	return i;
}

#endif // !defined(AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_)
