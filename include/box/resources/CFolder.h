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
#ifndef __SAMBOX_FOLDER__
#define __SAMBOX_FOLDER__

#include <resources/IResource.h>

/// @brief A folder is a special resource which contain resources.
class CFolder : public IResource
{
public:
	DEFINE_RESOURCE(CFolder, "folder_resource", e_ResourceType_Folder);

	/// @brief Default constructor.
	/// 
	/// @param p_sName Name of the folder.
	/// @param p_sPath Absolute path.
	/// @param p_pParent Pointer the parent (NULL for root folder)
	CFolder(const String &p_sName, const String &p_sPath, CFolder *p_pParent = NULL);
	~CFolder();

	typedef std::vector<IResource *> Resources;
	/// @brief Retrieves the array of the resources.
	/// 
	/// @return Array of the resources.
	const Resources &GetResources() const {return m_aResources;}

	/// @brief Add a new resource.
	/// 
	/// @param p_pResource New folder.
	void AddResource(IResource *p_pResource);

	/// @brief Delete an old resource.
	/// 
	/// @param p_pResource Delete the specified resource.
	void DeleteResource(IResource *p_pResource);

	/// @brief Retrieves parent folder.
	/// 
	/// @return Parent folder.
	CFolder *GetParent() const {return m_pParent;}

	/// @brief Retrieves if it is a root folder.
	/// 
	/// @return True if it is a root folder.
	bool IsRoot() const {return m_pParent == NULL;}

	/// @brief Load resource.
	/// 
	/// @return True if there is no error.
	virtual bool Load() override;

	/// @brief Unload resource.
	/// 
	/// @return True if there is no error.
	virtual bool Unload() override;	

private:
	Resources m_aResources; ///< Array of resources.

	CFolder *m_pParent; ///< Parent of the folder. NULL if the folder is a root folder.
};

#endif // __SAMBOX_FOLDER__
