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
#ifndef __SAMBOX_PLATFORM__
#define __SAMBOX_PLATFORM__

/// @brief A platform define the required exporter for the build.
class CPlatform : public sam::IAllocated
{
public:
	/// @brief Default constructor.
	CPlatform();
	~CPlatform();

	/// @brief Retrieves the name of the platform.
	/// 
	/// @return The name of the platform.
	const String &GetName() const {return m_sName;}

	/// @brief Retrieves the unique id of the platform.
	/// 
	/// @return The unique id of the platform.
	sam::ID GetId() const {return m_nId;}

	/// @brief Retrieves the exporter used for a specific resource type.
	/// 
	/// @return The name of exporter.
	const String &GetExporterName(EResourceType p_eResourceType) const {return m_pExportName[p_eResourceType];}

	/// @brief Retrieves the default format per platf
	/// @brief Read the configuration file.
	/// 
	/// @param p_sFilename Name of the configuration file.
	void Initialize(const char *p_sFilename);

	/// @brief Manual creation.
	/// 
	/// @param p_sName Name of the platform.
	/// @param p_aExportName Array of supported exporter per resource type.
	void Initialize(const char *p_sName, const char *p_aExportName[e_ResourceType_Nb]);

private:
	String m_sName; ///< Name of the platform.
	String m_pExportName[e_ResourceType_Nb]; ///< Array of used exporter.
	sam::ID m_nId; ///< Unique Id  
};

#endif // __SAMBOX_PLATFORM__