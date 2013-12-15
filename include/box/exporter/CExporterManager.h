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
#ifndef __SAM_EXPORTER_H__
#define __SAM_EXPORTER_H__

class CExporterManager
{
public:
	/// @brief Constructor.
	/// 
	/// @param p_nJobArraySize Number of pushable job in the array.
	CExporterManager(uint32 p_nJobArraySize = 128);
	~CExporterManager();

	/// @brief Request a new export.
	/// 
	/// @param p_pResource Resource to export.
	/// @param p_sDestination Absolute path to write the exported file.
	/// @param p_nOuputFormat Format requested for the export.
	/// @param p_nPlatformId Used for platform specific options.
	void RequestExport(IResource *p_pResource, const String &p_sDestination, uint32 p_nOutputFormat, sam::ID p_nPlatformId);

	/// @brief Register an exporter plugin.
	/// 
	/// @param p_sExporterParth Full path of the exporter to add.
	void RegisterExporter(const char *p_sExporterPath);

	/// @brief Register an exporter.
	/// 
	/// @param p_sExporter Pointer to the exporter to register.
	void RegisterExporter(IExporter *p_pExporter);

	/// @brief Register listener.
	///
	/// @param p_oListener Add a new listener.
	void RegisterListener(IExporterListener *p_pListener);

	/// @brief Submit export to the job manager.
	void Submit();

	/// @brief Retrieves specific exporter.
	/// 
	/// @param p_eResourceType Type of supported ressource by the exporter.
	/// @param p_sExporterName Name of the exporter.
	/// 
	/// @return Pointer to the exporter or null if not found.
	IExporter *GetExporter(EResourceType p_eResourceType, const char *p_sExporterName);

private:
	typedef std::list<IExporter*> Exporters;
	Exporters m_aExporters[e_ResourceType_Nb]; ///< List of available exporters per resource type.

	typedef std::list<IExporterListener*> Listeners;
	Listeners m_aListeners; ///< Exporter listener.

	struct SRequest
	{
		IExporter *m_pExporter;
		//Params m_aParams;
	};

	typedef std::queue<SRequest*> Requests;
	Requests m_aRequests;

	sam::CJobArray *m_pJobArray; ///< Job array for the export.
};

#endif // __SAM_EXPORTER_H__
