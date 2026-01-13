// DialogPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogPlayer.h"
#include <afxctl.h>
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayer dialog
#define		WM_PLAY_MSG			(WM_USER + 1001)

CDialogPlayer::CDialogPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPlayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPlayer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_hPlay = 0;
    m_dwCountTime = 0;
}


void CDialogPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPlayer)
	DDX_Control(pDX, IDC_SLIDER_PLAYPOS, m_Slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPlayer, CDialog)
	//{{AFX_MSG_MAP(CDialogPlayer)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, OnButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STEP_IN, OnButtonStepIn)
	ON_BN_CLICKED(IDC_BUTTON_STEP_OUT, OnButtonStepOut)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, OnButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PLAYFAST, OnButtonPlayfast)
	ON_BN_CLICKED(IDC_BUTTON_FASTBACK, OnButtonFastback)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, OnButtonRelease)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PLAYPOS, OnReleasedcaptureSliderPlaypos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayer message handlers

void CDialogPlayer::OnButtonOpenfile() 
{
    if(m_hPlay)
    {
        JBPlay_Release(m_hPlay);
        m_hPlay = 0;
    }
    CFileDialog dlg(TRUE);
    if(dlg.DoModal() != IDOK)
        return;
    USES_CONVERSION;
    DWORD dwReturn = JBPlay_OpenFile(T2A(dlg.GetPathName()),1,
        (GetDlgItem(IDC_STATIC_PLAY))->GetSafeHwnd(),0,
        &m_hPlay);
    if(m_hPlay)
    {
        JB_STREAM_PLAY_INFO jbplayinfo;
        CString strTime;
        memset(&jbplayinfo,0,sizeof(jbplayinfo));
        JBPlay_SetMessage(m_hPlay,GetSafeHwnd(),WM_PLAY_MSG);
        JBPlay_SetAudio(m_hPlay,TRUE);
        JBPlay_SetVolume(m_hPlay,10000);
        JBPlay_GetPlayInfo(m_hPlay,&jbplayinfo);
        m_dwCountTime = jbplayinfo.dwTimeLength / 1000;
        strTime.Format(_T("%02d:%02d:%02d"),m_dwCountTime / 3600,(m_dwCountTime / 60) % 60,m_dwCountTime % 60);
        SetDlgItemText(IDC_STATIC_TOTALTIME,strTime);
        m_Slider.SetRange(0,m_dwCountTime);
        OnButtonPlay();
    }
    else
    {
        ShowErrorMessage(dwReturn);
        SetDlgItemText(IDC_STATIC_TOTALTIME,_T("00:00:00"));
	}
}

void CDialogPlayer::OnButtonPlay() 
{
    if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_PLAY);
	}
}

LRESULT CDialogPlayer::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if(message == WM_PLAY_MSG) 
    {
        HANDLE hPlayer = (HANDLE)wParam;
        CString strTime;
        if(lParam == -1)
            lParam = m_dwCountTime;
        m_Slider.SetPos(lParam);
        strTime.Format(_T("%02d:%02d:%02d"),lParam/3600,(lParam/60)%60,lParam%60);
        GetDlgItem(IDC_STATIC_START_TIME)->SetWindowText(strTime);
        JB_STREAM_PLAY_INFO jbplayinfo;
        JBPlay_GetPlayInfo(hPlayer,&jbplayinfo);
    } 
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CDialogPlayer::OnButtonPause() 
{
    if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_PAUSE);
	}
}

void CDialogPlayer::OnButtonStepIn() 
{
    if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_STEPIN);
	}
}

void CDialogPlayer::OnButtonStepOut() 
{
    if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_STEPOUT);
	}
}

void CDialogPlayer::OnButtonCapture() 
{
    if(m_hPlay)
    {
        JBPlay_CapturePicture(m_hPlay,"D:\\test.bmp");
	}
}

void CDialogPlayer::OnButtonStop() 
{
	if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_STOP);
	}
}

void CDialogPlayer::OnButtonPlayfast() 
{
	if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_FASTPLAY);
	}
}

void CDialogPlayer::OnButtonFastback() 
{
    if(m_hPlay)
    {
        JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_FASTBACK);
	}
}

void CDialogPlayer::OnButtonRelease() 
{
    if(m_hPlay)
    {
        JBPlay_Release(m_hPlay);
        m_hPlay = 0;
	}
}

BOOL CDialogPlayer::DestroyWindow() 
{
	OnButtonRelease();
	
	return CDialog::DestroyWindow();
}

void CDialogPlayer::OnReleasedcaptureSliderPlaypos(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if(m_dwCountTime == 0 || m_hPlay == 0)
        return;
    CString str;
    JBPlay_SeekToSecond(m_hPlay,m_Slider.GetPos());
    str.Format (_T("%02d:%02d:%02d"),m_Slider.GetPos()/3600,(m_Slider.GetPos()/60)%60,m_Slider.GetPos()%60);
    SetDlgItemText(IDC_STATIC_START_TIME,str);
    JBPlay_PlayCommand(m_hPlay,JB_PLAY_CMD_PLAY);
 
	*pResult = 0;
}

BOOL CDialogPlayer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Slider.SetRange(0,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
