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
#ifndef __SAMBOX_CFOLDER__
#define __SAMBOX_CFOLDER__

namespace sam
{
	namespace box
	{
		/// @brief Represent a folder in the archetypes/packages/worlds tree.
		class CFolder : public IAllocated
		{
		public:
			typedef std::list<CFolder *> Folders;

			CFolder(const QDir &p_sPath, CFolder *p_pParent = NULL);
			~CFolder();

			QDir &GetDir() {return m_oDir;}

			CFolder *GetParent() const {return m_pParent;}

			void AddFolder(CFolder *p_pFolder);

			const Folders &GetFolders() const {return m_aFolders;}

		private:
			QDir m_oDir;
			CFolder *m_pParent;

			typedef std::list<CFile *> Files;
			Files m_aFiles;	///< List of files.

			typedef std::list<CFolder *> Folders;
			Folders m_aFolders; ///< List of folders.
		};

		Q_DECLARE_METATYPE(CFolder*);
	}
}

#endif // __SAMBOX_CFOLDER__
