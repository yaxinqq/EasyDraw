
// MFC_P3Doc.h : CMFC_P3Doc 类的接口
//


#pragma once

#define RECTANGLE 1
#define CIRCLE 2
#define TRIANGLE 3

// 自定义的文件存储类
class CMFC_P3EntityAtom : public CObject
{
public:
	CMFC_P3EntityAtom();
protected:
	DECLARE_SERIAL(CMFC_P3EntityAtom);
public:
	CArray<CPoint, CPoint> m_pointArray;
	int m_nType;
	virtual void Serialize(CArchive &ar);
	void SetData(CPoint startPoint, CPoint endPoint, int nType);
	CPoint GetStartPoint();
	CPoint GetEndPoint();
	int GetType();
};

class CMFC_P3Entity : public CObject
{
public:
	CMFC_P3Entity();
protected:
	DECLARE_SERIAL(CMFC_P3Entity);
public:
	//CArray<CMFC_P3EntityAtom, CMFC_P3EntityAtom> m_entityArray;
	CTypedPtrList<CObList, CMFC_P3EntityAtom*> m_entityArray;
	BOOL DrawPointShape(CDC *pDC);
	void AddEntityAtom(CMFC_P3EntityAtom &atom);
	CMFC_P3EntityAtom* NewEntityAtom();
	//BOOL DrawPointCircle(CDC *pDC);
	//BOOL DrawPointTriangle(CDC *pDC);
	virtual void Serialize(CArchive &ar);
};

//MFC Auto Doc
class CMFC_P3Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFC_P3Doc();
	DECLARE_DYNCREATE(CMFC_P3Doc)

// 特性
protected:
	CPen m_pen;
public:
	CTypedPtrList<CObList, CMFC_P3Entity*> m_entity;
	CPen* GetCurrentPen() {return &m_pen;}
	int nType;

// 操作
public:
	CMFC_P3Entity* NewEntity();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFC_P3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
