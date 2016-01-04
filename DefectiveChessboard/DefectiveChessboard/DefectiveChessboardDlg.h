
// DefectiveChessboardDlg.h : ͷ�ļ�
//

#pragma once

#include <string>
#include <vector>

using namespace std;

// CDefectiveChessboardDlg �Ի���
class CDefectiveChessboardDlg : public CDialogEx
{
// ����
public:
	CDefectiveChessboardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEFECTIVECHESSBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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