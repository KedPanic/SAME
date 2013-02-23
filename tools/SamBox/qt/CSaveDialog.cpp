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
#include "SamBoxPCH.h"
#include "qt/CSaveDialog.h"
#include "qt/GeneratedFiles/ui_savedialog.h"

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CSaveDialog::CSaveDialog(const QString &p_sMessage, QWidget *p_pParent /*= 0*/)
				: QDialog(p_pParent, Qt::Window | Qt::WindowTitleHint), ui(new Ui::SaveDialog)
			{
				ui->setupUi(this);
				ui->message->setText(p_sMessage);

				//////////////////////////////////////////////////////////////////////////
				// SLOT
				//////////////////////////////////////////////////////////////////////////
				connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(Save()));
				connect(ui->dontSaveButton, SIGNAL(clicked()), this, SLOT(DontSave()));
				connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(Cancel()));
			}

			CSaveDialog::~CSaveDialog()
			{
			}

			//////////////////////////////////////////////////////////////////////////
			//								SLOTS								    //
			//////////////////////////////////////////////////////////////////////////
			void CSaveDialog::Save()
			{
				done(e_Save);
			}

			void CSaveDialog::DontSave()
			{
				done(e_DontSave);
			}

			void CSaveDialog::Cancel()
			{
				done(e_Cancel);
			}
		}
	}
}
