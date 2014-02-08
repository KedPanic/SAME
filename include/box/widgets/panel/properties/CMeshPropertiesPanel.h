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
#ifndef __SAMBOX_MESH_PROPERTIES_PANEL__
#define __SAMBOX_MESH_PROPERTIES_PANEL__

class CMeshPropertiesPanel : public wxPanel
{
public:
	CMeshPropertiesPanel(wxWindow *p_pParent);

	/// @brief set the current mesh resource
	/// 
	/// @param p_pMeshResource Pointer to the current mesh resource.
	void SetMeshResource(CMeshResource *p_pMeshResource);

private:
	SMeshMetadata  m_oLocalMetadata;
	CMeshResource *m_pMeshResource;

	// Target Settings.
	wxNotebook *m_pTargetSettings;
	struct STargetSettings
	{
		uint32		m_nTargetId;
	};

	typedef std::vector<STargetSettings*> TargetSettings;
	TargetSettings m_aTargetSettings;

	void CreateEventTable();
	void CreateTargetSettingPage(CPlatform *p_pPlatform);

	void OnNewProject(sam::ISignal *p_pSignal);

	// UI EVENTS
	void OnApply(wxCommandEvent &p_oEvent);
};

#endif // __SAMBOX_MESH_PROPERTIES_PANEL__
