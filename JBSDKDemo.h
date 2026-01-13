// JBSDKDemo.h : main header file for the JBSDKDEMO application
//

#if !defined(AFX_JBSDKDEMO_H__2D0C1CAB_41CC_4EB7_9C1F_855A1748E9FC__INCLUDED_)
#define AFX_JBSDKDEMO_H__2D0C1CAB_41CC_4EB7_9C1F_855A1748E9FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoApp:
// See JBSDKDemo.cpp for the implementation of this class
//

class CJBSDKDemoApp : public CWinApp
{
public:
	CJBSDKDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJBSDKDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJBSDKDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void ShowErrorMessage(DWORD dwError);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JBSDKDEMO_H__2D0C1CAB_41CC_4EB7_9C1F_855A1748E9FC__INCLUDED_)
