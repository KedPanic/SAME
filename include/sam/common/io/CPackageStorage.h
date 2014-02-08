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
#ifndef __CPACKAGE_STORAGE__
#define __CPACKAGE_STORAGE__

#include <common/io/IResourceStorage.h>

namespace sam
{
	/// @brief Binary package to arrange the resources.
	/// 
	/// @remarks
	///				=============================
	///		HEADER	| SAMPACK! : 64 bits		|
	///				| version number: 32 bits	|
	///				| number of assets: 32 bits	|
	///				=============================
	///		ASSETS	| name: 2048 bits			|
	///		LIST	| position: 32 bits			|
	///				| xxxxxxxxxxxxxxxxxxxxxxxxx |
	///				=============================
	///		ASSETS  | size: 32 bits			    |
	///				| data: size bits			|
	///				| xxxxxxxxxxxxxxxxxxxxxxxxx |
	///				=============================
	class SAM_COMMON_API CPackageStorage : public IResourceStorage
	{
	public:
		static const uint32 ms_nVersion = '1.0';

		/// @brief Constructor.
		/// 
		/// @param p_sFullPath Full path.
		CPackageStorage(const char *p_sFullPath);

		/// @brief Destructor.
		~CPackageStorage();

		/// @brief Retrieves type of resource storage.
		/// 
		/// @return Type of resource storage.
		EResourceStorageType GetType() const {return e_ResourceStorage_Package;}

		/// @brief Retrieves full path of the location.
		/// 
		/// @return Full location path.
		const char *GetFullPath() const {return m_sFullPath;}

		/// @brief Retrieves IStream from the storage.
		/// 
		/// @param p_sName Name of the resource.
		///
		/// @return Pointer to the IStream or null if an error occurred.
		IStream *GetResource(const char *p_sName);

		/// @brief Retrieves path of the specified resource.
		/// 
		/// @param p_sName Name of the resource.
		///
		/// @return Path or null string.
		const char *GetPath(const char *p_sName) const;

		/// @brief Reload location.
		void Reload();

	private:
		struct SAsset
		{
			char m_sName[256];
			uint32 m_nPosition;
			IStream *m_pStream; ///< Null if not loaded.
		};

		typedef std::map<const char*, const SAsset, cmp_str> Assets;
		Assets m_aAssets;	///< Array of assets in the package.

		CFile m_oFile;		///< Physical package.
		char *m_sFullPath;	///< Full path of the stream location.

		/// @brief Create resource from package file.
		/// 
		/// @param p_nPosition Resource position in the package.
		/// 
		/// @return Created resource.
		IStream *CreateResource(uint32 p_nPosition);
	};
}
#endif // __CPACKAGE_STORAGE__
