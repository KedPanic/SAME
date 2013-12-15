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
#ifndef __SAMBOX_CUSTOM_EVENT__
#define __SAMBOX_CUSTOM_EVENT__

//////////////////////////////////////////////////////////////////////////
//							END OF INITIALIZATION						//
//////////////////////////////////////////////////////////////////////////
class CInitCompletedEvent;
wxDECLARE_EVENT(boxEVT_INIT_COMPLETED, CInitCompletedEvent);

/// @brief Event sended when 
class CInitCompletedEvent : public wxEvent
{
public:
	/// @brief Constructor.
	CInitCompletedEvent(int p_nWinId = wxID_ANY)
		: wxEvent(p_nWinId, boxEVT_INIT_COMPLETED)
	{

	}

	/// @brief Copy constructor.
	/// 
	/// @param p_oEvent Instance to copy.
	CInitCompletedEvent(const CInitCompletedEvent &p_oEvent)
		: wxEvent(p_oEvent)
	{
	}

	/// @brief Copy the event.
	/// 
	/// @return Pointer to the copy.
	virtual wxEvent *Clone() const {return new CInitCompletedEvent(*this); }

private:
	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(CInitCompletedEvent);
};

typedef void (wxEvtHandler::*boxInitCompletedEventFunction)(CInitCompletedEvent&);


//////////////////////////////////////////////////////////////////////////
//							LOADING COMPLETED		 					//
//////////////////////////////////////////////////////////////////////////
class CLoadingCompletedEvent;
wxDECLARE_EVENT(boxEVT_LOADING_COMPLETED, CLoadingCompletedEvent);

class CLoadingCompletedEvent : public wxEvent
{
public:
	/// @brief Constructor.
	CLoadingCompletedEvent(int p_nWinId = wxID_ANY)
		: wxEvent(p_nWinId, boxEVT_LOADING_COMPLETED)
	{

	}

	/// @brief Copy constructor.
	/// 
	/// @param p_oEvent Instance to copy.
	CLoadingCompletedEvent(const CLoadingCompletedEvent &p_oEvent)
		: wxEvent(p_oEvent)
	{
	}

	/// @brief Copy the event.
	/// 
	/// @return Pointer to the copy.
	virtual wxEvent *Clone() const {return new CLoadingCompletedEvent(*this); }

private:
	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(CLoadingCompletedEvent);
};

//////////////////////////////////////////////////////////////////////////
//								OPEN PROJECT							//
//////////////////////////////////////////////////////////////////////////
class COpenProjectEvent;
wxDECLARE_EVENT(boxEVT_OPEN_PROJECT, COpenProjectEvent);

class COpenProjectEvent : public wxEvent
{
public:
	/// @brief Constructor.
	COpenProjectEvent(int p_nWinId = wxID_ANY)
		: wxEvent(p_nWinId, boxEVT_OPEN_PROJECT), m_sPath("'")
	{

	}

	/// @brief Copy constructor.
	/// 
	/// @param p_oEvent Instance to copy.
	COpenProjectEvent(const COpenProjectEvent &p_oEvent)
		: wxEvent(p_oEvent), m_sPath(p_oEvent.m_sPath)
	{
	}

	/// @brief Copy the event.
	/// 
	/// @return Pointer to the copy.
	virtual wxEvent *Clone() const {return new COpenProjectEvent(*this); }

	/// @brief Set the project.
	///
	/// @param p_sPath Project path.
	void SetProjectParth(const wxString &p_sPath) {m_sPath = p_sPath;}

	/// @brief Retrieves the project path.
	/// 
	/// @return Project path.
	const wxString &GetProjectPath() const {return m_sPath;}

private:
	wxString m_sPath; ///< Project path.

	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(COpenProjectEvent);
};

typedef void (wxEvtHandler::*boxOpenProjectEventFunction)(COpenProjectEvent&);

//////////////////////////////////////////////////////////////////////////
//								CREATE PROJECT							//
//////////////////////////////////////////////////////////////////////////
class CCreateProjectEvent;
wxDECLARE_EVENT(boxEVT_CREATE_PROJECT, CCreateProjectEvent);

class CCreateProjectEvent : public wxEvent
{
public:
	/// @brief Constructor.
	CCreateProjectEvent(int p_nWinId = wxID_ANY)
		: wxEvent(p_nWinId, boxEVT_CREATE_PROJECT), m_sPath("")
	{

	}

	/// @brief Copy constructor.
	/// 
	/// @param p_oEvent Instance to copy.
	CCreateProjectEvent(const CCreateProjectEvent &p_oEvent)
		: wxEvent(p_oEvent), m_sPath(p_oEvent.m_sPath)
	{
	}

	/// @brief Copy the event.
	/// 
	/// @return Pointer to the copy.
	virtual wxEvent *Clone() const {return new CCreateProjectEvent(*this); }

	/// @brief Set the project.
	///
	/// @param p_sPath Project path.
	void SetProjectParth(const wxString &p_sPath) {m_sPath = p_sPath;}

	/// @brief Retrieves the project path.
	/// 
	/// @return Project path.
	const wxString &GetProjectPath() const {return m_sPath;}

private:
	wxString m_sPath; ///< Project path.

	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(CCreateProjectEvent);
};

typedef void (wxEvtHandler::*boxCreateProjectEventFunction)(CCreateProjectEvent&);

//////////////////////////////////////////////////////////////////////////
//								CREATE PACKAGE							//
//////////////////////////////////////////////////////////////////////////
class CCreatePackageEvent;
wxDECLARE_EVENT(boxEVT_CREATE_PACKAGE, CCreatePackageEvent);

class CCreatePackageEvent : public wxCommandEvent
{
public:
	/// @brief Constructor.
	CCreatePackageEvent(int p_nWinId = wxID_ANY)
		: wxCommandEvent(boxEVT_CREATE_PACKAGE, p_nWinId), m_pPackage(NULL)
	{

	}

	/// @brief Copy constructor.
	/// 
	/// @param p_oEvent Instance to copy.
	CCreatePackageEvent(const CCreatePackageEvent &p_oEvent)
		: wxCommandEvent(p_oEvent), m_pPackage(p_oEvent.m_pPackage)
	{
	}

	/// @brief Copy the event.
	/// 
	/// @return Pointer to the copy.
	virtual wxEvent *Clone() const {return new CCreatePackageEvent(*this); }

	/// @brief Set the created package.
	/// 
	/// @param p_pPackage Created package.
	void SetPackage(CFolder *p_pPackage) {m_pPackage = p_pPackage;}

	/// @brief Retrieves created package.
	/// 
	/// @return Pointer to the created package.
	CFolder *GetPackage() const {return m_pPackage;}

private:
	CFolder *m_pPackage;

	wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(CCreatePackageEvent);
};

typedef void (wxEvtHandler::*boxCreatePackageEventFunction)(CCreatePackageEvent&);

#endif // __SAMBOX_CUSTOM_EVENT__
