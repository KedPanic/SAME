//===========================================
// Copyright (c) Stone Age Machine, 2011-2012
//===========================================
#include "SamBoxPCH.h"
#include "CDatabase.h"

namespace sam
{
    CDatabase::CDatabase(wxWindow* parent)
        : Database(parent), m_bForceClose(false)
    {
    }

	CDatabase::~CDatabase()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//                    DATABASE IMPLEMENTATION                           //
	//////////////////////////////////////////////////////////////////////////
	void CDatabase::OnClose( wxCloseEvent& event )
	{
		Show(false);

		if(m_bForceClose == false)
		{
			event.Veto();			
		}
	}
}
