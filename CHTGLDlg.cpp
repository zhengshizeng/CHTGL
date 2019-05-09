// CHTGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CHTGL.h"
#include "CHTGLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHTGLDlg dialog

CCHTGLDlg::CCHTGLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHTGLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCHTGLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCHTGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHTGLDlg)
	DDX_Control(pDX, IDC_STATIC_TTEXT, m_STText);
	DDX_Control(pDX, IDC_BTNWLGL, m_BtnWLGL);
	DDX_Control(pDX, IDC_BTN_YJXX, m_BtnYJXX);
	DDX_Control(pDX, IDC_BTN_TCGL, m_BtnTCGL);
	DDX_Control(pDX, IDC_BTN_KPGL, m_BtnKPGL);
	DDX_Control(pDX, IDC_BTN_HTGL, m_BtnHTGL);
	DDX_Control(pDX, IDC_BTN_JBXX, m_BtnJBXX);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCHTGLDlg, CDialog)
	//{{AFX_MSG_MAP(CCHTGLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_SYSSETM, OnMSyssetm)
	ON_COMMAND(IDM_KEFU_BASE, OnMKefuBase)
	ON_COMMAND(IDM_GONGYI_BASE, OnMGongyiBase)
	ON_COMMAND(IDM_QYR_BASE, OnMQyrBase)
	ON_COMMAND(IDM_ADDHTM, OnMAddht)
	ON_COMMAND(IDM_YJGN, OnYjgn)
	ON_COMMAND(IDM_ADDSK, OnAddsk)
	ON_COMMAND(IDM_ADDFK, OnAddfk)
	ON_COMMAND(IDM_SELECTHT, OnSelectht)
	ON_COMMAND(IDM_MDELHT, OnMdelht)
	ON_COMMAND(IDM_KPCX, OnKpcx)
	ON_COMMAND(IDM_ADDKP, OnAddkp)	
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_JBXX, OnBtnJbxx)
	ON_BN_CLICKED(IDC_BTN_HTGL, OnBtnHtgl)
	ON_BN_CLICKED(IDC_BTNWLGL, OnBtnwlgl)
	ON_BN_CLICKED(IDC_BTN_KPGL, OnBtnKpgl)
	ON_BN_CLICKED(IDC_BTN_TCGL, OnBtnTcgl)
	ON_BN_CLICKED(IDC_BTN_YJXX, OnBtnYjxx)
	ON_MESSAGE(WM_CLIENT_MSG,OnClientMSG)
	ON_COMMAND(IDM_TCGL_ADD, OnTcglAdd)	
	ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
	ON_COMMAND(IDM_DATABACKUP, OnMSyssetm)
	ON_COMMAND(IDM_DATARES, OnMSyssetm)
	ON_COMMAND(IDM_TCGLAddByHT, OnTCGLAddByHT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHTGLDlg message handlers
void CCHTGLDlg::OnClientMSG(WPARAM wParam,LPARAM lParam)
{
	int iwParam=(int)wParam;
	switch (iwParam)
	{
	case 0:
		{
			int iCommand=(int)lParam;
			OnMsgBtnChange(iCommand);
			break;
		}
	case 1:
		{
			CString *pmsg=(CString *)lParam;
			CString temp=*pmsg;
			OnMsgHTBH(temp);
			delete pmsg;
			break;
		}
	case 9:
		dlgNextID=(int)lParam;
		break;
	default:
		break;
	}
}

BOOL CCHTGLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_menu.LoadMenu(IDR_MENU_MAIN/*menu id here*/);
    SetMenu(&m_menu);

	m_BtnJBXX.MoveWindow(0,100,186,44);
	m_BtnJBXX.LoadBitmap(IDB_BMP_JBXX);
	m_BtnJBXX.SetBtnDrawNum(0,2,1,1,0);

	m_BtnHTGL.MoveWindow(0,145,186,36);
	m_BtnHTGL.LoadBitmap(IDB_BMP_HTGL);
	m_BtnHTGL.SetBtnDrawNum(0,2,1,1,0);

	m_BtnWLGL.MoveWindow(0,181,186,36);
	m_BtnWLGL.LoadBitmap(IDB_BMP_WLGL);
	m_BtnWLGL.SetBtnDrawNum(0,2,1,1,0);

	m_BtnKPGL.MoveWindow(0,217,186,36);
	m_BtnKPGL.LoadBitmap(IDB_BMP_KPGL);
	m_BtnKPGL.SetBtnDrawNum(0,2,1,2,0);

	m_BtnTCGL.MoveWindow(0,253,186,36);
	m_BtnTCGL.LoadBitmap(IDB_BMP_TCGL);
	m_BtnTCGL.SetBtnDrawNum(0,2,1,2,0);

	m_BtnYJXX.MoveWindow(0,289,186,36);
	m_BtnYJXX.LoadBitmap(IDB_BMP_YJSX);
	m_BtnYJXX.SetBtnDrawNum(0,2,1,2,0);

	m_STText.MoveWindow(230,82,700,40);
//	m_STText.SetBkColor(RGB(28,99,161),TRUE);
	m_STText.SetTextColor(RGB(250,250,250));
	GetDlgItem(IDC_STATIC_WND)->MoveWindow(218,136,777,510);

	CWnd * outBroad = GetDlgItem(IDC_STATIC_WND);
	
	dlgyujing.Create(IDD_YUJING_DLG,outBroad);
	dlgBtnChange.Create(IDD_DLG_BTN,outBroad);
	dlgCustomer.Create(IDD_ADDCUSTOMER,outBroad);
	dlgaddQwr.Create(IDD_ADDQWR,outBroad);
	dlgaddHt.Create(IDD_ADDHT_DLG,outBroad);
	dlgshtlist.Create(IDD_DLG_SHT,outBroad);
	dlgSysSet.Create(IDD_SYS_DLG,outBroad);
	dlgAddSFK.Create(IDD_ADDSFK_DLG,outBroad);

	dlgshowid = 1;
	DlgShowORHide(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCHTGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCHTGLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCHTGLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCHTGLDlg::OnMSyssetm() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[系统设置]");
	DlgShowORHide(7);	
}

void CCHTGLDlg::OnMKefuBase() 
{
	// TODO: Add your command handler code here
	dlgCustomer.SetuKFLX(0);
	m_STText.SetCaptionSW("[基本信息]-->客户管理");
	DlgShowORHide(3);
}

void CCHTGLDlg::OnMGongyiBase() 
{
	// TODO: Add your command handler code here
	dlgCustomer.SetuKFLX(1);
	m_STText.SetCaptionSW("[基本信息]-->供应商管理");
	DlgShowORHide(3);
}

void CCHTGLDlg::OnMQyrBase() 
{
	// TODO: Add your command handler code here	
	m_STText.SetCaptionSW("[基本信息]-->签约人管理");
	DlgShowORHide(4);
}

void CCHTGLDlg::OnMAddht() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[合同管理]-->新增合同");
	DlgShowORHide(5);
}

void CCHTGLDlg::OnYjgn() 
{
	// TODO: Add your command handler code here
	DlgShowORHide(1);
}

void CCHTGLDlg::OnAddsk() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[往来管理]-->新增收款(查询要收款的合同)");
	dlgNextID=31;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnAddfk() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[往来管理]-->新增付款(查询要付款的合同)");
	dlgNextID=32;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnSelectht() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[合同管理]-->合同查询");
	dlgNextID=22;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnMdelht() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[合同管理]-->删除合同(查询要删除的合同)");
	dlgNextID=99;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnKpcx() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[开票管理]-->查询开票(查询要开票的合同)");
	dlgNextID=41;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnAddkp() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[开票管理]-->新增开票(查询要开票的合同)");
	dlgNextID=41;
	DlgShowORHide(6);
}

void CCHTGLDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,1024,768,SWP_NOMOVE | SWP_NOOWNERZORDER );
	//SetWindowPos(NULL,0,0,1030,820,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

BOOL CCHTGLDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CPaintDC dc(this); 
	CRect rect; 
	GetClientRect(&rect); 
	CDC dcMem; 
	dcMem.CreateCompatibleDC(&dc); 
	CBitmap bmpBackground; 
	bmpBackground.LoadBitmap(IDB_BMP_LOGINBK); 
	BITMAP bitmap; 
	bmpBackground.GetBitmap(&bitmap);
	int nRight = bitmap.bmWidth;
	int nBtonn = bitmap.bmHeight;
	CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground); 
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0, 
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
	return TRUE;
//	return CDialog::OnEraseBkgnd(pDC);
}


void CCHTGLDlg::DlgShowORHide(int dlgid)
{
	switch(dlgshowid)
	{
	case 1:dlgyujing.ShowWindow(SW_HIDE);//1
		break;
	case 2:dlgBtnChange.ShowWindow(SW_HIDE);//1
		break;
	case 3:dlgCustomer.ShowWindow(SW_HIDE);//1
		break;
	case 4:dlgaddQwr.ShowWindow(SW_HIDE);//1
		break;
	case 5:dlgaddHt.ShowWindow(SW_HIDE);//1
		break;
	case 6:dlgshtlist.ShowWindow(SW_HIDE);
		break;
	case 7:dlgSysSet.ShowWindow(SW_HIDE);
		break;
	case 8:
		dlgAddSFK.ShowWindow(SW_HIDE);
		break;
	default :
		break;
	}
	dlgshowid = dlgid;
	
	switch (dlgid)
	{
	case 1:
		m_STText.SetCaptionSW("[预警信息]");
		//AnimateWindow(dlgyujing,200, AW_SLIDE | AW_HOR_NEGATIVE);  //显示与隐藏窗口时能产生特殊的效果
		dlgyujing.ShowWindow(SW_SHOW);
		dlgyujing.CenterWindow();
		break;
	case 2:
		AnimateWindow(dlgBtnChange,200, AW_SLIDE | AW_HOR_NEGATIVE);  //显示与隐藏窗口时能产生特殊的效果
		dlgBtnChange.ShowWindow(SW_SHOW);
		dlgBtnChange.CenterWindow();
		break;
	case 3:		
		AnimateWindow(dlgCustomer,200, AW_SLIDE | AW_HOR_NEGATIVE);  //显示与隐藏窗口时能产生特殊的效果
		dlgCustomer.ShowWindow(SW_SHOW);
		dlgCustomer.CenterWindow();
		break;
	case 4:
		AnimateWindow(dlgaddQwr,200, AW_SLIDE | AW_HOR_NEGATIVE);  //显示与隐藏窗口时能产生特殊的效果
		dlgaddQwr.ShowWindow(SW_SHOW);
		dlgaddQwr.CenterWindow();
		break;
	case 5:
		dlgaddHt.ShowWindow(SW_SHOW);
		dlgaddHt.CenterWindow();
		break;
	case 6:
		dlgshtlist.ShowWindow(SW_SHOW);
		dlgshtlist.CenterWindow();
		break;
	case 7:
		AnimateWindow(dlgSysSet,200, AW_SLIDE | AW_HOR_NEGATIVE); 
		dlgSysSet.ShowWindow(SW_SHOW);
		dlgSysSet.CenterWindow();
		break;
	case 8:
		AnimateWindow(dlgAddSFK,200, AW_SLIDE | AW_HOR_NEGATIVE); 
		dlgAddSFK.ShowWindow(SW_SHOW);
		dlgAddSFK.CenterWindow();
		break;
	default :
		break;
	}
}

void CCHTGLDlg::OnBtnJbxx() 
{
	// TODO: Add your control notification handler code here	
	m_STText.SetCaptionSW("[基本信息]");
	dlgBtnChange.SetBtnShowHide(1);
	DlgShowORHide(2);
}

void CCHTGLDlg::OnBtnHtgl() 
{
	// TODO: Add your control notification handler code here	
	m_STText.SetCaptionSW("[合同管理]");
	dlgBtnChange.SetBtnShowHide(2);
	DlgShowORHide(2);
}

void CCHTGLDlg::OnBtnwlgl() 
{
	// TODO: Add your control notification handler code here
	m_STText.SetCaptionSW("[往来管理]");
	dlgBtnChange.SetBtnShowHide(3);
	DlgShowORHide(2);
}

void CCHTGLDlg::OnBtnKpgl() 
{
	// TODO: Add your control notification handler code here
	m_STText.SetCaptionSW("[开票管理]");
	dlgBtnChange.SetBtnShowHide(4);
	DlgShowORHide(2);
}

void CCHTGLDlg::OnBtnTcgl() 
{
	// TODO: Add your control notification handler code here
	m_STText.SetCaptionSW("[提成管理]");
	dlgBtnChange.SetBtnShowHide(5);
	DlgShowORHide(2);
}

void CCHTGLDlg::OnBtnYjxx() 
{
	// TODO: Add your control notification handler code here
	DlgShowORHide(1);
}

void CCHTGLDlg::OnTcglAdd() 
{
	// TODO: Add your command handler code here
	CTcglDlg dlgTcgl;
	dlgTcgl.DoModal();
}

void CCHTGLDlg::OnMsgBtnChange(int icommand)
{
	switch(icommand)
	{
	case 1:
		OnMKefuBase();
		break;
	case 2:
		OnMGongyiBase();
		break;
	case 3:
		OnMQyrBase();
		break;
	case 21:
		OnMAddht();
		break;
	case 22:
		OnSelectht();
		break;
	case 23:
		OnMdelht();
		break;
	case 31:
		OnAddsk();
		break;
	case 32:
		OnAddfk();
		break;
	case 41:
		OnAddkp();
		break;
	case 51:
		OnTcglAdd();
		break;
	case 52:
		OnTCGLAddByHT();
		break;
	default:
		break;
	}
}

void CCHTGLDlg::OnMsgHTBH(CString htbh)
{
	switch(dlgNextID)
	{
	case 99:
		ClearHTAllMsg(htbh);
		OnBtnHtgl();
		break;
	case 22:
		{
			CSelectHTDLG selectHTdlg;
			selectHTdlg.SetHTBH(htbh);
			selectHTdlg.DoModal();
		}
		break;
	case 31:
		m_STText.SetCaptionSW("[往来管理]-->新增收款");
		dlgAddSFK.SetHTBHAndKFLX(htbh,0);
		DlgShowORHide(8);
		break;
	case 32:
		m_STText.SetCaptionSW("[往来管理]-->新增付款");
		dlgAddSFK.SetHTBHAndKFLX(htbh,1);
		DlgShowORHide(8);
		break;
	case 41:
		{
			CKpgl_Dlg kpgjdlg;
			kpgjdlg.SetHTBH(htbh);
			kpgjdlg.DoModal();
		}
		break;
	case 52:
		{
			CDlgTcglAddByHT dlgtcgladdbyht;
			dlgtcgladdbyht.SetHTBH(htbh);
			dlgtcgladdbyht.DoModal();
		}
		break;
	default:
		break;
	}
}

void CCHTGLDlg::ClearHTAllMsg(CString htbh)
{
	CString temp,tempHtbh;
	tempHtbh.Format("%s",htbh);
	temp.Format("是否删除合同:[%s] 的【所有数据】,删除后数据将无法恢复!",tempHtbh);
	if(MessageBox(temp,"删除提示" ,MB_ICONEXCLAMATION |MB_OKCANCEL)==IDOK)
	{
		if(MessageBox(temp,"确定删除提示" ,MB_ICONEXCLAMATION |MB_OKCANCEL)==IDOK)
		{
			temp.Format("delete from ContractHT WHERE HTBH='%s' ",tempHtbh);
			if(theApp.ExecuteSql(temp)==TRUE)
			{
				AfxMessageBox("清除合同完成!");
			}
			temp.Format("delete from Receivables WHERE CustomerID='%s' ",tempHtbh);
			if(theApp.ExecuteSql(temp)==TRUE)
			{
				AfxMessageBox("清除明细完成!");
			}
			temp.Format("delete from KaiPiaoManager WHERE CustomerID='%s' ",tempHtbh);
			if(theApp.ExecuteSql(temp)==TRUE)
			{
				AfxMessageBox("清除开票明细完成!");
			}
			temp.Format("delete from ExtractM WHERE CustomerID='%s' ",tempHtbh);
			if(theApp.ExecuteSql(temp)==TRUE)
			{
				AfxMessageBox("清除提成明细完成!");
			}
		}
	}
}

void CCHTGLDlg::OnAboutbox() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}


void CCHTGLDlg::OnTCGLAddByHT() 
{
	// TODO: Add your command handler code here
	m_STText.SetCaptionSW("[提成管理]-->按合同添加提成记录(查询要提成的合同)");
	dlgNextID=52;
	DlgShowORHide(6);
}
