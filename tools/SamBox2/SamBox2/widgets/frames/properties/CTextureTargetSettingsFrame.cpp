#include "CTextureTargetSettingsFrame.h"
#include "ui_ctexturetargetsettingsframe.h"

#include "SamBox.h"
#include "CPlatform.h"
#include "exporter/CExporterManager.h"
#include "exporter/IExporter.h"

CTextureTargetSettingsFrame::CTextureTargetSettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CTextureTargetSettingsFrame),
    m_pPlatform(NULL)
{
    ui->setupUi(this);
}

CTextureTargetSettingsFrame::~CTextureTargetSettingsFrame()
{
    delete ui;
}

void CTextureTargetSettingsFrame::Initialize(CPlatform *p_pPlatform)
{
    m_pPlatform = p_pPlatform;

    // set supported size.
    for(uint32 nMaxSize = 32; nMaxSize <= 4096; nMaxSize <<= 1)
    {
        ui->comboBoxSize->addItem(QString::number(nMaxSize));
    }

    // set supported format.
    IExporter *pExporter = g_pExporterManager->GetExporter(e_ResourceType_Texture, p_pPlatform->GetExporterName(e_ResourceType_Texture).c_str());
    const IExporter::SFormat *pFormats = pExporter->GetFormat();
    for(uint32 nIndex = 0; nIndex < pExporter->GetNbSupportedFormats(); ++nIndex)
    {
        ui->comboBoxFormat->addItem(pFormats[nIndex].m_sReadableName);
        ui->comboBoxFormat->setItemData(nIndex, pFormats[nIndex].m_nFormat);
    }
}

void CTextureTargetSettingsFrame::SetSelection(int p_nSizeMaxSelection, int p_nFormatSelection)
{
    ui->comboBoxSize->setCurrentIndex(p_nSizeMaxSelection);
    ui->comboBoxFormat->setCurrentIndex(p_nFormatSelection);
}

int CTextureTargetSettingsFrame::GetSizeMax() const
{
    return ui->comboBoxSize->currentText().toInt();
}

int CTextureTargetSettingsFrame::GetFormat() const
{
    return ui->comboBoxFormat->currentData().toInt();
}
