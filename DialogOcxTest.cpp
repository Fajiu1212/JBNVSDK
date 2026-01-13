// DialogOcxTest.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogOcxTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOcxTest dialog


CDialogOcxTest::CDialogOcxTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOcxTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOcxTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogOcxTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOcxTest)
	DDX_Control(pDX, IDC_JBNVOCX_CTRL, m_jbnvocx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOcxTest, CDialog)
	//{{AFX_MSG_MAP(CDialogOcxTest)
	ON_BN_CLICKED(IDC_BUTTON_OPENSERVER, OnButtonOpenserver)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, OnButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_OCX_CHANNEL, OnButtonOcxChannel)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, OnButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PLAYPAGE, OnButtonShowPlaypage)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_CHANNEL, OnButtonCloseChannel)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_SERVER, OnButtonCloseServer)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CHN9, OnButtonChn9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#include "DialogLogon.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogOcxTest message handlers

void CDialogOcxTest::OnButtonOpenserver() 
{
    CDialogLogon dlg(m_strServerIp,m_nServerPort);
    if(dlg.DoModal() != IDOK)
        return;
    CString strAdd = dlg.m_strServer;
    WORD wPort = dlg.m_nPort;
    CString strName = dlg.m_strUserName;
    CString strPass = dlg.m_strPassword;
	m_jbnvocx.OpenServer(strAdd,wPort,strName,strPass);
}

void CDialogOcxTest::OnButtonSetup() 
{
	m_jbnvocx.ShowSetup(TRUE,0,0);
}

void CDialogOcxTest::OnButtonOcxChannel() 
{
		m_jbnvocx.OpenChannel(-1,0);
}

void CDialogOcxTest::OnButtonSnapshot() 
{
	m_jbnvocx.SnapShot(-1);
}

void CDialogOcxTest::OnButtonShowPlaypage() 
{
	m_jbnvocx.PlayBack();
}

void CDialogOcxTest::OnButtonCloseChannel() 
{
	m_jbnvocx.CloseChannel(-1);
}

void CDialogOcxTest::OnButtonCloseServer() 
{
	m_jbnvocx.CloseServer();
}

void CDialogOcxTest::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDialogOcxTest::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
    DWORD dwControlID[] = {IDC_BUTTON_OPENSERVER,
        IDC_BUTTON_SETUP,
        IDC_BUTTON_OCX_CHANNEL,
        IDC_BUTTON_SNAPSHOT,
        IDC_BUTTON_SHOW_PLAYPAGE,
        IDC_BUTTON_CLOSE_CHANNEL,
        IDC_BUTTON_CLOSE_SERVER,
        IDOK,IDCANCEL};
	for(int i = 0; i < sizeof(dwControlID) / sizeof(DWORD); i ++)
    {
        CWnd *lpWnd = GetDlgItem(dwControlID[i]);
        if(lpWnd && lpWnd->GetSafeHwnd())
        {
            CRect rc;
            lpWnd->GetWindowRect(&rc);
            rc.top = cy - 20;
            rc.bottom = rc.top + 20;
            lpWnd->MoveWindow(rc.left,rc.top,rc.Width(),rc.Height());
        }
    }
    if(m_jbnvocx.GetSafeHwnd())
    {
        m_jbnvocx.MoveWindow(0,0,cx,cy - 30);
    }
}

void CDialogOcxTest::OnButtonChn9() 
{
	m_jbnvocx.SetShowWindows(9);
	
}
