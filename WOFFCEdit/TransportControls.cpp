#include "stdafx.h"
#include "TransportControls.h"

IMPLEMENT_DYNAMIC(TransportControls, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(TransportControls, CDialogEx)
	ON_COMMAND(IDOK, &TransportControls::End)					//ok button
	ON_BN_CLICKED(IDOK, &TransportControls::OnBnClickedOk)	
	ON_COMMAND(IDCANCEL, &TransportControls::End)
	ON_BN_CLICKED(IDCANCEL, &TransportControls::OnBnClickedCancel)
	ON_BN_CLICKED(IDAPPLY, &TransportControls::OnBnClickedApply)
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
	: CDialogEx(IDD_TRANSPORT, pParent), m_sceneGraph(SceneGraph), index(0)
{
	objectTranslateX = 0.0f;
	objectTranslateY = 0.0f;
	objectTranslateZ = 0.0f;
	objectScaleX = 0.0f;
	objectScaleY = 0.0f;
	objectScaleZ = 0.0f;
	objectRotateX = 0.0f;
	objectRotateY = 0.0f;
	objectRotateZ = 0.0f;

}

TransportControls::TransportControls(CWnd* pParent)
	: CDialogEx(IDD_TRANSPORT, pParent), m_sceneGraph(nullptr), index(0)
{
	objectTranslateX = 0.0f;
	objectTranslateY = 0.0f;
	objectTranslateZ = 0.0f;
	objectScaleX = 0.0f;
	objectScaleY = 0.0f;
	objectScaleZ = 0.0f;
	objectRotateX = 0.0f;
	objectRotateY = 0.0f;
	objectRotateZ = 0.0f;
}

TransportControls::~TransportControls()
{

}

void TransportControls::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	if(m_currentSelection)
		UpdateIndexOnSelect(*m_currentSelection);

}

void TransportControls::SetTransportDataToSelectedObject()
{
}

void TransportControls::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// Binding edit controls to transport variables
	DDX_Text(pDX, ID_TRANSLATE_X, objectTranslateX);
	DDX_Text(pDX, ID_TRANSLATE_Y, objectTranslateY);
	DDX_Text(pDX, ID_TRANSLATE_Z, objectTranslateZ);
	DDX_Text(pDX, ID_SCALE_X, objectScaleX);
	DDX_Text(pDX, ID_SCALE_Y, objectScaleY);
	DDX_Text(pDX, ID_SCALE_Z, objectScaleZ);
	DDX_Text(pDX, ID_ROTATE_X, objectRotateX);
	DDX_Text(pDX, ID_ROTATE_Y, objectRotateY);
	DDX_Text(pDX, ID_ROTATE_Z, objectRotateZ);

	// setting up min/max range for text boxes
	DDV_MinMaxFloat(pDX, objectTranslateX, -500.0f, 500.0f);
	DDV_MinMaxFloat(pDX, objectTranslateY, -500.0f, 500.0f);
	DDV_MinMaxFloat(pDX, objectTranslateZ, -500.0f, 500.0f);

}

void TransportControls::End()
{
	// set flag here to tell that mouse picking is allowed
	onEndFunctionCall = true;
	_openedWithCmd = false;
	DestroyWindow();
}

void TransportControls::Select()
{

}

BOOL TransportControls::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_sceneGraph && index >= 0 && index < m_sceneGraph->size())
	{
		SceneObject selectedObject = (*m_sceneGraph)[index];
		objectTranslateX = selectedObject.posX;
		objectTranslateY = selectedObject.posY;
		objectTranslateZ = selectedObject.posZ;
		objectScaleX = selectedObject.scaX;
		objectScaleY = selectedObject.scaY;
		objectScaleZ = selectedObject.scaZ;
		objectRotateX = selectedObject.rotX;
		objectRotateY = selectedObject.rotY;
		objectRotateZ = selectedObject.rotZ;
	}
	else
	{
		objectTranslateX = 0.0f;
		objectTranslateY = 0.0f;
		objectTranslateZ = 0.0f;
		objectScaleX = 0.0f;
		objectScaleY = 0.0f;
		objectScaleZ = 0.0f;
		objectRotateX = 0.0f;
		objectRotateY = 0.0f;
		objectRotateZ = 0.0f;
	}

	UpdateData(FALSE);

	return TRUE;
}

void TransportControls::PostNcDestroy()
{
	// set m_transportControlsActive = false; here
	CDialogEx::PostNcDestroy();
}

void TransportControls::OnBnClickedOk()
{
	//GetDlgItem(ID_TRANSLATE_X)->SetFocus();

	if (UpdateData(TRUE))
	{
		 // Update the selected object's translate values.
        if (m_sceneGraph != nullptr && index >= 0 && index < (int)m_sceneGraph->size())
        {
            (*m_sceneGraph)[index].posX = objectTranslateX;
            (*m_sceneGraph)[index].posY = objectTranslateY;
            (*m_sceneGraph)[index].posZ = objectTranslateZ;

			(*m_sceneGraph)[index].scaX = objectScaleX;
            (*m_sceneGraph)[index].scaY = objectScaleY;
            (*m_sceneGraph)[index].scaZ = objectScaleZ;

			(*m_sceneGraph)[index].rotX = objectRotateX;
            (*m_sceneGraph)[index].rotY = objectRotateY;
            (*m_sceneGraph)[index].rotZ = objectRotateZ;
        }
		CDialogEx::OnOK();
	}

}

void TransportControls::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void TransportControls::OnBnClickedApply()
{
	if (UpdateData(TRUE))
	{
	 // Update the selected object's translate values.
        if (m_sceneGraph != nullptr && index >= 0 && index < (int)m_sceneGraph->size())
        {
            (*m_sceneGraph)[index].posX = objectTranslateX;
            (*m_sceneGraph)[index].posY = objectTranslateY;
            (*m_sceneGraph)[index].posZ = objectTranslateZ;

			(*m_sceneGraph)[index].scaX = objectScaleX;
			(*m_sceneGraph)[index].scaY = objectScaleY;
			(*m_sceneGraph)[index].scaZ = objectScaleZ;

			(*m_sceneGraph)[index].rotX = objectRotateX;
			(*m_sceneGraph)[index].rotY = objectRotateY;
			(*m_sceneGraph)[index].rotZ = objectRotateZ;
        }
	}
	onEndFunctionCall = true;
}


// Transport Text Box
void TransportControls::OnChangedTranslateX()
{
	CString strText;
    GetDlgItemText(ID_TRANSLATE_X, strText);
    double value = _tstof(strText);
    objectTranslateX = (float)value;

   //CString strDisplay;
   //strDisplay.Format(_T("%.2f"), objectTranslateX);
   //SetDlgItemText(ID_TRANSLATE_X, strDisplay);
}

void TransportControls::OnChangedTranslateY()
{
	CString strText;
    GetDlgItemText(ID_TRANSLATE_Y, strText);
    double value = _tstof(strText);
    objectTranslateY = (float)value;

  //CString strDisplay;
  //strDisplay.Format(_T("%.2f"), objectTranslateY);
  //SetDlgItemText(ID_TRANSLATE_Y, strDisplay);
}

void TransportControls::OnChangedTranslateZ()
{
	CString strText;
    GetDlgItemText(ID_TRANSLATE_Z, strText);
    double value = _tstof(strText);
    objectTranslateZ = (float)value;

    //CString strDisplay;
    //strDisplay.Format(_T("%.2f"), objectTranslateZ);
    //SetDlgItemText(ID_TRANSLATE_Z, strDisplay);
}

void TransportControls::OnChangedScaleX()
{
	CString strText;
    GetDlgItemText(ID_SCALE_X, strText);
    double value = _tstof(strText);
    objectScaleX = (float)value;
}

void TransportControls::OnChangedScaleY()
{
	CString strText;
    GetDlgItemText(ID_SCALE_Y, strText);
    double value = _tstof(strText);
    objectScaleY = (float)value;
}

void TransportControls::OnChangedScaleZ()
{
	CString strText;
    GetDlgItemText(ID_SCALE_Z, strText);
    double value = _tstof(strText);
    objectScaleZ = (float)value;
}

void TransportControls::OnChangedRotateX()
{
	CString strText;
    GetDlgItemText(ID_ROTATE_X, strText);
    double value = _tstof(strText);
    objectRotateX = (float)value;
}

void TransportControls::OnChangedRotateY()
{
	CString strText;
    GetDlgItemText(ID_ROTATE_Y, strText);
    double value = _tstof(strText);
    objectRotateY = (float)value;
}

void TransportControls::OnChangedRotateZ()
{
	CString strText;
    GetDlgItemText(ID_ROTATE_Z, strText);
    double value = _tstof(strText);
    objectRotateZ= (float)value;
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
	if (m_sceneGraph != nullptr && index >= 0 && index < (int)m_sceneGraph->size())
    {
        objectTranslateX = (*m_sceneGraph)[index].posX;
        objectTranslateY = (*m_sceneGraph)[index].posY;
        objectTranslateZ = (*m_sceneGraph)[index].posZ;
		objectScaleX = (*m_sceneGraph)[index].scaX;
        objectScaleY = (*m_sceneGraph)[index].scaY;
        objectScaleZ = (*m_sceneGraph)[index].scaZ;
		objectRotateX = (*m_sceneGraph)[index].rotX;
        objectRotateY = (*m_sceneGraph)[index].rotY;
        objectRotateZ = (*m_sceneGraph)[index].rotZ;


		UpdateData(FALSE);

        //CString strTranslate;
        //strTranslate.Format(_T("%.2f"), objectTranslateX);
        //SetDlgItemText(ID_TRANSLATE_X, strTranslate);

    }
}

void TransportControls::UpdateIndexOnSelect(int i)
{
	index = i;
}

