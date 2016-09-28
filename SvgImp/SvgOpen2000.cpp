// SvgOpen2000.cpp: implementation of the CSvgOpen2000 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SvgOpen2000.h"
#include "TranslatorNR.h"

extern const char* svgkey[];
extern const char* cgekey[];
extern const char* graphkey[];
extern const char* atrkey[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSvgOpen2000::CSvgOpen2000()
{

}

CSvgOpen2000::~CSvgOpen2000()
{

}

BOOL CSvgOpen2000::SvgParse(char *pFile,SVG_PAGE* page)
{
	if(pFile==NULL)
		return FALSE;

	BOOL bResult=TRUE;
	XMLNODEVTR *ndvtr=NULL;
	if(XMLAPI_Parse(pFile,&ndvtr))
	{
		const char* pVal=NULL;
		IXmlNode* pNode=NULL;
		for(XMLITERATOR itr=ndvtr->begin();itr!=ndvtr->end();++itr)
		{
			pNode=(*itr);
			if(pNode->IsKindof(svgkey[0]))//?xml
			{
				pVal=pNode->GetPropValue("encoding");
				m_byCode=GetCodeStyle(pVal);
			}
			else if(pNode->IsKindof(svgkey[1]))//SVG
			{
				pVal=pNode->GetPropValue("viewBox");
				if(!GetViewBox(pVal,&m_viewBox))
				{
					bResult=FALSE;
					break;
				}

				if(pNode->GetFirstSubNode())
				{
					IXmlNode* pSubNode=NULL;
					while((pSubNode=pNode->GetNextSubNode())!=NULL)
					{
						if(pSubNode->IsKindof(svgkey[2]) == 0)
						{
							if(pSubNode->GetFirstSubNode())
							{
								IXmlNode* pGrand=NULL;
								while(pGrand=pSubNode->GetNextSubNode())
								{
									if(!MainParse(pGrand))
									{
										bResult=FALSE;
										break;
									}
								}
							}
						}
					}
				}

			}
		/*	else
			{
				if(!MainParse(pNode))
					bResult=FALSE;
			}*/
		}
		XMLAPI_Release(ndvtr);
	}

	if(bResult)//ת��
	{
		bResult=Translate(page);
	}
	return bResult;
}


//ת��ͼ��
BOOL CSvgOpen2000::Translate(SVG_PAGE* page)
{
	if(m_pTranslator!=NULL)
		delete m_pTranslator;
	m_pTranslator=new CTranslatorNR(page);

	//ͼԪ����
	m_pTranslator->TranslateSymbol(&m_EleGrpVtr);
	for(LAYERVTR::iterator itr=m_LayerVtr.begin();itr!=m_LayerVtr.end();++itr)
	{
		const char* pName=(*itr)->GetLayerName();
		if(pName==NULL || strlen(pName)==0)
			continue;

		CLayer* pLayer=(*itr);
		//Head_Layer...........ͷ��
		if(strcmp(pName,"Head_Layer")==0)
			m_pTranslator->LayerHead(pLayer,&m_viewBox);
		//Measure_Layer....����ͼ��
		else if(strcmp(pName,"MeasurementValue_Layer")==0)
			m_pTranslator->LayerMeasure(*itr);
		//Text_Layer...........�ı�ͼ��
		else if(strcmp(pName,"Text_Layer")==0)
			m_pTranslator->LayerText(*itr);
		//PowerLine_Layer......�����ͼ��
		else if(strcmp(pName,"ACLine_Layer")==0)
			m_pTranslator->LayerPowerLine(*itr);
		//PowerTransformer_Layer��ѹ��ͼ��
		else if(strcmp(pName,"Transformer_Layer")==0)
			m_pTranslator->LayerTransformer2(*itr);
		else if(strcmp(pName,"Transformer3_Layer")==0)
			m_pTranslator->LayerTransformer3(*itr);
		//Button_Layer....��ťͼ��
		else if(strcmp(pName,"Other_Layer")==0)
			m_pTranslator->LayerButton(*itr);
		//Breaker_Layer........��·��ͼ��
		else if(strcmp(pName,"Breaker_Layer")==0)
			m_pTranslator->LayerBreaker(*itr);
		//Switch_Layer.........����ͼ��
		else if(strcmp(pName,"Disconnector_Layer")==0)
			m_pTranslator->LayerDisconnector(*itr);
		//Generator_Layer......�����ͼ��
		else if(strcmp(pName,"Generator_Layer")==0)
			m_pTranslator->LayerGenerator(*itr);
		//Reactor_Layer........�翹����
		else if(strcmp(pName,"Reactor_Layer")==0)
			m_pTranslator->LayerReactor(*itr);
		//ConnectLine_Layer....������ͼ��
		else if(strcmp(pName,"Link_Layer")==0)
			m_pTranslator->LayerConnectLine(*itr);
		//Load_Layer............����ͼ��
		else if(strcmp(pName,"Load_Layer")==0)
			m_pTranslator->LayerLoad(*itr);
		//DynamicPoint_Layer...��̬��ͼ��
		else if(strcmp(pName,"DynamicPoint_Layer")==0)
			m_pTranslator->LayerDynmic(*itr);
		//Compensator_Layer....��������
		else if(strcmp(pName,"Compensator_Layer")==0)
			m_pTranslator->LayerCompensator(*itr);
		//Bus_Layer............ĸ��ͼ��
		else if(strcmp(pName,"Bus_Layer")==0)
			m_pTranslator->LayerBus(*itr);
		else
			m_pTranslator->LayerGeneric(*itr);
	}
	
	return TRUE;
}

//��̬ͼԪ����
BOOL CSvgOpen2000::PolyFigureGroup()
{
	return TRUE;
}

