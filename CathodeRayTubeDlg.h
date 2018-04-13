
// CathodeRayTubeDlg.h: файл заголовка
//

#pragma once
#include "CModelDraw.h"
#include "afxcmn.h"


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


private:
	void InitializeModelPicture();
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl sliderCathod;
};
