// SysSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CHTGL.h"
#include "SysSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCHTGLApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CSysSetDlg dialog


CSysSetDlg::CSysSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysSetDlg)
	m_TypeName = _T("");
	//}}AFX_DATA_INIT
}


void CSysSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysSetDlg)
	DDX_Control(pDX, IDC_LIST_SKLX, m_TypeList);
	DDX_Text(pDX, IDC_EDIT_SKLX, m_TypeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSysSetDlg)
	ON_BN_CLICKED(IDC_BTN_SKLXSAVE, OnBtnSklxsave)
	ON_BN_CLICKED(IDC_BTN_SKLXDEL, OnBtnSklxdel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SKLX, OnItemchangedListSklx)
	ON_BN_CLICKED(IDC_BTN_Backup, OnBTNBackup)
	ON_BN_CLICKED(IDC_BTN_Restore, OnBTNRestore)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysSetDlg message handlers

void CSysSetDlg::OnBtnSklxsave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_TypeName == "")
	{
		MessageBox("������ʾ,�տ��������Ʋ���Ϊ��");
	}
	else
	{
		AddTypeList();
		m_TypeName = _T("");
		UpdateData(FALSE);
	}
}

void CSysSetDlg::OnBtnSklxdel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_TypeName == "")
	{
		MessageBox("����ѡ��Ҫɾ�����տ�����");
	}
	else
	{
		CString temp;
		temp.Format("�Ƿ�Ҫɾ���տ�����[%s]",m_TypeName);
		if(MessageBox(temp,"ɾ����ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{		
			try
			{
				_RecordsetPtr pRecordset;
				CString strSQL;	
				pRecordset.CreateInstance("ADODB.Recordset");
				pRecordset->CursorLocation = adUseClient;		
				strSQL.Format("Select * from TypeofCollection where TypeName = '%s' ", m_TypeName);
				pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
					adOpenDynamic, adLockOptimistic, adCmdText);
				
				if(pRecordset->RecordCount == 0)
				{
					temp.Format("ɾ��ʧ��!���ݿ����޸ü�¼![%s]",m_TypeName);
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
					UpdateTypeList();
				}
				m_TypeName = _T("");
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

BOOL CSysSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TypeList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_TypeList.InsertColumn(0,_T("�տ�����"),LVCFMT_LEFT,160,-1);

	UpdateTypeList();

	CString tempPath;
	TCHAR   exeFullPath[MAX_PATH];
	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	tempPath=exeFullPath;
	ExePath.Format("%s",tempPath.Left(tempPath.ReverseFind('\\')));
	strZDB.Format("%s\\Data.zdb",ExePath);//��ǰĿ¼�µ�LOG�ļ�·��

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CSysSetDlg::UpdateTypeList()
{	
	int k = 0;
	CString tempk;
	m_TypeList.DeleteAllItems();//����б�
	try
	{
		VARIANT cnt;
		cnt.vt = VT_INT;
		CString temp;
		temp.Format("SELECT * FROM TypeofCollection");
		_RecordsetPtr pSet = theApp.m_pConn->Execute((_bstr_t)temp,&cnt,adCmdUnknown);
		_variant_t vat;
		CString strTypeName;
		if(pSet != NULL)
		{
			while(!pSet->adoEOF)
			{
				vat =pSet->GetCollect("TypeName");
				if (vat.vt != VT_NULL)
				{
					strTypeName = (LPCSTR)_bstr_t(vat);
				}
				m_TypeList.InsertItem(k,strTypeName);
				k++;
				pSet->MoveNext();
			}
		}
		else
		{	
			TRACE("��ѯ����¼Ϊ��\n");
			return FALSE;
		}
//		theApp.m_pConn->Close();
	}
	catch (_com_error &comError)
	{
		tempk.Format("������ʾ,�����տ������б�ʧ��!%s",comError.Description());
		AfxMessageBox(tempk);
		return FALSE;
	}
	return TRUE;
}


void CSysSetDlg::OnItemchangedListSklx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_TypeName = m_TypeList.GetItemText(pNMListView->iItem,0);
	UpdateData(FALSE);
	*pResult = 0;
}


void CSysSetDlg::AddTypeList()
{
	
	CString temp,temp1;
	try
	{
		_RecordsetPtr pRecordset;
		pRecordset.CreateInstance("ADODB.Recordset");
		pRecordset->CursorLocation = adUseClient;
		CString strSQL;
		
		strSQL.Format("select * from TypeofCollection where TypeName = '%s'", m_TypeName);
		pRecordset->Open((_variant_t)_bstr_t(strSQL), _variant_t((IDispatch*)theApp.m_pConn, true), 
			adOpenDynamic, adLockOptimistic, adCmdText);
		if(pRecordset->RecordCount == 1)
		{
			temp1.Format("���ݿ����Ѵ���!�Ƿ�Ҫ������������Ϊ:,[%s]",m_TypeName);
			if(MessageBox(temp1,"�޸���ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->PutCollect("TypeName",(_variant_t)m_TypeName);
				pRecordset->Update();
			}
		}
		else if(pRecordset->RecordCount == 0)
		{
			temp1.Format("�Ƿ������տ�����:[%s]",m_TypeName);
			if(MessageBox(temp1,"������ʾ" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{
				pRecordset->AddNew();
				pRecordset->PutCollect("TypeName",(_variant_t)m_TypeName);
				pRecordset->Update();
			}
		}
		else
		{
			MessageBox("��ʾ,�˱�������ݿ��д��ڲ�ֹ1����¼!");
		}
		
		pRecordset->Close();
		pRecordset.Release();
		UpdateTypeList();
	}
	catch (_com_error e) 
	{
		temp1.Format("������ʾ,����տ�����ʧ��!\n%s",e.Description());
		MessageBox(temp1);
	}	
}

void CSysSetDlg::OnBTNBackup() 
{
	// TODO: Add your control notification handler code here
	CString bkfileName;
	CTime tempT=CTime::GetCurrentTime();

	bkfileName.Format("BK%s.zdb",tempT.Format("%Y%m%d%H%M%S"));
	CFileDialog dlg(FALSE,".zdb",bkfileName,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"��������(*.zdb)|*.zdb||");
	if(dlg.DoModal()==IDOK)
	{
		bkfileName=dlg.GetPathName();
		CopyFile(strZDB,bkfileName,FALSE);
		AfxMessageBox("�������"+bkfileName);
	}
}

void CSysSetDlg::OnBTNRestore() 
{
	// TODO: Add your control notification handler code here
	CString resFileName;
	CFileDialog dlg(TRUE,".zdb",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"��������(*.zdb)|*.zdb||");
	if(dlg.DoModal()==IDOK)
	{
		if (theApp.m_pConn->GetState() == adStateOpen)
		{
			theApp.m_pConn->Close();
		}
		if (theApp.m_pConn)
		{
			theApp.m_pConn.Release();
			theApp.m_pConn = NULL;
		}
		resFileName=dlg.GetPathName();
		CopyFile(resFileName,strZDB,FALSE);
		AfxMessageBox("��ԭ���!");
		SetCurrentDirectory(ExePath);
		if(FALSE==theApp.CreateConn())
		{
			AfxMessageBox("��������ʧ��!���������� !");			
		}
	}
}

HBRUSH CSysSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
