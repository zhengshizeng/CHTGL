// DlgBtnChange.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "DlgBtnChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBtnChange dialog


CDlgBtnChange::CDlgBtnChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBtnChange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBtnChange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBtnChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBtnChange)
	DDX_Control(pDX, IDC_BTN_HTADDTC, m_BTNHtAddTc);
	DDX_Control(pDX, IDC_BTN_AddTCGL, m_BtnAddTCGL);
	DDX_Control(pDX, IDC_BTN_ADDKP, m_Btn_AddKP);
	DDX_Control(pDX, IDC_BTN_ADDFK, m_BtnAddFK);
	DDX_Control(pDX, IDC_BTN_ADDSK, m_BtnAddSK);
	DDX_Control(pDX, IDC_BTN_HTSELECT, m_BtnHtSelect);
	DDX_Control(pDX, IDC_BTN_HTDelete, m_BtnHtDelete);
	DDX_Control(pDX, IDC_BTN_ADDHT, m_BtnAddHt);
	DDX_Control(pDX, IDC_BTN_BQYR, m_BtnBQYR);
	DDX_Control(pDX, IDC_BTN_BKF, m_BtnBKF);
	DDX_Control(pDX, IDC_BTN_BGYS, m_BtnBGYS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBtnChange, CDialog)
	//{{AFX_MSG_MAP(CDlgBtnChange)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_BKF, OnBtnBkf)
	ON_BN_CLICKED(IDC_BTN_BGYS, OnBtnBgys)
	ON_BN_CLICKED(IDC_BTN_BQYR, OnBtnBqyr)
	ON_BN_CLICKED(IDC_BTN_ADDHT, OnBtnAddht)
	ON_BN_CLICKED(IDC_BTN_HTSELECT, OnBtnHtselect)
	ON_BN_CLICKED(IDC_BTN_HTDelete, OnBTNHTDelete)
	ON_BN_CLICKED(IDC_BTN_ADDSK, OnBtnAddsk)
	ON_BN_CLICKED(IDC_BTN_ADDFK, OnBtnAddfk)
	ON_BN_CLICKED(IDC_BTN_ADDKP, OnBtnAddkp)
	ON_BN_CLICKED(IDC_BTN_AddTCGL, OnBTNAddTCGL)
	ON_BN_CLICKED(IDC_BTN_HTADDTC, OnBtnHtaddtc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBtnChange message handlers

void CDlgBtnChange::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,773,606,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

HBRUSH CDlgBtnChange::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if ( nCtlColor==CTLCOLOR_DLG  || nCtlColor ==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);  
		pDC->SetTextColor(RGB(20,20,20));
		HBRUSH   hbr1=CreateSolidBrush(RGB(255,255,255)); 
		return   hbr1; 
 	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CDlgBtnChange::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//GetDlgItem(IDC_BTN_BKF)->MoveWindow(0,600,100,100);

	
	m_BtnBGYS.LoadBitmap(IDB_BMP_BGYS);
	m_BtnBGYS.SetBtnDrawNum(0,1,2,1,0);

	m_BtnBKF.LoadBitmap(IDB_BMP_BKFGL);
	m_BtnBKF.SetBtnDrawNum(0,1,2,1,0);

	m_BtnBQYR.LoadBitmap(IDB_BMP_BQYR);
	m_BtnBQYR.SetBtnDrawNum(0,1,2,1,0);

	//////////////////////////////////////////////////////////////////////////
	m_BtnAddHt.LoadBitmap(IDB_BMP_HTGL_A);
	m_BtnAddHt.SetBtnDrawNum(0,1,2,1,0);

	m_BtnHtSelect.LoadBitmap(IDB_BMP_HTGL_S);
	m_BtnHtSelect.SetBtnDrawNum(0,1,2,1,0);

	m_BtnHtDelete.LoadBitmap(IDB_BMP_HTGL_D);
	m_BtnHtDelete.SetBtnDrawNum(0,1,2,1,0);
	//////////////////////////////////////////////////////////////////////////

	m_BtnBKF.MoveWindow(88,120,166,128);				
	m_BtnBQYR.MoveWindow(302,220,166,128);
	m_BtnBGYS.MoveWindow(514,120,166,128);
	//////////////////////////////////////////////////////////////////////////
	m_BtnAddHt.MoveWindow(88,120,166,128);				
	m_BtnHtSelect.MoveWindow(302,220,166,128);
	m_BtnHtDelete.MoveWindow(514,120,166,128);
	//////////////////////////////////////////////////////////////////////////
	m_BtnAddSK.MoveWindow(88,120,166,128);
	m_BtnAddFK.MoveWindow(514,120,166,128);
	//////////////////////////////////////////////////////////////////////////
	m_Btn_AddKP.MoveWindow(302,220,166,128);
	//////////////////////////////////////////////////////////////////////////
	m_BtnAddTCGL.MoveWindow(88,120,166,128);	
	m_BTNHtAddTc.MoveWindow(514,120,166,128);

	for (int i=1;i<6;i++)
	{
		SetBtnShoworHide(i,SW_HIDE);
	}
	m_uOldShowH=9;
	//SetBtnShowHide(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBtnChange::OnBtnBkf() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,1);
}

void CDlgBtnChange::OnBtnBgys() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,2);
}

void CDlgBtnChange::OnBtnBqyr() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,3);
}

void CDlgBtnChange::SetBtnShowHide(UINT uShowH)
{
	SetBtnShoworHide(m_uOldShowH,SW_HIDE);
	SetBtnShoworHide(uShowH,SW_SHOW);
	m_uOldShowH=uShowH;
}



void CDlgBtnChange::OnBtnAddht() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,21);
}

void CDlgBtnChange::OnBtnHtselect() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,22);
}

void CDlgBtnChange::OnBTNHTDelete() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,23);
}

void CDlgBtnChange::OnBtnAddsk() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,31);
}

void CDlgBtnChange::OnBtnAddfk() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,32);
}

void CDlgBtnChange::OnBtnAddkp() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,41);
}

void CDlgBtnChange::SetBtnShoworHide(UINT uShowh, int ishowhide)
{
	switch (uShowh)
	{
	case 1:
		m_BtnBKF.ShowWindow(ishowhide);
		m_BtnBQYR.ShowWindow(ishowhide);
		m_BtnBGYS.ShowWindow(ishowhide);
		break;
	case 2:
		m_BtnAddHt.ShowWindow(ishowhide);
		m_BtnHtSelect.ShowWindow(ishowhide);
		m_BtnHtDelete.ShowWindow(ishowhide);
		break;
	case 3:
		m_BtnAddSK.ShowWindow(ishowhide);
		m_BtnAddFK.ShowWindow(ishowhide);
		break;
	case 4:
		m_Btn_AddKP.ShowWindow(ishowhide);
		break;
	case 5:
		m_BtnAddTCGL.ShowWindow(ishowhide);
		m_BTNHtAddTc.ShowWindow(ishowhide);
		break;
	}
}

void CDlgBtnChange::OnBTNAddTCGL() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,51);
}

void CDlgBtnChange::OnBtnHtaddtc() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,0,52);
}
