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
#ifndef __SAMBOX_CPLATFORM_MANAGER_H__
#define __SAMBOX_CPLATFORM_MANAGER_H__

namespace sam
{
	namespace box
	{
		/// @brief Platform plugins manager for tools.
		class CPlatformManager : public IAllocated
		{
		public:
			CPlatformManager();
			~CPlatformManager();

			/// @brief Load specified plugin.
			/// 
			/// @param p_sPath Absolute plugin path.
			/// 
			/// @return Plugin or NULL if any error occurred.
			IPlatformPlugin *LoadPlugin(const char *p_sPath);

			/// @brief Unload specified plugin by name.
			/// 
			/// @param p_sName Plugin name to unload.
			/// 
			/// @return True or false if any error occurred.
			bool UnloadPlugin(const char *p_sName);

			/// @brief Retrieves plugin by name.
			/// 
			/// @param p_sName Plugin name.
			/// 
			/// @return Plugin or NULL if not found.
			IPlatformPlugin *GetPlugin(const char *p_sName) const;

		private:
			IPlatformPlugin *m_pFirstPlatformPlugin; ///< List header of loaded platform plugin.
		};
	}
}

#endif // __SAMBOX_CPLATFORM_MANAGER_H__
