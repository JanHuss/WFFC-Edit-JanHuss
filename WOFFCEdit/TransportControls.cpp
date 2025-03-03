#include "stdafx.h"
#include "TransportControls.h"

IMPLEMENT_DYNAMIC(TransportControls, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(TransportControls, CDialogEx)
	ON_COMMAND(IDOK, &TransportControls::End)					//ok button
	ON_BN_CLICKED(IDOK, &TransportControls::OnBnClickedOk)	
	ON_COMMAND(IDCANCEL, &TransportControls::End)
	ON_BN_CLICKED(IDCANCEL, &TransportControls::OnBnClickedCancel)
	ON_EN_CHANGE(ID_TRANSLATE_X, &TransportControls::OnChangedTranslateX)
	ON_EN_CHANGE(ID_TRANSLATE_Y, &TransportControls::OnChangedTranslateY)
	ON_EN_CHANGE(ID_TRANSLATE_Z, &TransportControls::OnChangedTranslateZ)
	ON_EN_CHANGE(ID_SCALE_X, &TransportControls::OnChangedScaleX)
	ON_EN_CHANGE(ID_SCALE_Y, &TransportControls::OnChangedScaleY)
	ON_EN_CHANGE(ID_SCALE_Z, &TransportControls::OnChangedScaleZ)
	ON_EN_CHANGE(ID_ROTATE_X, &TransportControls::OnChangedRotateX)
	ON_EN_CHANGE(ID_ROTATE_Y, &TransportControls::OnChangedRotateY)
	ON_EN_CHANGE(ID_ROTATE_Z, &TransportControls::OnChangedRotateZ)


END_MESSAGE_MAP()

TransportControls::TransportControls(CWnd* pParent, std::vector<SceneObject>* SceneGraph) 
	: CDialogEx(IDD_TRANSPORT, pParent)
{
	m_sceneGraph = SceneGraph;

}

TransportControls::TransportControls(CWnd* pParent)
	: CDialogEx(IDD_TRANSPORT, pParent)
{
}

TransportControls::~TransportControls()
{
}

void TransportControls::SetTransportDataToSelectedObject()
{
}

void TransportControls::DoDataExchange(CDataExchange* pDX)
{

}

void TransportControls::End()
{
	DestroyWindow();
}

void TransportControls::Select()
{

}

BOOL TransportControls::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(ID_TRANSLATE_X, _T("0.00"));
    SetDlgItemText(ID_TRANSLATE_Y, _T("0.00"));
    SetDlgItemText(ID_TRANSLATE_Z, _T("0.00"));
    SetDlgItemText(ID_SCALE_X, _T("0.00"));
    SetDlgItemText(ID_SCALE_Y, _T("0.00"));
    SetDlgItemText(ID_SCALE_Z, _T("0.00"));
    SetDlgItemText(ID_ROTATE_X, _T("0.00"));
    SetDlgItemText(ID_ROTATE_Y, _T("0.00"));
    SetDlgItemText(ID_ROTATE_Z, _T("0.00"));

	return TRUE;
}

void TransportControls::PostNcDestroy()
{
}

void TransportControls::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void TransportControls::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


// Transport Text Box
void TransportControls::OnChangedTranslateX()
{
	// float value passed through as a parameter, changing the current objects 
	// postion on the X axis
	CString strText;
    // Get the current text from the edit control.
    GetDlgItemText(ID_TRANSLATE_X, strText);

    // Convert the CString to a numeric value.
    // _tstof converts a CString to a double.
    double value = _tstof(strText);

    // Assign the value to your existing variable.
   	objectTranslateX = value;

	CString strScale;
    strScale.Format(_T("%.2f"), objectTranslateX);
	// Update the Scale X text block.
    SetDlgItemText(ID_SCALE_X, strScale);
}

void TransportControls::OnChangedTranslateY()
{
}

void TransportControls::OnChangedTranslateZ()
{
}

void TransportControls::OnChangedScaleX()
{
}

void TransportControls::OnChangedScaleY()
{
}

void TransportControls::OnChangedScaleZ()
{
}

void TransportControls::OnChangedRotateX()
{
}

void TransportControls::OnChangedRotateY()
{
}

void TransportControls::OnChangedRotateZ()
{
}

void TransportControls::OnObjectSelect()
{
	// function that will change the text box based on the 
	// selected objects translation,scaling and rotation
	//GetDlgItemText(hwndDlg, ID_TRANSLATE_X, numberRaw, sizeof(numberRaw));
	//swscanf_s(numberRaw, L"%d", &translateX);
	//// set scale x text box to the value of translate x for testing
	//SetDlgItemText(hwndDlg, ID_SCALE_X, numberRaw);
}

void TransportControls::UpdateTransportOnSelect()
{
		objectTranslateX = m_sceneGraph->at(index).posX;

		CString strTranslate;
		strTranslate.Format(_T("%.2f"), objectTranslateX);
		// Update the Scale X text block.
		SetDlgItemText(ID_TRANSLATE_X, strTranslate);
}

void TransportControls::UpdateIndexOnSelect(int i)
{
	index = i;
}

