#if !defined(AFX_DIALOGLOGON_H__F33D9E98_CC3A_4D35_B0E6_4E3469F97CA2__INCLUDED_)
#define AFX_DIALOGLOGON_H__F33D9E98_CC3A_4D35_B0E6_4E3469F97CA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogLogon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogLogon dialog

class CDialogLogon : public CDialog
{
// Construction
public:
	CDialogLogon(CString strServerIp,WORD wServerPort,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogLogon)
	enum { IDD = IDD_DIALOG_LOGON };
	CString	m_strPassword;
	int		m_nPort;
	CString	m_strServer;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogLogon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogLogon)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGLOGON_H__F33D9E98_CC3A_4D35_B0E6_4E3469F97CA2__INCLUDED_)
