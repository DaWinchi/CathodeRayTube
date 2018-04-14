
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
	DDX_Control(pDX, IDC_SLIDER_ANOD, sliderAnodHeight);
	DDX_Control(pDX, IDC_SLIDER_CONDUCTOR, sliderConductor);
}

BEGIN_MESSAGE_MAP(CCathodeRayTubeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RUN, &CCathodeRayTubeDlg::OnBnClickedRun)
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

	calculate = new CCalculate(&points);
	calculate->countGneratepoints = 1;
	calculate->cathod = &cathod;
	
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
	modelPicture.points = &points;

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

	conductorTop.x = 125;
	conductorTop.y = globalRectangle.y + 2;
	conductorTop.width = 40;
	conductorTop.height = 2;

	conductorBottom.x = 125;
	conductorBottom.y = globalRectangle.y - globalRectangle.height;
	conductorBottom.width = 40;
	conductorBottom.height = 2;

	sliderCathod.SetRange(1, globalRectangle.height/2);
	sliderCathod.SetPos(cathod.width);
	sliderCathod.SetTicFreq(10);

	sliderAnodHeight.SetRange(1, globalRectangle.height / 2);
	sliderAnodHeight.SetPos(anodUp.height);
	sliderAnodHeight.SetTicFreq(10);

	sliderConductor.SetRange(1, 75/2);
	sliderConductor.SetPos(conductorBottom.width/2);
	sliderConductor.SetTicFreq(10);
	
	modelPicture.globalRectangle = &globalRectangle;
	modelPicture.cathod = &cathod;
	modelPicture.anod1 = &anodUp;
	modelPicture.anod2 = &anodBottom;
	modelPicture.conductorTop = &conductorTop;
	modelPicture.conductorBottom = &conductorBottom;
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

	if (pScrollBar == (CScrollBar *)&sliderAnodHeight)
	{
		int value = sliderAnodHeight.GetPos();
		anodUp.height = value;
		anodBottom.height = anodBottom.height = anodUp.height;
		anodBottom.y = -globalRectangle.height / 2 + anodBottom.height;
		modelPicture.Update();
	}

	if (pScrollBar == (CScrollBar *)&sliderConductor)
	{
		int value = sliderConductor.GetPos();
		conductorBottom.x = conductorBottom.x + conductorBottom.width/2;
		conductorBottom.x = conductorBottom.x -value;
		conductorBottom.width = 2 * value;
		conductorTop.x = conductorTop.x + conductorTop.width/2;
		conductorTop.x = conductorTop.x - value;
		conductorTop.width = 2 * value;
		modelPicture.Update();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCathodeRayTubeDlg::OnBnClickedRun()
{
	hThreadCalculate = CreateThread(
		NULL,		// дескриптор защиты
		0,			// начальный размер стека ( Если это значение нулевое, новый поток использует по умолчанию размер стека исполняемой программы)
		(LPTHREAD_START_ROUTINE)ThreadCalculate,	 // функция потока
		this,		// параметр потока 
		0,			//oпции создания(здесь можно отложить запуск выполнения потока. Для запуска потока сразу же, передаём 0.)
		&pdwThreadCalculate);// идентификатор потока (указатель на переменную, куда будет сохранён идентификатор потока)


	
}

DWORD WINAPI ThreadCalculate(PVOID param)
{
	CCathodeRayTubeDlg *dlg = (CCathodeRayTubeDlg*)param;
	while (true)
	{
		dlg->calculate->CalculateSystem(0.0000000000000004);
		dlg->modelPicture.Update();
	}
	return 0;
}