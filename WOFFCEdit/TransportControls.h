#pragma once

#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>

class TransportControls: public CDialogEx
{
	DECLARE_DYNAMIC(TransportControls)

public:
	TransportControls(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
	TransportControls(CWnd* pParent = NULL);
	virtual ~TransportControls();
	void SetTransportDataToSelectedObject();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void Select();	//Item has been selected

	std::vector<SceneObject> * m_sceneGraph;
	int * m_currentSelection;


	DECLARE_MESSAGE_MAP()

	public:
	// Control variable for more efficient access of the listbox
	CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	// Transport changes
	afx_msg void OnChangedTranslateX();
	afx_msg void OnChangedTranslateY();
	afx_msg void OnChangedTranslateZ();
	afx_msg void OnChangedScaleX();
	afx_msg void OnChangedScaleY();
	afx_msg void OnChangedScaleZ();
	afx_msg void OnChangedRotateX();
	afx_msg void OnChangedRotateY();
	afx_msg void OnChangedRotateZ();

	// on selecting an object
	void OnObjectSelect();
	void UpdateTransportOnSelect();
	void UpdateIndexOnSelect(int i);

private:
	float objectTranslateX;
	float objectTranslateY;
	float objectTranslateZ;

	int index;
};
INT_PTR CALLBACK TransportProc( HWND   hwndDlg,UINT   uMsg,WPARAM wParam,LPARAM lParam);
