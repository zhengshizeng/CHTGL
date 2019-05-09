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
	//����Excel 2000������(����Excel) 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return FALSE;
	}
	m_sheelname=sheelname;
	ExcelApp.SetVisible(false); 
	//����ģ���ļ��������ĵ� 
	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path);
	CString strPath = path;
	strPath += "\\����ģ��.xls";
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 
	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strPath)));
	//�õ�Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true);
	//�õ�sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t(m_sheelname)),true);
	//wsMysheet.SetName(XLSfilename);
	// 	//���ģ�����
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
	//����У��еĸ��� 
	int   nColCount   =   pHeader-> GetItemCount(); //��
	int   nLineCount   =   listctrlx->GetItemCount();  //��
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
