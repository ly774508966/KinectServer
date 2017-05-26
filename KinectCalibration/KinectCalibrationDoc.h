
// KinectCalibrationDoc.h : CKinectCalibrationDoc 类的接口
//


#pragma once

class COpenGL;
class CKinectCalibrationView;
class CKinectCalibrationDoc : public CDocument
{
protected: // 仅从序列化创建
	CKinectCalibrationDoc();
	DECLARE_DYNCREATE(CKinectCalibrationDoc)

// 特性
public:
	COpenGL *m_nDocOpenGL;
	CKinectCalibrationView* pView;
// 操作
public:
	//afx_msg void OnFileOpen();
	CView* GetView(CRuntimeClass *pViewClass);
	void ViewReadSysInfo();
	void ViewChangeMatrix(CString filename);
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CKinectCalibrationDoc();
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
public:
	afx_msg void OnSetParam();
};
