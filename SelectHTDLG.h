#if !defined(AFX_SELECTHTDLG_H__A14096E0_C0EE_4068_9D16_3B118A5FB275__INCLUDED_)
#define AFX_SELECTHTDLG_H__A14096E0_C0EE_4068_9D16_3B118A5FB275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectHTDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectHTDLG dialog

class CSelectHTDLG : public CDialog
{
// Construction
public:
	int m_ikflx;
	BOOL UpdateKPList();
	BOOL UpdateSFKTJList();
	void SelectFromDB();
	void SetHTBH(CString htbh);
	CSelectHTDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectHTDLG)
	enum { IDD = IDD_SELECTHT_DLG };
	CListCtrl	m_List_KPMX;
	CListCtrl	m_ListSFKTJ;
	CString	m_EKFLX;
	CString	m_EKFMC;
	CString	m_EQYR;
	CString	m_ETCBL;
	CString	m_EJR;
	CString	m_EHTJR;
	CString	m_EHTBH;
	CString	m_EBZ;
	CString	m_EXMMS;
	COleDateTime	m_DateTime;
	double	m_Ekp1;
	double	m_Ekp2;
	double	m_Ekp3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectHTDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectHTDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExportxls();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTHTDLG_H__A14096E0_C0EE_4068_9D16_3B118A5FB275__INCLUDED_)
