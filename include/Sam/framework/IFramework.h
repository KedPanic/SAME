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
#ifndef __IFRAMEWORK__
#define __IFRAMEWORK__

#include "framework/CRenderConfig.h"

namespace sam
{
	/// @brief Define framework event.
	enum EFrameworkEvent
	{
		e_FE_Window_Close,
		e_FE_Window_Lost_Focus,
		e_FE_Window_Gain_Focus,
		e_FE_Window_Resize,
	};

	/// @brief Interface for framework event listener.
	class IFrameworkEventListener : public tpl::TList<IFrameworkEventListener>
	{
	public:
		/// @brief Called after initialization.
		virtual void OnPostInit() {}

		/// @brief Called when the application is shutdowning.
		virtual void OnShutdown() {}

		/// @brief Called once per frame.
		/// 
		/// @param p_fElapsedTime Elapsed time since the last frame (ITimer::GetFrameTime)
		virtual void OnUpdate(float p_fElapsedTime) {}

		/// @brief Called when system event occurred.
		/// 
		/// @param p_eEvent System event occurred.
		virtual void OnSystemEvent(EFrameworkEvent p_eEvent) {}
	};

	/// @brief Define type of pause.
	enum EFrameworkPause
	{
		e_FP_None,
		e_FP_Menu,
		e_FP_Extra,
	};

	/// @brief Define type of update.
	enum EFrameworkUpdate
	{
		e_FU_Normal          = 1 << 1,        
		e_FU_Ignore_Sound    = 1 << 2,
		e_FU_Ignore_Physics  = 1 << 3,
		e_FU_Ignore_AI       = 1 << 4,
		e_FU_Editor          = e_FU_Ignore_Sound | e_FU_Ignore_Physics | e_FU_Ignore_AI,
	};

    /// @enum Module Id.
    enum EFrameworkModule
    {        
        e_FM_Renderer = 1 << 0,
        e_FM_Sound    = 1 << 1,
        e_FM_Physics  = 1 << 2,

        e_FM_All = e_FM_Renderer | e_FM_Sound | e_FM_Physics,
    };


	/// @brief Root of application.
	class SAM_FRAMEWORK_API IFramework : public IAllocated
	{
	public:
		/// @brief Constructor.
		/// 
		/// @param p_sAppName Name of the application.
		IFramework(const char *p_sAppName);

		/// @brief Destructor.
		virtual ~IFramework();

		/// @brief Initialize system.
		/// 
        /// @param p_sSaveDir Save game directory relative to %home% directory.
        /// @param p_eModuleToInit Flag for module to init.
        ///
		/// @return Global environment variables.
		Env *Initialize(const char *p_sSaveDir, uint32 p_eModuleToInit = e_FM_All);

        /// @brief Shutdown application.        
        void Shutdown();

		/// @brief Have to be called at the end of initialization.
		/// 
        /// @param p_pEnv Global environment variable.
        ///
		/// @return True if its OK.
		virtual bool PostInit(Env *p_pEnv) = 0;

		/// @brief Preshutdown.
		virtual void PreShutdown() = 0;		

		/// @brief  Update all sub-systems.
		/// 
		/// @param p_iUpdate Update flags.
		/// @param p_ePause Type of pause.
		///
		/// @return False if we have to close application.
		virtual bool Update(int p_iUpdate, EFrameworkPause _ePause) = 0;

        /// @brief Begin rendering.
        virtual void BeginFrame() = 0;

        /// @brief Rendering.
        virtual void Render() = 0;
 
        /// @brief End rendering.
        virtual void EndFrame() = 0;  

		/// @brief Set mod name.
		/// 
		/// @param p_sModName Loading DLL mod.
		///
		/// @return False if the specified mod is not available.
		bool SetModName(const char *p_sModName);

		/// @brief Retrieves the name of the loaded mod or game title.
		///
		/// @return Mod name.
		const char *GetModName() const;

		/// @brief Retrieves if we have load a mod.
		/// 
		/// @return True if we have load a mod.
		bool IsMod() const;

		/// @brief Retrieves the directory where we write game save.
		/// 
		/// @return The directory where we write game save.
		const char *GetSaveDirectory() const;

		/// @brief Sets the data directory.
		/// 
		/// @param p_sPath Relative to executable directory.
		void SetDataDirectory(const char *p_sPath);

		/// @brief Retrieves the data directory.
		/// 
		/// @return The data directory.
		const char *GetDataDirectory() const;

		/// @brief Retrieves the mod data directory.
		/// 
		/// @return The mod data directory.
		const char *GetModDataDirectory() const;

		/// @brief Send framework event.
		/// 
		/// @param p_eEvent Framework event has to be throw.
		void OnSystemEvent(EFrameworkEvent p_eEvent);

		/// @brief Add a new framework event listener.
		/// 
		/// @param p_pListener Pointer to the new listener.
		void AddEventListener(IFrameworkEventListener *p_pListener);

		/// @brief Remove an old framework event listener.
		/// 
		/// @param p_pListener Pointer to the old listener to remove.
		void RemoveEventListener(IFrameworkEventListener *p_pListener);

		/// @brief On size event.
		/// 
		/// @param p_iWidth Width of the window.
		/// @param p_iHeight Height of the window.
		void OnSize(int p_iWidth, int p_iHeight);

		/// @brief On close event.
		void OnClose();

		/// @brief On gain focus.
		void OnGainFocus();

		/// @brief On lose focus.
		void OnLoseFocus();

	private:
		char *m_sSaveDir;     ///< Game save directory.
		char *m_sDataDir;     ///< Game data directory.
		char *m_sModData;     ///< Mod data directory.
		char *m_sAppName;     ///< Name of the application.
        bool m_bMod;          ///< True if a mod was loaded.
        DHANDLE m_pDLLGame;   ///< DLL of the game was loaded.
//        IGame *m_pGame;       ///< Pointer to the actual game.
		CTimer *m_pTimer;     ///< Timer.
        
		IFrameworkEventListener *m_pFirstFrameworkListener; ///< head of the linked list of framework event listener.

    protected:
        CRenderConfig m_oRenderConfig;  ///< Render configuration.
	};
}

#endif // __IFRAMEWORK__
