// AddHTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CHTGL.h"
#include "AddHTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAddHTDlg dialog


CAddHTDlg::CAddHTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddHTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddHTDlg)
	m_uTCBL = 2;
	m_Ehtjr = 0.0;
	m_Ejr = 0.0;
	m_TimeQWRQ = 0;
	m_TimeFKSJ = 0;
	m_EBz = _T("");
	m_Ehtbh = _T("");
	m_EXmms = _T("");
	m_Esyjr = 0.0;
	m_EMoneyDS = _T("");
	//}}AFX_DATA_INIT
}


void CAddHTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddHTDlg)
	DDX_Control(pDX, IDC_LIST_SFKTJ, m_ListCtrlSFKTJ);
	DDX_Control(pDX, IDC_COMBO_SFKMC, m_ComboSFKMC);
	DDX_Control(pDX, IDC_COMBO_QWR, m_Combo_QWR);
	DDX_Control(pDX, IDC_COMBO_KFMC, m_CbomboKFMC);
	DDX_Control(pDX, IDC_COMBO_KFLX, m_ComboKFLX);
	DDX_Text(pDX, IDC_EDIT_TCBL, m_uTCBL);
	DDX_Text(pDX, IDC_EDIT_HTJR, m_Ehtjr);
	DDX_Text(pDX, IDC_EDIT_JR, m_Ejr);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_TimeQWRQ);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_TimeFKSJ);
	DDX_Text(pDX, IDC_EDIT_BZ, m_EBz);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_Ehtbh);
	DDX_Text(pDX, IDC_EDIT_XMMS, m_EXmms);
	DDX_Text(pDX, IDC_EDIT_JR2, m_Esyjr);
	DDX_Text(pDX, IDC_EDIT_DSJR, m_EMoneyDS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddHTDlg, CDialog)
	//{{AFX_MSG_MAP(CAddHTDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_KFLX, OnSelchangeComboKflx)
	ON_BN_CLICKED(IDC_BTN_ADDTJ, OnBtnAddtj)
	ON_BN_CLICKED(IDC_BTN_DELTJ, OnBtnDeltj)
	ON_BN_CLICKED(IDC_BTN_ADDHT, OnBtnAddht)
	ON_BN_CLICKED(IDC_BTN_JRDS, OnBtnJrds)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddHTDlg message handlers

BOOL CAddHTDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ComboKFLX.InsertString(0,"客户");
	m_ComboKFLX.InsertString(1,"供应商");
	m_ComboKFLX.SetCurSel(0);

	m_ListCtrlSFKTJ.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListCtrlSFKTJ.InsertColumn(0,_T("编号"),LVCFMT_LEFT,60,-1);
	m_ListCtrlSFKTJ.InsertColumn(1,_T("名称"),LVCFMT_LEFT,220,-1);
	m_ListCtrlSFKTJ.InsertColumn(2,_T("日期"),LVCFMT_LEFT,120,-1);
	m_ListCtrlSFKTJ.InsertColumn(3,_T("金额"),LVCFMT_LEFT,100,-1);
	m_ListCtrlSFKTJ.InsertColumn(4,_T("备注"),LVCFMT_LEFT,160,-1);
	m_ListCtrlSFKTJ.InsertColumn(5,_T("ID"),LVCFMT_LEFT,-20,-1);	
	OnQRWCombox();
	SFKMCCombox();
	OnSelchangeComboKflx();
	OnNewAddHT();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddHTDlg::OnSelchangeComboKflx() 
{
	// TODO: Add your control notification handler code here
	int k=0;
	CString sqlTemp;
	int ikfType=0;
	ikfType=m_ComboKFLX.GetCurSel();
	if (ikfType==0)
	{
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("收款条件");
		GetDlgItem(IDC_STATIC_N2)->SetWindowText("收款名称:");
		GetDlgItem(IDC_STATIC_N3)->SetWindowText("收款时间:");
		GetDlgItem(IDC_STATIC_N4)->SetWindowText("收款金额:");
	}
	else
	{
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("付款条件");
		GetDlgItem(IDC_STATIC_N2)->SetWindowText("付款名称:");
		GetDlgItem(IDC_STATIC_N3)->SetWindowText("付款时间:");
		GetDlgItem(IDC_STATIC_N4)->SetWindowText("付款金额:");
	}
	m_CbomboKFMC.ResetContent();
	try
	{
		sqlTemp.Format("Select KFName,KFID from customer where kfType=%d ",ikfType);
		VARIANT cnt;
		cnt.vt = VT_INT;
		_RecordsetPtr pSet =theApp.m_pConn->Execute((_bstr_t)sqlTemp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL)
		{
			while (!pSet->adoEOF)
			{
				vat =pSet->GetCollect("KFName");
				if (vat.vt != VT_NULL)
				{
					m_CbomboKFMC.InsertString(k,(LPCSTR)_bstr_t(vat));
					
				}
				vat =pSet->GetCollect("KFID");
				if (vat.vt != VT_NULL)
				{
					m_ArrayKFID.Add((LPCSTR)_bstr_t(vat));
				}
				k++;
				pSet->MoveNext();				
			}
			pSet->Close();
			pSet.Release();
			m_CbomboKFMC.SetCurSel(0);
		}
	}
	catch (_com_error &comError)
	{
		sqlTemp.Format("OnSelchangeComboKflx Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(sqlTemp);
	}	
}

void CAddHTDlg::OnQRWCombox()
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

void CAddHTDlg::OnBtnAddtj() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (false==GetEsyjr())
	{
		return ;
	}
	CString tempName;
	m_ComboSFKMC.GetLBText(m_ComboSFKMC.GetCurSel(),tempName);
	TRACE("%s\n",tempName);
	
// 	temp.Format("%s",m_TimeFKSJ.Format("%Y-%m-%d"));
// 	TRACE("%s\n",temp);
	CString temp;
	int ICount=m_ListCtrlSFKTJ.GetItemCount();

	temp.Format("%d",ICount+1);
	m_ListCtrlSFKTJ.InsertItem(ICount,temp);
	m_ListCtrlSFKTJ.SetItemText(ICount,1,tempName);
	m_ListCtrlSFKTJ.SetItemText(ICount,2,m_TimeFKSJ.Format("%Y-%m-%d"));
	temp.Format("%.2f",m_Ejr);
	m_ListCtrlSFKTJ.SetItemText(ICount,3,temp);
	m_ListCtrlSFKTJ.SetItemText(ICount,4,m_EBz);
	m_ListCtrlSFKTJ.SetItemText(ICount,5,m_ArraySFKTJID.GetAt(m_ComboSFKMC.GetCurSel()));


	
	m_Ejr=0;
	m_EBz=_T("");
	
	UpdateData(FALSE);

}

void CAddHTDlg::OnBtnDeltj() 
{
	// TODO: Add your control notification handler code here
	
	POSITION pos = m_ListCtrlSFKTJ.GetFirstSelectedItemPosition();  
	if (pos == NULL)  
		TRACE0("No items were selected!\n");  
	else  
	{  
		while (pos)  
		{  
			int nItem = m_ListCtrlSFKTJ.GetNextSelectedItem(pos);  
			TRACE1("Item %d was selected!\n", nItem);  
			// you could do your own processing on nItem here  
			m_ListCtrlSFKTJ.DeleteItem(nItem);
		}  
	}  
	m_Ejr=0.0;
	GetEsyjr();
	UpdateData(FALSE);
}


void CAddHTDlg::SFKMCCombox()
{
	int k=0;
	CString sqlTemp;
	
	m_ComboSFKMC.ResetContent();
	try
	{
		sqlTemp.Format("Select * from TypeofCollection " );
		VARIANT cnt;
		cnt.vt = VT_INT;
		_RecordsetPtr pSet =theApp.m_pConn->Execute((_bstr_t)sqlTemp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL)
		{
			while (!pSet->adoEOF)
			{
				vat =pSet->GetCollect("TypeName");
				if (vat.vt != VT_NULL)
				{
					m_ComboSFKMC.InsertString(k,(LPCSTR)_bstr_t(vat));
					
				}
				vat =pSet->GetCollect("TypeCID");
				if (vat.vt != VT_NULL)
				{
					m_ArraySFKTJID.Add((LPCSTR)_bstr_t(vat));
				}
				k++;
				pSet->MoveNext();				
			}
			pSet->Close();
			pSet.Release();
			m_ComboSFKMC.SetCurSel(0);
		}
	}
	catch (_com_error &comError)
	{
		sqlTemp.Format("OnSelchangeComboKflx Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(sqlTemp);
	}	
}

void CAddHTDlg::OnBtnAddht() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Ehtbh==_T(""))
	{
		MessageBox("合同编号不能为空!");
	}
	else
	{
		if (m_Esyjr>0)
		{
			CString temp;
			temp.Format("还有剩余金额未添加到明细![%.2f] 是否续继续增加!",m_Esyjr);
			if(MessageBox(temp,"修改提示" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
			{			
				return ;
			}
		}
		AddHT();
		OnNewAddHT();
	}
}


void CAddHTDlg::AddHT()
{
	CString temp,temp1;
	try
	{
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance("ADODB.Recordset");
		pRecordset->CursorLocation = adUseClient;
		CString strSQL;
		
		strSQL.Format("select * from ContractHT where HTBH = '%s'", m_Ehtbh);
		pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
			adOpenDynamic, adLockOptimistic, adCmdText);
		if(pRecordset->RecordCount == 1)
		{
			temp1.Format("数据库中已存在这个合同编号[%s]!是否要修改合同!",m_Ehtbh);
			if(MessageBox(temp1,"修改提示" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->PutCollect("HTBH",(_variant_t)m_Ehtbh);//合同编号
				pRecordset->PutCollect("KFLX",(_variant_t)(long)m_ComboKFLX.GetCurSel());//客户类型
				pRecordset->PutCollect("QYRID",(_variant_t)m_ArrayQYRID.GetAt(m_Combo_QWR.GetCurSel()));//签约人ID				
				pRecordset->PutCollect("CDate",(_variant_t)m_TimeQWRQ.Format("%Y-%m-%d"));//合同日期
				pRecordset->PutCollect("KFID",(_variant_t)m_ArrayKFID.GetAt(m_CbomboKFMC.GetCurSel()));//客户ID
				pRecordset->PutCollect("HTMoney",(_variant_t)m_Ehtjr);//合同金额
				pRecordset->PutCollect("XMMiaoShu",(_variant_t)m_EXmms);//项目描述
				pRecordset->Update();
			}
		}
		else if(pRecordset->RecordCount == 0)
		{
			temp1.Format("是否新增合同编号[%s]",m_Ehtbh);
			if(MessageBox(temp1,"新增提示" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->AddNew();
				pRecordset->PutCollect("HTBH",(_variant_t)m_Ehtbh);//合同编号
				pRecordset->PutCollect("KFLX",(_variant_t)(long)m_ComboKFLX.GetCurSel());//客户类型
				pRecordset->PutCollect("QYRID",(_variant_t)m_ArrayQYRID.GetAt(m_Combo_QWR.GetCurSel()));//签约人ID				
				pRecordset->PutCollect("CDate",(_variant_t)m_TimeQWRQ.Format("%Y-%m-%d"));//合同日期
				pRecordset->PutCollect("KFID",(_variant_t)m_ArrayKFID.GetAt(m_CbomboKFMC.GetCurSel()));//客户ID
				pRecordset->PutCollect("HTMoney",(_variant_t)m_Ehtjr);//合同金额
				pRecordset->PutCollect("XMMiaoShu",(_variant_t)m_EXmms);//项目描述
				pRecordset->Update();
			}
		}
		else
		{
			MessageBox("提示,此编号在数据库中存在不止1条记录!");
		}
		
		pRecordset->Close();
		pRecordset.Release();
		//增加条件
		if (AddHTTJ()==TRUE)
		{
			MessageBox("添加成功!");
		}
		
	}
	catch (_com_error e) 
	{
		temp1.Format("错误提示,添加收款类型失败!\n%s",e.Description());
		MessageBox(temp1);
	}	
}

BOOL CAddHTDlg::AddHTTJ()
{
	int k=0;
	k=m_ListCtrlSFKTJ.GetItemCount();
	CString strTJNmae,strData,strJR,strBZ,sqlTemp;
	int i=0;
	while(i<k)
	{
		strTJNmae = m_ListCtrlSFKTJ.GetItemText(i,5);
		strData = m_ListCtrlSFKTJ.GetItemText(i,2);
		strJR = m_ListCtrlSFKTJ.GetItemText(i,3);
		strBZ = m_ListCtrlSFKTJ.GetItemText(i,4);
		TRACE("%d=%d,%s,%s,%s,%s \n",i,k,strTJNmae,strData,strJR,strBZ);
		i++;
		try
		{
			sqlTemp.Format("Insert into Receivables(TypeCID,ExpectMoney,ExpectData,CustomerID,QWRID,KFLX) \
				Values('%s','%s','%s','%s','%s','%d')",strTJNmae,strJR,strData,m_Ehtbh,m_ArrayQYRID.GetAt(m_Combo_QWR.GetCurSel()),m_ComboKFLX.GetCurSel());

			TRACE("\n%s\n",sqlTemp);
			VARIANT cnt;
			cnt.vt = VT_INT;
			theApp.m_pConn->Execute((_bstr_t)sqlTemp,&cnt,adCmdUnknown);
		}
		catch (_com_error &comError)
		{
			sqlTemp.Format("AddHTTJ Error ! %s,%s",comError.Description(),comError.ErrorMessage());
			AfxMessageBox(sqlTemp);
		}	
		
	}
	return TRUE;
}

void CAddHTDlg::OnBtnJrds() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_EMoneyDS=theApp.MoneytoDS(m_Ehtjr);
	m_Esyjr=m_Ehtjr;
	UpdateData(FALSE);
}

bool CAddHTDlg::GetEsyjr()
{
	int icount=m_ListCtrlSFKTJ.GetItemCount();
	double tempJR=0.0;
	for (int i=0;i<icount;i++)
	{
		tempJR+=atof(m_ListCtrlSFKTJ.GetItemText(i,3));
	}
	m_Esyjr=m_Ehtjr-tempJR;
	tempJR=m_Esyjr-m_Ejr;
	CString temp;
	if (tempJR<0)
	{
		temp.Format("剩余金额不足!%.2f - %.2f = %.2f",m_Esyjr,m_Ejr,tempJR);
		AfxMessageBox(temp);
		m_Ejr=m_Esyjr;
		UpdateData(FALSE);
		return false;
	}
	m_Esyjr=tempJR;
	return true;
}

void CAddHTDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,773,506,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

HBRUSH CAddHTDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CAddHTDlg::OnNewAddHT()
{
	m_Ehtjr=0.0f;
	m_Esyjr=0.0f;
	m_EXmms=_T("");
	m_ListCtrlSFKTJ.DeleteAllItems();

	m_TimeFKSJ=CTime::GetCurrentTime();
	m_TimeQWRQ=CTime::GetCurrentTime();
	
	m_Ehtbh.Format("HT_%s",m_TimeFKSJ.Format("%Y%m%d%H%M%S"));
	UpdateData(FALSE);
}
