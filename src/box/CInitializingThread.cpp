//===========================================
// Copyright (C) 2013 Cedric Liaudet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//===========================================
#include "SamBoxPCH.h"
#include "CInitializingThread.h"
#include "CSamBox.h"
#include "widgets/CSplashScreen.h"

// Constructor.
CInitializingThread::CInitializingThread(CSplashScreen *p_pSplashScreen)
 : m_pSplashScreen(p_pSplashScreen)
{

}

wxThread::ExitCode CInitializingThread::Entry()
{
	// Initialize Sam Engine.
	SendEvent(wxT("Initialize sam engine..."));
	sam::Env *pEnv = sam::InitCommon();
	sam::ModuleInit(pEnv);	

	wxInitAllImageHandlers();

	// Load XRC
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(g_pSamBox->GetDataPath() + wxT("xrc/CScenePanel.xrc"));
	wxXmlResource::Get()->Load(g_pSamBox->GetDataPath() + wxT("xrc/CProjectWizard.xrc"));
	wxXmlResource::Get()->Load(g_pSamBox->GetDataPath() + wxT("xrc/CMainFrame.xrc"));

	// Send end of initializing event.
 	CInitCompletedEvent *pEvent = new CInitCompletedEvent();
	pEvent->SetEventObject(m_pSplashScreen);
 	g_pSamBox->QueueEvent(pEvent);
	
	return NULL;
}

// Send event to the splash screen.
void CInitializingThread::SendEvent(const wxString &p_sMessage)
{
	wxCommandEvent *pEvent = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED);
	pEvent->SetString(p_sMessage);
	m_pSplashScreen->GetEventHandler()->QueueEvent(pEvent);	
}