// SelectHTDLG.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "SelectHTDLG.h"
#include "MyExcelz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CSelectHTDLG dialog


CSelectHTDLG::CSelectHTDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectHTDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectHTDLG)
	m_EKFLX = _T("");
	m_EKFMC = _T("");
	m_EQYR = _T("");
	m_ETCBL = _T("");
	m_EJR = _T("");
	m_EHTJR = _T("");
	m_EHTBH = _T("");
	m_EBZ = _T("");
	m_EXMMS = _T("");
	m_DateTime = COleDateTime::GetCurrentTime();
	m_Ekp1 = 0.0f;
	m_Ekp2 = 0.0f;
	m_Ekp3 = 0.0f;
	//}}AFX_DATA_INIT
}


void CSelectHTDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectHTDLG)
	DDX_Control(pDX, IDC_LIST_KPMX, m_List_KPMX);
	DDX_Control(pDX, IDC_LIST_SFKTJ, m_ListSFKTJ);
	DDX_Text(pDX, IDC_EDIT_KFLX, m_EKFLX);
	DDX_Text(pDX, IDC_EDIT_KFMC, m_EKFMC);
	DDX_Text(pDX, IDC_EDIT_QYR, m_EQYR);
	DDX_Text(pDX, IDC_EDIT_TCBL, m_ETCBL);
	DDX_Text(pDX, IDC_EDIT_HTJR, m_EHTJR);
	DDX_Text(pDX, IDC_EDIT_HTBH, m_EHTBH);
	DDX_Text(pDX, IDC_EDIT_XMMS, m_EXMMS);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_DateTime);
	DDX_Text(pDX, IDC_EDIT_KP1, m_Ekp1);
	DDX_Text(pDX, IDC_EDIT_KP2, m_Ekp2);
	DDX_Text(pDX, IDC_EDIT_KP3, m_Ekp3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectHTDLG, CDialog)
	//{{AFX_MSG_MAP(CSelectHTDLG)
	ON_BN_CLICKED(IDC_BTN_EXPORTXLS, OnBtnExportxls)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectHTDLG message handlers

void CSelectHTDLG::SetHTBH(CString htbh)
{
	m_EHTBH.Format("%s",htbh);
}

BOOL CSelectHTDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ikflx=0;
	if (m_EHTBH!=_T(""))
	{
		SelectFromDB();
	}
	if (m_ikflx==0)
	{
		m_ListSFKTJ.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
		m_ListSFKTJ.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
		m_ListSFKTJ.InsertColumn(1,_T("收款条件"),LVCFMT_LEFT,180,-1);
		m_ListSFKTJ.InsertColumn(2,_T("预收时间"),LVCFMT_LEFT,100,-1);
		m_ListSFKTJ.InsertColumn(3,_T("预收金额"),LVCFMT_LEFT,80,-1);
		m_ListSFKTJ.InsertColumn(4,_T("实收时间"),LVCFMT_LEFT,100,-1);
		m_ListSFKTJ.InsertColumn(5,_T("实收金额"),LVCFMT_LEFT,80,-1);
		m_ListSFKTJ.InsertColumn(6,_T("银行"),LVCFMT_LEFT,150,-1);
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("收款条件明细表");
	}
	else
	{
		m_ListSFKTJ.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
		m_ListSFKTJ.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
		m_ListSFKTJ.InsertColumn(1,_T("付款条件"),LVCFMT_LEFT,180,-1);
		m_ListSFKTJ.InsertColumn(2,_T("预付时间"),LVCFMT_LEFT,100,-1);
		m_ListSFKTJ.InsertColumn(3,_T("预付金额"),LVCFMT_LEFT,80,-1);
		m_ListSFKTJ.InsertColumn(4,_T("实付时间"),LVCFMT_LEFT,100,-1);
		m_ListSFKTJ.InsertColumn(5,_T("实付金额"),LVCFMT_LEFT,80,-1);
		m_ListSFKTJ.InsertColumn(6,_T("银行"),LVCFMT_LEFT,150,-1);
		GetDlgItem(IDC_STATIC_N1)->SetWindowText("付款条件明细表");
	}
	
	m_List_KPMX.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_List_KPMX.InsertColumn(0,_T("N"),LVCFMT_LEFT,40,-1);
	m_List_KPMX.InsertColumn(1,_T("票号"),LVCFMT_LEFT,180,-1);
	m_List_KPMX.InsertColumn(2,_T("开票时间"),LVCFMT_LEFT,120,-1);
	m_List_KPMX.InsertColumn(3,_T("开票金额"),LVCFMT_LEFT,100,-1);

	UpdateSFKTJList();
	UpdateKPList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectHTDLG::UpdateKPList()
{	
	int k = 0;
	CString tempk;
	m_List_KPMX.DeleteAllItems();
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select * from KaiPiaoManager WHERE CustomerID='%s' ",m_EHTBH);
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
			m_Ekp2=tempMoney;
			m_Ekp3=m_Ekp1-m_Ekp2;
			UpdateData(FALSE);
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

void CSelectHTDLG::SelectFromDB()
{
	CString tempk;
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select C.*,Q.QName,cu.KFName from ContractHT C,QWR Q,customer cu WHERE QYRID=QID and cu.KFID=C.KFID and HTBH ='%s' ",m_EHTBH);
		TRACE("%s\n",temp);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		if(pSet != NULL && !pSet->adoEOF)
		{			
			vat =pSet->GetCollect("QName");
			if (vat.vt != VT_NULL)
			{
				m_EQYR = (LPCSTR)_bstr_t(vat);
			}
			vat =pSet->GetCollect("KFName");
			if (vat.vt != VT_NULL)
			{
				m_EKFMC = (LPCSTR)_bstr_t(vat);
			}
			vat =pSet->GetCollect("KFLX");
			if (vat.vt != VT_NULL)
			{
				CString templx;
				templx = (LPCSTR)_bstr_t(vat);
				if (templx==_T("0"))
				{
					m_EKFLX.Format("客户");
					m_ikflx=0;
				}
				else
				{
					m_EKFLX.Format("供应商");
					m_ikflx=1;
				}
			}
			vat =pSet->GetCollect("HTMoney");
			if (vat.vt != VT_NULL)
			{
				m_EHTJR = (LPCSTR)_bstr_t(vat);
				m_Ekp1=atof(m_EHTJR);

			}
			vat =pSet->GetCollect("XMMiaoShu");
			if (vat.vt != VT_NULL)
			{
				m_EXMMS = (LPCSTR)_bstr_t(vat);
			}
			vat =pSet->GetCollect("CDate");
			if (vat.vt != VT_NULL)
			{
				m_DateTime=vat.date;
				//m_EXMMS = (LPCSTR)_bstr_t(vat);
			}

		}
		UpdateData(FALSE);
		pSet->Close();
		pSet.Release();
	}
	catch (_com_error &comError)
	{
		tempk.Format("错误提示,查询数据失败!%s",comError.Description());
		AfxMessageBox(tempk);
	}	
}


BOOL CSelectHTDLG::UpdateSFKTJList()
{	
	int k = 0;
	CString tempk;

	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("Select TypeName,ExpectMoney,ExpectData,SJMoney,SJDate from Receivables R, TypeofCollection T where T.TypeCID=R.TypeCID and CustomerID='%s' ",m_EHTBH);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strTypeName,strExMoney,strExData,strSMoney,strSDate;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				strTypeName=_T("");
				strExMoney=_T("");
				strExData=_T("");
				strSMoney=_T("");
				strSDate=_T("");
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
				tempk.Format("%d",k+1);
				m_ListSFKTJ.InsertItem(k,tempk);
				m_ListSFKTJ.SetItemText(k,1,strTypeName);
				m_ListSFKTJ.SetItemText(k,2,strExData);
				m_ListSFKTJ.SetItemText(k,3,strExMoney);				
				m_ListSFKTJ.SetItemText(k,4,strSDate);
				m_ListSFKTJ.SetItemText(k,5,strSMoney);
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

void CSelectHTDLG::OnBtnExportxls() 
{
	// TODO: Add your control notification handler code here
	CString fileName;
	fileName.Format("合同%s",m_EHTBH);
	CMyExcelz myexcelz;
	if (myexcelz.CreateEApplication("合同明细表")==TRUE)
	{
		myexcelz.SetItemTextz(2,2,m_EHTBH);
		myexcelz.SetItemTextz(2,4,m_EHTJR);
		myexcelz.SetItemTextz(3,2,m_EKFMC);
		myexcelz.SetItemTextz(4,2,m_EQYR);
		myexcelz.SetItemTextz(4,4,m_DateTime.Format("%Y-%m-%d"));
		myexcelz.SetItemTextz(5,2,m_ETCBL);
		myexcelz.SetItemTextz(6,2,m_EXMMS);

		myexcelz.DrawList(&m_ListSFKTJ,9,1);

		int tempi;
		tempi=11+m_ListSFKTJ.GetItemCount();

		myexcelz.SetItemTextz(tempi,1,"开票明细");
		myexcelz.DrawList(&m_List_KPMX,tempi+2,1);
		myexcelz.SaveExcel(fileName);
	}
}
