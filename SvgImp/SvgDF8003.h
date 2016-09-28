// SvgDF8003.h: interface for the CSvgDF8003 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGDF8003_H__656C82F5_15E1_40A1_BB76_6B786785E12D__INCLUDED_)
#define AFX_SVGDF8003_H__656C82F5_15E1_40A1_BB76_6B786785E12D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SvgBase.h"
class IXmlNode;

class CSvgDF8003 : public CSvgBase  
{
public:
	//����SVG�ļ�
	virtual BOOL SvgParse(char* pFile,SVG_PAGE* page);

	CSvgDF8003();
	virtual ~CSvgDF8003();
protected:

private:
	//ת��ͼ��
	virtual BOOL Translate(SVG_PAGE* page);
	//��̬ͼԪ����
	virtual BOOL PolyFigureGroup();
};

#endif // !defined(AFX_SVGDF8003_H__656C82F5_15E1_40A1_BB76_6B786785E12D__INCLUDED_)
