#if !defined(AFX_DIALOGPLAYER_H__2FFCBC8F_8397_4FA2_A7BB_60DF8B822F34__INCLUDED_)
#define AFX_DIALOGPLAYER_H__2FFCBC8F_8397_4FA2_A7BB_60DF8B822F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPlayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayer dialog

class CDialogPlayer : public CDialog
{
// Construction
public:
	CDialogPlayer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogPlayer)
	enum { IDD = IDD_DIALOG_PLAYER_FILE };
	CSliderCtrl	m_Slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPlayer)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
    HANDLE m_hPlay;
    DWORD  m_dwCountTime;
	// Generated message map functions
	//{{AFX_MSG(CDialogPlayer)
	afx_msg void OnButtonOpenfile();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonStepIn();
	afx_msg void OnButtonStepOut();
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonPlayfast();
	afx_msg void OnButtonFastback();
	afx_msg void OnButtonRelease();
	afx_msg void OnReleasedcaptureSliderPlaypos(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPLAYER_H__2FFCBC8F_8397_4FA2_A7BB_60DF8B822F34__INCLUDED_)
