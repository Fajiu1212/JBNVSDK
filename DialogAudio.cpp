// DialogAudio.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogAudio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagAUDIO_VOLUME_CONTROL{
    unsigned char bADC;
    unsigned char bDAC;
    unsigned char bGAIN;
    unsigned char bReserved[9];
}AUDIO_VOLUME_CONTROL;

/////////////////////////////////////////////////////////////////////////////
// CDialogAudio dialog


CDialogAudio::CDialogAudio(HANDLE hServer,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAudio::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAudio)
	//}}AFX_DATA_INIT
    m_hServer = hServer;
}
 

void CDialogAudio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAudio)
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_cSliderGAIN);
	DDX_Control(pDX, IDC_SLIDER_DAC, m_cSliderDAC);
	DDX_Control(pDX, IDC_SLIDER_ADC, m_cSliderADC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAudio, CDialog)
	//{{AFX_MSG_MAP(CDialogAudio)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//14)  P2P
#define DMS_NET_GET_AUDIO_CFG                  0x030510
#define DMS_NET_SET_AUDIO_CFG                  0x030511

BOOL CDialogAudio::OnInitDialog() 
{
	CDialog::OnInitDialog();

    AUDIO_VOLUME_CONTROL vol;
	
	DWORD dwReturn = JBNV_GetServerConfig(m_hServer,DMS_NET_GET_AUDIO_CFG,&vol,sizeof(vol));
    if(dwReturn != 0)
        return FALSE;
    m_cSliderADC.SetRange(0,0x7F);
    m_cSliderDAC.SetRange(0,0x7F); 
    m_cSliderGAIN.SetRange(0,0x1F);

    m_cSliderADC.SetPos(vol.bADC);
    m_cSliderDAC.SetPos(vol.bDAC);
    m_cSliderGAIN.SetPos(vol.bGAIN);

    CString strTmp;
    strTmp.Format(_T("0x%02X"),vol.bADC);
    SetDlgItemText(IDC_STATIC_ADC,strTmp);
    strTmp.Format(_T("0x%02X"),vol.bDAC);
    SetDlgItemText(IDC_STATIC_DAC,strTmp);
    strTmp.Format(_T("0x%02X"),vol.bGAIN);
    SetDlgItemText(IDC_STATIC_GAIN,strTmp);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAudio::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar)
	{
		switch (pScrollBar->GetDlgCtrlID())
		{
		case IDC_SLIDER_ADC:
        case IDC_SLIDER_DAC:
        case IDC_SLIDER_GAIN:
            {
                AUDIO_VOLUME_CONTROL vol;
                memset(&vol,0,sizeof(vol));
                vol.bADC = m_cSliderADC.GetPos();
                vol.bDAC = m_cSliderDAC.GetPos();
                vol.bGAIN = m_cSliderGAIN.GetPos();
                CString strTmp;
                strTmp.Format(_T("0x%02X"),vol.bADC);
                SetDlgItemText(IDC_STATIC_ADC,strTmp);
                strTmp.Format(_T("0x%02X"),vol.bDAC);
                SetDlgItemText(IDC_STATIC_DAC,strTmp);
                strTmp.Format(_T("0x%02X"),vol.bGAIN);
                SetDlgItemText(IDC_STATIC_GAIN,strTmp);
                JBNV_SetServerConfig(m_hServer,DMS_NET_SET_AUDIO_CFG,&vol,sizeof(vol));
            }
            break;
        default:
            break;
        }
    }
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
