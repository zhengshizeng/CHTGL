// CHTGL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CHTGL.h"
#include "CHTGLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "excel.h"
/////////////////////////////////////////////////////////////////////////////
// CCHTGLApp

BEGIN_MESSAGE_MAP(CCHTGLApp, CWinApp)
	//{{AFX_MSG_MAP(CCHTGLApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHTGLApp construction

CCHTGLApp::CCHTGLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCHTGLApp object

CCHTGLApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCHTGLApp initialization

BOOL CCHTGLApp::InitInstance()
{
	AfxEnableControlContainer();
	CoInitialize(NULL);
	if(FALSE==CreateConn())
	{
		return FALSE;
	}
// 	CString temp=MoneytoDS(123456.892);
// 	AfxMessageBox(temp);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCHTGLDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CCHTGLApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	CoUninitialize();
	return CWinApp::ExitInstance();
}

BOOL CCHTGLApp::CreateConn()
{
	m_pConn.CreateInstance("ADODB.Connection");
	if(m_pConn == NULL)//CoInitialize（NULL）未初始化
	{
		AfxMessageBox("初始化连接对象失败!");
		return FALSE;
	}
	HRESULT res = -1;
	try
	{
		//建立数据库连接
		CString Sqlstr;
		Sqlstr.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s","Data.zdb");
		res = m_pConn->Open((_bstr_t)Sqlstr,"","",0);
		
		if(res == S_OK)//0
		{
			TRACE("打开数据库成功!");
		}
		else
		{
			TRACE("打开数据库失败!");
			return FALSE;
		}
	}
	catch(_com_error e)		//捕捉异常
	{
		CString errormessage;
		errormessage.Format("数据库提示,连接数据库失败!,错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return FALSE;
	}
	return TRUE;
}
  

// BOOL CAdoConnection::ConnectAccess(CString dbpath, CString pass, long lOptions)
// {
// 	CString strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=") + dbpath;
// 	if (pass != _T("")) 
// 	{
// 		strConnect += _T("Jet OLEDB:Database Password=") + pass + _T(";");
// 	}
// 	return Open(LPCTSTR(strConnect), lOptions);
// }

double CCHTGLApp::OnSelectCount(CString str)
{
	double rdNum;
	CString sqltemp;
	try
	{
		sqltemp=str;
		TRACE("%s\n",sqltemp);
		VARIANT cnt;
		cnt.vt = VT_INT;
		_RecordsetPtr pSet =m_pConn->Execute((_bstr_t)sqltemp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL && (!pSet->adoEOF))
		{
			vat =pSet->GetCollect("countN");
			if (vat.vt != VT_NULL)
			{
				rdNum=atof((LPCSTR)_bstr_t(vat));				
			}
			pSet->Close();
			pSet.Release();
		}
	}
	catch (_com_error &comError)
	{
		sqltemp.Format("OnComboxCL Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(sqltemp);
		return 0.0f;
	}
	return rdNum;
}

BOOL CCHTGLApp::ExecuteSql(CString strsql)
{	
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		theApp.m_pConn->Execute((_bstr_t)strsql,&cnt,adCmdUnknown);
	}
	catch (_com_error &comError)
	{
		CString temp;
		temp.Format("AddHTTJ Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(temp);
		return FALSE;
	}	
	return TRUE;
}

CString CCHTGLApp::MoneytoDS(double dmoney)
{
	CString m_szRMB,m_szNumber;
	m_szNumber.Format("%.2lf",dmoney);
    int pos = m_szNumber.Find(_T("."));  
	
    CString szInteger, szFloat;  
    if (pos != -1)  
    {  
        szInteger = m_szNumber.Left(pos);  
        szFloat = m_szNumber.Mid(pos+1);  
        if (szFloat.GetLength() > 2)  
        {  
            szFloat = szFloat.Left(2);  
        }  
    }else{  
        szInteger = m_szNumber;  
    }  
	
    CString szNumberSeed = _T("零壹贰叁肆伍陆柒捌玖");  
    CString szRMBSeed = _T("元拾佰仟万拾佰仟亿拾佰仟万");  
    LPCTSTR lpInteger = (LPCTSTR)szInteger;  
	
    CString szRMB = _T("");  
    int iCount = 0;  
    for (int i= szInteger.GetLength() - 1; i > -1; i--)  
    {  
        char cNumber = lpInteger[i];  
        int nNumber = atoi(&cNumber);  
        szRMB = szNumberSeed.Mid(nNumber * 2, 2) + szRMBSeed.Mid(iCount * 2,2) + szRMB;  
        iCount++;  
    }  
	
    CString szRMBFloat = _T("");  
    LPCTSTR lpFloat = (LPCTSTR)szFloat;  
    if (szFloat.GetLength() > 0)  
    {  
        char cNumber = lpFloat[0];  
        int nNumber = atoi(&cNumber);  
        szRMB += szNumberSeed.Mid(nNumber * 2, 2) + _T("角");  
    }  
	
    if (szFloat.GetLength() > 1)  
    {  
        char cNumber = lpFloat[1];  
        int nNumber = atoi(&cNumber);  
        szRMB += szNumberSeed.Mid(nNumber * 2, 2) + _T("分");  
    }  
	
    m_szRMB = szRMB;  
	
    
	return m_szRMB;
}
