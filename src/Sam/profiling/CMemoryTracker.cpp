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
#include "SamProfilingPCH.h"
#include <profiling/CMemoryTracker.h>

#include <stdlib.h>
#include <fstream>

namespace sam
{
    // Log file.
    std::ofstream logFile;

    CMemoryTracker *CMemoryTracker::m_pMemoryTracker = NULL;

    /// @brief Default constructor
    CMemoryTracker::CMemoryTracker(void)
    {
        m_pMemoryTracker = this;

        // clean file.
        logFile.open("DSMemoryDebug.html");
        logFile.close();

        // create log file            
        logFile.open("DSMemoryDebug.html", std::ios_base::out | std::ios_base::app);

        // HTML Header
        logFile << "<HTML>\n"
            << "<HEAD>\n"
            << "\t<TITLE>sam engine System : Memory Tracker</TITLE>\n"
            << "<HEAD>\n"
            << "<BODY>\n"
            << "\t<TABLE width=\"100%\" height=\"100%\" border=\"1\">\n"
            << "\t\t<TR>\n"
            << "\t\t\t<TD>Type</TD><TD>Add.</TD><TD>File</TD><TD>Line</TD>\n"
            << "\t\t</TR>\n";
    }

    /// @brief Get the unique instance.
    /// 
    /// @return The unique instance of CMemoryManager
    CMemoryTracker *CMemoryTracker::GetInstance(void)
    {
        SAM_ASSERT(m_pMemoryTracker != NULL, "Memory tracker is null");

        return m_pMemoryTracker;
    }

    /// @brief Destroy the unique instance of CMemoryManager
    void CMemoryTracker::Release()
    {
        if(m_pMemoryTracker)
        {			
            m_pMemoryTracker->Log();

            // HTML Foot.
            logFile << "</BODY>\n"
                << "</HTML>";

            logFile.close();

            delete m_pMemoryTracker;
            m_pMemoryTracker = NULL;
        }
    }


    /// @brief Register a memory allocation.
    /// 
    /// @param _pPtr  Memory address.
    /// @param _iSize Allocated memory size.
    /// @param _sFile Name of the file.
    /// @param _iLine Line number in the file.
    void CMemoryTracker::RegisterAlloc(void *_pPtr, size_t _iSize, const char *_sFile, int _iLine)
    {		
        MemoryBloc *bloc = new MemoryBloc;
        bloc->ptr  = _pPtr;
        bloc->file = new char[strlen(_sFile)];
        strcpy(bloc->file, _sFile);
        bloc->line = _iLine;

        m_aMemoryBlocs[_pPtr] = bloc;

        // log it !
        logFile << "\t\t<TR>\n"
            << "\t\t\t<TD style=\"background-color:#FFCC00\">Alloc</TD><TD>0x" << _pPtr << "</TD><TD>" << _sFile << "</TD><TD>" << _iLine << "</TD>\n"
            << "\t\t</TR>\n";
        logFile.flush();
    }

    /// @brief Register a memory deallocation.
    /// 
    /// @param _pPtr  Memory address.
    void CMemoryTracker::RegisterFree(void *_pPtr)
    {
        MemoryBlocs::iterator it = m_aMemoryBlocs.find(_pPtr);
        if(it != m_aMemoryBlocs.end())
        {
            // log it !
            logFile << "\t\t<TR>\n"
                << "\t\t\t<TD style=\"background-color:#00FF55\">Free</TD><TD>0x" << it->first << "</TD><TD>" << it->second->file << "</TD><TD>" << it->second->line << "</TD>\n"
                << "\t\t</TR>\n";
            logFile.flush();

            // release memory
            delete it->second;
            m_aMemoryBlocs.erase(it);
        }
    }

    /// @brief Log the memory.
    void CMemoryTracker::Log()
    {
        MemoryBlocs::iterator it = m_aMemoryBlocs.begin(), it_end = m_aMemoryBlocs.end();
        if(it != it_end)
        {
            logFile << "</TABLE>\n<BR/><BR/>" 
                << "Memory Leak :\n"
                << "\t<TABLE width=\"100%\" border=\"1\">\n"
                << "\t\t<TR height=\"25\">\n"
                << "\t\t\t<TD>Type</TD><TD>Add.</TD><TD>File</TD><TD>Line</TD>\n"
                << "\t\t</TR>\n";

            // log all memory leak
            for(; it != it_end; it++)
            {
                logFile << "\t\t<TR height=\"25\">\n"
                    << "\t\t\t<TD style=\"background-color:#FF0000\">Leak</TD><TD>0x" << it->first << "</TD><TD>" << it->second->file << "</TD><TD>" << it->second->line << "</TD>\n"
                    << "\t\t</TR>\n";

                delete it->second;
            }

            logFile << "</TABLE>\n";
        }	
        else
		{
            logFile << "</TABLE>\n<BR/><BR/><B>No memory leak</B>\n";
		}

        logFile.flush();
    }
}
