
// DefectiveChessboardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DefectiveChessboard.h"
#include "DefectiveChessboardDlg.h"
#include "afxdialogex.h"
#include "Algorithm.h"

#include <fstream>

#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDefectiveChessboardDlg 对话框

CDefectiveChessboardDlg::CDefectiveChessboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDefectiveChessboardDlg::IDD, pParent)
	, m_KValue(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	iCount = -1;
	m_KValue = 0;
	RandomValue = -1;
}

void CDefectiveChessboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_KValue);
	DDV_MinMaxInt(pDX, m_KValue, 0, 20);
}

BEGIN_MESSAGE_MAP(CDefectiveChessboardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MakeChessBoard, &CDefectiveChessboardDlg::OnBnClickedMakechessboard)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Play_Bt, &CDefectiveChessboardDlg::OnBnClickedPlayBt)
	ON_BN_CLICKED(IDC_Pause_Bt, &CDefectiveChessboardDlg::OnBnClickedPauseBt)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Save_Bt, &CDefectiveChessboardDlg::OnBnClickedSaveBt)
	ON_BN_CLICKED(IDC_Read_Bt, &CDefectiveChessboardDlg::OnBnClickedReadBt)
END_MESSAGE_MAP()


// CDefectiveChessboardDlg 消息处理程序

BOOL CDefectiveChessboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CWnd *pWnd;
	pWnd = GetDlgItem( IDC_STATIC_Panel ); //获取控件指针
	pWnd->SetWindowPos( NULL,30,55,560,560,SWP_NOZORDER ); //把按钮移到窗口的(50,80)处

	pWnd = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	pWnd->SetWindowPos( NULL,80,630,80,30,SWP_NOZORDER ); //把按钮移到窗口的(50,80)处

	pWnd = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	pWnd->SetWindowPos( NULL,200,630,80,30,SWP_NOZORDER ); //把按钮移到窗口的(50,80)处

	pWnd = GetDlgItem( IDOK ); //获取控件指针
	pWnd->SetWindowPos( NULL,400,630,80,30,SWP_NOZORDER ); //把按钮移到窗口的(50,80)处

	SetWindowPos( NULL,0,0,630,720,SWP_NOZORDER );

	CWnd *pWnd_Play = NULL;
	CWnd *pWnd_Pause = NULL;
	pWnd_Play = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	if(pWnd_Play != NULL)
	{
		pWnd_Play->EnableWindow(FALSE);
	}
	pWnd_Pause = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	if(pWnd_Pause != NULL)
	{
		pWnd_Pause->EnableWindow(FALSE);
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDefectiveChessboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDefectiveChessboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDefectiveChessboardDlg::OnBnClickedMakechessboard()
{
	// TODO: 在此添加控件通知处理程序代码
	if(CDialogEx::UpdateData(TRUE))
	{
		iCount = 0;
        for(int iLoop = 0; iLoop < (int)m_pPictureBox.size(); ++iLoop)
        {
            DeleteOneStatic(m_pPictureBox[iLoop]);
        }
		m_pPictureBox.clear();
        
		Makechessboard(0);
	}
}

void CDefectiveChessboardDlg::Makechessboard(int Mode, int Random)
{
	int KValue = m_KValue;
	double RectCount = pow(2.0, (double)KValue);

	CRect rect;
	GetDlgItem(IDC_STATIC_Panel)->GetWindowRect(&rect);  //获取控件的屏幕坐标
	ScreenToClient(&rect);                               //转换为对话框上的客户坐标

	int length = (int)((rect.bottom - rect.top) / RectCount) - 1;

	for(int Row = 0; Row < RectCount; ++Row)
	{
		for(int Col = 0; Col < RectCount; ++Col)
		{
			CRect Coord;
			Coord.top = rect.top + 1 + (length + 1) * Row;
			Coord.bottom = rect.top + 1 + length + (length + 1) * Row;
			Coord.left = rect.left + 1 + (length + 1) * Col;
			Coord.right = rect.left + 1 + length + (length + 1) * Col;

			int temp_IDC = (Row + 1) * 100 + (Col + 1);

			m_pPictureBox.push_back(CreateOneStatic(Coord, temp_IDC));
		}
	}

	if(Mode == 0)
	{
		RandomValue = RandomNum(0, m_pPictureBox.size() - 1);
	}
	else
	{
		RandomValue = Random;
	}
	
	UpdateColorOneStatic(m_pPictureBox[RandomValue], 1);

	CWnd *pWnd_Play = NULL;
	CWnd *pWnd_Pause = NULL;
	pWnd_Play = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	if(pWnd_Play != NULL)
	{
		pWnd_Play->EnableWindow(TRUE);
	}
	pWnd_Pause = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	if(pWnd_Pause != NULL)
	{
		pWnd_Pause->EnableWindow(FALSE);
	}

	int Row_Temp = 0;
	int Col_Temp = 0;
	CodeData(RandomValue, Row_Temp, Col_Temp);
	Calc(KValue, Col_Temp, Row_Temp);

	if(iCount >= (int)s.size())
	{
		KillTimer(1);
		if(pWnd_Play != NULL)
		{
			pWnd_Play->EnableWindow(TRUE);
		}
		if(pWnd_Pause != NULL)
		{
			pWnd_Pause->EnableWindow(FALSE);
		}
		return;
	}
	
	for(int jLoop = 0; jLoop < iCount; ++jLoop)
	{
		for(int iLoop = 0; iLoop < 3; ++iLoop)
		{
			UpdateColorOneStatic(m_pPictureBox[DecodeData(s[jLoop].y[iLoop], s[jLoop].x[iLoop])], 2);
		}
	}
}

CStatic *CDefectiveChessboardDlg::CreateOneStatic(CRect Coord, UINT IDC)
{  
	CStatic *pStatic = NULL;
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_Grey);

	pStatic = new CStatic;  
	ASSERT_VALID(pStatic);  
	pStatic->Create(NULL,  WS_CHILD|WS_VISIBLE|SS_CENTER|SS_BITMAP|SS_CENTERIMAGE  , Coord, this, IDC);  
	pStatic->ModifyStyle(0xF,SS_BITMAP);
	pStatic->SetBitmap((HBITMAP)bitmap);
	pStatic->ShowWindow(TRUE);
	return pStatic;
}

int CDefectiveChessboardDlg::DeleteOneStatic(CStatic *pStatic)
{  
	pStatic->DestroyWindow();  
  
    delete pStatic;

	return 1;
}

int CDefectiveChessboardDlg::UpdateColorOneStatic(CStatic *pStatic,int mode, LPCTSTR str)
{
	CBitmap bitmap;
	if(mode == 0)
	{
		bitmap.LoadBitmap(IDB_Grey);
		pStatic->ModifyStyle(0xF,SS_BITMAP);
		pStatic->SetBitmap((HBITMAP)bitmap);
	}
	else if(mode == 1)
	{
		bitmap.LoadBitmap(IDB_Black);
		pStatic->ModifyStyle(0xF,SS_BITMAP);
		pStatic->SetBitmap((HBITMAP)bitmap);
	}
	else
	{
		bitmap.LoadBitmap(IDB_Red);
		pStatic->ModifyStyle(0xF,SS_BITMAP);
		pStatic->SetBitmap((HBITMAP)bitmap);
	}

	pStatic->ShowWindow(TRUE);

	return 1;
}

int CDefectiveChessboardDlg::RandomNum(int lower, int higher)
{
	srand(unsigned(time(NULL)));
	if(lower == higher)
	{
		return lower;
	}
	else
	{
		return lower + rand() % (higher-lower);
	}
}

void CDefectiveChessboardDlg::OnBnClickedPlayBt()
{
	// TODO: 在此添加控件通知处理程序代码

	SetTimer(1,500,NULL);
	CWnd *pWnd_Play = NULL;
	CWnd *pWnd_Pause = NULL;
	pWnd_Play = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	if(pWnd_Play != NULL)
	{
		pWnd_Play->EnableWindow(FALSE);
	}
	pWnd_Pause = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	if(pWnd_Pause != NULL)
	{
		pWnd_Pause->EnableWindow(TRUE);
	}
}

void CDefectiveChessboardDlg::OnBnClickedPauseBt()
{
	// TODO: 在此添加控件通知处理程序代码

	KillTimer(1);
	CWnd *pWnd_Play = NULL;
	CWnd *pWnd_Pause = NULL;
	pWnd_Play = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	if(pWnd_Play != NULL)
	{
		pWnd_Play->EnableWindow(TRUE);
	}
	pWnd_Pause = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	if(pWnd_Pause != NULL)
	{
		pWnd_Pause->EnableWindow(FALSE);
	}
}

void CDefectiveChessboardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);

	CWnd *pWnd_Play = NULL;
	CWnd *pWnd_Pause = NULL;
	pWnd_Play = GetDlgItem( IDC_Play_Bt ); //获取控件指针
	if(pWnd_Play != NULL)
	{
		pWnd_Play->EnableWindow(FALSE);
	}
	pWnd_Pause = GetDlgItem( IDC_Pause_Bt ); //获取控件指针
	if(pWnd_Pause != NULL)
	{
		pWnd_Pause->EnableWindow(TRUE);
	}

	if(iCount >= (int)s.size())
	{
		KillTimer(1);
		if(pWnd_Play != NULL)
		{
			pWnd_Play->EnableWindow(TRUE);
		}
		if(pWnd_Pause != NULL)
		{
			pWnd_Pause->EnableWindow(FALSE);
		}
		return;
	}

	//UpdateColorOneStatic(m_pPictureBox[iCount], 2);
	for(int iLoop = 0; iLoop < 3; ++iLoop)
	{
		UpdateColorOneStatic(m_pPictureBox[DecodeData(s[iCount].y[iLoop], s[iCount].x[iLoop])], 2);
	}
	iCount++;	
}

int CDefectiveChessboardDlg::DecodeData(int Row, int Col)
{
	int Length = (int)pow(2.0,(double)m_KValue);
	return Row * Length + Col;
}

void CDefectiveChessboardDlg::CodeData(int Num, int &Row, int &Col)
{
	int Length = (int)pow(2.0,(double)m_KValue);
	Row = Num / Length;
	Col = Num - Row * Length;
}

void CDefectiveChessboardDlg::OnBnClickedSaveBt()
{
	// TODO: 在此添加控件通知处理程序代码
	if(0 == m_KValue && -1 == RandomValue && -1 == iCount)
	{
		AfxMessageBox(_T("还未开始设置游戏"));
	}
	else
	{
		CString FilePathName;
		CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
		if(dlg.DoModal()==IDOK)
		{
			FilePathName = dlg.GetPathName();
			ofstream fout(FilePathName);
			fout << m_KValue << endl;
			fout << RandomValue << endl;
			fout << iCount;
			fout.close();
		}
	}
}

void CDefectiveChessboardDlg::OnBnClickedReadBt()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
	{
		iCount = 0;
		for(int iLoop = 0; iLoop < (int)m_pPictureBox.size(); ++iLoop)
		{
			DeleteOneStatic(m_pPictureBox[iLoop]);
		}
		m_pPictureBox.clear();

		FilePathName = dlg.GetPathName();
		ifstream fin(FilePathName);
		fin >> m_KValue;
		fin >> RandomValue;
		fin >> iCount;
		fin.close();
		Makechessboard(1, RandomValue);
		CDialogEx::UpdateData(FALSE);
	}
}
