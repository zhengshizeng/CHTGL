#if !defined(AFX_ADDHTDLG_H__75929951_82DF_4555_A6BD_108C9CEAFFDE__INCLUDED_)
#define AFX_ADDHTDLG_H__75929951_82DF_4555_A6BD_108C9CEAFFDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddHTDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddHTDlg dialog

class CAddHTDlg : public CDialog
{
// Construction
public:
	void OnNewAddHT();
	bool GetEsyjr();
	BOOL AddHTTJ();
	CStringArray m_ArraySFKTJID;
	CStringArray m_ArrayKFID;
	CStringArray m_ArrayQYRID;
	void AddHT();
	void SFKMCCombox();
	void OnQRWCombox();
	CAddHTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddHTDlg)
	enum { IDD = IDD_ADDHT_DLG };
	CListCtrl	m_ListCtrlSFKTJ;
	CComboBox	m_ComboSFKMC;
	CComboBox	m_Combo_QWR;
	CComboBox	m_CbomboKFMC;
	CComboBox	m_ComboKFLX;
	UINT	m_uTCBL;
	double	m_Ehtjr;
	double	m_Ejr;
	CTime	m_TimeQWRQ;
	CTime	m_TimeFKSJ;
	CString	m_EBz;
	CString	m_Ehtbh;
	CString	m_EXmms;
	double	m_Esyjr;
	CString	m_EMoneyDS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddHTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddHTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboKflx();
	afx_msg void OnBtnAddtj();
	afx_msg void OnBtnDeltj();
	afx_msg void OnBtnAddht();
	afx_msg void OnBtnJrds();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDHTDLG_H__75929951_82DF_4555_A6BD_108C9CEAFFDE__INCLUDED_)
