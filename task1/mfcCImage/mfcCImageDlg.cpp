
// mfcCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcCImage.h"
#include "mfcCImageDlg.h"
#include "afxdialogex.h"
#include  <iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define GRAY_COLOR 100
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:

//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnExitSizeMove();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
//ON_WM_EXITSIZEMOVE()
END_MESSAGE_MAP()


// CmfcCImageDlg 대화 상자



CmfcCImageDlg::CmfcCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

;
	m_nRadius = 20;
	m_nWidth = 640;
	m_nHeight = 480;

	m_nStartX = 100;
	m_nStartY =100;
	m_nEndX = 300;
	m_nEndY = 300;
}

void CmfcCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_DRAW, &CmfcCImageDlg::OnBnClickedBDraw)
	ON_BN_CLICKED(IDC_B_ACTiON, &CmfcCImageDlg::OnBnClickedBAction)
	ON_BN_CLICKED(IDC_B_OPEN, &CmfcCImageDlg::OnBnClickedBOpen)
	ON_EN_CHANGE(IDC_E_START_X, &CmfcCImageDlg::OnEnChangeEStartX)
	ON_EN_CHANGE(IDC_E_START_Y, &CmfcCImageDlg::OnEnChangeEStartY)
ON_WM_EXITSIZEMOVE()
END_MESSAGE_MAP()


// CmfcCImageDlg 메시지 처리기

BOOL CmfcCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	ModifyStyle(0, WS_THICKFRAME);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CalculateBorderSize();
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	ChangeImageSize();

	SetDlgItemInt(IDC_E_START_X, m_nStartX);
	SetDlgItemInt(IDC_E_START_Y, m_nStartY);
	SetDlgItemInt(IDC_E_END_X, m_nEndX);
	SetDlgItemInt(IDC_E_END_Y, m_nEndY);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcCImageDlg::CalculateBorderSize() {

	CRect windowRect;
	GetWindowRect(&windowRect); // 전체 창 크기와 위치를 가져옵니다.

	CRect clientRect;
	GetClientRect(&clientRect); // 클라이언트 영역의 크기를 가져옵니다.

	// 테두리 영역의 크기 계산
	m_borderWidth = (windowRect.Width() - clientRect.Width()) / 2;
	m_borderHeight = windowRect.Height() - clientRect.Height() - GetSystemMetrics(SM_CYCAPTION);


}

void CmfcCImageDlg::ChangeImageSize()
{
	RECT rect, textRect;

	GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_SIZE)->GetClientRect(&textRect);

	m_nWidth = rect.right - textRect.right - m_borderWidth*4;
	m_nHeight = rect.bottom- m_borderHeight;

	CString str;
	str.Format(_T("배경이미지 크기(%d,%d)\n입력 좌표(0,0) ~ (%d,%d)"), m_nWidth, m_nHeight, m_nWidth, m_nHeight);
	SetDlgItemText(IDC_STATIC_SIZE, str);

	Invalidate();
	UpdateWindow();
	UpdateDisplay();
}

void CmfcCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcCImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CmfcCImageDlg::DirectoryExists(const CString& directoryPath) {
	CFileFind finder;
	BOOL isFound = finder.FindFile(directoryPath);
	return isFound != 0;
}

void CmfcCImageDlg::cleanImage()
{
	int nPitch = m_image.GetPitch();
	int nHeight = m_image.GetHeight();
	int nWidth = m_image.GetWidth();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int y = 0; y < nHeight; ++y) {
		memset(fm + y * nPitch, 0xff, nWidth * m_image.GetBPP() / 8);
	}
}

void CmfcCImageDlg::GetCoord()
{
	m_nStartX = GetDlgItemInt(IDC_E_START_X);
	m_nStartY = GetDlgItemInt(IDC_E_START_Y);
	m_nEndX = GetDlgItemInt(IDC_E_END_X);
	m_nEndY = GetDlgItemInt(IDC_E_END_Y);
}
//
// 이미지 그리기
//
void CmfcCImageDlg::OnBnClickedBDraw()
{
	int nWidth = m_nWidth;
	int nHeight = m_nHeight;
	int nBpp = 8;//bit per pixel

	if (m_image != NULL)
		m_image.Destroy();

	m_image.Create(nWidth, nHeight, nBpp);

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256;i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	cleanImage();

	m_nRadius = rand() % (nHeight / 4);
	if (m_nRadius < 10)
		m_nRadius = 10;
	unsigned char* fm = (unsigned char*)m_image.GetBits();


	GetCoord();

	drawCircle(fm, m_nStartX, m_nStartY, m_nRadius, GRAY_COLOR);

	UpdateDisplay();
	//fm[nHeight/2 * nPitch + nWidth/2] = 0;
	
	//CClientDC dc(this);
	//m_image.Draw(dc, 0, 0);

	//int x = nWidth/2+10;
	//int y = nHeight/2+10;
	//// 출력할 텍스트
	//CString text = _T("안녕하세요, MFC!");
	//// 특정 좌표값에 텍스트 출력
	//dc.TextOut(x, y, text);
	//UpdateDisplay();

}

void CmfcCImageDlg::saveImage(int count)
{
	WCHAR buffer[MAX_PATH];

	::GetCurrentDirectory(MAX_PATH, buffer);

	CString str(buffer);
	str += "/Image";
	if (false == DirectoryExists(str))
		CreateDirectory(str, NULL);
	CString filename;
	filename.Format(_T("/save%d.bmp"), count);
	m_image.Save(str + filename);

}

void CmfcCImageDlg::moveCoord()
{
	if (m_dSlope != 0.0)
	{
		if (m_nEndX > m_nStartX)
		{
			if (m_nStartX < m_nEndX)
				m_nStartX++;
		}
		else if (m_nEndX < m_nStartX)
		{
			if (m_nStartX > m_nEndX)
				m_nStartX--;
		}
		m_nStartY = (int)(m_dSlope * m_nStartX + m_dIntercept);
	}
	else
	{
		if (m_nEndY > m_nStartY)
		{
			if (m_nStartY  < m_nEndY)
				m_nStartY++;
		}
		else if (m_nEndY < m_nStartY)
		{
			if (m_nStartY  > m_nEndY)
				m_nStartY--;
		}
	}
}

void CmfcCImageDlg::moveRect()
{
	int nGray = GRAY_COLOR;
	int nRadius = m_nRadius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	drawCircle(fm, m_nStartX, m_nStartY, nRadius, 0xff);//clean
	
	moveCoord();

	drawCircle(fm, m_nStartX, m_nStartY, nRadius, nGray);

	UpdateDisplay();
}

BOOL CmfcCImageDlg::validatePos(int x, int y)
{   
	BOOL bRet = FALSE;
	int nHeight = m_image.GetHeight();
	int nWidth = m_image.GetWidth();

	CRect rect(0,0, nWidth, nHeight);
	bRet = rect.PtInRect(CPoint(x, y));

	return bRet;
}

void CmfcCImageDlg::drawCircle(unsigned char* fm, int nCenterX, int nCenterY, int nRadius, int nGray)
{
	int nPitch = m_image.GetPitch();
	
	for (int j = nCenterY - nRadius;j < nCenterY + nRadius;j++) {
		for (int i = nCenterX - nRadius; i < nCenterX + nRadius;i++) {
			if (i < m_nWidth && j < m_nHeight)
			{
				if(i>0 && j>0)
				if (PtInCircle(i, j, nCenterX, nCenterY, nRadius))
					fm[j * nPitch + i] = nGray;
			}
		}
	}
}

BOOL CmfcCImageDlg::PtInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	BOOL bRet = FALSE;

	double dx = i - nCenterX;
	double dy = j - nCenterY;
	double dDist = dx * dx + dy * dy;
	if (dDist < nRadius * nRadius)
		bRet = TRUE;

	return bRet;
}

void CmfcCImageDlg::calculateLineEquation(int x1,int y1,int x2, int y2) {

	double dx = (x2 - x1);
	double dy = (y2 - y1);
	m_dIntercept =0.0;
	m_dSlope = 0.0;
	if (x2 != x1)
	{
		m_dSlope = dy / dx;
	}
	else
		m_dSlope = 0.0;

	m_dIntercept = y1 - m_dSlope * x1;// 절편 계산
}

void CmfcCImageDlg::OnBnClickedBAction()
{
	if (m_image != NULL)
	{
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		if (fm != NULL)
		{
			drawCircle(fm, m_nStartX, m_nStartY, m_nRadius, 0xff);//clean
			GetCoord();
			calculateLineEquation(m_nStartX, m_nStartY, m_nEndX, m_nEndY);
			int count = 0;
			while ((m_nStartX != m_nEndX && m_dSlope!=0.0) || (m_dSlope==0.0 && m_nStartY != m_nEndY))
			{
				moveRect();
				saveImage(count++);
				Sleep(10);
			}
		}
	}
}


void CmfcCImageDlg::OnBnClickedBOpen()
{
	if (m_image != NULL)
		m_image.Destroy();

	CFileDialog fileDlg(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST, _T("Image Files (*.bmp; *.jpg; *.png)|*.bmp; *.jpg; *.png||"));

	// 파일 선택 대화 상자 표시
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();

		// 이미지 로드
		HRESULT hr = m_image.Load(filePath);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("이미지 로드에 실패했습니다."));
		}
		else
		{
			GetCenterData();
			UpdateDisplay();
		}
	}
}


void CmfcCImageDlg::OnEnChangeEStartX()
{
	int nStartX = GetDlgItemInt(IDC_E_START_X);
}


void CmfcCImageDlg::OnEnChangeEStartY()
{
	int nStartY = GetDlgItemInt(IDC_E_START_Y);
}


void CmfcCImageDlg ::UpdateDisplay()
{
	CClientDC dc(this);
	if(m_image)
		m_image.Draw(dc, m_borderWidth, 0,m_nWidth,m_nHeight);
}

void CmfcCImageDlg::GetCenterData()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();
	int nHeight = m_image.GetHeight();;
	int nWidth = m_image.GetWidth();

	int nTh = GRAY_COLOR;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	int nLeft= INT_MAX;
	int nRight = 0;
	int nTop = INT_MAX;
	int mBottom =0;

	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom;j++)
		for (int i = rect.left; i < rect.right;i++)
		{
			if (fm[j * nPitch + i] <= nTh)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
				if (nLeft > i)nLeft = i;
				if (nRight < i)nRight = i;

				if (nTop > i)nTop = j;
				if (mBottom < j)mBottom = j;
			}
		}

	if (nCount > 0)
	{
		double dCentorX = (double)nSumX / nCount;
		double dCentorY = (double)nSumY / nCount;

		cout << nLeft << ',' << nTop << "\t" << nRight <<"," << mBottom<< endl;

		cout << dCentorX << "\t" << dCentorY << endl;
	}
}


void CmfcCImageDlg::OnExitSizeMove()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnExitSizeMove();
	ChangeImageSize();
}
