#if !defined(AFX_JBSDKDEMODLG_H__D9A21E31_EA53_45D8_BA64_A27393557566__INCLUDED_)
#define AFX_JBSDKDEMODLG_H__D9A21E31_EA53_45D8_BA64_A27393557566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJBSDKDemoDlg dialog

class CJBSDKDemoDlg : public CDialog
{
// Construction
public:
	long DefMessageProc(long wParam, long lParam);
	CJBSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL   m_bRecording;
	DWORD  m_dwRecorded;
	BOOL   m_bSetSecondWnd;
	BOOL   m_bZoomed;
// Dialog Data
	//{{AFX_DATA(CJBSDKDemoDlg)
	enum { IDD = IDD_JBSDKDEMO_DIALOG };
	CListCtrl	m_lvServer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJBSDKDemoDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_dwFrameCount;
	DWORD m_dwBeginTime;
	DWORD m_dwOldFrameCount;
	DWORD m_dwOldRecved;
	double m_dbaverageframe;
	HANDLE m_hStreamPlay;	//OpenStream
protected:
	HICON m_hIcon;
	HANDLE m_hServer;
	HANDLE m_hChannel;
	HANDLE m_hTMServer;
	// Generated message map functions
	//{{AFX_MSG(CJBSDKDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonOpenchannel();
	afx_msg void OnButtonCloseconnect();
	afx_msg void OnButtonBeginRecord();
	afx_msg void OnButtonStopRecord();
	afx_msg void OnButtonCloseChannel();
	afx_msg void OnButtonTest();
	afx_msg void OnButtonSearchServer();
	afx_msg void OnButtonPtzUp();
	afx_msg void OnButtonPtzStop();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonPtzRight();
	afx_msg void OnButtonPtzDown();
	afx_msg void OnButtonFocusFar();
	afx_msg void OnButtonFocusNear();
	afx_msg void OnButtonCall();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonSecondWnd();
	afx_msg void OnButtonZoom();
	afx_msg void OnButtonRemoteSnapshot();
	afx_msg void OnButtonLocalSnapshot();
	afx_msg void OnCheckSensorOut1();
	afx_msg void OnCheckSensorOut2();
	afx_msg void OnButtonSwitch();
	afx_msg void OnReleasedcaptureSliderBuffer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonGetServerState();
	afx_msg void OnButtonCreateTmServer();
	afx_msg void OnButtonAuto();
	afx_msg void OnButtonClosechannel();
	afx_msg void OnButtonOcxTest();
	afx_msg void OnButtonFilePlayer();
	afx_msg void OnButtonTalkback();
	afx_msg void OnButtonRemotePlayer();
	afx_msg void OnColumnclickListServer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAVol();
	afx_msg void OnButtonFaceLib();
	afx_msg void OnButtonListen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JBSDKDEMODLG_H__D9A21E31_EA53_45D8_BA64_A27393557566__INCLUDED_)
