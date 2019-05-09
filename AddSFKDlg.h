#if !defined(AFX_ADDSFKDLG_H__4DE47DB3_551F_45D7_853F_95656599B73C__INCLUDED_)
#define AFX_ADDSFKDLG_H__4DE47DB3_551F_45D7_853F_95656599B73C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSFKDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddSFKDlg dialog

class CAddSFKDlg : public CDialog
{
// Construction
public:
	CString strRID;
	BOOL UpdateSFKTJList();
	void SetHTBHAndKFLX(CString htbh,int ikflx);
	int m_ikflx;
	CAddSFKDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddSFKDlg)
	enum { IDD = IDD_ADDSFK_DLG };
	CListCtrl	m_ListSFKTJ;
	CString	m_EHtbh;
	CString	m_ETj;
	double	m_EYjjr;
	double	m_ESjjr;
	CString	m_EYjsj;
	CTime	m_TimeSJ;
	CString	m_EYH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddSFKDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddSFKDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnHtxq();
	afx_msg void OnBtnAddsf();
	afx_msg void OnItemchangedListSfktj(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSFKDLG_H__4DE47DB3_551F_45D7_853F_95656599B73C__INCLUDED_)
