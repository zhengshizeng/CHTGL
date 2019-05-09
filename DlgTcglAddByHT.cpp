// DlgTcglAddByHT.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "DlgTcglAddByHT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CDlgTcglAddByHT dialog


CDlgTcglAddByHT::CDlgTcglAddByHT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTcglAddByHT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTcglAddByHT)
	m_DateTime = 0;
	m_EdBl = 2.0;
	m_EdHkjr = 0.0;
	m_EHTBH = _T("");
	m_EdHtjr = 0.0;
	m_EdKT = 0.0;
	m_EdTcMoney = 0.0;
	m_EdWT = 0.0;
	m_EdYT = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgTcglAddByHT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTcglAddByHT)
	DDX_Control(pDX, IDC_LIST_TCMC, m_ListTCMC);
	DDX_Control(pDX, IDC_LIST_HKMC, m_ListHKMC);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_DateTime);
	DDX_Text(pDX, IDC_EDIT_BL, m_EdBl);
	DDX_Text(pDX, IDC_EDIT_HKJR, m_EdHkjr);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_EHTBH);
	DDX_Text(pDX, IDC_EDIT_HTJR, m_EdHtjr);
	DDX_Text(pDX, IDC_EDIT_KT, m_EdKT);
	DDX_Text(pDX, IDC_EDIT_TCMoney, m_EdTcMoney);
	DDX_Text(pDX, IDC_EDIT_WT, m_EdWT);
	DDX_Text(pDX, IDC_EDIT_YT, m_EdYT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTcglAddByHT, CDialog)
	//{{AFX_MSG_MAP(CDlgTcglAddByHT)
	ON_BN_CLICKED(IDC_BTN_SETBL, OnBtnSetbl)
	ON_BN_CLICKED(IDC_BTN_ADDTCMC, OnBtnAddtcmc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTcglAddByHT message handlers

void CDlgTcglAddByHT::OnBtnSetbl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EdBl>=0.0 && m_EdBl<=100.0)
	{
		m_EdKT=m_EdHtjr*m_EdBl/100;
		m_EdWT=m_EdKT-m_EdYT;
	}
	else
	{
		AfxMessageBox("提成比例设置范围 0-100  %");
	}
	UpdateData(FALSE);
}

BOOL CDlgTcglAddByHT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListHKMC.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListHKMC.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListHKMC.InsertColumn(1,_T("回款时间"),LVCFMT_LEFT,100,-1);
	m_ListHKMC.InsertColumn(2,_T("回款金额"),LVCFMT_LEFT,100,-1);
	m_ListHKMC.InsertColumn(3,_T("预收时间"),LVCFMT_LEFT,100,-1);
	m_ListHKMC.InsertColumn(4,_T("预计收款"),LVCFMT_LEFT,100,-1);
	//m_ListCtrlHT.InsertColumn(5,_T("未提成金额"),LVCFMT_LEFT,100,-1);
	
	m_ListTCMC.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListTCMC.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListTCMC.InsertColumn(1,_T("提成时间"),LVCFMT_LEFT,160,-1);
	m_ListTCMC.InsertColumn(2,_T("提成金额"),LVCFMT_LEFT,100,-1);

	m_DateTime=CTime::GetCurrentTime();
	OnMCSelect();
	OnSelectHKList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTcglAddByHT::OnBtnAddtcmc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString temp;
	temp.Format("INSERT INTO ExtractM  (TCMoney,TCTime,CustomerID) values('%.2f','%s','%s')",m_EdTcMoney,m_DateTime.Format("%Y-%m-%d"),m_EHTBH);				
	if(theApp.ExecuteSql(temp)==TRUE)
	{
		AfxMessageBox("增加完成!");
		m_EdTcMoney=0.0;
		UpdateData(FALSE);
		UpdateListTCMC();
	}
	
}

void CDlgTcglAddByHT::UpdateListTCMC()
{
	UpdateData(TRUE);
	int k = 0;
	CString tempk;
	double tempytcjr;
	tempytcjr=0.0f;
	m_ListTCMC.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select * from ExtractM where CustomerID='%s' ",m_EHTBH);
		TRACE("%s\n",temp);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strMoney,strTime;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("TCMoney");
				if (vat.vt != VT_NULL)
				{
					strMoney = (LPCSTR)_bstr_t(vat);
				}else{strMoney=_T("");}
				vat =pSet->GetCollect("TCTime");
				if (vat.vt != VT_NULL)
				{
					strTime = (LPCSTR)_bstr_t(vat);
				}else{strTime=_T("");}
				
				tempk.Format("%d",k+1);
				m_ListTCMC.InsertItem(k,tempk);				
				m_ListTCMC.SetItemText(k,1,strTime);
				m_ListTCMC.SetItemText(k,2,strMoney);
				
				tempytcjr+=atof(strMoney);
				k++;
				pSet->MoveNext();
			}
		}
		else
		{	
			AfxMessageBox("没有符合条件的数据!");
			return ;
		}
	}
	catch (_com_error &comError)
	{
		tempk.Format("错误提示,UpdateListTCMC 更新列表失败!%s",comError.Description());
		AfxMessageBox(tempk);
	}
	m_EdYT=tempytcjr;
	UpdateData(FALSE);
}

void CDlgTcglAddByHT::OnMCSelect()
{
	CString tempSql;
	tempSql.Format("Select HTMoney as countN from ContractHT where HTBH='%s' ",m_EHTBH);
	m_EdHtjr=theApp.OnSelectCount(tempSql);
	tempSql.Format("Select sum(SJMoney) as countN from Receivables where CustomerID='%s' and OKSFK=1 ",m_EHTBH);
	m_EdHkjr=theApp.OnSelectCount(tempSql);
	
	UpdateData(FALSE);
	UpdateListTCMC();
}

void CDlgTcglAddByHT::OnSelectHKList()
{
	UpdateData(TRUE);
	int k = 0;
	CString tempk;
	m_ListHKMC.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select * from Receivables where CustomerID='%s' and OKSFK=1 ",m_EHTBH);
		TRACE("%s\n",temp);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strDate,strMoney,stryjD,stryjM;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("SJDate");
				if (vat.vt != VT_NULL)
				{
					strDate = (LPCSTR)_bstr_t(vat);
				}else{strDate=_T("");}
				vat =pSet->GetCollect("SJMoney");
				if (vat.vt != VT_NULL)
				{
					strMoney = (LPCSTR)_bstr_t(vat);
				}else{strMoney=_T("");}
				
				vat =pSet->GetCollect("ExpectData");
				if (vat.vt != VT_NULL)
				{
					stryjD = (LPCSTR)_bstr_t(vat);
				}else{stryjD=_T("");}
				
				vat =pSet->GetCollect("ExpectMoney");
				if (vat.vt != VT_NULL)
				{
					stryjM = (LPCSTR)_bstr_t(vat);
				}else{stryjM=_T("");}
				
				tempk.Format("%d",k+1);
				m_ListHKMC.InsertItem(k,tempk);
				m_ListHKMC.SetItemText(k,1,strDate);
				m_ListHKMC.SetItemText(k,2,strMoney);
				m_ListHKMC.SetItemText(k,3,stryjD);
				m_ListHKMC.SetItemText(k,4,stryjM);
				k++;
				pSet->MoveNext();
			}
		}
		else
		{	
			AfxMessageBox("没有符合条件的数据!");
			return ;
		}
	}
	catch (_com_error &comError)
	{
		tempk.Format("错误提示,UpdateKFList更新列表失败!%s",comError.Description());
		AfxMessageBox(tempk);
	}
}

void CDlgTcglAddByHT::SetHTBH(CString htbh)
{
	m_EHTBH=htbh;
}
