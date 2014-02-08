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
#include "SamRendererPCH.h"
#include "renderer/CMesh.h"

#include "renderer/CRenderWindow.h"
#include "renderer/CVertexBuffer.h"
#include "renderer/CIndexBuffer.h"

namespace sam
{
	//////////////////////////////////////////////////////////////////////////
	//	VERSION 0.0
	//////////////////////////////////////////////////////////////////////////
	//
	//	MESH FILE FORMAT:
	//  
	//	[HEADER]
	//	int32 version
	//	[VERTEX DECLARATION]
	//	int32 nb_declerations
	//	SVertexDeclaration vertex_declaration_1
	//	...
	//	SVertexDeclaration vertex_declaration_n
	//	[VERTEX BUFFER]
	//  int32   nb_vertices
	//	int32	size
	//	int8	data
	//	[INDEX BUFFER]
	//	int32	size
	//	int16	index_0
	//	...
	//	int16	index_n
	//
	//////////////////////////////////////////////////////////////////////////
	bool CreateMeshVersion0(CMemoryStream &p_oStream, CVertexBuffer *p_pVertexBuffer, CIndexBuffer *_pIndexBuffer)
	{
		// vertex declaration.
		uint32 nNbVertexDeclarations = 0;
		p_oStream.Read(&nNbVertexDeclarations, sizeof(uint32));
		if(!nNbVertexDeclarations || nNbVertexDeclarations > e_VertexSemantic_Nb)
		{
			SamLogError("Malformed mesh file.");
			return false;
		}

		SVertexDeclaration aVertexDeclaration[e_VertexSemantic_Nb];
		for(uint32 nIndex = 0; nIndex < nNbVertexDeclarations; ++nIndex)
		{
			p_oStream.Read(&aVertexDeclaration[nIndex], sizeof(SVertexDeclaration));
		}

		// vertex buffer.
		uint32 nNbVertices = 0;
		p_oStream.Read(&nNbVertices, sizeof(uint32));
		if(nNbVertices == 0)
		{
			SamLogError("Malformed mesh file.");
			return false;
		}

		if(p_pVertexBuffer->Initialize(aVertexDeclaration, nNbVertexDeclarations, nNbVertices))
		{
			uint32 nBufferSize = 0;
			p_oStream.Read(&nBufferSize, sizeof(uint32));
			if(nBufferSize == 0)
			{
				SamLogError("Malformed mesh file.");
				return false;
			}

			void *aBuffer = SAM_ALLOC_ARRAY(uint8, nBufferSize);
			p_oStream.Read(aBuffer, nBufferSize);
			p_pVertexBuffer->MapWrite(0, aBuffer, nBufferSize);
		}

		// index buffer.
		uint32 nNbIndices = 0;
		p_oStream.Read(&nNbIndices, sizeof(uint32));
		if(nNbIndices == 0)
		{
			SamLogError("Malformed mesh file.");
			return false;
		}
		
		uint16 *pIndexBuffer = SAM_ALLOC_ARRAY(uint16, nNbIndices);
		p_oStream.Read(pIndexBuffer, sizeof(uint16) * nNbIndices);
		return _pIndexBuffer->Initialize(pIndexBuffer, nNbIndices);
	}
	//////////////////////////////////////////////////////////////////////////

	CMesh::CMesh()
		: m_pVertexBuffer(NULL), m_pIndexBuffer(NULL)
	{
	}

	CMesh::~CMesh()
	{
		if(m_pVertexBuffer)
		{
			SAM_DELETE m_pVertexBuffer;
		}
	}
	
	// Create mesh from memory buffer.
	bool CMesh::CreateMesh(uint8 *p_pBuffer, uint32 p_nSize)
	{
		CMemoryStream oMemoryStream(p_pBuffer, p_nSize);

		// retrieve version
		uint32 nVersion;
		oMemoryStream.Read(&nVersion, sizeof(uint32));

		if(nVersion == e_MeshVersion_0)
		{
			m_pVertexBuffer = g_Env->pRenderWindow->CreateVertexBuffer();
			m_pIndexBuffer = SAM_NEW CIndexBuffer;

			return CreateMeshVersion0(oMemoryStream, m_pVertexBuffer, m_pIndexBuffer);
		}

		return false;
	}
}
