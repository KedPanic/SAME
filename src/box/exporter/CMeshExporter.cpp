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
#include "resources/CMeshResource.h"

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

	const char *sMeshFilename = pMeshJobData->m_pMesh->GetPath().c_str();

	Assimp::Importer oImporter;
	const aiScene *pScene = oImporter.ReadFile(sMeshFilename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if(pScene)
	{
		for(uint32 nIndex = 0; nIndex < pScene->mNumMeshes; ++nIndex)
		{
			const aiMesh *pMesh = pScene->mMeshes[nIndex];

			// create vertex declaration.
			sam::SVertexDeclaration aVertexDeclaration[sam::e_VertexSemantic_Nb];

			uint32 nDeclarationSize = 0;
			uint32 nOffset = 0;
			if(pMesh->HasPositions())
			{
				aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Position;
				aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
				aVertexDeclaration[nDeclarationSize].m_nNbComponents = 3;
				aVertexDeclaration[nDeclarationSize].m_nOffset = nOffset;

				nDeclarationSize++;
				nOffset += sizeof(f32) * 3;
			}

			if(pMesh->HasNormals())
			{
				aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Normal;
				aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
				aVertexDeclaration[nDeclarationSize].m_nNbComponents = 3;
				aVertexDeclaration[nDeclarationSize].m_nOffset = nOffset;

				nDeclarationSize++;
				nOffset += sizeof(f32) * 3;
			}			

			if(pMesh->HasTextureCoords(0))
			{
				aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Texture_Coord0;
				aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
				aVertexDeclaration[nDeclarationSize].m_nNbComponents = 2;
				aVertexDeclaration[nDeclarationSize].m_nOffset = nOffset;

				nDeclarationSize++;
				nOffset += sizeof(f32) * 2;
			}

			if(pMesh->HasTangentsAndBitangents())
			{
				SAM_ASSERT(false, "have to be implemented");
			}			

			// create vertex buffer.
			sam::CVertexBuffer *pVertexBuffer = sam::g_Env->pRenderWindow->CreateVertexBuffer();
			pVertexBuffer->Initialize(aVertexDeclaration, nDeclarationSize, pMesh->mNumVertices);
			
			uint32 nElementIndex = 0;
			sam::CVertexElementIterator oIterator(pVertexBuffer);
			for(uint32 nVertexIndex = 0; nVertexIndex < oIterator.End(); ++oIterator)
			{
				if(pMesh->HasPositions())
				{
					aiVector3D oPosition = pMesh->mVertices[nVertexIndex]; 

 					oIterator.Get<f32>(nElementIndex, 0) = oPosition.x;
 					oIterator.Get<f32>(nElementIndex, 1) = oPosition.y;
					oIterator.Get<f32>(nElementIndex, 2) = oPosition.z;

					nElementIndex++;
				}

				if(pMesh->HasNormals())
				{
					aiVector3D oNormal = pMesh->mNormals[nVertexIndex]; 

					oIterator.Get<f32>(nElementIndex, 0) = oNormal.x;
					oIterator.Get<f32>(nElementIndex, 1) = oNormal.y;
					oIterator.Get<f32>(nElementIndex, 2) = oNormal.z;

					nElementIndex++;
				}

				if(pMesh->HasTextureCoords(0))
				{
					aiVector3D oTextureCoords = pMesh->mTextureCoords[0][nVertexIndex]; 

					oIterator.Get<f32>(nElementIndex, 0) = oTextureCoords.x;
					oIterator.Get<f32>(nElementIndex, 1) = oTextureCoords.y;

					nElementIndex++;
				}
			}

			// Create mesh resource.
		}
	}	

	SAM_FREE(pMeshJobData);
}


//////////////////////////////////////////////////////////////////////////
//								MESH EXPORTER							//
//////////////////////////////////////////////////////////////////////////
// Retrieves supported export format.
const IExporter::SFormat *CMeshExporter::GetFormat() const
{
	static SFormat s_oFormat;
	s_oFormat.m_nFormat = 0;
	s_oFormat.m_sReadableName = "Mesh";

	return &s_oFormat;
}

// Request an export.
sam::SJob CMeshExporter::CreateJob(IResource *p_pResource, const String &p_sDestination, sam::ID p_nPlatformId)
{
	SAM_ASSERT(p_pResource != NULL, "Resource can't be null.");

	CMeshResource *pMeshResource = (CMeshResource*)p_pResource;

	// create job data.
	SMeshJobData *pMeshJobData = SAM_ALLOC(SMeshJobData);
	pMeshJobData->m_pExporter = this;
	pMeshJobData->m_pMesh = pMeshResource;
	pMeshJobData->m_sDestination = p_sDestination;
	pMeshJobData->m_nPlatformId = p_nPlatformId;

	// Create the job.
	sam::SJob oJob =  {&MeshExportCallback, pMeshResource};
	return oJob;
}

// Method called by the job to export the resource.
bool CMeshExporter::Export(const sam::IStream *p_pStream, const String &p_sDestination, const SMeshMetadata &p_oMetadata, sam::ID p_nPlatformId)
{
	return true;
}
