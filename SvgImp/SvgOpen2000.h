// SvgOpen2000.h: interface for the CSvgOpen2000 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGOPEN2000_H__AFC4AE20_4EFC_4FC4_9B3D_2179A45B961F__INCLUDED_)
#define AFX_SVGOPEN2000_H__AFC4AE20_4EFC_4FC4_9B3D_2179A45B961F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SvgBase.h"

class CSvgOpen2000 : public CSvgBase  
{
public:
	//����SVG�ļ�
	virtual BOOL SvgParse(char* pFile,SVG_PAGE* page);

	CSvgOpen2000();
	virtual ~CSvgOpen2000();
protected:

private:
	//ת��ͼ��
	virtual BOOL Translate(SVG_PAGE* page);
	//��̬ͼԪ����
	virtual BOOL PolyFigureGroup();
};

#endif // !defined(AFX_SVGOPEN2000_H__AFC4AE20_4EFC_4FC4_9B3D_2179A45B961F__INCLUDED_)
