// DialogLogon.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogLogon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogLogon dialog


CDialogLogon::CDialogLogon(CString strServerIp,WORD wServerPort,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLogon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogLogon)
	m_strPassword = _T("admin");
	m_nPort = wServerPort;
	m_strServer = strServerIp;
	m_strUserName = _T("admin");
	//}}AFX_DATA_INIT
}


void CDialogLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogLogon)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 32);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 80, 65535);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_strServer);
	DDV_MaxChars(pDX, m_strServer, 64);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogLogon, CDialog)
	//{{AFX_MSG_MAP(CDialogLogon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogLogon message handlers

void CDialogLogon::OnOK() 
{
	UpdateData();
	
	CDialog::OnOK();
}
