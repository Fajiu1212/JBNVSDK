#if !defined(AFX_DIALOGFACEMANAGER_H__85DAE245_A39E_4B2D_A8A0_708BB59D472F__INCLUDED_)
#define AFX_DIALOGFACEMANAGER_H__85DAE245_A39E_4B2D_A8A0_708BB59D472F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFaceManager.h : header file
//
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CDialogFaceManager dialog
 
class CDialogFaceManager : public CDialog
{
// Construction
public:
	CDialogFaceManager(HANDLE hServer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogFaceManager)
	enum { IDD = IDD_DIALOG_FACE_MANAGE };
	CListCtrl	m_lvFace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFaceManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HANDLE m_hServer;
    int QueryServerFace(std::vector<DMS_FR_SAMPLE_QUERY_RES_S> *lpFaceInfo);
    void DoIPCDownload(SYSTEMTIME *stStart,SYSTEMTIME *stEnd);
    void DoNVRDownload(SYSTEMTIME *stStart,SYSTEMTIME *stEnd);
	// Generated message map functions
	//{{AFX_MSG(CDialogFaceManager)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRemoteSelect();
	afx_msg void OnButtonDeleteAll();
	afx_msg void OnButtonBatchIncrease();
	afx_msg void OnButtonFaceExport();
	afx_msg void OnButtonFaceImport();
	afx_msg void OnPaint();
	afx_msg void OnButtonSerach();
	afx_msg void OnButtonDownloadRec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFACEMANAGER_H__85DAE245_A39E_4B2D_A8A0_708BB59D472F__INCLUDED_)
