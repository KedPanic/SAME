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
#include "exporter/CMeshExporter.h"

//////////////////////////////////////////////////////////////////////////
//									JOB									//
//////////////////////////////////////////////////////////////////////////
struct SMeshJobData
{
	CMeshExporter *m_pExporter;
	CMeshResource *m_pMesh;
	String m_sDestination;
	sam::ID m_nPlatformId;
};

void MeshExportCallback(void *p_pData)
{
	SMeshJobData *pMeshJobData = (SMeshJobData*)p_pData;

	SAM_FREE(pMeshJobData);
}


//////////////////////////////////////////////////////////////////////////
//								TEXTURE EXPORTER						//
//////////////////////////////////////////////////////////////////////////
// Retrieves supported export format.
const SFormat *CMeshExporter::GetFormat() const
{

}

// Request an export.
sam::SJob CMeshExporter::CreateJob(IResource *p_pResource, const String &p_sDestination, sam::ID p_nPlatformId)
{

}

// Method called by the job to export the resource.
bool CMeshExporter::Export(const SImage &p_pImage, const String &p_sDestination, const SMeshMetadata &p_oMetadata, sam::ID p_nPlatformId)
{

}
