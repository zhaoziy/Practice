
// DefectiveChessboardDlg.h : 头文件
//

#pragma once

#include <string>
#include <vector>

using namespace std;

// CDefectiveChessboardDlg 对话框
class CDefectiveChessboardDlg : public CDialogEx
{
// 构造
public:
	CDefectiveChessboardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEFECTIVECHESSBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedMakechessboard();
	CStatic *CreateOneStatic(CRect Coord, UINT IDC);
    int DeleteOneStatic(CStatic *pStatic);
	int UpdateColorOneStatic(CStatic *pStatic,int mode, LPCTSTR str = _T(""));
	int RandomNum(int lower, int higher);
	int DecodeData(int x, int y);
	void CodeData(int Num, int &Row, int &Col);
	void Makechessboard(int Mode, int Random = 0);

private:
    vector<CStatic*> m_pPictureBox;

	int m_KValue;
	int RandomValue;
	int iCount;

public:
	afx_msg void OnBnClickedPlayBt();
	afx_msg void OnBnClickedPauseBt();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSaveBt();
	afx_msg void OnBnClickedReadBt();
};
