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
#ifndef __SAM_IEXPORTER_H__
#define __SAM_IEXPORTER_H__

/// @brief Interface of an exporter.
class IExporter
{
public:	
	/// @brief Supported format by the exporter.
	struct SFormat
	{
		const char *m_sReadableName; ///< Name of the format.
		uint32 m_nFormat;			 ///< ID of the format (internal usage).
	};

	/// @brief Check if the specified format is supported.
	/// 
	/// @param p_nFormat Format ID.
	/// 
	/// @return True if supported.
	INLINE bool IsSupported(uint32 p_nFormat) const
	{
		const SFormat *pFormats = GetFormat();
		for(uint32 nIndex = 0; nIndex < GetNbSupportedFormats(); ++nIndex)
		{
			if(pFormats[nIndex].m_nFormat == p_nFormat)
			{
				return true;
			}
		}

		return false;
	}

	/// @brief Retrieves type of exported resource.
	/// 
	/// @return Type of exported resource.
	virtual EResourceType GetResourceType() const = 0;

	/// @brief Retrieves the name of the exporter.
	/// 
	/// @return Name of the exporter.
	virtual const char *GetName() const = 0;

	/// @brief Retrieves supported export format.
	/// 
	/// @return Supported export format.
	virtual const SFormat *GetFormat() const = 0;

	/// @brief Retrieves how many format are supported.
	/// 
	/// @return How many format are supported.
	virtual uint32 GetNbSupportedFormats() const = 0;

	/// @brief Retrieves the default export format.
	/// 
	/// @return Default export format.
	virtual uint32 GetDefaultFormat() const = 0;

	/// @brief Request an export.
	/// 
	/// @param p_pResource Resource to export.
	/// @param p_sDestination Absolute path to write the exported file.
	/// @param p_nPlatformId Used for platform specific options.
	/// 
	/// @return The created job.
	virtual sam::SJob CreateJob(IResource *p_pResource, const String &p_sDestination, sam::ID p_nPlatformId) = 0;
};

#endif // __SAM_IEXPORTER_H__
