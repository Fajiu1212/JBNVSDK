// Picture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


#include <afxpriv2.h>

////////////////////////////////////////////////////////////////
// CPicture implementation
//

CPicture::CPicture()
{
}

CPicture::~CPicture()
{
}

//////////////////
// Load from resource. Looks for "IMAGE" type.
//
BOOL CPicture::Load(UINT nIDRes)
{
	// find resource in resource file
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,
		MAKEINTRESOURCE(nIDRes),
		_T("IMAGE")); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// create memory file and load it
	CMemFile file(lpRsrc, len);
	BOOL bRet = Load(file);
	FreeResource(hRsrc);

	return bRet;
}

//////////////////
// Load from path name.
//
BOOL CPicture::Load(LPCTSTR pszPathName)
{
	CFile file;
	if (!file.Open(pszPathName, CFile::modeRead|CFile::typeBinary))
		return FALSE;
	BOOL bRet = Load(file);
	if(bRet == FALSE)
		TRACE(_T("Load Image %s Failed\n"),pszPathName);
	file.Close();
	return bRet;
}

//////////////////
// Load from CFile
//
BOOL CPicture::Load(CFile& file)
{
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	return Load(ar);
}

//////////////////
// Load from archive--create stream and load from stream.
//
BOOL CPicture::Load(CArchive& ar)
{
	CArchiveStream arcstream(&ar);
	return Load((IStream*)&arcstream);
}

//////////////////
// Load from stream (IStream). This is the one that really does it: call
// OleLoadPicture to do the work.
//
BOOL CPicture::Load(IStream* pstm)
{
	Free();
	HRESULT hr = OleLoadPicture(pstm, 0, FALSE,
		IID_IPicture, (void**)&m_spIPicture);
	if(hr)
		return FALSE;		//0x800A01E1 ÎÞÐ§Í¼Æ¬	
	return TRUE;
}

//////////////////
// Render to device context. Covert to HIMETRIC for IPicture.
// Image's original size is srcWidth and srcHeight(hmWidth, hmHeight)
// Image's dest rect is rcImage
// Windows's absolute rect is rcWindow
BOOL CPicture::Render(CDC* pDC, float fZoom, CRect srcRC, CRect &destRC, CRect windowRC, LPCRECT prcMFBounds) const
{
	ASSERT(pDC);
	if(m_spIPicture == NULL ) return FALSE;
	
	int delta_left, delta_top, delta_right, delta_bottom;
//	long hmWidth,hmHeight; // HIMETRIC units
//	GetHIMETRICSize(hmWidth, hmHeight); // get picture metric width and height
	int srcWidth, srcHeight;
	srcWidth = srcRC.right-srcRC.left;
	srcHeight = srcRC.bottom-srcRC.top;

	if ( destRC.left>=windowRC.left ) {
		delta_left = 0;
	}
	else {
		delta_left = windowRC.left-destRC.left;
	}
	if ( destRC.top>=windowRC.top ) {
		delta_top = 0;
	}
	else {
		delta_top = windowRC.top-destRC.top;
	}
	if ( destRC.right<=windowRC.right ) {
		delta_right = 0;
	}
	else {
		delta_right = destRC.right-windowRC.right;
	}
	if ( destRC.bottom<=windowRC.bottom ) {
		delta_bottom = 0;
	}
	else {
		delta_bottom = destRC.bottom-windowRC.bottom;
	}
	
	destRC.left += delta_left;
	destRC.top += delta_top;
	destRC.right -= delta_right;
	destRC.bottom -= delta_bottom;
	srcRC.left += (int)(delta_left*fZoom);
	srcRC.top += (int)(delta_top*fZoom);
	srcRC.right -= (int)(delta_right*fZoom);
	srcRC.bottom -= (int)(delta_bottom*fZoom);
	CSize point(srcRC.left, srcHeight - srcRC.top);
	CSize size(srcRC.right-srcRC.left, srcRC.bottom-srcRC.top);
	pDC->DPtoHIMETRIC(&size);
	pDC->DPtoHIMETRIC(&point);
#if 0
	TRACE(_T("Render destRC %d %d %d %d point %d %d size %d %d %p\n"),destRC.left, destRC.top, 
		destRC.right-destRC.left, destRC.bottom-destRC.top,
		point.cx, point.cy, size.cx, -size.cy, prcMFBounds);
#endif
	m_spIPicture->Render(*pDC, destRC.left, destRC.top, 
		destRC.right-destRC.left, destRC.bottom-destRC.top,
		point.cx, point.cy, size.cx, -size.cy, prcMFBounds);

	return TRUE;
}

//////////////////
// Get image size in pixels. Converts from HIMETRIC to device coords.
//
BOOL CPicture::GetImageSize(CRect &rc,CDC* pDC) const
{
	if (!m_spIPicture)
		return FALSE;
	
	LONG hmWidth, hmHeight; // HIMETRIC units
	m_spIPicture->get_Width(&hmWidth);
	m_spIPicture->get_Height(&hmHeight);
	CSize sz(hmWidth,hmHeight);
	if (pDC==NULL) {
		CWindowDC dc(NULL);
		dc.HIMETRICtoDP(&sz); // convert to pixels
	} else {
		pDC->HIMETRICtoDP(&sz);
	}
	rc.left = 0;
	rc.top = 0;
	rc.right = sz.cx;
	rc.bottom = sz.cy;
	return TRUE;
}
LONG CPicture::WriteStreamToFile(CFile &file)
{
	if(m_spIPicture == NULL ) return 0;
	LONG nBytesWrite;
	CArchive arstore(&file, CArchive::store | CArchive::bNoFlushOnDelete);
	CArchiveStream arcstream(&arstore);
	HRESULT  hRet = m_spIPicture->SaveAsFile((IStream*)&arcstream, FALSE,&nBytesWrite);
	return (hRet == S_OK)?nBytesWrite:0;
}





