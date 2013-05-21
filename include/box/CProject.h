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
#ifndef __PROJECT__
#define __PROJECT__

class CProject : public sam::ISerializable
{
	IMPLEMENT_SERIALIZABLE(CProject, "project");

public:
	struct SConfiguration : public wxObject
	{

	};

	/// @brief Default constructor.
	CProject();

	/// @brief Destructor.
	~CProject();

	/// @brief Initialize the project.
	/// 
	/// @param p_pConfig Configuration.
	bool Initialize(SConfiguration *p_pConfig);

	/// @brief Retrieve if the project have changed since the last save.
	/// 
	/// @return True if the project is dirty.
	bool IsDirty() const {return m_bIsDirty;}

	/// @brief Flag the project as dirty.
	void Dirty() {m_bIsDirty = true;}

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	void Read(sam::ISerializer *p_pContext);

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	void Write(sam::ISerializer *p_pContext);

private:
	SConfiguration *m_pConfiguration;
	bool m_bIsDirty;
};

#endif // __PROJECT__
