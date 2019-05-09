#if !defined(AFX_TCGLDLG_H__FABE009B_48BB_4C0B_9B75_170E2AD52375__INCLUDED_)
#define AFX_TCGLDLG_H__FABE009B_48BB_4C0B_9B75_170E2AD52375__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TcglDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTcglDlg dialog

class CTcglDlg : public CDialog
{
// Construction
public:
	void UpdateListTCMC();
	CString m_ehtbhT;
	CStringArray m_ArrayQYRID;
	void OnQRWCombox();
	CTcglDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTcglDlg)
	enum { IDD = IDD_DLG_TCGL };
	CListCtrl	m_ListCtrlHt2;
	CListCtrl	m_ListCtrlHT;
	CComboBox	m_Combo_QWR;
	UINT	m_ENianDu;
	CString	m_Ehtbh;
	double	m_Edhtjr;
	double	m_EdKT;
	double	m_EdTCMoney;
	double	m_EdWT;
	double	m_EdYT;
	double	m_EBl;
	double	m_EHkjr;
	CTime	m_DateTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcglDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTcglDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSelectht();
	afx_msg void OnItemchangedListHt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnMcselect();
	afx_msg void OnBtnSetbl();
	afx_msg void OnBtnAddtcmc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCGLDLG_H__FABE009B_48BB_4C0B_9B75_170E2AD52375__INCLUDED_)
