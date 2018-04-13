
// CathodeRayTubeDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "CathodeRayTube.h"
#include "CathodeRayTubeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CCathodeRayTubeDlg



CCathodeRayTubeDlg::CCathodeRayTubeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CATHODERAYTUBE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCathodeRayTubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODEL_PIC, modelPicture);
	DDX_Control(pDX, IDC_SLIDER_CATHOD, sliderCathod);
}

BEGIN_MESSAGE_MAP(CCathodeRayTubeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений CCathodeRayTubeDlg

BOOL CCathodeRayTubeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	
	InitializeModelPicture();
	modelPicture.Update();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCathodeRayTubeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCathodeRayTubeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCathodeRayTubeDlg::InitializeModelPicture()
{
	modelPicture.xmax = 200;
	modelPicture.xmin = -10;
	modelPicture.ymax = 25;
	modelPicture.ymin = -25;
	globalRectangle.x = -5;
	globalRectangle.y = 20;
	globalRectangle.width = 200;
	globalRectangle.height = 40;

	cathod.x = -2;
	cathod.y = 10;
	cathod.width = 2;
	cathod.height = 20;

	anodUp.x = 30;
	anodUp.y = globalRectangle.y;
	anodUp.width = 1;
	anodUp.height = 10;

	anodBottom.x = 30;	
	anodBottom.width = 1;
	anodBottom.height = anodUp.height;
	anodBottom.y = -globalRectangle.height/2 +anodBottom.height;

	sliderCathod.SetRange(1, globalRectangle.height/2);
	sliderCathod.SetPos(cathod.width);
	sliderCathod.SetTicFreq(10);

	
	modelPicture.globalRectangle = &globalRectangle;
	modelPicture.cathod = &cathod;
	modelPicture.anod1 = &anodUp;
	modelPicture.anod2 = &anodBottom;
}

void CCathodeRayTubeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (pScrollBar == (CScrollBar *)&sliderCathod)
	{
		int value = sliderCathod.GetPos();
		cathod.y = value;
		cathod.height = value * 2;
		modelPicture.Update();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
