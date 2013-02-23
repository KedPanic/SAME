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
#include "qt/CFolderViewer.h"
#include "qt/CHandleWidget.h"
#include "CFolder.h"

#include <QtWidgets/QLabel>

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CFolderViewer::CFolderViewer(QWidget* p_pParent/* = NULL*/)
				: QGraphicsView(p_pParent), m_pFolder(NULL)
			{
				QGraphicsScene *pGraphicsScene = new QGraphicsScene();
				setScene(pGraphicsScene);				
			}
			
			CFolderViewer::~CFolderViewer()
			{

			}

			void CFolderViewer::Update()
			{
				setSceneRect(0, 0, parentWidget()->width(), parentWidget()->height());

				if(m_pFolder)
				{
					SetFolder(m_pFolder);
				}
			}

			void CFolderViewer::SetFolder(CFolder *p_pFolder)
			{
				SAM_ASSERT(p_pFolder, "Folder is null");
				m_pFolder = p_pFolder;
				scene()->clear();				

				const CFolder::Folders &aFolders = m_pFolder->GetFolders();
				CFolder::Folders::const_iterator it_begin = aFolders.begin(), it_end = aFolders.end();
				uint32 nPosX = 0, nPosY = 0;

				for(; it_begin != it_end; ++it_begin, nPosX += 94)
				{	
					if(nPosX + 94 > size().width())
					{
						nPosX = 0;
						nPosY += 70;
					}
					CHandleWidget *pHandleWidget = new CHandleWidget((*it_begin)->GetDir().dirName(), QPixmap(QStringLiteral(":/data/48x48/directory.png")));

					QGraphicsProxyWidget *pProxy = scene()->addWidget(pHandleWidget);
					pProxy->setPos(nPosX, nPosY);
				}
			}

			void CFolderViewer::Scale(int32 p_nFactor)
			{
				return;
				qreal scale = qPow(qreal(2), (p_nFactor - 50) / qreal(50));

				QMatrix m;
				m.scale(scale, scale);

				setMatrix(m);
				QMatrix mm = matrix();

				// compute width of the viewer with current scale.
				int nWidth = size().width();
				size().setWidth(nWidth - ((nWidth * scale) - nWidth));

				Update();
			}
		}
	}
}
