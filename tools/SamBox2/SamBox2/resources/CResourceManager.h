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
#ifndef __SAMBOX_RESOURCE_MANAGER__
#define __SAMBOX_RESOURCE_MANAGER__

class CResourceManager
{
public:
	/// @brief Default constructor.
	CResourceManager();
	~CResourceManager();

	/// @brief Add a resource factory.
	/// 
	/// @param p_pResourceFactory Resource factory to add.
	void AddResourceFactory(IResourceFactory *p_pResourceFactory);

	/// @brief Create the resource.
	/// 
	/// @param p_sName	Name of the resource.
    /// @param p_sSourcePath Absolute path of the resource.
    /// @param p_sPackage Name of the package.
	/// @param p_eResourceType Type of resource to create.
	/// 
	/// @return Created resource or NULL if an error occurred.
    IResource *Create(const sam::String &p_sName, const sam::String &p_sSourcePath, const sam::String &p_sPackage, EResourceType p_eResourceType = e_ResourceType_Unknown);

	/// @brief Create the resource.
	/// 
	/// @param p_sName	Name of the resource.
    /// @param p_sSourcePath Absolute path of the resource.
    /// @param p_sPackage Name of the package.
	/// 
	/// @return Created resource or NULL if an error occurred.
	template<class Resource>
    IResource *Create(const sam::String &p_sName, const sam::String &p_sSourcePath, const sam::String &p_sPackage)
	{
        return Create(p_sName, p_sSourcePath, p_sPackage, Resource::GetType());
	}

	/// @brief Retrieve the type of the resource from the name.
	/// 
	/// @param p_sName	Name of the resource.
	/// 
	/// @return Resource type.
	EResourceType FindResourceType(const sam::String &p_sName);

private:
	typedef std::list<IResourceFactory *> ResourceFactories;
	ResourceFactories m_aResourceFactories[e_ResourceType_Nb]; ///< Resource factory arranged per resource type.

	typedef std::map<sam::ID, IResource *> Resources;
	Resources m_aResources[e_ResourceType_Nb]; ///< Array of resource arranged per type.
};

#endif // __SAMBOX_RESOURCE_MANAGER__
