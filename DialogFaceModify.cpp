// DialogFaceModify.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogFaceModify.h"
#include "include/JBNVSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFaceModify dialog


CDialogFaceModify::CDialogFaceModify(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFaceModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFaceModify)
	m_strName = _T("");
	m_nAge = 0;
	m_strID = _T("");
	m_strOther = _T("");
	//}}AFX_DATA_INIT
}


void CDialogFaceModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFaceModify)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_OTHER, m_strOther);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFaceModify, CDialog)
	//{{AFX_MSG_MAP(CDialogFaceModify)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_PIC, OnButtonSelectPic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFaceModify message handlers


BOOL CDialogFaceModify::OnInitDialog()
{
	m_lpFace = 0;
    SetWindowText(_T("增加模式"));

    SetDlgItemInt(IDC_EDIT_AGE,18);

	CComboBox* cbox1 = (CComboBox*)GetDlgItem(IDC_COMBO_SEX);
	cbox1->AddString(_T("男"));
	cbox1->AddString(_T("女"));
	cbox1->SetCurSel(0);

	CComboBox* cbox2 = (CComboBox*)GetDlgItem(IDC_COMBO_ROLE);
	cbox2->AddString(_T("黑名单"));
	cbox2->AddString(_T("白名单"));
	cbox2->AddString(_T("VIP客人"));
	cbox2->SetCurSel(1);

	return TRUE;
}

void CDialogFaceModify::OnButtonSelectPic() 
{
	// TODO: Add your control notification handler code here
	CFileDialog *pDlg = new CFileDialog(TRUE,_T("*.*"), _T(""), NULL,_T("JPEG Files (*.JPG)|*.JPG|BMP Files(*.bmp)|*.bmp||"), this);
	TRACE(_T("sizeof dlg = %d sizeof(CString) = %d\n"),sizeof(CFileDialog),sizeof(CString));
	if(pDlg->DoModal() != IDOK)
	{
		delete pDlg;
		return;
	}
	CString strPath = pDlg->GetPathName();
    delete pDlg;
	LoadInputImage(strPath);

}


#include <WinCrypt.h>

DWORD GetFileMD5(CString strFile,CString &strMd5)
{
    CFile file;
    if(file.Open(strFile,CFile::modeRead,0) == FALSE)
        return -1;
    
    HCRYPTPROV hCryptProv;
    HCRYPTHASH hCryptMD5;
    DWORD dwDataLen = 16;
    BYTE	hashValue[16];
    CryptAcquireContext(&hCryptProv,0,0,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET);
    CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hCryptMD5);
    
    // Check input pointer    
    BYTE bBuffer[2048];
    while(1)
    {
        DWORD dwReaded = file.Read(bBuffer,2048);
        if(dwReaded > 0)
        {
            CryptHashData(hCryptMD5,bBuffer,dwReaded,0);
        }
        else
            break;
    }
    
    CryptGetHashParam(hCryptMD5,HP_HASHVAL,hashValue,&dwDataLen,0);
    CryptDestroyHash(hCryptMD5);
    CryptReleaseContext(hCryptProv,0);
    
    // Table with hex digits for integers 0,1,2,...15    
    static const CHAR * digits = "0123456789ABCDEF";   
    
    // 16 bytes in MD5 digest    
    static const int md5Len = 16;
    
    // Array of TCHAR's storing the MD5 digest string in hex    
    // (each MD5 byte is represented with two hex digits, and +1 is for end-of-string)    
    CHAR hexDigest[ (md5Len * 2) + 1 ];
    
    CHAR * pCurrHexDigit = hexDigest;   
    const BYTE * pCurrDigestByte = hashValue;   
    for ( int i = 0; i < md5Len; i++ )   
    {   
        *pCurrHexDigit++ = digits[ (*pCurrDigestByte) >> 4 ];      // high nibble of current byte    
        *pCurrHexDigit++ = digits[ (*pCurrDigestByte) & 0x0F ];    // low nibble of current byte    
        
        // Process next digest byte    
        ++pCurrDigestByte;   
    }   
    
    // End of string    
    *pCurrHexDigit = TEXT('\0');
    strMd5 = hexDigest;
    return 0;
}

CString GetTempFileName()
{
    TCHAR csBuf[256];
    TCHAR csBuf2[256];
    GetTempPath(256,csBuf);
    GetTempFileName(csBuf,_T("Tmp"),0,csBuf2);
    return csBuf2;	//生成临时的图片 
}

void CDialogFaceModify::LoadInputImage(CString strImage)
{
    USES_CONVERSION;

    CRect rcSrcFace;
    CRect rcDstFace;
	CSize szInputImage;    
    CString strOut = GetTempFileName();	//生成临时的图片
	int nError = JBNV_GetFaceImage(
        T2A(strImage),          //IN  输入的JPG图片
        T2A(strOut),            //IN  输出的图片名称，默认JPG格式
        &szInputImage,          //OUT strImage 的高宽
        &rcSrcFace,             //OUT 输入图片人脸位置
        &rcDstFace);            //OUT 截取成功的图片的人脸位置
    if(nError == VFD_ERROR_LOAD_IMAGE)
    {
        AfxMessageBox(_T("加载人脸图片失败，请确认图片格式正确"));
        return;
	}
    else if(nError == VFD_ERROR_RECT_INVALID)
	{
		AfxMessageBox(_T("检测失败，没有在图片内发现人脸"));
		return;
	}
	else if(nError == VFD_ERROR_FACE_MORE)
	{
		AfxMessageBox(_T("图片内检测到多于一个人脸，请重新确认图片"));
		return;
	}
	else if(nError == VFD_ERROR_VFD_ERROR)
	{
		AfxMessageBox(_T("指定的图片内的人脸不符合要求，请重新确认图片"));
		return;
	}
	else if(nError == VFD_ERROR_IMAGE_SIZE)
	{
		AfxMessageBox(_T("输入的照片太大，请重新选择照片"));
		return;
	}
	else if(nError == VFD_ERROR_FACE_SMALL)
	{
		AfxMessageBox(_T("指定的图片内的人脸太小，不符合要求，请重新确认图片"));
		return;
	}
	else if(nError < 0)
	{
		ASSERT(FALSE);
		return;
    }

    
  
    CString strTmp; 
    m_picFacerc = rcSrcFace;
    m_SmallFacerc = rcDstFace;
    
    strTmp.Format(_T("图片分辨率 %d x %d 人脸坐标 %d %d %d %d"),szInputImage.cx,szInputImage.cy,
        rcDstFace.left,rcDstFace.top,rcDstFace.right,rcDstFace.bottom);
    SetDlgItemText(IDC_STATIC_INFO,strTmp);
    
    if(m_pic.Load(strImage) == FALSE)
    {
        AfxMessageBox(_T("加载图片失败，请确认图片格式正确"));
    }
    else
    {
        m_pic2.Load(strOut);
        if(m_strSmallPic.GetLength())
        {
            DeleteFile(m_strSmallPic);
        }
        m_strSmallPic = strOut;
        m_strPicture = strImage;
        Invalidate();
	}
}

DMS_FR_SAMPLE_S *CDialogFaceModify::GetFaceInfo(DWORD *lpSize)
{
	if(lpSize == 0)
		return 0;
	*lpSize = m_dwBufSize;
	return m_lpFace;
}

void CDialogFaceModify::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    if(m_pic.IsLoad())
    {
        CDC MemDC;
        CBitmap MemBitmap;
        CRect srcRC,destRC;
        
        
        MemDC.CreateCompatibleDC((CDC *)&dc);
        GetDlgItem(IDC_STATIC_SRC)->GetWindowRect(destRC);
        ScreenToClient(destRC);
        if ( m_pic.GetImageSize(srcRC) == TRUE && srcRC.Width() && srcRC.Height())
        {
            CRect rc;
            rc.left = 0;
            rc.top = 0;
            rc.right = destRC.Width();
            rc.bottom = destRC.Height();
            MemBitmap.CreateCompatibleBitmap((CDC *)&dc,destRC.Width(),destRC.Height());
            CBitmap*pOldBmp = MemDC.SelectObject(&MemBitmap);
            
            if( m_pic.Render(&MemDC, 1, srcRC, rc,rc) == FALSE)
            {
                MemDC.SelectObject(pOldBmp);
                MemDC.DeleteDC();
                MemBitmap.DeleteObject();
                return;
            }
            
            dc.BitBlt(destRC.left,destRC.top,destRC.right,destRC.bottom,&MemDC,0,0,SRCCOPY);
            
            MemDC.SelectObject(pOldBmp);
            MemBitmap.DeleteObject();
            
            //	CPen CRecPen(PS_SOLID,2,RGB(220,0,40));
            CPen CRecPen(PS_SOLID,2,RGB(255,255,255));
            //	CBrush hRecBrush(RGB(255,0,0));
            HPEN hOldPen=(HPEN)SelectObject(dc.m_hDC,(HPEN)CRecPen);
            
            CRect Rect;
            Rect.left	= destRC.left + m_picFacerc.left	* destRC.Width() / srcRC.Width();
            Rect.top	= destRC.top + m_picFacerc.top		* destRC.Height() / srcRC.Height();
            Rect.right	= destRC.left + m_picFacerc.right * destRC.Width() / srcRC.Width();
            Rect.bottom = destRC.top + m_picFacerc.bottom * destRC.Height() / srcRC.Height();
            
            dc.MoveTo(Rect.left+1,Rect.top+1);
            dc.LineTo(Rect.right-1,Rect.top+1);
            dc.LineTo(Rect.right-1,Rect.bottom-1);
            dc.LineTo(Rect.left+1,Rect.bottom-1);
            dc.LineTo(Rect.left+1,Rect.top+1);
            dc.SelectObject(hOldPen);
            
        }
        if(m_pic2.GetImageSize(srcRC) == TRUE && srcRC.Width() && srcRC.Height())
        {
            GetDlgItem(IDC_STATIC_FACE)->GetWindowRect(destRC);
            ScreenToClient(destRC);
            CRect rc;
            rc.left = 0;
            rc.top = 0;
            rc.right = destRC.Width();
            rc.bottom = destRC.Height();
            MemBitmap.CreateCompatibleBitmap((CDC *)&dc,destRC.Width(),destRC.Height());
            CBitmap*pOldBmp = MemDC.SelectObject(&MemBitmap);
            
            if( m_pic2.Render(&MemDC, 1, srcRC, rc,rc) == FALSE)
            {
                MemDC.SelectObject(pOldBmp);
                MemDC.DeleteDC();
                MemBitmap.DeleteObject();
                return;
            }
            
            dc.BitBlt(destRC.left,destRC.top,destRC.right,destRC.bottom,&MemDC,0,0,SRCCOPY);
            
            MemDC.SelectObject(pOldBmp);
            MemBitmap.DeleteObject();
            
            if(m_SmallFacerc.Width() && m_SmallFacerc.Height())
            {
                CPen CRecPen(PS_SOLID,2,RGB(220,0,40));
                //	CBrush hRecBrush(RGB(255,0,0));
                HPEN hOldPen=(HPEN)SelectObject(dc.m_hDC,(HPEN)CRecPen);
                
                CRect Rect;
                Rect.left	= destRC.left + m_SmallFacerc.left	* destRC.Width() / srcRC.Width();
                Rect.top	= destRC.top + m_SmallFacerc.top		* destRC.Height() / srcRC.Height();
                Rect.right	= destRC.left + m_SmallFacerc.right * destRC.Width() / srcRC.Width();
                Rect.bottom = destRC.top + m_SmallFacerc.bottom * destRC.Height() / srcRC.Height();
                
                dc.MoveTo(Rect.left+1,Rect.top+1);
                dc.LineTo(Rect.right-1,Rect.top+1);
                dc.LineTo(Rect.right-1,Rect.bottom-1);
                dc.LineTo(Rect.left+1,Rect.bottom-1);
                dc.LineTo(Rect.left+1,Rect.top+1);
                dc.SelectObject(hOldPen);
            }
        }
        MemDC.DeleteDC();
    }
	
}

#define ROLE_WHITE      1
#define ROLE_BLACK      2
#define ROLE_VIP        3


void CDialogFaceModify::OnOK() 
{
    UpdateData(TRUE);
    
    USES_CONVERSION;
    
 
    if(m_strSmallPic.GetLength() == 0)
    {
        AfxMessageBox(_T("请选择人脸图片"));
        return;
    }
    if(m_lpFace)
    {
        delete m_lpFace;
        m_lpFace = 0;
    }
    CFile file;
    if(file.Open(m_strSmallPic,CFile::modeRead,0) == FALSE)
    {
        TRACE(_T("Open %s Failed %d\n"),m_strSmallPic,GetLastError());
        AfxMessageBox(_T("打开人脸图片失败，请确认图片可读"));
        return;
    }
    CString strGUID;
    CComboBox *lpCmb = (CComboBox *)GetDlgItem(IDC_COMBO_SEX);
    DWORD dwFileSize = file.GetLength();
    m_dwBufSize = sizeof(DMS_FR_SAMPLE_S) + 2048 + dwFileSize;
    m_lpFace = (DMS_FR_SAMPLE_S *)new BYTE[m_dwBufSize];
    
    memset(m_lpFace,0,sizeof(DMS_FR_SAMPLE_S));
    m_lpFace->dwSize = sizeof(DMS_FR_SAMPLE_S);
    /*
    //修改模式
    if(m_lpInput)
    {
        m_lpFace->id = m_lpInput->FrData.id;
        m_lpFace->x = m_lpInput->FrData.x;
        m_lpFace->y = m_lpInput->FrData.y;
        m_lpFace->w = m_lpInput->FrData.w;
        m_lpFace->h = m_lpInput->FrData.h;
    }
    else*/
        m_lpFace->id = -1;  //新增填-1
    
    strcpy(m_lpFace->name,T2A(m_strName));
    m_lpFace->age = m_nAge;
    GetDlgItemText(IDC_EDIT_UUID,strGUID);
    strcpy(m_lpFace->uuid,T2A(strGUID));
    
    CString strTmp;
    GetDlgItemText(IDC_EDIT_ICCARD,strTmp);
    if(strTmp.GetLength() > 31)
        strTmp = strTmp.Left(31);
    strcpy(m_lpFace->csICCard,T2A(strTmp));
    
    GetDlgItemText(IDC_EDIT_TEL,strTmp);
    if(strTmp.GetLength() > 15)
        strTmp = strTmp.Left(15);
    strcpy(m_lpFace->csTel,T2A(strTmp));
    
    m_lpFace->sex = lpCmb->GetCurSel() == 0 ? 'M' : 'F';
    lpCmb = (CComboBox *)GetDlgItem(IDC_COMBO_ROLE);
    int nSelect = lpCmb->GetCurSel();
 
    if(nSelect == 0)
        m_lpFace->role = ROLE_BLACK;
    else if(nSelect == 1)
        m_lpFace->role = ROLE_WHITE;
    else if(nSelect == 2)
        m_lpFace->role = ROLE_VIP;
    m_lpFace->x = (WORD)m_SmallFacerc.left;
    m_lpFace->y = (WORD)m_SmallFacerc.top;
    m_lpFace->w = (WORD)m_SmallFacerc.Width();
    m_lpFace->h = (WORD)m_SmallFacerc.Height();
    strcpy(m_lpFace->identity_num,T2A(m_strID));
    strcpy(m_lpFace->csOther,T2A(m_strOther));
    m_lpFace->feature_len = 0;
    m_lpFace->data_len = dwFileSize;
    file.Read(((BYTE *)m_lpFace + sizeof(DMS_FR_SAMPLE_S) + m_lpFace->feature_len),dwFileSize);
    file.Close();
     
    TCHAR csBuf[256];
    
    GetTempPath(256,csBuf);
    CString strTmpPath = csBuf;
    
    if(m_strSmallPic.GetLength() && m_strSmallPic.Left(strTmpPath.GetLength()) != strTmpPath)
        DeleteFile(m_strSmallPic);
 
	
	CDialog::OnOK();
}
