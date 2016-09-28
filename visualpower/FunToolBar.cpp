// FunToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "FunToolBar.h"
#include "ComObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char* g_pFun[]={"��������","ĸ�ߵȸ���","ĸ�ߵȸ��ߵ�","ĸ�ߵȸ��߸�","����ߵȸ���","��ѹ���ȸ���","���ɵȸ���",\
                      "���泱��","�����ȼ���","���������","�޹�����������","��ѹ������","��ѹ���¶�","N-1��ѹ��������",\
					  "N-1������������","N-1��������","Ԥ��N-1��ѹ��������","Ԥ��N-1������������","Ԥ��N-1��������",\
					  "N-1Ӱ��","������Ϣ","ϵͳͳ�ư�ͼ","SOE�ط�","��Ƶ�𵴼���"};//24��

extern comobj  cobj;		//��������
/////////////////////////////////////////////////////////////////////////////
// FunToolBar

FunToolBar::FunToolBar()
{
	CFont font;
	color=GetSysColor(COLOR_3DFACE);
	font.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"����" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	mdc.Create(1,1);
	curft=0;
}

FunToolBar::~FunToolBar()
{
}


BEGIN_MESSAGE_MAP(FunToolBar, CToolBar)
	//{{AFX_MSG_MAP(FunToolBar)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FunToolBar message handlers

void FunToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CRect rt;
	CToolBar::OnSize(nType, cx, cy);
	GetItemRect(1,&rt); 
	rt1=rt;
	rt1.left+=4;
	//rt1.top+=1;
	rt1.right-=1;
	rt1.bottom-=1;
	rt2=rt1;
	rt2.OffsetRect(-rt1.left,-rt1.top);
	rw=rt.Width();
	rh=rt.Height();
	mdc.SizeChange(rw,rh);	
	
}

void FunToolBar::OnPaint() 
{
	
	CToolBar::OnPaint();
	CClientDC dc(this);
	Showft();
	mdc.BitBlt(dc.m_hDC,rt1);
}


void FunToolBar::Showft()
{
	char p[100];
	CRect rt;
	mdc.FillBG(0x7f7f7f);
	mdc.CDraw3DRect(rt2,0,0xffffff);
	rt=rt2;
	rt.left+=2;
	rt.right-=2;
	if(curft>=24||curft<0) strcpy(p,"δ֪����");	
	else strcpy(p,g_pFun[curft]);
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//�����µĹ��ܺ�
void FunToolBar::ReDrawNewFt()
{
	curft=cobj.swin->m_CurFun;
	CClientDC dc(this);
	Showft();
	mdc.BitBlt(dc.m_hDC,rt1);
}