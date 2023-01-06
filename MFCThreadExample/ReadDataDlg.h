#pragma once
#include "datadialog.h"
#include <iostream>
#include <fstream>

using namespace std;

class CReadDataDlg :	public CDataDialog
{
	DECLARE_DYNAMIC(CReadDataDlg)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();	
	
	DECLARE_MESSAGE_MAP()

public:
	CReadDataDlg(CWnd* pParent = NULL);
	virtual ~CReadDataDlg(void);

	afx_msg void OnOK();
	afx_msg void OnCancle();
	afx_msg void OnReadDataFromTheFile();
	void ReadThread(void *pParam);	
	virtual CWnd* GetParent();

	CWinThread *m_pWinThread;	
private:	
	CWnd* m_pParent;
};
