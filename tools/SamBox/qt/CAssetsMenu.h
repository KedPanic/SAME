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
#ifndef __SAMBOX_CASSETS_MENU__
#define __SAMBOX_CASSETS_MENU__

namespace sam
{
	namespace box
	{
		namespace qt
		{
			class CAssetsMenu : public QObject
			{
				Q_OBJECT

			public:
				enum EType
				{
					e_Type_Archetypes,
					e_Type_Packages,
					e_Type_Worlds,
				};

				CAssetsMenu();

				void Show(const QPoint &p_oPosition, EType p_eType, bool p_bIsRoot);

			private:
				EType m_eType;
				QMenu m_aMenu[e_Type_Worlds + 1];
				QAction *m_pCreateFolder;
				QAction *m_pDeleteFolder;
				QAction *m_pImportAsset;

			public slots:
				void CreateFolder();
				void DeleteFolder();

				void CreateArchetype();
				void CreatePackage();
				void CreateWorld();	

				void ImportAsset();
			};
		}
	}
}

#endif // __SAMBOX_CASSETS_MENU__
