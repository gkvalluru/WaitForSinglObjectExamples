#pragma once
#include "datadialog.h"
#include <iostream>
#include <fstream>

using namespace std;

class CWriteDataDlg :	public CDataDialog
{
	DECLARE_DYNAMIC(CWriteDataDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	
	DECLARE_MESSAGE_MAP()

public:
	CWriteDataDlg(CWnd* pParent = NULL);
	virtual ~CWriteDataDlg(void);

	afx_msg void OnOK();
	afx_msg void OnCancle();
	afx_msg void OnWriteDataInToFile();

	virtual CWnd* GetParent();
	
	CWinThread *m_pWinThread;

private:
	CWnd* m_pParent;	
};
