#if !defined(AFX_ADDCUSTOMERDLG_H__87B71ADD_A3F2_4568_9252_833052F41BDC__INCLUDED_)
#define AFX_ADDCUSTOMERDLG_H__87B71ADD_A3F2_4568_9252_833052F41BDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddCustomerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddCustomerDlg dialog

class CAddCustomerDlg : public CDialog
{
// Construction
public:
	void SetuKFLX(UINT uKFLX);
	BOOL UpdateKFList();

	CAddCustomerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddCustomerDlg)
	enum { IDD = IDD_ADDCUSTOMER };
	CListCtrl	m_List_Kfzl;
	CString	m_KFName;
	CString	m_ContactPerson;
	CString	m_Telephone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddCustomerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddCustomerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnItemchangedListKfzl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_uKFLX;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDCUSTOMERDLG_H__87B71ADD_A3F2_4568_9252_833052F41BDC__INCLUDED_)
