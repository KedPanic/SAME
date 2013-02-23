//===========================================
// Copyright (c) Stone Age Machine, 2011-2012
//===========================================
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "wx/wxSamBox.h"

namespace sam
{
    class CDatabase : public Database
    {
    public:
        CDatabase(wxWindow* parent);
		~CDatabase();

    private:
		bool m_bForceClose;

		//////////////////////////////////////////////////////////////////////////
		//                    DATABASE IMPLEMENTATION                           //
		//////////////////////////////////////////////////////////////////////////
		void OnClose( wxCloseEvent& event );
    };
}

#endif //__DATABASE_H__
