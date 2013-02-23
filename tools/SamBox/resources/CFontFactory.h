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
#ifndef __SAMBOX_CFONT_FACTORY__
#define __SAMBOX_CFONT_FACTORY__

#include "resources/IResourceFactory.h"

namespace sam
{
	namespace box
	{
		/// @brief Font factory is used to import true type font.
		class CFontFactory : public IResourceFactory
		{
		public:
			CFontFactory();

			/// @brief Initialize it !.
			/// 
			/// @return True if no error occurred.
			bool Initialize();

			/// @brief Create the resource.
			/// 
			/// @param p_sName Resource name.
			/// @param p_sPath Path where the resource will be created.
			/// 
			/// @return Created resource or NULL.
			IResource *Create(const String &p_sName, const String &p_sPath);

			/// @brief Import the resource.
			/// 
			/// @param p_sPath Absolute path of the resource to import.
			/// 
			/// @return True of there is no error.
			bool Import(const String &p_sPath);

			/// @brief Check if the resource is supported.
			/// 
			/// @param p_sExtension File extension.
			/// 
			/// @return True if it is supported.
			bool IsSupported(const String &p_sExtension) const;

		private:
			String m_sExtension;
		};
	}
}

#endif // __SAMBOX_CFONT_FACTORY__
