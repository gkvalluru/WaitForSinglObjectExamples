// MFCThreadExample.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCThreadExampleApp:
// See MFCThreadExample.cpp for the implementation of this class
//

class CMFCThreadExampleApp : public CWinApp
{
public:
	CMFCThreadExampleApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCThreadExampleApp theApp;