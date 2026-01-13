// DialogPlayerRemote.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogPlayerRemote.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayerRemote dialog


CDialogPlayerRemote::CDialogPlayerRemote(HANDLE hServer,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPlayerRemote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPlayerRemote)
	m_tDateBegin = 0;
	m_tTimeBegin = 0;
	m_tDateEnd = 0;
	m_tTimeEnd = 0;
	//}}AFX_DATA_INIT
    m_hServer = hServer;
    m_hPlayer = 0;
}


void CDialogPlayerRemote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPlayerRemote)
	DDX_DateTimeCtrl(pDX, IDC_DTP_DATE_BEGIN, m_tDateBegin);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TIME_BEGIN, m_tTimeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DTP_DATE_END, m_tDateEnd);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TIME_END, m_tTimeEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPlayerRemote, CDialog)
	//{{AFX_MSG_MAP(CDialogPlayerRemote)
	ON_BN_CLICKED(IDC_BUTTON_FILE_PLAY, OnButtonFilePlay)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_PLAY_BY_TIME, OnButtonRemotePlayByTime)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayerRemote message handlers
BOOL CDialogPlayerRemote::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    CListCtrl *lpLv = (CListCtrl *)GetDlgItem(IDC_LIST_REPLAY_FILES);
    lpLv->InsertColumn(0,_T("FileName"),LVCFMT_LEFT,100);
    lpLv->InsertColumn(1,_T("FileSize"),LVCFMT_LEFT,80);
    lpLv->SetExtendedStyle(lpLv->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogPlayerRemote::OnButtonFilePlay() 
{
    int nIndex;
    CString strFileName;
    CListCtrl *lpLv = (CListCtrl *)GetDlgItem(IDC_LIST_REPLAY_FILES);
    nIndex = lpLv->GetNextItem(-1, LVNI_SELECTED);
    if(nIndex == 0)
        return;
    strFileName = lpLv->GetItemText(nIndex,0);
    JB_STREAM_PLAY_INFO playinfo;
    if (m_hServer == NULL)
        return;
    if(m_hPlayer)
    {
        JBPlay_Release(m_hPlayer);
        m_hPlayer = 0;
    }
    USES_CONVERSION;
    DWORD dwError = JBPlay_PlayBackByName(m_hServer,T2A(strFileName),
        0,GetDlgItem(IDC_STATIC_PLAY)->GetSafeHwnd(),
        &playinfo,&m_hPlayer);
    if(dwError)
    {
        ShowErrorMessage(dwError);
        return;
    }
	JBPlay_RemotePlayCommand(m_hPlayer, JB_PLAY_CMD_PLAY, 0);	
}

void CDialogPlayerRemote::OnButtonRemotePlayByTime() 
{ 
    UpdateData(TRUE);
    if (m_hServer == NULL)
        return;
    if(m_hPlayer)
    {
        JBPlay_Release(m_hPlayer);
        m_hPlayer = 0;
    }
    JB_STREAM_PLAY_INFO playinfo;
    JBNV_TIME tBegin = {m_tDateBegin.GetYear(), 
                        m_tDateBegin.GetMonth(), 
                        m_tDateBegin.GetDay(),
                        m_tTimeBegin.GetHour(), 
                        m_tTimeBegin.GetMinute(), 
                        m_tTimeBegin.GetSecond()};
    JBNV_TIME tEnd = {  m_tDateEnd.GetYear(), 
                        m_tDateEnd.GetMonth(), 
                        m_tDateEnd.GetDay(),
                        m_tTimeEnd.GetHour(), 
                        m_tTimeEnd.GetMinute(), 
                        m_tTimeEnd.GetSecond()};
 
    DWORD dwret = JBPlay_PlayBackByTime(m_hServer, 0, 
        tBegin, tEnd, 0, GetDlgItem(IDC_STATIC_PLAY)->GetSafeHwnd(), & playinfo, &m_hPlayer);
    if (dwret == 0)
    {
        JBPlay_RemotePlayCommand(m_hPlayer, JB_PLAY_CMD_PLAY, 0);
    }
}

BOOL CDialogPlayerRemote::DestroyWindow() 
{
	if(m_hPlayer)
    {
        JBPlay_Release(m_hPlayer);
        m_hPlayer = 0;
    }
	
	return CDialog::DestroyWindow();
}

void CDialogPlayerRemote::OnButtonSearch() 
{
    if(m_hServer == 0)
        return;
    JBNV_SetMessage(m_hServer,GetSafeHwnd(),WM_JB_MSG);
    JBNV_FIND_FILE_REQ findrequest;
    memset(&findrequest,0,sizeof(findrequest));
    findrequest.dwSize = sizeof(findrequest);
    findrequest.BeginTime.dwYear = 2012;
    findrequest.BeginTime.dwMonth = 03;
    findrequest.BeginTime.dwDay = 8;
    findrequest.BeginTime.dwHour = 0;
    findrequest.BeginTime.dwMinute = 0;
    findrequest.BeginTime.dwSecond = 0;
    
    findrequest.EndTime.dwYear = 2012;
    findrequest.EndTime.dwMonth = 3;
    findrequest.EndTime.dwDay = 8;
    findrequest.EndTime.dwHour = 23;
    findrequest.EndTime.dwMinute = 59;
    findrequest.EndTime.dwSecond = 59;
    
    findrequest.nChannel = -1;
    findrequest.nFileType = 0xff;
    DWORD dwError = JBNV_GetServerConfig(m_hServer,CMD_GET_FILELIST,&findrequest,sizeof(findrequest));
    if(dwError)
    {
        ShowErrorMessage(dwError);
        return;
	}
}

LRESULT CDialogPlayerRemote::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if(message == WM_JB_MSG)
    {
        HANDLE hServer = (HANDLE)wParam;
        JB_SERVER_MSG *lpJbMsg = (JB_SERVER_MSG *)lParam;
        if(hServer == NULL)
            return 0;
        if(lpJbMsg->dwMsg == JB_MSG_FILE_NAME_DATA) 
        {
            CListCtrl *lpLv = (CListCtrl *)GetDlgItem(IDC_LIST_REPLAY_FILES);
            lpLv->DeleteAllItems();
            CString strFileSize;
            JBNV_FIND_FILE_RESP *lpresp = (JBNV_FIND_FILE_RESP *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG));
            JBNV_FILE_DATA_INFO *lpDataInfo = (JBNV_FILE_DATA_INFO *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG) + sizeof(JBNV_FIND_FILE_RESP));
            for(DWORD i = 0; i < lpresp->nCount; i ++)
            {
                lpLv->InsertItem(i,CString(lpDataInfo->sFileName));
                strFileSize.Format(_T("%dM"),lpDataInfo->nFileSize/1024/1024);
                lpLv->SetItemText(i,1,strFileSize);
                TRACE(_T("%40s %10d\n"),lpDataInfo->sFileName,lpDataInfo->nFileSize);
                lpDataInfo ++;
            }
        }
    }
	return CDialog::DefWindowProc(message, wParam, lParam);
}
