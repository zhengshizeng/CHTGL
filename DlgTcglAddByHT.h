#if !defined(AFX_DLGTCGLADDBYHT_H__47107904_5B97_4CFE_A762_327AB224E42C__INCLUDED_)
#define AFX_DLGTCGLADDBYHT_H__47107904_5B97_4CFE_A762_327AB224E42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTcglAddByHT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTcglAddByHT dialog

class CDlgTcglAddByHT : public CDialog
{
// Construction
public:
	void SetHTBH(CString htbh);
	void OnSelectHKList();
	void OnMCSelect();
	void UpdateListTCMC();
	CDlgTcglAddByHT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTcglAddByHT)
	enum { IDD = IDD_DLG_TCGLAddByHT };
	CListCtrl	m_ListTCMC;
	CListCtrl	m_ListHKMC;
	CTime	m_DateTime;
	double	m_EdBl;
	double	m_EdHkjr;
	CString	m_EHTBH;
	double	m_EdHtjr;
	double	m_EdKT;
	double	m_EdTcMoney;
	double	m_EdWT;
	double	m_EdYT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTcglAddByHT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTcglAddByHT)
	afx_msg void OnBtnSetbl();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddtcmc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTCGLADDBYHT_H__47107904_5B97_4CFE_A762_327AB224E42C__INCLUDED_)
