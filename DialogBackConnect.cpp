// DialogBackConnect.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogBackConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		WM_BACKCONNECT_MSG	(WM_USER + 3220)
/////////////////////////////////////////////////////////////////////////////
// CDialogBackConnect dialog


CDialogBackConnect::CDialogBackConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogBackConnect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogBackConnect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_hServer = 0;
    m_bStartBackConnect = FALSE;
}


void CDialogBackConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogBackConnect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogBackConnect, CDialog)
	//{{AFX_MSG_MAP(CDialogBackConnect)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_BACK_CONNECT, OnButtonOpenBackConnect)
	ON_BN_CLICKED(IDC_BUTTON_END, OnButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CHANNEL, OnButtonOpenChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBackConnect message handlers

int WINAPI JBNV_BackConnectCallBack(JBNV_BROADCAST_DATA *lpData,DWORD dwUser)
{
    CDialogBackConnect *lpDlg = (CDialogBackConnect *)dwUser;
    if(dwUser == 0)
        return 0;
    lpDlg->SendMessage(WM_BACKCONNECT_MSG,(DWORD)lpData);
    return 0;
}

void CDialogBackConnect::OnButtonStart() 
{
    DWORD dwError;
    if(m_bStartBackConnect)
    {
        OnButtonEnd();
    }
    dwError = JBNV_StartBackConnectListen(GetSafeHwnd(),
        WM_BACKCONNECT_MSG, //SDK Message
        8800);              //Local Listen Port

    //dwError = JBNV_StartBackConnectListenEx(JBNV_BackConnectCallBack,this,8800);
    if(dwError)
    {
        ShowErrorMessage(dwError);
        return;
    }
    SetDlgItemText(IDC_STATIC_INFO,_T("Start Listen At Port 8800"));
    m_bStartBackConnect = TRUE;
}

void CDialogBackConnect::OnButtonOpenBackConnect() 
{
    CComboBox *lpCmb = (CComboBox *)GetDlgItem(IDC_COMBO_SERVER);
    if(lpCmb == 0)
        return ;
    if(m_hServer)
    {
        JBNV_CloseServer(m_hServer);
        m_hServer = 0;
    }
    int nItem = lpCmb->GetCurSel();
    if(nItem < 0)
    {
        return;
    }

    JBNV_BROADCAST_DATA *lpData = (JBNV_BROADCAST_DATA *)lpCmb->GetItemData(nItem);
    if(lpData == 0)
        return ;
    struct in_addr addr;
    addr.s_addr = lpData->dwRemoteIp;
    TRACE(_T("Start Connect To %s(%d)\n"),CString(inet_ntoa(addr)),lpData->wRemotePort);
    DWORD dwError = JBNV_OpenServerByBackConnect(lpData->dwRemoteIp,lpData->wRemotePort,"admin","admin",&m_hServer);
    if(dwError)
    {
        ShowErrorMessage(dwError);
        return;
    }
    //设置消息，当服务器连接上后，通过此消息通知用户
    JBNV_SetMessage(m_hServer,GetSafeHwnd(),WM_JB_MSG);
	AfxMessageBox(_T("Back Connect To Server Success"));
}

void CDialogBackConnect::OnButtonEnd() 
{
    DWORD dwError = JBNV_StopBackConnectListen();
    if(dwError)
    {
        ShowErrorMessage(dwError);
        return;
    }
    m_bStartBackConnect = FALSE;
}

BOOL CDialogBackConnect::DestroyWindow() 
{
	if(m_hServer)
    {
        JBNV_CloseServer(m_hServer);
        m_hServer = 0;
    }
    if(m_bStartBackConnect)
    {
        OnButtonEnd();
    }
	return CDialog::DestroyWindow();
}

LRESULT CDialogBackConnect::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if(message == WM_BACKCONNECT_MSG)
    {
        JBNV_BROADCAST_DATA *lpbcdata = (JBNV_BROADCAST_DATA *)wParam;
        CComboBox *lpCmb = (CComboBox *)GetDlgItem(IDC_COMBO_SERVER);
        if(lpCmb == 0)
            return 0;
        struct in_addr addr;
        addr.s_addr = lpbcdata->dwRemoteIp;
 
        CString strRemoteIp;
        CString strTmp;

        strRemoteIp.Format(_T("B_%s"),CString(inet_ntoa(addr)));
        strTmp.Format(_T("Recv Device %s Connect\n"),strRemoteIp);
        SetDlgItemText(IDC_STATIC_INFO,strTmp);
        int nIndex = lpCmb->FindString(-1,strRemoteIp);
        if(nIndex == -1)
        {
            int nItem = lpCmb->InsertString(-1,strRemoteIp);
            JBNV_BROADCAST_DATA *lpdata = new JBNV_BROADCAST_DATA;
            memcpy(lpdata,lpbcdata,sizeof(JBNV_BROADCAST_DATA));
            lpCmb->SetItemData(nItem,(DWORD)lpdata);
            lpCmb->SetCurSel(0);
        }
        else
        {
            JBNV_BROADCAST_DATA *lpData = (JBNV_BROADCAST_DATA *)lpCmb->GetItemData(nIndex);
            if(lpData)
                memcpy(lpData,lpbcdata,sizeof(JBNV_BROADCAST_DATA));
        }
    }
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CDialogBackConnect::OnButtonOpenChannel() 
{
	if(m_hServer == 0)
		return;

 
	
}
