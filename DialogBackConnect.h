#if !defined(AFX_DIALOGBACKCONNECT_H__5B1F337D_A796_42D2_B461_404E9B1EEEC8__INCLUDED_)
#define AFX_DIALOGBACKCONNECT_H__5B1F337D_A796_42D2_B461_404E9B1EEEC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogBackConnect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogBackConnect dialog

class CDialogBackConnect : public CDialog
{
// Construction
public:
	CDialogBackConnect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogBackConnect)
	enum { IDD = IDD_DIALOG_BACK_CONNECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBackConnect)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
    HANDLE m_hServer;
    BOOL   m_bStartBackConnect;
	// Generated message map functions
	//{{AFX_MSG(CDialogBackConnect)
	afx_msg void OnButtonStart();
	afx_msg void OnButtonOpenBackConnect();
	afx_msg void OnButtonEnd();
	afx_msg void OnButtonOpenChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBACKCONNECT_H__5B1F337D_A796_42D2_B461_404E9B1EEEC8__INCLUDED_)
