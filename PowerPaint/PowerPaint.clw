; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainWin
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PowerPaint.h"
LastPage=0

ClassCount=32
Class1=CPowerPaintApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=33
Resource1=IDD_GETIDDLG
Class2=CMainWin
Class5=workwin
Class6=tlswin
Class7=canvas
Resource2=IDR_BASGRP
Resource3=IDD_PRTDLG
Class8=pagectl
Resource4=IDD_GETNAME
Class9=NaviWin
Class10=egpwin
Class11=spiwin
Class12=layerwin
Resource5=IDD_TEXTDLG
Resource6=IDR_RMENU
Resource7=IDD_OPENPW0
Resource8=IDR_TLIMG
Resource9=IDD_ABOUTBOX
Resource10=IDR_RMENU2
Resource11=IDD_SCRTEXT
Resource12=IDD_CFGCOLOR
Resource13=IDR_LMENU
Resource14=IDR_MAINFRAME
Resource15=IDD_YBDBSRC
Resource16=IDD_VLEVDLG
Resource17=IDD_SELELEGRP
Resource18=IDD_GUIDEDLG
Resource19=IDD_PAGEATTR
Resource20=IDD_IMGDLG
Resource21=IDD_ZOOMDLG
Class13=guiddlg
Class14=CCfgCRDlg
Class15=PatrDlg
Class16=egatrdlg
Class17=CPrtMode
Class18=CSelVLev
Class19=typeselw
Class20=CTypeWin
Class21=TestWin
Class22=CCloseWin
Resource22=IDD_EGPATTR
Class23=imgopen
Resource23=IDR_RMENU5
Class24=BFCfgDlg
Resource24=IDD_RALATEDLG
Class25=CCfgZmDlg
Resource25=IDR_CTLBAR
Resource26=IDR_ELEMENU
Class26=SelEDlg
Resource27=IDR_SPICMG
Class27=TextDlg
Resource28=IDR_ACTGRP
Class28=ScrtDlg
Resource29=IDR_RMENU1
Class29=GetNMDlg
Resource30=IDR_RMENU6
Class30=CCfgMeter
Resource31=IDR_RMENU3
Class31=GetIdDlg
Resource32=IDR_RMENU4
Class32=CImportDlg
Resource33=IDD_IMPORT_SVG

[CLS:CPowerPaintApp]
Type=0
HeaderFile=PowerPaint.h
ImplementationFile=PowerPaint.cpp
Filter=N

[CLS:CMainWin]
Type=0
HeaderFile=MainWin.h
ImplementationFile=MainWin.cpp
Filter=W
LastObject=CMainWin
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_FILE_SAVE




[CLS:CAboutDlg]
Type=0
HeaderFile=PowerPaint.cpp
ImplementationFile=PowerPaint.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342177294

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=IDC_INSVG
Command6=IDC_INSVG_BAT
Command7=IDC_OUTSVG
Command8=IDC_PRINT
Command9=IDC_PUTOUT
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=IDC_STRAIGHT
Command16=IDC_TOSQRT
Command17=ID_IMGSTRATCH
Command18=ID_FILTER_SMOTH
Command19=ID_FILTER_GRAY
Command20=ID_FILTER_REDUCE
Command21=ID_FILTER_REV
Command22=ID_FILTER_WL
Command23=ID_TRAN_MIR
Command24=ID_TRAN_UD
Command25=ID_BD_BRIGHT
Command26=ID_BD_BLACK
Command27=ID_BD_BLK
Command28=IDC_COPYTOCLIB
Command29=IDC_PASTECLIB
Command30=IDC_CUTNOUSE
Command31=IDC_MODIFONT
Command32=IDC_SETPAGE
Command33=IDC_DRAWATTR
Command34=ID_VLCOLOR
Command35=IDC_FILLPTN
Command36=IDC_FILLCOLOR
Command37=IDC_SHOWGUIDE
Command38=IDC_GUIDE
Command39=IDC_ADDPAGE
Command40=IDC_ADDLAYER
Command41=IDC_DELCURPAGE
Command42=IDC_DELCURLAYER
Command43=IDC_DRAWRT
Command44=IDC_ZMCTL
Command45=IDC_EGPTOSGL
Command46=IDC_RESETSITE
Command47=IDC_SHOWSITE
Command48=IDC_NOCONDEV
Command49=IDC_NOCDEV
Command50=IDC_TOHMIDIR
Command51=IDC_BUSRALATE
Command52=IDC_GETNM
Command53=IDC_GETID
Command54=IDC_SVGNAME
Command55=IDC_DBXTOZONE
Command56=IDC_TEST
Command57=ID_VIEW_TOOLBAR
Command58=ID_VIEW_STATUS_BAR
Command59=IDC_BASTL
Command60=IDC_ACTTL
Command61=ID_APP_ABOUT
CommandCount=61

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_GOTOTOP
Command6=ID_GOTOBUTTOM
Command7=ID_EDIT_UNDO
Command8=ID_NORMAL
Command9=ID_MOVEPIC
Command10=ID_PARTZOOM
Command11=ID_ZOOMIO
Command12=ID_ZOOMNML
Command13=ID_LINE_ADDDOT
Command14=ID_LINE_SUBDOT
Command15=ID_CUTLINE
Command16=ID_BINDLINE
Command17=ID_CLEARIMG
Command18=ID_CUTIMG
Command19=ID_TRANIMG
Command20=ID_PAINTIMG
Command21=ID_BRIGHTIMG
Command22=ID_SETREGON
Command23=ID_CUTREGON
Command24=IDC_STRAIGHT
Command25=ID_APP_ABOUT
CommandCount=25

[TB:IDR_BASGRP]
Type=1
Class=?
Command1=ID_COORD
Command2=ID_TABLE
Command3=ID_TEXT
Command4=ID_IMAGE
Command5=ID_ESITE
Command6=ID_EGPMB
Command7=ID_LINE
Command8=ID_ARROW
Command9=ID_RECT
Command10=ID_CIRCLE
Command11=ID_ARC
Command12=ID_HSIN
Command13=ID_SIN
Command14=ID_GLASS
Command15=ID_PATH
CommandCount=15

[TB:IDR_ACTGRP]
Type=1
Class=?
Command1=ID_METER1
Command2=ID_METER2
Command3=ID_METER3
Command4=ID_METER4
Command5=ID_ANALOG
Command6=ID_ACTOBJ
Command7=ID_BAR
Command8=ID_CONLINE
Command9=ID_FLOW
Command10=ID_BUS
Command11=ID_POLYZONE
Command12=ID_PIE
Command13=ID_SYSPIE
Command14=ID_DATE
Command15=ID_TIME
Command16=ID_GIFANL
Command17=ID_PUSH
Command18=ID_SELFCTL
Command19=ID_FLASH
CommandCount=19

[TB:IDR_CTLBAR]
Type=1
Class=?
Command1=ID_PAGEUP
Command2=ID_LEFT
Command3=ID_RIGHT
Command4=ID_PAGEDOWN
CommandCount=4

[TB:IDR_TLIMG]
Type=1
Class=?
Command1=ID_BUTTON32857
Command2=ID_BUTTON32858
Command3=ID_BUTTON32859
CommandCount=3

[MNU:IDR_ELEMENU]
Type=1
Class=?
Command1=IDC_OPENEGRP
Command2=IDC_SAVEEGRP
Command3=ID_SAVEAS
Command4=IDC_ADDEMPTY
Command5=IDC_PASTENORMAL
Command6=IDC_PASTEALARM
Command7=IDC_DELAEGRP
Command8=IDC_SETUP
Command9=IDC_COPYTODESK
CommandCount=9

[MNU:IDR_RMENU]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_GOTOTOP
Command5=ID_GOTOBUTTOM
Command6=IDC_STRAIGHT
Command7=ID_ALIGN_LEFT
Command8=ID_ALIGN_RIGHT
Command9=ID_ALIGN_UP
Command10=ID_ALIGN_DOWN
Command11=ID_ALIGN_HG
Command12=ID_ALIGN_WD
Command13=ID_ALIGN_DSTX
Command14=ID_ALIGN_DSTY
Command15=ID_EDIT_ATTR
Command16=ID_CONNECT_DEV
Command17=ID_EDIT_DEV
Command18=IDC_AVCCFG
CommandCount=18

[MNU:IDR_RMENU1]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_ATTR
Command5=IDC_DBXTOLINE
Command6=IDC_DBXTOCL
CommandCount=6

[MNU:IDR_RMENU2]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_ATTR
Command5=ID_EDIT_SFT
Command6=ID_ABOUT_SFT
CommandCount=6

[MNU:IDR_RMENU3]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_ATTR
Command5=ID_DBSOURCE
CommandCount=5

[MNU:IDR_RMENU4]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_ALIGN_UP
Command5=ID_ALIGN_DOWN
Command6=ID_ALIGN_LEFT
Command7=ID_ALIGN_RIGHT
Command8=ID_ALIGN_HG
Command9=ID_ALIGN_WD
Command10=ID_ALIGN_DSTX
Command11=ID_ALIGN_DSTY
Command12=ID_SETVLEV
Command13=ID_SETFONT
Command14=ID_SETCOLOR
CommandCount=14

[MNU:IDR_RMENU5]
Type=1
Class=?
Command1=ID_CURNML
Command2=ID_EDIT_PASTE
CommandCount=2

[MNU:IDR_SPICMG]
Type=1
Class=?
Command1=IDC_ADDSPIC
Command2=IDC_OPENSPIC
Command3=IDC_SAVESPIC
Command4=IDC_DELSPIC
Command5=IDC_DELNOUSE
Command6=IDC_COPYTODESK
Command7=IDC_DEFPTN
Command8=IDC_DEFACT
CommandCount=8

[MNU:IDR_LMENU]
Type=1
Class=?
Command1=IDC_ADDLAYER
Command2=IDC_DELCURLAYER
Command3=IDC_GOTOP
Command4=IDC_GOBOTTOM
CommandCount=4

[MNU:IDR_RMENU6]
Type=1
Class=?
Command1=ID_MENUITEM32920
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_GOTOTOP
Command5=ID_GOTOBUTTOM
Command6=ID_EDIT_ATTR
Command7=ID_CONNECT_DEV
Command8=IDC_SELELEBUS
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_ADDLINEDOT
Command2=ID_EDIT_COPY
Command3=IDC_SUBLINEDOT
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
Command8=IDC_STRAIGHT
Command9=ID_EDIT_CUT
Command10=IDC_ZMIN
Command11=ID_EDIT_UNDO
Command12=IDC_ZMOUT
CommandCount=12

[DLG:IDD_CFGCOLOR]
Type=1
Class=?
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_VLNAME,listbox,1352728833
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_COLORR,edit,1350631552
Control10=IDC_COLORG,edit,1350631552
Control11=IDC_COLORB,edit,1350631552
Control12=IDC_PALLT,button,1342242816
Control13=IDC_SCOLOR,static,1342177294
Control14=IDC_STATIC,static,1342177283
Control15=IDC_STATIC,button,1342177287

[DLG:IDD_EGPATTR]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_NAME,edit,1350631552
Control9=IDC_TYPE,combobox,1344339970
Control10=IDC_SUBTYPE,combobox,1344339970
Control11=IDC_SITESUM,combobox,1344339970
Control12=IDC_MSG,listbox,1352728833
Control13=IDC_STATIC,static,1342177283
Control14=IDC_ANALYSE,button,1342242816

[DLG:IDD_GUIDEDLG]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GSIZE,edit,1350631552
Control7=IDC_STYPE,combobox,1344339970
Control8=IDC_COLOR,static,1342177287
Control9=IDC_MODIC,button,1342242816
Control10=IDC_STATIC,static,1342177283

[DLG:IDD_PAGEATTR]
Type=1
Class=?
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NAME,edit,1350631552
Control8=IDC_TYPE,combobox,1344339970
Control9=IDC_WIDTH,edit,1350631552
Control10=IDC_HEIGHT,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_SHOWBYRT,button,1342242819
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_X1,edit,1350631552
Control18=IDC_X2,edit,1350631552
Control19=IDC_Y1,edit,1350631552
Control20=IDC_Y2,edit,1350631552
Control21=IDC_ENABLESEN,button,1342242819
Control22=IDC_NO3D,button,1342242819

[DLG:IDD_PRTDLG]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO1,combobox,1344339970
Control6=IDC_COMBO2,combobox,1344339970
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342177283

[DLG:IDD_VLEVDLG]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST1,listbox,1352728833
Control5=IDC_STATIC,static,1342177283

[DLG:IDD_IMGDLG]
Type=1
Class=?
ControlCount=6
Control1=IDC_SHOWPREVIEW,button,1342242819
Control2=IDC_DEPTH,button,1342242819
Control3=IDC_WIDTH,static,1342308352
Control4=IDC_HEIGHT,static,1342308352
Control5=IDC_FSIZE,static,1342308352
Control6=IDC_PREVIEWBTN,button,1342259211

[DLG:IDD_RALATEDLG]
Type=1
Class=?
ControlCount=19
Control1=IDC_OPENPWF,button,1342242816
Control2=IDC_BUS,listbox,1352728833
Control3=IDC_ADD,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_RALATED,SysListView32,1350631437
Control8=IDC_FILENAME,edit,1350631552
Control9=IDC_PAGENO,combobox,1344339971
Control10=IDC_INDEX,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342177283
Control18=IDC_STATIC,static,1342177283
Control19=IDC_CLEARRA,button,1342242816

[DLG:IDD_ZOOMDLG]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ZOOMOUT,button,1342242819
Control4=IDC_ZOOMIN,button,1342242819
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_FDBS1,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_FNM1,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_HM1,edit,1350631552
Control13=IDC_FROMFM1,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_FDBS2,edit,1350631552
Control18=IDC_FNM2,edit,1350631552
Control19=IDC_HM2,edit,1350631552
Control20=IDC_FROMFM2,button,1342242816
Control21=IDC_DEFZM1,button,1342242819
Control22=IDC_DEFZM2,button,1342242819
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_ZM1,edit,1350631552
Control26=IDC_ZM2,edit,1350631552

[DLG:IDD_OPENPW0]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PAGE,combobox,1344339970
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PNO,edit,1342244992

[DLG:IDD_SELELEGRP]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TY,static,1342177287
Control4=IDC_SCROL,scrollbar,1342177280

[DLG:IDD_TEXTDLG]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,edit,1350631552

[DLG:IDD_SCRTEXT]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,edit,1350631620

[DLG:IDD_GETNAME]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PNAME,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LNAME,static,1342308352
Control5=IDC_PROGRESS1,msctls_progress32,1350565888
Control6=IDC_DNAME,static,1342308352
Control7=IDC_NUM,static,1342308352

[DLG:IDD_YBDBSRC]
Type=1
Class=?
ControlCount=29
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST1,SysListView32,1350631437
Control5=IDC_DBSRC,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_MTSHW,static,1342177298
Control8=IDC_STATIC,button,1342177287
Control9=IDC_VMIN,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_VMAX,edit,1350631552
Control13=IDC_USERDEF,button,1342242816
Control14=IDC_DELUSER,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_V1,edit,1350631552
Control19=IDC_V2,edit,1350631552
Control20=IDC_V3,edit,1350631552
Control21=IDC_V4,edit,1350631552
Control22=IDC_COLOR1,static,1342177287
Control23=IDC_COLOR2,static,1342177287
Control24=IDC_MODICOLOR1,button,1342242816
Control25=IDC_MODICOLOR2,button,1342242816
Control26=IDC_STATIC,static,1342177283
Control27=IDC_MODIPARAM,button,1342242816
Control28=IDC_DS,combobox,1344339970
Control29=IDC_STATIC,static,1342308352

[DLG:IDD_GETIDDLG]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_PNAME,static,1342308352
Control5=IDC_LNAME,static,1342308352
Control6=IDC_NUM,static,1342308352
Control7=IDC_DNAME,static,1342308352

[DLG:IDD_IMPORT_SVG]
Type=1
Class=CImportDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SRCPATH,edit,1350631552
Control4=IDC_BTNSCR,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_DIRPATH,edit,1350631552
Control8=IDC_BTNDIR,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_LIST_SVG,SysListView32,1350649873
Control11=IDC_CHECK_ALL,button,1342242819

[CLS:CImportDlg]
Type=0
HeaderFile=importdlg.h
ImplementationFile=importdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImportDlg

