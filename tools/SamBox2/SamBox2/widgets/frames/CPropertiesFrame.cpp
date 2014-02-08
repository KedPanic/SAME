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
#include "cpropertiesframe.h"
#include "ui_cpropertiesframe.h"

#include "SamBox.h"
#include "resources/IResource.h"

#include "properties/CTextureFrame.h"

CPropertiesFrame::CPropertiesFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPropertiesFrame),
    m_eLastFrameVisible(e_ResourceType_Nb)
{
    ui->setupUi(this);

    ui->frameHeader->setVisible(false);

    // create frame per resource type.
    m_apFrames[e_ResourceType_Font] = NULL;
    m_apFrames[e_ResourceType_Mesh] = NULL;
    m_apFrames[e_ResourceType_Texture] = new CTextureFrame(ui->frameResourceProperties);

    for(uint32 nIndex = 0; nIndex < e_ResourceType_Nb; ++nIndex)
    {
        if(m_apFrames[nIndex]) /// TEMP
        {
            ui->frameResourceProperties->layout()->addWidget(m_apFrames[nIndex]);
            m_apFrames[nIndex]->setVisible(false);
        }
    }
}

CPropertiesFrame::~CPropertiesFrame()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////
/// SLOTS
/////////////////////////////////////////////////////////////////
void CPropertiesFrame::on_resourceSelected(IResource *p_pResource)
{    
    if(p_pResource)
    {
        p_pResource->Load();
        ui->frameHeader->setVisible(true);

        ui->labelIcon->setPixmap(p_pResource->icon().pixmap(32, 32));
        ui->labelName->setText(p_pResource->text());

        if(m_eLastFrameVisible < e_ResourceType_Nb && p_pResource->GetResourceType() != m_eLastFrameVisible)
        {
            m_apFrames[m_eLastFrameVisible]->setVisible(false);
        }

        if(p_pResource->GetResourceType() < e_ResourceType_Nb)
        {
            m_eLastFrameVisible = p_pResource->GetResourceType();
            m_apFrames[p_pResource->GetResourceType()]->setVisible(true);
            m_apFrames[p_pResource->GetResourceType()]->SetResource(p_pResource);
        }
    }
    else
    {
        ui->frameHeader->setVisible(false);
    }
}
