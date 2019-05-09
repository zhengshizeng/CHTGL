// SHTListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "SHTListDlg.h"
#include "SelectHTDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CSHTListDlg dialog


CSHTListDlg::CSHTListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSHTListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSHTListDlg)
	m_TimeS = 0;
	m_TimeE = 0;
	m_EHtbh = _T("");
	//}}AFX_DATA_INIT
}


void CSHTListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSHTListDlg)
	DDX_Control(pDX, IDC_COMBO_GONGYI, m_Combo_GongYi);
	DDX_Control(pDX, IDC_COMBO_KEFU, m_Combo_KeFu);
	DDX_Control(pDX, IDC_COMBO_QWR, m_Combo_QWR);
	DDX_Control(pDX, IDC_LIST_HTL, m_ListHTl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_TimeS);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_TimeE);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_EHtbh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSHTListDlg, CDialog)
	//{{AFX_MSG_MAP(CSHTListDlg)
	ON_BN_CLICKED(IDC_BTN_SELECT, OnBtnSelect)
	ON_BN_CLICKED(IDC_CHECK_GongYi, OnCHECKGongYi)
	ON_BN_CLICKED(IDC_CHECK_KeFu, OnCHECKKeFu)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBtnNext)
	ON_BN_CLICKED(IDC_BTN_CKXQ, OnBtnCkxq)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_HTL, OnItemchangedListHtl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSHTListDlg message handlers

BOOL CSHTListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListHTl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListHTl.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_ListHTl.InsertColumn(1,_T("合同编号"),LVCFMT_LEFT,180,-1);
	m_ListHTl.InsertColumn(2,_T("客户名称"),LVCFMT_LEFT,200,-1);
	m_ListHTl.InsertColumn(3,_T("签约人"),LVCFMT_LEFT,80,-1);
	m_ListHTl.InsertColumn(4,_T("签约日期"),LVCFMT_LEFT,100,-1);
	m_ListHTl.InsertColumn(5,_T("合同金额"),LVCFMT_LEFT,80,-1);
	m_ListHTl.InsertColumn(6,_T("项目描述"),LVCFMT_LEFT,180,-1);

	m_TimeS=CTime::GetCurrentTime();
	m_TimeE=m_TimeS;
	OnQRWCombox();
	SelecCustomer(1);
	SelecCustomer(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSHTListDlg::OnBtnSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sqlTemp,temp;
	sqlTemp.Format("Select co.HTBH,cu.KFName,q.QName,CDate,HTMoney,XMMiaoShu from ContractHT co,customer cu,QWR q WHERE co.KFID=cu.KFID and q.QID=co.QYRID");
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_QYR))->GetCheck())
	{
		//AfxMessageBox("QYR");
		temp.Format(" and co.QYRID=%s ",m_ArrayQYRID.GetAt(m_Combo_QWR.GetCurSel()));
		sqlTemp+=temp;
		TRACE("%s\n",sqlTemp);
	}
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_QYDATA))->GetCheck())
	{
		temp.Format(" and CDate between #%s# and #%s# ",m_TimeS.Format("%Y-%m-%d"),m_TimeE.Format("%Y-%m-%d"));
		sqlTemp+=temp;
		//AfxMessageBox(temp);
	}
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_KeFu))->GetCheck())
	{
		//AfxMessageBox("按客户查询没完成");		
		temp.Format(" and co.KFID=%s",strKFArr.GetAt(m_Combo_KeFu.GetCurSel()));
		sqlTemp+=temp;
		TRACE("%s\n",sqlTemp);
	}
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_GongYi))->GetCheck())
	{
		//AfxMessageBox("按供应查询没完成");
		temp.Format(" and co.KFID=%s",strGYArr.GetAt(m_Combo_GongYi.GetCurSel()));
		sqlTemp+=temp;
		TRACE("%s\n",sqlTemp);
	}
	UpdateList(sqlTemp);
	if (m_ListHTl.GetItemCount()==0)
	{
		AfxMessageBox("查询完成!没有符合条件的数据!");
	}
//	AfxMessageBox("查询完成!");
}

void CSHTListDlg::OnCHECKGongYi() 
{
	// TODO: Add your control notification handler code here
	( (CButton*)GetDlgItem(IDC_CHECK_KeFu))->SetCheck(FALSE);
}

void CSHTListDlg::OnCHECKKeFu() 
{
	// TODO: Add your control notification handler code here
	( (CButton*)GetDlgItem(IDC_CHECK_GongYi))->SetCheck(FALSE);
}


void CSHTListDlg::OnQRWCombox()
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

BOOL CSHTListDlg::SelecCustomer(int ikflx)
{
	int k=0;
	CString sqlTemp,tempname,strKFID; 
	try
	{
		sqlTemp.Format("Select KFName,KFID from customer where kfType=%d ",ikflx);
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
					tempname=(LPCSTR)_bstr_t(vat);					
				}
				vat =pSet->GetCollect("KFID");
				if (vat.vt != VT_NULL)
				{
					strKFID=(LPCSTR)_bstr_t(vat);
				}

				
				if (ikflx==0)
				{					
					m_Combo_KeFu.InsertString(k,tempname);
					strKFArr.Add(strKFID);
				}
				else
				{
					m_Combo_GongYi.InsertString(k,tempname);
					strGYArr.Add(strKFID);
				}
				k++;
				pSet->MoveNext();				
			}
			pSet->Close();
			pSet.Release();
			if (ikflx==0)
			{
				m_Combo_KeFu.SetCurSel(0);
			}
			else
			{
				m_Combo_GongYi.SetCurSel(0);
			}
			
		}
	}
	catch (_com_error &comError)
	{
		sqlTemp.Format("OnSelchangeComboKflx Error ! %s,%s",comError.Description(),comError.ErrorMessage());
		AfxMessageBox(sqlTemp);
		return FALSE;
	}	
	return TRUE;
}


BOOL CSHTListDlg::UpdateList(CString sqlTemp)
{	
	int k = 0;
	CString tempk;
	m_ListHTl.DeleteAllItems();//清空列表
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)sqlTemp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				tempk.Format("%d",k+1);
				m_ListHTl.InsertItem(k,tempk);
				vat =pSet->GetCollect("HTBH");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,1,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("KFName");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,2,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("QName");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,3,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("CDate");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,4,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("HTMoney");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,5,(LPCSTR)_bstr_t(vat));
				}
				vat =pSet->GetCollect("XMMiaoShu");
				if (vat.vt != VT_NULL)
				{
					m_ListHTl.SetItemText(k,6,(LPCSTR)_bstr_t(vat));
				}
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

void CSHTListDlg::OnBtnNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EHtbh.IsEmpty())
	{
		AfxMessageBox("合同编号为空不能下一步!");
	}
	else
	{
		m_ListHTl.DeleteAllItems();		
		::PostMessage(GetParent()->GetParent()->m_hWnd,WM_CLIENT_MSG,1,LPARAM(new CString(m_EHtbh)));
		m_EHtbh=_T("");
		UpdateData(FALSE);
	}
	
	
}

void CSHTListDlg::OnBtnCkxq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EHtbh.IsEmpty())
	{
		AfxMessageBox("合同编号为空,请先查询!");
	}
	else
	{		
		CSelectHTDLG selectHTdlg;
		selectHTdlg.SetHTBH(m_EHtbh);
		selectHTdlg.DoModal();
	}
}

void CSHTListDlg::OnItemchangedListHtl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_EHtbh = m_ListHTl.GetItemText(pNMListView->iItem,1);
	UpdateData(FALSE);
	*pResult = 0;
}
