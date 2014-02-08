//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#include "CFileWatcher.h"

#include "SamBox.h"

#if defined(SAM_PLATFORM_WIN)
class CFileWatcherPrivate
{
public:
    CFileWatcherPrivate(CFileWatcher *p_pOwner)
        : m_pOwner(p_pOwner), m_oDirHandle(INVALID_HANDLE_VALUE)
    {

    }

    void SetPath(const QString &p_sPath)
    {
        if(m_oDirHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_oDirHandle);
            CloseHandle(m_oOverlapped.hEvent);

            m_oDirHandle = INVALID_HANDLE_VALUE;
        }

        m_oDirHandle = CreateFile(p_sPath.toStdWString().c_str(), FILE_LIST_DIRECTORY,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
                                OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

        if(m_oDirHandle != INVALID_HANDLE_VALUE)
        {
            m_oOverlapped.hEvent = CreateEvent(NULL, true, false, NULL);

            RefreshWatch();
        }
    }

private:
    OVERLAPPED m_oOverlapped;
    BYTE m_pBuffer[32 * 1024];    
    CFileWatcher *m_pOwner;
    HANDLE m_oDirHandle;

    void RefreshWatch()
    {
        ReadDirectoryChangesW(m_oDirHandle, m_pBuffer, sizeof(m_pBuffer), false,
                              FILE_NOTIFY_CHANGE_FILE_NAME  |
                              FILE_NOTIFY_CHANGE_DIR_NAME   |
                              FILE_NOTIFY_CHANGE_LAST_WRITE |
                              FILE_NOTIFY_CHANGE_CREATION,
                              NULL, &m_oOverlapped, CFileWatcherPrivate::FileWatcherCallback
                              );
    }

    static void CALLBACK FileWatcherCallback(DWORD p_nErrorCode, DWORD p_nNumberOfBytesTransfered, LPOVERLAPPED p_pOverlapped)
    {
       if(p_nNumberOfBytesTransfered == 0)
        {
            return;
        }

        CFileWatcherPrivate *pWatcher = (CFileWatcherPrivate*)p_pOverlapped;
        size_t nOffset = 0;
        PFILE_NOTIFY_INFORMATION pNotify;

        if(p_nErrorCode == ERROR_SUCCESS)
        {
            QString sSecondFilename; ///< used for when it is a renamed action.

            do
            {
                pNotify = (PFILE_NOTIFY_INFORMATION)&pWatcher->m_pBuffer[nOffset];
                nOffset += pNotify->NextEntryOffset;

                QString sFilename = QString::fromWCharArray(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));

                switch(pNotify->Action)
                {
                case FILE_ACTION_ADDED:
                    pWatcher->m_pOwner->emitEvent(CFileWatcher::e_Event_FileCreated, sFilename);
                    break;

                case FILE_ACTION_REMOVED:
                    pWatcher->m_pOwner->emitEvent(CFileWatcher::e_Event_FileRemoved, sFilename);
                    break;

                case FILE_ACTION_MODIFIED:
                    pWatcher->m_pOwner->emitEvent(CFileWatcher::e_Event_FileModified, sFilename);
                    break;

                case FILE_ACTION_RENAMED_OLD_NAME:
                    if(sSecondFilename.isEmpty())
                    {
                        sSecondFilename = sFilename;
                    }
                    else
                    {
                        pWatcher->m_pOwner->emitEvent(CFileWatcher::e_event_FileRenamed, sSecondFilename, sFilename);
                    }
                    break;

                case FILE_ACTION_RENAMED_NEW_NAME:
                    if(sSecondFilename.isEmpty())
                    {
                        sSecondFilename = sFilename;
                    }
                    else
                    {
                        pWatcher->m_pOwner->emitEvent(CFileWatcher::e_event_FileRenamed, sFilename, sSecondFilename);
                    }
                    break;
                }
            }while(pNotify->NextEntryOffset != 0);
        }

        pWatcher->RefreshWatch();
    }
};

#else
# error UNSUPPORTED PLATFORM
#endif

CFileWatcher::CFileWatcher(QObject *parent) :
    QObject(parent),
    m_pFileWatcherPrivate(NULL)
{
    m_pFileWatcherPrivate = new CFileWatcherPrivate(this);
}

void CFileWatcher::setPath(const QString &p_sPath)
{
    m_pFileWatcherPrivate->SetPath(p_sPath);
}

void CFileWatcher::emitEvent(EEvent p_eEvent, const QString &p_sName, const QString &p_sOldName/* = QString()*/)
{
    switch(p_eEvent)
    {
    case e_Event_FileCreated:
        emit fileCreated(p_sName);
        break;

    case e_Event_FileRemoved:
        emit fileRemoved(p_sName);
        break;

    case e_Event_FileModified:
        emit fileModified(p_sName);
        break;

    case e_event_FileRenamed:
        emit fileRenamed(p_sOldName, p_sName);
        break;
    }
}
