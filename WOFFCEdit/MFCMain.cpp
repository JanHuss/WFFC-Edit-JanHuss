#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT, &MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_EDIT_TRANSPORTCONTROLS, &MFCMain::MenuEditTransport)
	ON_COMMAND(ID_BUTTON40001, &MFCMain::ToolBarButton1)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(NULL,
		_T("World Of Flim-Flam Craft Editor"),
		WS_OVERLAPPEDWINDOW,
		CRect(100, 100, 1024, 768),
		NULL,
		NULL,
		0,
		NULL
	);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width = WindowRECT.Width();
	m_height = WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{
			//int ID = m_ToolSystem.getCurrentSelectionID();
			std::vector<int> ID = m_ToolSystem.getCurrentSelectionIDs();
			std::wstring statusString = L"Selected amount of Objects: " + std::to_wstring(ID.size());
			//std::wstring statusString = L"shift bool is: " + std::to_wstring(m_ToolSystem.getBool());
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);
		}
		// if dialog box end is true then set the dialog box to false
		if (m_TransportControls.onEndFunctionCall)
		{
			m_TransportControls.onEndFunctionCall = false;
			m_ToolSystem.m_d3dRenderer.setDialogBoxOpen(false);
			m_ToolSystem.m_d3dRenderer.BuildDisplayList(m_TransportControls.m_sceneGraph);
		}
		// keyboard command transport controls
		if (m_ToolSystem.m_toolInputCommands.openTransport == true && m_TransportControls._openedWithCmd == false)
		{
			m_TransportControls._openedWithCmd = true;
			MenuEditTransport();
		}
			

	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::MenuEditTransport()
{
	m_TransportControls.Create(IDD_TRANSPORT);	//Start up modeless
	m_TransportControls.ShowWindow(SW_SHOW);	//show modeless
	m_TransportControls.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
	updateIndexOnSelect();
	m_TransportControls.onEndFunctionCall = false;
	//m_TransportControls._openedWithCmd = false;
	m_ToolSystem.m_d3dRenderer.setDialogBoxOpen(true);
}

void MFCMain::ToolBarButton1()
{

	m_ToolSystem.onActionSave();
}

void MFCMain::updateIndexOnSelect()
{
	if (m_TransportControls.GetSafeHwnd() != NULL)
	{
		// Update the internal index to match the new selection.
		m_TransportControls.UpdateIndexOnSelect(m_ToolSystem.m_selectedObject);
		m_TransportControls.UpdateTransportOnSelect();
	}
}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
