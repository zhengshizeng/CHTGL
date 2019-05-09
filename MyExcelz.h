// MyExcelz.h: interface for the CMyExcelz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXCELZ_H__13D5C11D_E148_4838_B3AA_3257E93B686F__INCLUDED_)
#define AFX_MYEXCELZ_H__13D5C11D_E148_4838_B3AA_3257E93B686F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "excel.h"
class CMyExcelz  
{
public:
	void SetItemTextz(long x,long y,int idata);
	void SetItemTextz(long x,long y,CString str);
	CString m_sheelname;
	void DrawList(CListCtrl *listctrlx,int nCol,int nLine);
	void SaveExcel(CString XLSfilename);
	BOOL CreateEApplication(CString sheelname);
	CMyExcelz();
	virtual ~CMyExcelz();
private:
	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge;
};

#endif // !defined(AFX_MYEXCELZ_H__13D5C11D_E148_4838_B3AA_3257E93B686F__INCLUDED_)
