
// MFC_P3View.cpp : CMFC_P3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_P3.h"
#endif

#include "MFC_P3Doc.h"
#include "MFC_P3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_P3View

IMPLEMENT_DYNCREATE(CMFC_P3View, CView)

BEGIN_MESSAGE_MAP(CMFC_P3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_P3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFC_P3View 构造/析构

CMFC_P3View::CMFC_P3View()
{
	// TODO: 在此处添加构造代码
	//m_memDC.CreateCompatibleDC(NULL); 
}

CMFC_P3View::~CMFC_P3View()
{
}

BOOL CMFC_P3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC_P3View 绘制

void CMFC_P3View::OnDraw(CDC* pDC)
{
	CMFC_P3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//CRect rect;
	//GetClientRect(&rect);
	//m_nWidth = rect.Width();
	//m_nHeight = rect.Height();
	//m_memDC.FillSolidRect(0,0,m_nWidth,m_nHeight,RGB(255,255,255)); 

	CTypedPtrList<CObList, CMFC_P3Entity*>& entityList = pDoc->m_entity;
	POSITION pos = entityList.GetHeadPosition();
	while(pos != NULL)
	{
		CMFC_P3Entity *pEntity = entityList.GetNext(pos);
		pEntity->DrawPointShape(pDC);
	}
}


// CMFC_P3View 打印


void CMFC_P3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_P3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC_P3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC_P3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFC_P3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC_P3View::OnLButtonUp(UINT /* nFlags */, CPoint point)
{
	if(GetCapture() != this)
	{
		return;
	}

	CPoint use[3] = {};
	m_endPoint = point;

	CMFC_P3Doc *pDoc = GetDocument();

	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
	switch(m_nType)
	{
	case RECTANGLE:
		dc.Rectangle(CRect(m_startPoint, m_endPoint));
		break;
	case CIRCLE:
		dc.Ellipse(CRect(m_startPoint, m_endPoint));
		break;
	case TRIANGLE:
		use[0].SetPoint(m_startPoint.x, m_endPoint.y);
		use[1] = m_endPoint;
		use[2].SetPoint((m_endPoint.x + m_startPoint.x) / 2, 
						  m_startPoint.y);
		dc.Polygon(use, 3);
		break;
	default:
		break;
	}

	/*m_memBitmap.CreateCompatibleBitmap(GetDC(),m_nWidth,m_nHeight); 
	CBitmap *pOldBit=m_memDC.SelectObject(&m_memBitmap); 

	switch(m_nType)
	{
	case RECTANGLE:
		m_memDC.Rectangle(CRect(m_startPoint, m_endPoint));
		break;
	case CIRCLE:
		m_memDC.Ellipse(CRect(m_startPoint, m_endPoint));
		break;
	case TRIANGLE:
		use[0].SetPoint(m_startPoint.x, m_endPoint.y);
		use[1] = m_endPoint;
		use[2].SetPoint((m_endPoint.x + m_startPoint.x) / 2, 
						  m_startPoint.y);
		m_memDC.Polygon(use, 3);
		break;
	default:
		break;
	}
	GetDC()->BitBlt(0,0,m_nWidth,m_nHeight,&m_memDC,0,0,SRCCOPY);
	m_memBitmap.DeleteObject(); */

	CMFC_P3EntityAtom *tmp = m_pEntity->NewEntityAtom();
	tmp->SetData(m_startPoint, m_endPoint, m_nType);
	m_pEntity->m_entityArray.AddTail(tmp);

	ReleaseCapture();
	return;
}

void CMFC_P3View::OnLButtonDown(UINT /* nFlags */, CPoint point)
{
	if(m_nType != RECTANGLE && m_nType != CIRCLE && m_nType != TRIANGLE)
	{
		return;
	}

	CMFC_P3Doc *pDoc = GetDocument();
	m_pEntity = pDoc->NewEntity();
	
	SetCapture();
	m_startPoint = point;
	return;
}

void CMFC_P3View::OnMouseMove(UINT /* nFlags */, CPoint point)
{
	if(GetCapture() != this)
	{
		return;
	}

	//Invalidate();

	/*CPoint use[3] = {};
	m_endPoint = point;

	CMFC_P3Doc *pDoc = GetDocument();

	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
	switch(m_nType)
	{
	case RECTANGLE:
		dc.Rectangle(CRect(m_startPoint, m_endPoint));
		break;
	case CIRCLE:
		dc.Ellipse(CRect(m_startPoint, m_endPoint));
		break;
	case TRIANGLE:
		use[0].SetPoint(m_startPoint.x, m_endPoint.y);
		use[1] = m_endPoint;
		use[2].SetPoint((m_endPoint.x + m_startPoint.x) / 2, 
						  m_startPoint.y);
		dc.Polygon(use, 3);
		break;
	default:
		break;
	}*/

	/*m_memBitmap.CreateCompatibleBitmap(GetDC(),m_nWidth,m_nHeight); 
	CBitmap *pOldBit=m_memDC.SelectObject(&m_memBitmap); 

	switch(m_nType)
	{
	case RECTANGLE:
		m_memDC.Rectangle(CRect(m_startPoint, m_endPoint));
		break;
	case CIRCLE:
		m_memDC.Ellipse(CRect(m_startPoint, m_endPoint));
		break;
	case TRIANGLE:
		use[0].SetPoint(m_startPoint.x, m_endPoint.y);
		use[1] = m_endPoint;
		use[2].SetPoint((m_endPoint.x + m_startPoint.x) / 2, 
						  m_startPoint.y);
		m_memDC.Polygon(use, 3);
		break;
	default:
		break;
	}
	GetDC()->BitBlt(0,0,m_nWidth,m_nHeight,&m_memDC,0,0,SRCCOPY);
	m_memBitmap.DeleteObject(); */

	return;
}


void CMFC_P3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC_P3View 诊断

#ifdef _DEBUG
void CMFC_P3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_P3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_P3Doc* CMFC_P3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_P3Doc)));
	return (CMFC_P3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_P3View 消息处理程序