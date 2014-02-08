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
#ifndef CFILEWATCHER_H
#define CFILEWATCHER_H

#include <QObject>

class CFileWatcherPrivate;

class CFileWatcher : public QObject
{
    Q_OBJECT
public:
    explicit CFileWatcher(QObject *parent = 0);

    void setPath(const QString &p_sPath);

signals:
    void fileCreated(const QString &p_sFilepath);
    void fileRemoved(const QString &p_sFilepath);    
    void fileModified(const QString &p_sFilepath);
    void fileRenamed(const QString &p_sOldFilepath, const QString &p_sNewFilepath);

protected:
    enum EEvent
    {
        e_Event_FileCreated,
        e_Event_FileRemoved,
        e_Event_FileModified,
        e_event_FileRenamed,
    };

    void emitEvent(EEvent p_eEvent, const QString &p_sName, const QString &p_sOldName = QString());

private:
    friend class CFileWatcherPrivate;
    CFileWatcherPrivate *m_pFileWatcherPrivate;
};

#endif // CFILEWATCHER_H
