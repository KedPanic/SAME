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
	sam::String m_sDestination;
	sam::ID m_nPlatformId;
};

struct SMeshHeader
{
	uint32 m_nVersion;
};

void MeshExportCallback(void *p_pData)
{
	SMeshJobData *pMeshJobData = (SMeshJobData*)p_pData;

	const char *sMeshFilename = pMeshJobData->m_pMesh->GetPath().c_str();

	Assimp::Importer oImporter;
	const aiScene *pScene = oImporter.ReadFile(sMeshFilename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if(pScene)
	{
		/*
		MESH FILE FORMAT:

		[HEADER]
		int32 version
		[VERTEX DECLARATION]
		int32 nb_declerations
		SVertexDeclaration vertex_declaration_1
		...
		SVertexDeclaration vertex_declaration_n
		[VERTEX BUFFER]
		int32	nb_vertices
		int32	size
		int8	data
		[INDEX BUFFER]
		int32	size
		int32	index_0
		...
		int32	index_n
		[MATERIAL]
		*/		
		sam::CFile oFile;
		oFile.Open((pMeshJobData->m_sDestination + pMeshJobData->m_pMesh->GetName()).c_str(),  sam::e_OM_Write | sam::e_OM_Binary);

		/* writing header */
		{
			SMeshHeader oHeader;
			oHeader.m_nVersion = CMeshExporter::m_nVersion;

			oFile.Write(&oHeader, sizeof(SMeshHeader));
		}		

		for(uint32 nIndex = 0; nIndex < pScene->mNumMeshes; ++nIndex)
		{
			const aiMesh *pMesh = pScene->mMeshes[nIndex];

			/* writing vertex declaration. */
			uint32 nStride = 0;
			{
				sam::SVertexDeclaration aVertexDeclaration[sam::e_VertexSemantic_Nb];

				uint32 nDeclarationSize = 0;				
				if(pMesh->HasPositions())
				{				
					aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Position;
					aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
					aVertexDeclaration[nDeclarationSize].m_nNbComponents = 3;
					aVertexDeclaration[nDeclarationSize].m_nOffset = nStride;

					nDeclarationSize++;
					nStride += sizeof(f32) * 3;
				}

				if(pMesh->HasNormals())
				{
					aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Normal;
					aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
					aVertexDeclaration[nDeclarationSize].m_nNbComponents = 3;
					aVertexDeclaration[nDeclarationSize].m_nOffset = nStride;

					nDeclarationSize++;
					nStride += sizeof(f32) * 3;
				}			

				if(pMesh->HasTextureCoords(0))
				{
					aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Texture_Coord0;
					aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
					aVertexDeclaration[nDeclarationSize].m_nNbComponents = 2;
					aVertexDeclaration[nDeclarationSize].m_nOffset = nStride;

					nDeclarationSize++;
					nStride += sizeof(f32) * 2;
				}

				if(pMesh->HasVertexColors(0))
				{
					aVertexDeclaration[nDeclarationSize].m_eSemantic = sam::e_VertexSemantic_Color0;
					aVertexDeclaration[nDeclarationSize].m_eType = sam::e_Type_Float;
					aVertexDeclaration[nDeclarationSize].m_nNbComponents = 4;
					aVertexDeclaration[nDeclarationSize].m_nOffset = nStride;

					nDeclarationSize++;
					nStride += sizeof(f32) * 4;
				}

				if(pMesh->HasTangentsAndBitangents())
				{
					SAM_ASSERT(false, "have to be implemented");
				}

				oFile.Write(&nDeclarationSize, sizeof(nDeclarationSize));
				for(uint32 nDecleration = 0; nDecleration < nDeclarationSize; ++nDecleration)
				{
					oFile.Write(&aVertexDeclaration[nDecleration], sizeof(sam::SVertexDeclaration));
				}
			}			

			/* writing vertex buffer */
			{
				uint32 nBufferSize = pMesh->mNumVertices * nStride;
				oFile.Write(&pMesh->mNumVertices, sizeof(uint32));
				oFile.Write(&nBufferSize, sizeof(uint32));

				uint32 nElementIndex = 0;
				float *afVertexBuffer = new float[nStride / sizeof(float)];
				for(uint32 nVertexIndex = 0; nVertexIndex < pMesh->mNumVertices; ++nVertexIndex)
				{
					uint32 nOffset = 0;
					if(pMesh->HasPositions())
					{
						afVertexBuffer[nOffset + 0] = pMesh->mVertices[nVertexIndex].x;
						afVertexBuffer[nOffset + 1] = pMesh->mVertices[nVertexIndex].y;
						afVertexBuffer[nOffset + 2] = pMesh->mVertices[nVertexIndex].z;

						nOffset += 3;
					}

					if(pMesh->HasNormals())
					{
						afVertexBuffer[nOffset + 0] = pMesh->mNormals[nVertexIndex].x;
						afVertexBuffer[nOffset + 1] = pMesh->mNormals[nVertexIndex].y;
						afVertexBuffer[nOffset + 2] = pMesh->mNormals[nVertexIndex].z;

						nOffset += 3;
					}

					if(pMesh->HasTextureCoords(0))
					{
						aiVector3D oTextureCoords = pMesh->mTextureCoords[0][nVertexIndex]; 

						afVertexBuffer[nOffset + 0] = pMesh->mTextureCoords[0][nVertexIndex].x;
						afVertexBuffer[nOffset + 1] = pMesh->mTextureCoords[0][nVertexIndex].y;

						nOffset += 2;
					}

					if(pMesh->HasVertexColors(0))
					{
						afVertexBuffer[nOffset + 0] = pMesh->mColors[0][nVertexIndex].r;
						afVertexBuffer[nOffset + 1] = pMesh->mColors[0][nVertexIndex].g;
						afVertexBuffer[nOffset + 2] = pMesh->mColors[0][nVertexIndex].b;
						afVertexBuffer[nOffset + 3] = pMesh->mColors[0][nVertexIndex].a;

						nOffset += 4;
					}

					oFile.Write(afVertexBuffer, nStride);
				}

				delete[] afVertexBuffer;				
			}

			/* writing index buffer */
			{
				uint32 nNbIndices = pMesh->mNumFaces * 3; // only triangle are supported.
				oFile.Write(&nNbIndices, sizeof(uint32));

				uint16 *anIndices = new uint16[nNbIndices];
				for(uint32 nIndex = 0; nIndex < pMesh->mNumFaces; ++nIndex)
				{
					SAM_ASSERT(pMesh->mFaces[nIndex].mNumIndices == 3, "Only triangle are supported");

					anIndices[nIndex * 3 + 0] = pMesh->mFaces[nIndex].mIndices[0];
					anIndices[nIndex * 3 + 1] = pMesh->mFaces[nIndex].mIndices[1];
					anIndices[nIndex * 3 + 2] = pMesh->mFaces[nIndex].mIndices[2];
				}

				oFile.Write(anIndices, sizeof(uint16) * nNbIndices);
				delete[] anIndices;
			}
		}

		// write file.
		oFile.Close();
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
sam::SJob CMeshExporter::CreateJob(IResource *p_pResource, const sam::String &p_sDestination, sam::ID p_nPlatformId)
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
	sam::SJob oJob =  {&MeshExportCallback, pMeshJobData};
	return oJob;
}

// Method called by the job to export the resource.
bool CMeshExporter::Export(const sam::IStream *p_pStream, const sam::String &p_sDestination, const SMeshMetadata &p_oMetadata, sam::ID p_nPlatformId)
{
	return true;
}
