#pragma once

#include "Resource.h"
// DataDialgo dialog

class CDataDialog : public CDialog
{
	DECLARE_DYNAMIC(CDataDialog)

public:
	CDataDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataDialog();

// Dialog Data
	enum { IDD = IDD_DATADIALGO };
	
	virtual CString GetWriteDataFromTextCtrl();
	virtual void SetDataToTextCtrl(CString str);
	void SetWindowTitle(CString str);
	void SetButtonText(CString str);
	void SetReadAndWriteStraticText(CString str);
	void EnableMainWndOKButton();
	void EnableDisableButtons(BOOL bVal);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_strWindowTitle;
	CEdit m_EditCtrl;
	CButton m_WriteButton;	
	CStatic m_ReadAndWriteText;
	CWnd* m_pParent;
};
