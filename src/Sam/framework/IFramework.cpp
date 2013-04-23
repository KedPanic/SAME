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
#include "SamFrameworkPCH.h"
#include "framework/IFramework.h"
#include "framework/CLocalizationManager.h"
#include "framework/WndProc.h"

#include "common/SamModuleInit.h"

namespace sam
{
	/// @brief Constructor.
	/// 
	/// @param p_sAppName Name of the application.
	IFramework::IFramework(const char *p_sAppName)
		: m_sSaveDir(NULL), m_sDataDir(NULL), m_sModData(NULL), 
		m_sAppName(NULL), m_bMod(false), m_pDLLGame(0), 
		m_pTimer(NULL), m_pFirstFrameworkListener(NULL)
	{
	}

	/// @brief Destructor.
	IFramework::~IFramework()
	{
	}

    /// @brief Initialize system.
    /// 
    /// @param p_sSaveDir Save game directory relative to %home% directory.
    /// @param p_eModuleToInit Flag for module to init.
    ///
    /// @return Global environment variables.
    Env *IFramework::Initialize(const char *p_sSaveDir, uint32 p_eModuleToInit /*= e_FM_All*/)
	{
        // Initialize common module.
        Env *pEnv = InitCommon();
        ModuleInit(pEnv);

        // Initialize game save directory.
        char homePath[MAX_PATH];
        if(GetHomePath(homePath))
        {
            m_sSaveDir = SAM_ALLOC_ARRAY(char, strlen(p_sSaveDir) + strlen(homePath) + 1);
            sprintf(m_sSaveDir, "%s/%s", homePath, p_sSaveDir);

            // create directory if necessary.
            if(!IsDirectory(m_sSaveDir) && !CreateDirectory(m_sSaveDir))
            {
                SamLogWarning("Unable to create game save directory %s", m_sSaveDir);
            }
        }
        else
        {
            SamLogWarning("Unable to set game save directory.");
        }

        // Set log file.
        sprintf(homePath, "%s/engine.log", m_sSaveDir);
        g_Env->pLog->SetFilename(homePath);

        // Initialize sub components.
        if(p_eModuleToInit & e_FM_Renderer)
        {
            CreateRenderManager(pEnv)->SetWndProc(WndProc);

            char renderConfigFile[MAX_PATH];
            // check if file exist in the home directory.
            // we always use the last configuration set by the player.
            sprintf(renderConfigFile, "%s/defaultrendererconfig.cfg", m_sSaveDir);
            if(!IsFile(renderConfigFile))
            {
                // check if file exist in the application directory.
                char currentPath[MAX_PATH];
                if(!GetCurrentWorkingDirectory(MAX_PATH, currentPath))
                {
                    SamLogError("Unable to find working directory.");
                    return NULL;
                }

                sprintf(currentPath, "%s/defaultrendererconfig.cfg", currentPath);
                if(!IsFile(currentPath))
                {
                    SamLogError("Unable to read default renderer configuration file %s.", currentPath);
                    return NULL;
                }

                // copy file to save directory.
                CopyFile(currentPath, renderConfigFile);
            }

            // Read configuration file.
            helper::Serialize(e_Serializer_JSon, &m_oRenderConfig, renderConfigFile, true);            
        }


        if(p_eModuleToInit & e_FM_Sound)
        {
            //CreateSoundEngine(pEnv);
        }

        if(p_eModuleToInit & e_FM_Physics)
        {
            //CreatePhysicalWorld(pEnv);
        }

        pEnv->pFramework = this;
        pEnv->pLocalizationManager = SAM_NEW CLocalizationManager;

        // Should be setting the application.
        // Create window etc...
        PostInit(pEnv);

        return pEnv;
	}

    /// @brief Shutdown application.        
    void IFramework::Shutdown()
    {
        if(g_Env->pLocalizationManager)
        {
            SAM_DELETE g_Env->pLocalizationManager;
            g_Env->pLocalizationManager = NULL;
        }

        if(g_Env->pInputManager)
        {
            DestroyInputManager();
        }

        if(g_Env->pRenderWindow)
        {
            DestroyRenderManager();
        }

        ShutdownCommon();
    }

	/// @brief Set mod name.
	/// 
	/// @param p_sModName Loading DLL mod.
	///
	/// @return False if the specified mod is not available.
	bool IFramework::SetModName(const char *p_sModName)
	{
		// Set full path
		char sModFullPath[256] = {'\0'};
		sprintf(sModFullPath, "Mod/%s/bin/%s%s", p_sModName, p_sModName, SHARED_LIBRARY_EXT);

		// Check if DLL mod exist
		if(IsFile(sModFullPath))
		{
			// Try to load the DLL.
			SamLog("Load mod %s", p_sModName);
			m_pDLLGame = SamLoadLibrary(sModFullPath);

			if(m_pDLLGame != NULL)
			{
				// Get starting symbol.
// 				IGame::CreateGame pFunc = (IGame::CreateGame)SamGetSymbol(m_pDLLGame, "CreateGame");
// 				if(pFunc)
// 				{     
// 					if(m_pGame = pFunc(g_Env))
// 					{
// 						m_sAppName = p_sModName;
// 						m_bMod = true;
// 
// 						return true;
// 					}
// 					else
// 						SamLogError("Unable to create game from the specified mod '%s'", p_sModName);                                    
// 				}
// 				else
// 					SamLogError("Unable to get symbol 'CreateGame' from the specified mod '%s'", p_sModName);                
			}        
			else
				SamLogError("Unable to load DLL of the specified mod '%s'", p_sModName);
		}    
		else
			SamLogError("Unable to find DLL of the specified mod '%s'", p_sModName);

		// Release DLL.
		if(m_pDLLGame)
		{
			SamFreeLibrary(m_pDLLGame);
			m_pDLLGame = NULL;
		}

		return false;
	}

	/// @brief Retrieves the name of the loaded mod or game title.
	///
	/// @return Mod name.
	const char *IFramework::GetModName() const
	{
		return m_sAppName;
	}

	/// @brief Retrieves if we have load a mod.
	/// 
	/// @return True if we have load a mod.
	bool IFramework::IsMod() const
	{
		return m_bMod;
	}

    /// @brief Retrieves the directory where we write game save.
    /// 
    /// @return The directory where we write game save.
	const char *IFramework::GetSaveDirectory() const
	{
		return m_sSaveDir;
	}

    /// @brief Sets the data directory.
    /// 
    /// @param p_sPath Relative to executable directory.
	void IFramework::SetDataDirectory(const char *p_sPath)
	{
		char sPath[MAX_PATH];
		// Retrieves executable folder.
		if(GetCurrentWorkingDirectory(MAX_PATH, sPath))
		{
			uint32 nSize = strlen(sPath) + strlen(p_sPath);

			m_sDataDir = SAM_ALLOC_ARRAY(char, nSize + 1);
			strcpy(m_sDataDir, sPath);
			sprintf(m_sDataDir, "%s%s", sPath, p_sPath);

			m_sModData = SAM_ALLOC_ARRAY(char, nSize + 9);            
			sprintf(m_sModData, "%sMod\\%s\\bin\\%s", sPath, m_sAppName, p_sPath);
		}
	}

	/// @brief Retrieves the data directory.
	/// 
	/// @return The data directory.
	const char *IFramework::GetDataDirectory() const
	{
		return m_sDataDir;
	}

	/// @brief Retrieves the mod data directory.
	/// 
	/// @return The mod data directory.
	const char *IFramework::GetModDataDirectory() const
	{
		return m_sModData;
	}

	/// @brief Send framework event.
	/// 
	/// @param p_eEvent Framework event has to be throw.
	void IFramework::OnSystemEvent(EFrameworkEvent p_eEvent)
	{
		// Send shutdown to the listeners.
		IFrameworkEventListener *pListener = m_pFirstFrameworkListener;
		while(pListener)
		{
			pListener->OnSystemEvent(p_eEvent);
			pListener = pListener->GetNext();
		}
	}

	/// @brief Add a new framework event listener.
	/// 
	/// @param p_pListener Pointer to the new listener.
	void IFramework::AddEventListener(IFrameworkEventListener *p_pListener)
	{
		SAM_ASSERT(p_pListener != NULL, "Unable to add p_pListener, p_pListener is NULL.");

		if(m_pFirstFrameworkListener == NULL)
			m_pFirstFrameworkListener = p_pListener;
		else
			m_pFirstFrameworkListener->Add(p_pListener);
	}

	/// @brief Remove an old framework event listener.
	/// 
	/// @param p_pListener Pointer to the old listener to remove.
	void IFramework::RemoveEventListener(IFrameworkEventListener *p_pListener)
	{
		SAM_ASSERT(m_pFirstFrameworkListener != NULL, "Unable to remove p_pListener, there aren't framework event listener.");

		m_pFirstFrameworkListener->Remove(p_pListener);
	}

    /// @brief On size event.
	/// 
	/// @param p_iWidth Width of the window.
	/// @param p_iHeight Height of the window.
	void IFramework::OnSize(int p_iWidth, int p_iHeight)
	{
		OnSystemEvent(e_FE_Window_Resize);
	}

	/// @brief On close event.
	void IFramework::OnClose()
	{
		OnSystemEvent(e_FE_Window_Close);
	}

	/// @brief On gain focus.
	void IFramework::OnGainFocus()
	{
		OnSystemEvent(e_FE_Window_Gain_Focus);
	}

	/// @brief On lose focus.
	void IFramework::OnLoseFocus()
	{
		OnSystemEvent(e_FE_Window_Lost_Focus);
	}
}
