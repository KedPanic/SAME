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
#include "CWorld.h"
#include "CSamBox.h"

namespace sam
{
	namespace box
	{
		// Constructor.
		CWorld::CWorld(const QString &p_sPath)
			: m_sPath(p_sPath), m_bHasChanged(false)
		{

		}

		CWorld::CWorld()
			: m_sPath("untitled"), m_bHasChanged(false)
		{
		}

		CWorld::~CWorld()
		{
		}

		// Set the path of the world.
		void CWorld::SetPath(const QString &p_sPath)
		{
			QDir sAppFolder(CSamBox::GetInstance()->GetAppFolder() + "/world/");

			// rename old file.
			sAppFolder.rename(sAppFolder.absolutePath() + p_sPath, sAppFolder.absolutePath() + p_sPath);

			m_sPath = p_sPath;
		}

		// Save the world.
		void CWorld::Save()
		{
		}

		// Serialize the object
		void CWorld::Read(ISerializer *p_pContext)
		{
		}

		// Serialize the object
		void CWorld::Write(ISerializer *p_pContext)
		{
		}
	}
}
