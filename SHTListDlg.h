#if !defined(AFX_SHTLISTDLG_H__B327ABF4_0F91_48BC_8DDC_2F09F05DEAF3__INCLUDED_)
#define AFX_SHTLISTDLG_H__B327ABF4_0F91_48BC_8DDC_2F09F05DEAF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SHTListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSHTListDlg dialog

class CSHTListDlg : public CDialog
{
// Construction
public:
	BOOL UpdateList(CString sqlTemp);
	CStringArray strKFArr,strGYArr;
	BOOL SelecCustomer(int ikflx);
	CStringArray m_ArrayQYRID;
	void OnQRWCombox();
	CSHTListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSHTListDlg)
	enum { IDD = IDD_DLG_SHT };
	CComboBox	m_Combo_GongYi;
	CComboBox	m_Combo_KeFu;
	CComboBox	m_Combo_QWR;
	CComboBox	m_ComboTJ;
	CListCtrl	m_ListHTl;
	CTime	m_TimeS;
	CTime	m_TimeE;
	CString	m_EHtbh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHTListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSHTListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSelect();
	afx_msg void OnCHECKGongYi();
	afx_msg void OnCHECKKeFu();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnCkxq();
	afx_msg void OnItemchangedListHtl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHTLISTDLG_H__B327ABF4_0F91_48BC_8DDC_2F09F05DEAF3__INCLUDED_)
