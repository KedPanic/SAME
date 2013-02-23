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
#include "IPlatformPlugin.h"
#include "CPlatformManager.h"

namespace sam
{
	namespace box
	{
		/// @brief Platform plugin DLL function.
		typedef IPlatformPlugin *(*CreatePlatformPlugin)();
		typedef bool *(*DestroyPlatformPlugin)();

		CPlatformManager::CPlatformManager()
			: m_pFirstPlatformPlugin(NULL)
		{
		}

		CPlatformManager::~CPlatformManager()
		{
			if(m_pFirstPlatformPlugin)
			{
				while(m_pFirstPlatformPlugin)
				{
					// free it !
					DestroyPlatformPlugin pFunc = (DestroyPlatformPlugin)SamGetSymbol(m_pFirstPlatformPlugin->GetLibrary(), "DestroyPlatformPlugin");
					pFunc();
					SamFreeLibrary(m_pFirstPlatformPlugin->GetLibrary());

					m_pFirstPlatformPlugin = m_pFirstPlatformPlugin->GetNext();
				}
			}
		}

		// Load specified plugin.
		IPlatformPlugin *CPlatformManager::LoadPlugin(const char *p_sPath)
		{
			Library pLibrary = SamLoadLibrary(p_sPath);
			if(pLibrary != NULL)
			{
				// Get starting symbol.
				CreatePlatformPlugin pFunc = (CreatePlatformPlugin)SamGetSymbol(pLibrary, "CreatePlatformPlugin");
				IPlatformPlugin *pPlugin = pFunc();

				if(pPlugin)
				{
					// Add created plugin to the linked list.
					if(!m_pFirstPlatformPlugin)
					{
						m_pFirstPlatformPlugin = pPlugin;
					}
					else
					{
						m_pFirstPlatformPlugin->Add(pPlugin);
					}

					pPlugin->SetLibrary(pLibrary);
					return pPlugin;
				}

				// Unload DLL.
				SamFreeLibrary(pLibrary);
			}

			return NULL;
		}

		// Unload specified plugin by name.
		bool CPlatformManager::UnloadPlugin(const char *p_sName)
		{
			IPlatformPlugin *pCurrent = m_pFirstPlatformPlugin;
			while(pCurrent)
			{
				if(strcmp(pCurrent->GetName(), p_sName) == 0)
				{
					// free it !
					DestroyPlatformPlugin pFunc = (DestroyPlatformPlugin)SamGetSymbol(pCurrent->GetLibrary(), "DestroyPlatformPlugin");
					pFunc();
					SamFreeLibrary(pCurrent->GetLibrary());

					return true;
				}

				pCurrent = pCurrent->GetNext();
			}
        
			SamLogWarning("Unable to find plugin '%s'", p_sName);
			return false;
		}

		// Retrieves plugin by name.
		IPlatformPlugin *CPlatformManager::GetPlugin(const char *p_sName) const
		{
			IPlatformPlugin *pCurrent = m_pFirstPlatformPlugin;
			while(pCurrent)
			{
				if(strcmp(pCurrent->GetName(), p_sName) == 0)
				{
					return pCurrent;
				}

				pCurrent = pCurrent->GetNext();
			}

			SamLogWarning("Unable to find plugin '%s'", p_sName);
			return NULL;
		}
	}
}
