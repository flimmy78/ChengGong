#if!defined(__SPLITASS_H)
#define __SPLITASS_H
//�зִ��ڰ���
//CJH 1999��11�����

class SplitAss{
public:
	SplitAss();
	~SplitAss();
	void Create(CWnd *cwnd,CWnd *cwnd1,CWnd *cwnd2,char *text=NULL,int style=0);
	void SetInitPosition(int pos);
	void OnMouseMove(CPoint point);
	void OnLButtonDown(CPoint point);
	void OnLButtonUp(CPoint point);
	void OnSize(int cx,int cy);
	void OnPaint(CDC&dc);
	CWnd *pwin;       //����Ӧ��������
	CWnd *wnd1,*wnd2; //�Ӵ���
private:
	void drawxorline(CPoint point);
	void ComputRect();//������������λ��
	CRect rw1,rw2;    //�������ڵľ���
	int  style;       //0=�����з� 1=�����з�
	char titlebz;     //�����־
	char title[45];   //�����ַ�
	int  position;    //��ǰ�з�λ��
	int  wx,wy;		  //�����ڵĴ�С
	CPoint opos;
	CPen pen;
	CFont font;
	int  dnbz;		  //ѹ������־
	int  cursor;      //��ǰ���
	int  closebz;     //�رձ�־
	HCURSOR hcurx,hcury;
};

#endif