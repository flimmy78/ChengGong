// Figure.h: interface for the CFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGURE_H__0807DE32_0E97_4DB2_A39D_835836DC5D37__INCLUDED_)
#define AFX_FIGURE_H__0807DE32_0E97_4DB2_A39D_835836DC5D37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*#if !defined(__cplusplus)
    #define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
    extern "C++"
    {
		template <typename _CountofType, size_t _SizeOfArray>
			char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
		#define _countof(_Array) sizeof(*__countof_helper(_Array))
    }
#endif*/

#include <vector>
#include <math.h>
#include <jhsyslibL.h>

const double PI=3.1415926535;

const POINT ZEROPT=CPoint(0,0); 
const int GNAME_MAX=64; //������Ƴ���
const int LEFT_SHIFT00=1; //����0λ
const int LEFT_SHIFT01=1<<1; //
const int LEFT_SHIFT02=1<<2; //
const int LEFT_SHIFT03=1<<3; //
const int LEFT_SHIFT04=1<<4; //
const int LEFT_SHIFT05=1<<5; //
const int LEFT_SHIFT06=1<<6; //
const int LEFT_SHIFT07=1<<7; //
const int LEFT_SHIFT08=1<<8; //
const int LEFT_SHIFT09=1<<9; //
const int LEFT_SHIFT10=1<<10; //
const int LEFT_SHIFT11=1<<11; //
const int LEFT_SHIFT12=1<<12; //
const int LEFT_SHIFT13=1<<13; //
const int LEFT_SHIFT14=1<<14; //
const int LEFT_SHIFT15=1<<15; //����15λ

typedef struct MATRIX //����ṹ
{
	MATRIX(){memset(this,0,sizeof(MATRIX));fa=1.0f;fd=1.0f;};	
	float fa;
	float fb;
	float fc;
	float fd;
	float fe;
	float ff;
}MATRIX;

enum GTYPE
{
	GTYPE_LINE=0,	//��
	GTYPE_POLYL=1,	//����
	GTYPE_PATH=2,	//·��
	GTYPE_POLYG=3,	//�����
	GTYPE_RECT=4,	//����
	GTYPE_CIRCLE=5, //Բ
	GTYPE_ELLIPSE=6,//��Բ
	GTYPE_TEXT=7,   //�ı�
	GTYPE_IMAGE=8, //ͼ��
	GTYPE_GUSE=9, //ʹ������ͼ��
	GTYPE_ARC=10, //��
	GTYPE_UNKWN=255  //δ֪
};

//SVG����ͼ��*************************��ʼ
typedef struct G_LINE//SVG��
{
	G_LINE(){memset(this,0,sizeof(G_LINE));};	
	POINT sp;
	POINT ep;
	float swidth;
	DWORD lcolor; 
	MATRIX mx;	//�任����
	unsigned int check;//У��ǰ��������Ƿ���Ч��ÿ��ȡ�ص����Բ�һ��ȫ
}SVG_LINE;

typedef struct G_RECT//rect����
{
	G_RECT(){memset(this,0,sizeof(G_RECT));};	
	POINT lt;
	float height;
	float width;
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	MATRIX mx;	//�任����
	unsigned int check;
	unsigned char full;
}G_RECT;

typedef struct G_POLYLINE//polyline����
{
	G_POLYLINE(){memset(this,0,sizeof(G_POLYLINE));};	
	POINT pt[1500];
	int ptnum;
	float swidth;
	DWORD lcolor;
	MATRIX mx;	//�任����
	unsigned int check;
}G_POLYLINE;

typedef struct G_POLYGON//polygon�����
{
	G_POLYGON(){memset(this,0,sizeof(G_POLYGON));};	
	POINT pt[1500];
	int ptnum;
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	MATRIX mx;	//�任����
	unsigned int check;
}G_POLYGON;

typedef struct G_CIRCLE//circleԲ
{
	G_CIRCLE(){memset(this,0,sizeof(G_CIRCLE));};
	POINT cp;
	float r;
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	MATRIX mx;	//�任����
	unsigned int check;
}G_CIRCLE;

typedef struct G_ELLIPSE//ellipse��Բ
{
	G_ELLIPSE(){memset(this,0,sizeof(G_ELLIPSE));};	
	POINT cp;
	float rx;
	float ry;
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	MATRIX mx;	//�任����
	unsigned int check;
}G_ELLIPSE;

typedef struct G_TEXT//text�ı�
{
	G_TEXT(){memset(this,0,sizeof(G_TEXT));};	
	POINT lt;
	char szText[256];
	char lfFace[16];
	int  fsize;
	DWORD lcolor;
	DWORD fcolor;
	BYTE wmode;
	unsigned char italic;
	unsigned char underline;
	MATRIX mx;	//�任����
	unsigned int check;
}G_TEXT;


typedef struct G_PATH//path·��
{
	G_PATH(){memset(this,0,sizeof(G_PATH));};	
	char szPath[256];
	char rclass[32];
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	MATRIX mx;	//�任����
	unsigned int check;
}G_PATH;

typedef struct G_IMAGE//imageͼ��
{
	G_IMAGE(){memset(this,0,sizeof(G_IMAGE));};
	POINT lt;
	float height;
	float width;
	char href[256];
	float fscan;
	float fangle;
	MATRIX mx;	//�任����
	unsigned int check;
}G_IMAGE;

typedef struct G_ARC//����
{
	G_ARC(){memset(this,0,sizeof(G_ARC));};	
	POINT sp;
	float rx;
	float ry;
	float xaixsr;//��X��ת
	unsigned char larc;//��Ǳ�־
	unsigned char sweep;//ʱ�뷽���־
	POINT ep;
	float swidth;
	DWORD lcolor;
	DWORD fcolor;
	POINT center;
	MATRIX mx;	//�任����
	unsigned int check;
}G_ARC;

typedef struct G_GUSE//ʹ������ͼ��
{
	G_GUSE(){memset(this,0,sizeof(G_GUSE));};	
	POINT lt;
	void* use;	//ͼԪָ��
	MATRIX mx;	//�任����
	unsigned int check;
}G_GUSE;
//SVG����ͼ��*************************����

typedef struct CSS_STYLE//css����
{
	CSS_STYLE(){memset(this,0,sizeof(CSS_STYLE));};	
	std::string descr;
	DWORD lcolor;
	DWORD fcolor;
	unsigned char vVol;
}CSS_STYLE;
typedef std::vector<CSS_STYLE> CSSSTYLEVTR;

//�������������ǽṹ��ҪΪ�����ͷ��ڴ�
class CFigure  
{
public:
	BOOL SetFullColor(DWORD color);
	//������ɫ
	BOOL SetColor(DWORD color);
	//����ͼ��
	BOOL GetRect(CRect &rt);
	//��������
	GTYPE IsKindOf(){return m_type;};
	//����ͼ��
	int GetFigure(void* pFigure,int size){ 
		if(size==m_size){
			memcpy(pFigure,m_pGraph,m_size);return TRUE;}
		else return FALSE;};
	const char* GetHref(){return m_phref;};
	//���ó�����
	void SetHref(const char* phref);
	//������
	void SetClass(CSS_STYLE* pClass){m_pClass=pClass;};
	//������
	const CSS_STYLE* GetClass(){return m_pClass;};

	CFigure(const CFigure& figure);
	CFigure(GTYPE type,void* pFigure,int size);
	virtual ~CFigure();
private:
	GTYPE m_type;
	int m_size;
	unsigned char* m_pGraph;
	char* m_phref;
	CSS_STYLE* m_pClass;
};
typedef std::vector<CFigure> FIGUREVTR;

inline CFigure::CFigure(GTYPE type,void* pFigure,int size)
{
	m_phref=NULL;
	m_type=type;
	m_size=size;
	m_pGraph=new unsigned char[size];
	memcpy(m_pGraph,pFigure,size);
	m_pClass=NULL;
};

inline CFigure::CFigure(const CFigure& figure)
{
	m_type=figure.m_type;
	m_size=figure.m_size;
	m_pClass=figure.m_pClass;
	if(m_size>0)
	{
		m_pGraph=new unsigned char[m_size];
		memcpy(m_pGraph,figure.m_pGraph,m_size);
	}
	else
		m_pGraph=NULL;
	if(figure.m_phref!=NULL)
	{
		int len=strlen(figure.m_phref);
		if(len>0)
		{
			m_phref=new char[len+1];
			strcpy(m_phref,figure.m_phref);
		}
	}
	else
		m_phref=NULL;
};

inline CFigure::~CFigure()
{
	if(m_pGraph!=NULL){
		delete []m_pGraph;
		m_pGraph=NULL;}
	m_size=0;
	if(m_phref!=NULL){
		delete []m_phref;
		m_phref=NULL;}
};


inline void CFigure::SetHref(const char* phref)
{
	if(m_phref!=NULL){
		delete []m_phref;} 
	m_phref=new char[strlen(phref)+1];
	strcpy(m_phref,phref);
};

class CFigureGroup
{
public:
	BOOL SetGroupFullColor(DWORD color);
	BOOL SetGroupColor(DWORD color);
	//���ͼ��
	void AddFigure(CFigure figure);
	//������λ�þ���
	void GetGroupRect(CRect &rt){rt=m_rt;};
	//������λ�þ���
	void SetGroupRect(CRect* pRt){m_rt=*pRt;};
	//��������
	const char* GetGroupName(){return m_szName;};
	//�Ƚ�����
	int CompareName(const char* pName){return strcmp(m_szName,pName);};
	
	BOOL GetFirstFigure(){m_figitr=m_FigureVtr.begin();if(m_figitr!=m_FigureVtr.end()) return TRUE;return FALSE;};
	CFigure* GetNextFigure();

	void* m_pGroupParent;

	CFigureGroup(const char* pName){m_figitr=NULL;m_pGroupParent=NULL;strcpy(m_szName,pName);};
	virtual ~CFigureGroup(){m_FigureVtr.clear();};
private:
	char m_szName[GNAME_MAX];
	FIGUREVTR m_FigureVtr;
	FIGUREVTR::iterator m_figitr;
	CRect m_rt;
};
typedef std::vector<CFigureGroup*> FIGUREGRPVTR;

inline void CFigureGroup::AddFigure(CFigure figure)
{
	CRect rt;
	if(figure.GetRect(rt)){
		rt.NormalizeRect();
		if(m_FigureVtr.size()==0)
			m_rt=rt;
		else
		{
			POINT ltp,rbp;
			ltp.x=rt.left<m_rt.left?rt.left:m_rt.left;
			ltp.y=rt.top<m_rt.top?rt.top:m_rt.top;
			rbp.x=rt.right>m_rt.right?rt.right:m_rt.right;
			rbp.y=rt.bottom>m_rt.bottom?rt.bottom:m_rt.bottom;

			m_rt=CRect(ltp,rbp);
		}
		m_rt.NormalizeRect();
	}
	if(strstr(m_szName,"transformer")!=NULL)
		figure.SetColor(RGB(255,255,255));
	m_FigureVtr.push_back(figure);

}

inline BOOL CFigureGroup::SetGroupColor(DWORD color)
{
	if(!GetFirstFigure())
		return FALSE;
	CFigure* pFigure=NULL;
	while((pFigure=GetNextFigure())!=NULL)
	{
		pFigure->SetColor(color);
	}
	return TRUE;
}

inline BOOL CFigureGroup::SetGroupFullColor(DWORD color)
{
	if(!GetFirstFigure())
		return FALSE;
	CFigure* pFigure=NULL;
	while((pFigure=GetNextFigure())!=NULL)
	{
		pFigure->SetFullColor(color);
	}
	return TRUE;
}

inline CFigure* CFigureGroup::GetNextFigure()
{
	CFigure* pFigure=NULL;
	if(m_figitr!=NULL && m_figitr!=m_FigureVtr.end())
	{
		pFigure=(CFigure*)&(*m_figitr);
		m_figitr++;
	}
	return pFigure;
}

void PPOffset(POINT* pOffset,POINT *pt, int num);
inline void PPOffset(POINT* pOffset,POINT *pt, int num)
{
	if(pOffset==NULL || pt==NULL || num==0)
		return;
	if(pOffset->x!=0 || pOffset->y!=0)
	{
		for(int i=0;i<num;i++)
		{
			pt[i].x=pt[i].x-pOffset->x;
			pt[i].y=pt[i].y-pOffset->y;
		}
	}
}

//��ľ�������
CPoint PointMatrix(CPoint pt,const MATRIX* pMatrix);
inline CPoint PointMatrix(CPoint pt,const MATRIX* pMatrix)
{
	CPoint ptResult=ZEROPT;
	if(pMatrix==NULL)
		return ptResult;

	ptResult.x=pt.x*pMatrix->fa+pt.y*pMatrix->fc+pMatrix->fe;
	ptResult.y=pt.x*pMatrix->fb+pt.y*pMatrix->fd+pMatrix->ff;

	return ptResult;
}

//��ľ�������
DPOINT PointMatrix(DPOINT pt,const MATRIX* pMatrix);
inline DPOINT PointMatrix(DPOINT pt,const MATRIX* pMatrix)
{
	DPOINT ptResult;
	ptResult.x=0.0;
	ptResult.y=0.0;
	if(pMatrix==NULL)
		return ptResult;

	ptResult.x=pt.x*pMatrix->fa+pt.y*pMatrix->fc+pMatrix->fe;
	ptResult.y=pt.x*pMatrix->fb+pt.y*pMatrix->fd+pMatrix->ff;

	return ptResult;
}
/////����任��ʽ ��ת-������-��ƽ��
// Sx*cos��				Sx*sin��           0
//-Sy*sin��				Sy*cos��           0
// tx*cos��-ty*sin��	tx*sin��+ty*cos��  1 
//�任������ȡ����ת�Ƕ�
float GetAngFromMatrix(const MATRIX* pMatrix);
inline float GetAngFromMatrix(const MATRIX* pMatrix)
{
	double angle=0.0f;
	double fSx=sqrt(pMatrix->fa*pMatrix->fa+pMatrix->fb*pMatrix->fb);
	angle=acos(pMatrix->fa/fSx);

	//SVG��ת�����ӻ�˳ת
	if(angle>0)
		angle=2*PI-angle;
	else if(angle<0)
		angle=-angle;
	return (float)angle;
}

//���εľ�������
CRect RectMatrix(CRect rt,const MATRIX* pMatrix);
inline CRect RectMatrix(CRect rt,const MATRIX* pMatrix)
{
	CRect rect;
	DPOINT ptLT,ptBR;
	ptLT.x=rt.left;
	ptLT.y=rt.top;
	ptLT=PointMatrix(ptLT,pMatrix);
	ptBR.x=rt.right;
	ptBR.y=rt.bottom;
	ptBR=PointMatrix(ptBR,pMatrix);
	rect=CRect(ptLT.x,ptLT.y,ptBR.x,ptBR.y);
	
	return rect;
}

//�����
void MutiMatrix(MATRIX* pFaciend,const MATRIX* pMultiplier);
inline void MutiMatrix(MATRIX* pFaciend,const MATRIX* pMultiplier)
{
	if(pMultiplier==NULL || pFaciend==NULL)
		return ;

	MATRIX mx;
	memcpy(&mx,pFaciend,sizeof(MATRIX));

	pFaciend->fa=mx.fa*pMultiplier->fa+mx.fb*pMultiplier->fc;
	pFaciend->fb=mx.fa*pMultiplier->fb+mx.fb*pMultiplier->fd;
	pFaciend->fc=mx.fc*pMultiplier->fa+mx.fd*pMultiplier->fc;
	pFaciend->fd=mx.fc*pMultiplier->fb+mx.fd*pMultiplier->fd;
	pFaciend->fe=mx.fe*pMultiplier->fa+mx.ff*pMultiplier->fc+pMultiplier->fe;
	pFaciend->ff=mx.fe*pMultiplier->fb+mx.ff*pMultiplier->fd+pMultiplier->ff;
}

//ȡ����Բ����
BOOL GetEllipseCenter(POINT *pStart, POINT *pEnd, int rx, int ry, POINT* pRet);
inline BOOL GetEllipseCenter(POINT *pStart, POINT *pEnd, int rx, int ry, POINT *pRet)
{
	//��Բ�任X0=X-rx*sina;Y0=Y-ry*cosa;
	//������֪��ʼ������������Asina+Bcosb=1Ȼ���ø�����ʽ����
	if(ry==0 || rx==0)
		return FALSE;

	double dCos=(pStart->y-pEnd->y)/ry;
	double dSin=(pStart->x-pEnd->x)/rx;

	double dA=-2*dSin/(dCos*dCos+dSin*dSin);
	double dB=-2*dCos/(dCos*dCos+dSin*dSin);

	double dP=asin(1/(sqrt(dA*dA+dB*dB)));
	double dP2=PI-dP;
	double dFai=atan2(dB,dA);
	if(dA==0)
		dFai=dB/fabs(dB)*PI/2;
	dP=dP-dFai;
	
	double dSinP=sin(dP);
	double dCosP=cos(dP);

	pRet[0].x=pEnd->x-rx*dSinP;
	pRet[0].y=pEnd->y-ry*dCosP;

	//�ڶ�����
	dP=dP2-dFai;//���Ǹ�����ʽ�Ƴ�
	dSinP=sin(dP);
	dCosP=cos(dP);

	pRet[1].x=pEnd->x-rx*dSinP;
	pRet[1].y=pEnd->y-ry*dCosP;
	return TRUE;
}

//ȡ��Բ������
BOOL GetArcCenter(POINT *pStart, POINT *pEnd, int rx, int ry, int larc, int dirt, POINT &ret);
inline BOOL GetArcCenter(POINT *pStart, POINT *pEnd, int rx, int ry, int larc, int dirt, POINT &ret)
{
	POINT ptCenter[2],ptTemp,ptTemp2;
	if(!GetEllipseCenter(pStart, pEnd, rx, ry,ptCenter))
		return FALSE;

	ptTemp.x=pEnd->x-pStart->x;
	ptTemp.y=pEnd->y-pStart->y;
	double dAngle=atan2(ptTemp.y,ptTemp.x);
	if(dAngle<0)
		dAngle=6.2831852+dAngle;

	ptTemp.x=ptCenter[0].x-pStart->x;
	ptTemp.y=ptCenter[0].y-pStart->y;

	MATRIX mx;
	mx.fa=cos(dAngle);
	mx.fb=sin(dAngle);
	mx.fc=-sin(dAngle);
	mx.fd=cos(dAngle);
	ptTemp=PointMatrix(ptTemp,&mx);

	ptTemp2.x=ptCenter[1].x-pStart->x;
	ptTemp2.y=ptCenter[1].y-pStart->y;
	ptTemp2=PointMatrix(ptTemp2,&mx);

	if(ptTemp.y/ptTemp.x>ptTemp2.y/ptTemp2.x)//0�������
	{
		//����������ĵ㣬˳ʱ����ʼ�㵽ĩ����࣬��ʱ����ʼ�㵽ĩ���Ҳ�
		if((larc==1 && dirt==1)||(larc==0 && dirt==0))
			ret=ptCenter[0];
		else
			ret=ptCenter[1];
	}
	else //0�����Ҳ�
	{
		//����������ĵ㣬˳����С��ʼ�㵽ĩ����࣬˳С�������ʼ�㵽ĩ���Ҳ�
		if((larc==1 && dirt==1)||(larc==0 && dirt==0))
			ret=ptCenter[1];
		else
			ret=ptCenter[0];
	}

	return TRUE;
}

//������ɫ
inline BOOL CFigure::SetFullColor(DWORD color)
{
	BOOL bRet=FALSE;
	switch(m_type)
	{
	case GTYPE_ARC:
		{
			G_ARC* pTemp=(G_ARC*)m_pGraph;
			pTemp->fcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_POLYG:
		{
			G_POLYGON* pTemp=(G_POLYGON*)m_pGraph;
			pTemp->fcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_RECT:
		{
			G_RECT* pTemp=(G_RECT*)m_pGraph;
			pTemp->fcolor=color;
			pTemp->full=1;
			bRet=TRUE;
		}
		break;
	case GTYPE_CIRCLE:
		{
			G_CIRCLE* pTemp=(G_CIRCLE*)m_pGraph;
			pTemp->fcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_ELLIPSE:
		{
			G_ELLIPSE* pTemp=(G_ELLIPSE*)m_pGraph;
			pTemp->fcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_TEXT:
		{
			G_TEXT* pTemp=(G_TEXT*)m_pGraph;
			pTemp->fcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_GUSE:
		{
			G_GUSE* pTemp=(G_GUSE*)m_pGraph;
			if(pTemp->use!=NULL)
			{
				CFigureGroup* pGroup=(CFigureGroup*)pTemp->use;
				if(pGroup!=NULL)
					pGroup->SetGroupColor(color);
				bRet=TRUE;
			}
		}
		break;
	}
	return bRet;
}

//������ɫ
inline BOOL CFigure::SetColor(DWORD color)
{
	BOOL bRet=FALSE;
	switch(m_type)
	{
	case GTYPE_LINE:
		{
			G_LINE* pTemp=(G_LINE*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_POLYL:
		{
			G_POLYLINE* pTemp=(G_POLYLINE*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_ARC:
		{
			G_ARC* pTemp=(G_ARC*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_POLYG:
		{
			G_POLYGON* pTemp=(G_POLYGON*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_RECT:
		{
			G_RECT* pTemp=(G_RECT*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_CIRCLE:
		{
			G_CIRCLE* pTemp=(G_CIRCLE*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_ELLIPSE:
		{
			G_ELLIPSE* pTemp=(G_ELLIPSE*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_TEXT:
		{
			G_TEXT* pTemp=(G_TEXT*)m_pGraph;
			pTemp->lcolor=color;
			bRet=TRUE;
		}
		break;
	case GTYPE_GUSE:
		{
			G_GUSE* pTemp=(G_GUSE*)m_pGraph;
			if(pTemp->use!=NULL)
			{
				CFigureGroup* pGroup=(CFigureGroup*)pTemp->use;
				if(pGroup!=NULL)
					pGroup->SetGroupColor(color);
				bRet=TRUE;
			}
		}
		break;
	}
	return bRet;
}

//����ͼ��
inline BOOL CFigure::GetRect(CRect &rt)
{
	BOOL bRet=FALSE;
	switch(m_type)
	{
	case GTYPE_LINE:
		{
			G_LINE* pTemp=(G_LINE*)m_pGraph;
			rt.left=pTemp->sp.x<pTemp->ep.x?pTemp->sp.x:pTemp->ep.x;
			rt.right=pTemp->sp.x>pTemp->ep.x?pTemp->sp.x:pTemp->ep.x;
			rt.top=pTemp->sp.y<pTemp->ep.y?pTemp->sp.y:pTemp->ep.y;
			rt.bottom=pTemp->sp.y>pTemp->ep.y?pTemp->sp.y:pTemp->ep.y;
			bRet=TRUE;
		}
		break;
	case GTYPE_POLYL:
		{
			G_POLYLINE* pTemp=(G_POLYLINE*)m_pGraph;
			for(int i=0;i<pTemp->ptnum;i++)
			{
				if(pTemp->pt[i].x<rt.left || i==0)
					rt.left=pTemp->pt[i].x;
				if(pTemp->pt[i].x>rt.right || i==0)
					rt.right=pTemp->pt[i].x;
				if(pTemp->pt[i].y<rt.top || i==0)
					rt.top=pTemp->pt[i].y;
				if(pTemp->pt[i].y>rt.bottom || i==0)
					rt.bottom=pTemp->pt[i].y;
			}
			bRet=TRUE;
		}
		break;
	case GTYPE_ARC:
		{
			G_ARC* pTemp=(G_ARC*)m_pGraph;
			rt.left=pTemp->center.x-pTemp->rx;
			rt.right=pTemp->center.x+pTemp->rx;
			rt.top=pTemp->center.y-pTemp->ry;
			rt.bottom=pTemp->center.y+pTemp->ry;
			bRet=TRUE;
		}
		break;
	case GTYPE_POLYG:
		{
			G_POLYGON* pTemp=(G_POLYGON*)m_pGraph;
			for(int i=0;i<pTemp->ptnum;i++)
			{
				if(pTemp->pt[i].x<rt.left || i==0)
					rt.left=pTemp->pt[i].x;
				if(pTemp->pt[i].x>rt.right || i==0)
					rt.right=pTemp->pt[i].x;
				if(pTemp->pt[i].y<rt.top || i==0)
					rt.top=pTemp->pt[i].y;
				if(pTemp->pt[i].y>rt.bottom || i==0)
					rt.bottom=pTemp->pt[i].y;
			}
			bRet=TRUE;
		}
		break;
	case GTYPE_RECT:
		{
			G_RECT* pTemp=(G_RECT*)m_pGraph;
			rt.left=pTemp->lt.x;
			rt.right=pTemp->lt.x+pTemp->width;
			rt.top=pTemp->lt.y;
			rt.bottom=pTemp->lt.y+pTemp->height;
			bRet=TRUE;
		}
		break;
	case GTYPE_CIRCLE:
		{
			G_CIRCLE* pTemp=(G_CIRCLE*)m_pGraph;
			rt.left=pTemp->cp.x-pTemp->r;
			rt.right=pTemp->cp.x+pTemp->r;
			rt.top=pTemp->cp.y-pTemp->r;
			rt.bottom=pTemp->cp.y+pTemp->r;
			bRet=TRUE;
		}
		break;
	case GTYPE_ELLIPSE:
		{
			G_ELLIPSE* pTemp=(G_ELLIPSE*)m_pGraph;
			rt.left=pTemp->cp.x-pTemp->rx;
			rt.right=pTemp->cp.x+pTemp->rx;
			rt.top=pTemp->cp.y-pTemp->ry;
			rt.bottom=pTemp->cp.y+pTemp->ry;
			bRet=TRUE;
		}
		break;
	case GTYPE_TEXT:
		{
			G_TEXT* pTemp=(G_TEXT*)m_pGraph;
			rt.left=pTemp->lt.x;
			rt.right=pTemp->lt.x+pTemp->fsize*strlen(pTemp->szText)/2;
			rt.top=pTemp->lt.y;
			rt.bottom=pTemp->lt.y+pTemp->fsize;
			bRet=TRUE;
		}
		break;
	case GTYPE_IMAGE:
		{
			G_IMAGE* pTemp=(G_IMAGE*)m_pGraph;
			rt.left=pTemp->lt.x;
			rt.right=pTemp->lt.x+pTemp->width;
			rt.top=pTemp->lt.y;
			rt.bottom=pTemp->lt.y+pTemp->height;
			bRet=TRUE;
		}
		break;
	case GTYPE_GUSE:
		{
			G_GUSE* pTemp=(G_GUSE*)m_pGraph;
			if(pTemp->use!=NULL)
			{
				CFigureGroup* pGroup=(CFigureGroup*)pTemp->use;
				pGroup->GetGroupRect(rt);
				bRet=TRUE;
			}
		}
		break;
	}
	return bRet;
};

struct FIGUREELE//ͼԪ
{
	FIGUREELE(){memset(this,0,sizeof(FIGUREELE));};
	void* pEleGrp;
	CFigureGroup* pGrp0;
	CFigureGroup* pGrp1;
};
typedef std::vector<FIGUREELE*> FIGUREELEVTR;

#endif // !defined(AFX_FIGURE_H__0807DE32_0E97_4DB2_A39D_835836DC5D37__INCLUDED_)
