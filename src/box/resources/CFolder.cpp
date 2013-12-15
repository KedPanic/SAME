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
#include "resources/CFolder.h"
#include "resources/IResource.h"

// Default constructor.
CFolder::CFolder(const String &p_sName, const String &p_sPath, CFolder *p_pParent /*= NULL*/)
	: IResource(p_sName, p_sPath), m_pParent(p_pParent)
{
	m_nID = sam::CreateID(p_sPath.c_str(), p_sPath.size());

	if(wxDir::Exists(m_sPath) == false)
	{
		wxFileName::Mkdir(m_sPath);
	}

	// set the folder thumbnail.
	m_pThumbnail = ::GetThumbnail(e_Thumbnail_Folder);
}

CFolder::~CFolder()
{
	Resources::iterator it = m_aResources.begin(), it_end = m_aResources.end();
	while(it != it_end)
	{
		SAM_DELETE *it;
		it = m_aResources.erase(it);
	}
}

// Add a new resource.
void CFolder::AddResource(IResource *p_pResource)
{
#if defined(SAM_DEBUG) && 0
	Resources::iterator it = m_aResources.begin(), it_end = m_aResources.end();
	for(;it != it_end; ++it)
	{
		SAM_ASSERT((*it)->GetID() != p_pResource->GetID(), "Resource collision, the resource already exist or already added");
	}
#endif

	m_aResources.push_back(p_pResource);
}

// Delete an old resource.
void CFolder::DeleteResource(IResource *p_pResource)
{
	SAM_ASSERT(p_pResource != NULL, "The resource is null");

	Resources::iterator it = m_aResources.begin(), it_end = m_aResources.end();
	while(it != it_end)
	{
		if(*it == p_pResource)
		{
			m_aResources.erase(it);
			break;
		}		
	}
}

// Load resource.
bool CFolder::Load()
{
	return true;
}

// Unload resource.
bool CFolder::Unload()
{
	return true;
}
