#if !defined(AFX_ADDQWRDLG_H__4EE61C4B_7222_4FE2_9C3C_8A8572917968__INCLUDED_)
#define AFX_ADDQWRDLG_H__4EE61C4B_7222_4FE2_9C3C_8A8572917968__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQWRDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddQWRDlg dialog

class CAddQWRDlg : public CDialog
{
// Construction
public:
	BOOL UpdateQWRList();
	CAddQWRDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddQWRDlg)
	enum { IDD = IDD_ADDQWR };
	CListCtrl	m_List_QWR;
	CString	m_EName;
	CString	m_ESfz;
	CString	m_ETel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddQWRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddQWRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnDel();
	afx_msg void OnItemchangedListQwr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQWRDLG_H__4EE61C4B_7222_4FE2_9C3C_8A8572917968__INCLUDED_)
