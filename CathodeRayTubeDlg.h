
// CathodeRayTubeDlg.h: файл заголовка
//

#pragma once
#include "CModelDraw.h"
#include "CGraphic.h"
#include "afxcmn.h"
#include "CCalculate.h"
#include "afxwin.h"
#include "CConductorValueGraph.h"

// Диалоговое окно CCathodeRayTubeDlg
class CCathodeRayTubeDlg : public CDialog
{
// Создание
public:
	CCathodeRayTubeDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CATHODERAYTUBE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CModelDraw modelPicture;

	RectangleObject globalRectangle;
	RectangleObject cathod;
	RectangleObject anodUp;
	RectangleObject anodBottom;
	RectangleObject conductorTop;
	RectangleObject conductorBottom;

	CCalculate *calculate;


	vector<PointEl> points;
	vector<PointF> pointsGraph;
	vector<PointF> pointsCondTop;
	vector<PointF> pointsCondBottom;

	HANDLE hThreadCalculate;
	DWORD pdwThreadCalculate;

private:
	void InitializeModelPicture();
	void InitializeGraphicPicture();
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl sliderCathod;
	CSliderCtrl sliderAnodHeight;
	CSliderCtrl sliderConductor;
	afx_msg void OnBnClickedRun();
	double timeStep;
	afx_msg void OnEnChangeStepTime();
	CStatic textCountPoints;
	int countGeneratedParticles;
	afx_msg void OnEnChangeStepGenerateCount();
	double Ucathod;
	double Uanod;
	afx_msg void OnEnChangeCathod();
	afx_msg void OnEnChangeAnod();
	afx_msg void OnBnClickedStop();
	BOOL DestroyWindow();
	CGraphic graphPicture;
	afx_msg void OnBnClickedUpdate();
	double Ucond;
	afx_msg void OnEnChangeConductor();
	void InitializeConductorPicture();
	CConductorValueGraph conductorPicture;
	double countIterat;
	afx_msg void OnEnChangeConductor2();
};

DWORD WINAPI ThreadCalculate(PVOID param);
