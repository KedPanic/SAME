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
#include <SamBoxPCH.h>
#include "qt/CProjectWizard.h"
#include "qt/GeneratedFiles/ui_projectwizard.h"

#include "CSamBox.h"

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CProjectWizard::CProjectWizard(QWidget *parent) 
				: QWidget(parent), ui(new Ui::ProjectWizard)
			{
				ui->setupUi(this);
				ReadLastProjects();

				//////////////////////////////////////////////////////////////////////////
				// SLOT
				//////////////////////////////////////////////////////////////////////////

				/* New Project */
				connect(ui->projectBrowseButton, SIGNAL(clicked()), this, SLOT(BrowseProject()));
				connect(ui->gameBrowseButton, SIGNAL(clicked()), this, SLOT(BrowseGame()));
				connect(ui->createProjectButton, SIGNAL(clicked()), this, SLOT(CreateProject()));

				/* Recent Projects */
				connect(ui->openProjectButton, SIGNAL(clicked()), this, SLOT(OpenProject()));
			}

			CProjectWizard::~CProjectWizard()
			{
				WriteLastProjects();

				delete ui;
			}

			// Read file to list last opened projects.
			void CProjectWizard::ReadLastProjects()
			{
				QByteArray sFilePath((CSamBox::GetInstance()->GetAppFolder() + "/projects.json").toLocal8Bit());

				CJSONSerializer oSerializer((char*)sFilePath.data());
				if(oSerializer.BeginSerialization(true, "projects"))
				{
					while(oSerializer.BeginElem("project"))
					{
						char *sProject = oSerializer.ReadValue("name");
						if(IsDirectory(sProject))
						{
							ui->recentsProjectsView->addItem(sProject);
						}
						oSerializer.EndElem();
					}
					oSerializer.EndSerialization();
				}
			}

			// Write file to list last opened projects.
			void CProjectWizard::WriteLastProjects()
			{
				QByteArray sFilePath((CSamBox::GetInstance()->GetAppFolder() + "/projects.json").toLocal8Bit());

				CJSONSerializer oSerializer((char*)sFilePath.data());
				if(oSerializer.BeginSerialization(false, "projects"))
				{
					for(int32 index = 0; index < ui->recentsProjectsView->count(); ++index)
					{
						QListWidgetItem *pItem = ui->recentsProjectsView->item(index);

						oSerializer.BeginElem("project");
						QByteArray sName(pItem->text().toLocal8Bit());
						oSerializer.WriteValue("name", (char*)sName.data());
						oSerializer.EndElem();
					}

					oSerializer.EndSerialization();
				}
			}

			//////////////////////////////////////////////////////////////////////////
			//								SLOTS								    //
			//////////////////////////////////////////////////////////////////////////
			void CProjectWizard::BrowseProject()
			{
				QDir dir = OpenDirDialog(this, "Project Location");
				ui->projectLocation->setText(dir.absolutePath() + "/");
			}

			void CProjectWizard::BrowseGame()
			{
				QDir dir = OpenDirDialog(this, "Game Location");
				ui->gameLocation->setText(dir.absolutePath() + "/");
			}

			void CProjectWizard::CreateProject()
			{
				QDir oDir(ui->projectLocation->text());
				if(oDir.exists() && oDir.isAbsolute())
				{
					if(CSamBox::GetInstance()->CreateProject(ui->projectLocation->text()))
					{
						// Create folders.
						QDir sFolder(ui->projectLocation->text());
						sFolder.mkdir("packages");
						sFolder.mkdir("worlds");
						sFolder.mkdir("archetypes");

						ui->recentsProjectsView->addItem(ui->projectLocation->text());

						// Go to SamBox.
						CSamBox::GetInstance()->OpenSamBox();
					}
				}
			}

			void CProjectWizard::OpenProject()
			{
				QListWidgetItem *pItem = ui->recentsProjectsView->currentItem();
				if(pItem)
				{
					// change the widget position.
					QListWidgetItem *pClone = pItem->clone();
					delete pItem;
					ui->recentsProjectsView->insertItem(0, pClone);
					ui->recentsProjectsView->setCurrentRow(0);

					CSamBox::GetInstance()->OpenProject(pClone->text());

					// Go to SamBox.
					CSamBox::GetInstance()->OpenSamBox();
				}
			}
		}
	}
}
