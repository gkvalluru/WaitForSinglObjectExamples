// DataDialgo.cpp : implementation file
//

#include "stdafx.h"
#include "MFCThreadExample.h"
#include "DataDialog.h"
#include "MFCThreadExampleDlg.h"


// DataDialgo dialog

IMPLEMENT_DYNAMIC(CDataDialog, CDialog)

CDataDialog::CDataDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDataDialog::IDD, pParent)
{
	m_strWindowTitle = "";
	m_pParent = pParent;
}

CDataDialog::~CDataDialog()
{
}

void CDataDialog::DoDataExchange(CDataExchange* pDX)
{	
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl);	
	DDX_Control(pDX, DATAFILE_BUTTON, m_WriteButton);
	DDX_Control(pDX, IDC_STATIC_READANDWRITE, m_ReadAndWriteText);

	CDialog::DoDataExchange(pDX);
}

BOOL CDataDialog::OnInitDialog()
{
	SetWindowText(m_strWindowTitle);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
	
	if(pSysMenu != NULL)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	return CDialog::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CDataDialog, CDialog)

END_MESSAGE_MAP()


void CDataDialog::SetWindowTitle(CString str)
{
	m_strWindowTitle = str;
}

CString CDataDialog::GetWriteDataFromTextCtrl()
{
	CString sData = _T("");
	m_EditCtrl.GetWindowText(sData);
	m_EditCtrl.SetWindowText(_T(""));

	return sData;
}


void CDataDialog::SetDataToTextCtrl(CString str)
{
	m_EditCtrl.SetWindowText(_T(""));
	m_EditCtrl.SetWindowText(str);
}

void CDataDialog::SetButtonText(CString str)
{
	m_WriteButton.SetWindowText(str);
}

void CDataDialog::SetReadAndWriteStraticText(CString str)
{
	m_ReadAndWriteText.SetWindowText(str);

}

void CDataDialog::EnableDisableButtons(BOOL bVal)
{
	GetDlgItem(IDOK)->EnableWindow(bVal);
}

void CDataDialog::EnableMainWndOKButton()
{
	if(m_pParent)
	{
		CMFCThreadExampleDlg *pMainDlg = (CMFCThreadExampleDlg*)m_pParent;

		if( pMainDlg->m_pWriteDlg == NULL && pMainDlg->m_pReadDlg == NULL)
			pMainDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}