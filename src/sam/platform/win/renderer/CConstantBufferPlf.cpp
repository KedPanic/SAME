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
#include "renderer/CConstantBuffer.h"

#include "renderer/CRenderWindow.h"

namespace sam
{
	// Constructor.
	CConstantBuffer::CConstantBuffer()
		: m_pBuffer(NULL)
	{

	}

	// Destructor.
	CConstantBuffer::~CConstantBuffer()
	{
		if(m_pBuffer)
		{
			m_pBuffer->Release();
		}
	}

	// Initialize the index buffer.
	bool CConstantBuffer::Initialize(uint32 p_nSize)
	{
		// Setup the index buffer.
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = p_nSize;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		
		HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_pBuffer);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		return true;
	}

	// Lock vertex buffer.
	bool CConstantBuffer::MapWrite(void *p_pBuffer, uint32 p_nSize)
	{
		SAM_ASSERT(p_pBuffer != NULL, "Buffer is null");

		// Lock the vertex buffer.
		D3D11_MAPPED_SUBRESOURCE subressource;
		ZeroMemory(&subressource, sizeof(D3D11_MAPPED_SUBRESOURCE));

		HRESULT hResult = g_Env->pRenderWindow->GetD3DContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subressource);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		memcpy(subressource.pData, p_pBuffer, p_nSize);
		Unmap();

		return true;
	}

	// Lock constant buffer.
	bool CConstantBuffer::MapRead(void *p_pBuffer, uint32 _nSize)
	{
		SAM_ASSERT(p_pBuffer != NULL, "Buffer is null");

		// Lock the constant buffer.
		D3D11_MAPPED_SUBRESOURCE subressource;
		ZeroMemory(&subressource, sizeof(D3D11_MAPPED_SUBRESOURCE));

		HRESULT hResult = g_Env->pRenderWindow->GetD3DContext()->Map(m_pBuffer, 0, D3D11_MAP_READ, 0, &subressource);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		p_pBuffer = subressource.pData;
		return true;
	}

	// Unlock constant buffer.
	void CConstantBuffer::Unmap(void)
	{
		g_Env->pRenderWindow->GetD3DContext()->Unmap(m_pBuffer, 0);
	}
}
