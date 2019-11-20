
// MFC_P3View.h : CMFC_P3View 类的接口
//

#pragma once
#include "MFC_P3Doc.h"

class CMFC_P3View : public CView
{
protected: // 仅从序列化创建
	CMFC_P3View();
	DECLARE_DYNCREATE(CMFC_P3View);

// 特性
public:
	CMFC_P3Doc* GetDocument() const;

protected:
	CPoint m_startPoint;
	CPoint m_endPoint;
	int m_nType;
	CMFC_P3Entity* m_pEntity;

	//CDC m_memDC;
	//CBitmap m_memBitmap;
	//int m_nWidth;
	//int m_nHeight;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFC_P3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void SetDrawType(int nType){m_nType = nType;}

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFC_P3View.cpp 中的调试版本
inline CMFC_P3Doc* CMFC_P3View::GetDocument() const
   { return reinterpret_cast<CMFC_P3Doc*>(m_pDocument); }
#endif

