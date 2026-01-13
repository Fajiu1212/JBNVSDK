#if !defined(AFX_DIALOGAUDIO_H__040BB758_25AC_466D_B143_487CDA456AD3__INCLUDED_)
#define AFX_DIALOGAUDIO_H__040BB758_25AC_466D_B143_487CDA456AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAudio.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAudio dialog

class CDialogAudio : public CDialog
{
// Construction
public:
	CDialogAudio(HANDLE hServer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAudio)
	enum { IDD = IDD_DIALOG_AUDIO };
	CSliderCtrl	m_cSliderGAIN;
	CSliderCtrl	m_cSliderDAC;
	CSliderCtrl	m_cSliderADC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAudio)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    HANDLE m_hServer;
	// Generated message map functions
	//{{AFX_MSG(CDialogAudio)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGAUDIO_H__040BB758_25AC_466D_B143_487CDA456AD3__INCLUDED_)
