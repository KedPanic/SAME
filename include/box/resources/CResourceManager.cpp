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
#include "resources/CResourceManager.h"

#include "resources/IResource.h"
#include "resources/IResourceFactory.h"

CResourceManager *g_pResourceManager = NULL;

// Default constructor.
CResourceManager::CResourceManager()
{
	SAM_TRAP(g_pResourceManager == NULL);
	g_pResourceManager = this;
}

CResourceManager::~CResourceManager()
{

}

// Add a resource factory.
void CResourceManager::AddResourceFactory(IResourceFactory *p_pResourceFactory)
{

}

// Create the resource.
IResource *CResourceManager::Create(const String &p_sName, const String &p_sPath, EResourceType p_eResourceType /*= e_ResourceType_Unknown*/)
{	
	return NULL;
}
