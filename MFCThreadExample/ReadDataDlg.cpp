#include "StdAfx.h"
#include "ReadDataDlg.h"
#include "MFCThreadExampleDlg.h"


UINT ReadDataFromTheFile(void *pParam);

IMPLEMENT_DYNAMIC(CReadDataDlg, CDataDialog)

CReadDataDlg::CReadDataDlg(CWnd* pParent) : CDataDialog(pParent)
{
	m_pParent = pParent;
	m_pWinThread = NULL;
}

void CReadDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDataDialog::DoDataExchange(pDX);
}


BOOL CReadDataDlg::OnInitDialog()
{
	return CDataDialog::OnInitDialog();
}


CReadDataDlg::~CReadDataDlg(void)
{
}

BEGIN_MESSAGE_MAP(CReadDataDlg, CDataDialog)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL,OnCancle)
	ON_COMMAND(DATAFILE_BUTTON, OnReadDataFromTheFile)
END_MESSAGE_MAP()


void CReadDataDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	if(m_pParent)
	{
		((CMFCThreadExampleDlg *)m_pParent)->m_pWriteDlg = NULL;
	}

	EnableMainWndOKButton();
}

void CReadDataDlg::OnOK()
{
	if(UpdateData(true))
    {	
		((CMFCThreadExampleDlg*)m_pParent)->UpdateData(false);
        DestroyWindow();
	}
}

void CReadDataDlg::OnCancle()
{
	DestroyWindow();	
}

void CReadDataDlg::OnReadDataFromTheFile()
{
	ReadThread(this);
}

void CReadDataDlg::ReadThread(void *pParam)
{
	EnableDisableButtons(FALSE);

	if(m_pWinThread == NULL)
	{
		m_pWinThread = AfxBeginThread(ReadDataFromTheFile, this);
		SetReadAndWriteStraticText(_T("Data Reading thread started...."));
	}
	else
	{
		CMFCThreadExampleDlg *pMainWnd = (CMFCThreadExampleDlg*)m_pParent;

		if(pMainWnd->m_pWriteDlg->m_pWinThread == NULL)
			return;

		//if( (pMainWnd->m_pWriteDlg != NULL) && (pMainWnd->m_pWriteDlg->m_pWinThread != NULL) )			
		WaitForSingleObject(pMainWnd->m_pWriteDlg->m_pWinThread->m_hThread, INFINITE);
		
		//m_pWinThread->ResumeThread();
	}
}

CWnd* CReadDataDlg::GetParent()
{
	return m_pParent;
}

UINT ReadDataFromTheFile(void *pParam)
{
	CReadDataDlg *pReadData = (CReadDataDlg*)pParam;
	CWnd *pParent = pReadData->GetParent();

	CMFCThreadExampleDlg *pMainWnd = dynamic_cast<CMFCThreadExampleDlg*>(pParent);

	CString strDataFromFile = _T("");
	strDataFromFile = pMainWnd->ReadDataInFromFile();
	pReadData->SetDataToTextCtrl(strDataFromFile);
	Sleep(1000);

	//pReadData->SetReadAndWriteStraticText(_T("Data Reading thread suspended...."));
	//pReadData->m_pWinThread->SuspendThread();
	pReadData->EnableDisableButtons(TRUE);
	
	return 0;
}
