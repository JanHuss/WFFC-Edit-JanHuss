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
	void SetObjectData(std::vector<SceneObject>* SceneGraph, int * Selection);	//passing in pointers to the data the class will operate on.

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSPORT };
#endif

	float objectTranslateX;
	float objectTranslateY;
	float objectTranslateZ;

	void SetTransportDataToSelectedObject();

	void UpdateIndexOnSelect(int i);


protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedApply();
	
	afx_msg void OnChangedTranslateX();
	afx_msg void OnChangedTranslateY();
	afx_msg void OnChangedTranslateZ();

	void OnObjectSelect();
	void UpdateTransportOnSelect();

	afx_msg void End();		//kill the dialogue
	afx_msg void Select();	//Item has been selected




	public:
	// Control variable for more efficient access of the listbox
	CListBox m_listBox;

	// Transport changes
	afx_msg void OnChangedScaleX();
	afx_msg void OnChangedScaleY();
	afx_msg void OnChangedScaleZ();
	afx_msg void OnChangedRotateX();
	afx_msg void OnChangedRotateY();
	afx_msg void OnChangedRotateZ();

	

private:

	std::vector<SceneObject> * m_sceneGraph;
	int * m_currentSelection;
	int index;
};
INT_PTR CALLBACK TransportProc( HWND   hwndDlg,UINT   uMsg,WPARAM wParam,LPARAM lParam);
