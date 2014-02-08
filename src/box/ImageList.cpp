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
#include "ImageList.h"
#include "resources/IResource.h"

static wxImageList *m_pImageList = NULL; ///< Image list used for the icons.	

wxImageList *GetImageList()
{
	return m_pImageList;
}

// Retrieves the generic thumbnail.
static wxBitmap s_pThumbnail[e_Thumbnail_Nb];
wxBitmap *GetThumbnail(EThumbnail p_eThumbnailType)
{
	return &s_pThumbnail[p_eThumbnailType];
}



void CreateImageListAndThumbnail()
{
	SAM_ASSERT(m_pImageList == NULL, "Image list already created");

	wxIcon oIcons[e_Icon_Nb];
	oIcons[e_Icon_Folder] = wxArtProvider::GetIcon(wxART_FOLDER, wxART_LIST, wxSize(16, 16));
	oIcons[e_Icon_SelectedFolder] = wxArtProvider::GetIcon(wxART_FOLDER_OPEN, wxART_LIST, wxSize(16, 16));
	oIcons[e_Icon_FolderOpen] = wxArtProvider::GetIcon(wxART_FOLDER_OPEN, wxART_LIST, wxSize(16, 16));
	oIcons[e_Icon_Texture] = wxIcon("../data/sambox/icons/16x16/texture.xpm", wxBITMAP_TYPE_XPM);
	oIcons[e_Icon_Mesh] = wxIcon("../data/sambox/icons/16x16/mesh.xpm", wxBITMAP_TYPE_XPM);
	oIcons[e_Icon_Font] = wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_LIST, wxSize(16, 16));
	oIcons[e_Icon_File] = wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_LIST, wxSize(16, 16));

	m_pImageList = new wxImageList(16, 16, true);
	for(uint32 nIndex = 0; nIndex < e_Icon_Nb; ++nIndex)
	{
		m_pImageList->Add(oIcons[nIndex]);
	}


	// create thumbnails.
	s_pThumbnail[e_Thumbnail_Folder] = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_LIST, wxSize(64, 64));
}

EIcons GetIconFromResource(IResource *p_pResource)
{
	switch(p_pResource->GetResourceType())
	{
	case e_ResourceType_Texture:
		return e_Icon_Texture;

	case e_ResourceType_Font:
		return e_Icon_Font;

	case e_ResourceType_Mesh:
		return e_Icon_Mesh;

	case e_ResourceType_Folder:
		return e_Icon_Folder;	

	case e_ResourceType_Unknown:
		{
			//wxMimeTypesManager mimeTypeManager;
			//wxFileType *pFileType = mimeTypeManager.GetFileTypeFromExtension("ods");

			return e_Icon_File;
		}		
	
	default:
		SAM_ASSERT(false, "No icon found for the resource type %d", p_pResource->GetResourceType());
	}

	return e_Icon_File;
}

wxIcon GetIcon(IResource *p_pResource)
{
	EIcons eIcon = GetIconFromResource(p_pResource);

	return m_pImageList->GetIcon(eIcon);
}