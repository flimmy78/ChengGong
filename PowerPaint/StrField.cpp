// StrField.cpp: implementation of the StrField class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPaint.h"
#include "StrField.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StrField::StrField()
{
	fldsum=0;
}

StrField::~StrField()
{

}

//����һ���´��������������
int StrField::SetNewStr(char *str)
{
	char *lp;
	fldsum=1;
	lpt[0]=str; //��һ��Ϊ��ʼ��
	lp=str;
	for(;;)
	{
		if(*lp==0) break;
		if(*lp==',')
		{
			*lp=0;
			lp++;
			lpt[fldsum]=lp;
			fldsum++;
			continue;
		}
		lp++;
	}
	return fldsum;
}
