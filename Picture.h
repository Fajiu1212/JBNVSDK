// Picture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__8B8F6120_24C7_45D0_9430_888CDF231B12__INCLUDED_)
#define AFX_PICTURE_H__8B8F6120_24C7_45D0_9430_888CDF231B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>

class CPicture {
public:
	LONG WriteStreamToFile(CFile &file);
	CPicture();
	~CPicture();
	BOOL IsLoad()	{ return m_spIPicture ? TRUE : FALSE;};
	// Load frm various sosurces
    BOOL Load(UINT nIDRes);
    BOOL Load(LPCTSTR pszPathName);
    BOOL Load(CFile& file);
    BOOL Load(CArchive& ar);
    BOOL Load(IStream* pstm);
    
    // render to device context
    BOOL Render(CDC* pDC, float fZoom, CRect srcRC, CRect &destRC, CRect windowRC,  
        LPCRECT prcMFBounds=NULL) const;
    
    BOOL GetImageSize(CRect &size,CDC* pDC=NULL) const;
    
    operator IPicture*() {
        return m_spIPicture;
    }
    
    void GetHIMETRICSize(OLE_XSIZE_HIMETRIC& cx, OLE_YSIZE_HIMETRIC& cy) const {
        cx = cy = 0;
        HRESULT m_hr = m_spIPicture->get_Width(&cx);
        ASSERT(SUCCEEDED(m_hr));
        m_hr = m_spIPicture->get_Height(&cy);
        ASSERT(SUCCEEDED(m_hr));
    }
    
    void Free() {
        if (m_spIPicture) {
            m_spIPicture.Release();
        }
    }
    
protected:
    CComQIPtr<IPicture>m_spIPicture;		 // ATL smart pointer to IPicture
    // last error code
};

#endif // !defined(AFX_PICTURE_H__8B8F6120_24C7_45D0_9430_888CDF231B12__INCLUDED_)
