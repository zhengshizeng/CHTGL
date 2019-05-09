// MyExcelz.cpp: implementation of the CMyExcelz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chtgl.h"
#include "MyExcelz.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyExcelz::CMyExcelz()
{

}

CMyExcelz::~CMyExcelz()
{

}

BOOL CMyExcelz::CreateEApplication(CString sheelname)
{
	//创建Excel 2000服务器(启动Excel) 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return FALSE;
	}
	m_sheelname=sheelname;
	ExcelApp.SetVisible(false); 
	//利用模板文件建立新文档 
	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path);
	CString strPath = path;
	strPath += "\\导出模板.xls";
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 
	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strPath)));
	//得到Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true);
	//得到sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t(m_sheelname)),true);
	//wsMysheet.SetName(XLSfilename);
	// 	//添加模板个数
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true);
	return TRUE;
}


void CMyExcelz::SaveExcel(CString XLSfilename)
{
	CFileDialog dlg(FALSE,"Worksheet Files (*.xls)|*.xls",XLSfilename,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"Worksheet Files(*.xls)|*.xls|All Files (*.*)|*.*||");
	if(dlg.DoModal()==IDOK)
	{
		XLSfilename=dlg.GetPathName();
	}
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t(m_sheelname)),true);
	wsMysheet.Activate();
//	strPath.Format("%s\\%s.xls",path,XLSfilename);
	wsMysheet.SaveAs(XLSfilename,vtMissing,vtMissing,vtMissing,vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);
	ExcelApp.SetVisible(true); 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch();
}

void CMyExcelz::DrawList(CListCtrl *listctrlx, int nCol, int nLine)
{
	CHeaderCtrl*   pHeader   = listctrlx->GetHeaderCtrl(); 
	//获得行，列的个数 
	int   nColCount   =   pHeader-> GetItemCount(); //列
	int   nLineCount   =   listctrlx->GetItemCount();  //行
	nColCount = nColCount < 1? 1: nColCount;
	
	HDITEM   hdi;  
	TCHAR     lpBuffer[256]; 
	//	LPCTSTR   lpszmyString; 
	hdi.mask   =   HDI_TEXT; 
	hdi.pszText   =   lpBuffer;  
	hdi.cchTextMax   =   256; 
	
	CString str;
	for (int j   =0;   j <nColCount;   j++ )
	{
		pHeader->GetItem( j, &hdi );
        str= hdi.pszText;
		rgMyRge.SetItem(_variant_t((long)(nCol-1)),_variant_t((long)(j+nLine)),_variant_t(str));
	}
	
	for(int i =0;   i <nLineCount ;  i++) 
	{ 
		for(int j   =0;   j <nColCount;   j++) 
		{ 
			CString str;
			//	str.Format("%d",i);
			str=listctrlx->GetItemText(i,j);
			rgMyRge.SetItem(_variant_t((long)(i+nCol)),_variant_t((long)(j+nLine)),_variant_t(str)); 			
		}
	}
}

void CMyExcelz::SetItemTextz(long x, long y, CString str)
{
	rgMyRge.SetItem(_variant_t((long)(x)),_variant_t((long)(y)),_variant_t(str));
}

void CMyExcelz::SetItemTextz(long x, long y, int idata)
{
	rgMyRge.SetItem(_variant_t((long)(x)),_variant_t((long)(y)),_variant_t((long)(idata)));
}
