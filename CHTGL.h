// CHTGL.h : main header file for the CHTGL application
//

#if !defined(AFX_CHTGL_H__D3A61C6C_F025_4AAF_8355_79A093748C24__INCLUDED_)
#define AFX_CHTGL_H__D3A61C6C_F025_4AAF_8355_79A093748C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCHTGLApp:
// See CHTGL.cpp for the implementation of this class
//

class CCHTGLApp : public CWinApp
{
public:
	double OnSelectCount(CString str);
	CString MoneytoDS(double dmoney);
	BOOL ExecuteSql(CString strsql);
//	void ExportExcel(CListCtrl *listctrlx,CString XLSfilename);
	BOOL CreateConn();
	CCHTGLApp();
	_ConnectionPtr m_pConn;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHTGLApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCHTGLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTGL_H__D3A61C6C_F025_4AAF_8355_79A093748C24__INCLUDED_)
