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
#ifndef __SAMBOX_CWORLD_H__
#define __SAMBOX_CWORLD_H__

namespace sam
{
	namespace box
	{
		class CWorld : public ISerializable
		{
		public:
			IMPLEMENT_SERIALIZABLE(CWorld, "world");

			/// @brief Constructor.
			/// 
			/// @param p_sPath World path.
			CWorld(const QString &p_sPath);

			/// @brief Default constructor.
			CWorld();
			~CWorld();

			/// @brief Set the path of the world.
			/// 
			/// @param p_sPath New path.
			void SetPath(const QString &p_sPath);

			/// @brief Retrieves current name.
			/// 
			/// @return World name.
			const QString &GetPath() const {return m_sPath;}

			/// @brief Retrieves if world has changed.
			/// 
			/// @return True if world has changed.
			bool HasChanged() const {return m_bHasChanged;}

			/// @brief Save the world.
			void Save();

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Read(ISerializer *p_pContext);

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Write(ISerializer *p_pContext);

		private:
			QString m_sPath;
			bool m_bHasChanged;
		};
	}
}

#endif // __SAMBOX_CWORLD_H__
