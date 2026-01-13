// JBSDKDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "JBSDKDemo.h"
#include "JBSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoApp

BEGIN_MESSAGE_MAP(CJBSDKDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CJBSDKDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoApp construction

CJBSDKDemoApp::CJBSDKDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJBSDKDemoApp object

CJBSDKDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoApp initialization

DWORD WINAPI GetWindowsIpAddressInfo (DWORD *lpIpAddress,DWORD *lpdwSize);

BOOL CJBSDKDemoApp::InitInstance()
{
	
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	CoInitialize(NULL);
#if (_MSC_VER <= 1200)
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	DWORD dwIpaddress[256];
	DWORD dwSize = 256 * 4;
	GetWindowsIpAddressInfo(dwIpaddress,&dwSize);

	CJBSDKDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CJBSDKDemoApp::ExitInstance() 
{
	CoUninitialize();
	
	return CWinApp::ExitInstance();
}

void ShowErrorMessage(DWORD dwError)
{
    CHAR csError[256];
    //获取错误信息的默认描述说明
    JBNV_GetErrorMessage(dwError,	//错误号
        csError,	//说明返回描述
        256,		//长度
        GetThreadLocale() & 0xFFFF);//语言
    MessageBox(0,CString(csError),_T("Error"),MB_ICONERROR);
}