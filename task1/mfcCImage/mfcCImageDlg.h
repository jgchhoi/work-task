
// mfcCImageDlg.h: 헤더 파일
//

#pragma once


// CmfcCImageDlg 대화 상자
class CmfcCImageDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfcCImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	int m_nWidth;// 이미지 Draw 영역
	int m_nHeight;//이미지 Draw 영역
	int m_nRadius;// 반지름
	int m_nStartX;
	int m_nStartY;
	int m_nEndX;
	int m_nEndY;
	CImage m_image;
	double  m_dSlope = 0.0;
	double  m_dIntercept = 0.0;
	int m_borderWidth = 0;
	int m_borderHeight =0 ;

	bool DirectoryExists(const CString& directoryPath);
	void saveImage(int count);
	void UpdateDisplay();
	void moveRect();
	void moveCoord();
	void cleanImage();
	BOOL validatePos(int x, int y);
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	BOOL PtInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBDraw();
	afx_msg void OnBnClickedBAction();
	afx_msg void OnBnClickedBOpen();
	afx_msg void OnEnChangeEStartX();
	afx_msg void OnEnChangeEStartY();

	void GetCoord();
	void GetCenterData();
	void calculateLineEquation(int x1, int y1, int x2, int y2);
	void ChangeImageSize();
	void CalculateBorderSize();

	afx_msg void OnExitSizeMove();
};
