// JBSDKDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JBSDKDemo.h"
#include "JBSDKDemoDlg.h"
#include "DialogBackConnect.h"

#pragma comment (lib,"./lib/jbnvsdk.lib")

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
 

#define		WM_SEARCH_SERVER	(WM_USER + 1023)
#define		WM_SERVER_BREAK		(WM_USER + 1025)
#define		TIME_RECORD_ID		1920
#define		TIME_CHANNEL_ID		1921
#define		TIME_CHANNEL_FRAME	1922	

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoDlg dialog

CJBSDKDemoDlg::CJBSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJBSDKDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJBSDKDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hTMServer = 0;
	m_dbaverageframe = 0;
	m_dwFrameCount = 0;
	m_bRecording = 0;
	m_dwRecorded = 0;
	m_bSetSecondWnd = 0;
	m_bZoomed = 0;
	m_dwBeginTime = 0;
	m_dwOldFrameCount = 0;
	m_dwOldRecved = 0;
	m_hServer = 0;
	m_hChannel = 0;
 
}

void CJBSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJBSDKDemoDlg)
	DDX_Control(pDX, IDC_LIST_SERVER, m_lvServer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJBSDKDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CJBSDKDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_OPENCHANNEL, OnButtonOpenchannel)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECONNECT, OnButtonCloseconnect)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_RECORD, OnButtonBeginRecord)
	ON_BN_CLICKED(IDC_BUTTON_STOP_RECORD, OnButtonStopRecord)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_SERVER, OnButtonSearchServer)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_UP, OnButtonPtzUp)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_STOP, OnButtonPtzStop)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_RIGHT, OnButtonPtzRight)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_DOWN, OnButtonPtzDown)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS_FAR, OnButtonFocusFar)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS_NEAR, OnButtonFocusNear)
	ON_BN_CLICKED(IDC_BUTTON_CALL, OnButtonCall)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SECOND_WND, OnButtonSecondWnd)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM, OnButtonZoom)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_SNAPSHOT, OnButtonRemoteSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_LOCAL_SNAPSHOT, OnButtonLocalSnapshot)
	ON_BN_CLICKED(IDC_CHECK_SENSOR_OUT1, OnCheckSensorOut1)
	ON_BN_CLICKED(IDC_CHECK_SENSOR_OUT2, OnCheckSensorOut2)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, OnButtonSwitch)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BUFFER, OnReleasedcaptureSliderBuffer)
	ON_BN_CLICKED(IDC_BUTTON_GET_SERVER_STATE, OnButtonGetServerState)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECHANNEL, OnButtonClosechannel)
	ON_BN_CLICKED(IDC_BUTTON_OCX_TEST, OnButtonOcxTest)
	ON_BN_CLICKED(IDC_BUTTON_FILE_PLAYER, OnButtonFilePlayer)
	ON_BN_CLICKED(IDC_BUTTON_TALKBACK, OnButtonTalkback)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_PLAYER, OnButtonRemotePlayer)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SERVER, OnColumnclickListServer)
	ON_BN_CLICKED(IDC_BUTTON_A_VOL, OnButtonAVol)
	ON_BN_CLICKED(IDC_BUTTON_FACE_LIB, OnButtonFaceLib)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, OnButtonListen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoDlg message handlers

BOOL CJBSDKDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CEdit *lpEdit = (CEdit *)GetDlgItem(IDC_EDIT_CALL);
	lpEdit->SetLimitText(2);
	SetDlgItemInt(IDC_EDIT_CALL,1);
	//初始化参数
	CSliderCtrl *lpSlider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_BUFFER);
	lpSlider->SetRange(0,100);
	lpSlider->EnableWindow(FALSE);
	SetDlgItemInt(IDC_STATIC_MIN_BUFFER,0);
 
 
    m_lvServer.InsertColumn(0,_T("Server"),LVCFMT_LEFT,100);
    m_lvServer.InsertColumn(1,_T("Port"),LVCFMT_LEFT,60);
    m_lvServer.InsertColumn(2,_T("Name"),LVCFMT_LEFT,100);
    m_lvServer.InsertColumn(3,_T("ChannelCount"),LVCFMT_LEFT,100);
    m_lvServer.InsertColumn(4,_T("Type"),LVCFMT_LEFT,80);
    m_lvServer.InsertColumn(5,_T("P2PiD"),LVCFMT_LEFT,140);
	m_lvServer.SetExtendedStyle(m_lvServer.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_hServer = 0;
	m_hChannel = 0;
 
	m_bSetSecondWnd = FALSE;
	m_bRecording = FALSE;
	m_dwRecorded = 0;
	m_bZoomed = FALSE;
	SetDlgItemInt(IDC_EDIT_PORT,8200);
	SetDlgItemText(IDC_EDIT_USERNAME,_T("admin"));
	SetDlgItemText(IDC_EDIT_PASSWORD,_T("admin"));
	//首先开始搜索服务器
	OnButtonSearchServer();
	m_hStreamPlay = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJBSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJBSDKDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJBSDKDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/************************************************************************/
/* SDK                                                                  */
/************************************************************************/

int WINAPI JBNVRecvStreamDataCallback(
					HANDLE hServer,
					DWORD dwClientIndex,	//客户窗口索引，客户自定义
					DWORD dwChannelNo,		//服务器通道号，从0开始
					PBYTE pbDataBuffer,		//结构类型为JBNV_DATAPACK
					DWORD dwUser)
{
	//播放视频数据
	JB_DATAPACK *lpdp = (JB_DATAPACK *)pbDataBuffer;
	CJBSDKDemoDlg *lpDlg = (CJBSDKDemoDlg *)dwUser;
	if(lpdp->IsSampleHead)
		lpDlg->m_dwFrameCount++;
	
	if(lpDlg->m_hStreamPlay)
		JBPlay_InputDataPack(lpDlg->m_hStreamPlay,lpdp);
	return 0;
}

#define VIDEO_DECODE_XVID		1
#define VIDEO_DECODE_H264		2
#define VIDEO_DECODE_MP4A		3
#define VIDEO_DECODE_H2642		4
#define VIDEO_DECODE_MJPEG		5
#define VIDEO_DECODE_X264		6
#define VIDEO_DECODE_MPEG2		7
#define VIDEO_DECODE_H2642_2	1004

#include <atlconv.h>
 
void CJBSDKDemoDlg::OnButtonConnect() 
{
    int nSelect = m_lvServer.GetNextItem(-1, LVNI_SELECTED);
    if(nSelect == -1)
        return;
	OnButtonClosechannel();
	OnButtonCloseconnect();
	HANDLE hServer = 0;
	CString strAdd;
	CString strName;
	CString strPass;
	GetDlgItemText(IDC_EDIT_USERNAME,strName);
	GetDlgItemText(IDC_EDIT_PASSWORD,strPass);
    strAdd = m_lvServer.GetItemText(nSelect,0);
	WORD wPort = _ttoi(m_lvServer.GetItemText(nSelect,1));
	USES_CONVERSION;
	//连接服务器
	DWORD dwError = JBNV_OpenServer(
		T2A(strAdd),					//地址
		wPort,					//端口
		T2A(strName),				//用户名
		T2A(strPass),				//密码
		&m_hServer);			//如果成功，则返回一个此服务器连接的句柄
	if(dwError)
	{
		ShowErrorMessage(dwError);
		return;
	}
	m_dwFrameCount = 0;
	//设置消息，当服务器连接上后，通过此消息通知用户
	JBNV_SetMessage(m_hServer,GetSafeHwnd(),WM_JB_MSG);
	JBNV_SetStreamCallBack(m_hServer,JBNVRecvStreamDataCallback,(DWORD)this);
	if(m_hStreamPlay)
	{
		JBPlay_Release(m_hStreamPlay);
		m_hStreamPlay = 0;
	}
	// Stream Play
	JBNV_SERVER_INFO si;
	si.dwSize = sizeof(si);
	JBNV_GetServerInfo(m_hServer,&si);
	JBPlay_OpenStream(VIDEO_DECODE_H2642,GetDlgItem(IDC_STATIC_PLAY)->GetSafeHwnd(),FALSE,&m_hStreamPlay);
	WAVEFORMATEX wfx;
	memset(&wfx,0,sizeof(wfx ));
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 8000;
	wfx.wBitsPerSample = 16;
	wfx.wFormatTag = 0x003E;
	wfx.nAvgBytesPerSec = 4000;	
	JBPlay_SetAudioFormat(m_hStreamPlay,&wfx); 
	JBPlay_SetAudio(m_hStreamPlay,TRUE);


	AfxMessageBox(_T("Successful connection to the specified server, you can perform any of the following operations."));
}

void WINAPI myDrawOSD( HDC hDC,  SIZE *pImageSize, SIZE *pDCSize, DWORD dwUser)
{
	CJBSDKDemoDlg *lpDlg = (CJBSDKDemoDlg *)dwUser;
	if(lpDlg && hDC)
	{
		if(lpDlg->m_bRecording)
		{
			SetBkMode(hDC,TRANSPARENT);
			HBRUSH hBrush;
			HGDIOBJ hOld;
			RECT rc;
			if(pDCSize->cx > 352)
			{
				rc.left = pDCSize->cx - 48;
				rc.right = pDCSize->cx - 8;
				if(pDCSize->cy > 288)
				{	//D1
					rc.top = 16;
					rc.bottom = 56;
				}
				else
				{	//HD1
					rc.top = 8;
					rc.bottom = 28;
				}
			}
			else if(pDCSize->cx == 352)
			{	//CIF
				rc.left = pDCSize->cx-24;
				rc.right = pDCSize->cx-4;
				rc.top = 8;
				rc.bottom = 28;
			}else {//QCIF
				rc.left = pDCSize->cx-12;
				rc.right = pDCSize->cx-2;
				rc.top = 4;
				rc.bottom = 14;
			}
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOld = SelectObject(hDC,hBrush);
			Ellipse(hDC,rc.left,rc.top,rc.right,rc.bottom);
			SelectObject(hDC,hOld);
			DeleteObject(hBrush);
			CString strTmp;
			strTmp.Format(_T("Recorded %d ...\n"),lpDlg->m_dwRecorded);
			TextOut(hDC,20,50,strTmp,strTmp.GetLength());
		}
	}
}
 

void WINAPI myVideoCallback(HANDLE hHandle,DWORD dwVideoMode,DWORD dwWidth,DWORD dwHeight,BYTE *lpData,DWORD dwLineLength,DWORD dwUser)
{
	//...
}

void CJBSDKDemoDlg::OnButtonOpenchannel() 
{
	if(m_hServer && m_hChannel == 0)
	{
		m_dwFrameCount = 0;
		m_dwOldFrameCount = 0;
		m_dwOldRecved = 0;
		m_dwBeginTime = GetTickCount();
		DWORD dwError = JBNV_OpenChannel(m_hServer,0,0,0,0,GetDlgItem(IDC_STATIC_IMAGE)->GetSafeHwnd(),FALSE,0,&m_hChannel);
		JBNV_SetOSDCallback(m_hChannel,myDrawOSD,(DWORD)this);
		JBNV_SetVideoCallback(m_hChannel,myVideoCallback,(DWORD)this);
		JBNV_Mute(m_hChannel,FALSE);
		SetTimer(TIME_CHANNEL_ID,80,NULL);
		SetTimer(TIME_CHANNEL_FRAME,1000,NULL);
		CSliderCtrl *lpSlider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_BUFFER);
		lpSlider->SetPos(0);
		SetDlgItemInt(IDC_STATIC_MIN_BUFFER,0);
		lpSlider->EnableWindow(TRUE);

		JBNV_CHANNEL_INFO jbci;
		jbci.dwSize = sizeof(jbci);
		JBNV_GetChannelInfo(m_hServer,0,&jbci);
	}
}


long CJBSDKDemoDlg::DefMessageProc(long wParam, long lParam) 
{
	HANDLE hServer = (HANDLE)wParam;
	JB_SERVER_MSG *lpJbMsg = (JB_SERVER_MSG *)lParam;
	TRACE(_T("DefMessageProc %X\n"),lpJbMsg->dwMsg);
	if(hServer == NULL)
		return 0;
	switch(lpJbMsg->dwMsg) {
	case JB_MSG_VIDEOLOST:		//视频丢失
	case JB_MSG_MOVEDETECT:		//移动告警
	case JB_MSG_VIDEORESUME:	//视频恢复
	case JB_MSG_SENSOR_ALARM:	//探头告警
		TRACE(_T("Alarm Info\n"));
		break;
	case JB_MSG_RESETSERVER:	
		//服务器因为参数修改需要重新启动
		//不能在消息回调中执行关闭操作，容易造成死琐，所以
		//使用PostMessage处理，同理，通道断开也需要这样操作。
		TRACE(_T("Server Reboot\n"));
		if(m_hServer == hServer)
			PostMessage(WM_SERVER_BREAK,TRUE);
		return 1;
	case JB_MSG_JPEGSNAP:
		//调用OCX进行图片保存工作
		//m_jbnvocx.DefMessageProc(wParam,lParam);
		break;
	case JB_MSG_UPGRADE:
	case JB_MSG_UPGRADEOK:
		//m_jbnvocx.DefMessageProc(wParam,lParam);
		break;
	case JB_MSG_CRCERROR:
	case JB_MSG_SERVER_BUSY:
	case JB_MSG_TALK_REQUEST:
		break;
	case JB_MSG_COMDATA:
		{
			JB_COM_DATA *lpComData = (JB_COM_DATA *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG));
		}
		break;
	case JB_MSG_USERDATA:
		break;
	case JB_MSG_FILE_NAME_DATA:
		{
			JBNV_FIND_FILE_RESP *lpresp = (JBNV_FIND_FILE_RESP *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG));
			JBNV_FILE_DATA_INFO *lpDataInfo = (JBNV_FILE_DATA_INFO *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG) + sizeof(JBNV_FIND_FILE_RESP));
			for(DWORD i = 0; i < lpresp->nCount; i ++)
			{
				TRACE(_T("%40s %10d\n"),lpDataInfo->sFileName,lpDataInfo->nFileSize);
				lpDataInfo ++;
			}
		}
		break;

	case JB_MSG_FILE_DATA:
		//m_jbnvocx.DefMessageProc(wParam,lParam);
		break;
		//收到人形报警消息
	case JB_MSG_HSR_ALARM:
		{
			ICE_HSR_RESULT_S *lphsr = (ICE_HSR_RESULT_S *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG));
		}
		break;
		//收到人形报警清除消息
	case JB_MSG_HSR_ALARM_C:
		{
	//		TRACE(_T("%s(%d) : JB_MSG_HSR_ALARM_C\n"),CString(__FILE__),__LINE__);			
		}
		break;
		//收到人脸比对消息
	case JB_MSG_FACE_RECOGNIZE:
		{
			DMS_FR_CMP_RET *lpRet = (DMS_FR_CMP_RET *)((char *)lpJbMsg + sizeof(JB_SERVER_MSG));
			if(lpRet->dwSize == sizeof(DMS_FR_CMP_RET))
			{
				/*
				CString strTmp;
				TCHAR m_cRecordDisk = GetFreeDisk();
				if(m_cRecordDisk == 0)
					break;
				ZHX_FR_CMP_RET CmpRet;
				memcpy(&CmpRet,lpRet,sizeof(DMS_FR_CMP_RET));
				strTmp.Format(_T("%c:\\%s\\%s\\%04d-%02d-%02d\\%s(%d)\\%02d(%02d_%02d_%02d_%03d)_Face_%d.JPG"), 
					m_cRecordDisk, GetRecordRootPath(), _T("Capture"),lpJbMsg->st.wYear,lpJbMsg->st.wMonth,lpJbMsg->st.wDay,
					CString(si.szServerIp),si.wServerPort,lpJbMsg->dwChannel + 1, 
					lpJbMsg->st.wHour,lpJbMsg->st.wMinute,lpJbMsg->st.wSecond, lpJbMsg->st.wMilliseconds,
					lpRet->id);
				DWORD dwError = Safe_WriteImageFile(strTmp,((char *)lpRet) + sizeof(DMS_FR_CMP_RET),lpRet->snap_len);
				if(dwError == ERROR_ACCESS_DENIED)
				{
					m_strCaptureFile.Format(_T("人脸图片保存失败，请以管理员身份运行程序后再试"));
					m_dwCaptureTick = GetTickCount();
				}
				else
				{
					m_strCaptureFile.Format(_T("人脸图片保存成功，保存在：%s"),strTmp);
					m_dwCaptureTick = GetTickCount();
				}
				CmpRet.strSnap = strTmp;

				if(lpRet->src_len && strlen(lpRet->uuid))
				{
					strTmp.Format(_T("%c:\\%s\\%s\\%s.jpg"),m_cRecordDisk, GetRecordRootPath(),_T("FaceData"),CString(lpRet->uuid));
					CmpRet.strSrc = strTmp;
					Safe_WriteImageFile(strTmp,((char *)lpRet) + sizeof(DMS_FR_CMP_RET) + lpRet->snap_len,lpRet->src_len);
				}
				TRACE(_T("%s(%d) : JB_MSG_FACE_RECOGNIZE snaplen %d srclen %d score %d name %s\n"),CString(__FILE__),__LINE__,
					lpRet->snap_len,lpRet->src_len,lpRet->score,CString(lpRet->name));
				GetParent()->SendMessage(WM_VFR_CMP_SHOW,(DWORD)&CmpRet,(DWORD)pNode);
				*/
			}
		}
		break;
        //收到人脸抓拍消息
	case JB_MSG_HFC_ALARM:
		{
			/*
			CString strTmp;
			DWORD dwWrited = 0;
			 
			TCHAR m_cRecordDisk = GetFreeDisk();
			if(m_cRecordDisk == 0)
				break;
			char *lpBuffer = (char *)lpJbMsg + sizeof(JB_SERVER_MSG);
			DMS_NET_FACE_CAPTURE_RESULT_S *lpData = (DMS_NET_FACE_CAPTURE_RESULT_S *)lpBuffer;
			if(lpData->struct_size != sizeof(DMS_NET_FACE_CAPTURE_RESULT_S))
				break;

			JBNV_FACE_SNAPSHOT FaceCapture;

			FaceCapture.id	 = lpData->id;
			FaceCapture.score = lpData->score;
			FaceCapture.rect = lpData->rect;
			FaceCapture.lpfaceImage = lpBuffer + sizeof(DMS_NET_FACE_CAPTURE_RESULT_S);
			FaceCapture.faceImageLen = lpData->face_data_len;
			FaceCapture.bgImageLen = lpData->bg_data_len;
			if(FaceCapture.bgImageLen)
				FaceCapture.lpbgImage = lpBuffer + sizeof(DMS_NET_FACE_CAPTURE_RESULT_S) + lpData->face_data_len;
			

			strTmp.Format(_T("%c:\\%s\\%s\\%04d-%02d-%02d\\%s(%d)\\%02d(%02d_%02d_%02d_%03d)_Face_%d.JPG"), 
				m_cRecordDisk, GetRecordRootPath(), _T("Capture"),lpJbMsg->st.wYear,lpJbMsg->st.wMonth,lpJbMsg->st.wDay,
				CString(si.szServerIp),si.wServerPort,lpJbMsg->dwChannel + 1, 
				lpJbMsg->st.wHour,lpJbMsg->st.wMinute,lpJbMsg->st.wSecond, lpJbMsg->st.wMilliseconds,
				lpData->id);

//			TRACE(_T("%s(%d) : Snapshot Face To %s\n"),CString(__FILE__),__LINE__,strTmp);

			FaceCapture.strFaceName = strTmp;
			
			DWORD dwError = Safe_WriteImageFile(strTmp,FaceCapture.lpfaceImage,lpData->face_data_len);
			if(dwError == ERROR_ACCESS_DENIED)
			{
				m_strCaptureFile.Format(_T("人脸图片保存失败，请以管理员身份运行程序后再试"));
				m_dwCaptureTick = GetTickCount();
			}
			else
			{
				m_strCaptureFile.Format(_T("人脸图片保存成功，保存在：%s"),strTmp);
				m_dwCaptureTick = GetTickCount();
			}
 
			
			strTmp.Format(_T("%c:\\%s\\%s\\%04d-%02d-%02d\\%s(%d)\\%02d(%02d_%02d_%02d_%03d)_Snap_%d.JPG"), 
				m_cRecordDisk, GetRecordRootPath(), _T("Capture"),lpJbMsg->st.wYear,lpJbMsg->st.wMonth,lpJbMsg->st.wDay,
				CString(si.szServerIp),si.wServerPort,lpJbMsg->dwChannel + 1, 
				lpJbMsg->st.wHour,lpJbMsg->st.wMinute,lpJbMsg->st.wSecond, lpJbMsg->st.wMilliseconds,lpData->id);

			FaceCapture.strBgName = strTmp;

			if(FaceCapture.bgImageLen)
				dwError = Safe_WriteImageFile(strTmp,FaceCapture.lpbgImage,FaceCapture.bgImageLen);
			GetParent()->SendMessage(WM_VFR_SNAPSHOW,(DWORD)&FaceCapture,(DWORD)pNode);
			*/
		}
		break;
	default:
		break;
	}
	return 0;
}
 

LRESULT CJBSDKDemoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message) {
	case WM_JB_MSG:
		return DefMessageProc(wParam,lParam);
	case WM_SERVER_BREAK:
		OnButtonClosechannel();
		OnButtonCloseconnect();
		break;
	case WM_SEARCH_SERVER:
		{
			JBNV_SERVER_MSG_DATA *lpMsg = (JBNV_SERVER_MSG_DATA *)wParam;
			{
                CString strTmp;
                int nCount = m_lvServer.GetItemCount();
                for(int i = 0; i < nCount; i ++)
                {
                    if(m_lvServer.GetItemText(i,0) == CString(lpMsg->jbServerPack.szIp))
                        return 0;
                }
                int nItem = m_lvServer.InsertItem(m_lvServer.GetItemCount(),CString(lpMsg->jbServerPack.szIp));
                strTmp.Format(_T("%d"),lpMsg->jbServerPack.wMediaPort);
                m_lvServer.SetItemText(nItem,1,strTmp);
				m_lvServer.SetItemText(nItem,2,CString(lpMsg->jbServerPack.szServerName));
                strTmp.Format(_T("%d"),lpMsg->jbServerPack.wChannelCount);
                m_lvServer.SetItemText(nItem,3,strTmp);
                strTmp.Format(_T("%08X %s"),lpMsg->jbServerPack.dwDeviceType,
                    lpMsg->jbServerPack.wChannelCount != 1 ? _T("NVR") : _T("IPC"));
                m_lvServer.SetItemText(nItem,4,strTmp);
                JBNV_SERVER_PACK *lpPack = new JBNV_SERVER_PACK;
                memcpy(lpPack,&lpMsg->jbServerPack,sizeof(JBNV_SERVER_PACK));
                m_lvServer.SetItemData(nItem,(DWORD)lpPack);
                //if(m_lvServer.GetNextItem(-1, LVNI_SELECTED) == -1)
                //    m_lvServer.SetItemState(0,);
			}
		}
		break;
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CJBSDKDemoDlg::OnButtonClosechannel() 
{
	if(GetSafeHwnd() == FALSE)
		return;
	if(m_hChannel)
		JBNV_CloseChannel(m_hChannel);
	if(m_bRecording)
	{
		KillTimer(TIME_RECORD_ID);
		m_bRecording = FALSE;
		m_dwRecorded = 0;
	}
	CSliderCtrl *lpSlider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_BUFFER);
	lpSlider->SetPos(0);
	SetDlgItemInt(IDC_STATIC_MIN_BUFFER,0);
	lpSlider->EnableWindow(FALSE);
	KillTimer(TIME_CHANNEL_ID);
	m_bZoomed = FALSE;
	SetDlgItemText(IDC_STATIC_CHANNEL,_T(""));
	m_bSetSecondWnd = FALSE;
	m_hChannel = 0;

}

void CJBSDKDemoDlg::OnButtonCloseconnect() 
{
	if(GetSafeHwnd() == 0)
		return;
	if(m_hStreamPlay)
	{
		JBPlay_Release(m_hStreamPlay);
		m_hStreamPlay = 0;
	}
	if(m_hServer)
		JBNV_CloseServer(m_hServer);
	if(m_bRecording)
	{
		KillTimer(TIME_RECORD_ID);
		m_bRecording = FALSE;
		m_dwRecorded = 0;
	}
	KillTimer(TIME_CHANNEL_ID);
	m_bZoomed = FALSE;
	SetDlgItemText(IDC_STATIC_CHANNEL,_T(""));
	m_bSetSecondWnd = FALSE;
	m_hServer = 0;
}

BOOL CJBSDKDemoDlg::DestroyWindow() 
{
	if(GetSafeHwnd())
	{
        for(int i = 0; i < m_lvServer.GetItemCount(); i ++)
        {
            JBNV_SERVER_PACK  *lpPack = (JBNV_SERVER_PACK  *)m_lvServer.GetItemData(i);
            if(lpPack)
                delete lpPack;
        }
	    m_lvServer.DeleteAllItems();
		OnButtonClosechannel();
		OnButtonCloseconnect();
        if(m_hStreamPlay)
        {
            JBPlay_Release(m_hStreamPlay);
            m_hStreamPlay = 0;
	    }
	}
	return CDialog::DestroyWindow();
}
 
void CJBSDKDemoDlg::OnButtonBeginRecord() 
{
	if(m_hChannel)
	{
		DWORD dwReturn = JBNV_StartRecord(m_hChannel,"D:\\TEST.asf",0);
		if(dwReturn == 0)
		{
			m_bRecording = TRUE;
			SetTimer(TIME_RECORD_ID,1000,NULL);
		}
		ShowErrorMessage(dwReturn);
	}
}

void CJBSDKDemoDlg::OnButtonStopRecord() 
{
	if(m_hChannel)
	{
		DWORD dwReturn = JBNV_StopRecord(m_hChannel);
		if(dwReturn == 0)
			m_bRecording = FALSE;
		ShowErrorMessage(dwReturn);
	}
}

int WINAPI SearchServerCallBack_(JBNV_SERVER_MSG_DATA *lpServerMsgData,	//服务器返回的消息
											 sockaddr_in *lpRemote,DWORD dwUser)
{
    CJBSDKDemoDlg *lpDlg = (CJBSDKDemoDlg *)dwUser;
    if(lpDlg == 0)
        return 0;
    lpDlg->SendMessage(WM_SEARCH_SERVER,(DWORD)lpServerMsgData,(DWORD)lpRemote);
    return 0;
}
 
void CJBSDKDemoDlg::OnButtonSearchServer() 
{
    for(int i = 0; i < m_lvServer.GetItemCount(); i ++)
    {
        JBNV_SERVER_PACK  *lpPack = (JBNV_SERVER_PACK  *)m_lvServer.GetItemData(i);
        if(lpPack)
            delete lpPack;
    }
	m_lvServer.DeleteAllItems();
	//JBNV_SearchServer(GetSafeHwnd(),WM_SEARCH_SERVER);
    JBNV_SearchServerEx(SearchServerCallBack_,(DWORD)this);
}

DWORD WINAPI AddIPAddressToComputer(LPCSTR csIPAddress);
 

#define ERR_PARAM               0x19200000
#define ERR_CONNECT_TIMEOUT     0x19200001
#define ERR_CONNECT_FAILED      0x19200002
#define ERR_SEND_FAILED         0x19200003
#define ERR_RECV_FAILED         0x19200004
#define ERR_SET_FAILED          0x19200005
#define ERR_CREATE_FILE         0x19200006
#define ERR_FLASH_SIZE              0x1001


DWORD ConnectToServer(DWORD dwIpaddress,WORD wPort,SOCKET *lpSocket)
{
    SOCKADDR_IN sockAddr;
    SOCKET m_hServerSocket;
    WSANETWORKEVENTS netEvents;
    DWORD   dwError;
    unsigned long ul = 0;
    if(dwIpaddress == 0 || wPort == 0)
    {
        return ERR_PARAM;
    }

    memset(&sockAddr,0,sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(wPort);
	sockAddr.sin_addr.s_addr = dwIpaddress;
	HANDLE m_hRecvedEvent = WSACreateEvent();
    m_hServerSocket = socket(AF_INET,SOCK_STREAM,0);
    WSAEventSelect(m_hServerSocket,m_hRecvedEvent,FD_CONNECT | FD_CLOSE);
    INT nRet = connect(m_hServerSocket, (sockaddr *)&sockAddr,sizeof(sockAddr));
    DWORD dwWait = WSAWaitForMultipleEvents(1,&m_hRecvedEvent,FALSE,10000,FALSE);
    if(dwWait == WSA_WAIT_TIMEOUT)
    {
        dwError = ERR_CONNECT_TIMEOUT;
        goto FAILED;
    }
    else if(dwWait == WAIT_OBJECT_0)
    {
        memset(&netEvents,0,sizeof(netEvents));
        nRet = WSAEnumNetworkEvents(m_hServerSocket,m_hRecvedEvent,&netEvents);
        if(nRet == SOCKET_ERROR)
        {
            dwError = ERR_CONNECT_FAILED;
            goto FAILED;
        }
        else if((netEvents.lNetworkEvents & FD_CONNECT) && netEvents.iErrorCode[FD_CONNECT_BIT])
        {
            dwError = ERR_CONNECT_FAILED;
            goto FAILED;
        }
    }
    else
    {
        TRACE(_T("dwWait = %d\n"),dwWait);
    }
    WSAEventSelect(m_hServerSocket,m_hRecvedEvent,0);
    
	ioctlsocket(m_hServerSocket,FIONBIO,&ul);
    *lpSocket = m_hServerSocket;
    return 0;
FAILED:
    WSAEventSelect(m_hServerSocket,m_hRecvedEvent,0);
    closesocket(m_hServerSocket);
    CloseHandle(m_hRecvedEvent);
    return dwError;
}
 

void ShowErrorInfo(DWORD dwError)
{
    CString strInfo;
    switch (dwError)
    {
    case ERR_PARAM:
        strInfo = _T("参数错");break;
    case ERR_CONNECT_TIMEOUT:
        strInfo = _T("连接超时");break;
    case ERR_CONNECT_FAILED:
        strInfo = _T("连接失败");break;
    case ERR_SEND_FAILED:
        strInfo = _T("发送失败");break;
    case ERR_RECV_FAILED:
        strInfo = _T("接收失败");break;
    case ERR_SET_FAILED:
        strInfo = _T("设置出错");break;
    case ERR_CREATE_FILE:
        strInfo = _T("创建文件出错");break;
    case ERR_FLASH_SIZE:
        strInfo = _T("FLASH大小不正确");break;
    default:
        break;
    }
 
    {
        AfxMessageBox(strInfo,MB_ICONERROR);
    }
}

#pragma comment(lib,"Ws2_32.lib")


typedef struct tagDMS_NET_OTA_UPGRADE_RESP
{
    int download_len;
    int upgrade_len;
}DMS_NET_OTA_UPGRADE_RESP;

#define DMS_NET_CMD_OTA_UPGRADE_REQ             0xA01000F1
#define DMS_ERR_UPGRADE_LATEST_VERSION          0x1B000014 //当前已是最新版本
#define DMS_ERR_UPGRADE_FIND_VERSION      		0x1B000015 //发现新版本软件

void CJBSDKDemoDlg::OnButtonTest() 
{
//    DMS_NET_OTA_UPGRADE_RESP Resp;
//    memset(&Resp,0,sizeof(Resp));
//    DWORD dwReturn = JBNV_GetServerConfig(m_hServer, DMS_NET_CMD_OTA_UPGRADE_REQ, &Resp,sizeof(Resp));
//    TRACE(_T("dwReturn = %08X upgrade_len %d download_len %d\n"),dwReturn,Resp.upgrade_len,Resp.download_len);
//    if(dwReturn == DMS_ERR_UPGRADE_LATEST_VERSION)
//        AfxMessageBox(_T("设备已经是最新版本"));
//    else if(dwReturn == 0)
//        AfxMessageBox(_T("发现新版本软件"));
//    else if(dwReturn)
//         AfxMessageBox(_T("不支持的指令"));
    DMS_VOICE_PACKET_HEADER *lpBuffer = 0;
	CFile file;
	//if(file.Open(_T("D:\\Temp\\fr1"),CFile::modeRead,0) == FALSE)
	if(file.Open(_T("D:\\Log\\fr3.pcm"),CFile::modeRead,0) == FALSE)
	{
		AfxMessageBox(_T("打开文件失败"));
		return;
	}
	DWORD dwFileSize = file.GetLength();
	lpBuffer = (DMS_VOICE_PACKET_HEADER *)new BYTE[dwFileSize + sizeof(DMS_VOICE_PACKET_HEADER)];
	lpBuffer->dwSize = sizeof(DMS_VOICE_PACKET_HEADER);
	lpBuffer->dwFormatTag = 19;
	lpBuffer->dwVoiceSize = dwFileSize;
	lpBuffer->dwReserved = 0;
	file.Read((char *)lpBuffer + sizeof(DMS_VOICE_PACKET_HEADER), dwFileSize);
	file.Close();
	DWORD dwReturn = JBNV_GetServerConfig(m_hServer, CMD_PLAY_VOICE_ONLINE, lpBuffer,sizeof(DMS_VOICE_PACKET_HEADER) + dwFileSize);
	if(dwReturn)
	{
		ShowErrorMessage(dwReturn);
	}
	delete lpBuffer;
}

void CJBSDKDemoDlg::OnButtonPtzUp() 
{
	if(m_hServer)
		JBNV_PTZControlEx(m_hServer,0,PTZ_CMD_UP,0,0);
}

void CJBSDKDemoDlg::OnButtonPtzStop() 
{
	if(m_hServer)
		JBNV_PTZControlEx(m_hServer,0,PTZ_CMD_STOP,0,0);
}

void CJBSDKDemoDlg::OnButtonLeft() 
{
	if(m_hServer)
		JBNV_PTZControlEx(m_hServer,0,PTZ_CMD_LEFT,0,0);
}

void CJBSDKDemoDlg::OnButtonPtzRight() 
{
	if(m_hServer)
		JBNV_PTZControlEx(m_hServer,0,PTZ_CMD_RIGHT,0,0);
}

void CJBSDKDemoDlg::OnButtonPtzDown() 
{
	if(m_hServer)
		JBNV_PTZControlEx(m_hServer,0,PTZ_CMD_DOWN,0,0);
}

void CJBSDKDemoDlg::OnButtonFocusFar() 
{
	if(m_hServer)
		JBNV_PTZControl(m_hServer,0,PTZ_CMD_FOCUS_SUB,0);
}

void CJBSDKDemoDlg::OnButtonFocusNear() 
{
	if(m_hServer)
		JBNV_PTZControl(m_hServer,0,PTZ_CMD_FOCUS_ADD,0);
}

void CJBSDKDemoDlg::OnButtonCall() 
{
	if(m_hServer)
		JBNV_PTZControl(m_hServer,0,PTZ_CMD_CALL,GetDlgItemInt(IDC_EDIT_CALL));
}

 

double dbframerate = 0;

void CJBSDKDemoDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIME_RECORD_ID)
	{
		if(m_hChannel)
			JBNV_GetRecorded(m_hChannel,&m_dwRecorded);
	}
	if(nIDEvent == TIME_CHANNEL_ID)
	{
		if(m_hServer)
		{
			//检查网络状态，如果断线，则进行相应处理
			JBNV_NETWORK_STATUS NetStatus;
			memset(&NetStatus,0,sizeof(NetStatus));
			JBNV_GetServerNetStatus(m_hServer,&NetStatus);
			if(NetStatus.dwServerStatus == NetStatus_Break)
				TRACE(_T("Server Is Break\n"));
			else 
			{
				for(int i = 0 ; i < 64; i ++)
				{
					if(NetStatus.dwChannelStatus[i][0] == NetStatus_Break)
					{
						TRACE(_T("Channel Is Break\n"));
					}
				}
			}
		}
		if(m_hChannel)
		{
			CString strTmp;
			DWORD m_dwRecved = 0;
			JBNV_GetRecvCount(m_hChannel,&m_dwRecved);
			strTmp.Format(_T("Recved: %u Rate:%0.02f %0.02f Kbps"),m_dwRecved,m_dbaverageframe,
				dbframerate);
			SetDlgItemText(IDC_STATIC_CHANNEL,strTmp);
		}
	}
	if(TIME_CHANNEL_FRAME == nIDEvent)
	{
		double dbframe = m_dwFrameCount - m_dwOldFrameCount;
		m_dbaverageframe = dbframe;
		m_dwOldFrameCount = m_dwFrameCount;
		if(m_hChannel)
		{
			DWORD m_dwRecved = 0;
			JBNV_GetRecvCount(m_hChannel,&m_dwRecved);
			dbframerate = (m_dwRecved - m_dwOldRecved) / 1000;
			dbframerate *= 8;
			m_dwOldRecved = m_dwRecved;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CJBSDKDemoDlg::OnButtonSecondWnd() 
{
	HWND hSecondWnd = GetDlgItem(IDC_STATIC_SECOND_IMAGE)->GetSafeHwnd();
	if(m_hServer && m_hChannel)
	{
		if(m_bSetSecondWnd == FALSE)
			JBNV_SetSecondSurface(m_hServer,0,hSecondWnd,NULL,NULL,0);
		else
			JBNV_SetSecondSurface(m_hServer,0,0,NULL,NULL,0);
		m_bSetSecondWnd = !m_bSetSecondWnd;
	}
}

void CJBSDKDemoDlg::OnButtonZoom() 
{
	if(m_hChannel)
	{
		CRect rc;
		JBNV_CHANNEL_INFO jbci;
		jbci.dwSize = sizeof(jbci);
		JBNV_GetChannelInfo(m_hServer,0,&jbci);
		if(m_bZoomed)
			rc.SetRect(0,0,jbci.dwStream1Width,jbci.dwStream1Height);
		else
			rc.SetRect(0,0,jbci.dwStream1Width / 2,jbci.dwStream1Height / 2);
		JBNV_SetDisplayRect(m_hChannel,&rc);
		m_bZoomed = !m_bZoomed;
	}
}

void CJBSDKDemoDlg::OnButtonRemoteSnapshot() 
{
	if(m_hServer)
	{
		DWORD dwChannel = 0;
		JBNV_SetServerConfig(m_hServer,CMD_SNAPSHOT,&dwChannel,sizeof(int));
	}
}

void CJBSDKDemoDlg::OnButtonLocalSnapshot() 
{
	if(m_hChannel)
	{
		DWORD dwSize = 0;
		DWORD dwError = JBNV_CaptureBitmap(m_hChannel,NULL,&dwSize);
		if(dwSize == 0)
			return ;
		BYTE *lpByte = new BYTE[dwSize];
		if(lpByte == 0)
			return ;
		dwError = JBNV_CaptureBitmap(m_hChannel,lpByte,&dwSize);
		JBNV_SERVER_INFO si;
		si.dwSize = sizeof(si);
		JBNV_GetServerInfo(m_hServer,&si);
		if(dwError == 0)
		{
			DWORD dwWrited = 0;
			SYSTEMTIME st;
			//本客户端检索路径:NVFile\年-月-日\LastImage\IP(端口)\P_01
			CString	csTmp;
			CString csBuf;
			GetLocalTime(&st);
			SYSTEMTIME *pst = &st;
			csBuf = "D:\\Snapshot";
			CreateDirectory(csBuf,NULL);
			csTmp.Format(_T("\\%04d-%02d-%02d"),pst->wYear,pst->wMonth,pst->wDay);
			csBuf += csTmp;
			CreateDirectory(csBuf, NULL) ;
			csTmp.Format(_T("\\%s(%u)"),CString(si.szServerIp),si.wServerPort);
			csBuf += csTmp;
			CreateDirectory(csBuf, NULL) ;
			csTmp = "\\P_01";
			csBuf += csTmp;
			CreateDirectory(csBuf, NULL) ;
			csTmp.Format(_T("\\%02d_%02d_%02d.BMP"),pst->wHour,pst->wMinute,pst->wSecond);
			csBuf += csTmp;
			HANDLE hFile = CreateFile(csBuf,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				delete lpByte;
				return ;
			}
			WriteFile(hFile,lpByte,dwSize,&dwWrited,0);
			CloseHandle(hFile);
		}
		delete lpByte;
	}
}

void CJBSDKDemoDlg::OnCheckSensorOut1() 
{
	if(m_hServer == 0)
		return;
	DWORD dwSensorOutID = 0;
	JBNV_SENSOR_STATE st;
	st.dwSize = sizeof(st);
	st.dwSensorID = 1 << dwSensorOutID;
	st.dwSensorOut = IsDlgButtonChecked(IDC_CHECK_SENSOR_OUT1) << dwSensorOutID;
	DWORD dwError = JBNV_SetServerConfig(m_hServer,CMD_SET_SENSOR_STATE,&st,sizeof(st));	
}

void CJBSDKDemoDlg::OnCheckSensorOut2() 
{
	if(m_hServer == 0)
		return;
	DWORD dwSensorOutID = 1;
	JBNV_SENSOR_STATE st;
	st.dwSize = sizeof(st);
	st.dwSensorID = 1 << dwSensorOutID;
	st.dwSensorOut = IsDlgButtonChecked(IDC_CHECK_SENSOR_OUT2) << dwSensorOutID;
	DWORD dwError = JBNV_SetServerConfig(m_hServer,CMD_SET_SENSOR_STATE,&st,sizeof(st));	
}

BOOL bSwitch = FALSE;

void CJBSDKDemoDlg::OnButtonSwitch() 
{
	if(m_hChannel)	
	{
		if(bSwitch)
			JBNV_SetDisplayhWnd(m_hChannel,GetDlgItem(IDC_STATIC_IMAGE)->GetSafeHwnd());
		else
			JBNV_SetDisplayhWnd(m_hChannel,GetDlgItem(IDC_STATIC_THREE_IMAGE)->GetSafeHwnd());
		bSwitch = !bSwitch;
	}
}

void CJBSDKDemoDlg::OnReleasedcaptureSliderBuffer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_hChannel)
	{
		CSliderCtrl *lpSlider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_BUFFER);
		JBNV_SetStreamBufferSize(m_hChannel,lpSlider->GetPos(),200);
		SetDlgItemInt(IDC_STATIC_MIN_BUFFER,lpSlider->GetPos());
	}
	*pResult = 0;
}

void CJBSDKDemoDlg::OnButtonGetServerState() 
{
	DWORD dwReturn = 0;
	if(m_hServer)
	{
		char csBuf[1024];
		dwReturn = JBNV_GetServerConfig(m_hServer,CMD_GET_CENTER_LICENCE,csBuf,1024);
		JB_SERVER_STATE	jbst;
		jbst.dwSize = sizeof(JB_SERVER_STATE);
		dwReturn = JBNV_GetServerConfig(m_hServer,CMD_GET_SERVER_STATUS,&jbst,sizeof(JB_SERVER_STATE));
		if(dwReturn == 0)
		{
			CString strTmp;
			strTmp.Format(_T("服务器通道状态 %08X 告警输入 %08X 告警输出 %08X 连接数 %d"),
				jbst.dwVideoState,jbst.dwAlarmInState,jbst.dwAlarmOutState,jbst.dwLinkNum);
			AfxMessageBox(strTmp);
		}
	}
	
}
 

void CJBSDKDemoDlg::OnButtonAuto() 
{
	static BOOL bAutoStart = FALSE;
	if(m_hServer == 0)
		return;
	JBNV_PTZControl(m_hServer,0,bAutoStart ? PTZ_CMD_AUTO_STOP : PTZ_CMD_AUTO_STRAT,0);
	bAutoStart = !bAutoStart;
}
 
#include "DialogOcxTest.h"

void CJBSDKDemoDlg::OnButtonOcxTest() 
{
    int nItem = m_lvServer.GetNextItem(-1, LVNI_SELECTED);
#ifndef _DEBUG
    if(nItem == -1)
        return;
#endif
	CDialogOcxTest dlg; 
    if(nItem != -1)
    {
        dlg.m_strServerIp = m_lvServer.GetItemText(nItem,0);
        dlg.m_nServerPort = _ttoi(m_lvServer.GetItemText(nItem,1));
    }
    dlg.DoModal();
}

#include "DialogPlayer.h"
//File Player Demo
void CJBSDKDemoDlg::OnButtonFilePlayer() 
{
	CDialogPlayer dlg;
    dlg.DoModal();
}

#include "DialogTalkback.h"

void CJBSDKDemoDlg::OnButtonTalkback() 
{
	CDialogTalkback dlg;
    dlg.DoModal();
}

#include "DialogPlayerRemote.h"

void CJBSDKDemoDlg::OnButtonRemotePlayer() 
{
    if(m_hServer == 0)
    {
        return;
    }
	CDialogPlayerRemote dlg(m_hServer);
    dlg.DoModal();
    JBNV_SetMessage(m_hServer,GetSafeHwnd(),WM_JB_MSG);
}

 

 
int static CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    int nRetVal = 0;
    JBNV_SERVER_PACK *pData1 = (JBNV_SERVER_PACK *)lParam1;
	JBNV_SERVER_PACK *pData2 = (JBNV_SERVER_PACK *)lParam2;
    switch(lParamSort)
    {
    case 0: //ip
        nRetVal = strcmp(pData1->szIp,pData2->szIp);
        break;
    case 1:	//PORT
        nRetVal = pData1->wMediaPort < pData2->wMediaPort;
        break;
    case 2: //NAME
        nRetVal = strcmp(pData1->szServerName,pData2->szServerName);
        break;
    case 3: //CHANNELCOUNT
        nRetVal = pData1->wChannelCount < pData2->wChannelCount;
        break;
    case 4: //TYPE
        nRetVal = pData1->dwDeviceType < pData2->dwDeviceType;
        break;
    }
    return nRetVal;
}


void CJBSDKDemoDlg::OnColumnclickListServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    
	m_lvServer.SortItems(MyCompareProc,pNMListView->iSubItem);
	
	*pResult = 0;
}
 

typedef struct tagDMS_NET_P2P_CFG
{
    DWORD dwSize;
    DWORD dwEnable;
    char  csID[64];
    char  csRes[64];
}DMS_NET_P2P_CFG;
 

#include "DialogAudio.h"

void CJBSDKDemoDlg::OnButtonAVol() 
{
	if(m_hServer == 0)
        return;
    CDialogAudio dlg(m_hServer);
    dlg.DoModal();
}

#include "DialogFaceManager.h"

void CJBSDKDemoDlg::OnButtonFaceLib() 
{	
    JBNV_SERVER_INFO si;
    memset(&si,0,sizeof(si));
    si.dwSize = sizeof(si);
    if(m_hServer == 0)
		return;
    JBNV_GetServerInfo(m_hServer,&si);
    if(si.dwServerCPUType != 0x3516A200 && si.dwServerCPUType != 0x3516C500 &&
        si.dwServerCPUType != 0x3616D300)
		return;
	CDialogFaceManager dlg(m_hServer);
	dlg.DoModal();
}

void CJBSDKDemoDlg::OnButtonListen() 
{
	CDialogBackConnect dlg;
    dlg.DoModal();
}
