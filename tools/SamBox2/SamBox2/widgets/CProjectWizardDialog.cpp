#include "SamBox.h"
#include "CProjectWizardDialog.h"
#include "ui_cprojectwizarddialog.h"

#include "CSamBox.h"
#include "CProject.h"
#include "CPlatform.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QCheckBox>

CProjectWizardDialog::CProjectWizardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CProjectWizardDialog)
{
    ui->setupUi(this);

    // set default project path.
    int nCurrentFolderIndex = 1;
    QDir oDefaultProjectDir;
    QString sDefaultProjectPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/New SamBox Project";
    oDefaultProjectDir.setPath(sDefaultProjectPath);
    while(oDefaultProjectDir.exists())
    {
        oDefaultProjectDir.setPath(QString(sDefaultProjectPath + " %1").arg(nCurrentFolderIndex));
        nCurrentFolderIndex++;
    }

    ui->textProjectLocation->setText(oDefaultProjectDir.absolutePath());

    // set available platforms.
    const Platforms &aPlatforms = g_pSamBox->GetSupportedPlatforms();
    for(uint nIndex = 0; nIndex < aPlatforms.size(); ++nIndex)
    {
        QCheckBox *pCheckBox = new QCheckBox(ui->optionsPlatforms);
        pCheckBox->setObjectName(QStringLiteral("checkBox"));
        pCheckBox->setLayoutDirection(Qt::LeftToRight);
        pCheckBox->setCheckable(true);

        if(nIndex == 0) // 0 = PC
        {
            pCheckBox->setChecked(true);
            pCheckBox->setEnabled(false);
            pCheckBox->setText("PC (default)");
        }
        else
        {
            pCheckBox->setText(aPlatforms[nIndex]->GetName().c_str());
        }

        ui->verticalLayout_5->addWidget(pCheckBox);

        m_aPlatformOptions.push_back(pCheckBox);
    }

    // set available scene manager.
    // TODO: create scene manager per editor mode.

    // set recents projects.
    sam::String sRecentProjectFile = (QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/recentprojects.json").toStdString();
    if(QFile::exists(sRecentProjectFile.c_str()))
    {
        sam::CJSONSerializer oSerializer(sRecentProjectFile.c_str());
        oSerializer.BeginSerialization(true, "projects");
        while(oSerializer.BeginElem("project"))
        {
            QString sProjectPath = oSerializer.ReadValue("path");
            ui->listRecentProjects->addItem(sProjectPath);
           oSerializer.EndElem();
        }

        oSerializer.EndSerialization();

        ui->listRecentProjects->setCurrentRow(0);
    }
    else
    {
        ui->ButtonOpen->setEnabled(false);
    }

    // create project is the default tab.
    ui->Wizard->setCurrentIndex(1);
}

CProjectWizardDialog::~CProjectWizardDialog()
{
    sam::String sRecentProjectFile = (QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/recentprojects.json").toStdString();
    sam::CJSONSerializer oSerializer(sRecentProjectFile.c_str());
    oSerializer.BeginSerialization(false, "projects");
    for(int32 nIndex = 0; nIndex < ui->listRecentProjects->count(); ++nIndex)
    {
        QListWidgetItem *pItem = ui->listRecentProjects->item(nIndex);

        oSerializer.BeginElem("project");
        oSerializer.WriteValue("path", pItem->text().toStdString().c_str());
        oSerializer.EndElem();
    }
    oSerializer.EndSerialization();

    delete ui;
}

/////////////////////////////////////////////////////////////////
/// SLOTS
/////////////////////////////////////////////////////////////////
void CProjectWizardDialog::on_ButtonCreateProject_clicked()
{
    if(ui->textProjectLocation->text().isEmpty() == false)
    {
        CProject *pProject = g_pSamBox->GetCurrentProject();
        if(pProject != NULL)
        {
            QMessageBox oMsgBox(QMessageBox::Warning, "SamBox - Warning", QString("Do you want to save your project %1 ?").arg(pProject->GetProjectName().c_str()), QMessageBox::Ok);
            switch(oMsgBox.exec())
            {
            case QMessageBox::Save:
                pProject->SaveProject();
                break;

            case QMessageBox::Discard:
                break;

            case QMessageBox::Cancel:
            default:
                // nothing to do.
                break;
            }
        }

        // create configuration.
        CProject::SConfiguration oConfiguration;
        {
            // platforms.
            const Platforms &aPlatforms = g_pSamBox->GetSupportedPlatforms();
            for(uint32 nIndex = 0; nIndex < m_aPlatformOptions.size(); ++nIndex)
            {
                if(m_aPlatformOptions[nIndex]->isChecked())
                {
                    oConfiguration.m_aPlatforms.push_back(aPlatforms[nIndex]);
                }
            }

            // editor mode.
            if(ui->option2dMode->isChecked())
            {
                oConfiguration.m_eMode = e_Mode_2D;
            }
            else
            {
                oConfiguration.m_eMode = e_Mode_3D;
            }

            // scene manager.
            oConfiguration.m_sSceneManager = ui->optionSceneManager->currentText().toStdString();
        }

        // create project.
        QDir oDir(ui->textProjectLocation->text());
        sam::String sName = oDir.dirName().toStdString();
        sam::String sPath = oDir.path().toStdString();
        pProject = CreateNewProject(sName, sPath, &oConfiguration);

        // add the project to the list.
        ui->listRecentProjects->insertItem(0, oDir.absolutePath());

        // sent event project created.
        emit OnProjectCreated(pProject);

        deleteLater();
    }
}

void CProjectWizardDialog::on_ButtonBrowse_clicked()
{
    QFileDialog oDialog(this);
    oDialog.setFileMode(QFileDialog::Directory);

    if(oDialog.exec())
    {
        // directory have to be empty.
        if(oDialog.directory().entryList(QDir::NoDotAndDotDot | QDir::Files).count() != 0)
        {
            QMessageBox oMsgBox(QMessageBox::Information, "SamBox - Info", "Unable to create project. Folder have to be empty.", QMessageBox::Ok);
            oMsgBox.exec();
        }
        else
        {
            ui->textProjectLocation->setText(oDialog.directory().absolutePath());
        }
    }
}

void CProjectWizardDialog::on_ButtonOpen_clicked()
{
    // remove the selected item from the list.
    QListWidgetItem *pItem = ui->listRecentProjects->selectedItems()[0];
    int nRow = ui->listRecentProjects->row(pItem);
    ui->listRecentProjects->takeItem(nRow);

    // create project.
    QDir oDir(pItem->text());
    sam::String sName = oDir.dirName().toStdString();
    sam::String sPath = oDir.path().toStdString();
    CProject *pProject = new CProject(sName, sPath);
    pProject->LoadProject();

    // sent event project created.
    emit OnProjectOpened(pProject);

    ui->listRecentProjects->insertItem(0, pItem);

    deleteLater();
}
