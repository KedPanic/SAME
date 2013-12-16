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
#ifndef __SAMBOX_MESH_EXPORTER__
#define __SAMBOX_MESH_EXPORTER__

#include <exporter/IExporter.h>

/// @brief Mesh exporter.
class CMeshExporter : public IExporter
{
public:
	static const uint32 m_nVersion = 0; ///< Metadata structure version.

	/// @brief Retrieves type of exported resource.
	/// 
	/// @return Type of exported resource.
	EResourceType GetResourceType() const override {return e_ResourceType_Mesh;}

	/// @brief Retrieves supported export format.
	/// 
	/// @return Supported export format.
	const SFormat *GetFormat() const override;

	/// @brief Retrieves how many format are supported.
	/// 
	/// @return How many format are supported.
	uint32 GetNbSupportedFormats() const override {return 1;}

	/// @brief Retrieves the default export format.
	/// 
	/// @return Default export format.
	uint32 GetDefaultFormat() const override {return 0;}

	/// @brief Request an export.
	/// 
	/// @param p_pResource Resource to export.
	/// @param p_sDestination Absolute path to write the exported file.
	/// @param p_nPlatformId Used for platform specific options.
	/// 
	/// @return The created job.
	sam::SJob CreateJob(IResource *p_pResource, const String &p_sDestination, sam::ID p_nPlatformId) override;

	/// @brief Method called by the job to export the resource.
	/// 
	/// @param p_pStream Mesh to export.
	/// @param p_sDestination Absolute path to write the exported file.
	/// @param p_oMetadata Metadata used for the exportation.
	/// @param p_nPlatformId Used for platform specific options.
	bool Export(const sam::IStream *p_pStream, const String &p_sDestination, const SMeshMetadata &p_oMetadata, sam::ID p_nPlatformId);
};

#endif // __SAMBOX_MESH_EXPORTER__
