#if !defined(AFX_DIALOGPLAYERREMOTE_H__E8B082BC_0645_46B7_B82A_ACA230982295__INCLUDED_)
#define AFX_DIALOGPLAYERREMOTE_H__E8B082BC_0645_46B7_B82A_ACA230982295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPlayerRemote.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogPlayerRemote dialog

class CDialogPlayerRemote : public CDialog
{
// Construction
public:
	CDialogPlayerRemote(HANDLE hServer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogPlayerRemote)
	enum { IDD = IDD_DIALOG_PLAYER_REMOTE };
	CTime	m_tDateBegin;
	CTime	m_tTimeBegin;
	CTime	m_tDateEnd;
	CTime	m_tTimeEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPlayerRemote)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
    HANDLE m_hPlayer;
    HANDLE m_hServer;
	// Generated message map functions
	//{{AFX_MSG(CDialogPlayerRemote)
	afx_msg void OnButtonFilePlay();
	afx_msg void OnButtonRemotePlayByTime();
	afx_msg void OnButtonSearch();
    virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPLAYERREMOTE_H__E8B082BC_0645_46B7_B82A_ACA230982295__INCLUDED_)
