// DialogFaceManager.cpp : implementation file
//

#include "stdafx.h"
#include "jbsdkdemo.h"
#include "DialogFaceManager.h"
#include "include/JBNVSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFaceManager dialog


CDialogFaceManager::CDialogFaceManager(HANDLE hServer,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFaceManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFaceManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hServer = hServer;
}


void CDialogFaceManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFaceManager)
	DDX_Control(pDX, IDC_LIST_FACE, m_lvFace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFaceManager, CDialog)
	//{{AFX_MSG_MAP(CDialogFaceManager)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_SELECT, OnButtonRemoteSelect)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, OnButtonDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_BATCH_INCREASE, OnButtonBatchIncrease)
	ON_BN_CLICKED(IDC_BUTTON_FACE_EXPORT, OnButtonFaceExport)
	ON_BN_CLICKED(IDC_BUTTON_FACE_IMPORT, OnButtonFaceImport)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SERACH, OnButtonSerach)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_REC, OnButtonDownloadRec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFaceManager message handlers
enum lvFaceItem{
	item_id,
	item_uuid,
	item_name,
	item_age,
	item_sex,
	item_role,
	item_identity,
}; 

void CDialogFaceManager::OnButtonSerach() 
{
	DMS_FR_SAMPLE_QUERY_RES_S QueryRes;
	DMS_FR_SAMPLE_S *Picture = 0;
	DMS_FR_SAMPLE_QUERY_COND_S *lpQuery = (DMS_FR_SAMPLE_QUERY_COND_S *)&QueryRes;
  
    CComboBox *lpCmb = (CComboBox *)GetDlgItem(IDC_COMBO_ROLE);
	memset(&QueryRes,0,sizeof(QueryRes));
	lpQuery->page_index = 0;	//第0页
	lpQuery->page_size = 50;
	lpQuery->role = lpCmb->GetCurSel();	
    //strcpy(lpQuery->csName,T2A(strTmp));
	lpQuery->struct_size = sizeof(DMS_FR_SAMPLE_QUERY_COND_S);
	int nQueryIndex = lpQuery->page_index;

	m_lvFace.DeleteAllItems();
	
	TRACE(_T("CMD_FR_QUERY_SAMPLE page_index = %d role = %d\n"),lpQuery->page_index,lpQuery->role);
	DWORD dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_QUERY_SAMPLE,&QueryRes,sizeof(DMS_FR_SAMPLE_QUERY_RES_S));
	if(dwReturn == 0)
	{
		
		Picture = (DMS_FR_SAMPLE_S *)new BYTE[256 * 1024];
		for(int i = 0; i < QueryRes.query_size; i ++)
		{
			memset(Picture,0,sizeof(DMS_FR_SAMPLE_S));
			Picture->dwSize = sizeof(DMS_FR_SAMPLE_S);
			Picture->id = QueryRes.sample[i].id;
 			dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_REQ_SAMPLE_PIC,Picture,256 * 1024);
 
			CString strTmp;
			strTmp.Format(_T("%d"),Picture->id);
			int nItem = m_lvFace.InsertItem(m_lvFace.GetItemCount(),strTmp);
			m_lvFace.SetItemText(nItem,item_name,CString(Picture->name));
			m_lvFace.SetItemText(nItem,item_uuid,CString(Picture->uuid));
			strTmp.Format(_T("%d"),Picture->age);
			m_lvFace.SetItemText(nItem,item_age,strTmp);
			strTmp.Format(_T("%s"),Picture->sex == _T('M') ? _T("Man") : _T("Woman"));
			m_lvFace.SetItemText(nItem,item_sex,strTmp);
			if(Picture->role == 1)
				strTmp = "白名单";
			else if(Picture->role == 2)
				strTmp = "黑名单";
			else if(Picture->role == -1)
				strTmp = "陌生人";
			else
				strTmp = " ";
			m_lvFace.SetItemText(nItem,item_role,strTmp);
			m_lvFace.SetItemText(nItem,item_identity,CString(Picture->identity_num));
		}
		delete Picture;
	}
}

#include "DialogFaceModify.h"

void CDialogFaceManager::OnButtonAdd() 
{	
	CDialogFaceModify dlg;
	if(dlg.DoModal() != IDOK)
		return;
 
	DWORD dwSize;
	DMS_FR_SAMPLE_S *lpPicture = dlg.GetFaceInfo(&dwSize);
	if(lpPicture == 0)
		return;
	DWORD dwReturn = JBNV_SetServerConfig(m_hServer,CMD_FR_ADD_SAMPLE,lpPicture,dwSize); //第一个参数传的是设备的句柄，指定给哪台设备增加人脸信息
	if(dwReturn)
	{
		char csErr[256];
		JBNV_GetErrorMessage(dwReturn,csErr,256,0);
		TRACE(_T("JBNV_SetServerConfig Return %s\n"),CString(csErr));
	}
	delete lpPicture;
    if(dwReturn)
        return;
	
#if 0
	CFile file;
	file.Open(_T("D:\\Test.jpg"),CFile::modeRead,0);
	DWORD dwFileSize = file.GetLength();
	DWORD m_dwBufSize = sizeof(DMS_FR_SAMPLE_S) + 2048 + dwFileSize;
	DMS_FR_SAMPLE_S *m_lpFace = (DMS_FR_SAMPLE_S *)new BYTE[m_dwBufSize];
	
	memset(m_lpFace,0,sizeof(DMS_FR_SAMPLE_S));
	m_lpFace->dwSize = sizeof(DMS_FR_SAMPLE_S);
	m_lpFace->id = -1;	//if is modify ,this is input id;
	strcpy(m_lpFace->name,"刘强东");
	m_lpFace->age = 18;
	
	strcpy(m_lpFace->uuid,"GUID");	//guid or file md5;
	m_lpFace->sex = 'M';// : 'F';
	m_lpFace->role = 1;
	strcpy(m_lpFace->identity_num,"210021199901010001");
	strcpy(m_lpFace->csOther,"测试");
	m_lpFace->feature_len = 0;
	m_lpFace->data_len = dwFileSize;
	file.Read(((BYTE *)m_lpFace + sizeof(DMS_FR_SAMPLE_S) + m_lpFace->feature_len),dwFileSize);
	file.Close();
  
	DWORD dwReturn = JBNV_SetServerConfig(m_hServer,CMD_FR_ADD_SAMPLE,m_lpFace,m_dwBufSize);
	if(dwReturn)
	{
		char csErr[256];
		JBNV_GetErrorMessage(dwReturn,csErr,256,0);
		TRACE(_T("JBNV_SetServerConfig Return %s\n"),CString(csErr));
	}
	delete m_lpFace;
#endif 
}

void CDialogFaceManager::OnButtonModify() 
{
	CFile file;
	file.Open(_T("D:\\Test.jpg"),CFile::modeRead,0);
	DWORD dwFileSize = file.GetLength();
	DWORD m_dwBufSize = sizeof(DMS_FR_SAMPLE_S) + 2048 + dwFileSize;
	DMS_FR_SAMPLE_S *m_lpFace = (DMS_FR_SAMPLE_S *)new BYTE[m_dwBufSize];
	
	memset(m_lpFace,0,sizeof(DMS_FR_SAMPLE_S));
	m_lpFace->dwSize = sizeof(DMS_FR_SAMPLE_S);
	m_lpFace->id = 0;	//if is modify ,this is input id;
	strncpy(m_lpFace->name,"刘强东",32);
	m_lpFace->age = 18;
	
	strncpy(m_lpFace->uuid,"GUID",36);	//guid or file md5;
	m_lpFace->sex = 'M';// : 'F';
	m_lpFace->role = 1;
	strncpy(m_lpFace->identity_num,"210021199901010001",30);
	strncpy(m_lpFace->csOther,"测试",64);
	m_lpFace->feature_len = 0;
	m_lpFace->data_len = dwFileSize;
	file.Read(((BYTE *)m_lpFace + sizeof(DMS_FR_SAMPLE_S) + m_lpFace->feature_len),dwFileSize);
	file.Close();
	
	//update sample;
	DWORD dwReturn = JBNV_SetServerConfig(m_hServer,CMD_FR_UPDATE_SAMPLE,m_lpFace,m_dwBufSize);
	if(dwReturn)
	{
		char csErr[256];
		JBNV_GetErrorMessage(dwReturn,csErr,256,0);
		TRACE(_T("JBNV_SetServerConfig Return %s\n"),CString(csErr));
	}
	delete m_lpFace;
}

void CDialogFaceManager::OnButtonDel() 
{
	DMS_FR_SAMPLE_S FrData;
	memset(&FrData,0,sizeof(FrData));
	FrData.data_len = 0;
	FrData.feature_len = 0;
	FrData.dwSize = sizeof(DMS_FR_SAMPLE_S);
    int nSelect = m_lvFace.GetNextItem(-1,LVNI_SELECTED);
    if(nSelect < 0)
        return;
    CString strID = m_lvFace.GetItemText(nSelect,item_id);
	FrData.id = _ttoi(strID);	//need delete item id;
 
	DWORD dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_DEL_SAMPLE,&FrData,sizeof(DMS_FR_SAMPLE_S));
}

BOOL CDialogFaceManager::OnInitDialog() 
{
 
	CDialog::OnInitDialog();
	
	m_lvFace.SetExtendedStyle(m_lvFace.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
 
	m_lvFace.InsertColumn(item_id,_T("ID"),LVCFMT_LEFT,80);		//设备端保存的人脸的ID码，不同设备之间会重叠
	m_lvFace.InsertColumn(item_uuid,_T("UUID"),LVCFMT_LEFT,80);	//系统或平台区分前端设备的唯一ID
	m_lvFace.InsertColumn(item_name,_T("Name"),LVCFMT_LEFT,80);		//姓名
	m_lvFace.InsertColumn(item_age,_T("AGE"),LVCFMT_LEFT,80);		//年龄
	m_lvFace.InsertColumn(item_sex,_T("sex"),LVCFMT_LEFT,80);		//性别
	m_lvFace.InsertColumn(item_role,_T("role"),LVCFMT_LEFT,80);		//ROLE 黑白名单
	m_lvFace.InsertColumn(item_identity,_T("identity"),LVCFMT_LEFT,80);//身份证
 
	//初始化Combox的值
	CComboBox* cbox_page = (CComboBox*)GetDlgItem(IDC_COMBO_PAGE);
	cbox_page->AddString(_T("第 1 页"));
	cbox_page->SetCurSel(0);
	CComboBox* cbox_List = (CComboBox*)GetDlgItem(IDC_COMBO_ROLE);
	cbox_List->SetCurSel(0);

 
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
 

//远程设备选择
void CDialogFaceManager::OnButtonRemoteSelect() 
{
	// TODO: Add your control notification handler code here
	
 

}

//删除所有
void CDialogFaceManager::OnButtonDeleteAll() 
{
 
	// TODO: Add your control notification handler code here
	int nReturn = AfxMessageBox(_T("你确定要删除设备内所有的人脸数据嘛？删除后不可\r\n恢复，请慎重选择!"),MB_YESNO);
	if(nReturn == IDYES)
    {
        JBNV_SetServerConfig(m_hServer,DMS_NET_CMD_FR_RESET_SAMPLE_DB,0,0);
    }
}

//批量增加
void CDialogFaceManager::OnButtonBatchIncrease() 
{
	TCHAR szFilter[] = _T("Excel 2013 File (*.xlsx)|*.xlsx|Excel 2007 File (*.xls)|*.xls||");
	CFileDialog *pFDlg = new CFileDialog(TRUE,NULL,0,OFN_EXPLORER|OFN_FILEMUSTEXIST,szFilter,this);
	if(pFDlg->DoModal() != IDOK)
	{
		delete pFDlg;
		return;
	}
}

#define FDB_MAGIC       0x01AF31A1

typedef struct tagFDB_FILE_HEADER{
    DWORD dwMagic;
    DWORD dwFaceCount;
    DWORD dwFileSize;
    DWORD dwCRC32;
    DWORD dwReserved[4];
}FDB_FILE_HEADER;

//人脸库导出
void CDialogFaceManager::OnButtonFaceExport() 
{
    FDB_FILE_HEADER header;
    DMS_FR_SAMPLE_QUERY_RES_S QueryRes;
    DMS_FR_SAMPLE_S *Picture = 0;
    DMS_FR_SAMPLE_QUERY_COND_S *lpQuery = (DMS_FR_SAMPLE_QUERY_COND_S *)&QueryRes;

    TCHAR szFilter[] = _T("Face Data Base (*.fdb)|*.fdb||");
    CString strFileName;
    SYSTEMTIME st;
    GetLocalTime(&st);
 
    strFileName.Format(_T("%04d-%02d-%02d.fdb"),st.wYear,st.wMonth,st.wDay);

    CFileDialog *pDlg = new CFileDialog(FALSE,NULL,strFileName,OFN_EXPLORER,szFilter,this);

    CFile OutputFile;
    int nSaved = 0;
    CString strTmp;

    if(pDlg->DoModal() != IDOK)
    {
        delete pDlg;
        return;
    }
    strFileName = pDlg->GetPathName();
    delete pDlg;
    if(OutputFile.Open(strFileName,CFile::modeCreate | CFile::modeReadWrite,0) == FALSE)
    {     
        AfxMessageBox(_T("打开输出文件失败，请检查路径"));
        return;
    }

    DWORD dwReturn = 0;
    char csBuf[256];
    Picture = (DMS_FR_SAMPLE_S *)new BYTE[256 * 1024];
    int nPage_index = 0;
    JBNV_SERVER_INFO si;
    si.dwSize = sizeof(si);
    JBNV_GetServerInfo(m_hServer,&si);
    

    memset(&header,0,sizeof(header));
    while(1)
    {
        memset(&QueryRes,0,sizeof(QueryRes));
	    lpQuery->page_index = nPage_index;
        lpQuery->page_size = 50;
        lpQuery->role = 0;
        lpQuery->struct_size = sizeof(DMS_FR_SAMPLE_QUERY_COND_S);
        dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_QUERY_SAMPLE,&QueryRes,sizeof(DMS_FR_SAMPLE_QUERY_RES_S));
        if(dwReturn == 0)
        {
            if(QueryRes.total_size == 0)
            {
                strTmp.Format(_T("设备没有人脸信息，无法导出"));
                //SetDlgInfoString(strTmp);
                break;
            }
            if(nPage_index == 0)
            {
                strTmp.Format(_T("设备共保存有 %d 个人脸信息"),QueryRes.total_size);
                //SetDlgInfoString(strTmp);
                
                header.dwMagic = FDB_MAGIC;
                header.dwFaceCount = QueryRes.total_size;
                OutputFile.Write(&header,sizeof(FDB_FILE_HEADER));
            }
            for(int i = 0; i < QueryRes.query_size; i ++)
            {
                memset(Picture,0,sizeof(DMS_FR_SAMPLE_S));
                Picture->dwSize = sizeof(DMS_FR_SAMPLE_S);
                Picture->id = QueryRes.sample[i].id;
                dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_REQ_SAMPLE_PIC,Picture,256 * 1024);
                if(dwReturn == 0)
                {
                    strTmp.Format(_T("正在导出 %s 的数据，已保存 %d/%d 个，完成 %d%%"),CString(QueryRes.sample[i].name),
                        nSaved,QueryRes.total_size,nSaved * 100 / QueryRes.total_size);
                    nSaved ++;
                    //SetDlgInfoString(strTmp);
                    OutputFile.Write(Picture,sizeof(DMS_FR_SAMPLE_S) + Picture->feature_len + Picture->data_len);
                }
                else
                    break;
            }
        }
        if(dwReturn)
        {
            JBNV_GetErrorMessage(dwReturn,csBuf,256,0);
            strTmp.Format(_T("导出时发生异常，错误信息：%s"),CString(csBuf));
            //SetDlgInfoString(strTmp);
            break;
        }
        nPage_index ++;
        if((QueryRes.total_size + 49) / 50 == nPage_index)
            break;
    }

    if(dwReturn == 0)
    {
		header.dwFileSize = OutputFile.Seek(0, SEEK_CUR);
        OutputFile.Seek(0,SEEK_SET);
        OutputFile.Write(&header,sizeof(header));
        OutputFile.Close();
        strTmp.Format(_T("导出完毕，共有 %d 个人脸数据"),header.dwFaceCount);
        //SetDlgInfoString(strTmp);
    }
    delete Picture;
}


class CFaceManagerImport
{
public:
    CFaceManagerImport() {
        m_lpBuffer = 0;  
        m_lpFace = 0;
        memset(&header,0,sizeof(header));
    };
    ~CFaceManagerImport()
    {
        if(m_lpFace)
        {
            delete m_lpFace;
            m_lpFace = 0;
        }
        if(m_lpBuffer)
        {
            delete m_lpBuffer;
            m_lpBuffer = 0;
        }
    }
    BOOL OpenFDBFile(CString strFile,CString &strError)
    {
        if(file.Open(strFile,CFile::modeRead,0) == 0)
        {
            strError = (_T("打开导入文件失败，请确认文件可读"));
            return FALSE;
        }
        if(file.Read(&header,sizeof(header)) != sizeof(header))
        {
            strError = (_T("读取导入文件失败，请确认文件可读"));
            return FALSE;
        }
        if(header.dwMagic != FDB_MAGIC || header.dwFileSize == 0 || header.dwFaceCount == 0)
        {
            strError = (_T("读取导入文件失败，文件校验码不正确"));
            return FALSE;
        }
        m_lpBuffer = new BYTE[header.dwFileSize];
        if(m_lpBuffer == 0)
        {
            strError = (_T("分配内存读取文件失败，请关闭程序部分功能后再试"));
            return FALSE;
        }
        //读取数据
        m_lpFace = new DMS_FR_SAMPLE_S *[header.dwFaceCount];
        memset(m_lpFace,0,header.dwFaceCount * sizeof(DMS_FR_SAMPLE_S *));
        file.Read(m_lpBuffer,header.dwFileSize - sizeof(header));
        file.Close();
        
        //建立指针列表
        BYTE *lpData = m_lpBuffer;
        for(int i = 0; i < header.dwFaceCount; i ++)
        {
            m_lpFace[i] = (DMS_FR_SAMPLE_S *)lpData;
            lpData += sizeof(DMS_FR_SAMPLE_S) + m_lpFace[i]->data_len + m_lpFace[i]->feature_len;
        }
        return TRUE;
    }
    DWORD GetFaceCount()  {   return header.dwFaceCount;  };
    DMS_FR_SAMPLE_S *GetFaceData(DWORD dwFace) {   
        ASSERT(dwFace < header.dwFaceCount);
        return m_lpFace[dwFace]; 
    };
private:
    BYTE *m_lpBuffer;
    DMS_FR_SAMPLE_S **m_lpFace;
    FDB_FILE_HEADER header;
    CFile file;
};


int CDialogFaceManager::QueryServerFace(std::vector<DMS_FR_SAMPLE_QUERY_RES_S> *lpFaceInfo)
{
    DWORD dwReturn = 0;
    int nPage_index = 0;
    JBNV_SERVER_INFO si;
    CString strTmp;
    char csBuf[256];
    si.dwSize = sizeof(si);
    JBNV_GetServerInfo(m_hServer,&si);
    DMS_FR_SAMPLE_QUERY_RES_S QueryRes;
    DMS_FR_SAMPLE_QUERY_COND_S *lpQuery = (DMS_FR_SAMPLE_QUERY_COND_S *)&QueryRes;
    //查询前端人脸信息
    while(1)
    {
        memset(&QueryRes,0,sizeof(QueryRes));
        lpQuery->page_index = nPage_index;
        lpQuery->page_size = 50;
        lpQuery->role = 0;
        lpQuery->struct_size = sizeof(DMS_FR_SAMPLE_QUERY_COND_S);
        dwReturn = JBNV_GetServerConfig(m_hServer,CMD_FR_QUERY_SAMPLE,&QueryRes,sizeof(DMS_FR_SAMPLE_QUERY_RES_S));
        if(dwReturn == 0)
        {
            if(QueryRes.total_size == 0)
            {
                break;
            }
            if(nPage_index == 0)
            {
                strTmp.Format(_T("设备共保存有 %d 个人脸信息，正在查询前端信息"),QueryRes.total_size);
                //SetDlgInfoString(strTmp);
            }
            lpFaceInfo->push_back(QueryRes);
            TRACE(_T("nPage_index = %d query_size = %d\n"),nPage_index,QueryRes.query_size);
        }
        else
        {
            JBNV_GetErrorMessage(dwReturn,csBuf,256,0);
            strTmp.Format(_T("导入时发生异常，错误信息：%s"),CString(csBuf));
            //SetDlgInfoString(strTmp);
            return -1;
        }
        nPage_index ++;
        
        
        
        if((QueryRes.total_size + 49) / 50 == nPage_index)
            break;
    }
    return 0;
}

//人脸库导入
void CDialogFaceManager::OnButtonFaceImport() 
{
    TCHAR szFilter[] = _T("Face Data Base (*.fdb)|*.fdb||");
    CString strFileName;
    
    
    CFileDialog *pDlg = new CFileDialog(TRUE,NULL,NULL,OFN_NODEREFERENCELINKS | OFN_FILEMUSTEXIST | OFN_EXPLORER,szFilter,this);
    if(pDlg->DoModal() != IDOK)
    {
        delete pDlg;
        return;
    }
    CString m_strImportFile = pDlg->GetPathName();
    delete pDlg;
    
    DWORD dwReturn;
    CString strTmp;
    CFaceManagerImport Import; 
    if(Import.OpenFDBFile(m_strImportFile,strTmp) == FALSE)
    {
        AfxMessageBox(strTmp);
        return ;
    }

    std::vector<DMS_FR_SAMPLE_QUERY_RES_S> FaceInfo;
    if(QueryServerFace(&FaceInfo) < 0)
        return ;
  
    int nImportCount = 0;
    int nSkipCount = 0;
    int nUpdateCount = 0;
    char csBuf[256];

    for(DWORD i = 0; i < Import.GetFaceCount(); i ++)
    {
		unsigned int s;
        DMS_FR_SAMPLE_S *lpFaceData = Import.GetFaceData(i);
        if(lpFaceData->uuid[0] == 0)
            continue;
        //TRACE(_T("Input %d UUID %s\n"),i,CString(lpFaceData->uuid));
        BOOL bFind = 0;
        BOOL bModify = 0;
        strTmp.Format(_T("正在导入第 %d 个人脸，总计有 %d 需要导入"),i,Import.GetFaceCount());
        //SetDlgInfoString(strTmp);
        
        //查看前端是否有这个UUID，没有，则添加进去，有则略过
        for(s = 0; s < FaceInfo.size(); s ++)
        {
            DMS_FR_SAMPLE_QUERY_RES_S *lpRes = &FaceInfo.at(s);
     
            for(int j = 0; j < lpRes->query_size; j ++)
            {
                //TRACE(_T("Server UUID %s\n"),CString(lpRes->sample[j].uuid));
                if(strcmp(lpFaceData->uuid,lpRes->sample[j].uuid) == 0)
                {
                    bFind = 1;
                    lpFaceData->id = lpRes->sample[j].id;
                    //最后的图像大小和特征大小lpRes->sample[j]内没有，不进行比较
                    if(memcmp(lpFaceData,&lpRes->sample[j],sizeof(DMS_FR_SAMPLE_S) - sizeof(int) * 2) != 0)
                    {
                        //数据不同，需要修改
                        bModify = 1;
                    }
                    break;
                }
            }
            if(bFind)
                break;
        }
        if(bFind)
        {
            if(bModify)
            {
                dwReturn = JBNV_SetServerConfig(m_hServer,CMD_FR_UPDATE_SAMPLE,lpFaceData,sizeof(DMS_FR_SAMPLE_S) + lpFaceData->feature_len + lpFaceData->data_len);
                if(dwReturn == 0)
                {
                    nUpdateCount ++;
                    strTmp.Format(_T("更新第 %d 个人脸数据成功"),i);
                    //SetDlgInfoString(strTmp);
                }
            }
            else
            {
                nSkipCount ++;

                strTmp.Format(_T("已存在人脸，略过..."));
                //SetDlgInfoString(strTmp);
            }
            continue;
        }
        //检查已经导入过的，是否有重复UUID
        for(s = 0;s < i; s ++)
        {
            DMS_FR_SAMPLE_S *lpFaceData2 = Import.GetFaceData(s);
            if(lpFaceData2->uuid[0] == 0)
                continue;
            if(strcmp(lpFaceData2->uuid,lpFaceData->uuid) == 0)
            {
                bFind = 1;
                break;
            }
        }
        if(bFind)
        {
            strTmp.Format(_T("已存在人脸，略过..."));
            //SetDlgInfoString(strTmp);
            nSkipCount ++;
            continue;
        }
        TRACE(_T("%s(%d) : Input  %d UUID %s Not Find At Server\n"),CString(__FILE__),__LINE__, i,CString(lpFaceData->uuid));
        lpFaceData->id = -1;
        //lpFaceData->dwSize = sizeof(DMS_FR_SAMPLE_S);
        dwReturn = JBNV_SetServerConfig(m_hServer,CMD_FR_ADD_SAMPLE,lpFaceData,
            sizeof(DMS_FR_SAMPLE_S) + lpFaceData->data_len + lpFaceData->feature_len);
        if(dwReturn)
        {
            JBNV_GetErrorMessage(dwReturn,csBuf,256,0);
            strTmp.Format(_T("导入时发生异常，错误信息：%s"),CString(csBuf));
            //SetDlgInfoString(strTmp);
            return ;
        }
        TRACE(_T("%s(%d) : Import %d UUID %s Success\n"),CString(__FILE__),__LINE__, i,CString(lpFaceData->uuid));
        nImportCount ++;
    }
    strTmp.Format(_T("导入完毕，共导入 %d 个人脸数据 ,略过 %d 个, 更新  %d 个"),nImportCount,nSkipCount,nUpdateCount);
    //SetDlgInfoString(strTmp);

}


void CDialogFaceManager::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

DWORD GetDWORDTime(SYSTEMTIME *lpTime)
{
    if(lpTime == 0 || lpTime->wYear < 2000 || lpTime->wMonth < 1 || lpTime->wDay < 1)
    {
        TRACE(_T("GetDWORDTime Input Param Error\n"));
        return 0xFFFFFFFF;
    }
    DWORD dwTime = (lpTime->wYear - 2000) * 12;    //yue
    dwTime = (dwTime + lpTime->wMonth - 1) * 31;       //day   
    dwTime = (dwTime + lpTime->wDay - 1) * 24;         //hour
    dwTime = (dwTime + lpTime->wHour) * 60;        //min
    dwTime = (dwTime + lpTime->wMinute) * 60;      //sec
    dwTime = (dwTime + lpTime->wSecond);
    return dwTime;
}
 
DWORD GetNVRTime(int nYear,int nMon,int nDay,int nHour,int nMin,int nSecond)
{
    SYSTEMTIME stTime;
    stTime.wYear     = nYear;
    stTime.wMonth    = nMon;
    stTime.wDay      = nDay;
    stTime.wHour     = nHour;
    stTime.wMinute   = nMin;
    stTime.wSecond   = nSecond;
    return GetDWORDTime(&stTime);
}

DWORD GetNVRTime_(const char *lpdate)
{
    if(lpdate == 0)
        return 0;
    int nYear = 0;
    int nMonth;
    int nDay;
    int nHour;
    int nMin;
    int nSec;
    if(sscanf(lpdate,"%04d-%02d-%02d %02d:%02d:%02d",&nYear,&nMonth,&nDay,&nHour,&nMin,&nSec) == 6)
    {
        return GetNVRTime(nYear,nMonth,nDay,nHour,nMin,nSec);
    }
    return 0;
}


void GetRecordTime(SYSTEMTIME *lpTime,DWORD dwTime)
{
    lpTime->wSecond = dwTime % 60;
    dwTime = dwTime / 60;
    lpTime->wMinute = dwTime % 60;
    dwTime = dwTime / 60;
    lpTime->wHour = dwTime % 24;
    dwTime = dwTime / 24;
    lpTime->wDay = (dwTime % 31) + 1;
    dwTime = dwTime / 31;
    lpTime->wMonth = (dwTime % 12) + 1;
    dwTime = dwTime / 12;
    lpTime->wYear = dwTime + 2000;
    lpTime->wMilliseconds = 0;
    CTime TDay(lpTime->wYear,lpTime->wMonth,lpTime->wDay,0,0,0);
    SYSTEMTIME stTmp;
    TDay.GetAsSystemTime(stTmp);
    lpTime->wDayOfWeek = stTmp.wDayOfWeek;
    return ;
}


void CDialogFaceManager::DoIPCDownload(SYSTEMTIME *stStart,SYSTEMTIME *stEnd)
{
    DMS_FR_RECORD_QUERY_RES_S Res;
    int nPageIndex = 0;
    memset(&Res,0,sizeof(Res));
    DMS_FR_RECORD_QUERY_BY_TIME_REQ_S *lpQuery = (DMS_FR_RECORD_QUERY_BY_TIME_REQ_S *)&Res;
    lpQuery->struct_size = sizeof(DMS_FR_RECORD_QUERY_BY_TIME_REQ_S);
    lpQuery->page_index = nPageIndex;
    lpQuery->page_size = DMS_FR_QUERY_HIS_MAX_NUM;
    sprintf(lpQuery->start_time,"%04d-%02d-%02d 00:00:00",stStart->wYear,stStart->wMonth,stStart->wDay);
    sprintf(lpQuery->end_time,"%04d-%02d-%02d 23:59:59",stEnd->wYear,stEnd->wMonth,stEnd->wDay);
    DWORD dwError = JBNV_GetServerConfig(m_hServer,DMS_NET_CMD_FR_QUERY_HISTORY_BY_TIME,&Res,sizeof(Res));
    while(dwError == 0)
    {
        TRACE(_T("Res total_size %d struct_size %d query_size %d sizeof(Res) %d\n"),Res.total_size,Res.struct_size,Res.query_size,sizeof(Res));
        for(int i = 0; i < Res.query_size; i ++)
        {
            TRACE(_T("uuid %s name %s time %s\n"),CString(Res.record[i].uuid),CString(Res.record[i].name),CString(Res.record[i].datetime));
        }
        if(Res.query_size < DMS_FR_QUERY_HIS_MAX_NUM)
            break;
        nPageIndex ++;  //下一页
        lpQuery->struct_size = sizeof(DMS_FR_ATTANDENCE_QUERY_COND_S);
        lpQuery->page_size = DMS_FR_QUERY_HIS_MAX_NUM;
        lpQuery->page_index = nPageIndex;   
        sprintf(lpQuery->start_time,"%04d-%02d-%02d 00:00:00",stStart->wYear,stStart->wMonth,stStart->wDay);
        sprintf(lpQuery->end_time,"%04d-%02d-%02d 23:59:59",stEnd->wYear,stEnd->wMonth,stEnd->wDay);
        dwError = JBNV_GetServerConfig(m_hServer,DMS_NET_CMD_FR_QUERY_HISTORY_BY_TIME,lpQuery,sizeof(Res));
    }
}


void CDialogFaceManager::DoNVRDownload(SYSTEMTIME *stStart,SYSTEMTIME *stEnd)
{
    DMS_FR_ATTANDENCE_QUERY_RES_S Res;
    memset(&Res,0,sizeof(Res));
    int nPageIndex = 0;
    DWORD dwStartTime = GetNVRTime(stStart->wYear,stStart->wMonth,stStart->wDay,0,0,0);
    DWORD dwEndTime = GetNVRTime(stEnd->wYear,stEnd->wMonth,stEnd->wDay,23,59,59); 
    DMS_FR_ATTANDENCE_QUERY_COND_S *lpQuery = (DMS_FR_ATTANDENCE_QUERY_COND_S *)&Res;
    lpQuery->struct_size = sizeof(DMS_FR_ATTANDENCE_QUERY_COND_S);
    lpQuery->page_size = 100;
    lpQuery->page_index = nPageIndex;
    lpQuery->chn = -1;
    
    lpQuery->start_time = dwStartTime;
    lpQuery->end_time = dwEndTime; 
    DWORD dwError = JBNV_GetServerConfig(m_hServer,DMS_NET_CMD_FR_GET_ATTANDENCE_DB,lpQuery,sizeof(Res));
    TRACE(_T("DMS_NET_CMD_FR_GET_ATTANDENCE_DB Return %08X\n"),dwError);
    while(dwError == 0)
    {
        TRACE(_T("Res total_size %d struct_size %d query_size %d sizeof(Res) %d\n"),Res.total_size,Res.struct_size,Res.query_size,sizeof(Res));
        for(int i = 0; i < Res.query_size; i ++)
        {
            SYSTEMTIME st;
            GetRecordTime(&st,Res.fr_log[i].data_time);
            TRACE(_T("uuid %s name %s time %04d-%02d-%02d %02d:%02d:%02d sorce %d\n"),CString(Res.fr_log[i].uuid),CString(Res.fr_log[i].name),
                st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,
                Res.fr_log[i].sorce);
        }
        if(Res.query_size < 100)
            break;
        nPageIndex ++;  //next page.
        lpQuery->struct_size = sizeof(DMS_FR_ATTANDENCE_QUERY_COND_S);
        lpQuery->page_size = 100;
        lpQuery->page_index = nPageIndex;
        lpQuery->chn = -1;
        lpQuery->start_time = dwStartTime;
        lpQuery->end_time = dwEndTime; 
        dwError = JBNV_GetServerConfig(m_hServer,DMS_NET_CMD_FR_GET_ATTANDENCE_DB,lpQuery,sizeof(Res));
    }
}

void CDialogFaceManager::OnButtonDownloadRec() 
{
    JBNV_SERVER_INFO si;
    si.dwSize = sizeof(si);
    SYSTEMTIME stStart;
    SYSTEMTIME stEnd;
    memset(&stStart,0,sizeof(stStart));
    stStart.wYear = 2019;
    stStart.wMonth = 5;
    stStart.wDay = 8;
    memcpy(&stEnd,&stStart,sizeof(SYSTEMTIME));
    stEnd.wDay = 9;
    JBNV_GetServerInfo(m_hServer,&si);
    if(si.wChannelNum > 1)
        DoNVRDownload(&stStart,&stEnd);
    else
        DoIPCDownload(&stStart,&stEnd);
	
}
