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
#ifndef __CACTION_MAP_MANAGER__
#define __CACTION_MAP_MANAGER__

#include <SamConfig.h>

namespace sam
{
	/// @brief Manage the action manager.
	class SAM_API CActionMapManager : IAllocated
	{
	public:
		/// @brief Constructor.
		CActionMapManager();

		/// @brief Destructor.
		~CActionMapManager();

		/// @brief Load action maps from XML file.
		/// 
		/// @param _sFile Name of the file.
		void LoadFromXML(const String &_sFile);

		/// @brief Create a new action map.
		/// 
		/// @param _sName Name of the action map.
		IActionMap *CreateActionMap(const String &_sName);


	private:
		typedef std::list<IActionMap*> ActionMaps;
		ActionMaps m_aActionMaps; ///< Array of action maps.
	};
}

#endif // __CACTION_MAP_MANAGER__
