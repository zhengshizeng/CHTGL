// CHTGLDlg.h : header file
//

#if !defined(AFX_CHTGLDLG_H__81ADF97A_77B8_481A_935B_6AEA1950BD83__INCLUDED_)
#define AFX_CHTGLDLG_H__81ADF97A_77B8_481A_935B_6AEA1950BD83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SysSetDlg.h"
#include "AddCustomerDlg.h"
#include "AddQWRDlg.h"
#include "AddHTDlg.h"
#include "YuJingDlg.h"
#include "SHTListDlg.h"
#include "AddSFKDlg.h"
#include "SelectHTDLG.h"
#include "Kpgl_Dlg.h"
#include "DlgBtnChange.h"
#include "TcglDlg.h"
#include "DlgTcglAddByHT.h"
/////////////////////////////////////////////////////////////////////////////
// CCHTGLDlg dialog

class CCHTGLDlg : public CDialog
{
// Construction
public:
	void ClearHTAllMsg(CString htbh);
	void OnMsgHTBH(CString htbh);
	void OnMsgBtnChange(int icommand);
	//////////////////////////////////////////////////////////////////////////
	CYuJingDlg		dlgyujing;
	CDlgBtnChange	dlgBtnChange;	
	CAddCustomerDlg dlgCustomer;
	CAddQWRDlg		dlgaddQwr;
	CAddHTDlg		dlgaddHt;
	CSHTListDlg		dlgshtlist;
	CSysSetDlg		dlgSysSet;
	CAddSFKDlg		dlgAddSFK;
	//////////////////////////////////////////////////////////////////////////
	CCHTGLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCHTGLDlg)
	enum { IDD = IDD_CHTGL_DIALOG };
	CStaticz	m_STText;
	CButtonzEx	m_BtnWLGL;
	CButtonzEx	m_BtnYJXX;
	CButtonzEx	m_BtnTCGL;
	CButtonzEx	m_BtnKPGL;
	CButtonzEx	m_BtnHTGL;
	CButtonzEx	m_BtnJBXX;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHTGLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCHTGLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMSyssetm();
	afx_msg void OnMKefuBase();
	afx_msg void OnMGongyiBase();
	afx_msg void OnMQyrBase();
	afx_msg void OnMAddht();
	afx_msg void OnYjgn();
	afx_msg void OnAddsk();
	afx_msg void OnAddfk();
	afx_msg void OnSelectht();
	afx_msg void OnMdelht();
	afx_msg void OnKpcx();
	afx_msg void OnAddkp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnJbxx();
	afx_msg void OnBtnHtgl();
	afx_msg void OnBtnwlgl();
	afx_msg void OnBtnKpgl();
	afx_msg void OnBtnTcgl();
	afx_msg void OnBtnYjxx();
	afx_msg void OnClientMSG(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTcglAdd();
	afx_msg void OnAboutbox();
	afx_msg void OnTCGLAddByHT();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMenu m_menu;
	int dlgNextID,dlgPreID;
	int dlgshowid;
	void DlgShowORHide(int dlgid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTGLDLG_H__81ADF97A_77B8_481A_935B_6AEA1950BD83__INCLUDED_)
