// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6FD0BFC3_BF8F_434E_A425_2C228CA51C76__INCLUDED_)
#define AFX_STDAFX_H__6FD0BFC3_BF8F_434E_A425_2C228CA51C76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#undef   WINVER    
#define   WINVER   0X5000
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define WM_CLIENT_MSG WM_USER+86

#include "CMFC5286D.H"
#pragma comment(lib,"CMFC5286D.lib")
/*����ADO�ľ���*/
#pragma warning(disable: 4146)
// #pragma warning(disable: 4244)
#import "C:\Program Files\Common Files\SYSTEM\ADO\msado15.dll" no_namespace rename("EOF","adoEOF")
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6FD0BFC3_BF8F_434E_A425_2C228CA51C76__INCLUDED_)
