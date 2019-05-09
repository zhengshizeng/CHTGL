#if !defined(AFX_DLGBTNCHANGE_H__351FCC34_C09B_4DCF_B9EA_07DCF5828513__INCLUDED_)
#define AFX_DLGBTNCHANGE_H__351FCC34_C09B_4DCF_B9EA_07DCF5828513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBtnChange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBtnChange dialog

class CDlgBtnChange : public CDialog
{
// Construction
public:
	UINT m_uOldShowH;
	void SetBtnShoworHide(UINT uShowh,int ishowhide);
	void SetBtnShowHide(UINT uShowH);
	CDlgBtnChange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBtnChange)
	enum { IDD = IDD_DLG_BTN };
	CButton	m_BTNHtAddTc;
	CButton	m_BtnAddTCGL;
	CButton	m_Btn_AddKP;
	CButton	m_BtnAddFK;
	CButton	m_BtnAddSK;
	CButtonzEx	m_BtnHtSelect;
	CButtonzEx	m_BtnHtDelete;
	CButtonzEx	m_BtnAddHt;
	CButtonzEx	m_BtnBQYR;
	CButtonzEx	m_BtnBKF;
	CButtonzEx	m_BtnBGYS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBtnChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBtnChange)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBkf();
	afx_msg void OnBtnBgys();
	afx_msg void OnBtnBqyr();
	afx_msg void OnBtnAddht();
	afx_msg void OnBtnHtselect();
	afx_msg void OnBTNHTDelete();
	afx_msg void OnBtnAddsk();
	afx_msg void OnBtnAddfk();
	afx_msg void OnBtnAddkp();
	afx_msg void OnBTNAddTCGL();
	afx_msg void OnBtnHtaddtc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBTNCHANGE_H__351FCC34_C09B_4DCF_B9EA_07DCF5828513__INCLUDED_)
