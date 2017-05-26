
// KinectCalibrationDoc.h : CKinectCalibrationDoc ��Ľӿ�
//


#pragma once

class COpenGL;
class CKinectCalibrationView;
class CKinectCalibrationDoc : public CDocument
{
protected: // �������л�����
	CKinectCalibrationDoc();
	DECLARE_DYNCREATE(CKinectCalibrationDoc)

// ����
public:
	COpenGL *m_nDocOpenGL;
	CKinectCalibrationView* pView;
// ����
public:
	//afx_msg void OnFileOpen();
	CView* GetView(CRuntimeClass *pViewClass);
	void ViewReadSysInfo();
	void ViewChangeMatrix(CString filename);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CKinectCalibrationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnSetParam();
};
