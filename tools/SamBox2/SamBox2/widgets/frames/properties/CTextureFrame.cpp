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
#include "CTextureFrame.h"
#include "ui_ctextureframe.h"

#include "SamBox.h"
#include "CSamBox.h"
#include "CProject.h"
#include "CPlatform.h"
#include "exporter/CExporterManager.h"
#include "resources/CTextureResource.h"
#include "resources/STextureMetadata.h"

#include "CTextureTargetSettingsFrame.h"

#include <QDir>

CTextureFrame::CTextureFrame(QWidget *parent) :
    IPropertiesFrame(parent),
    ui(new Ui::CTextureFrame)
{
    ui->setupUi(this);

    // Common.
    ui->comboBoxWrapMode->addItem("Mirror");        // sam::e_TextureWrap_Mirror
    ui->comboBoxWrapMode->addItem("Repeat");        // sam::e_TextureWrap_Repeat
    ui->comboBoxWrapMode->addItem("Clamp");         // sam::e_TextureWrap_Clamp

    ui->comboBoxFilterMode->addItem("Point");       // e_TextureFilter_Point
    ui->comboBoxFilterMode->addItem("Bilinear");    // e_TextureFilter_Bilinear
    ui->comboBoxFilterMode->addItem("Trilinear");   // e_TextureFilter_Trilinear

    // Mip Maps.
    ui->checkBoxMipMapGenerate->setChecked(true);

    ui->comboBoxMipMapFilter->addItem("Box");       // e_MipMapFilter_Box
    ui->comboBoxMipMapFilter->addItem("Triangle");  // e_MipMapFilter_Triangle
    ui->comboBoxMipMapFilter->addItem("Kaiser");    // e_MipMapFilter_Kaiser

    // Target Settings.
    CProject *pProject = g_pSamBox->GetCurrentProject();

    const Platforms &aPlatforms = pProject->GetConfiguration().m_aPlatforms;
    Platforms::const_iterator oPlatformIt = aPlatforms.begin();
    Platforms::const_iterator oPlatformItEnd = aPlatforms.end();
    while(oPlatformIt != oPlatformItEnd)
    {
        CTextureTargetSettingsFrame *pTargetSettings = new CTextureTargetSettingsFrame(ui->tabWidgetPlatform);
        pTargetSettings->Initialize((*oPlatformIt));

        ui->tabWidgetPlatform->addTab(pTargetSettings, (*oPlatformIt)->GetName().c_str());
        ++oPlatformIt;
    }
}

CTextureFrame::~CTextureFrame()
{
    delete ui;
}

void CTextureFrame::SetResource(IResource *p_pTextureResource)
{
    if(m_pResource)
    {
        m_pResource->Unload();
    }

    m_pResource = p_pTextureResource;
    CTextureResource *pTextureResource = (CTextureResource*)m_pResource;
    const STextureMetadata &oMetadata = pTextureResource->GetMetadata();

    // update the properties panel.
    ui->comboBoxWrapMode->setCurrentIndex(oMetadata.m_eTextureWrap);
    ui->comboBoxFilterMode->setCurrentIndex(oMetadata.m_eTextureFilter);
    ui->checkBoxMipMapGenerate->setChecked(oMetadata.m_bGenerateMipMap);
    ui->comboBoxMipMapFilter->setCurrentIndex(oMetadata.m_eMipMapFilter);

    for(uint32 nIndex = 0; nIndex < oMetadata.m_aTargetSettings.size(); ++nIndex)
    {
        int nSelectionIndex = 7;
        uint32 nMaxSize = oMetadata.m_aTargetSettings[nIndex].m_nMaxSize;
        while(nMaxSize > 32 /* min size */)
        {
            nMaxSize >>= 1;
            --nSelectionIndex;
        }

        CTextureTargetSettingsFrame *pTargetSettings = (CTextureTargetSettingsFrame*)ui->tabWidgetPlatform->widget(nIndex);
        pTargetSettings->SetSelection(7 - nSelectionIndex, oMetadata.m_aTargetSettings[nIndex].m_nFormat);
    }
}

void CTextureFrame::on_pushButton_clicked()
{
    CTextureResource *pTextureResource = (CTextureResource*)m_pResource;
    CProject *pProject = g_pSamBox->GetCurrentProject();

    // save the settings.
    STextureMetadata oLocalMetadata;
    oLocalMetadata.m_eTextureWrap = (sam::ETextureWrap )ui->comboBoxWrapMode->currentIndex();
    oLocalMetadata.m_eTextureFilter = (ETextureFilter)ui->comboBoxFilterMode->currentIndex();
    oLocalMetadata.m_bGenerateMipMap = ui->checkBoxMipMapGenerate->isChecked();
    oLocalMetadata.m_eMipMapFilter = (EMipMapFilter)ui->comboBoxMipMapFilter->currentIndex();
    for(int nIndex = 0; nIndex < ui->tabWidgetPlatform->count(); ++nIndex)
    {
        CTextureTargetSettingsFrame *pTargetSettings = (CTextureTargetSettingsFrame*)ui->tabWidgetPlatform->widget(nIndex);

        STextureMetadata::STargetSettings targetSettings;
        targetSettings.m_nTargetId = pTargetSettings->GetPlatform()->GetId();
        targetSettings.m_nFormat = pTargetSettings->GetFormat();
        targetSettings.m_nMaxSize = pTargetSettings->GetSizeMax();
        oLocalMetadata.m_aTargetSettings.push_back(targetSettings);
    }
    pTextureResource->SetMetadata(oLocalMetadata);

    // write the metadata.
    sam::String sMetadataPath = pTextureResource->GetPath() + ".metadata";
    sam::CJSONSerializer oSerializer(sMetadataPath.c_str());
    oSerializer.BeginSerialization(false, sMetadataPath.c_str());
    pTextureResource->Write(&oSerializer);
    oSerializer.EndSerialization();

    // export per platform.
    for(int nIndex = 0; nIndex < ui->tabWidgetPlatform->count(); ++nIndex)
    {
        CTextureTargetSettingsFrame *pTargetSettings = (CTextureTargetSettingsFrame*)ui->tabWidgetPlatform->widget(nIndex);
        g_pExporterManager->RequestExport(pTextureResource, pTargetSettings->GetFormat(), pTargetSettings->GetPlatform());
    }
}
