#if !defined(AFX_DIALOGFACEMODIFY_H__0108BBB9_21A3_409F_96DA_8E276921F540__INCLUDED_)
#define AFX_DIALOGFACEMODIFY_H__0108BBB9_21A3_409F_96DA_8E276921F540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFaceModify.h : header file
//
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogFaceModify dialog

class CDialogFaceModify : public CDialog
{
// Construction
public:
	CDialogFaceModify(CWnd* pParent = NULL);   // standard constructor
	DMS_FR_SAMPLE_S *GetFaceInfo(DWORD *lpSize);
// Dialog Data
	//{{AFX_DATA(CDialogFaceModify)
	enum { IDD = IDD_DIALOG_FACE_MODITY };
	CString	m_strName;
	int		m_nAge;
	CString	m_strID;
	CString	m_strOther;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFaceModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	DWORD m_dwBufSize;
    void LoadInputImage(CString strImage);
	DMS_FR_SAMPLE_S *m_lpFace;

    CRect m_picFacerc;
    CRect m_SmallFacerc;

    CPicture		m_pic;
    CPicture		m_pic2;

    CString         m_strSmallPic;
    CString         m_strPicture;

	// Generated message map functions
	//{{AFX_MSG(CDialogFaceModify)
	afx_msg void OnButtonSelectPic();
	afx_msg void OnPaint();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFACEMODIFY_H__0108BBB9_21A3_409F_96DA_8E276921F540__INCLUDED_)
