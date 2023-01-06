// MFCThreadExampleDlg.h : header file
//
#include "WriteDataDlg.h"
#include "ReadDataDlg.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define FILE_NAME "WriteAndReadData.txt"

#pragma once


// CMFCThreadExampleDlg dialog
class CMFCThreadExampleDlg : public CDialog
{
// Construction
public:
	CMFCThreadExampleDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMFCThreadExampleDlg();

// Dialog Data
	enum { IDD = IDD_MFCTHREADEXAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();	

	void WriteDataInToFile(CString strData);
	CString ReadDataInFromFile();

	CWriteDataDlg *m_pWriteDlg;
	CReadDataDlg *m_pReadDlg;

	fstream m_fReadAndWriteStream;

	bool m_isSeekFromBegening;
	int m_iCurOffset;
	int m_iOldOffSet;

	CStatic m_WriteDlgText;
	CStatic m_ReadDlgText;
};
