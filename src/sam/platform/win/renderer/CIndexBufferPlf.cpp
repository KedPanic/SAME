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
#include "renderer/CIndexBuffer.h"

#include "renderer/CRenderWindow.h"

namespace sam
{
	// Constructor.
	CIndexBuffer::CIndexBuffer()
		: m_pBuffer(NULL), m_nNbIndices(0)
	{

	}

	// Destructor.
	CIndexBuffer::~CIndexBuffer()
	{
		if(m_pBuffer)
		{
			m_pBuffer->Release();
		}
	}

	// Initialize the index buffer.
	bool CIndexBuffer::Initialize(const uint16 *p_anIndices, uint32 p_nNbIndices)
	{
		m_nNbIndices = p_nNbIndices;

		// Setup the index buffer.
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(uint16) * m_nNbIndices;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA oInitData;
		ZeroMemory( &oInitData, sizeof(oInitData) );
		oInitData.pSysMem = p_anIndices;

		HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreateBuffer(&bufferDesc, &oInitData, &m_pBuffer);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		return true;
	}
}
