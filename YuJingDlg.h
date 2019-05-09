#if !defined(AFX_YUJINGDLG_H__B813D2AE_61C7_45BE_BC9C_61FB5315167E__INCLUDED_)
#define AFX_YUJINGDLG_H__B813D2AE_61C7_45BE_BC9C_61FB5315167E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YuJingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYuJingDlg dialog

class CYuJingDlg : public CDialog
{
// Construction
public:
	BOOL UpdateList();
	CYuJingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYuJingDlg)
	enum { IDD = IDD_YUJING_DLG };
	CListCtrlz	m_List_SK;
	CString	m_EHtbh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYuJingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYuJingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSelectht();
	afx_msg void OnItemchangedListSk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExport();
	afx_msg void OnBtnAddsk();
	afx_msg void OnBtnAddfk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUJINGDLG_H__B813D2AE_61C7_45BE_BC9C_61FB5315167E__INCLUDED_)
