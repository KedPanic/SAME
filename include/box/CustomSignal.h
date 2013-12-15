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
#ifndef __SAMBOX_CUSTOM_SIGNAL__
#define __SAMBOX_CUSTOM_SIGNAL__

enum ECustomSignal
{
	e_CustomSignal_ResourceCreated,
	e_CustomSignal_ResourceSelected,
	e_CustomSignal_ProjectInitialized,
};

//////////////////////////////////////////////////////////////////////////
//							RESOURCE CREATED							//
//////////////////////////////////////////////////////////////////////////
class CResourceCreatedSignal : public sam::ISignal
{
public:
	CResourceCreatedSignal(IResource *p_pResource)
		: m_pResource(p_pResource)
	{

	}

	uint32 GetType() const {return e_CustomSignal_ResourceCreated;}

	/// @brief Retrieves the created resource.
	/// 
	/// @return Pointer to the created resource.
	IResource *GetResource() const {return m_pResource;}

private:
	IResource *m_pResource;
};

//////////////////////////////////////////////////////////////////////////
//							RESOURCE SELECTED							//
//////////////////////////////////////////////////////////////////////////
class CResourceSelected : public sam::ISignal
{
public:
	CResourceSelected(IResource *p_pResource)
		: m_pResource(p_pResource)
	{

	}

	uint32 GetType() const {return e_CustomSignal_ResourceSelected;}

	/// @brief Retrieves the created resource.
	/// 
	/// @return Pointer to the created resource.
	IResource *GetResource() const {return m_pResource;}

private:
	IResource *m_pResource;
};

//////////////////////////////////////////////////////////////////////////
//						PROJECT INITIALIZED								//
//////////////////////////////////////////////////////////////////////////
class CProjectInitializedSignal : public sam::ISignal
{
public:
	CProjectInitializedSignal(CProject *p_pProject)
		: m_pProject(p_pProject)
	{

	}

	uint32 GetType() const {return e_CustomSignal_ProjectInitialized;}

	/// @brief Retrieves the project.
	/// 
	/// @return Pointer to the project.
	CProject *GetProject() const {return m_pProject;}

private:
	CProject *m_pProject;
};

#endif // __SAMBOX_CUSTOM_SIGNAL__
