// YuJingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "YuJingDlg.h"

#include "SelectHTDLG.h"
#include "MyExcelz.h"
#include "AddSFKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CYuJingDlg dialog


CYuJingDlg::CYuJingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYuJingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYuJingDlg)
	m_EHtbh = _T("");
	//}}AFX_DATA_INIT
}


void CYuJingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYuJingDlg)
	DDX_Control(pDX, IDC_LIST_SK, m_List_SK);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_EHtbh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYuJingDlg, CDialog)
	//{{AFX_MSG_MAP(CYuJingDlg)
	ON_BN_CLICKED(IDC_BTN_SELECTHT, OnBtnSelectht)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SK, OnItemchangedListSk)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_BN_CLICKED(IDC_BTN_ADDSK, OnBtnAddsk)
	ON_BN_CLICKED(IDC_BTN_ADDFK, OnBtnAddfk)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuJingDlg message handlers

BOOL CYuJingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List_SK.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_List_SK.InsertColumn(0,_T("类型"),LVCFMT_LEFT,70,-1);
	m_List_SK.InsertColumn(1,_T("合同编号"),LVCFMT_LEFT,160,-1);
	m_List_SK.InsertColumn(2,_T("付款名称"),LVCFMT_LEFT,180,-1);
	m_List_SK.InsertColumn(3,_T("预计日期"),LVCFMT_LEFT,120,-1);
	m_List_SK.InsertColumn(4,_T("预计金额"),LVCFMT_LEFT,100,-1);
	m_List_SK.InsertColumn(5,_T("过期天数"),LVCFMT_LEFT,80,-1);
	m_List_SK.SetLineColor(RGB(242,247,250),RGB(238,238,238));
	m_List_SK.SetHeadColor(RGB(210,230,250),RGB(1,86,167),RGB(185,217,232));
	m_List_SK.SetTextColor(RGB(251,21,21));


//	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Select T.TypeName,KFLX,ExpectMoney,ExpectData,CustomerID from Receivables R, TypeofCollection T  Where OKSFK=0 and ExpectData<#2018-04-05# and T.TypeCID=R.TypeCID

void CYuJingDlg::OnBtnSelectht() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CSelectHTDLG selectHTdlg;
	selectHTdlg.SetHTBH(m_EHtbh);
	selectHTdlg.DoModal();
}


BOOL CYuJingDlg::UpdateList()
{	
	int k = 0;
	CString tempk;
	m_List_SK.DeleteAllItems();//清空列表
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		CTime tempTime;
		tempTime=CTime::GetCurrentTime();		
		temp.Format("Select T.TypeName,KFLX,ExpectMoney,ExpectData,CustomerID,datediff('d',ExpectData, now) as BZ from Receivables R, TypeofCollection T  Where OKSFK=0 and ExpectData<#%s# and T.TypeCID=R.TypeCID",tempTime.Format("%Y-%m-%d"));
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strKFLX,strTypeName,strExpectMoney,strExpectData,strCustomerID,strBZ;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("KFLX");
				if (vat.vt != VT_NULL)
				{
					strKFLX = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("TypeName");
				if (vat.vt != VT_NULL)
				{
					strTypeName = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("ExpectMoney");
				if (vat.vt != VT_NULL)
				{
					strExpectMoney = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("ExpectData");
				if (vat.vt != VT_NULL)
				{
					strExpectData = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("CustomerID");
				if (vat.vt != VT_NULL)
				{
					strCustomerID = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("BZ");
				if (vat.vt != VT_NULL)
				{
					strBZ = (LPCSTR)_bstr_t(vat);
				}

				if (strKFLX==_T("0"))
				{
					m_List_SK.InsertItem(k,"收款<--");					
				}
				else
				{
					m_List_SK.InsertItem(k,"付款-->");
				}
				m_List_SK.SetItemText(k,1,strCustomerID);	
				m_List_SK.SetItemText(k,2,strTypeName);					
				m_List_SK.SetItemText(k,3,strExpectData);
				m_List_SK.SetItemText(k,4,strExpectMoney);
				m_List_SK.SetItemText(k,5,strBZ+"天");
				k++;
	
				pSet->MoveNext();
			}
		}
		else
		{	
			TRACE("查询到记录为空\n");
			return FALSE;
		}
	}
	catch (_com_error &comError)
	{
		tempk.Format("错误提示,UpdateKFList更新列表失败!%s",comError.Description());
		AfxMessageBox(tempk);
		return FALSE;
	}
	return TRUE;
}

void CYuJingDlg::OnItemchangedListSk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_EHtbh = m_List_SK.GetItemText(pNMListView->iItem,1);
	UpdateData(FALSE);
	*pResult = 0;
}

void CYuJingDlg::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CString fileName;
	
	fileName.Format("预警信息");
		
	
	CMyExcelz myexcelz;
	if (myexcelz.CreateEApplication("Sheet1")==TRUE)
	{
		myexcelz.SetItemTextz(1,1,fileName);
		myexcelz.DrawList(&m_List_SK,3,1);
		myexcelz.SaveExcel(fileName);
	}
}

void CYuJingDlg::OnBtnAddsk() 
{
	// TODO: Add your control notification handler code here
	if(m_EHtbh.IsEmpty())
	{
		AfxMessageBox("请选择要新增收款的合同");
	}
	else
	{
		::SendMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,9,31);
		::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,1,LPARAM(new CString(m_EHtbh)));
	}

}

void CYuJingDlg::OnBtnAddfk() 
{
	// TODO: Add your control notification handler code here
	if(m_EHtbh.IsEmpty())
	{
		AfxMessageBox("请选择要新增付款的合同");
	}
	else
	{
		::SendMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,9,32);
		::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,1,LPARAM(new CString(m_EHtbh)));
	}
}

void CYuJingDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,773,506,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

HBRUSH CYuJingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if ( nCtlColor==CTLCOLOR_DLG  || nCtlColor ==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);  
		pDC->SetTextColor(RGB(20,20,20));
		HBRUSH   hbr1=CreateSolidBrush(RGB(255,255,255)); 
		return   hbr1; 
 	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CYuJingDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow)
	{
		TRACE("OnShowWindow 显示=%d \n",bShow);
		UpdateList();
	}
	else
	{
		TRACE("OnShowWindow 隐藏=%d \n",bShow);
	}
}
