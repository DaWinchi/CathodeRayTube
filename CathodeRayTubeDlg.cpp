
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

CRITICAL_SECTION cs;

CCathodeRayTubeDlg::CCathodeRayTubeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CATHODERAYTUBE_DIALOG, pParent)
	, timeStep(7e-7)
	, countGeneratedParticles(2)
	, Ucathod(-1e+8)
	, Uanod(1e+8)
	, Ucond(1e+8)
	, countIterat(300)
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
	DDX_Text(pDX, IDC_STEP_TIME, timeStep);
	DDX_Control(pDX, IDC_COUNT, textCountPoints);
	DDX_Text(pDX, IDC_STEP_GENERATE_COUNT, countGeneratedParticles);
	DDV_MinMaxInt(pDX, countGeneratedParticles, 0, 1000000000);
	DDX_Text(pDX, IDC_CATHOD, Ucathod);
	DDX_Text(pDX, IDC_ANOD, Uanod);
	DDX_Control(pDX, IDC_GRAPH, graphPicture);
	DDX_Text(pDX, IDC_CONDUCTOR, Ucond);
	DDX_Control(pDX, IDC_GRAPH2, conductorPicture);
	DDX_Text(pDX, IDC_CONDUCTOR2, countIterat);
}

BEGIN_MESSAGE_MAP(CCathodeRayTubeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RUN, &CCathodeRayTubeDlg::OnBnClickedRun)
	ON_EN_CHANGE(IDC_STEP_TIME, &CCathodeRayTubeDlg::OnEnChangeStepTime)
	ON_EN_CHANGE(IDC_STEP_GENERATE_COUNT, &CCathodeRayTubeDlg::OnEnChangeStepGenerateCount)
	ON_EN_CHANGE(IDC_CATHOD, &CCathodeRayTubeDlg::OnEnChangeCathod)
	ON_EN_CHANGE(IDC_ANOD, &CCathodeRayTubeDlg::OnEnChangeAnod)
	ON_BN_CLICKED(IDC_STOP, &CCathodeRayTubeDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_UPDATE, &CCathodeRayTubeDlg::OnBnClickedUpdate)
	ON_EN_CHANGE(IDC_CONDUCTOR, &CCathodeRayTubeDlg::OnEnChangeConductor)
	ON_EN_CHANGE(IDC_CONDUCTOR2, &CCathodeRayTubeDlg::OnEnChangeConductor2)
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
	InitializeCriticalSection(&cs);
	InitializeModelPicture();
	InitializeGraphicPicture();
	InitializeConductorPicture();
	modelPicture.Update();
	graphPicture.Update();

	calculate = new CCalculate(&points, &pointsGraph, &pointsCondTop, &pointsCondBottom);
	calculate->countGneratepoints = countGeneratedParticles;
	calculate->cathod = &cathod;
	calculate->globalRectangle = &globalRectangle;
	calculate->anodTop = &anodUp;
	calculate->anodBottom = &anodBottom;
	calculate->conductorTop = &conductorTop;
	calculate->conductorBottom = &conductorBottom;

	calculate->v = countIterat;

	calculate->Ucat = Ucathod;
	calculate->Uan = Uanod;
	calculate->Uampl_cond = Ucond;
	calculate->Ucon1 = Ucond;
	calculate->Ucon2 = -Ucond;
	
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

	modelPicture.xmax = 0.2;
	modelPicture.xmin = -0.01;
	modelPicture.ymax = 0.025;
	modelPicture.ymin = -0.025;
	globalRectangle.x = -0.005;
	globalRectangle.y = 0.02;
	globalRectangle.width = 0.2;
	globalRectangle.height = 0.04;

	cathod.x = -0.002;
	cathod.y = 0.005;
	cathod.width = 0.002;
	cathod.height = 0.01;

	anodUp.x = 0.06;
	anodUp.y = globalRectangle.y;
	anodUp.width = 0.001;
	anodUp.height = 0.017;

	anodBottom.x = 0.060;	
	anodBottom.width = 0.001;
	anodBottom.height = anodUp.height;
	anodBottom.y = -globalRectangle.height/2 +anodBottom.height;

	conductorTop.x = 0.125;
	conductorTop.y = globalRectangle.y + 0.002;
	conductorTop.width = 0.04;
	conductorTop.height = 0.002;

	conductorBottom.x = 0.125;
	conductorBottom.y = globalRectangle.y - globalRectangle.height;
	conductorBottom.width = 0.04;
	conductorBottom.height = 0.002;

	sliderCathod.SetRange(1, globalRectangle.height/2*1000);
	sliderCathod.SetPos(cathod.width*1000);
	sliderCathod.SetTicFreq(10);

	sliderAnodHeight.SetRange(1, globalRectangle.height / 2*1000);
	sliderAnodHeight.SetPos(anodUp.height*1000);
	sliderAnodHeight.SetTicFreq(10);

	sliderConductor.SetRange(1, 75/2);
	sliderConductor.SetPos(conductorBottom.width/2*1000);
	sliderConductor.SetTicFreq(10);
	
	modelPicture.globalRectangle = &globalRectangle;
	modelPicture.cathod = &cathod;
	modelPicture.anod1 = &anodUp;
	modelPicture.anod2 = &anodBottom;
	modelPicture.conductorTop = &conductorTop;
	modelPicture.conductorBottom = &conductorBottom;
}


void CCathodeRayTubeDlg::InitializeConductorPicture()
{
	conductorPicture.pointsTop = &pointsCondTop;
	conductorPicture.pointsBottom = &pointsCondBottom;	

	conductorPicture.xmax = globalRectangle.height / 2;
	conductorPicture.xmin = -globalRectangle.height / 2;
	conductorPicture.ymax = 10.f;
	conductorPicture.ymin = -10.f;
	conductorPicture.step_x = globalRectangle.height / 10;
	conductorPicture.step_y = 3.f;

}

void CCathodeRayTubeDlg::InitializeGraphicPicture()
{
	graphPicture.points = &pointsGraph;

	graphPicture.xmax = globalRectangle.height / 2;
	graphPicture.xmin = -globalRectangle.height / 2;
	graphPicture.ymax = 10.f;
	graphPicture.ymin = -1.f;
	graphPicture.step_x = globalRectangle.height / 10;
	graphPicture.step_y = 3.f;
}
void CCathodeRayTubeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (pScrollBar == (CScrollBar *)&sliderCathod)
	{
		int value = sliderCathod.GetPos();
		cathod.y = (double)value/1000;
		cathod.height = (double)(value/1000.f * 2.f);
		modelPicture.Update();
	}

	if (pScrollBar == (CScrollBar *)&sliderAnodHeight)
	{
		int value = sliderAnodHeight.GetPos();
		anodUp.height = (double)value/1000.f;
		anodBottom.height = anodUp.height;
		anodBottom.y = -globalRectangle.height / 2.f + anodBottom.height;
		modelPicture.Update();
	}

	if (pScrollBar == (CScrollBar *)&sliderConductor)
	{
		int value = sliderConductor.GetPos();
		conductorBottom.x = conductorBottom.x + conductorBottom.width/2;
		conductorBottom.x = conductorBottom.x -value/1000.f;
		conductorBottom.width = 2.f * value/1000.f;
		conductorTop.x = conductorTop.x + conductorTop.width/2;
		conductorTop.x = conductorTop.x - value/1000.f;
		conductorTop.width = 2.f * value/1000.f;
		modelPicture.Update();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCathodeRayTubeDlg::OnBnClickedRun()
{
	calculate->CalculateInit(0.0000000000000004);	
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
		EnterCriticalSection(&cs);
		dlg->calculate->CalculateSystem(dlg->timeStep);	
		LeaveCriticalSection(&cs);

		dlg->modelPicture.RedrawWindow();	
		dlg->graphPicture.RedrawWindow();
		dlg->conductorPicture.RedrawWindow();
		
		CString str;
		str.Format(TEXT("%d"), dlg->points.size());
		dlg->textCountPoints.SetWindowTextW(str);
	}
	return 0;
}

void CCathodeRayTubeDlg::OnEnChangeStepTime()
{
	UpdateData(TRUE);	
}


void CCathodeRayTubeDlg::OnEnChangeStepGenerateCount()
{
	UpdateData(TRUE);
	EnterCriticalSection(&cs);
	calculate->countGneratepoints = countGeneratedParticles;
	LeaveCriticalSection(&cs);
}


void CCathodeRayTubeDlg::OnEnChangeCathod()
{
	UpdateData(TRUE);
	EnterCriticalSection(&cs);
	calculate->Ucat = Ucathod;
	LeaveCriticalSection(&cs);
}


void CCathodeRayTubeDlg::OnEnChangeAnod()
{
	UpdateData(TRUE);
	EnterCriticalSection(&cs);
	calculate->Uan = Uanod;
	LeaveCriticalSection(&cs);
}


void CCathodeRayTubeDlg::OnBnClickedStop()
{
	TerminateThread(hThreadCalculate, pdwThreadCalculate);
	//DeleteCriticalSection(&cs);
}

BOOL CCathodeRayTubeDlg::DestroyWindow()
{
	TerminateThread(hThreadCalculate, pdwThreadCalculate);
	return -1;
}

void CCathodeRayTubeDlg::OnBnClickedUpdate()
{
	EnterCriticalSection(&cs);
	pointsGraph.clear();
	pointsCondTop.clear();
	pointsCondBottom.clear();
	conductorPicture.xmax = 0;
	graphPicture.xmax = 0;
	calculate->alltime = timeStep;


	LeaveCriticalSection(&cs);
}


void CCathodeRayTubeDlg::OnEnChangeConductor()
{
	UpdateData(TRUE);
	EnterCriticalSection(&cs);
	calculate->Uampl_cond = Ucond;	
	LeaveCriticalSection(&cs);
}


void CCathodeRayTubeDlg::OnEnChangeConductor2()
{
	UpdateData(TRUE);
	EnterCriticalSection(&cs);
	calculate->v = countIterat;
	LeaveCriticalSection(&cs);
}
