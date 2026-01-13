// DialogTalkback.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogTalkback.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTalkback dialog


CDialogTalkback::CDialogTalkback(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTalkback::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTalkback)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogTalkback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTalkback)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogTalkback, CDialog)
	//{{AFX_MSG_MAP(CDialogTalkback)
	ON_BN_CLICKED(IDC_BUTTON_BEGINTALK, OnButtonBegintalk)
	ON_BN_CLICKED(IDC_BUTTON_STOPTALK, OnButtonStoptalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTalkback message handlers

void CDialogTalkback::OnButtonBegintalk() 
{
    CString strAdd;
    GetDlgItemText(IDC_EDIT_SERVER,strAdd);
    WORD wPort = GetDlgItemInt(IDC_EDIT_PORT);
    USES_CONVERSION;
    DWORD dwReturn = JBNV_TalkOpen(T2A(strAdd),wPort);
    if(dwReturn)
    {
        ShowErrorMessage(dwReturn);
        return;
	}
}

void CDialogTalkback::OnButtonStoptalk() 
{
    DWORD dwReturn = JBNV_TalkClose();
    if(dwReturn)
    {
        ShowErrorMessage(dwReturn);
        return;
	}
}

BOOL CDialogTalkback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_EDIT_SERVER,_T("192.168.1.16"));
	SetDlgItemText(IDC_EDIT_PORT,_T("8200"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
