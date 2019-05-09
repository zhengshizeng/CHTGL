#if !defined(AFX_KPGL_DLG_H__DFAA717E_B1A1_4713_BC50_79CB13BBF42C__INCLUDED_)
#define AFX_KPGL_DLG_H__DFAA717E_B1A1_4713_BC50_79CB13BBF42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Kpgl_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKpgl_Dlg dialog

class CKpgl_Dlg : public CDialog
{
// Construction
public:
	void SetHTBH(CString htbh);
	BOOL GetHTMoneyByHTBH();
	BOOL UpdateKPList();
	CKpgl_Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKpgl_Dlg)
	enum { IDD = IDD_DLG_KPGL };
	CComboBox	m_ComboFPLX;
	CListCtrl	m_List_KPMX;
	CString	m_EFPHM;
	float	m_EKPMoney;
	CTime	m_TimeKP;
	float	m_E1Money;
	float	m_E2Money;
	float	m_E3Money;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKpgl_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKpgl_Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddkp();
	afx_msg void OnBtnDel();
	afx_msg void OnItemchangedListKpmx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strHTBH;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KPGL_DLG_H__DFAA717E_B1A1_4713_BC50_79CB13BBF42C__INCLUDED_)
