// AddSFKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "AddSFKDlg.h"
#include "SelectHTDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAddSFKDlg dialog


CAddSFKDlg::CAddSFKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSFKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddSFKDlg)
	m_EHtbh = _T("");
	m_ETj = _T("");
	m_EYjjr =0.0f;
	m_ESjjr = 0.0f;
	m_EYjsj = _T("");
	m_TimeSJ = 0;
	m_EYH = _T("");
	//}}AFX_DATA_INIT
}


void CAddSFKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSFKDlg)
	DDX_Control(pDX, IDC_LIST_SFKTJ, m_ListSFKTJ);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_EHtbh);
	DDX_Text(pDX, IDC_EDIT_TJ, m_ETj);
	DDX_Text(pDX, IDC_EDIT_YJJR, m_EYjjr);
	DDX_Text(pDX, IDC_EDIT_SJJR, m_ESjjr);
	DDX_Text(pDX, IDC_EDIT_YJSJ, m_EYjsj);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_TimeSJ);
	DDX_Text(pDX, IDC_EDIT_YH, m_EYH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSFKDlg, CDialog)
	//{{AFX_MSG_MAP(CAddSFKDlg)
	ON_BN_CLICKED(IDC_BTN_HTXQ, OnBtnHtxq)
	ON_BN_CLICKED(IDC_BTN_ADDSF, OnBtnAddsf)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SFKTJ, OnItemchangedListSfktj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSFKDlg message handlers

BOOL CAddSFKDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListSFKTJ.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListSFKTJ.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListSFKTJ.InsertColumn(1,_T("收付款条件"),LVCFMT_LEFT,180,-1);
	m_ListSFKTJ.InsertColumn(2,_T("预计时间"),LVCFMT_LEFT,100,-1);
	m_ListSFKTJ.InsertColumn(3,_T("预计金额"),LVCFMT_LEFT,80,-1);
	m_ListSFKTJ.InsertColumn(4,_T("实计时间"),LVCFMT_LEFT,100,-1);
	m_ListSFKTJ.InsertColumn(5,_T("实计金额"),LVCFMT_LEFT,80,-1);
	m_ListSFKTJ.InsertColumn(6,_T("银行"),LVCFMT_LEFT,150,-1);
	m_ListSFKTJ.InsertColumn(7,_T("RID"),LVCFMT_LEFT,-20,-1);


	m_TimeSJ=CTime::GetCurrentTime();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddSFKDlg::SetHTBHAndKFLX(CString htbh, int ikflx)
{
	m_ikflx=ikflx;
	m_EHtbh=htbh;
	if (m_ikflx==0)
	{
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("收款条件明细表");
		GetDlgItem(IDC_STATIC_TJ)->SetWindowText("收款条件:");
		GetDlgItem(IDC_STATIC_TJ2)->SetWindowText("预收时间:");
		GetDlgItem(IDC_STATIC_TJ3)->SetWindowText("预收金额:");
		GetDlgItem(IDC_STATIC_TJ4)->SetWindowText("实收时间:");
		GetDlgItem(IDC_STATIC_TJ5)->SetWindowText("实收金额:");
	}
	else
	{
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("付款条件明细表");
		GetDlgItem(IDC_STATIC_TJ)->SetWindowText("付款条件:");
		GetDlgItem(IDC_STATIC_TJ2)->SetWindowText("预付时间:");
		GetDlgItem(IDC_STATIC_TJ3)->SetWindowText("预付金额:");
		GetDlgItem(IDC_STATIC_TJ4)->SetWindowText("实付时间:");
		GetDlgItem(IDC_STATIC_TJ5)->SetWindowText("实付金额:");
	}
	if (!m_EHtbh.IsEmpty())
	{
		UpdateSFKTJList();
	}
}

BOOL CAddSFKDlg::UpdateSFKTJList()
{	
	int k = 0;
	CString tempk;
	m_ListSFKTJ.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select TypeName,ExpectMoney,ExpectData,SJMoney,SJDate,RID,BankNo from Receivables R, TypeofCollection T where T.TypeCID=R.TypeCID and CustomerID='%s' ",m_EHtbh);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strTypeName,strExMoney,strExData,strSMoney,strSDate,strRid,strBankNo;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				strTypeName=_T("");
				strExMoney=_T("");
				strExData=_T("");
				strSMoney=_T("");
				strSDate=_T("");
				strRid=_T("");
				strBankNo=_T("");
				vat =pSet->GetCollect("TypeName");
				if (vat.vt != VT_NULL)
				{
					strTypeName = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("ExpectMoney");
				if (vat.vt != VT_NULL)
				{
					strExMoney = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("ExpectData");
				if (vat.vt != VT_NULL)
				{
					strExData = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("SJMoney");
				if (vat.vt != VT_NULL)
				{
					strSMoney = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("SJDate");
				if (vat.vt != VT_NULL)
				{
					strSDate = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("BankNo");
				if (vat.vt != VT_NULL)
				{
					strBankNo = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("RID");
				if (vat.vt != VT_NULL)
				{
					strRid = (LPCSTR)_bstr_t(vat);
				}
				tempk.Format("%d",k+1);
				m_ListSFKTJ.InsertItem(k,tempk);
				m_ListSFKTJ.SetItemText(k,1,strTypeName);
				m_ListSFKTJ.SetItemText(k,2,strExData);
				m_ListSFKTJ.SetItemText(k,3,strExMoney);				
				m_ListSFKTJ.SetItemText(k,4,strSDate);
				m_ListSFKTJ.SetItemText(k,5,strSMoney);
				m_ListSFKTJ.SetItemText(k,6,strBankNo);
				m_ListSFKTJ.SetItemText(k,7,strRid);
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

void CAddSFKDlg::OnBtnHtxq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CSelectHTDLG selectHTdlg;
	selectHTdlg.SetHTBH(m_EHtbh);
	selectHTdlg.DoModal();
}

void CAddSFKDlg::OnBtnAddsf() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString temp;
	
	if (m_ESjjr!=m_EYjjr)
	{
		temp.Format("实际金额和预计金额不一样,是否继续增加!");
		if(MessageBox(temp,"增加提示" ,MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
		{
			m_ESjjr=m_EYjjr;
			UpdateData(FALSE);
			return ;
		}
	}
	
	temp.Format("UPDATE Receivables SET SJMoney='%.2f',SJDate='%s',BankNo='%s',OKSFK='1' WHERE RID=%s ",m_ESjjr,m_TimeSJ.Format("%Y-%m-%d"),m_EYH,strRID);				
	if(theApp.ExecuteSql(temp)==TRUE)
	{
		AfxMessageBox("增加完成!");
		m_ESjjr=0.0f;
		UpdateSFKTJList();	
	}
}

void CAddSFKDlg::OnItemchangedListSfktj(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_ETj = m_ListSFKTJ.GetItemText(pNMListView->iItem,1);
	m_EYjsj = m_ListSFKTJ.GetItemText(pNMListView->iItem,2);
	m_EYjjr = atof(m_ListSFKTJ.GetItemText(pNMListView->iItem,3));
	strRID= m_ListSFKTJ.GetItemText(pNMListView->iItem,7);
	UpdateData(FALSE);
	*pResult = 0;
}
