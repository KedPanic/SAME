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
#ifndef __SAMBOX_MAIN_FRAME__
#define __SAMBOX_MAIN_FRAME__

class CMainFrame : public wxFrame, public sam::ISerializable
{
	IMPLEMENT_SERIALIZABLE(CMainFrame, "MainFrame");

public:
	enum
	{
		// File.
		e_Menu_OpenWorld,
		e_Menu_SaveWorld,
		e_Menu_NewProject,
		e_Menu_OpenProject,
		e_Menu_SaveProject,
		e_Menu_Exit,

		// Edit.
	};

	/// @brief Constructor.
	/// 
	/// @param p_pParent Parent window.
	/// @param p_nId Unique ID.
	CMainFrame(wxWindow *p_pParent, wxWindowID p_nId = -1);

	~CMainFrame();

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	void Read(sam::ISerializer *p_pContext);

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	void Write(sam::ISerializer *p_pContext);

private:
	wxAuiManager *m_pAuiManager;
	boxAuiNotebook *m_pMainNotebook; ///< Center notebook.
	boxAuiNotebook *m_pRightNotebook;
	boxAuiNotebook *m_pBottomNotebook;
	boxAuiNotebook *m_pLeftNotebook;

	static const long ID_MAIN_NOTEBOOK;
	static const long ID_RIGHT_NOTEBOOK;
	static const long ID_BOTTOM_NOTEBOOK;
	static const long ID_LEFT_NOTEBOOK;

	/// @brief Create dynamic events.
	void CreateEventTable();
	
	void OnNewProject(wxCommandEvent &p_oEvent);
	void OnOpenProject(wxCommandEvent &p_oEvent);
	void OnSaveProject(wxCommandEvent &p_oEvent);
};

#endif // __SAMBOX_MAIN_FRAME__
