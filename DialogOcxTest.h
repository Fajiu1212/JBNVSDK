//{{AFX_INCLUDES()
#include "jbnvocx.h"
//}}AFX_INCLUDES
#if !defined(AFX_DIALOGOCXTEST_H__8A2B41B4_7E2F_4801_9673_7FA9BB245D10__INCLUDED_)
#define AFX_DIALOGOCXTEST_H__8A2B41B4_7E2F_4801_9673_7FA9BB245D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOcxTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogOcxTest dialog

class CDialogOcxTest : public CDialog
{
// Construction
public:
	CDialogOcxTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOcxTest)
	enum { IDD = IDD_DIALOG_OCX_TEST };
	CJBNVOCX	m_jbnvocx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOcxTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
    CString m_strServerIp;
    WORD    m_nServerPort;
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogOcxTest)
	afx_msg void OnButtonOpenserver();
	afx_msg void OnButtonSetup();
	afx_msg void OnButtonOcxChannel();
	afx_msg void OnButtonSnapshot();
	afx_msg void OnButtonShowPlaypage();
	afx_msg void OnButtonCloseChannel();
	afx_msg void OnButtonCloseServer();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonChn9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOCXTEST_H__8A2B41B4_7E2F_4801_9673_7FA9BB245D10__INCLUDED_)
