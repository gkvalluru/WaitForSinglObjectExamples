#include "StdAfx.h"
#include "WriteDataDlg.h"
#include "MFCThreadExampleDlg.h"
#include "Resource.h"


UINT WriteDataIntoTheFile(void *pParam);

IMPLEMENT_DYNAMIC(CWriteDataDlg, CDataDialog)

CWriteDataDlg::CWriteDataDlg(CWnd* pParent) : CDataDialog(pParent)
{
	m_pParent = pParent;
	m_pWinThread = NULL;
}

void CWriteDataDlg::DoDataExchange(CDataExchange* pDX)
{	
	CDataDialog::DoDataExchange(pDX);
}


BOOL CWriteDataDlg::OnInitDialog()
{
	return CDataDialog::OnInitDialog();
}


CWriteDataDlg::~CWriteDataDlg(void)
{
		
}

BEGIN_MESSAGE_MAP(CWriteDataDlg, CDataDialog)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL,OnCancle)
	ON_COMMAND(DATAFILE_BUTTON, OnWriteDataInToFile)
END_MESSAGE_MAP()


void CWriteDataDlg::PostNcDestroy()
{	
	CDialog::PostNcDestroy();
	if(m_pParent)
	{
		((CMFCThreadExampleDlg *)m_pParent)->m_pWriteDlg = NULL;
	}	

	EnableMainWndOKButton();
}

void CWriteDataDlg::OnOK()
{
	if(UpdateData(true))
    {	
		((CMFCThreadExampleDlg*)m_pParent)->UpdateData(false);
        DestroyWindow();
	}
}

void CWriteDataDlg::OnCancle()
{
	DestroyWindow();	
}

CWnd* CWriteDataDlg::GetParent()
{
	return m_pParent;
}


void CWriteDataDlg::OnWriteDataInToFile()
{
	EnableDisableButtons(FALSE);

	if(m_pWinThread == NULL)
	{
		m_pWinThread = AfxBeginThread(WriteDataIntoTheFile, this);	
		SetReadAndWriteStraticText(_T("Data Writing thread started...."));
	}
	else
	{
		CMFCThreadExampleDlg *pMainWnd = (CMFCThreadExampleDlg*)m_pParent;

		if(pMainWnd->m_pReadDlg != NULL && pMainWnd->m_pReadDlg->m_pWinThread != NULL)
			WaitForSingleObject(pMainWnd->m_pReadDlg->m_pWinThread->m_hThread, INFINITE);

		m_pWinThread->ResumeThread();
	}
}


UINT WriteDataIntoTheFile(void *pParam)
{	
	/*CString sFileName;
	pWriteData->m_fileObject.Open(_T("WriteAndReadData.txt"), CFile::modeCreate|CFile::modeWrite);
	char szSampleText[100];
     strcpy(szSampleText, "Sample Text for CFile Write function Example");
     pWriteData->m_fileObject.Write(szSampleText,100); */

	CWriteDataDlg *pWriteData = (CWriteDataDlg*)pParam;	
	CWnd *pParent = pWriteData->GetParent();

	CMFCThreadExampleDlg *pMainWnd = dynamic_cast<CMFCThreadExampleDlg*>(pParent);

	//while(1)
	//{
	CString strData  = pWriteData->GetWriteDataFromTextCtrl();

	if(!strData.IsEmpty())
		pMainWnd->WriteDataInToFile(strData);			

	Sleep(1000);

	pWriteData->EnableDisableButtons(TRUE);

		//pWriteData->SetReadAndWriteStraticText(_T("Data Writing thread suspended...."));
		//pWriteData->m_pWinThread->SuspendThread();	
	//}

	return 0;
}
