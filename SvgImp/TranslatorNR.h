// TranslatorNR.h: interface for the CTranslatorNR class.
//˵����������ҪΪOPEN2000���ף���ӦCSvgOpen2000��������Ҫ�̳и�д
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATORNR_H__E9C21524_9FEE_42C0_80D4_26C6CFDDC012__INCLUDED_)
#define AFX_TRANSLATORNR_H__E9C21524_9FEE_42C0_80D4_26C6CFDDC012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Translator.h"

class CTranslatorNR : public CTranslator  
{
public:
	CTranslatorNR(SVG_PAGE* page);
	virtual ~CTranslatorNR();

};

#endif // !defined(AFX_TRANSLATORNR_H__E9C21524_9FEE_42C0_80D4_26C6CFDDC012__INCLUDED_)
