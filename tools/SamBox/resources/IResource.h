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
#ifndef __SAMBOX_IRESOURCE_H__
#define __SAMBOX_IRESOURCE_H__

namespace sam
{
	namespace box
	{
		/// @enum Type of resource.
		enum EResourceType
		{
			e_RT_Texture,
			e_RT_Sound,
			e_RT_Font,
			e_RT_Material,

			e_RT_Total,
		};

		/// @brief Interface for resource.
		class IResource : public ISerializable, public CFile
		{
		public:
			/// @brief Constructor.
			/// 
			/// @param p_sName Resource name.
			/// @param p_sPath Absolute path.
			IResource(const QString &p_sName, const QString &p_sPath);

			/// @brief Destructor.
			virtual ~IResource();

			/// @brief Retrieves resource name.
			/// 
			/// @return Resource name.
			const QString& GetName() const {return m_sName;}

			/// @brief Retrieves absolute path.
			/// 
			/// @return Absolute path.
			const QString& GetPath() const {return m_sPath;}

			/// @brief Retrieves type of resource.
			/// 
			/// @return Type of resource.
			virtual EResourceType GetType() const = 0;

			/// @brief Load resource.
			/// 
			/// @return True if there is no error.
			virtual bool Load() = 0;

			/// @brief Unload resource.
			/// 
			/// @return True if there is no error.
			virtual bool Unload() = 0;

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			virtual void Read(ISerializer *p_pContext);

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			virtual void Write(ISerializer *p_pContext);

		private:
			QString m_sName;         ///< Resource name.
			QString m_sPath;         ///< Absolute path.
		};
	}
}

#endif // __SAMBOX_IRESOURCE_H__
