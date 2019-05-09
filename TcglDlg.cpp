// TcglDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "TcglDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CTcglDlg dialog


CTcglDlg::CTcglDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcglDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcglDlg)
	m_ENianDu = 0;
	m_Ehtbh = _T("");
	m_Edhtjr = 0.0;
	m_EdKT = 0.0;
	m_EdTCMoney = 0.0;
	m_EdWT = 0.0;
	m_EdYT = 0.0;
	m_EBl = 2.0;
	m_EHkjr = 0.0;
	m_DateTime = 0;
	//}}AFX_DATA_INIT
}


void CTcglDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcglDlg)
	DDX_Control(pDX, IDC_LIST_HT2, m_ListCtrlHt2);
	DDX_Control(pDX, IDC_LIST_HT, m_ListCtrlHT);
	DDX_Control(pDX, IDC_COMBO_QWR, m_Combo_QWR);
	DDX_Text(pDX, IDC_EDIT_NIANDU, m_ENianDu);
	DDV_MinMaxUInt(pDX, m_ENianDu, 2000, 2030);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_Ehtbh);
	DDX_Text(pDX, IDC_EDIT_HTJR, m_Edhtjr);
	DDX_Text(pDX, IDC_EDIT_KT, m_EdKT);
	DDX_Text(pDX, IDC_EDIT_TCMoney, m_EdTCMoney);
	DDX_Text(pDX, IDC_EDIT_WT, m_EdWT);
	DDX_Text(pDX, IDC_EDIT_YT, m_EdYT);
	DDX_Text(pDX, IDC_EDIT_BL, m_EBl);
	DDX_Text(pDX, IDC_EDIT_HKJR, m_EHkjr);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_DateTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTcglDlg, CDialog)
	//{{AFX_MSG_MAP(CTcglDlg)
	ON_BN_CLICKED(IDC_BTN_SELECTHT, OnBtnSelectht)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_HT, OnItemchangedListHt)
	ON_BN_CLICKED(IDC_BTN_MCSELECT, OnBtnMcselect)
	ON_BN_CLICKED(IDC_BTN_SETBL, OnBtnSetbl)
	ON_BN_CLICKED(IDC_BTN_ADDTCMC, OnBtnAddtcmc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcglDlg message handlers

BOOL CTcglDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListCtrlHT.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListCtrlHT.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListCtrlHT.InsertColumn(1,_T("合同编号"),LVCFMT_LEFT,160,-1);
	m_ListCtrlHT.InsertColumn(2,_T("回款时间"),LVCFMT_LEFT,100,-1);
	m_ListCtrlHT.InsertColumn(3,_T("回款金额"),LVCFMT_LEFT,100,-1);
	m_ListCtrlHT.InsertColumn(4,_T("预收时间"),LVCFMT_LEFT,100,-1);
	m_ListCtrlHT.InsertColumn(5,_T("预计收款"),LVCFMT_LEFT,100,-1);
	//m_ListCtrlHT.InsertColumn(5,_T("未提成金额"),LVCFMT_LEFT,100,-1);

	m_ListCtrlHt2.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListCtrlHt2.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListCtrlHt2.InsertColumn(1,_T("提成时间"),LVCFMT_LEFT,160,-1);
	m_ListCtrlHt2.InsertColumn(2,_T("提成金额"),LVCFMT_LEFT,100,-1);

	OnQRWCombox();
	//m_ENianDu=2018;
	m_DateTime=CTime::GetCurrentTime();
	m_ENianDu=m_DateTime.GetYear();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTcglDlg::OnBtnSelectht() 
{
	// TODO: Add your control notification handler code here
	//
	UpdateData(TRUE);
	int k = 0;
	CString tempk;
	m_ListCtrlHT.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select CustomerID,SJDate,SJMoney,ExpectData,ExpectMoney from Receivables where year(SJDate)=%d and OKSFK=1 and QWRID='%s' ",m_ENianDu,m_ArrayQYRID.GetAt(m_Combo_QWR.GetCurSel()));
		TRACE("%s\n",temp);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strBh,strDate,strMoney,stryjD,stryjM;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("CustomerID");
				if (vat.vt != VT_NULL)
				{
					strBh = (LPCSTR)_bstr_t(vat);
				}else{strBh=_T("");}
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
				m_ListCtrlHT.InsertItem(k,tempk);
				m_ListCtrlHT.SetItemText(k,1,strBh);
				m_ListCtrlHT.SetItemText(k,2,strDate);
				m_ListCtrlHT.SetItemText(k,3,strMoney);
				m_ListCtrlHT.SetItemText(k,4,stryjD);
				m_ListCtrlHT.SetItemText(k,5,stryjM);
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
	k=m_ListCtrlHT.GetItemCount();
	if (k==0)
	{
		AfxMessageBox("没有符合条件的数据!");
	}
	else
	{
		//
	}
}

void CTcglDlg::OnQRWCombox()
{
	int k=0;
	CString sqlTemp;
	
	m_Combo_QWR.ResetContent();
	try
	{
		sqlTemp.Format("Select QName,QID from QWR " );
		VARIANT cnt;
		cnt.vt = VT_INT;
		_RecordsetPtr pSet =theApp.m_pConn->Execute((_bstr_t)sqlTemp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL)
		{
			while (!pSet->adoEOF)
			{
				vat =pSet->GetCollect("QName");
				if (vat.vt != VT_NULL)
				{
					m_Combo_QWR.InsertString(k,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("QID");
				if (vat.vt != VT_NULL)
				{
					m_ArrayQYRID.Add((LPCSTR)_bstr_t(vat));
				}
				k++;
				pSet->MoveNext();				
			}
			pSet->Close();
			pSet.Release();
			m_Combo_QWR.SetCurSel(0);
		}
	}
	catch (_com_error &comError)
	{
		sqlTemp.Format("OnSelchangeComboKflx Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(sqlTemp);
	}	
}

void CTcglDlg::OnItemchangedListHt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_Ehtbh = m_ListCtrlHT.GetItemText(pNMListView->iItem,1);
	UpdateData(FALSE);
	*pResult = 0;
}

void CTcglDlg::OnBtnMcselect() 
{
	// TODO: Add your control notification handler code here
	CString tempSql;
	tempSql.Format("Select HTMoney as countN from ContractHT where HTBH='%s' ",m_Ehtbh);
	m_Edhtjr=theApp.OnSelectCount(tempSql);
		tempSql.Format("Select sum(SJMoney) as countN from Receivables where CustomerID='%s' and OKSFK=1 ",m_Ehtbh);
	m_EHkjr=theApp.OnSelectCount(tempSql);

	m_ehtbhT=m_Ehtbh;
	UpdateData(FALSE);
	UpdateListTCMC();
	
}

void CTcglDlg::OnBtnSetbl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EBl>=0.0 && m_EBl<=100.0)
	{
		m_EdKT=m_Edhtjr*m_EBl/100;
		m_EdWT=m_EdKT-m_EdYT;
	}
	else
	{
		AfxMessageBox("提成比例设置范围 0-100  %");
	}
	UpdateData(FALSE);
}

void CTcglDlg::UpdateListTCMC()
{
	UpdateData(TRUE);
	int k = 0;
	CString tempk;
	double tempytcjr;
	tempytcjr=0.0f;
	m_ListCtrlHt2.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select * from ExtractM where CustomerID='%s' ",m_ehtbhT);
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
				m_ListCtrlHt2.InsertItem(k,tempk);				
				m_ListCtrlHt2.SetItemText(k,1,strTime);
				m_ListCtrlHt2.SetItemText(k,2,strMoney);

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

void CTcglDlg::OnBtnAddtcmc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString temp;
	temp.Format("INSERT INTO ExtractM  (TCMoney,TCTime,CustomerID) values('%.2f','%s','%s')",m_EdTCMoney,m_DateTime.Format("%Y-%m-%d"),m_ehtbhT);				
	if(theApp.ExecuteSql(temp)==TRUE)
	{
		AfxMessageBox("增加完成!");
		m_EdTCMoney=0.0;	
		UpdateListTCMC();
	}
	UpdateData(FALSE);
}
