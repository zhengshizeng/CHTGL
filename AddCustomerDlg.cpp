// AddCustomerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "AddCustomerDlg.h"
#include "MyExcelz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAddCustomerDlg dialog


CAddCustomerDlg::CAddCustomerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCustomerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddCustomerDlg)
	m_KFName = _T("");
	m_ContactPerson = _T("");
	m_Telephone = _T("");
	m_uKFLX=0;
	//}}AFX_DATA_INIT
}


void CAddCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddCustomerDlg)
	DDX_Control(pDX, IDC_LIST_KFZL, m_List_Kfzl);
	DDX_Text(pDX, IDC_EDIT1, m_KFName);
	DDX_Text(pDX, IDC_EDIT2, m_ContactPerson);
	DDX_Text(pDX, IDC_EDIT5, m_Telephone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddCustomerDlg, CDialog)
	//{{AFX_MSG_MAP(CAddCustomerDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_KFZL, OnItemchangedListKfzl)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddCustomerDlg message handlers

BOOL CAddCustomerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List_Kfzl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_List_Kfzl.InsertColumn(0,_T("���"),LVCFMT_LEFT,60,-1);
	m_List_Kfzl.InsertColumn(1,_T("�� ��"),LVCFMT_LEFT,200,-1);
	m_List_Kfzl.InsertColumn(2,_T("��ϵ��"),LVCFMT_LEFT,100,-1);
	m_List_Kfzl.InsertColumn(3,_T("�绰"),LVCFMT_LEFT,100,-1);
	m_List_Kfzl.InsertColumn(4,_T("Ӧ��"),LVCFMT_LEFT,80,-1);
	m_List_Kfzl.InsertColumn(5,_T("Ӧ��"),LVCFMT_LEFT,80,-1);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddCustomerDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_KFName==_T(""))
	{
		MessageBox("���Ʋ���Ϊ��!");
	}

	CString temp,temp1;
	CString strKFlx;
	if (m_uKFLX==0)
	{
		strKFlx.Format("�ͻ�");
	}
	else
	{
		strKFlx.Format("��Ӧ��");
	}
	try
	{
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance("ADODB.Recordset");
		pRecordset->CursorLocation = adUseClient;
		CString strSQL;
		
		strSQL.Format("select * from customer where KFName = '%s' and kfType=%d ", m_KFName,m_uKFLX);
		pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
			adOpenDynamic, adLockOptimistic, adCmdText);
		if(pRecordset->RecordCount == 1)
		{
			temp1.Format("���ݿ����Ѵ���!�Ƿ�Ҫ����[%s]����Ϊ:[%s]",strKFlx,m_KFName);
			if(MessageBox(temp1,"�޸���ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				if (m_uKFLX==0)
				{
					pRecordset->PutCollect("kfType",_variant_t(long(0)));
				}
				else
				{
					pRecordset->PutCollect("kfType",_variant_t(long(1)));
				}
				pRecordset->PutCollect("KFName",(_variant_t)m_KFName);
				pRecordset->PutCollect("ContactPerson",(_variant_t)m_ContactPerson);
				pRecordset->PutCollect("Telephone",(_variant_t)m_Telephone);
				pRecordset->Update();
				MessageBox("�޸ĳɹ�!");
			}
		}
		else if(pRecordset->RecordCount == 0)
		{
			temp1.Format("�Ƿ�����%s:[%s]",strKFlx,m_KFName);
			if(MessageBox(temp1,"������ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->AddNew();
				if (m_uKFLX==0)
				{
					pRecordset->PutCollect("kfType",_variant_t(long(0)));
				}
				else
				{
					pRecordset->PutCollect("kfType",_variant_t(long(1)));
				}
				pRecordset->PutCollect("KFName",(_variant_t)m_KFName);
				pRecordset->PutCollect("ContactPerson",(_variant_t)m_ContactPerson);
				pRecordset->PutCollect("Telephone",(_variant_t)m_Telephone);
				pRecordset->Update();
				MessageBox("��ӳɹ�!");
			}
		}
		else
		{
			MessageBox("��ʾ,�����������ݿ��д��ڲ�ֹ1����¼!");
		}
		
		pRecordset->Close();
		pRecordset.Release();

		UpdateKFList();
		m_KFName = _T("");
		m_ContactPerson = _T("");
		m_Telephone = _T("");
		UpdateData(FALSE);
		

	}
	catch (_com_error e) 
	{
		temp1.Format("������ʾ,���%s����ʧ��!\n%s",strKFlx,e.Description());
		MessageBox(temp1);
	}
}



BOOL CAddCustomerDlg::UpdateKFList()
{	
	int k = 0;
	CString tempk;
	m_List_Kfzl.DeleteAllItems();//����б�
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("SELECT * FROM customer where kfType=%d",m_uKFLX);
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strTypeName,strConPerson,strTel;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("KFName");
				if (vat.vt != VT_NULL)
				{
					strTypeName = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("ContactPerson");
				if (vat.vt != VT_NULL)
				{
					strConPerson = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("Telephone");
				if (vat.vt != VT_NULL)
				{
					strTel = (LPCSTR)_bstr_t(vat);
				}
				tempk.Format("%d",k+1);
				m_List_Kfzl.InsertItem(k,tempk);
				m_List_Kfzl.SetItemText(k,1,strTypeName);
				m_List_Kfzl.SetItemText(k,2,strConPerson);
				m_List_Kfzl.SetItemText(k,3,strTel);
				k++;
				pSet->MoveNext();
			}
		}
		else
		{	
			TRACE("��ѯ����¼Ϊ��\n");
			return FALSE;
		}
	}
	catch (_com_error &comError)
	{
		tempk.Format("������ʾ,UpdateKFList�����б�ʧ��!%s",comError.Description());
		AfxMessageBox(tempk);
		return FALSE;
	}
	return TRUE;
}

void CAddCustomerDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strKFlx;
	if (m_uKFLX==0)
	{
		strKFlx.Format("�ͻ�");
	}
	else
	{
		strKFlx.Format("��Ӧ��");
	}
	
	if ( m_KFName == "")
	{
		MessageBox("����ѡ���±���Ҫɾ��������!");
	}
	else
	{
		CString temp;
		temp.Format("�Ƿ�Ҫɾ��%s:[%s]",strKFlx,m_KFName);
		if(MessageBox(temp,"ɾ����ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{		
			try
			{
				_RecordsetPtr pRecordset;
				CString strSQL;	
				pRecordset.CreateInstance("ADODB.Recordset");
				pRecordset->CursorLocation = adUseClient;		
				strSQL.Format("select * from customer where KFName = '%s' and kfType=%d ", m_KFName,m_uKFLX);
				pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
					adOpenDynamic, adLockOptimistic, adCmdText);
				
				if(pRecordset->RecordCount == 0)
				{
					temp.Format("ɾ��ʧ��!���ݿ����޸ü�¼![%s]",m_KFName);
					MessageBox(temp,"��ʾ",MB_OK);
					pRecordset->Close();
					pRecordset.Release();
				}
				else
				{
					pRecordset->Delete(adAffectCurrent);		
					pRecordset->UpdateBatch(adAffectAll);
					pRecordset->Close();
					pRecordset.Release();
					UpdateKFList();
				}
				m_KFName = _T("");
				m_ContactPerson = _T("");
				m_Telephone = _T("");
				UpdateData(FALSE);
				
			}
			catch (_com_error e) 
			{
				temp.Format("������ʾ,ɾ��ʧ��!%s",e.Description());
				AfxMessageBox(temp);
			}
		}
	}
}

void CAddCustomerDlg::OnItemchangedListKfzl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_KFName = m_List_Kfzl.GetItemText(pNMListView->iItem,1);
	m_ContactPerson = m_List_Kfzl.GetItemText(pNMListView->iItem,2);
	m_Telephone = m_List_Kfzl.GetItemText(pNMListView->iItem,3);
	UpdateData(FALSE);
	*pResult = 0;
}

void CAddCustomerDlg::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CString fileName;
	if (m_uKFLX==0)
	{
		fileName.Format("�ͻ���Ϣ��");
	}
	else
	{
		fileName.Format("��Ӧ����Ϣ��");
	}	
	
	CMyExcelz myexcelz;
	if (myexcelz.CreateEApplication("Sheet1")==TRUE)
	{
		myexcelz.SetItemTextz(1,1,fileName);
		myexcelz.DrawList(&m_List_Kfzl,3,1);
		myexcelz.SaveExcel(fileName);
	}
}

void CAddCustomerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,773,506,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

HBRUSH CAddCustomerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CAddCustomerDlg::SetuKFLX(UINT uKFLX)
{
	m_uKFLX=uKFLX;
	if (m_uKFLX==0)
	{
		GetDlgItem(IDC_STATIC_NAME)->SetWindowText("�ͻ�����:");
	}
	else
	{
		GetDlgItem(IDC_STATIC_NAME)->SetWindowText("��Ӧ������:");		
	}

	UpdateKFList();
}
