// AddQWRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chtgl.h"
#include "AddQWRDlg.h"

#include "MyExcelz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAddQWRDlg dialog


CAddQWRDlg::CAddQWRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddQWRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddQWRDlg)
	m_EName = _T("");
	m_ESfz = _T("");
	m_ETel = _T("");
	//}}AFX_DATA_INIT
}


void CAddQWRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQWRDlg)
	DDX_Control(pDX, IDC_LIST_QWR, m_List_QWR);
	DDX_Text(pDX, IDC_EDIT_NAME, m_EName);
	DDX_Text(pDX, IDC_EDIT_SFZ, m_ESfz);
	DDX_Text(pDX, IDC_EDIT_TEL, m_ETel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQWRDlg, CDialog)
	//{{AFX_MSG_MAP(CAddQWRDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_QWR, OnItemchangedListQwr)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQWRDlg message handlers

BOOL CAddQWRDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List_QWR.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_List_QWR.InsertColumn(0,_T("���"),LVCFMT_LEFT,60,-1);
	m_List_QWR.InsertColumn(1,_T("����"),LVCFMT_LEFT,120,-1);
	m_List_QWR.InsertColumn(2,_T("���֤"),LVCFMT_LEFT,180,-1);
	m_List_QWR.InsertColumn(3,_T("�ֻ���"),LVCFMT_LEFT,100,-1);
	m_List_QWR.InsertColumn(4,_T("����ɽ��"),LVCFMT_LEFT,120,-1);
	m_List_QWR.InsertColumn(5,_T("δ��ɽ��"),LVCFMT_LEFT,120,-1);

	UpdateQWRList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddQWRDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EName==_T("") || m_ESfz==_T(""))
	{
		MessageBox("���� ���֤ ����Ϊ��!");
	}
	
	CString temp,temp1;
	try
	{
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance("ADODB.Recordset");
		pRecordset->CursorLocation = adUseClient;
		CString strSQL;
		
		strSQL.Format("select * from QWR where QName = '%s'  ", m_EName);
		pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
			adOpenDynamic, adLockOptimistic, adCmdText);
		if(pRecordset->RecordCount == 1)
		{
			temp1.Format("���ݿ����Ѵ���!�Ƿ�Ҫ������Ϣ:[%s]",m_EName);
			if(MessageBox(temp1,"�޸���ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->PutCollect("QName",(_variant_t)m_EName);
				pRecordset->PutCollect("QSFZ",(_variant_t)m_ESfz);
				pRecordset->PutCollect("QTel",(_variant_t)m_ETel);
				pRecordset->Update();
				MessageBox("�޸ĳɹ�!");
			}
		}
		else if(pRecordset->RecordCount == 0)
		{
			temp1.Format("�Ƿ�����ǩԼ��:[%s]",m_EName);
			if(MessageBox(temp1,"������ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->AddNew();
				pRecordset->PutCollect("QName",(_variant_t)m_EName);
				pRecordset->PutCollect("QSFZ",(_variant_t)m_ESfz);
				pRecordset->PutCollect("QTel",(_variant_t)m_ETel);
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
		
		UpdateQWRList();
		m_EName = _T("");
		m_ESfz = _T("");
		m_ETel = _T("");
		UpdateData(FALSE);
		
		
	}
	catch (_com_error e) 
	{
		temp1.Format("������ʾ,���ǩԼ������ʧ��!\n%s",e.Description());
		MessageBox(temp1);
	}
}

void CAddQWRDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	
	if ( m_EName == "")
	{
		MessageBox("����ѡ���±���Ҫɾ��������!");
	}
	else
	{
		CString temp;
		temp.Format("�Ƿ�Ҫɾ��[%s]",m_EName);
		if(MessageBox(temp,"ɾ����ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{		
			try
			{
				_RecordsetPtr pRecordset;
				CString strSQL;	
				pRecordset.CreateInstance("ADODB.Recordset");
				pRecordset->CursorLocation = adUseClient;		
				strSQL.Format("select * from QWR where QName = '%s'  ", m_EName);
				pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
					adOpenDynamic, adLockOptimistic, adCmdText);
				
				if(pRecordset->RecordCount == 0)
				{
					temp.Format("ɾ��ʧ��!���ݿ����޸ü�¼![%s]",m_EName);
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
					UpdateQWRList();
				}
				m_EName = _T("");
				m_ESfz = _T("");
				m_ETel = _T("");
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


BOOL CAddQWRDlg::UpdateQWRList()
{	
	int k = 0;
	CString tempk;
	m_List_QWR.DeleteAllItems();//����б�
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("select * from QWR");
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strName,strSFZ,strTel;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("QName");
				if (vat.vt != VT_NULL)
				{
					strName = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("QSFZ");
				if (vat.vt != VT_NULL)
				{
					strSFZ = (LPCSTR)_bstr_t(vat);
				}
				vat =pSet->GetCollect("QTel");
				if (vat.vt != VT_NULL)
				{
					strTel = (LPCSTR)_bstr_t(vat);
				}
				tempk.Format("%d",k+1);
				m_List_QWR.InsertItem(k,tempk);
				m_List_QWR.SetItemText(k,1,strName);
				m_List_QWR.SetItemText(k,2,strSFZ);
				m_List_QWR.SetItemText(k,3,strTel);
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
		tempk.Format("������ʾ,UpdateQWRList�����б�ʧ��!%s",comError.Description());
		AfxMessageBox(tempk);
		return FALSE;
	}
	return TRUE;
}

void CAddQWRDlg::OnItemchangedListQwr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_EName = m_List_QWR.GetItemText(pNMListView->iItem,1);
	m_ESfz = m_List_QWR.GetItemText(pNMListView->iItem,2);
	m_ETel = m_List_QWR.GetItemText(pNMListView->iItem,3);
	UpdateData(FALSE);
	*pResult = 0;
}

void CAddQWRDlg::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CMyExcelz myexcel;
	myexcel.CreateEApplication("Sheet1");
	myexcel.SetItemTextz(1,1,"ǩԼ�˵���");
	myexcel.DrawList(&m_List_QWR,3,1);
	myexcel.SaveExcel("ǩԼ�˵���");
}

void CAddQWRDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetWindowPos(NULL,0,0,773,506,SWP_NOMOVE | SWP_NOOWNERZORDER );
}

HBRUSH CAddQWRDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
