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
#ifndef CTEXTURETARGETSETTINGSFRAME_H
#define CTEXTURETARGETSETTINGSFRAME_H

#include <QFrame>

namespace Ui {
class CTextureTargetSettingsFrame;
}

class CPlatform;

class CTextureTargetSettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CTextureTargetSettingsFrame(QWidget *parent = 0);
    ~CTextureTargetSettingsFrame();

    void Initialize(CPlatform *p_pPlatform);

    CPlatform *GetPlatform() const {return m_pPlatform;}

    void SetSelection(int p_nSizeMaxSelection, int p_nFormatSelection);

    int GetSizeMax() const;
    int GetFormat() const;

private:
    Ui::CTextureTargetSettingsFrame *ui;
    CPlatform *m_pPlatform;
};

#endif // CTEXTURETARGETSETTINGSFRAME_H
