// MFCThreadExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCThreadExample.h"
#include "MFCThreadExampleDlg.h"

#include <iostream>

using namespace std;

UINT WriteDataIntoTheFile(void *pParam);
UINT ReadDataFromTheFile(void *pParam);


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FILE_NAME "WriteAndReadData.txt"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCThreadExampleDlg dialog




CMFCThreadExampleDlg::CMFCThreadExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCThreadExampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	

	m_pWriteDlg = NULL;
	m_pReadDlg = NULL;
	m_isSeekFromBegening = true;	
}

CMFCThreadExampleDlg::~CMFCThreadExampleDlg()
{
	m_fReadAndWriteStream.close();
}


void CMFCThreadExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_WRITEDLG, m_WriteDlgText);
	DDX_Control(pDX, IDC_STATIC_READDLG, m_ReadDlgText);

	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCThreadExampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCThreadExampleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CMFCThreadExampleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCThreadExampleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCThreadExampleDlg message handlers

BOOL CMFCThreadExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);		
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCThreadExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCThreadExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCThreadExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCThreadExampleDlg::OnBnClickedButton1()
{
	if(m_pWriteDlg)
	{
		m_pWriteDlg ->SetForegroundWindow();
	}
	else
	{
		CWnd *pWnd = GetDesktopWindow();
		m_pWriteDlg = new CWriteDataDlg(this);
		m_pWriteDlg->SetWindowTitle(_T("Write Dialog"));
		m_pWriteDlg->Create(CDataDialog::IDD, pWnd);
		m_pWriteDlg->SetButtonText(_T("Write"));
		m_pWriteDlg->ShowWindow(SW_SHOW);

		GetDlgItem(IDOK)->EnableWindow(FALSE);
		m_WriteDlgText.SetWindowText(_T("Write Dlg Opend..."));
	}
}

void CMFCThreadExampleDlg::OnBnClickedButton2()
{
	if(m_pReadDlg)
	{
		m_pReadDlg->SetForegroundWindow();
	}
	else
	{
		CWnd *pWnd = GetDesktopWindow();
		m_pReadDlg = new CReadDataDlg(this);
		m_pReadDlg->SetWindowTitle(_T("Read Dialog"));
		m_pReadDlg->Create(CDataDialog::IDD, pWnd);
		m_pReadDlg->SetButtonText(_T("Read"));
		m_pReadDlg->ShowWindow(SW_SHOW);

		GetDlgItem(IDOK)->EnableWindow(FALSE);
		m_ReadDlgText.SetWindowText(_T("Read Dlg Opend..."));
	}		
}


void CMFCThreadExampleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CMFCThreadExampleDlg::WriteDataInToFile(CString strData)
{

	if(!m_fReadAndWriteStream.is_open())
		m_fReadAndWriteStream.open("Open_File.txt", ios::in | ios::out | ios::trunc);

	if(m_fReadAndWriteStream.is_open())
	{
		//https://stackoverflow.com/questions/5550838/how-to-convert-cstring-to-ofstream

		m_fReadAndWriteStream << CT2A(strData) << "\n";
		m_fReadAndWriteStream.flush();

		m_iCurOffset = m_fReadAndWriteStream.tellp(); 

		if(m_isSeekFromBegening)
		{
			m_fReadAndWriteStream.seekg(0, ios::beg);
			m_isSeekFromBegening = false;
			m_iOldOffSet = m_iCurOffset;
		}
		else
		{
			m_fReadAndWriteStream.seekg(m_iOldOffSet, ios::beg);
			m_iOldOffSet = m_iCurOffset;
		}
	}
}

CString CMFCThreadExampleDlg::ReadDataInFromFile()
{
	if(m_fReadAndWriteStream.is_open())
	{
		CString strData;
		string name;

		while(m_fReadAndWriteStream >> name)
		{
			CString strTemp;
			strTemp = name.c_str();	
			strData = strData + strTemp + _T(" ");
		}

		m_fReadAndWriteStream.seekg(m_iCurOffset, ios::end);

		return strData;
	}

	return _T("");
}

