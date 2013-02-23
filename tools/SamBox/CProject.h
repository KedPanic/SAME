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
#ifndef __SAMBOX_CPROJECT__
#define __SAMBOX_CPROJECT__

namespace sam
{
	namespace box
	{
		class CProject : public ISerializable
		{
		public:
			IMPLEMENT_SERIALIZABLE(CProject, "project");

			/// @brief Constructor.
			/// 
			/// @param p_sPath Project folder.
			CProject(const QString &p_sPath);
			~CProject();

			/// @brief Retrieves path.
			/// 
			/// @return Project path.
			const QDir &GetPath() const {return m_sPath;}

			/// @brief Save the project.
			void Save();

			/// @brief Open the project.
			void Open();

		private:
			QDir m_sPath;				///< Project folder.
			QString m_sCurrentWorld;	///< Name of the current world.

			typedef std::vector<CPackage*> Packages;
			Packages m_aPackages; ///< Array of packages.

			typedef std::vector<QString> Worlds;
			Worlds m_apWorlds; ///< Array of attached world.

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Read(ISerializer *p_pContext);

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Write(ISerializer *p_pContext);
		};
	}
}
#endif // __SAMBOX_CPROJECT__
