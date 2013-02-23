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
#ifndef __CFONT_H__
#define __CFONT_H__

#include "resources/IResource.h"

namespace sam
{
	namespace box
	{
		/// @brief
		class CFont : public IResource
		{
		public:
			/// @brief Retrieves type of resource.
			/// 
			/// @return Type of resource.
			EResourceType GetType() const {return e_RT_Font;}

			/// @brief Load resource.
			/// 
			/// @return True if there is no error.
			bool Load();

			/// @brief Unload resource.
			/// 
			/// @return True if there is no error.
			bool Unload();

			/// @brief Retrieves if resource is loaded.
			/// 
			/// @return True if resource is loaded.
			bool IsLoaded() const;

		private:
			String m_sCharaters;	///< List of supported charaters.
			//CTexture *m_pTexture;	///< Generated texture.
		};
	}
}
#endif // __CFONT_H__
