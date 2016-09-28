// SvgImp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SvgImp.h"
#include "SvgDF8003.h"
#include "SvgOpen2000.h"

//SVG���뺯��
SVGIMP_API int SvgImport(char* pSvgFile,char* pStyle,SVG_PAGE** page)
{
	*page=new SVG_PAGE;
	if(strcmp(pStyle,"Open2000")==0)//DF8003
	{
		CSvgDF8003 df8003;
		BOOL bRet = df8003.SvgParse(pSvgFile,*page);
		return bRet;
	}
	else if(strcmp(pStyle,"Open2000")==0)
	{
		CSvgOpen2000 op2000;
		return op2000.SvgParse(pSvgFile,*page);
	}
	return 0;
}

//�ͷ�SVG_PAGE����
SVGIMP_API void ReleaseSvgPage(SVG_PAGE* page)
{
	if(page!=NULL)
	{
		//�ͷ����ͼԪ
		for(SVGELEGRPVTR::iterator i=page->egrpVtr.begin();i!=page->egrpVtr.end();++i)
		{
			SVG_ELEGRP* pGrp=*i;
			//״̬һͼԪ
			for(SVGGRAPHVTR::iterator j=pGrp->g1Vtr.begin();j!=pGrp->g1Vtr.end();++j)
			{
				delete [](*j)->graph;
				delete (*j);
			}
			pGrp->g1Vtr.clear();

			//״̬��ͼԪ
			for(j=pGrp->g2Vtr.begin();j!=pGrp->g2Vtr.end();++j)
			{
				delete [](*j)->graph;
				delete (*j);
			}
			pGrp->g2Vtr.clear();

			delete pGrp;
		}

		//�ͷ�ͼ��
		for(int k=0;k<page->laynum;k++)
		{
			for(SVGGRAPHVTR::iterator j=page->layer[k].gVtr.begin();j!=page->layer[k].gVtr.end();++j)
			{
				delete [](*j)->graph;
				delete (*j);
			}
			page->layer[k].gVtr.clear();
		}
		delete page;
	}
}

