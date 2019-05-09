#if !defined(AFX_SYSSETDLG_H__03171FA0_5779_47F0_A222_399851964D73__INCLUDED_)
#define AFX_SYSSETDLG_H__03171FA0_5779_47F0_A222_399851964D73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysSetDlg dialog

class CSysSetDlg : public CDialog
{
// Construction
public:
	CString ExePath;
	CSysSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysSetDlg)
	enum { IDD = IDD_SYS_DLG };
	CListCtrl	m_TypeList;
	CString	m_TypeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysSetDlg)
	afx_msg void OnBtnSklxsave();
	afx_msg void OnBtnSklxdel();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListSklx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBTNBackup();
	afx_msg void OnBTNRestore();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString strZDB;
	BOOL UpdateTypeList();
	void AddTypeList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSSETDLG_H__03171FA0_5779_47F0_A222_399851964D73__INCLUDED_)
