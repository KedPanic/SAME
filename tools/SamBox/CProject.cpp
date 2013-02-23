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
#include "CProject.h"
#include "resources/CPackage.h"
#include "CWorld.h"
#include "CSamBox.h"

namespace sam
{
	namespace box
	{
		// constructor.
		CProject::CProject(const QString &p_sPath)
			: m_sPath(p_sPath)
		{		
		}

		CProject::~CProject()
		{
		}

		// Save the project.
		void CProject::Save()
		{
			QByteArray sProjectFile = m_sPath.filePath("project").toLocal8Bit();
			QByteArray sBackupFile = m_sPath.filePath("project.back").toLocal8Bit();

			// Create a backup
			m_sPath.rename(sProjectFile, sBackupFile);

			CBinarySerializer oSerializer(sProjectFile.data());
			oSerializer.BeginSerialization(false, "project");
			Write(&oSerializer);
			oSerializer.EndSerialization();

			// Remove backup.
			m_sPath.remove(sBackupFile);
		}

		// Open the project.
		void CProject::Open()
		{
			QByteArray sProjectFile = m_sPath.filePath("project").toLocal8Bit();
			QByteArray sBackupFile = m_sPath.filePath("project.back").toLocal8Bit();

			// Check if a backup exist.
			if(m_sPath.exists(sBackupFile))
			{
				if(CSamBox::Message("A backup was found. Do you want to restore it ?") == QMessageBox::Yes)
				{
					// Create a backup of the current project if the backup was corrupted.
					m_sPath.rename(sProjectFile, sProjectFile + ".last");

					m_sPath.rename(sBackupFile, sProjectFile);
				}
			}

			// Open the project.
			CBinarySerializer oSerializer(sProjectFile.data());
			oSerializer.BeginSerialization(true, "project");
			Read(&oSerializer);
			oSerializer.EndSerialization();

			// Open world or create it if there isn't world.
			if(!m_sCurrentWorld.size())
			{
				CSamBox::GetInstance()->CreateWorld();
			}
			else
			{
				CSamBox::GetInstance()->OpenWorld(m_sCurrentWorld);
			}
		}

		// Serialize the object
		void CProject::Read(ISerializer *p_pContext)
		{
			m_sCurrentWorld = p_pContext->ReadValue("world");
		}

		// Serialize the object
		void CProject::Write(ISerializer *p_pContext)
		{
			QByteArray sCurrentWorld = m_sCurrentWorld.toLocal8Bit();
			p_pContext->WriteValue("world", (char*)sCurrentWorld.data());
		}
	}
}
