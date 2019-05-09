// Kpgl_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "Kpgl_Dlg.h"
#include "MyExcelz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CKpgl_Dlg dialog


CKpgl_Dlg::CKpgl_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKpgl_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKpgl_Dlg)
	m_EFPHM = _T("");
	m_EKPMoney = 0.0f;
	m_TimeKP = 0;
	m_E1Money = 0.0f;
	m_E2Money = 0.0f;
	m_E3Money = 0.0f;
	//}}AFX_DATA_INIT
}


void CKpgl_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKpgl_Dlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComboFPLX);
	DDX_Control(pDX, IDC_LIST_KPMX, m_List_KPMX);
	DDX_Text(pDX, IDC_EDIT_FPHM, m_EFPHM);
	DDX_Text(pDX, IDC_EDIT_KPMONEY, m_EKPMoney);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_TimeKP);
	DDX_Text(pDX, IDC_EDIT_YIKPMONEY, m_E1Money);
	DDX_Text(pDX, IDC_EDIT_YKPMONEY, m_E2Money);
	DDX_Text(pDX, IDC_EDIT_WKPMONEY, m_E3Money);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKpgl_Dlg, CDialog)
	//{{AFX_MSG_MAP(CKpgl_Dlg)
	ON_BN_CLICKED(IDC_BTN_ADDKP, OnBtnAddkp)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_KPMX, OnItemchangedListKpmx)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKpgl_Dlg message handlers
void CKpgl_Dlg::SetHTBH(CString htbh)
{
	m_strHTBH.Format("%s",htbh);
}


BOOL CKpgl_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List_KPMX.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_List_KPMX.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_List_KPMX.InsertColumn(1,_T("票号"),LVCFMT_LEFT,180,-1);
	m_List_KPMX.InsertColumn(2,_T("开票时间"),LVCFMT_LEFT,120,-1);
	m_List_KPMX.InsertColumn(3,_T("开票金额"),LVCFMT_LEFT,100,-1);
	m_List_KPMX.InsertColumn(4,_T("发票类型"),LVCFMT_LEFT,100,-1);

	m_ComboFPLX.InsertString(0,"普通发票");
	m_ComboFPLX.InsertString(1,"增值税发票");
	m_ComboFPLX.SetCurSel(0);

	m_TimeKP=CTime::GetCurrentTime();

	//m_strHTBH.Format("HT_20180402132531");
	if (!m_strHTBH.IsEmpty())
	{
		UpdateKPList();
	}
	GetHTMoneyByHTBH();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKpgl_Dlg::OnBtnAddkp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strKPType;
	if (m_EFPHM.IsEmpty())
	{
		AfxMessageBox("发票号码不能为空!");
		return ;
	}
	if (m_EKPMoney > m_E3Money)
	{
		strKPType.Format("开票金额不能大于未开票金额!\n[%.2f元]  >  [%.2f元]",m_EKPMoney,m_E3Money);
		m_EKPMoney=m_E3Money;
		UpdateData(FALSE);
		AfxMessageBox(strKPType);
		return ;
	}
	
	m_ComboFPLX.GetLBText(m_ComboFPLX.GetCurSel(),strKPType);
	CString tempSQL;
	tempSQL.Format("INSERT INTO KaiPiaoManager (CustomerID,PiaoHao,KPiaoTime,KPiaoMoney,KPiaoType) values('%s','%s','%s','%f','%s') ",\
		m_strHTBH,m_EFPHM,m_TimeKP.Format("%Y-%m-%d"),m_EKPMoney,strKPType);

	//AfxMessageBox(tempSQL);
	if (theApp.ExecuteSql(tempSQL)==TRUE)
	{
		UpdateKPList();
		m_E3Money=m_E1Money-m_E2Money;
		UpdateData(FALSE);

	}
}


BOOL CKpgl_Dlg::UpdateKPList()
{	
	int k = 0;
	CString tempk;
	m_List_KPMX.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select * from KaiPiaoManager WHERE CustomerID='%s' ",m_strHTBH);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strPh,strKPTime,strKPMoney,strKPType;
		float tempMoney;
		tempMoney=0.0f;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				strPh=_T("");
				strKPTime=_T("");
				strKPMoney=_T("");
				strKPType=_T("");
				vat =pSet->GetCollect("PiaoHao");
				if (vat.vt != VT_NULL)
				{
					strPh = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("KPiaoTime");
				if (vat.vt != VT_NULL)
				{
					strKPTime = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("KPiaoMoney");
				if (vat.vt != VT_NULL)
				{
					strKPMoney = (LPCSTR)_bstr_t(vat);
					tempMoney+=(float)atof(strKPMoney);
				}
				vat =pSet->GetCollect("KPiaoType");
				if (vat.vt != VT_NULL)
				{
					strKPType = (LPCSTR)_bstr_t(vat);
				}
				tempk.Format("%d",k+1);
				m_List_KPMX.InsertItem(k,tempk);
				m_List_KPMX.SetItemText(k,1,strPh);
				m_List_KPMX.SetItemText(k,2,strKPTime);
				m_List_KPMX.SetItemText(k,3,strKPMoney);				
				m_List_KPMX.SetItemText(k,4,strKPType);
				k++;
				pSet->MoveNext();
			}
			m_E2Money=tempMoney;
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

void CKpgl_Dlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	if ( m_EFPHM == "")
	{
		MessageBox("请先选择下表中要删除的数据!");
	}
	else
	{
		CString temp;
		temp.Format("是否要删除发票号码为[%s]的开票记录?",m_EFPHM);
		if(MessageBox(temp,"删除提示" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{		
			try
			{
				_RecordsetPtr pRecordset;
				CString strSQL;	
				pRecordset.CreateInstance("ADODB.Recordset");
				pRecordset->CursorLocation = adUseClient;		
				strSQL.Format("Select * from KaiPiaoManager WHERE PiaoHao='%s' ", m_EFPHM);
				pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
					adOpenDynamic, adLockOptimistic, adCmdText);
				
				if(pRecordset->RecordCount == 0)
				{
					temp.Format("删除失败!数据库中无该记录![%s]",m_EFPHM);
					MessageBox(temp,"提示",MB_OK);
					pRecordset->Close();
					pRecordset.Release();
				}
				else
				{
					pRecordset->Delete(adAffectCurrent);		
					pRecordset->UpdateBatch(adAffectAll);
					pRecordset->Close();
					pRecordset.Release();
					UpdateKPList();
				}
				m_E3Money=m_E1Money-m_E2Money;
				m_EFPHM = _T("");
				m_EKPMoney=0.0f;
				UpdateData(FALSE);
				
			}
			catch (_com_error e) 
			{
				temp.Format("错误提示,删除失败!%s",e.Description());
				AfxMessageBox(temp);
			}
		}
	}
}

void CKpgl_Dlg::OnItemchangedListKpmx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_EFPHM = m_List_KPMX.GetItemText(pNMListView->iItem,1);
	UpdateData(FALSE);
	*pResult = 0;
}

void CKpgl_Dlg::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CString fileName,temp;
	fileName.Format("合同%s开票明细",m_strHTBH);
	CMyExcelz myexcelz;
	if (myexcelz.CreateEApplication("开票明细表")==TRUE)
	{
		myexcelz.SetItemTextz(1,1,fileName);
		
		myexcelz.SetItemTextz(2,1,"应开票金额:");
		temp.Format("%.2f",m_E1Money);
		myexcelz.SetItemTextz(2,2,temp);
		
		myexcelz.SetItemTextz(3,1,"已开票金额:");
		temp.Format("%.2f",m_E2Money);
		myexcelz.SetItemTextz(3,2,temp);

		myexcelz.SetItemTextz(4,1,"应开票金额:");
		temp.Format("%.2f",m_E3Money);
		myexcelz.SetItemTextz(4,2,temp);
		
		myexcelz.DrawList(&m_List_KPMX,7,1);
		
		myexcelz.SaveExcel(fileName);
	}
}

BOOL CKpgl_Dlg::GetHTMoneyByHTBH()
{
	CString temp;
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		
		temp.Format("Select HTMoney from ContractHT WHERE HTBH='%s'",m_strHTBH);

		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strHtMoney;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("HTMoney");
				if (vat.vt != VT_NULL)
				{
					strHtMoney = (LPCSTR)_bstr_t(vat);
					m_E1Money=(float)atof(strHtMoney);
					m_E3Money=m_E1Money-m_E2Money;
				}
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
		temp.Format("错误提示,查询合同金额出错!%s",comError.Description());
		AfxMessageBox(temp);
		return FALSE;
	}
	return TRUE;
}
